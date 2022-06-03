#ifndef SEMILLA_HXX
#define SEMILLA_HXX

#include "Imagen.hxx"

using namespace std;

class Semilla
{
private:
    int fil; //X
    int col; //Y
    int intensidad; //L
public:
    void SetFila(int fila);
    void SetColumna(int col);
    void SetIntensidad(int l);
    int ObtenerFila();
    int ObtenerColumna();
    int ObtenerIntesidad();
};

#endif