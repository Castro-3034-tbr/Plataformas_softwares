#!/usr/bin/env python3
import rospy
from movimientos.srv import DatoMovimiento, DatoMovimientoResponse
from geometry_msgs.msg import Twist
import math

def movimiento_depredador(req):
    """Funcion para mover el depredador """
    
    #Definicion de variables locales 
    distancia = req.distancia
    presa_pose = req.pose_presa
    depredador_pose = req.pose_depredador
    
    #Calculo de las velocidades
    vel_linear_x = 1.5*math.sqrt(math.pow((presa_pose.x-depredador_pose.x),2)+ math.pow((presa_pose.y - depredador_pose.y),2))
    vel_angular_z = 4 * (math.atan2(presa_pose.y - depredador_pose.y, presa_pose.x - depredador_pose.x) - depredador_pose.theta)
    
    #Publicacion de las velocidades
    datos_velocidades = Twist()
    velocidad_depredador = rospy.Publisher("depredador/cmd_vel",Twist,queue_size=10)
    
    #Publicacion 
    datos_velocidades.linear.x = vel_linear_x*0.300
    datos_velocidades.angular.z = vel_angular_z
    velocidad_depredador.publish(datos_velocidades)
    
    return DatoMovimientoResponse()


#Creamos el nodo de movimiento de depredador
rospy.init_node('nodo_movimiento_depredador')
rospy.loginfo("Nodo movimiento depredador iniciado")

#Creacion del servicio de movimiento de depredador
srv_movimiento_depredador= rospy.Service('servicio_movimiento_depredador',DatoMovimiento, movimiento_depredador)

rospy.spin()