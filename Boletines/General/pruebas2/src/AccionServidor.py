#!/usr/bin/env python3
import rospy
import actionlib
from pruebas2.msg import MensajeAccionAction, MensajeAccionGoal, MensajeAccionResult, MensajeAccionFeedback


class Servidor(object):
    """Clase para el servidor de accion"""
    __result = MensajeAccionResult()
    __feedback = MensajeAccionFeedback()
    
    def __init__(self):
        self.__act_server= actionlib.SimpleActionServer("Accion",MensajeAccionAction, self.goal_callback, False)
        self.__act_server.start()
    
    def goal_callback(self, goal):
        """Funcion que se ejecuta cuando llega una peticion"""
        datos= goal.goal
        rate = rospy.Rate(1)
        cancelado = False
        
        rospy.loginfo("Peticion: " + str(datos))
        
        #Procesamos la peticion
        for i in range(0, datos+1):
            self.__feedback.Feedback = i
            if self.__act_server.is_preempt_requested():
                rospy.loginfo("Peticion cancelada")
                self.__act_server.set_preempted()
                cancelado = True
                break
            #Enviamos el feedback
            self.__act_server.publish_feedback(self.__feedback)
            rospy.loginfo("Feedback: " + str(i))
            rate.sleep()
        
        if not cancelado:
            self.__result.Resultado = datos
            rospy.loginfo("Peticion completada")
            self.__act_server.set_succeeded(self.__result)


#Creacion del nodo principal
rospy.init_node('servidor_accion')
rospy.loginfo("Nodo servidor activado")

#Creacion del servidor
Servidor()
rospy.loginfo("Objeto cliente creado")

rospy.spin()
