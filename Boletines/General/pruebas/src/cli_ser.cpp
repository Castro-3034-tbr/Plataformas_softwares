#include <ros/ros.h>
#include <pruebas/MensajeServicio.h>
#include <std_msgs/Int32.h>

#include <iostream>
using namespace std;

int main(int argc, char ** argv){
    //Creacion del nodo cliente_servicio 
    ros::init(argc, argv, "cliente_servicio");
    ros::NodeHandle nh;
    ROS_INFO("Nodo Cliente creado");

    //Creacion del cliente
    ros::ServiceClient cliente= nh.serviceClient<pruebas::MensajeServicio>("Servicio");
    ROS_INFO("Cliente creado");

    //Esperamos a que el servidor este activo
    cliente.waitForExistence();
    ROS_INFO("Servidor activo");

    // Creacion de un publicador
    ros::Publisher pub = nh.advertise<std_msgs::Int32>("Repuesta", 1000);

    //Creacion del mensaje
    pruebas::MensajeServicio msg;
    msg.request.Peticion = 14;

    std_msgs::Int32 msg2;
    int respuesta;

    //Enviamos el mensaje
    if (cliente.call(msg)){
        respuesta= msg.response.Resultado;
        ROS_INFO("El resultado es: %d", msg.response.Resultado);
    }
    else{
        ROS_INFO("El resultado no ha llegado");
    }

    msg2.data = respuesta;
    pub.publish(msg2);
    ROS_INFO("El mensaje ha llegado");

}