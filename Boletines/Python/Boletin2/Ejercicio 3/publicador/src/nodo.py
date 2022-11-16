#!/usr/bin/env python3
import rospy
from ej1.msg import usuario

rospy.init_node('nodo')

#Creamos el topic donde vamos a publicar
pub = rospy.Publisher('usuarios', usuario, queue_size=10)

#Creamos la frecuencia de publicacion
rate = rospy.Rate(2)

while not rospy.is_shutdown():
    #Creamos el mensaje
    mensaje = usuario()
    mensaje.nombre = 'Juan'
    mensaje.edad = 20
    mensaje.coeficiente = 1.5
    
    pub.publish(mensaje)
    rate.sleep()