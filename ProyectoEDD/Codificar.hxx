#ifndef CODIFICAR_HXX
#define CODIFICAR_HXX

#include "Imagen.hxx"
#include "Dato.hxx"
#include "Huffman.hxx"

using namespace std;


class Codificar {
  private:
    string archivoHuffman;
    Imagen imgCargada;
    vector <Dato> Frecuencias;
    map <int, int> myMap;


    string nImgDecod;
    string nHufffmanDecod;
    Imagen imgDecod;

    
  public:
    void setArchivo(string arch);
    void setImagen(Imagen img);
    void setNombreImgDecod(string n);
    void setNombreHuffmanDecod(string h);


    string getNombreHufffmanDecod();


    void CodificarImagen(bool &codC);
    void VerificarVector (int aux);
    void ImprimirVector();
    bool Comparacion(Dato num1, Dato num2);
    void LlenarMap();
    void ImprimirMap();
    bool CodificarInfo();
    bool ArchivoBin();
    vector<Dato> ObtenerBytes();
    string UnificarCodigo(int arr[], int tam);


    bool DecodificarImagen();
    int BuscarIndice(int val);
    int BuscarCodigo(string code);
    void CrearImgDecod();
    string ObtenerNombreHuffmanDecod();
    
};


#endif