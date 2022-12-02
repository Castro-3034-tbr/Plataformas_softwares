#include <ros/ros.h>
#include <ejercicio5/MensajeServicio.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

#include <iostream>
using namespace std;

class Servidor{
    /*Creacion de la clase del servidor de anccion*/
    private:
        ros::NodeHandle nh;
        ros::ServiceServer server;
        ros::Subscriber suscriptor_posicion;
        ros::Publisher publicador_velocidad;
        int posicion_x = 0;
        int posicion_y = 0;
    
    public:
        //Constructor 
        Servidor(){
            server = nh.advertiseService("servicio", &Servidor::callback, this);
            suscriptor_posicion = nh.subscribe("odom", 1000, &Servidor::posicionCallback, this);
            publicador_velocidad = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        }
        void posicionCallback(const nav_msgs::Odometry::ConstPtr& msg){
            posicion_x = msg->pose.pose.position.x;
            posicion_y = msg->pose.pose.position.y;
        }

        void movimiento_recto(int pasos, int direccion)
        {
            /*Funcion que se ejecuta para mover el robot x pasos para delante*/

            ROS_INFO("Moviendo el robot %d pasos con direccion %d", pasos, direccion);

            // Creacion del mensaje
            geometry_msgs::Twist msg;
            msg.linear.x = 50 * direccion;

            ros::Rate rate(5);
            for (int i = 0; i <= pasos; i++)
            {
                publicador_velocidad.publish(msg);
                rate.sleep();
            }
        }

        void girar_noventa(int direccion)
        {
            /*Funcion que se ejecuta para mover el robot 90 grados*/

            ROS_INFO("Girando el robot 90 grados con direccion %d", direccion);
            // Creacion del mensaje
            geometry_msgs::Twist msg;
            msg.angular.z = 1.6 * direccion;

            ros::Rate loop_rate(1);
            for (int i = 0; i < 5; i++)
            {
                publicador_velocidad.publish(msg);
                loop_rate.sleep(); // loop_rate de 1hz
            }
        }

        bool callback(ejercicio5::MensajeServicioRequest &req, ejercicio5::MensajeServicioResponse &res){
            /*Funcion que se ejecuta cuando se pide una peticion al servidor */

            //Definicion de datos llegados
            int posX = req.X ;
            int posY = req.Y;

            // Calculo de la distancia
            float distanciaX = posX - posicion_x;
            float distanciaY = posY - posicion_y;

            // Calculo de pasos
            int pasosX = distanciaX / 0.5 + 1;
            int pasosY = distanciaY / 0.5 + 1;

            ROS_INFO("Pasos en X: %d , Pasos en Y: %d", pasosX, pasosY);
            int direccionX = 1;
            if (pasosX < 0)
            {
                direccionX = -1;
                pasosX *= -1;
            }

            int direccionY = 1;
            if (pasosY < 0)
            {
                direccionY = -1;
                pasosY *= -1;
            }

            ROS_INFO("Direccion en X: %d , Direccion en Y: %d", direccionX, direccionY);

            //Bucle de movimiento
            Servidor::movimiento_recto(pasosX, direccionX);
            Servidor::girar_noventa(direccionY);
            Servidor::movimiento_recto(pasosY, direccionY);

            //Respuesta del servicio
            res.succes = true;

            return true;
        }
};   


int main (int argc, char ** argv){
    //Creacion del nodo principal
    ros::init(argc, argv, "servidor_clase");
    ros::NodeHandle nh;

    //Creamos el objeto del servidor
    Servidor servidor;

    ros::spin();
    return 0;
}
