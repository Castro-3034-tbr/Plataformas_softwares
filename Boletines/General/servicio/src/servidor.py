#!/usr/bin/env python3
import rospy 
import actionlib
from pruebas.msg import MensajeAccionAction, MensajeAccionGoal, MensajeAccionResult, MensajeAccionFeedback

class ServidorAccion(object):
    #Creacion de las varibles privadas 
    __feedback = MensajeAccionFeedback()
    __result = MensajeAccionResult()
    
    def __init__(self):
        self.__servidor = actionlib.SimpleActionServer('Accion', MensajeAccionAction, self.__ejecutar, False)
        self.__servidor.start()
        rospy.loginfo("Servidor iniciado")
    
    def __ejecutar(self, peticion):
        
        dato = peticion.Peticion
        rospy.loginfo("Peticion: " + str(dato))
        
        rate = rospy.Rate(1)
        
        cancelado = False
        
        for i in range(1, dato + 1):
            if self.__servidor.is_preempt_requested():
                rospy.loginfo("Peticion cancelada")
                self.__servidor.set_preempted()
                cancelado = True
                break
            self.__feedback.Feedback = i
            self.__servidor.publish_feedback(self.__feedback)
            rate.sleep()
        
        if cancelado == False:
            self.__result.Resultado = 13
            rospy.loginfo("Peticion terminada")
            self.__servidor.set_succeeded(self.__result)
    

#Creacion del nodo principal
rospy.init_node('servidor_accion')
rospy.loginfo("Nodo servidor activado")

#Creacion del servidor
servidor = ServidorAccion()

#Bucle 
rospy.spin()
