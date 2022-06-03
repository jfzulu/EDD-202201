#include "Semilla.hxx"

void Semilla::SetFila(int fila){
    this->fil = fila; 
}

void Semilla::SetColumna(int col){
    this->col = col;
}

void Semilla::SetIntensidad(int l){
    this->intensidad = l;
}

int Semilla::ObtenerColumna(){
    return this->col;
}

int Semilla::ObtenerFila(){
    return this->fil;
}

int Semilla::ObtenerIntesidad(){
    return this->intensidad;
}

