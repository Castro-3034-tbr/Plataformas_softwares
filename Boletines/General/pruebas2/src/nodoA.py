#!/usr/bin/env python3
import rospy 
from pruebas2.msg import Mensaje


#Creamos el nodo principal 
rospy.init_node("NodeA")

#Creamos un publicador
pub = rospy.Publisher("TopicA", Mensaje, queue_size=10)

#Creamos un objeto de tipo Mensaje
msg = Mensaje()

contador = 0
rospy.sleep(1)

#Creamos un bucle para enviar mensajes 
while not rospy.is_shutdown():
    contador += 1
    msg.A = contador
    
    print ("Publicando mensaje: ", msg.A)
    
    pub.publish(msg)
    
    rospy.sleep(1)
