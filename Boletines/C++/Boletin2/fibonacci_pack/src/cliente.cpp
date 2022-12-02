#include <ros/ros.h>
#include <fibonacci_pack/fibo.h>
#include <iostream>
using namespace std;

int main(int argc, char ** argv){
    //Crecion del nodo principal del cliente
    ros::init(argc, argv, "cliente");
    ros::NodeHandle nh;

    //Creacion del cliente
    ros::ServiceClient client = nh.serviceClient<fibonacci_pack::fibo>("fibonacci");
    ROS_INFO("Cliente creado");


    //Esperamos por el servicio
    client.waitForExistence();
    ROS_INFO("Cliente conectado");

    //Creamos la peticion por terminal
    fibonacci_pack::fibo peticion;

    cout << "Introduce el tope: ";
    cin >> peticion.request.tope;

    //Enviamos la peticion
    if(client.call(peticion)){
        ROS_INFO("El servicio finalizo correctamente");
        ROS_INFO("Respuesta: %s", peticion.response.lista.c_str());
    }
    else {
        ROS_INFO("El servicio no finalizo correctamente");
    }

}