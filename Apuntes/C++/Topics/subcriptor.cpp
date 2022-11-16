#include <ros/ros.h>
#include <std_msgs/Int32.h>

void Callback(const std_msgs::Int32::ConstPtr& msg)
{
    /*Funcion que se ejecuta cuando llega un mensaje por el topic subcriptor*/
    ROS_INFO("I heard: [%d]", msg->data);
}

int mian(int argc, char **argv){

    //Creamos el nodo principal 
    ros::init(argc, argv, "subcriptor");
    ros::NodeHandle nh;

    //Creamos el subcriptor
    ros::Subscriber sub = nh.subscribe("topic", 1000, Callback);

    //Creacion del bucle infinito 
    ros::spin();

    return 0;
    
}