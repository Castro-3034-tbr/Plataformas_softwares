"""
TODO: Creacion de un servidor de accion
"""

#!/usr/bin/env python3
from sre_constants import SUCCESS
import rospy
import actionlib

from servidor_action.msg import MensajeAction,MensajeResult,MensajeFeedback #Importamos los mensajes de la accion desde el paquete donde estan definidos 

class accion_simple(object):
    #Creamos dos variables privadas que seran mensajes 
    __retroalimentacion = MensajeFeedback()
    __resultado = MensajeResult()
    
    def __init__(self):
        #Creamos el servidor 
        self.__act_serv= actionlib.SimpleActionServer("accion_servidor",MensajeAction,self.goal_callback,False) 
        #Iniciamos el servidor
        self.__act_serv.start()
    
    def goal_callback(self,datos):
        """Funcion que se ejecuta cuando se pide una accion al servidor
        RETURN: MensajeResult
        """
        #Creamos la variable con los datos que llegan a la accion
        Datos = datos.goal 
        
        #Definimos la variable del estado de la accion
        succes = False
        
        #Definimos una variable par el estado de cancelado
        cancelado = False
        #Creamos un bucle 
        while True :
            
            #<--> Acciones <-->
            
            #Comprobamos que no hay una cancelacion anticipateda 
            if self.__act_serv.is_preempt_requested():
                #Fijamos el estado de la accion como cancelada anticipatedamente 
                cancelado = True
                self.__act_serv.set_preempted() 
                break
            
            #Definimos el valor del feedback
            self.__retroalimentacion.feedback = 1 
            #Publicamos el valor del feedback
            self.__act_serv.publish_feedback(self.__retroalimentacion)
        
        #Comprobamos si el proceso esta finalizado
        if cancelado== False :
            if succes:
                #Definimos el valor del resultado
                self.__resultado.resultado = 1
                #Ponemos el estado como finalizado y devolvemos el resultado
                self.__act_serv.set_succeeded(self.__resultado)
            else :
                #Definimos el estado como abortado pero si no fue cancelada anticipatedamente
                self.__act_serv.set_aborted() 

#FIXME:Modulo principal

rospy.init_node("accion_servidor")#Inciamos el nodo de accion_servidor
accion_simple() #Creamos la clase 
rospy.spin()