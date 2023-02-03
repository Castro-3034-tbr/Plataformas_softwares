#!/usr/bin/env python3
import rospy 
from pruebas2.srv import MensajeServicio, MensajeServicioResponse



def callback(request):
    print("Peticion: ", request.Peticion)
    respuesta = MensajeServicioResponse()
    respuesta.Resultado = request.Peticion * 2
    return respuesta

#Creacion del nodo principal
rospy.init_node('servicio')
rospy.loginfo("Nodo servicio activado")

#Creacion del servicio
mi_servicio = rospy.Service('Servicio', MensajeServicio, callback)
rospy.loginfo("Servicio activado")

rospy.spin()