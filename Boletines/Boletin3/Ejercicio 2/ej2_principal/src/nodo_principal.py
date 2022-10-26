#!/usr/bin/env python3
import rospy 
from std_srvs.srv import Empty, EmptyRequest
from movimientos.srv import DatoMovimiento, DatoMovimientoRequest
from turtlesim.msg import Pose
import math


def obtener_pose_presa(msg ):
    """
    Funcion para obtener la pose del elemento
    """
    global pose_presa, dato_presa
    
    dato_presa = True
    pose_presa =msg

def obtener_pose_depredador(msg):
    """
    Funcion para obtener la pose del depredador
    """
    global pose_depredador,dato_depredador
    
    dato_depredador = True
    pose_depredador =msg
    

def calculo_distancia(pose1, pose2):
    """
    Calculo de la distancia de separacion entre dos elementos 
    RETURN: FLOAT
    """
    xb = pose1.x - pose2.x
    yb = pose1.y - pose2.y
    distancia = math.sqrt(xb * xb + yb * yb)
    
    return distancia

#Creamos el nodo principal
rospy.init_node('nodo_principal')
rospy.loginfo('Nodo principal iniciado')

#Creacion de variables globales
rate= rospy.Rate(4)
pose_presa  = Pose()
pose_depredador= Pose()
dato_presa=False
dato_depredador=False
umbral = 1

#Esperamos por los servidores de servicios 
rospy.wait_for_service('/servicio_creacion')
rospy.loginfo('Servicio de creacion disponible')
rospy.wait_for_service('/servicio_movimiento_presa')
rospy.loginfo('Servicio de movimiento presa disponible')
rospy.wait_for_service('/servicio_movimiento_depredador')
rospy.loginfo('Servicio de movimiento depredador disponible')

#Creamos el cliente para el servicio de creacion
creacion_personajes = rospy.ServiceProxy('/servicio_creacion', Empty)
rospy.loginfo('Servicio de creacion conectado')

peticion = EmptyRequest()
personajes = creacion_personajes(peticion)
rospy.loginfo('Personajes creados')

#FIXME: Movimento de los personajes

#Obtencion de los datos de las posiciones de los personajes 
rate = rospy.Rate(10)
rospy.Subscriber("presa/pose",Pose,obtener_pose_presa)
while not dato_presa:
    rate.sleep()

print("Pose presa: ", pose_presa)
rospy.Subscriber("depredador/pose",Pose,obtener_pose_depredador)
while not dato_depredador:
    rate.sleep()

print("Pose depredador: ", pose_depredador)


#Conectamos a servicio del movimiento de la presa
movimiento_presas = rospy.ServiceProxy('/servicio_movimiento_presa', Empty)
rospy.loginfo('Servicio de movimiento presa conectado')

#Conectamos al servicio del movimiento del depredador
moviento_depredador = rospy.ServiceProxy('/servicio_movimiento_depredador', DatoMovimiento)
rospy.loginfo('Servicio de movimiento depredador conectado')

distancia = calculo_distancia(pose_presa,pose_depredador)

while distancia > umbral and not rospy.is_shutdown():
    
    #Movimiento de la presa 
    peticion = EmptyRequest()
    movimiento_presas(peticion)
    
    #Movimiento del depredador
    peticion_depredador = DatoMovimientoRequest()
    peticion_depredador.distancia = distancia
    peticion_depredador.pose_depredador = pose_depredador
    peticion_depredador.pose_presa = pose_presa
    moviento_depredador(peticion_depredador)
    
    #Recalculacion de la distacia
    distancia = calculo_distancia(pose_presa,pose_depredador)
    
    rate.sleep()
