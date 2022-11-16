#include <ros/ros.h>
#include <cualificaciones/MensajeCualificacion.h>


#include <iostream>
using namespace std;

int main(int arg, char ** arv){
    //Creacion del nodo plublicador 
    ros::init(arg, arv, "publicador");
    ros::NodeHandle nh;

    //Creacion del publicador
    ros::Publisher publicador = nh.advertise<cualificaciones::MensajeCualificacion>("cualificacion", 10);

    //Creacion del mensaje 
    cualificaciones::MensajeCualificacion Mensaje;

    //Creacion dela frecuancia del bucle 
    int siguiente = 1;

    while (ros::ok() and siguiente != 0){
        //Peticion de los datos por terminal 
        string nombrealumno;
        cout << "Introduce el nombre: ";
        cin >> nombrealumno;

        string asignatura;
        cout << "Introduce la asignatura: ";
        cin >> asignatura;

        int convocatoria;
        cout << "Introduce la convocatoria: ";
        cin >> convocatoria;

        int nota;
        cout << "Introduce la nota: ";
        cin >> nota;

        //Asignacion de los datos al mensaje
        Mensaje.NombreAlumno = nombrealumno;
        Mensaje.Asignatura = asignatura;
        Mensaje.Convocatoria = convocatoria;
        Mensaje.Nota = nota;
        //Publicacion del mensaje
        publicador.publish(Mensaje);

        cout << "¿Desea seguir publicando? (1: Si, 0: No): ";
        cin >> siguiente;
    }

    ros::spin();
    
    return 0;
}