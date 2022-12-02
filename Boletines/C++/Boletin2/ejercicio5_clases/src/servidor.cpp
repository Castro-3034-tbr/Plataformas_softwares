#include <ros/ros.h>
#include <ejercicio5/MensajeServicio.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>


#include <iostream>
using namespace std;

//Definicion de variables globales
int posicion_x = 0;
int posicion_y = 0;

ros::Publisher publicador_velocidad;

void posicionCallback(const nav_msgs::OdometryConstPtr & msg){
    /*Obtencion del posicion del robot cuando llega por mensaje*/

    //
    posicion_x = msg->pose.pose.position.x;
    posicion_y = msg->pose.pose.position.y;
    
}


void movimiento_recto(int pasos, int direccion){
    /*Funcion que se ejecuta para mover el robot x pasos para delante*/

    ROS_INFO("Moviendo el robot %d pasos con direccion %d", pasos, direccion);

    //Creacion del mensaje 
    geometry_msgs::Twist msg;
    msg.linear.x = 50*direccion;

    ros::Rate rate(5);
    for(int i=0; i <= pasos; i++){
        publicador_velocidad.publish(msg);
        rate.sleep();
    }
}

void girar_noventa(int direccion){
    /*Funcion que se ejecuta para mover el robot 90 grados*/

    ROS_INFO("Girando el robot 90 grados con direccion %d", direccion);
    //Creacion del mensaje
    geometry_msgs::Twist msg;
    msg.angular.z = 1.6*direccion;

    ros::Rate loop_rate(1);
    for (int i = 0; i < 5; i++){
        publicador_velocidad.publish(msg);
        loop_rate.sleep(); // loop_rate de 1hz
    }
}




bool funcionServicio(ejercicio5::MensajeServicioRequest &req, ejercicio5::MensajeServicioResponse &res){
    /*Funcion que se ejecuta cuando se pide una peticion al servicio */
    ROS_INFO("Peticion recibida");

    //Obtencion de los datos de la peticion
    int posX = req.X;
    int posY = req.Y;

    //Calculo de la distancia
    float distanciaX = posX - posicion_x;
    float distanciaY = posY - posicion_y;

    //Calculo de pasos
    int pasosX = distanciaX/0.5+1;
    int pasosY = distanciaY/0.5+1;

    ROS_INFO("Pasos en X: %d , Pasos en Y: %d", pasosX, pasosY);
    int direccionX = 1;
    if (pasosX < 0){
        direccionX = -1;
        pasosX*=-1;
    }
    
    
    int direccionY = 1;
    if (pasosY <0){
        direccionY = -1;
        pasosY*=-1;
    }
    
    ROS_INFO("Direccion en X: %d , Direccion en Y: %d", direccionX, direccionY);
    
    //Bucle de movimiento 
    movimiento_recto(pasosX,direccionX);
    girar_noventa(direccionY);
    movimiento_recto(pasosY,1);

    //Respuesta del servicio
    res.succes = 1 ;

    return true; 
}

int main (int argc, char ** argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "servidor");
    ros::NodeHandle nh;
    ROS_INFO("Nodo servidor creado");

    //Creacion del servicio
    ros::ServiceServer service = nh.advertiseService<ejercicio5::MensajeServicioRequest, ejercicio5::MensajeServicioResponse>("ServicioMovimiento", funcionServicio);
    ROS_INFO("Servicio creado");

    //Creacion del publicador de velocidad
    publicador_velocidad = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    //Suscripcion al topico de posicion
    ros::Subscriber sub = nh.subscribe("odom", 1000, posicionCallback);
    ROS_INFO("Suscripcion al topico de posicion creada");
    
    //Creacion de varios hilos
    ros::MultiThreadedSpinner spinner(4);
    spinner.spin();
    return 0;
}
