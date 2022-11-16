#include <ros/ros.h>
#include <std_msgs/Int32.h>
using namespace std;

//Definicion de 
int suma = 0;
int contador = 0;
ros::Publisher pub;

void callback(const std_msgs::Int32::ConstPtr& msg){
    /*Funcion que se ejecuta cuando se recibe un mensaje por el subcriptor nodoB*/
    ROS_INFO("EL numero recibido es %d", msg->data);

    //Defincion de variables globales
    int numero = msg->data; 

    //Creacion de la suma 
    suma += numero; ;
    contador++; 

    
    if (contador %10 == 0){
        //Creacion del mensaje 
        std_msgs::Int32 Mensaje;
        Mensaje.data = suma;
        pub.publish(Mensaje);
        //Reiniciamos el valor de suma 
        suma = 0 ;
        ROS_INFO("La suma es: %d", suma);
    }
    
}

int main(int argc, char **argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "NodoBPrincipal");
    ros::NodeHandle nh;

    //Creacion del subscriptor
    ros::Subscriber nodoB = nh.subscribe("nodoA", 10, callback);

    //Creaciond del publicador 
    pub = nh.advertise<std_msgs::Int32>("nodoB", 10);
    

    //Bucle 
    ros::spin();
    return 0;

}