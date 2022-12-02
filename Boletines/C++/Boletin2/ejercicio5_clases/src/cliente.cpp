#include <ros/ros.h>
#include <ejercicio5/MensajeServicio.h>

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    //Creacion del nodo principal
    ros::init(argc, argv, "cliente");
    ros::NodeHandle nh;

    //Creacion del cliente
    ros::ServiceClient cliente = nh.serviceClient<ejercicio5::MensajeServicio>("ServicioMovimiento");
    ROS_INFO("Cliente creado");
    cliente.waitForExistence();

    //Creacion del mensaje de peticion
    ejercicio5::MensajeServicio srv;
    cout<< "Introduce la posicion X: ";
    cin>> srv.request.X;
    cout<< "Introduce la posicion Y: ";
    cin>> srv.request.Y;

    //Llamada al servicio
    if (cliente.call(srv)){
        
        ROS_INFO_STREAM("Reusltado de la llamada: " <<(srv.response.succes));
        return 0;
    }
    else{
        ROS_INFO("Error al llamar al servicio");
        return 1;
    }
}