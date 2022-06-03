#ifndef VOLUMEN_HXX
#define VOLUMEN_HXX


#include "Imagen.hxx"

using namespace std;

class Volumen {
  // Conjuntos mínimo de datos
  private:
    string nombreBase;
    int n_im; //Maximo 99
    vector < Imagen > volumen;
    int ancho;
    int altura;
    int maxVal;

  // Comportamiento (operaciones)
  public:
    Volumen()=default;
    void CargarVolumen (char base[], int nim, bool &volC);
    void InfoVolumen();
    void AgregarImg(Imagen img);

    int ObtenerFilas();
    int ObtenerColumnas();
    int ObtenerNumeroImagenes();
    vector <Imagen> ObtenerListaImagenes();
    int ObtenerMaxVal();

    void ImprimirVolumen();
    
    
};

#endif