"""
TODO: Creacion de un servidor para un servicio
"""


#!/usr/bin/env python
import rospy
from std_srvs.srv import Empty, EmptyResponse #Importa el tipo de mensaje que necesitamos 

def mi_callback(request):
    """
    Funcion que sera ejecutada cuando se llame al servicio mi_servicio
    """
    print("Peticion recibida")
    return (EmptyResponse) #Retorno un mensaje vacio 

rospy.init_node('servidor') #Inicializa el nodo
mi_servicio = rospy.Service("mi_servicio", Empty, mi_callback) #Crea el servicio. Argumentos: Nombre del servicio, Tipo de mensaje, Funcion que se ejecuta cuando se recibe una peticion

rospy.spin() #Mantiene el nodo activo