#include "Comando.hxx"
#include "Imagen.hxx"
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

void Comando::CargarComandos(vector<Comando> &c)
{
  Comando cmd_aux;
  // Cargar Comando 1
  cmd_aux.cmd = "cargar_imagen";
  cmd_aux.n_para = 2;
  cmd_aux.ayuda =
      "FORMATO: cargar_imagen 'imagen.pgm'; \n\t\tFUNCION: El comando carga en "
      "memoria la imagen identificada con el nombre_imagen.pgm";
  c.push_back(cmd_aux);

  // Comando 2: Cargar Volumen
  cmd_aux.cmd = "cargar_volumen";
  cmd_aux.n_para = 3;
  cmd_aux.ayuda =
      "FORMATO: cargar_volumen 'nombre_base' n_im; \n\t\tFUNCION: El comando "
      "carga en memoria la serie ordenada de imágenes identificada con el "
      "nombre_base y cuyo tamaño corresponde a n_im imágenes (la serie podrá "
      "tener máximo 99 imágenes). Todas las imágenes de la serie deben estar "
      "nombradas como nombre_basexx.pgm, donde xx corresponde a dos dígitos de "
      "identificación de la posición de la imagen en la serie (varía en el "
      "rango 01 - n_im ).";
  c.push_back(cmd_aux);

  // Comando 3: Info Imagen
  cmd_aux.cmd = "info_imagen";
  cmd_aux.n_para = 1;
  cmd_aux.ayuda =
      "FORMATO: info_imagen; \n\t\tFUNCION: El comando muestra en pantalla la "
      "información básica de la imagen actualmente cargada en memoria";
  c.push_back(cmd_aux);

  // Comando 4: Info Volumen
  cmd_aux.cmd = "info_volumen";
  cmd_aux.n_para = 1;
  cmd_aux.ayuda = "FORMATO: info_volumen; \n\t\tFUNCION: El comando muestra en "
                  "pantalla la informacion basica de la serie de "
                  "imagenes(volumen) cargadas en memoria actualmente";
  c.push_back(cmd_aux);

  // Comando 5: Proyeccion 2D
  cmd_aux.cmd = "proyeccion2D";
  cmd_aux.n_para = 4;
  cmd_aux.ayuda =
      "FORMATO: proyeccion2D *direccion* *criterio* 'nombre_archivo.pgm'; "
      "\n\t\tFUNCION: El comando toma la serie ordenada de imagenes cargadas "
      "en memoria y de acuerdo a una direccion especifica dada, recorre la "
      "posicion del plano en esta posicion, generando un valor de resultante "
      "de cada posicion";
  c.push_back(cmd_aux);

  // Comando 6:
  cmd_aux.cmd = "codificar_imagen";
  cmd_aux.n_para = 2;
  cmd_aux.ayuda =
      "FORMATO: codificar_imagen *nombre_archivo.huffman*; \n\t\tComando que genera el archivo de texto con la correspondiente codificacion de Huffman para la imagen que se encuentra actualmente cargada en memoria, almanacenandolo en disco bajo el nombre *nombre_archivo.huffman*";
  c.push_back(cmd_aux);

  // Comando 7
  cmd_aux.cmd = "decodificar_archivo";
  cmd_aux.n_para = 3;
  cmd_aux.ayuda =
      "FORMATO: decodificar_archivo *nombre_archivo.huffman* *nombre_imagen.pgm*; \n\t\tComando que carga en memoria la información de codificación contenida en el archivo *nombre_archivo.huffman* y luego genera la correspondiente imagen decodificada en formato PGM, almacenandola en disco bajo el nombre *nombre_imagen.pgm*";
  c.push_back(cmd_aux);

  // Comando 8
  cmd_aux.cmd = "segmentar";
  cmd_aux.n_para = 17;
  cmd_aux.ayuda = "FORMATO: segmentar *salida_imagen.pgm* *sx1* *sy1* *sl1* *sx2* *sy2* *sl2* ...; \n\t\tComando que carga en memoria la informacion del conjunto de semillas correspondientes a la imagen cargada en memoria, para luego realizar la segmentacion, la imagen con las etiquetas quedan cargada en *salida_imagen.pgm* ";
  c.push_back(cmd_aux);

  // COMANDO AYUDA: AYUDA
  cmd_aux.cmd = "ayuda";
  cmd_aux.n_para = 1;
  cmd_aux.ayuda = "FORMATO: ayuda;\n\t\tComando que proporciona informacion de "
                  "los comandos, ayuda al usuario";
  c.push_back(cmd_aux);

  cmd_aux.cmd = "ayuda";
  cmd_aux.n_para = 2;
  cmd_aux.ayuda =
      "FORMATO: ayuda *comando*;\n\t\tFUNCION: Comando que proporciona "
      "informacion de un comando en especifico, ayuda al usuario";
  c.push_back(cmd_aux);

  // COMANDO AYUDA
  cmd_aux.cmd = "salir";
  cmd_aux.n_para = 1;
  cmd_aux.ayuda =
      "FORMATO: exit; \n\t\tFUNCION: Comando que finaliza, termina el programa";
  c.push_back(cmd_aux);
}

