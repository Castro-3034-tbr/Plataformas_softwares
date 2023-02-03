#!/usr/bin/env python3
import rospy 
from pruebas.srv import MensajeServicio , MensajeServicioResponse

def callback(data):
    """Funcion que se ejecuta cuando se recibe cuando se pide una servicio"""
    rospy.loginfo("Peticion: {}".format(data.Peticion))
    return MensajeServicioResponse(data.Peticion*2)

#Creacion del nodo de un servicio
rospy.init_node("servidor_servicio")
rospy.loginfo("Nodo servidor_servicio iniciado")

#Creacion del servicio 
mi_servicio = rospy.Service("Servicio",MensajeServicio,callback)
rospy.loginfo("Servicio Servicio iniciado")

#Bucle    
rospy.spin()