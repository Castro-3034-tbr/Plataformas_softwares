""" 
TODO: Creacion de nodo para poder subscribirse a un topic
"""
#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32

def callback(msg):
    """
    Funcion que se ejecuta cuando se recibe un mensaje
    """
    print ( msg )

rospy.init_node('lectura')#Creamos el nodo
rospy.Subscriber('laser', Int32, callback) #Nos suscribimos al topic laser

rospy.spin() #Mantener el nodo activo