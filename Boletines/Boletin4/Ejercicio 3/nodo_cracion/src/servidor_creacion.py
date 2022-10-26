#!/usr/bin/env python3
import rospy
from turtlesim.srv import Spawn , SpawnRequest , Kill , KillRequest
from nodo_cracion.srv import DatosCreacion, DatosCreacionRequest

def creacion_personajes(req):
    """Funcion que crea los personajes presa y depredador"""
    #Leemos los datos que llegan al callbak
    pose_presa = req.PosePresa
    pose_depredador = req.PoseDepredador
    
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
    datos_presa.x = pose_presa.x
    datos_presa.y = pose_presa.y
    datos_presa.theta = pose_presa.theta
    datos_presa.name = "presa"
    presa = s_spawn(datos_presa)
    rospy.loginfo("Presa created")
    datos_depredador = SpawnRequest()
    datos_depredador.x =pose_depredador.x
    datos_depredador.y = pose_depredador.y
    datos_depredador.theta = pose_depredador.theta
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
    
    return DatosCreacionRequest()

#Creacion del nodo 
rospy.init_node('servidor_creacion')
rospy.loginfo('Nodo servidor_creacion creado')

#Creacion del servidor para crear
servicio_creacion = rospy.Service('servicio_creacion', DatosCreacion, creacion_personajes)
rospy.loginfo('Servicio de creacion creado')

rospy.spin()