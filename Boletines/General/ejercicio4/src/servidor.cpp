#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ejercicio4/MensajeAccionAction.h>
#include <std_msgs/Int32.h>

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
class Servidor{
    /*Clase del servidor de accion*/
    private:
        ros::NodeHandle nh;
        actionlib::SimpleActionServer<ejercicio4::MensajeAccionAction> server;
        string action_name;
        ejercicio4::MensajeAccionFeedback feedback;
        ejercicio4::MensajeAccionResult result;
        ros::Subscriber sub = nh.subscribe("topic_ramdom_server", 1000, &Servidor::CBNum, this);

        void executeCB(const ejercicio4::MensajeAccionGoalConstPtr &goal)
        {
            int interations = goal->Interations;
            int seed = goal->Seed;
            bool estado = true;
            int AletorioNum = 0;
            ros::Rate loop_rate(1);
            srand(seed);

            for (int i = 0; i < interations; i++){
                // Comprobamos si se ha cancelado
                if (server.isPreemptRequested()){
                    estado = false;
                    ROS_INFO("Cancelado");
                    break;
                }
                // Generamos un numero aleatorio

                AletorioNum = rand() % 10;

                // Enviamos el feedback
                feedback.PartialResult = AletorioNum;
                server.publishFeedback(feedback);
                loop_rate.sleep();
                
            }
            // Enviamos el resultado
            result.LastNumber = AletorioNum;
            if (estado == true)
            {
                server.setSucceeded(result);
            }
            else
            {
                server.setPreempted(result);
            }
        }

        void CBNum(const std_msgs::Int32::ConstPtr& msg){
            ROS_INFO("Lectura del numero: %d", msg->data);
        }
    public:
        Servidor(string name): server(nh,name, boost::bind(&Servidor::executeCB, this, _1), false), action_name(name){
            server.start();
        }
};

int main(int argc, char ** argv){

    //Creamos el nodo principal
    ros::init(argc, argv, "servidor");
    ros::NodeHandle nh;

    //Creamos el servidor
    Servidor Servidor("Servidor_ej4");

    ros::spin();
    return 0;

}