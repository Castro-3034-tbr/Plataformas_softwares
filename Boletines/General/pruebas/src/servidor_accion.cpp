#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <pruebas/MensajeAccionAction.h>

#include <iostream>
#include <string>
using namespace std;
/*
actionlib::SimpleActionServer<pruebas::MensajeAccionAction> *servidor=NULL;

void cbaccion(const pruebas::MensajeAccionGoalConstPtr &peticion){
    pruebas::MensajeAccionResult resultado;
    pruebas::MensajeAccionFeedback feedback;

    bool estado = true;
    ros::Rate loop_rate(1);

    for(int i=0; i<10; i++){

        if(servidor->isPreemptRequested()){
            ROS_INFO("El cliente ha cancelado la peticion");
            estado = false;
            break;
        }
        feedback.Feedback = i;
        servidor->publishFeedback(feedback);
        resultado.Resultado = i;
        loop_rate.sleep();
        
    }
    if (estado){
        servidor->setSucceeded(resultado);
    }
    else{
        servidor->setPreempted(resultado);
    }


}

int main (int argc , char ** argv){
    ros::init(argc, argv, "servidor_accion");
    ros::NodeHandle nh;

    servidor = new actionlib::SimpleActionServer<pruebas::MensajeAccionAction>(nh, "servidor_accion", cbaccion ,false);
    servidor->start();
    ros::spin();
}

*/

class Servidor{
    private:
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<pruebas::MensajeAccionAction> servidor_;
        std::string action_name_;
        pruebas::MensajeAccionFeedback feedback_;
        pruebas::MensajeAccionResult resultado_;
    
    void CB(const pruebas::MensajeAccionGoalConstPtr &peticion){
        bool estado = true;
        ros::Rate loop_rate(1);

        for(int i=0; i<10; i++){

            if(servidor_.isPreemptRequested()){
                ROS_INFO("El cliente ha cancelado la peticion");
                estado = false;
                break;
            }
            feedback_.Feedback = i;
            servidor_.publishFeedback(feedback_);
            resultado_.Resultado = i;
            loop_rate.sleep();
            
        }
        if (estado){
            servidor_.setSucceeded(resultado_);
        }
        else{
            servidor_.setPreempted(resultado_);
        }
    }

    public:
        Servidor(std::string name) : servidor_(nh_, name, boost::bind(&Servidor::CB, this, _1), false), action_name_(name){
            servidor_.start();
        }
        ~Servidor(void){
        }

};

int main(int argc, char ** argv){
    ros::init(argc, argv, "servidor_accion");
    Servidor servidor("servidor_accion");
    ros::spin();
}