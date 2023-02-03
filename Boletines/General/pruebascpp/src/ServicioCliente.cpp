#include <ros/ros.h>
#include <pruebascpp/MensajeServicio.h>

#include <iostream>
using namespace std;

int main(int argc, char **argv){

    //Creacion del nodo principal
    ros::init(argc, argv, "nodo_cliente");
    ros::NodeHandle nh;

    //Creacion del cliente 
    ros::ServiceClient cliente= nh.serviceClient<pruebascpp::MensajeServicio>("Servicio");
    ROS_INFO("Cliente creado");

    //Esperamos por el servicio 
    cliente.waitForExistence();
    ROS_INFO("Servicio encontrado");

    //Creamos el mensaje
    pruebascpp::MensajeServicio msg;
    msg.request.Peticion = 5;

    //Llamamos al servicio
    if(cliente.call(msg)){
        ROS_INFO("Respuesta: %d", msg.response.Resultado);
        return 0;
    }
    else{
        ROS_ERROR("Fallo al llamar al servicio");
        return 1;
    }
}