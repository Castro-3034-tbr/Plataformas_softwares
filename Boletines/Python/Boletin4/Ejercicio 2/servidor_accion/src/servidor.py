#!/usr/bin/env python3
import rospy
import actionlib

#Importacion de los mensajes 
from servidor_accion.msg import MensajeServidorAction,MensajeServidorResult,MensajeServidorFeedback

class servidor_accion(object):
    """Clase del servidor de accion """
    
    #Creamos las variables privadas
    __retroalimentacion = MensajeServidorFeedback()
    __resultado = MensajeServidorResult()
    
    def __init__(self):
        """Constructor de la clase"""
        #Creamos el servidor de accion
        self.__act_serv = actionlib.SimpleActionServer("servidor_accion",MensajeServidorAction,self.goal_callback,False)
        #Iniciamos el servidor de accion
        self.__act_serv.start()
        print("Creado")
    
    def goal_callback(self,datos):
        """
        Funcion que se ejecuta cuando se pide a accion al servidor
        """
        #Creamos las variables locales
        rospy.loginfo("Accion iniciada")
        ciclos = datos.ciclos_umbral
        print("Ciclos:",ciclos)
        success = True
        cancelado = False
        rate = rospy.Rate(6)
        i = 0
        
        while i < ciclos:
            #Aumentamos el contador 
            i +=1 
            
            #Comprobacion de que no hay una cancelacion anticipateda
            
            if self.__act_serv.is_preempt_requested():
                rospy.loginfo("Cancelacion anticipada")
                cancelado = True
                self.__act_serv.get.cancel()
                break
            
            #Enviamos el feedback
            self.__retroalimentacion.contador = i
            self.__act_serv.publish_feedback(self.__retroalimentacion)
            
            rate.sleep()
        
        #Comprobamos que el 
        
        if success:
            print("Enviamos resulatado ")
            self.__resultado.valor_final = i
            self.__resultado.exito = True
            print("resulatado",self.__resultado)
            self.__act_serv.set_succeeded(self.__resultado)
        else:
            #Definimos el estado del servidor como abortado 
            self.__act_serv.set_aborted()

#Creacion del nodo servidor accion 
rospy.init_node('servidor_accion')
rospy.loginfo('Servidor accion iniciado')

#Creamos la clase 
servidor_accion()
rospy.loginfo("Servidor de accion creado")

rospy.spin()