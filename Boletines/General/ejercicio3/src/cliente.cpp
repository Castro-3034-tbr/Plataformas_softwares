#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <ejercicio3/MensajeAccionAction.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

actionlib::SimpleActionClient<ejercicio3::MensajeAccionAction> *client=NULL

#include <iostream>
using namespace std;

void doneCB(const actionlib::SimpleClientGoalState &state, const Prueba::MensajeAccionResultConstPtr &result){
    /*Funcion que se ejecuta cuando se termina la accion*/ 
    ROS_INFO("Terminado y el resultado es: %d", result->resultado.resultado);
}

void feedbackCB(const Prueba::MensajeAccionFeedbackConstPtr &feedback){
    /*Funcion que se ejecuta cuando se envia feedback*/ 
    ROS_INFO("Feedback: %d", feedback->resultado.resultado);
    if (feedback->resultado.resultado <= 1){
        ROS_INFO("Se ha detectado un obstaculo");
        // Cancelar la accion
        cliente->cancelGoal();
    }
}

void activeCB(){
        /*Funcion que se ejecuta cuando se activa la accion*/ 
    ROS_INFO("Accion activa");
}


int main(int argc, char **argv)
{
    // Creacion del nodo principal
    ros::init(argc, argv, "cliente");
    ros::NodeHandle nh;

    // Creacion del cliente
    cliente = new actionlib::SimpleActionClient<ejercicio3::MensajeAccionAction>("servidor", true);
    cliente->waitForServer();
    ROS_INFO("Cliente iniciado");

    // Creacion del mensaje
    ejercicio3::MensajeAccionGoal goal;
    goal.Velocidad = 1;
    goal.Tiempo = 5;

    // Envio del mensaje
    cliente->sendGoal(goal, &doneCB, &activeCB, &feedbackCB);
    ROS_INFO("Mensaje enviado");
    bool rdo=client->waitForResult(ros::Duration(30));
    if(rdo){
        ROS_INFO("Terminado");
    }
    else{
        ROS_INFO("No terminado");
    }
}
