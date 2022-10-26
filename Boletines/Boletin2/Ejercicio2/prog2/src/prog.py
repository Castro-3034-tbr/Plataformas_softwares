#!/usr/bin/env python3
import rospy
from std_msgs.msg import Bool
from prog1.msg import posicion #Importamos el mensaje personalizado
import random

#Funcion que se ejecuta cuando llega un mensaje
def callback(data):
    """
    Funcion que se ejecuta cuando llega un mensaje
    """
    
    #Generamos un booleano aleatorio
    respu = Bool()
    booleano = bool(random.randint(0, 1))
    respu.data = booleano
    
    #Enviamos el mensaje en el topic "respuesta"
    respuesta.publish(respu)
    

#Creacion de un nodo 
rospy.init_node("prog2")

#Subcribimos al nodo Objetivo_presa
rospy.Subscriber('objetivo_presa', posicion, callback)

#Creamos el publicador para reenviar el mensaje
respuesta = rospy.Publisher('respuesta', Bool, queue_size=10)

#Generamos el bucle infinito
rospy.spin()