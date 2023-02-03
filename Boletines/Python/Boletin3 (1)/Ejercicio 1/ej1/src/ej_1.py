#!/usr/bin/python3
import math
from pickletools import read_uint1
import rospy
from turtlesim.srv import Spawn, SpawnRequest, Kill, KillRequest
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist



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
    

def leer_velocidad_presa(msg):
    """Lectura de la velocidad de la presa """ 
    global datos_velocidad_presa 
    
    datos_velocidad_presa = msg

def leer_velocidad_depredador(msg):
    """Lectura de la velocidad del depredador """ 
    global datos_velocidad_depredador 
    
    datos_velocidad_depredador = msg
    

def calculo_distancia(pose1, pose2):
    """
    Calculo de la distancia de separacion entre dos elementos 
    RETURN: FLOAT
    """
    xb = pose1.x - pose2.x
    yb = pose1.y - pose2.y
    distancia = math.sqrt(xb * xb + yb * yb)
    
    return distancia

#Creacion del nodo
rospy.init_node('Simulador_tortuga')
rospy.loginfo("Nodo cliente running")

#Declaracion de variable globales
umbral = 1
rate = rospy.Rate(4)



#FIXME: Creacion de presa y depredador

# Esperamos por el servicio 
rospy.wait_for_service("/spawn")
rospy.loginfo("Servicio /spawn available")
rospy.wait_for_service("/kill")
rospy.loginfo("Servicio /kill available")

#Conectamos con el servicio
s_spawn = rospy.ServiceProxy("/spawn", Spawn)
rospy.loginfo("Servicio /spawn conect")

#Mandamos los valores al servicio
datos_presa = SpawnRequest()
datos_presa.x = 5.0
datos_presa.y = 10.0
datos_presa.theta = 3.1416
datos_presa.name = "presa"
presa = s_spawn(datos_presa)
rospy.loginfo("Presa created")


datos_depredador = SpawnRequest()
datos_depredador.x = 5.0
datos_depredador.y = 5.0
datos_depredador.theta = 6.0
datos_depredador.name = "depredador"
depredador = s_spawn(datos_depredador)
rospy.loginfo("Depredador created")


#Matamos el objeto tutlet1
s_kill = rospy.ServiceProxy("/kill",Kill)
rospy.loginfo("Servicio /kill conect")
m_kill = KillRequest()
m_kill.name = "turtle1"
turtle1 = s_kill(m_kill)
rospy.loginfo("turtle1 removed ")

#FIXME:Moviminto para presa y depredador
rospy.sleep(1)

#Posicion de la presa
pose_presa  = Pose()
pose_depredador= Pose()
dato_presa=False
dato_depredador=False

while not dato_presa:
    rospy.Subscriber("presa/pose",Pose,obtener_pose_presa)

while not dato_depredador:
    rospy.Subscriber("depredador/pose",Pose,obtener_pose_depredador)


#Subcripcion al topic de velocidad de ambos elementos
datos_velocidad_presa = Twist()
datos_velocidad_depredador = Twist()
velocidad_presa = rospy.Publisher("presa/cmd_vel",Twist,queue_size=10)
velocidad_depredador = rospy.Publisher("depredador/cmd_vel",Twist,queue_size=10)

rospy.loginfo("Empezamos el movimineto")

#Bucle de movimiento
while calculo_distancia(pose_presa,pose_depredador)>umbral and not rospy.is_shutdown() :
    vel_linear_x = 1.5*math.sqrt(math.pow((pose_presa.x-pose_depredador.x),2)+ math.pow((pose_presa.y - pose_depredador.y),2))
    vel_angular_z = 4 * (math.atan2(pose_presa.y - pose_depredador.y, pose_presa.x - pose_depredador.x) - pose_depredador.theta)
    
    #Asignacion de datos a la velocidad de la presa
    datos_velocidad_presa.linear.x = 0.3
    datos_velocidad_presa.angular.z = 0.08
    
    #Asignacion de datos a la velocidad del depredador
    datos_velocidad_depredador.linear.x = vel_linear_x*0.300
    datos_velocidad_depredador.angular.z = vel_angular_z
    
    #Publicacion de los datos
    velocidad_presa.publish(datos_velocidad_presa)
    velocidad_depredador.publish(datos_velocidad_depredador)
    
    #Impresion de la distancia 
    print("Distancia: ",calculo_distancia(pose_presa,pose_depredador))
    
    rate.sleep()

print("El depredador a cogido la presa")