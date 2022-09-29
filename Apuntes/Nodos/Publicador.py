"""
TODO: Creacion de un node el que enviara informacion a un topic
"""

#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32

rospy.init_node("Primer nodo") #Para crear un nodo

pub = rospy.Publisher("laser", Int32, queue_size=10) #Para crear un topic y si existe el topic solo se conecta a el
a = Int32() #Comfiguramos a como un mensaje de tipo Int32
contador = 0 #Creamos una variable contador
rate = rospy.Rate(10) #Para crear un rate de 10Hz

while not rospy.is_shutdown(): #Mientras no se cierre el nodo 
    contador += 1
    a.data = contador
    pub.publish(a) #Publicamos el mensaje
    rate.sleep() #Esperamos el tiempo necesario para que el rate sea de 10Hz




rospy.spin() #Para que el nodo no se cierre, bucle infinito