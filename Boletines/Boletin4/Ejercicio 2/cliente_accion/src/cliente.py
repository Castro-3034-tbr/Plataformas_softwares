#!/usr/bin/env python3
from __future__ import print_function
import rospy
import actionlib
from servidor_accion.msg import MensajeServidorAction,MensajeServidorGoal, MensajeServidorResult, MensajeServidorFeedback

def fun_resultado(req,req2):
    """Funcion que se ejecuta cuando la accion devuelve el resultado"""
    print("Entra")
    print("Resultado:", req , "REq2", req2)

def fun_feedback(req):
    """Funcion que se ejecuta cuando la accion devuelve el feedback"""
    
    print("Feedback:", req)

#Creamos el nodo principal 
rospy.init_node("cliente")
rospy.loginfo("nodo Cliente creado")


#Creamos el cliente al servicioç
cliente = actionlib.SimpleActionClient("servidor_accion",MensajeServidorAction)
cliente.wait_for_server()
rospy.loginfo("Servidor de accion disponible")

#Creamos el mensaje de goal
goal = MensajeServidorGoal()
goal.ciclos_umbral= 15
print("Goal:", goal)


#Enviamos el mensaje al servidor
cliente.send_goal(goal,done_cb=fun_resultado ,feedback_cb=fun_feedback)

rospy.spin()