#!/usr/bin/env python3
import rospy 
from Ej1a.msg import msg_ex

def muestreo(msg):
    """
    Funcion para mostar la informacion del mensaje

    """
    print(msg)

#Creacion del nodo 
rospy.init_node("subcriptor")

#Creacion del la suscripcion
rospy.Subscriber("consigna", msg_ex, muestreo)

rospy.spin()