#!/usr/bin/env python3
import rospy
import actionlib
from bol4.msg import Mensaje1Action, Mensaje1Feedback, Mensaje1Result
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

def callback(data):
    """Funcion que se ejecuta cuando se recibe un mensaje por el topic base_scan_0"""
    global izquierda, centro , derecha
    datos = data.ranges
    encontrado = True
    #print(datos)
    
    izquierda = datos[0]
    centro = datos[len(datos)//2]
    derecha = datos[len(datos)-1]
    
    #rospy.loginfo("Izquierda: {} Centro: {} Derecha: {}".format(izquierda, centro, derecha))
    

class Servidor(object):
    """Creacion de la clase del servidor"""
    __retroalimentacion = Mensaje1Feedback()
    __resultado = Mensaje1Result()
    
    def __init__(self):
        self.__act_serv= actionlib.SimpleActionServer("servidor_clase", Mensaje1Action, self.servidorCB, False)
        self.__act_serv.start()
        rospy.loginfo("Servidor iniciado")
    
    def servidorCB(self,datos):
        """Funcionq ue se ejecuta cuando se pide una accion al servidor
        RETURN:Mensaje1Result"""

        #Leemos el dato del tiempo por terminal 
        tiempo = int(input("Introduce el tiempo de espera: "))
        
        #Creamos las variables locales 
        rate = rospy.Rate(1)
        success = True
        cancelado = False
        
        global izquierda, centro, derecha
        
        #Creamos el bucle
        for i in range(1,tiempo+1):
            #Comprobamos si se ha cancelado la accion 
            if self.__act_serv.is_preempt_requested():
                rospy.loginfo("La accion ha sido cancelada")
                self.__act_serv.set_preempted()
                cancelado = True
                break 
            
            if centro <0.5:
                rospy.loginfo("El robot esta demasiado cerca de un obstaculo")
                success = False
                break
            
            #Creo el mensaje para mover el robot
            msg = Twist()
            msg.linear.x = 0.2
            pub.publish(msg)
            rospy.loginfo("Moviendo el robot")
            
            #Definimos el mensaje de retroalimentacion
            self.__retroalimentacion.izquierda = izquierda
            self.__retroalimentacion.centro = centro
            self.__retroalimentacion.derecha = derecha
            self.__act_serv.publish_feedback(self.__retroalimentacion)
            rate.sleep()
        
        if not cancelado:
            if success:
                rospy.loginfo("La accion ha finalizado con exito")
                self.__resultado.result= "Acierto"
                self.__act_serv.set_succeeded(self.__resultado)
            else:
                rospy.loginfo("La accion ha finalizado sin exito")
                self.__resultado.result= "Fallo"
                self.__act_serv.set_aborted(self.__resultado)


#Creamos el nodo principal 
rospy.init_node("servidor_clase")
rospy.loginfo("Nodo creado")

#Creamos el objeto de servidor 
Servidor()
rospy.loginfo("Servidor creado")

#Creacion de varibles globales
izquierda = 0
centro = 0
derecha = 0
rospy.loginfo("Variables globales creadas")

#Creamos el subcriptor de base_scan_0
rospy.Subscriber("base_scan_1", LaserScan, callback)
rospy.loginfo("Subscriptor creado")

sub_rate = rospy.Rate(10)
encontrado = False
while encontrado == False:
    sub_rate.sleep()

#Creamos el publicador de cmd_vel
pub = rospy.Publisher("cmd_vel", Twist, queue_size=1)
rospy.loginfo("Publicador creado")
#Bucle 
