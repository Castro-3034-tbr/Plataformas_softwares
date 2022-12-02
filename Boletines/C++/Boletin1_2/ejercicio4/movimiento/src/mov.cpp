#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>


#include <iostream>
using namespace std;

//Definicion de variables globales
ros::Publisher CmdVel;
float distancia_frontal;

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
    /*Funcion que se ejecuta cuando llega un valor por el topic base_scan*/

    int tamano = msg->ranges.size();
    distancia_frontal = msg->ranges[tamano/2];
    ROS_INFO("Distancia frontal: %f", distancia_frontal);
}

//Funcion para moverse recto 
void movimiento_recto(float dir){
    /*Funcion que se ejecuta cuando se quiere mover el robot recto*/

    //Creacion del mensaje
    geometry_msgs::Twist msg;
    msg.linear.x = 5*dir;

    //Publicacion del mensaje
    if (distancia_frontal >1){
        CmdVel.publish(msg);
    }
}

void movimiento_giratorio(float dir){
    /*Funcion que se ejecuta cuando se queire girar el robot*/

    //Creacion del bucle 
    ros::Rate loop_rate(0.5);
    
    //Creacion del mensaje
    geometry_msgs::Twist msg;
    msg.angular.z = 1.6*dir;

    for (int i = 0; i < 2; i++){
        CmdVel.publish(msg);
        loop_rate.sleep(); 
    }
}


int main(int argc, char **argv){

    //Creacion del nodo principal
    ros::init(argc, argv, "Movimiento");
    ros::NodeHandle nh;


    //Creacion del publicador de velocidad
    CmdVel = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    //Creacion del subcriptor del laser 
    ros::Subscriber Laser= nh.subscribe("/base_scan_1", 100, laserCallback);

    while (ros::ok()){
        //Peticion de la opcion de movimiento por terminal 
        int opcion;
        cout << "Introduzca la opcion de movimiento: ";
        cin >> opcion;

        //Switch para seleccionar el movimiento
        switch(opcion){
            case 6:
                //Movimiento recto para delante
                ROS_INFO("Movimiento recto para delante");
                movimiento_recto(1);
                break;
                
            case 4:
                //Movimiento recto para atras 
                ROS_INFO("Movimiento recto para atras");
                movimiento_recto(-1);
                break;
            case 8:
                //Giro para la izquierda
                ROS_INFO("Giro para la izquierda");
                movimiento_giratorio(1);
                break;

            case 2:
                //Giro para la derecha
                ROS_INFO("Giro para la derecha");
                movimiento_giratorio(-1);
                break;
            
        }
        ros::spinOnce();
    }
    return 0;
}