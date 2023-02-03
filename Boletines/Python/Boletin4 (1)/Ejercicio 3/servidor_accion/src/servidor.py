#!/usr/bin/env python3
import rospy
import actionlib
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from servidor_acciones.msg import MovimientoAccionAction, MovimientoResultado, MovimientoFeedback
from std_srvs.srv import Empty, EmptyRequest

class servidor_accion(object):
    """Clase de la accion de movimiento del la presa"""
    
    #Definicion de las variables secretas 
    __resultado = MensajeAccionResultado()
    __feedback = MovimientoFeedback()
    
    def __init__(self):
        #Creamos el servidor 
        self.__act_srv = actionlib.SimpleActionServer('servicio_movimiento_presa', MovimientoAccionAction, self.ejecutar_accion, False)
    
    def ejecutar_accion(self, goal):
        """Funcion que se ejecuta cuando se recibe una peticion de la accion"""
        
        global velocidad_presa, posicion_presa
        
        #Esperamos por el servicio de control de presa 
        rospy.wait_for_service('/servicio_movimiento_presa')
        rospy.loginfo('Servicio de movimiento presa disponible')
        
        #Conexion a al servicio 
        self.control_presa = rospy.ServiceProxy('/servicio_movimiento_presa', DatoMovimiento) 
        
        while distancia > 2 :
            self.control_presa() 
        

#Creacion del nodo servidor 
rospy.init_node('servidor')
rospy.loginfo('Nodo servidor iniciado')



#Subcripcion de los topics 
posicion_presa= Pose()
encontrado_presa = False 
rate_sub = rospy.Rate(10)
rospy.Subcriber('/presa/pose', Pose, callback_posicion_presa)

while encontrado_presa == False:
    rate_sub.sleep()

velocidad_presa = rospy.Publisher('/presa/cmd_vel', Twist, queue_size=10)

