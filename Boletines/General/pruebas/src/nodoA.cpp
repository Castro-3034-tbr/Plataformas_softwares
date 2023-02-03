#include <ros/ros.h>
#include <pruebas/mensaje.h>

#include <iostream>
using namespace std;

int main(int argc, char ** argv){
    //Creacion del nodo principal
    ros::init(argc, argv, "nodoA");
    ros::NodeHandle nh;

    //Creacion del publicador
    ros::Publisher pub = nh.advertise<pruebas::mensaje>("NodoA", 1000);

    //Creacion del mensaje
    pruebas::mensaje msg;
    msg.A = 0;
    msg.B = 1;
    
    //Creacion del bucle
    ros::Rate loop_rate(1);
    while(ros::ok()){
        msg.A += 1;
        msg.B += 1;
        pub.publish(msg);
        ROS_INFO("A: %d  B: %d", msg.A , msg.B);
        loop_rate.sleep();
    }
    return 0;
}