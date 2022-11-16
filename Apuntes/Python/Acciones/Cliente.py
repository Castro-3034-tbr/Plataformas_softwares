"""
TODO: Creacion de un programa para un cliente de acciones 
"""
#!/usr/bin/env python3
import rospy
import actionlib
from action_server.msg import MensajeAction, MensajeGoal,MensajeResult , MensajeFeedback

def mi_funcion(feedback):
    """
    Funcion que se ejecuta cuando el servidor envia feedback
    """
    print(feedback)

def acabado(result):
    """
    Funcion que se ejecuta cuando el servidor termina de ejecutar la accion
    """
    print("El resultado es: ", result.resultado)
    

#Inciamos el nodo de accion_cliente
rospy.init_node("accion_cliente")

#Creamos el cliente de accion
cliente = actionlib.SimpleActionClient("accion_servidor",MensajeAction)
#Esperamos al servidor de acciones
cliente.wait_for_server()

#Creamos el mensaje goal
goal = MensajeGoal()
goal.ciclos = 10

#Enviamos el mensaje goal
cliente.send_goal(goal,done_cb = acabado, feedback_cb=mi_funcion)

#FIXME: Optativas 

cliente.cancel_goal() #Para hacer cancelaciones anticipadas
status = cliente.get_status() #Para obtener el estado de la accion con el siguiente cogido "0 = pendiente 1 = ejecutandose 2 = finalizado 3= warning 4 = error 5 = cancelado"
cliente.wait_for_result() #Esperamos a que el servidor termine de ejecutar la accion
