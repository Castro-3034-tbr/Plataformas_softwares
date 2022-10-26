#!usr/bin/env python3
import rospy
from prog1.msg import ObjetivoPresa
from std_srvs.srv import Empty, EmptyRequest
from std_msgs.msg import Bool
from turtlesim.msg import Pose
import math

def callback_objetivo_presa(req):
    """Funcion que se activira cuando hay un objetivo de la presa"""
    print(req)

def callback_resultado(req):
    """Funcion que se activara cuando hay un resultado"""
    global dato_resultado
    
    dato_resultado = req.data

def callback_pose_presa(req):
    """Funcion que se activara cuando hay una pose de la presa"""
    
    global pose_presa
    pose_presa = req

def callback_pose_predador(req):
    """Funcion que se activara cuando hay una pose del predador"""
    global pose_depredador
    pose_depredador = req

def calcular_distancia(pose1,pose2):
    """Calculo de la distancia entre dos puntos
    RETURN:FLOAT"""
    xb = pose1.x - pose2.x
    yb = pose1.y - pose2.y
    distancia = math.sqrt(xb * xb + yb * yb)
    
    return distancia


#Definicion de variables globales
umbral = 1
pose_presa = Pose()
dato_pose_presa = False
pose_depredador = Pose()
dato_pose_depredador = False

dato_resultado = False


#Creacion del nodo prog1
rospy.init_node('prog1')
rospy.loginfo('Nodo prog1 creado')

#Nos conectamos al servidor de servicio de creacion inicial 
rospy.wait_for_service('creacion_inicial')
rospy.loginfo('Servicio creacion_inicial disponible')

#Creamos la conexion inical 
creacion_inicial = rospy.ServiceProxy('creacion_inicial', Empty)
rospy.loginfo("Servicio creacion_inicial conectado")
peticion = EmptyRequest()
creacion_inicial(peticion)

#Creamos el topic objetivo_presa
objetivo_presa = rospy.Publisher('objetivo_presa', ObjetivoPresa, queue_size=10)

#Nos subcribimos a los topics 
rospy.Subscriber('objetivo_presa', ObjetivoPresa, callback_objetivo_presa)

rospy.Subscriber("resultado", Bool, callback_resultado)

while dato_pose_presa == False:
    rospy.Subcriber("presa/pose", Pose, callback_pose_presa)

while dato_pose_depredador == False:
    rospy.Subcriber("predador/pose", Pose, callback_pose_predador)

#Enviamos el objetivo de la presa
dato= ObjetivoPresa()

dato.x = 1
dato.y = 1

#Comienzo del movimiento del depredador detras de la presa 
distancia = calcular_distancia(pose_presa, pose_depredador)
while not rospy.is_shutdown() and distancia>umbral:
    #Movimiento del depredador
    
    #Recalculo de la distancia 