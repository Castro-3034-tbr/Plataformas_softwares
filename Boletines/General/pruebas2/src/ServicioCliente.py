#!/usr/bin/env python3
import rospy 
from pruebas2.srv import MensajeServicio, MensajeServicioRequest

#Creacion del nodo principal
rospy.init_node('cliente')
rospy.loginfo("Nodo cliente activado")

#Creacion del cliente
rospy.wait_for_service('Servicio')
rospy.loginfo("Servicio activado")

#Nos conectamos al servicio
servicio = rospy.ServiceProxy('Servicio', MensajeServicio)
rospy.loginfo("Servicio conectado")

#Creacion de la peticion
peticion = MensajeServicioRequest()
peticion.Peticion = 5

respuesta = servicio(peticion)
rospy.loginfo("Enviamos la peticion")

rospy.loginfo(respuesta)
