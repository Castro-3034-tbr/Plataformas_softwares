#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32

def callback(mensaje):
    print("El valor del mensaje es: ", mensaje.data)

rospy.init_node('nodo_A')

#Creamos el topic donde vamos a publicar el numero que se pide por terminal

nodoA = rospy.Publisher('nodo_A', Int32, queue_size=10)

while True:
    numero = int(input('Introduce un numero: '))
    num = Int32()

    nodoA.publish(numero)

    #Lectura del topic respuesta_B
    #rospy.Subscriber('respuesta_B', Int32, callback)

rospy.spin()