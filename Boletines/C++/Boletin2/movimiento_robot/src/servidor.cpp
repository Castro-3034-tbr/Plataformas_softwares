#include <ros/ros.h>
#include <movimiento_robot/movimiento.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
using namespace std;

//Declaracion de variables globales
float distancia_frontal;
ros::Publisher CmdVel;

void funcion_laser(const sensor_msgs::LaserScan::ConstPtr& msg){
    //Funcion que se obtiene la distancia frontal del robot cuando se publica en el topic /scan

    int posicion_fontal = (msg->ranges).size();
    distancia_frontal = msg->ranges[posicion_fontal/2];

}

bool funcion_movimiento(movimiento_robot::movimiento::Request &req, movimiento_robot::movimiento::Response &res){
    //Funcion que se ejecuta cuando se llama al servicio /movimiento_robot
    
    //Creamos el mensaje de velocidad
    geometry_msgs::Twist velocidad;
    velocidad.linear.x = 0.3;

    //Creamos el movimiento del robot

    ros::Rate loop_rate(1);

    for( int j = 0 ; j<4 ;j++){
        //Movimiento recto
        velocidad.angular.z = 0;
        for(int i= 0; i<req.area; i++){
            if(distancia_frontal > 0.5){
                CmdVel.publish(velocidad);
                loop_rate.sleep();
            }
            else{
                velocidad.linear.x = 0;
                CmdVel.publish(velocidad);
                loop_rate.sleep();
            }
        }
        //Movimiento giratorio
        velocidad.linear.x = 0;
        velocidad.angular.z = 1.6;
        for(int i = 0; i<2 ; i++){
            CmdVel.publish(velocidad);
            loop_rate.sleep();
        }
    }
}

int main(int argc, char ** argv){

    //Creacion del nodo principal 
    ros::init(argc, argv, "servidor");
    ros::NodeHandle nh;

    //Creacion del servicio
    ros::ServiceServer server = nh.advertiseService<movimiento_robot::movimientoRequest, movimiento_robot::movimientoResponse>("movimiento_servicio", funcion_movimiento);

    //Creacion del subcriptor del topic de laser_scan 
    ros::Subscriber sub = nh.subscribe("/base_scan_0", 1000, funcion_laser); 

    //Creacion del publicador del topic de velocidad
    CmdVel=nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    //Creacion de varios hilos de escucha 
    ros::MultiThreadedSpinner spinner(3);
    spinner.spin();
}