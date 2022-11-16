#include <ros/ros.h>
#include <cualificaciones/MensajeCualificacion.h>
using namespace std;

void Callback(const cualificaciones::MensajeCualificacion::ConstPtr& msg){
    /*Funcion que se ejecuta cuando se recibe un mensaje por el subcritor*/
    ROS_INFO("Nombre: %s , Asignatura %s , Convocatoria %d , Nota %d", msg->NombreAlumno.c_str(), msg->Asignatura.c_str(), msg->Convocatoria, msg->Nota);

}
int main(int argv, char ** arg){
    //Creacion de nodo subcriptor 
    ros::init(argv, arg, "NodoSubcriptor");
    ros::NodeHandle nh;

    //Creacion del subcriptor
    ros::Subscriber sub = nh.subscribe("cualificacion", 10, Callback);

    ros::spin();

    return 0;
}