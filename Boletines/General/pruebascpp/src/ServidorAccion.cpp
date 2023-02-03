#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <pruebascpp/MensajeAccionAction.h>

#include <iostream>
#include <string>
using namespace std;

class Servidor{
    private:
        ros::NodeHandle nh;
        actionlib::SimpleActionServer<pruebascpp::MensajeAccionAction> server;
        string action_name;
        pruebascpp::MensajeAccionFeedback Feedback;
        pruebascpp::MensajeAccionResult Result;

    void cbServidor(const pruebascpp::MensajeAccionGoalConstPtr &goal){
        /*Funcion que se ejecuta cuando se pode una accion al servidor*/
        ROS_INFO("El servidor ha recibido la peticion: %d", goal->peticion);
        int limite = goal->peticion;
        ros::Rate rate(1);
        bool estado = true;
        int resultado=0;

        for (int i= 0; i <= limite; i++){
            if (server .isPreemptRequested()){
                ROS_INFO("El cliente ha cancelado la accion");
                estado = false;
                break;
            }
            Feedback.feedback = i;
            resultado = i;
            server.publishFeedback(Feedback);
            rate.sleep();
        }

        if (estado){
            Result.resultado = resultado;
            server.setSucceeded(Result);
            ROS_INFO("El servidor ha terminado con exito");
        }
        else {
            server.setPreempted(Result);
        }
    }

    public:
        Servidor(string name): server(nh , name , boost::bind(&Servidor::cbServidor, this , _1) , false), action_name(name){
            //Iniciamos el servidor
            server.start();
            ROS_INFO("El servidor ha iniciado");
        }
};

int main(int argc, char ** argv){
    //Creacion del nodo servidor
    ros::init(argc, argv, "servidor_accion");
    ROS_INFO("El servidor ha creado el nodo");
    Servidor servidor("Servidor");
    ROS_INFO("El servidor ha creado el servidor");
    ros::spin();
}