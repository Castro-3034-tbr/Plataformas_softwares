#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
using namespace std;

//Creacion del programa principal 
int main(int argc, char **argv)
{
    //Inicializacion del nodo
    ros::init(argc, argv, "nodo_contador");
    //Creacion del objeto nodo
    ros::NodeHandle nh;

    //Creacion del publicador 
    ros::Publisher pub = nh.advertise<std_msgs::Int32>("numeros", 5);

    //Creacion del objeto mensaje
    std_msgs::Int32 msg;

    ros::Rate rate(10);
    int cont = 0;

    while(ros::ok() ){
        msg.data = cont;
        pub.publish(msg);
        cont++;
        rate.sleep();
    }

    return 0;
}