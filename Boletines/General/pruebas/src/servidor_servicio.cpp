#include <ros/ros.h>
#include <pruebas/MensajeServicio.h>

#include <iostream>
using namespace std;

/*
bool callback(pruebas::MensajeServicioRequest &req, pruebas::MensajeServicioResponse &res){
    cout << "Peticion: " << req.Peticion << endl;
    res.Resultado = req.Peticion * 2;
    return true;
}

int main(int argc, char ** argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "servidor_servicio");
    ros::NodeHandle nh;

    //Creacion del servidor
    ros::ServiceServer servidor = nh.advertiseService<pruebas::MensajeServicioRequest, pruebas::MensajeServicioResponse>("servicio", callback);

    ros::MultiThreadedSpinner spinner(4);
    spinner.spin();
    return 0;
}
*/

class Servidor{
    private:
        ros::NodeHandle nh;
        ros::ServiceServer servidor;

        bool callback(pruebas::MensajeServicioRequest &req, pruebas::MensajeServicioResponse &res)
        {
            cout << "Peticion: " << req.Peticion << endl;
            res.Resultado = req.Peticion * 2;
            return true;
        }

    public:
        Servidor(){
            servidor = nh.advertiseService("servicio", &Servidor::callback, this);
        }

        
};      


int main(int argc, char ** argv){
    //Creacion del nodo principal 
    ros::init(argc, argv, "servidor_servicio");
    ros::NodeHandle nh;

    //Creacion del servidor
    Servidor servidor;

    ros::MultiThreadedSpinner spinner(4);
    spinner.spin();
    return 0;
}