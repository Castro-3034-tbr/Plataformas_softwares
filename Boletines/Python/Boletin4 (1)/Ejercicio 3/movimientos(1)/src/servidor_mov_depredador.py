#!/usr/bin/env python3
import rospy
from movimientos.srv import DatosMovimientoDepredador, DatosMovimientoDepredadorResponse
import math

def movimiento_depredador(req):
    """Funcion para mover el depredador """
    print("Hola")
    print(req)
    
    #Leemos los datos recibidos 
    pose_presa = req.PosePresa
    pose_depredador = req.PoseDepredador
    
    
    
    #Calculo de la distancia entre la presa y el depredador
    xb = pose_presa.x - pose_depredador.x
    yb = pose_presa.y - pose_depredador.y
    distancia = math.sqrt(xb*xb + yb*yb)
    
    #Calculo de las velocidades
    vel_linear_x = 1.5*math.sqrt(math.pow((pose_presa.x-pose_depredador.x),2)+ math.pow((pose_presa.y - pose_depredador.y),2))
    vel_angular_z = 4 * (math.atan2(pose_presa.y - pose_depredador.y, pose_presa.x - pose_depredador.x) - pose_depredador.theta)
    
    #Creacion del mensaje de respuesta
    resultado =  DatosMovimientoDepredadorResponse()
    resultado.VelocidadDepredador.linear.x = vel_linear_x*0.300
    resultado.VelocidadDepredador.angular.z = vel_angular_z
    resultado.Distancia = distancia
    
    print(resultado)
    return resultado


#Creamos el nodo de movimiento de depredador
rospy.init_node('nodo_movimiento_depredador')
rospy.loginfo("Nodo movimiento depredador iniciado")

#Creacion del servicio de movimiento de depredador
srv_movimiento_depredador= rospy.Service('servicio_movimiento_depredador',DatosMovimientoDepredador, movimiento_depredador)
rospy.loginfo("Servicio movimiento depredador creado")

rospy.spin()