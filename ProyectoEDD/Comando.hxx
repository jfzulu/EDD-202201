#ifndef COMANDO_HXX
#define COMANDO_HXX

#include <string>
#include <vector>
#include "Imagen.hxx"
using namespace std;

/**
  * @class Comandos, representa la información almacenada y el manejo de los comandos
*/
class Comando {
  // Conjunto mínimo de datos
  protected:
    string cmd; 
    int n_para;
    string ayuda;
    string msj_exito;
    string msj_fallo;

  // Comportamiento (operaciones)
  public:
    Comando()=default;
    void FijarComando(string comando);
    void FijarParametros(int n);
    void CargarComandos(vector<Comando> &c);
    vector<string> Dividir(string str, char pattern, int &cont);
    bool ValidarComando(int contP, vector<string> parametros, vector<Comando> c);
    void ImprimirComandos(vector<Comando> c);
    int EjecutarComando(vector<string> parametros, vector<Comando> c, int cantP);

};

#endif