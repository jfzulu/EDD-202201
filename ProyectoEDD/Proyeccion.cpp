#include "Proyeccion.hxx"
#include <iostream>
using namespace std;
void Proyeccion::setDireccion(string dir) { this->direccion = dir; }
void Proyeccion::setCriterio(string cri) { this->criterio = cri; }
void Proyeccion::setArchivo(string arch) { this->archivo = arch; }
Volumen Proyeccion::ObtenerVolumen() { return this->volumenRecibido; }
void Proyeccion::printInfo() {
  cout << "\nInformacion de Proyeccion: " << endl
       << "Direccion: " << this->direccion << endl
       << "Criterio: " << this->criterio << endl
       << "Archivo: " << this->archivo << endl;
}
void Proyeccion::crearProyeccion(Volumen volumen, bool &proC) {
  this->volumenRecibido = volumen;
  std::vector<Imagen> l = this->volumenRecibido.ObtenerListaImagenes();
  if (this->direccion == "X" || this->direccion == "x") {
    this->ProyeccionEnX(l);
    proC=true;
  }
  if (this->direccion == "Y" || this->direccion == "y") {
    this->ProyeccionEnY(l);
    proC= true;
  }
  if (this->direccion == "Z" || this->direccion == "z") {
    this->ProyeccionEnZ(l);
    proC=true;  
  }
  
}

void Proyeccion::ProyeccionEnX(std::vector<Imagen> l) {
  this->resultado.FijarFilas(this->volumenRecibido.ObtenerNumeroImagenes());
  this->resultado.FijarColumnas(l[0].ObtenerColumnas());
  this->resultado.FijarNombre(this->archivo);
  // Contar las columnas
  int maximo;
  int minimo;
  float promedio;
  float mediana;
  std::vector< int > datosMediana;
  float suma; //Sumatoria para el promedio
  for (int k = 0; k < l.size();
       k++) { // Primer ciclo por n imagenes en el volumen
         
    for (int i = 0; i < l[k].ObtenerColumnas();
         i++) {                      // Segundo ciclo por columnas
      maximo = 0;                    // Se inicializa en cero los valores
      minimo = l[k].ObtenerMaxVal(); // Cada columna se haya un valor unico
      promedio = 0;
      suma = 0;
      mediana = 0;
      datosMediana.clear();
      for (int j = 0; j < l[k].ObtenerFilas(); j++) { // Tercer ciclo por filas
        if (this->criterio == "maximo") {   // Si el criterio es maximo
          if (maximo < l[k].matriz[i][j]) { // El valor maximo es menor?
            maximo = l[k].matriz[i][j];     // Se le asigna a maximo ese valor
          }
        }
        if (this->criterio == "minimo") {   // Si el criterio es minimo
          if (minimo > l[k].matriz[i][j]) { // El valor de minimo es mayor?
            minimo = l[k].matriz[i][j];     // Se le asigna a minimo ese valor
          }
        }
        if (this->criterio == "promedio") { // Si el criterio es promedio
          suma =
              suma +
              l[k].matriz[i][j]; // Se suma todos los valores de dicha columna
        }
        if (this->criterio == "mediana") {  //Si el criterio es mediana
          datosMediana.push_back(l[k].matriz[i][j]); //Se agrega ese valor al vector de datos
        }

      } // Fin de tercer ciclo

      if (this->criterio == "maximo") {
        this->resultado.matriz[k][i] = maximo;
      }

      if (this->criterio == "minimo") {
        this->resultado.matriz[k][i] = minimo;
      }
      if (this->criterio == "promedio") {
        promedio = suma / l[k].ObtenerFilas(); // La sumatoria calculada se
                                               // divide por el numero de filas
        this->resultado.matriz[k][i] =
            promedio; // Se le asigna el valor promedio a la matriz
      }
      if (this->criterio == "mediana") {
        sort(datosMediana.begin(), datosMediana.end()); //Ordenar los elementos en el vector
        if (datosMediana.size() %2 == 2 )
        {
          mediana= datosMediana[datosMediana.size() / 2] + datosMediana[datosMediana.size() / 2 + 1];
          mediana = mediana/2;
        }else{
          mediana = datosMediana[datosMediana.size() / 2 + 1];
        }
        this->resultado.matriz[k][i] = mediana;
      }
    } // Fin de segundo ciclo
  
  } // Fin de primer ciclo
  this->resultado.FijarMaxVal();
}
void Proyeccion::ProyeccionEnY(std::vector<Imagen> l) {
  this->resultado.FijarFilas(this->volumenRecibido.ObtenerFilas());
  this->resultado.FijarColumnas(this->volumenRecibido.ObtenerNumeroImagenes());
  this->resultado.FijarNombre(this->archivo);
  int col = this->volumenRecibido.ObtenerColumnas();
  // Contar las columnas
  int maximo;
  int minimo;
  float promedio;
  float mediana;
  std::vector< int > datosMediana;
  float suma; //Sumatoria para el promedio
  for (int k = 0; k <  this->volumenRecibido.ObtenerNumeroImagenes() ;
       k++) { // Primer ciclo por n imagenes en el volumen
         
    for (int i = 0; i < l[k].ObtenerFilas();
         i++) {                      // Segundo ciclo para las filas
      maximo = 0;                    // Se inicializa en cero los valores
      minimo = this->volumenRecibido.ObtenerMaxVal(); // Cada columna se haya un valor unico
      promedio = 0;
      suma = 0;
      mediana = 0;
      datosMediana.clear();
      for (int j = 0; j < l[k].ObtenerColumnas(); j++) { // Tercer ciclo para las columnas
        if (this->criterio == "maximo") {   // Si el criterio es maximo
          if (maximo < l[k].matriz[i][j]) { // El valor maximo es menor?
            maximo = l[k].matriz[i][j];     // Se le asigna a maximo ese valor
          }
        }
        if (this->criterio == "minimo") {   // Si el criterio es minimo
          if (minimo > l[k].matriz[i][j]) { // El valor de minimo es mayor?
            minimo = l[k].matriz[i][j];     // Se le asigna a minimo ese valor
          }
        }
        if (this->criterio == "promedio") { // Si el criterio es promedio
          suma =
              suma +
              l[k].matriz[i][j]; // Se suma todos los valores de dicha columna
        }
        if (this->criterio == "mediana") {  //Si el criterio es mediana
          datosMediana.push_back(l[k].matriz[i][j]); //Se agrega ese valor al vector de datos
        }

      } // Fin de tercer ciclo

      if (this->criterio == "maximo") {
        this->resultado.matriz[i][k] = maximo;
      }

      if (this->criterio == "minimo") {
        this->resultado.matriz[i][k] = minimo;
      }
      if (this->criterio == "promedio") {
        promedio = suma / l[k].ObtenerColumnas(); // La sumatoria calculada se
                                               // divide por el numero de filas
        this->resultado.matriz[i][k] =
            promedio; // Se le asigna el valor promedio a la matriz
      }
      if (this->criterio == "mediana") {
        sort(datosMediana.begin(), datosMediana.end()); //Ordenar los elementos en el vector
        if (datosMediana.size() %2 != 0 )
        {
          mediana= datosMediana[datosMediana.size() / 2] + datosMediana[datosMediana.size() / 2 + 1];
          mediana = mediana/2;
        }else{
          mediana = datosMediana[datosMediana.size() / 2 + 1];
        }
        this->resultado.matriz[i][k] = mediana;
      }
    } // Fin de segundo ciclo
  
  } // Fin de primer ciclo
  this->resultado.FijarMaxVal();
  
}

