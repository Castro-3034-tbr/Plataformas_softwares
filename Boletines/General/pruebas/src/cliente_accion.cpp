#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <pruebas/MensajeAccionAction.h>

#include <iostream>
#include <string>
using namespace std;

//Definicion de variables globales
actionlib::SimpleActionClient<pruebas::MensajeAccionAction> *cliente=NULL;

//Funcion de callback cuando se recibe un feedback
void feedbackCB(const pruebas::MensajeAccionFeedbackConstPtr &feedback){
    cout << "Feedback recibido: " << feedback->Feedback << endl;
    if (feedback->Feedback == 20){
        cliente->cancelAllGoals();
    }
}

void activeCB(){
    cout << "El servidor ha recibido la peticion" << endl;
}

void doneCB(const actionlib::SimpleClientGoalState &estado, const pruebas::MensajeAccionResultConstPtr &resultado){
    cout << "El servidor ha terminado la peticion y el resultado es" << resultado->Resultado << endl;
}

int main(int agrc, char ** argv ){
    ros::init(agrc, argv, "cliente_accion");
    ros::NodeHandle nh;

    //Creamos el cliente
    cliente = new actionlib::SimpleActionClient<pruebas::MensajeAccionAction>("servidor_accion", true);
    //Esperamos a que el servidor este activo
    cliente->waitForServer();

    //Creamos el mensaje
    pruebas::MensajeAccionGoal peticion;
    peticion.Peticion = 1;

    cliente->sendGoal(peticion, doneCB , activeCB, feedbackCB);
    
    bool rdo=cliente->waitForResult(ros::Duration(30));
    if (rdo){
        ROS_INFO("El estado del servidor es: %s" , cliente->getState().toString().c_str());
    }
}