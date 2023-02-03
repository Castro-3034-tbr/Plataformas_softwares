#include <ros/ros.h>
#include <std_msgs/Int32.h>
using namespace std;

int main(int argv, char ** arg){
    //Creacion del nodo principal 
    ros::init(argv, arg, "NodoAPrincipal");
    ros::NodeHandle nh;

    //Creacion del publicador
    ros::Publisher nodoA = nh.advertise<std_msgs::Int32>("nodoA", 10);

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
    }
    
    return 0;
}