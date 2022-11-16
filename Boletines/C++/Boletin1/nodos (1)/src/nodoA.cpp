#include <ros/ros.h>
#include <std_msgs/Int32.h>
using namespace std;



void callback_nodoB(const std_msgs::Int32::ConstPtr& msg){
    /*Funcion que se ejecuta cuando se recibe un mensaje por el subcriptor nodoB*/
    ROS_INFO("EL numero recibido es %d", msg->data);
}

int main(int argc, char ** argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "NodoAPrincipal");
    ros::NodeHandle nh;

    //Creacion del publicador
    ros::Publisher nodoA = nh.advertise<std_msgs::Int32>("nodoA", 10);

    //Creacion de subcriptor
    ros::Subscriber nodoB = nh.subscribe("nodoB", 10, callback_nodoB);

    //Creacion del mensaje
    std_msgs::Int32 Mensaje;
    
    //Creacion de variables locales 
    int numero = 0;

    while (ros::ok()){
        
        //Peticion de los datos por terminal 
        cout << "Introduce un numero: ";
        cin >> numero;

        //Asignacion de los datos al mensaje
        Mensaje.data = numero;
        //Publicacion del mensaje
        nodoA.publish(Mensaje);

        ros::spinOnce();
    }
    

    return 0;
}