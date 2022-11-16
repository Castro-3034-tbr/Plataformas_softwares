"""
TODO: Creacion de un servidor con mensajes personalizados
"""

#!/usr/bin/env python3
import rospy
from mi_paquete.srv import MiMensaje, MiMensajeResponse 

def mi_callback(request):
    """
    Funcion que sera ejecutada cuando se llame al servicio mi_servicio
    """
    #Definimos el mensaje de respuesta y añadimos rellenamos el campo respuesta
    mi_respuesta = MiMensajeResponse()
    mi_respuesta.exito = True
    
    print("Se ha ejecutado el servicio mi_servicio")
    return (mi_respuesta)


#Creacion del nodo 
rospy.init_node('Servicio_mensajes_personalizados')
mi_servicio = rospy.Service('mi_servicio', MiMensaje, mi_callback)
rospy.spin()