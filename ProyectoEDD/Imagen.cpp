#include <iostream>
#include "Imagen.hxx"
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
string Imagen::ObtenerNombre (){
  return this->nombre;
}


void Imagen::CargarImagen (string nImagen, bool &imgC)
{
  
  ifstream archivo(nImagen);
  string linea;
  string numero;
  char pattern= ' ';

  string temp;

  if (archivo.is_open())
  {
    this->nombre= nImagen;
    //Leer codigo
    getline (archivo, linea);
    this->codigo=linea;

    //Leer n_col y n_fil    W(ancho-col) - H(alto-filas)
    getline (archivo, linea);
     int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> results;

  while (posFound >= 0) {
    posFound = linea.find(pattern, posInit);
    splitted = linea.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
    int ancho = atoi(results[0].c_str());
    int altura = atoi(results[1].c_str());
    this->columnas = ancho;
    this->filas= altura;
    
    //Leer Max
    getline(archivo, linea);
    int max= atoi(linea.c_str());
    this->max_val = max;

    
    //Leer Matriz- Se lee por linea
    vector < int > fran;
    int aux=0;
    for (int i=0 ; i<this->filas; i++)
      {
        for (int j=0; j<this->columnas; j++)
          {
            archivo >> aux;
            fran.push_back(aux);
          }
        
      } 
    archivo.close();
    
    int **m;
    m=new int*[this->filas];
    /*
    for (int i=0 ; i<img.filas; i++)
      {
        m[i]=new int[img.columnas];
      }
    */
    int cont=0;
    for (int i=0 ; i<this->filas; i++)
      {
        for (int j=0; j<this->columnas; j++)
          {
            this->matriz[i][j]=fran[cont];
            cont++;
          }
        
      } 
    imgC=true;
  }else {
    this->nombre="";
    cout << "No se encotro el archivo"<<endl;
    imgC=false;
  }
  
  
}

void Imagen::InfoImagen(){

  cout << "IMAGEN CARGADA EN MEMORIA"<<endl;
  cout << "Codigo: "<< this->nombre <<endl;
  cout << "Ancho : "<< this->columnas <<endl;
  cout << "Altura: "<< this->filas << endl;
  
}

int Imagen::ObtenerColumnas(){
  return this->columnas;
}

int Imagen::ObtenerFilas(){
  return this->filas;
}

void Imagen::ImprimirMatriz(){
  for (int i=0 ; i< this->filas; i++)
    {
      for (int j=0; j< this->columnas; j++)
        {
          cout << this->matriz[i][j]<< "-";
        }
      cout << "FIN"<<endl;
    }
}

int Imagen::ObtenerMaxVal(){
  return this->max_val;
}

void Imagen::FijarCodigo(string cod){
  this->codigo= cod;
}
void Imagen::FijarNombre(string nom){
  this->nombre= nom;
}
void Imagen::FijarColumnas(int col){
  this->columnas= col;
}
void Imagen::FijarFilas(int fil){
  this->filas= fil;
}
void Imagen::FijarMaxVal(){
  int maxVal=0;
  for (int i=0; i< this->filas; i++)
    {
      for (int j=0; j<this->columnas; j++)
        {
          if (maxVal < this->matriz[i][j])
          {
            maxVal = this->matriz[i][j];
          }
        }
    }

  this->max_val = maxVal;
}

void Imagen::FijarMaxVal(int maxVal){
  this->max_val= maxVal;
}