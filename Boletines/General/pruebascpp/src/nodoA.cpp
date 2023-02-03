#include <ros/ros.h>
#include <pruebascpp/Mensaje.h>

#include <iostream>
using namespace std;

int main(int argc, char ** argv){

    //Creamos el nodo principal no
    ros::init(argc, argv, "nodoA");
    ros::NodeHandle nh;

    //Creamos el publicador
    ros::Publisher pub = nh.advertise<pruebascpp::Mensaje>("topicA", 1000);

    //Creamos el mensaje
    pruebascpp::Mensaje msg;

    int contador = 0;

    //Creamos el bucle de publicacion
    ros::Rate loop_rate(1);

    while (ros::ok()) {
        contador += 1;
        msg.A = contador;
        pub.publish(msg);
        loop_rate.sleep();
    }
}