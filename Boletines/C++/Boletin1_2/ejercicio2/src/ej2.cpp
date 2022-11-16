#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <algorithm>


using namespace std;


void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    //Funcion que se ejecuta cada vez que llega un mensaje de laser

    //Calculo de la distancia del elemeento central 
    int centro = (msg->ranges).size()/2;
    float distancia = msg->ranges[centro];

    //Comprobacion del primer elemento 
    float distancia1 = msg->ranges[0];

    //Obtencion de la distancia minima y de su angulo de varido 
    vector<float>::const_iterator it = min_element(msg->ranges.begin(), msg->ranges.end());
    float distancia_minima = *it;

    //Impresion de los datos 
    ROS_INFO("Distancia del elemento central: %f  distancia1: %f distancia_minima: %f angulo_minimo  %f", distancia, distancia1, distancia_minima , (it-msg->ranges.begin())*msg->angle_increment*180/3.1416);

}

int main (int argc , char ** argv ){

    //Creacion del nodo principal
    ros::init(argc, argv, "ej2");
    ros::NodeHandle nh;

    //Creacion del subcriptor 
    ros::Subscriber sub = nh.subscribe("/scan", 1000, laserCallback);

    ros::spin();

}