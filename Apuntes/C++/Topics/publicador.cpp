#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <iostream>
using namespace std;

int main(int argc, char ** argv){

    //Creamos el nodo principal del programa
    ros::init(argc, argv, "Nodo publicador");
    ros::NodeHandle nh;

    //Creamos el Publicador
    ros::Publisher pub = nh.advertise<std_msgs::Int32>(contador, 1);

    //Creacion del mensaje
    std_msgs::Int32 cont;
    cont.data = 0;

    //Creacion de la frecuencia de publicacion 
    ros::Rate loop_rate(1);

    //Bucle de publicacion
    while (ros::ok()){
        pub.publish(cont);
        cont.data++;
        loop_rate.sleep();
    }

    return 0;
}