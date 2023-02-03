#!/usr/bin/env python3
import rospy 
import actionlib
from std_srvs.srv import Empty, EmptyRequest
from nodo_cracion.srv import DatosCreacion , DatosCreacionRequest
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
import math

def callback_posicion_presa(req):
    """Funcion que se ejecuta cuando se recibe la posicion de la presa"""
    
    global posicion_presa, encontrado_presa 
    
    posicion_presa = req
    encontrado_presa = True

def callback_posicion_depredador(req):
    """Funcion que se ejecuta cuando se recibe la posicion del depredador"""
    
    global posicion_depredador, encontrado_depredador 
    
    posicion_depredador = req
    encontrado_depredador = True



#Creamos el nodo cliente 
rospy.init_node('cliente')
rospy.loginfo('Nodo cliente iniciado')

#Esperamos por los servicios 
rospy.wait_for_service('/servicio_creacion')
rospy.loginfo('Servicio de creacion disponible')
rospy.wait_for_service('/servicio_movimiento_presa')
rospy.loginfo('Servicio de movimiento presa disponible')
rospy.wait_for_service('/servicio_movimiento_depredador')
rospy.loginfo('Servicio de movimiento depredador disponible')

#Esperamos por las acciones 

#Invocamos el servicio de creacion

creacion_personajes = rospy.ServiceProxy('/servicio_creacion', DatosCreacion)
rospy.loginfo('Servicio de creacion conectado')

peticion_creacion = DatosCreacionRequest()
peticion_creacion.PoseDepredador.x = 9
peticion_creacion.PoseDepredador.y = 10
peticion_creacion.PoseDepredador.theta = 3.14

peticion_creacion.PosePresa.x = 1
peticion_creacion.PosePresa.y = 1
peticion_creacion.PosePresa.theta = 6

personajes = creacion_personajes(peticion_creacion)
rospy.loginfo('Personajes creados')

#FIXME: Movimiento de los personajes

#Subcripcion de la posicion de los personajes
posicion_presa= Pose()
posicion_depredador = Pose()
encontrado_presa = False 
encontrado_depredador = False
rate_sub = rospy.Rate(10)

rospy.Subscriber('/presa/pose', Pose, callback_posicion_presa)
rospy.Subscriber('/depredador/pose', Pose, callback_posicion_depredador)

while not encontrado_presa and encontrado_depredador:
    rate_sub.sleep()

#Subcripcion de la velocidad de los personajes

velocidad_depredador = Twist()
encontrado_velocidad_depredador = False

velocidad_depredador = rospy.Publisher('/depredador/cmd_vel', Twist, queue_size=10)

#Iniciamos la accion de movimiento

#Empezamos el bucle de movimiento
