#!/usr/bin/env python3

from tkinter import N
import rospy
from std_msgs.msg import Int32

i = 0
suma = 0
numero = 0  

def callback(mensaje):
    """
    Funcion para obetener el valor del mensaje
    """
    global i, suma , respuesta
    i += 1
    numero = mensaje.data
    
    suma += numero
    print(numero ,"La suma es: ", suma, "I", i)
    
    if i == 10:
        print("condicion cumplida")
        respuesta.publish(suma)
        i = 0
        suma = 0


rospy.init_node('nodo_B')
rospy.loginfo('Nodo B iniciado')


#Nos subcribimos al nodo 
rospy.Subscriber('nodo_A', Int32, callback)

print("La suma es: ", suma)
#Enviamos el resultado de la suma por un nuevo topic 
respuesta = rospy.Publisher('respuesta_B', Int32, queue_size=10)
print("i es: ", i)


rospy.spin()