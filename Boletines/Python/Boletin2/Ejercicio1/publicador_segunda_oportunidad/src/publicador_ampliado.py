#!/usr/bin/env python3
from random import *
import rospy
from Ej1a.msg import msg_ampliado

#Creacion del nodo principal
rospy.init_node("publicador_ampliado")

#Creacion del nodo publicador
publicador = rospy.Publisher("consigna", msg_ampliado, queue_size=1)

mensaje = msg_ampliado()

rate = rospy.Rate(10)

while not rospy.is_shutdown():
    #Rellenar el mensaje
    mensaje.comando = choice(["iniciar", "continuar", "interrumpir"])
    mensaje.tiempo = randint(30, 100)
    
    mensaje.point.position.x = randint(0, 100)
    mensaje.point.position.y = randint(0, 100)
    mensaje.point.position.z = randint(0, 100)
    
    mensaje.point.orientation.x = randint(0, 100)
    mensaje.point.orientation.y = randint(0,100)
    mensaje.point.orientation.z = randint(0, 100)
    
    mensaje.cadena = "Hola mundo"
    
    mensaje.resultado = choice([True, False])
    
    #Publicar el mensaje+
    publicador.publish(mensaje)
    