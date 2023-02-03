#include <ros/ros.h>
#include <std_msgs/Int32.h>
using namespace std;

void callback(const std_msgs::Int32::ConstPtr& msg, int *suma,  int *contador){
    /*Funcion que se ejecuta cuando se recibe un mensaje por el subcriptor nodoB*/
    ROS_INFO("EL numero recibido es %d", msg->data);

    //Defincion de variables globales
    int numero = msg->data; 

    //Creacion de la suma 
    int suma_fun = *suma ;
    int contador_fun = *contador;

    if (contador_fun == 10){
        suma_fun += numero;
        contador = contador + 1;
        contador = 0;
        ROS_INFO("La suma es: %d", suma_fun);
    }
    else{
        suma_fun += numero;
    }

}

int main(int argv, char **arg){
    //Creacion del nodo principal 
    ros::init(argv, arg, "NodoBPrincipal");
    ros::NodeHandle nh;

    //Creacion del subscriptor
    ros::Subscriber nodoB = nh.subscribe("nodoA", 10, callback);

    //Creacion de la variable global 
    int suma = 0;
    int contador = 0;

    ros::spin();
    return 0;

}