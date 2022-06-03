#ifndef PROYECCION_HXX
#define PROYECCION_HXX


#include "Volumen.hxx"


using namespace std;

class Proyeccion{
  private:
    string direccion;
    string criterio;
    string archivo;
    Imagen resultado;
    Volumen volumenRecibido;
    
  public:
    void setDireccion(string dir);
    void setCriterio(string cri);
    void setArchivo(string arch);
    void printInfo();
    void crearProyeccion(Volumen volumen, bool &proC);
    void ProyeccionEnX(std::vector <Imagen> l);
    void ProyeccionEnY(std::vector <Imagen> l);
    void ProyeccionEnZ(std::vector <Imagen> l);
    Volumen ObtenerVolumen();
    void CrearArchivo();

};

#endif