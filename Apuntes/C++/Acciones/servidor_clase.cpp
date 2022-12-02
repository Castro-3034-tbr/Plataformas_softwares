#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <Prueba/MensajeAccionAction.h>


#include <string>
#include <iostream>
using namespace std;


class Servidor{
    private:
        //Definicion de las varaibles privadas 
        ros::NodeHandle nh;
        actionlib::SimpleActionServer<Prueba::MensajeAccionAction> server;
        Prueba::MensajeAccionFeedback feedback;
        Prueba::MensajeAccionResult result;
        string accion_name;

    public:
        //Declaramos el contructor 
        Servidor(string name): server(nh, name, boost::bind(&Servidor::cbServidor, this , _1) ,false ),accion_name = name{
            //Inicializamos el servidor
            servidor.start();
        }
    
        void cbServidor(const Prueba::MensajeAccionGoalConstPtr &goal){
            /*Funcion que se ejecuta cuando se pide una accion al servidor */

            // FIXME: Accion (Ejemplo)
            for (int i = 0; i < goal->numero; i++)
            {
                // Comprobamos si se ha cancelado la accion
                if (server.isPreemptRequested()){
                    ROS_INFO("El cliente ha cancelado la accion");
                    estado = false;
                    break;
                }

                // Enviamos el feedback
                feedback.progreso = 0;
                server.publishFeedback(feedback);
            }

            //Enviamos el resultado 
            result.resultado = 0;
            if (estado == true){
                server.setSucceeded(result);
            }
            else{
                server.setPreempted(reuslt);
            }
    }
}

int main(int argc, char ** argv){

    //Creamos el nodo principal 
    ros::init(argc, argv, "Servidor_clase");

    //Creamos el objeto servidor
    Servidor servidor("Servidor_accion");

    ros::spin();

    return 0;
}