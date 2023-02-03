#!/usr/bin/env python3
import rospy
from movimientos.srv import DatosMovimientosPresa , DatosMovimientosPresaResponse
import math

def movimiento_presa(req):
    """Funcion que mueve la presa """
    
    #Leemos los datos recibidos
    pose_presa = req.PosePresa
    pose_objetivo = req.Objetivo
    
    #Calculo de la distancia 
    xb = pose_presa.x - pose_objetivo.x
    yb = pose_presa.y - pose_objetivo.y
    distancia = math.sqrt(xb*xb + yb*yb)
    
    #Calculo de las velocidades
    vel_linear_x = 1.5*math.sqrt(math.pow((pose_objetivo.x-pose_presa.x),2)+ math.pow((pose_objetivo.y - pose_presa.y),2))
    vel_angular_z = 4 * (math.atan2(pose_objetivo.y - pose_presa.y, pose_objetivo.x - pose_presa.x) - pose_presa.theta)

    #Creacion del mensaje de respuesta
    resultado = DatosMovimientosPresaResponse()
    resultado.VelocidadPresa.linear.x = vel_linear_x*0.300
    resultado.VelocidadPresa.angular.z = vel_angular_z
    resultado.Distancia = distancia
    
    return resultado 

#Creacion de nodo movimiento presa
rospy.init_node('nodo_movimiento_presa')
rospy.loginfo('Nodo movimiento presa iniciado')

srv_movimiento_presa = rospy.Service('servicio_movimiento_presa', DatosMovimientosPresa, movimiento_presa)
rospy.loginfo('Servicio de movimiento presa creado')

rospy.spin()