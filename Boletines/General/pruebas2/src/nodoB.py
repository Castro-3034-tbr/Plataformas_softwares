#!/usr/bin/env python3
import rospy 
from pruebas2.msg import Mensaje
from std_msgs.msg import Int32

#Creamos el nodo principal 
rospy.init_node("NodeB")

def callback(msg):
    global pub
    print ("Recibido: ", msg.A)
    mensaje = Int32()
    mensaje.data = msg.A*2
    pub.publish(mensaje)

#Creamos un publicador
pub = rospy.Publisher("TopicB", Int32, queue_size=10)
sub = rospy.Subscriber("TopicA", Mensaje, callback)

rospy.spin()