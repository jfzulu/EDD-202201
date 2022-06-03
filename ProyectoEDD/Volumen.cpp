#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "Volumen.hxx"
#include "Imagen.hxx"

void Volumen::CargarVolumen (char base[], int nim, bool &volC){
  Volumen vol;
  string inicio= "01";
  char format[]= ".pgm";
  
  char nombre[150]="";
  int decena= 0;
  int unidad= 1;
  char uni[2];
  Imagen img;
  fstream archivo;
  char dec[2];
  sprintf(dec, "%i", decena);
  for (int i=0 ; i< nim; i++)
    {
      if (unidad <10)
      {
        sprintf(uni, "%i", unidad);
        strcpy(nombre, base);
        strcat(nombre, dec);
        strcat(nombre, uni);
        strcat(nombre, format);
        unidad++;
      }
      else
      {
        decena++;
        unidad=0;
        sprintf(dec, "%i", decena);
        sprintf(uni, "%i", unidad);
        strcpy(nombre, base);
        strcat(nombre, dec);
        strcat(nombre, uni);
        strcat(nombre, format);
        unidad++;        
      }
      //cout << nombre<<endl;

      img.CargarImagen(nombre, volC);
      if (!volC){
        break;
      } else{
        this->AgregarImg(img);      
      }
    }

  this->n_im= nim;  
  this->nombreBase= base;
  this->altura= img.ObtenerFilas();
  this->ancho= img.ObtenerColumnas();
  this->maxVal = img.ObtenerMaxVal();
  
  
  
}

void Volumen::AgregarImg(Imagen img){
  this->volumen.push_back(img);
}

void Volumen::InfoVolumen(){
  cout << "INFORMACION VOLUMEN"<<endl;
  cout << "Nombre base: "<< this->nombreBase<<endl;
  cout << "Cantidad Imgs: "<< this->n_im<<endl;
  cout << "Ancho: "<< this->ancho<<endl;
  cout << "Altura: "<<this->altura <<endl;
}


int Volumen::ObtenerFilas(){
  return this->altura;
}
int Volumen::ObtenerColumnas(){
  return this->ancho;
}
vector <Imagen> Volumen::ObtenerListaImagenes(){
  return this->volumen;
}
void Volumen::ImprimirVolumen(){
  for (int i=0; i<this->volumen.size(); i++)
    {
      cout << "IMAGEN "<< i+1<<endl;
      this->volumen[i].ImprimirMatriz();
    }
}

int Volumen::ObtenerNumeroImagenes(){
  return this->n_im;
}

int Volumen::ObtenerMaxVal(){
  return this->maxVal;
}