"""
TODO: Creacion de un cliente para un servicio

"""

#!/usr/bin/env python
import rospy
from paquete.srv import Mensaje, MensajeRequest

rospy.init_node('cliente_servicio') #Crea el topic
rospy.wait_for_service('/nombre_servicio')#Espera asta que el servicio se este ejecutando para ofrecer el servicio

#Se crea la conexion con el servicio
servicio = rospy.ServiceProxy("/servicio", "nombre del servicio")

#Se crea el objeto de "Tipo de mensaje" para enviarlo al servicio
peticion = MensajeRequest()
peticion.dato = "dato" #Asignacion de los datos a la peticion 

#Se envia la peticion al servicio 
resultado = servicio(peticion)

#Se imprime el resultado
print(resultado)
