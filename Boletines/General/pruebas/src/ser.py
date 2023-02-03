#!/usr/bin/env python3
import rospy
import actionlib
from pruebas.msg import MensajeAccionAction, MensajeAccionFeedback, MensajeAccionResult 
from pruebas.msg import mensaje
from std_msgs.msg import Int32

def callback(data):
    """Funcion que se ejecuta cuando se recibe un mensaje por el topic nodoA"""
    global numA, numB
    
    numA = data.A
    numB = data.B
    
    rospy.loginfo("numA: {} numB: {}".format(numA, numB))


class Servidor(object):
    """Clase del servidor"""
    #Objetos privados
    __feedback = MensajeAccionFeedback()
    __result = MensajeAccionResult()
    
    def __init__(self):
        self._act_serv = actionlib.SimpleActionServer("NodoB", MensajeAccionAction, self.callback, False)
        self._act_serv.start()
        rospy.loginfo("Servidor iniciado")
        
    def callback(self, goal):
        """Funcionq que se ejecuta cunado se recibe una peticion de accion"""
        #Obtenemos el numero de iteraciones
        dato = goal.Peticion
        rospy.loginfo("Peticion: {}".format(dato))
        
        #Creamos las variables de control
        rate=rospy.Rate(1)
        cancelado = False
        success = True
        global numA, numB ,pub, msg
        
        for i in range(0, dato+1,1):
            if self._act_serv.is_preempt_requested():
                self._act_serv.set_preempted()
                cancelado = True
                break
            
            if numA > 50:
                success = False
                rospy.loginfo("numA mayor que 50")
                break
            
            self.__feedback.Feedback = i
            self._act_serv.publish_feedback(self.__feedback)
            
            msg.data = numA + numB
            pub.publish(msg)
            rospy.loginfo("Publicado: {}".format(i))
            
            rate.sleep()
        
        if not cancelado:
            if success:
                self.__result.Resultado = numA + numB
                self._act_serv.set_succeeded(self.__result)
                rospy.loginfo("Resultado: {}".format(self.__result.Resultado))
            else:
                self._act_serv.set_aborted()
        
#Definimos el nodo servidor 
rospy.init_node("servidor")
rospy.loginfo("Servidor iniciado")

#Creamos el subcriptor
numA = 0    
numB = 0
rospy.Subscriber("NodoA" , mensaje, callback)
rospy.loginfo("Subscriptor creado")

#Creacion del publisher
msg = Int32()
pub = rospy.Publisher("Pub", Int32, queue_size=10)

#Creamos el servidor
server = Servidor()

rospy.spin()