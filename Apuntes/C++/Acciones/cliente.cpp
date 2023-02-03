//tenemos que añadir en el paquete actionlib 
#include <ros/ros.h>
#include <Prueba/MensajeAccionAction.h>
#include <actionlib/client/simple_action_client.h>

#include <iostream>
using namespace std;

//Definicion de variables globales
actionlib::SimpleActionClient<Prueba::MensajeAccionAction> *cliente=NULL;

void doneCB(const actionlib::SimpleClientGoalState& state, const Prueba::MensajeAccionResultConstPtr& result){
    /*Funcion que se ejecuta cuando se termina la accion*/
    ROS_INFO("Terminado y el resultado es: %d", result->resultado.resultado);
}

void feedbackCB(const Prueba::MensajeAccionFeedbackConstPtr& feedback){
    /*Funcion que se ejecuta cuando se envia feedback*/
    ROS_INFO("Progreso: %d", feedback->progreso);

    //Calcelacion de la accion
    if (feedback->progreso == 50){
        ROS_INFO("Cancelando accion");
        cliente->cancelAllGoals();
    }
}

void activeCB(){
    /*Funcion que se ejecuta cuando se activa la accion*/
    ROS_INFO("Accion activa");
}

int main(int argc, char ** argv ){

    //Creamos el nodo principal
    ros::init(argc, argv, "nodo_cliente");
    ros::NodeHandle nh;

    //Creamos el cliente
    cliente =new actionlib::SimpleActionClient<Prueba::MensajeAccionAction> ("Servidor_accion", true);
    
    //Esperamos a que el servidor se inicie
    cliente->waitForServer();
    ROS_INFO("Servidor_accion conectado");

    //Creamos el mensaje
    Prueba::MensajeAccionGoal goal;
    goal.numero = 5;

    // FIXME: (Opcion 1)
    // Enviamos el mensaje
    cliente->sendGoal(goal, doneCB , activeCB, feedbackCB);

    //Esperamos a que el servidor nos devuelva el resultado 
    bool rdo=cliente->waitForResult(ros::Duration(30));
    if(rdo){
        ROS_INFO("El estado del servidor es: %s", cliente->getState().toString().c_str());
        ROS_INFO("El resultado es: %d", cliente->getResult()->resultado);
    }
    else{
        ROS_INFO("El servidor no ha devuelto el resultado");
    }

    //FIXME: (Opcion 2)


    //Esperamos a que el servidor nos devuelva el resultado
    action::SimpleClientGoalState estado = cliente->getState();
    while (estado == actionlib::SimpleClientGoalState::PENDING or estado == actionlib::SimpleClientGoalState::ACTIVE){
        ROS_INFO("El estado del servidor es: %s", estado->toString().c_str());
        estado = cliente->getState();
    }
    ROS_INFO("El resultado es: %d", estado.getResult()->result)



    return 0;
}