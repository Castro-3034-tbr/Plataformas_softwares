#include <ros/ros.h>
#include <std_msgs/Int32.h>

#include <iostream>
using namespace std;

//Declaracion de variables globales 
int a = 0;
bool encontrado = false;

void callback(const std_msgs::Int32::ConstPtr& msg){
    ROS_INFO("Recibido: %d", msg->data);
    a = msg->data;
    encontrado = true;
}

int main(int argc, char ** argv){
    //Creacion del nodoA
    ros::init(argc, argv, "nodoC");
    ros::NodeHandle nh;
    ROS_INFO("Nodo A creado");

    //Creacion del publicador
    ros::Publisher pub = nh.advertise<std_msgs::Int32>("PublicacionA", 1000);
    ROS_INFO("Publicador creado");

    //Creacion de un subscriptor
    ros::Subscriber sub = nh.subscribe("ModoB", 1000, &callback);

    std_msgs::Int32 msg;
    ros::Rate rate(1);

    while (ros::ok()){
        msg.data = a*2;
        pub.publish(msg);
        ROS_INFO("Publicando: %d", msg.data);
        ros::spinOnce();
        rate.sleep();
    }

    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();

    return 0;
}