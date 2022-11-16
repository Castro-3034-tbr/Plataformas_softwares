#!/usr/bin/env python3
import rospy
import actionlib
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from std_srvs.srv import Empty, EmptyRequest
from movimientos.srv import DatosMovimientosPresa , DatosMovimientosPresaRequest
from servidor_accion.msg import MensajeAccionAction, MensajeAccionResult, MensajeAccionFeedback


def callback_posicion_presa(req):
    """Funcion que se ejecuta cuando se recibe la posicion de la presa"""
    
    global posicion_presa, encontrado_presa 
    
    posicion_presa = req
    encontrado_presa = True
    

class servidor_accion(object):
    """Clase de la accion de movimiento del la presa"""
    
    #Definicion de las variables secretas 
    __resultado = MensajeAccionResult()
    __feedback = MensajeAccionFeedback()
    
    def __init__(self):
        #Creamos el servidor 
        self.__act_srv = actionlib.SimpleActionServer('accion_movimiento_presa', MensajeAccionAction, self.ejecutar_accion, False)
        self.__act_srv.start()
        rospy.loginfo("Servidor de accion iniciado")
    
    def ejecutar_accion(self, goal):
        """Funcion que se ejecuta cuando se recibe una peticion de la accion"""
        
        global velocidad_presa, posicion_presa
        rospy.loginfo("Ejecutando accion del movimiento de la presa")
        #Esperamos por el servicio de control de presa 
        rospy.wait_for_service('/servicio_movimiento_presa')
        rospy.loginfo('Servicio de movimiento presa disponible')
        
        #Conexion a al servicio 
        self.control_presa = rospy.ServiceProxy('/servicio_movimiento_presa', DatosMovimientosPresa) 
        rospy.loginfo('Servicio de movimiento presa conectado')
        
        #Envio inicial al servicio de control de presa
        peticion_presa = DatosMovimientosPresaRequest()
        peticion_presa.Objetivo = goal.Objetivo
        peticion_presa.PosePresa = posicion_presa
        
        resultado = self.control_presa(peticion_presa)
        
        while resultado.Distancia > 2 :
            #Peticion de los datos a al servicio de control de presa
            peticion_presa = DatosMovimientosPresaRequest()
            peticion_presa.Objetivo = goal.Objetivo
            peticion_presa.PosePresa = posicion_presa
            
            resultado = self.control_presa(peticion_presa)
            
            #Publicacion de los datos de feedback
            self.__feedback.Distancia = resultado.Distancia
            self.__act_srv.publish_feedback(self.__feedback)
            
            #Publicacion de la velocidad de la presa en el topic
            velocidad_presa.publish(resultado.VelocidadPresa)
            
            #Comprobacion de si se ha cancelado la accion
            if self.__act_srv.is_preempt_requested():
                cancelado = True
                self.__act_srv.set_preempt()
                break
        
        succes = True
        
        
        if succes:
            self.__resultado.Estado = True
            self.__resultado.Diferencia = resultado.Distancia
            self.__act_srv.set_succeeded(self.__resultado)
        else :
            self.__act_srv.set_aborted()
        

#Creacion del nodo servidor 
rospy.init_node('servidor')
rospy.loginfo('Nodo servidor iniciado')



#Subcripcion de los topics 
posicion_presa= Pose()
encontrado_presa = False 
rate_sub = rospy.Rate(10)

rospy.Subscriber('/presa/pose', Pose, callback_posicion_presa)
while encontrado_presa == False:
    rate_sub.sleep()

velocidad_presa = rospy.Publisher('/presa/cmd_vel', Twist, queue_size=10)

#Creamos la clase del servidor de accion
servidor_accion()
rospy.loginfo("Servidor de accion creado")

rospy.spin()