#!/usr/bin/env python3
import rospy
from prog1.msg import ObjetivoPresa
from movimientos.srv import mover_presa

def callback_objetivo_presa(req):
    """Funcion que se activira cuando hay un objetivo de la presa"""
    global objetivo_presa
    
    objetivo_presa = req
    
    #Invocacion del servicion de control de la presa
    

#Definicion de variables globales
objetivo_presa = ObjetivoPresa()

#Creacion de nodo prog2
rospy.init_node('prog2')
rospy.loginfo('Nodo prog2 creado')

#Esperamos por los servicios
rospy.wait_for_service("/mover_presa")
rospy.loginfo('Servicio mover_presa disponible')


#Subcripcion al topic objetivo presa 
rospy.Subscriber("/objetivo_presa", ObjetivoPresa, callback_objetivo_presa)

