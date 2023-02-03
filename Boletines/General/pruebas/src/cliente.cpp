#include <ros/ros.h>
#include <pruebas/MensajeAccionAction.h>
#include <actionlib/client/simple_action_client.h>

#include <iostream>
using namespace std;

void doneCb(const actionlib::SimpleClientGoalState& state, const pruebas::MensajeAccionResultConstPtr& result){
    ROS_INFO("Terminado");
    ROS_INFO("Resultado: %d", result->Resultado);
}

void activeCb(){
    ROS_INFO("Activo");
}

void feedbackCb(const pruebas::MensajeAccionFeedbackConstPtr& feedback){
    ROS_INFO("Feedback: %d", feedback->Feedback);
}

//Creacion del cliente
actionlib::SimpleActionClient<pruebas::MensajeAccionAction> *cliente=NULL;

int main(int argc, char ** argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "cliente");
    ros::NodeHandle nh;
    ROS_INFO("Cliente creado");

    //Creacion del cliente 
    cliente = new actionlib::SimpleActionClient<pruebas::MensajeAccionAction>("NodoB", true);
    ROS_INFO("Cliente creado");
    //esperamos a que el servidor este activo
    cliente->waitForServer();
    ROS_INFO("Servidor activo");

    //Creacion del mensaje
    pruebas::MensajeAccionGoal msg;
    msg.Peticion = 14;

    //enviamos el mensaje
    cliente->sendGoal(msg, doneCb, activeCb, feedbackCb);
    ROS_INFO("Mensaje enviado");
    bool rdo= cliente->waitForResult(ros::Duration(50));
    if(rdo){
        ROS_INFO("El resultado es: %d", cliente->getResult()->Resultado);
    }
    else{
        ROS_INFO("El resultado no ha llegado");
    }


}