void Proyeccion::ProyeccionEnZ(std::vector<Imagen> l) {
  this->resultado.FijarFilas(this->volumenRecibido.ObtenerFilas());
  this->resultado.FijarColumnas(this->volumenRecibido.ObtenerColumnas());
  this->resultado.FijarNombre(this->archivo);
  // Contar las columnas
  int maximo;
  int minimo;
  float promedio;
  float mediana;
  std::vector< int > datosMediana;
  float suma; //Sumatoria para el promedio
  for (int i = 0; i <  this->volumenRecibido.ObtenerFilas() ;
       i++) { // Primer ciclo para las Filas en el volumen
         
    for (int j = 0; j < this->volumenRecibido.ObtenerColumnas();
         j++) {                      // Segundo ciclo para las columnas
      maximo = 0;                    // Se inicializa en cero los valores
      minimo = this->volumenRecibido.ObtenerMaxVal(); // Cada columna se haya un valor unico
      promedio = 0;
      suma = 0;
      mediana = 0;
      datosMediana.clear();
      for (int k = 0; k <this->volumenRecibido.ObtenerNumeroImagenes(); k++) { // Tercer ciclo para las imagenes
        if (this->criterio == "maximo") {   // Si el criterio es maximo
          if (maximo < l[k].matriz[i][j]) { // El valor maximo es menor?
            maximo = l[k].matriz[i][j];     // Se le asigna a maximo ese valor
          }
        }
        if (this->criterio == "minimo") {   // Si el criterio es minimo
          if (minimo > l[k].matriz[i][j]) { // El valor de minimo es mayor?
            minimo = l[k].matriz[i][j];     // Se le asigna a minimo ese valor
          }
        }
        if (this->criterio == "promedio") { // Si el criterio es promedio
          suma =
              suma +
              l[k].matriz[i][j]; // Se suma todos los valores de dicha columna
        }
        if (this->criterio == "mediana") {  //Si el criterio es mediana
          datosMediana.push_back(l[k].matriz[i][j]); //Se agrega ese valor al vector de datos
        }

      } // Fin de tercer ciclo

      if (this->criterio == "maximo") {
        this->resultado.matriz[i][j] = maximo;
      }

      if (this->criterio == "minimo") {
        this->resultado.matriz[i][j] = minimo;
      }
      if (this->criterio == "promedio") {
        promedio = suma / this->volumenRecibido.ObtenerNumeroImagenes(); // La sumatoria calculada se
                                               // divide por el numero de imagenes
        this->resultado.matriz[i][j] =
            promedio; // Se le asigna el valor promedio a la matriz
      }
      if (this->criterio == "mediana") {
        mediana = 0;
        sort(datosMediana.begin(), datosMediana.end()); //Ordenar los elementos en el vector
          mediana = datosMediana[datosMediana.size()/ 2];
        this->resultado.matriz[i][j] = mediana;
      }
    } // Fin de segundo ciclo
  
  } // Fin de primer ciclo
  this->resultado.FijarMaxVal();
}


void Proyeccion::CrearArchivo(){
  ofstream file;
  int aux=0;
  int cont=0;
  vector < int > myVec;
  myVec.clear();
  file.open(this->archivo);
  file << "P2\n";
  file << this->resultado.ObtenerColumnas()<<" "<<this->resultado.ObtenerFilas()<<endl;
  file << this->resultado.ObtenerMaxVal()<<endl;
  
  for (int i=0; i<this->resultado.ObtenerFilas(); i++)
    {
      for (int j=0; j<this->resultado.ObtenerColumnas(); j++)
        {
          aux= this->resultado.matriz[i][j];
          file << aux << " ";
          cont++;
          if (cont == 40)
          {
            cont=0;
            file<< "\n";
          }
        }
    }
  
  

  file.close();
}