vector<string> Comando::Dividir(string str, char pattern, int &cont)
{
  int posInit = 0;
  int posFound = 0;
  string splitted;
  vector<string> results;

  while (posFound >= 0)
  {
    posFound = str.find(pattern, posInit);
    splitted = str.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
    cont++;
  }

  return results;
}

bool Comando::ValidarComando(int contP, vector<string> parametros,
                             vector<Comando> c)
{
  string cmd = parametros[0];
  bool ext = false;

  for (int i = 0; i < c.size(); i++)
  {
    if (cmd == c[i].cmd && parametros.size() <= c[i].n_para)
    {
      ext = true;
      break;
    }
  }
  return ext;
}

int Comando::EjecutarComando(vector<string> parametros, vector<Comando> c,
                             int cantP)
{
  string cmd = parametros[0]; // Se guarda el comando ingresado
  string format = "pgm";      // Formato recibido de imagen
  string format2 = "huffman";
  int pos = 0; // Posicion del comando en la lista de comandos
  Imagen a{};
  int tam_p = 0; // Tamaño de parametro
  for (int i = 0; i < c.size(); i++)
  {
    if (cmd == c[i].cmd)
      pos = i;
  }

  if (cmd == "cargar_imagen")
  {
    string prm = parametros[1];
    tam_p = prm.size();
    string fp = prm.substr(tam_p - 3, tam_p);
    if (fp == format)
    {
      cout << "Formato valido" << endl;
      return 1;
    }
    else
    {
      cout << "Parametro no valido, Formato no valido" << endl;
      return -1;
    }
  }

  if (cmd == "cargar_volumen")
  {
    string nombreB = parametros[1];
    int baseMax = atoi(parametros[2].c_str());
    if (baseMax > 99)
      return -1;

    return 2;
  }

  if (cmd == "info_imagen")
  {
    return 3;
  }

  if (cmd == "info_volumen")
  {
    return 4;
  }

  if (cmd == "proyeccion2D")
  {
    string prm = parametros[3];
    string direccion = parametros[1];
    string criterio = parametros[2];
    tam_p = prm.size();
    if (tam_p < 4)
    {
      cout << "Formato de archivo no valido" << endl;
      return -1;
    }
    string fp = prm.substr(tam_p - 3, tam_p);
    if (fp == format &&
        (direccion == "x" || direccion == "y" || direccion == "z" ||
         direccion == "X" || direccion == "Y" || direccion == "Z") &&
        (criterio == "maximo" || criterio == "minimo" ||
         criterio == "promedio" || criterio == "mediana"))
    {
      cout << "Formato valido" << endl;
      return 5;
    }
    else
    {
      cout << "Parametro no valido, Formato no valido" << endl;
      return -1;
    }
  }

  if (cmd == "codificar_imagen")
  {
    string prm = parametros[1];
    tam_p = prm.size();
    if (tam_p < 8)
    {
      cout << "Formato de archivo no valido" << endl;
      return -1;
    }
    string fp = prm.substr(tam_p - 7, tam_p);
    if (fp == format2)
    {
      cout << "Formato valido" << endl;
      return 6;
    }
    else
    {
      cout << "Parametro no valido, Formato no valido" << endl;
      return -1;
    }
  }

  if (cmd == "decodificar_archivo")
  {
    string huf = parametros[1];
    string pgm = parametros[2];
    int tam_h = huf.size();
    int tam_p = pgm.size();
    if (tam_h < 8 || tam_p < 4)
    {
      cout << "Formato de archivo no valido" << endl;
      return -1;
    }
    string fh = huf.substr(tam_h - 7, tam_h);
    string fp = pgm.substr(tam_p - 3, tam_p);
    if (fh == format2 && fp == format)
    {
      cout << "Formato Valido" << endl;
      return 7;
    }
    else
    {
      cout << "Parametro no valido, Formato no valido" << endl;
      return -1;
    }
  }



  if (cmd == "segmentar")
  {
    string pgm = parametros[1];
    int tam_p= pgm.size();
    if (tam_p <4)
    {
      cout << "Formato de archivo no valido"<<endl;
      return -1;
    }

    string fp = pgm.substr(tam_p - 3, tam_p);
    if (fp == format)
    {
      cout << "Formato Valido"<<endl;
      return 8;
    }
    else
    {
      cout << "Parametro no valido, Formato no valido"<<endl;
      return -1;
    }

  }




  if (parametros.size() == 1 && cmd == "ayuda")
  {
    cout << "Lista de comandos" << endl;
    for (int i = 0; i < c.size(); i++)
    {
      cout << "\t-" << c[i].cmd << endl;
    }

    return 0;
  }

  if (cmd == "ayuda")
  {
    bool ex = false;
    string cmda = parametros[1];
    for (int i = 0; i < c.size(); i++)
    {
      if (cmda == c[i].cmd)
      {
        cout << "Comando: " << c[i].cmd << endl;
        cout << c[i].ayuda << endl;
        ex = true;
      }
    }
    if (ex != true)
    {
      cout << "Parametro no encontrado. Ingrese 'ayuda' para lista de comandos"
           << endl;
      return -1;
    }
    return 0;
  }

  return 0;
}