#include <ros/ros.h>
#include <Servicio/Prueba.h>
#include <iostream>
using namespace std;

bool callback (Servicio::PruebaRequest &req, Servicio::PruebaResponse &res){
    /*Funcion que se ejecuta cuando llega una peticion al servidor*/

    //Ejemplo 
    ros::Rate rate(1);
    for(int i = 0 ; i < req.valor ; i++){
        ROS_INFO("Esperando %d segundos", i);
        rate.sleep();
    }
    res.valor = req.valor*2;

    return true;
}

int main(int argc, char ** argv){
    //Creacion del nodo principal
    ros::init_node("Servidor", argc, argv);
    ros::NodeHandle nh;

    //Creacion del servidor de servicios
    ros::ServiceServer server = nh.advertiseService<Servicio::PruebaRequest , Servicio:PruebaResponse >("Servidor", callback);

    //Creamos varios hilos de escucha
    ros::MultiThreadedSpinner spinner(4);
    spinner.spin();
}