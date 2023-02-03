#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <pruebascpp/MensajeAccionAction.h>

#include <iostream>
using namespace std;

//Definciion de vataibles globable
actionlib::SimpleActionClient<pruebascpp::MensajeAccionAction> *cliente;

void doneCB(const actionlib::SimpleClientGoalState& state, const pruebascpp::MensajeAccionResultConstPtr& result){
    ROS_INFO("El servidor ha terminado con el estado: %s", state.toString().c_str());
    ROS_INFO("El resultado es: %d", result->resultado);
}

void activeCB(){
    ROS_INFO("El servidor ha activado la accion");
}

void feedbackCB(const pruebascpp::MensajeAccionFeedbackConstPtr& feedback){
    ROS_INFO("El servidor ha enviado el feedback: %d", feedback->feedback);
}

int main(int argc, char ** argv){
    //Creacion del nodo cliente
    ros::init(argc, argv, "cliente_accion");
    ros::NodeHandle nh;

    //Creacion del cliente
    cliente = new actionlib::SimpleActionClient<pruebascpp::MensajeAccionAction>("Servidor",true);
    ROS_INFO("El cliente ha creado el cliente");
    //esperamos por el servidor
    cliente->waitForServer();
    ROS_INFO("El cliente ha encontrado el servidor");

    //Creamos el mensaje
    pruebascpp::MensajeAccionGoal Peticion;
    Peticion.peticion = 10;
    ROS_INFO("El cliente ha creado la petición");

    //Enviamos el mensaje
    cliente->sendGoal(Peticion, doneCB ,activeCB ,feedbackCB);
    ROS_INFO("El cliente ha enviado la petición");

    //Esperamos a que termine
    bool rdo=cliente->waitForResult(ros::Duration(30));
    if(rdo){
        ROS_INFO("El estado del servidor es: %s", cliente->getState().toString().c_str());
    }
    else{
        ROS_INFO("El servidor no ha terminado en 30 segundos");
    }
}