#include <ros/ros.h>
#include <Prueba/MensajeServicio.h>


class Servidor{
    /*Clase de un servidor de servicios*/
    private:
        ros::NodeHandle nh;
        ros::ServiceServer server;


    public:
        //Creamos el constructor
        Servidor(){
            server = nh.advertiseService("servicio", &Servidor::callback, this);
        }

    bool callback(Preueba::MensajeServicioRequest &req, Prueba::MensajeServicioResponse &res){
        /*Función callback del servicio*/
        ROS_INFO("Recibido: %s", req.mensaje.c_str());
        return true;
    }
}

int main(int argc, char **argv){

    //Creo el nodo principal
    ros::init(argc, argv, "servidor_con_clase");
    
    //Creo el objeto del servicio
    Servidor servidor;

    ros::spin();
    return 0;
}