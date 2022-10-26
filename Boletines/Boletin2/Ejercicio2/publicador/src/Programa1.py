#!/usr/bin/env python3
import rospy
from prog1.msg import posicion #Importamos el mensaje personalizado 
from std_msgs.msg import Bool
import random

def callback(mensaje):
    """
    Funcion que se ejecuta cuando llega un mensaje
    """
    global resultado
    if mensaje.data == True:
        """Terminamos el programa"""
        resultado = True
    else:
        print("Continuamos")

#Inializamos el nodo 
rospy.init_node("prog1")

resultado = False
#Creamos el publicador Objetivo_presa
objetivo = rospy.Publisher('objetivo_presa', posicion, queue_size=10)

#Creamos el mensaje
mensaje = posicion()

rate = rospy.Rate(1)

while not rospy.is_shutdown() or resultado == False:
    rospy.Subscriber("respuesta", Bool, callback)
    mensaje.x = random.randint(0, 1)
    mensaje.y = random.randint(0, 1)
    objetivo.publish(mensaje)
    rate.sleep()