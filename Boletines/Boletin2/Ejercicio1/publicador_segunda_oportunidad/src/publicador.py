#!/usr/bin/env python3
from random import randint,choice
import rospy
from Ej1a.msg import msg_ex
#Creacion de variables globales
opciones = ["iniciar", "continuar", "interrumpir"]

#Creacion del nodo
rospy.init_node("publicador")

#Creacion del topic 
consigna = rospy.Publisher('consigna', msg_ex, queue_size=10)

#Creacion del mensaje 
mensaje = msg_ex()
#Creacion de la frecuencia del bucle 
rate = rospy.Rate(1)

#Bucle
while not rospy.is_shutdown():
    
    #Añadimos los datos al mensaje
    mensaje.comando  = choice(opciones)
    
    mensaje.tiempo=randint(30,100)
    
    mensaje.point.position.x=randint(0,100)
    mensaje.point.position.y=randint(0,100)
    mensaje.point.position.z=randint(0,100)
    
    mensaje.point.orientation.x=randint(0,100)
    mensaje.point.orientation.y=randint(0,100)
    mensaje.point.orientation.z=randint(0,100)
    
    #Publicamos el mensaje
    consigna.publish(mensaje)