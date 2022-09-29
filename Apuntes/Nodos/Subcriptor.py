""" 
TODO: Creacion de nodo para poder subscribirse a un topic
"""
#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32

def hola(msg):
    print ( msg )

rospy.init_node('lectura')#Creamos el nodo de lectura
rospy.Subscriber('laser', Int32, hola) #Nos suscribimos al topic laser

rospy.spin() #Mantener el nodo activo