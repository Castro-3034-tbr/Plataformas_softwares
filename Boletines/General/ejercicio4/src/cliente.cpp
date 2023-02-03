#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <ejercicio4/MensajeAccionAction.h>
#include <std_msgs/Int32.h>
#include <iostream>
#include <string>
using namespace std;

//Definicion de variables globales
actionlib::SimpleActionClient<ejercicio4::MensajeAccionAction> *client=NULL;
ros::Publisher pub;

int SumaMax = 0;
int PartialSum = 0;

//Funciones del servidor
void doneCb(const actionlib::SimpleClientGoalState& state, const ejercicio4::MensajeAccionResultConstPtr& result){
    ROS_INFO("Terminado");
    ROS_INFO("El ultimo elemento es: %d", result->LastNumber);
    
    std_msgs::Int32 msg;
    msg.data = result->LastNumber;
    pub.publish(msg);
}

void activeCb(){
    ROS_INFO("Mensaje enviado");
}

void feedbackCb(const ejercicio4::MensajeAccionFeedbackConstPtr& feedback){

    std_msgs::Int32 msg;
    msg.data = feedback->PartialResult;
    pub.publish(msg);


    ROS_INFO("El numero parcial es: %d", feedback->PartialResult);
    PartialSum += feedback->PartialResult;
    ROS_INFO("La suma parcial es: %d", PartialSum);
    if(PartialSum > SumaMax){
        ROS_INFO("La suma parcial es mayor que la suma maxima");
        client->cancelAllGoals();
    }
}

int main(int argc , char ** argv){
    //Creamos el nodo principal
    ros::init(argc, argv, "cliente");
    ros::NodeHandle nh;

    //Creamos el cliente
    client = new actionlib::SimpleActionClient<ejercicio4::MensajeAccionAction>("Servidor_ej4", true);
    ROS_INFO("Cliente creado");
    client->waitForServer();
    ROS_INFO("Servidor conectado");

    //Creamos el publicador
    pub = nh.advertise<std_msgs::Int32>("topic_ramdom_server", 1000);

    //Creamos el mensaje
    ejercicio4::MensajeAccionGoal goal;
    cout << "Introduce la semilla: ";
    cin >> goal.Seed;
    cout << "Introduce las interacciones: ";
    cin >> goal.Interations;

    cout << "Introduce la suma maxima: ";
    cin >> SumaMax;

    //Enviamos el mensaje
    client->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

    actionlib::SimpleClientGoalState state = client->getState();
    while (state == actionlib::SimpleClientGoalState::ACTIVE or state == actionlib::SimpleClientGoalState::PENDING){
        state = client->getState();
        ROS_INFO("Estado: %s", state.toString().c_str());
        ros::Duration(1).sleep();
    }

}