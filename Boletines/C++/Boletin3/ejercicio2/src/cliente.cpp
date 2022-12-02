#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib_tutorials/FibonacciAction.h>

#include <iostream>
using namespace std;

//Definicion de varaibles globales
actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction> *cliente=NULL;
int goal = 10;

void doneCB(const actionlib::SimpleClientGoalState& state,const actionlib_tutorials::FibonacciResultConstPtr& result){
    /*Funcion que se ejecuta cuando hay un resultado*/
    
    ROS_INFO("Secuencia de fibonacci: ");
    for(int i=0;i<result->sequence.size();i++){
        cout<<result->sequence[i]<<" ";
    }
    cout<<endl;
}

void activeCB(){
    /*Funcion que se ejecuta cuando el cliente se activa*/
    ROS_INFO("Cliente activo");
}

void feedbackCB(const actionlib_tutorials::FibonacciFeedbackConstPtr& feedback){
    /*Funcion que se ejecuta cuando hay un feedback*/
    if (feedback->sequence[feedback->sequence.size()-1]>goal){
        cliente->cancelGoal();
    }

}

int main(int argc, char ** argv){

    //Creamos el nodo principal 
    ros::init(argc, argv, "test_fibonacci");
    ros::NodeHandle nh;

    //Creamos el cliente
    cliente = new actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction>("fibonacci", true);
    ROS_INFO("Cliente creado");

    //Esperamos por el servidor de accion 
    cliente->waitForServer();
    ROS_INFO("Servidor de accion encontrado");

    //Creamos el mensaje 
    actionlib_tutorials::FibonacciGoal goal;
    goal.order = 10;

    //Enviamos el mensaje
    cliente->sendGoal(goal, doneCB, activeCB, feedbackCB);
    ROS_INFO("Mensaje enviado");
    bool rdo = cliente->waitForResult(ros::Duration(30.0));
    if (rdo){
        ROS_INFO("El estado del resultado es: %s", cliente->getState().toString().c_str());
    }
    else{
        ROS_INFO("El estado del resultado es: %s", cliente->getState().toString().c_str());
    }

    return 0;
}