#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ejercicio3/MensajeAccionAction.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

#include <iostream>
using namespace std;

class Servidor{
    private:
        ros::NodeHandle nh;
        actionlib::SimpleActionServer<ejercicio3::MensajeAccionAction> server;

        ros::Publisher velocidad=nh.advertise<geometry_msgs::Twist>("/cmd_vel",1000);
        ros::Subscriber base =nh.subscribe("/base_scan0",1000,&Servidor::CBLaser,this);
        int distancia=0;

        ejercicio3::MensajeAccionFeedback feedback;
        ejercicio3::MensajeAccionResult result;
    
    public:
    Servidor(string name): server(nh,name,boost::bind(&Servidor::CBServidor,this,_1),false){
        server.start();
        ROS_INFO("Servidor iniciado");
    }

    void CBLaser(const sensor_msgs::LaserScan::ConstPtr& msg){
        ROS_INFO("Lectura del laser");
        //Calcula de la distancia minima 
        distancia = msg->ranges[0];
    }

    void CBServidor(const ejercicio3::MensajeAccionGoalConstPtr &goal){
        ROS_INFO("Accion ejecutada");
        //Lectura de la velocidad 
        int vel = goal->Velocidad;
        ROS_INFO("Velocidad: %d",vel);
        int tiempo = goal->Tiempo;

        //Creaciond el mensaje 
        geometry_msgs::Twist msg;
        msg.linear.x=vel;
        msg.angular.z=0;

        //Bucle de ejecucion 
        ros::Rate rate(1);
        int contador=0;
        bool estado = true;
        for(int i=0;i<tiempo+1;i++){
            //Comprobacion de si la accion ha sido cancelada 
            if (server.isPreemptRequested()){
                ROS_INFO("Accion cancelada");
                estado = false;
                break;
            }
            
            //Publicacion del mensaje
            velocidad.publish(msg);
            ROS_INFO("Publicacion del mensaje");
            contador = i;

            //Publicacion del feedback
            feedback.Distancia = distancia;
            server.publishFeedback(feedback);
            ROS_INFO("Publicacion del feedback");

            rate.sleep();

        }

        //Enviamos el resultado 
        result.TiempoEfectivo = contador;
        if (estado==true){
            ROS_INFO("Accion completada");
            server.setSucceeded(result);
        }
        else{
            server.setPreempted(result);
        }
    }

};

int main(int argc, char ** argv){

    //Creamos el nodo principal
    ros::init(argc, argv, "servidor");
    ROS_INFO("Nodo Servidor creado");

    //Creamos el servidor
    Servidor servidor("Servidor");

    ros::spin();
}