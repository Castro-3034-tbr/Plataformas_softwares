#!/usr/bin/env python3
import rospy 
import actionlib
from pruebas2.msg import MensajeAccionAction, MensajeAccionGoal

def done(resutl, result2):
    print("Resultado",result2.Resultado)
    
def active():
    rospy.loginfo("Accion activa")

def feedback(feedback):
    global cliente
    rospy.loginfo(feedback)
    if feedback == 3:
        rospy.loginfo("Accion cancelada")

#Creacion del nodo principal
rospy.init_node('cliente_accion')
rospy.loginfo("Nodo cliente activado")

#Creacion del cliente
cliente = actionlib.SimpleActionClient('Accion', MensajeAccionAction)
rospy.loginfo("Accion activada")
cliente.wait_for_server()
rospy.loginfo("Accion conectada")

#Creacion de la peticion
peticion = MensajeAccionGoal()
peticion.goal = 5

#Enviamos la peticion
cliente.send_goal(peticion, done_cb =  done , active_cb = active, feedback_cb = feedback)
cliente.wait_for_result()