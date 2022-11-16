#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
using namespace std;

void callback(const nav_msgs::Odometry::ConstPtr& msg)
{
    //Funcion que se ejecuta cuando llega un mensaje por el topic odom 
    ROS_INFO_STREAM("informacion: x " << msg->pose.pose.position.x << "  y "<<msg->pose.pose.position.y);
    
}
int main(int argc, char **argv){

    //Creacion del nodo principal
    ros::init(argc, argv, "NodoPrincipal");
    ros::NodeHandle nh;

    //Creacion del subcriptor 
    ros::Subscriber sub= nh.subscribe("/odom",1000 , callback);

    //Creacion del bucle 
    ros::spin();

}