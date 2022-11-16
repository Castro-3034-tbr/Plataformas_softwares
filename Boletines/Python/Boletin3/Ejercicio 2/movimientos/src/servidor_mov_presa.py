#!/usr/bin/env python3
import rospy
from std_srvs.srv import Empty, EmptyResponse
from geometry_msgs.msg import Twist
import random

def movimiento_presa(req):
    """Funcion que mueve la presa """
    
    #Puclicacion al topic de movimiento de la presa
    velocidades__presa = rospy.Publisher('/presa/cmd_vel', Twist, queue_size=1) 

    #Asiganmos valores al mensajes 
    vel_presa = Twist()
    vel_presa.linear.x= 0.3
    vel_presa.angular.z= 0.08
    
    #Enviamos los mensajes
    velocidades__presa.publish(vel_presa)
    
    rospy.loginfo("Se mueve la presa ")
    
    return EmptyResponse()

#Creacion de nodo movimiento presa
rospy.init_node('nodo_movimiento_pressa')
rospy.loginfo('Nodo movimiento presa iniciado')

srv_movimiento_presa = rospy.Service('servicio_movimiento_presa', Empty, movimiento_presa)
rospy.loginfo('Servicio de movimiento presa creado')

rospy.spin()