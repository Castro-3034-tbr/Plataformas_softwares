#!/usr/bin/env python3
from urllib import response
import rospy
from std_srvs.srv import Empty, EmptyResponse
from turtlesim.srv import Spawn , SpawnRequest , Kill , KillRequest


def creacion_personajes(req):
    """Funcion que crea los personajes presa y depredador"""
    
    #FIXME: Creacion de presa y depredador

    # Esperamos por el servicio 
    rospy.wait_for_service("/spawn")
    rospy.loginfo("Servicio /spawn available")
    rospy.wait_for_service("/kill")
    rospy.loginfo("Servicio /kill available")

    #Conectamos con el servicio
    s_spawn = rospy.ServiceProxy("/spawn", Spawn)
    rospy.loginfo("Servicio /spawn conect")

    #Mandamos los valores al servicio
    datos_presa = SpawnRequest()
    datos_presa.x = 5.0
    datos_presa.y = 10.0
    datos_presa.theta = 3.1416
    datos_presa.name = "presa"
    presa = s_spawn(datos_presa)
    rospy.loginfo("Presa created")
    datos_depredador = SpawnRequest()
    datos_depredador.x = 5.0
    datos_depredador.y = 5.0
    datos_depredador.theta = 6.0
    datos_depredador.name = "depredador"
    depredador = s_spawn(datos_depredador)
    rospy.loginfo("Depredador created")


    #Matamos el objeto tutlet1
    s_kill = rospy.ServiceProxy("/kill",Kill)
    rospy.loginfo("Servicio /kill conect")
    m_kill = KillRequest()
    m_kill.name = "turtle1"
    turtle1 = s_kill(m_kill)
    rospy.loginfo("turtle1 removed ")
    
    return EmptyResponse()

#Creacion del nodo 
rospy.init_node('servidor_creacion')
rospy.loginfo('Nodo servidor_creacion creado')

#Creacion del servidor para crear
servicio_creacion = rospy.Service('servicio_creacion', Empty, creacion_personajes)
rospy.loginfo('Servicio de creacion creado')

rospy.spin()