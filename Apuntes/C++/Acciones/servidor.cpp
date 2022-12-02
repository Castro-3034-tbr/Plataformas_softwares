#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <Prueba/MensajeAccionAction.h>

#include <iostream>
using namespace std;

//Definicion de variables globales
actionlib::SimpleActionServer<Prueba::MensajeAccionAction> *servidor=NULL;

void cbaccion(const Prueba::MensajeAccionGoalConstPtr &goal){
    /*Funcion que se ejecuta cuando se pide una accion al servidor */

    //Creamos los mensajes 
    Prueba::MensajeAccionFeedback feedback;
    Prueba::MensajeAccionResult result;

    bool estado = true;

    //FIXME: Accion (Ejemplo)
    for(int i=0; i<goal->numero; i++){
        //Comprobamos si se ha cancelado la accion
        if (servidor->isPreemptRequested()){
            ROS_INFO("El cliente ha cancelado la accion");
            estado = false
            break;
        }

        //Enviamos el feedback
        feedback.progreso = 0;
        servidor->publishFeedback(feedback);
    }

    //Enviamos el resultado
    result.resultado = 0;
        //Comprobamos que no se ha cancelado la accion
    if (estado == true){
        servidor->setSucceeded(result);
    }
    else{
        servidor->setPreempted(result);
    }

}


int main(int argc, char ** argv ){

    //Creamos el nodo principal
    ros::init(argc, argv, "nodo_servidor");
    ros::NodeHandle nh;

    //Creamos el servidor
    servidor =new actionlib::SimpleActionServer<Prueba::MensajeAccionAction> (nh, "Servidor_accion",cbaccion ,false);
    servidor.start();
    ROS_INFO("Servidor_accion iniciado");

    ros::spin();

    return 0;
}