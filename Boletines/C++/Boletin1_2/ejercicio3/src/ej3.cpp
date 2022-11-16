#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char ** argv){

    //Creacion del nodo principal
    ros::init(argc, argv, "ej3");
    ros::NodeHandle nh;

    //Creacion del publicador
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);

    //Creacion del mensaje
    geometry_msgs::Twist msg;
    
    //Peticion de las velocidades por teclado

    std::cout << "Introduce la velocidad lineal: ";
    std::cin >> msg.linear.x;
    std::cout << "Introduce la velocidad angular: ";
    std::cin >> msg.angular.z;

    while(ros::ok()){

        pub.publish(msg);
    }

}