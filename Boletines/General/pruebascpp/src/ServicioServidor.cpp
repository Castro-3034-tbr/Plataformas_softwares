#include <ros/ros.h>
#include <pruebascpp/MensajeServicio.h>

#include <iostream>
using namespace std;

/*
bool callback(pruebascpp::MensajeServicioRequest &req, pruebascpp::MensajeServicioResponse &res){
    cout << "Peticion: " << req.Peticion << endl;
    res.Resultado = req.Peticion * 2;
    return true;
}


int main (int argc, char ** argv){

    // Creacion del nodo principal
    ros::init(argc, argv, "servidor_servicio");
    ros::NodeHandle nh;

    // Creacion del servidor
    ros::ServiceServer servidor = nh.advertiseService<pruebascpp::MensajeServicioRequest, pruebascpp::MensajeServicioResponse>("Servicio", callback);
    ROS_INFO("Servidor creado");

    ros::MultiThreadedSpinner spinner(4);
    spinner.spin();
    return 0;
}
*/

class Servidor{
    private:
        ros::NodeHandle nh;
        ros::ServiceServer servidor;

        bool callback (pruebascpp::MensajeServicioRequest &req, pruebascpp::MensajeServicioResponse &res){
            cout << "Peticion: " << req.Peticion << endl;
            res.Resultado = req.Peticion * 2;
            return true;
        }
    
    public:
        Servidor(){
            servidor = nh.advertiseService("Servicio", &Servidor::callback, this);
        }
};


int main(int argc, char ** argv ){
    // Creacion del nodo principal
    ros::init(argc, argv, "servidor_servicio");
    ros::NodeHandle nh;
    
    //Creacion del objeto de servicio
    Servidor servidor;
    ros::spin();
    return 0;
}