#include <ros/ros.h>
#include <fibonacci_pack/fibo.h>
#include <iostream>
using namespace std;

bool function_fibonacci(fibonacci_pack::fiboRequest &req, fibonacci_pack::fiboResponse &res){
    /*Funcion que se ejecuta cuando llega una peticion al servidor*/

    //Calculo del numero de fibonacci con un tope de 100 y el resultado lo añadimos a un string
    ROS_INFO("Iniciamos el calculo del numero de fibonacci");
    int a = 0, b = 1, c = 0;
    string s = "";
    for (int i = 0; i < req.tope; i++){
        c = a + b;
        a = b;
        b = c;
        s += to_string(c) + " ";
    }
    
    //Impresion del resultado
    ROS_INFO("El resultado es: %s", s.c_str());
    //Asignamos el resultado a la respuesta
    res.lista = s;
    return true;

}

int main(int argc, char ** argv){
    //Creacion del nodo principal del servicio 
    ros::init(argc, argv, "servidor");
    ros::NodeHandle nh;

    //Creacion del servicio
    ros::ServiceServer server = nh.advertiseService<fibonacci_pack::fiboRequest, fibonacci_pack::fiboResponse>("fibonacci", function_fibonacci);
    ROS_INFO("Servicio creado");

    ros::spin();
    return 0;
}