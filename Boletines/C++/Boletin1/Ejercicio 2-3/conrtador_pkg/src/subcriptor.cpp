#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
using namespace std;

void CallbackNumeros(const std_msgs::Int32::ConstPtr &msg){
    ROS_INFO_STREAM("El numero recibido es:" << msg->data);

}

int main(int argc, char **argv)
{
    //Inicializacion del nodo
    ros::init(argc, argv, "nodo_subcriptor");
    //Creacion del objeto nodo
    ros::NodeHandle nh;

    //Creacion del subcriptor 
    ros::Subscriber sub = nh.subscribe<std_msgs::Int32>("numeros", 5, CallbackNumeros);
    ROS_INFO("Subcriptor creado");
    ros::spin();


    return 0;
}