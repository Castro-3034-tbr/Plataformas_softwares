#include <ros/ros.h>
#include <pruebas2/Mensaje.h>
#include <std_msgs/Int32.h>

#include <iostream>
using namespace std;

//Creacion de variables globales
int valor = 0;


void callback(const pruebas2::Mensaje::ConstPtr& msg){
    cout << "Recibido: " << msg->A << endl;
    valor = msg->A*2;
}

int main(int argc, char ** argv){
    //Creamos el nodo principal 
    ros::init(argc, argv, "nodoB");
    ros::NodeHandle nh;

    //Creamos un suscriptor
    ros::Subscriber sub = nh.subscribe("topicA", 1000, callback);
    ros::Publisher pub = nh.advertise<std_msgs::Int32>("topicB", 1000);

    //Creamos el mensaje
    std_msgs::Int32 msg;
    ros::Rate loop_rate(1);


    //Creamos el bucle
    while(ros::ok()){
        msg.data = valor;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::MultiThreadedSpinner spinner(4);
    spinner.spin();
    return 0;
}