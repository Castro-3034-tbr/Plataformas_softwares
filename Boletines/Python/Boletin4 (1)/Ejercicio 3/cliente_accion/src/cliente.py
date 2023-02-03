#!/usr/bin/env python3
import rospy 
import actionlib
from std_srvs.srv import Empty, EmptyRequest
from nodo_cracion.srv import DatosCreacion , DatosCreacionRequest
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from servidor_accion.msg import MensajeAccionAction,MensajeAccionGoal
from movimientos.srv import DatosMovimientoDepredador, DatosMovimientoDepredadorRequest
import math

def callback_posicion_presa(req):
    """Funcion que se ejecuta cuando se recibe la posicion de la presa"""
    
    global posicion_presa, encontrado_presa 
    
    posicion_presa = req
    encontrado_presa = True
    
    

def callback_posicion_depredador(req):
    """Funcion que se ejecuta cuando se recibe la posicion del depredador"""
    
    global posicion_depredador, encontrado_depredador 
    
    posicion_depredador = req
    encontrado_depredador = True

def callback_result(req,requ2):
    """Funcion que se ejecuta cuando se recibe el resultado de la accion"""
    
    global bool_resultado , distancia_resultado
    
    
    bool_resultado = requ2.Estado
    distancia_resultado = requ2.Diferencia

def callback_feedback(req):
    """Funcion que se ejecuta cuando se recibe el feedback de la accion"""
    
    global distancia_feedbacks
    
    distancia_feedbacks = req.Distancia 
    print("Distancia feedback: ", distancia_feedbacks)
    

#Creamos el nodo cliente 
rospy.init_node('cliente')
rospy.loginfo('Nodo cliente iniciado')

#Creacion de variables globales 
umbral = 2

#Esperamos por los servicios 
rospy.wait_for_service('/servicio_creacion')
rospy.loginfo('Servicio de creacion disponible')
rospy.wait_for_service('/servicio_movimiento_presa')
rospy.loginfo('Servicio de movimiento presa disponible')
rospy.wait_for_service('/servicio_movimiento_depredador')
rospy.loginfo('Servicio de movimiento depredador disponible')
rospy.wait_for_service("/servicio_movimiento_depredador")
rospy.loginfo('Servicio de movimiento depredador disponible')

#Esperamos por las acciones
accion_movimineto_presa = actionlib.SimpleActionClient("accion_movimiento_presa", MensajeAccionAction,)
accion_movimineto_presa.wait_for_server()
rospy.loginfo("Accion de movimiento de presa conectado")

#Invocamos el servicio de creacion

creacion_personajes = rospy.ServiceProxy('/servicio_creacion', DatosCreacion)
rospy.loginfo('Servicio de creacion conectado')

peticion_creacion = DatosCreacionRequest()
peticion_creacion.PoseDepredador.x = 9
peticion_creacion.PoseDepredador.y = 10
peticion_creacion.PoseDepredador.theta = 3.14

peticion_creacion.PosePresa.x = 1
peticion_creacion.PosePresa.y = 1
peticion_creacion.PosePresa.theta = 6

creacion = creacion_personajes(peticion_creacion)
rospy.loginfo('Personajes creados')

#FIXME: Movimiento de los personajes

#Subcripcion de la posicion de los personajes
posicion_presa= Pose()
posicion_depredador = Pose()
encontrado_presa = False 
encontrado_depredador = False
rate_sub = rospy.Rate(4)

rospy.Subscriber('/presa/pose', Pose, callback_posicion_presa)
rospy.Subscriber('/depredador/pose', Pose, callback_posicion_depredador)

while encontrado_presa!=True and encontrado_depredador != True:
    rate_sub.sleep()

#Subcripcion de la velocidad de los personajes

velocidad_depredador = Twist()
encontrado_velocidad_depredador = False

velocidad_depredador = rospy.Publisher('/depredador/cmd_vel', Twist, queue_size=10)
rospy.loginfo('Publicador de velocidad de depredador conectado')

#Mandamos el punto objetivo a la presa 
posicion_objetivo = MensajeAccionGoal()
posicion_objetivo.Objetivo.x = 5
posicion_objetivo.Objetivo.y = 5

distancia_feedback = 0
bool_resultado = 0
distancia_resultado = 0

accion_movimineto_presa.send_goal(posicion_objetivo, done_cb=callback_result, feedback_cb=callback_feedback)
rospy.loginfo('Punto objetivo enviado al servidor de accion')

#Creamos el proxi conn el servicio de movimiento del depredador 
movimiento_depredador = rospy.ServiceProxy('/servicio_movimiento_depredador', DatosMovimientoDepredador)
rospy.loginfo("Movimiento depredador conectado")

#Peticion inaical al servicio de movimiento del depredador
peticion_depredador = DatosMovimientoDepredadorRequest()
peticion_depredador.PosePresa = posicion_presa
peticion_depredador.PoseDepredador = posicion_depredador

movimiento_depredador_resultado = movimiento_depredador(peticion_depredador)

#FIXME:Bucle de movimiento
rospy.loginfo("Comienza el bucle de movimiento")
while not rospy.is_shutdown() and movimiento_depredador_resultado.Distancia > umbral and distancia_feedback < 3:
    #Invocamos el servicio de movimiento del depredador
    peticion_depredador = DatosMovimientoDepredadorRequest()
    peticion_depredador.PosePresa = posicion_presa
    peticion_depredador.PoseDepredador = posicion_depredador
    
    movimiento_depredador_resultado = movimiento_depredador(peticion_depredador)
    
    #Publicacion de las velocidades en el topic 
    velocidad_depredador.publish(movimiento_depredador_resultado.VelocidadDepredador)

    
