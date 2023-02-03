#include <ros/ros.h>
#include <pruebas/mensaje.h>
#include <std_msgs/Int32.h>

#include <iostream>
using namespace std;

ros::Publisher pub;
int a = 0;

void callback(const pruebas::mensaje::ConstPtr& msg){
    cout << "A: " << msg->A << endl;
    cout << "B: " << msg->B << endl;
    a = msg->A;
}

int main(int argc , char ** argv){
    //Creacion del nodo principal
    ros::init(argc, argv, "nodoB");
    ros::NodeHandle nh;

    //Creacion del subscriptor
    ros::Subscriber sub = nh.subscribe("NodoA", 1000, callback);

    pub = nh.advertise<std_msgs::Int32>("NodoB", 1000);
    std_msgs::Int32 msg;

    while (ros::ok()){
        msg.data = 2;
        pub.publish(msg);
        ros::spinOnce();
    }
    
    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();
    return 0;
}