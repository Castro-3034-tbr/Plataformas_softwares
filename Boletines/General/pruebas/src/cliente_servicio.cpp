#include <ros/ros.h>
#include <pruebas/MensajeServicio.h>
#include <std_msgs/Int32.h>

#include <iostream>
using namespace std;

int main(int argc, char ** argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "cliente_servicio");
    ros::NodeHandle nh;

    //Creacion del cliente
    ros::ServiceClient cliente = nh.serviceClient<pruebas::MensajeServicio>("servicio");
    cliente.waitForExistence();


    pruebas::MensajeServicio msg;
    msg.request.Peticion= 2;


    //Enviamos el mensaje
    if(cliente.call(msg)){ 
        cout << "Respuesta: " << msg.response.Resultado  << endl;
        return 1;
    }else{
        cout << "Error en la llamada al servicio" << endl;
        return 0;
    }
}