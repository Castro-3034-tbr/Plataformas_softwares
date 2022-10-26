#!/usr/bin/env python3
import rospy 
from ej1.msg import usuario

rospy.init_node('subcribtor')

#Subcripcion al topic usuario
def callback(data):
    print(data)

rospy.Subscriber('usuarios', usuario, callback)

rospy.spin()