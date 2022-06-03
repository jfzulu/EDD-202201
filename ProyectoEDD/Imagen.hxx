#ifndef IMAGEN_HXX
#define IMAGEN_HXX

#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <sstream>



using namespace std;

class Imagen {
  // Conjuntos mínimo de datos
  private:
    string codigo;
    string nombre;
    int columnas;
    int filas;
    int max_val;
    

  // Comportamiento (operaciones)
  public:
    int matriz[300][300];
    Imagen()=default;
    string ObtenerNombre();
    int ObtenerColumnas();
    int ObtenerFilas();
    int ObtenerMaxVal();

    void FijarCodigo(string cod);
    void FijarNombre(string nom);
    void FijarColumnas(int col);
    void FijarFilas(int fil);
    void FijarMaxVal();
    void FijarMaxVal(int maxVal);
    void CargarImagen (string nImagen, bool &imgC);
    void ImprimirMatriz();
    void InfoImagen ();
};

#endif