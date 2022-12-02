#include "ros/ros.h"
#include "Servicio/Prueba.h"
#include "iostream"
using namespace std;

int main(int argc, char **argv){
    //Creamos el nodo principal 
    ros::int_node("Cliente", argc, argv);
    ros::NodeHandle nh;
    
    //Creacion del cliente de servicios
    ros::ServiceClient client = nh.serviceClient<std_msgs::Int32>("Servidor");

    //Espremos para que el servidor este listo
    client = waitForExistence();
    ROS_INFO("Servidor listo");

    //Creamos el mensaje
    Servicio::Prueba peticion;
    peticion.request.valor = 5;

    //Llamamos al servicio
    if(client.call(msg)){
        //Si el servicio se ejecuto correctamente
        ROS_INFO("El servicio finalizo correctamente");
        //
        ROS_INFO("El resultado es: %d", msg.response.valor_respues);
        return 0
    }
    else{
        ROS_ERROR("Fallo al llamar al servicio");
        return 1;
    }

}