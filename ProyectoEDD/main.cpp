/*
ENTREGA DE PROYECTO 1, ESTRUCTURA DE DATOS 2022-01
FEBRERO 2022
ELABORADO POR JOSE FERNANDO ZULUAGA ORTIZ
JUAN REYES
ISABELLA BLANCO
*/

#include "Codificar.hxx"
#include "Comando.hxx"
#include "Imagen.hxx"
#include "Proyeccion.hxx"
#include "Volumen.hxx"
#include "Segmentacion.hxx"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>

int main(int argc, char **argv)
{
  vector<Comando> l_comandos; // Lista de comandos
  vector<string> parametros;  // Vector con los parametros ingresados
  int contP = 0;              // Contador de parametros
  bool img_cargada = false;
  bool vol_cargado = false;
  bool pro_cargada = false;
  bool cod_cargada = false;
  bool decod_cargada = false;
  bool img_segmentada= false;
  l_comandos.clear();
  string comando_ingresado;
  Comando comando;
  Imagen imagen;
  Volumen volumen;
  Proyeccion proyeccion;
  Codificar codificar;
  Segmentacion segmentar;

  std::vector<Dato> bits; // Guarda el total de bites que toca leer
  bits.clear();
  comando.CargarComandos(l_comandos);
  // comando.ImprimirComandos(l_comandos);
  do
  {
    int op = 0;
    bool existe = false;
    contP = 0;
    cout << "$";
    std::getline(std::cin, comando_ingresado); // Ingresa comando
    parametros.clear();
    parametros = comando.Dividir(comando_ingresado, ' ', contP);
    existe = comando.ValidarComando(contP, parametros, l_comandos);
    if (comando_ingresado != "salir")
    {
      if (existe)
      {
        op = comando.EjecutarComando(parametros, l_comandos, contP);
        if (op == 1)
        {
          string pgm = parametros[1];
          imagen.CargarImagen(pgm, img_cargada);
          if (img_cargada)
          {
            cout << "La imagen " << imagen.ObtenerNombre() << " ha sido cargada"
                 << endl;
            // imagen.ImprimirMatriz();
          }
          else
            cout << "La imagen " << pgm << " no ha podido ser cargada" << endl;
        }
        if (op == 2)
        {
          string b = parametros[1];
          char base[150];
          strcpy(base, b.c_str());
          int n_im = atoi(parametros[2].c_str());
          volumen.CargarVolumen(base, n_im, vol_cargado);
          if (vol_cargado)
          {
            cout << "El volumen " << b << " ha sido cargado" << endl;
            // volumen.ImprimirVolumen();
          }
          if (!vol_cargado)
            cout << "El volumen " << b << " no ha podido ser cargado" << endl;
        }
        if (op == 3)
        {
          if (img_cargada == true)
          {
            imagen.InfoImagen();
          }
          else
            cout << "No hay una imagen cargada en memoria" << endl;
        }
        if (op == 4)
        {
          if (vol_cargado == true)
          {
            volumen.InfoVolumen();
          }
          else
            cout << "No hay un volumen cargado en memoria" << endl;
        }
        if (op == 5)
        {
          if (vol_cargado)
          { // if volumen cargado
            pro_cargada = false;
            proyeccion.setDireccion(parametros[1]);
            proyeccion.setCriterio(parametros[2]);
            proyeccion.setArchivo(parametros[3]);
            proyeccion.crearProyeccion(volumen, pro_cargada);
            proyeccion.CrearArchivo();
            if (pro_cargada == true)
            {
              cout << "La proyección 2D del volumen en memoria ha sido generada"
                   << endl;
            }
            else
            {
              cout << "El volumen aún no ha sido cargado en memoria" << endl;
            }
          }
          else
            cout << "El volumen aun no ha sido cargado en memoria" << endl;
        }
        //
        if (op == 6)
        {
          // CODIFICACION
          cod_cargada = false;
          if (img_cargada == true)
          {
            codificar.setArchivo(parametros[1]);
            codificar.setImagen(imagen);
            codificar.CodificarImagen(cod_cargada);
            // codificar.ImprimirVector(); // Imprime Good
            bits = codificar.ObtenerBytes();
            if (cod_cargada)
            {
              cout << "La imagen en memoria ha sido codificada exitosamente"
                   << endl;
            }
          }
          else
          {
            cout << "No hay una imagen cargada en memoria" << endl;
          }
        }

        if (op == 7)
        {
          if (cod_cargada)
          {
            bool Decod = false;
            codificar.setNombreHuffmanDecod(parametros[1]);
            codificar.setNombreImgDecod(parametros[2]);
            Decod = codificar.DecodificarImagen();
            cout << "El archivo " << codificar.ObtenerNombreHuffmanDecod() << " ha sido decodificado exitosamente" << endl;
          }
          else
          {
            cout << "El archivo " << codificar.getNombreHufffmanDecod() << " no ha podido ser decodificado" << endl;
          }
        }

        if (op == 8)
        {
          if (img_cargada)
          {
            segmentar.setNombreImagen(parametros[1]);
            segmentar.getSemillas(parametros);
            //segmentar.MostrarInfoSemillas();
            img_segmentada= segmentar.segmentarImagen(imagen);

            if (img_segmentada)
            {
              cout << "La imagen en memoria fue segmentada correctamente y guardada en "<<segmentar.obtenerNombreImagen()<<endl;
            }else 
            {
              cout << "La imagen en memoria no pudo ser segmentada"<<endl;
            }
          }else
          {
            cout << "No hay una imagen cargada en memoria "<<endl;
          }
        }
      }
    }
    if (!existe)
      cout << "Comando/Parametros invalido" << endl;

  } while (comando_ingresado != "salir");
  cout << "^_^ Que tenga Feliz dia y muchas gracias por todo profe :)" << endl;
}