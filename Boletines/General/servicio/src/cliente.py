#!/usr/bin/env python3
import rospy 
import actionlib
from pruebas.msg import MensajeAccionAction, MensajeAccionGoal

def active ():
    rospy.loginfo("Accion activa")

def done (estado, resultado):
    rospy.loginfo("Accion terminada")
    rospy.loginfo("Estado: " + str(estado))
    rospy.loginfo("Resultado: " + str(resultado))

def feedback (feedback):
    global cliente
    rospy.loginfo("Feedback: " + str(feedback))
    if feedback.Feedback == 300:
        cliente.cancel_goal()
        rospy.loginfo("Peticion cancelada")

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
peticion.Peticion = 14

#Envio de la peticion
cliente.send_goal(peticion, done_cb=done, active_cb=active, feedback_cb= feedback)
rospy.loginfo("Peticion enviada")

#Espera de la respuesta
cliente.wait_for_result()
rospy.loginfo("Respuesta recibida")
