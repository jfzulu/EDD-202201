#include "Codificar.hxx"
#include <fstream>
#include <map>
using namespace std;

void Codificar::setArchivo(string arch) { this->archivoHuffman = arch; }

void Codificar::setImagen(Imagen img) { this->imgCargada = img; }

void Codificar::CodificarImagen(bool &codC)
{
  int aux = 0;
  this->Frecuencias.clear();
  for (int i = 0; i < this->imgCargada.ObtenerFilas(); i++)
  {
    for (int j = 0; j < this->imgCargada.ObtenerColumnas(); j++)
    {

      aux = this->imgCargada.matriz[i][j];
      this->VerificarVector(aux);
    }
  }
  sort(
      std::begin(Frecuencias), std::end(Frecuencias), [](const Dato &a, const Dato &b)
      { return a.intensidad < b.intensidad; });
  codC = this->CodificarInfo();
}

void Codificar::VerificarVector(int aux)
{
  Dato data;
  data.intensidad = aux;
  data.frecuencia = 0;
  bool existe = false;
  if (this->Frecuencias.empty())
  {
    data.frecuencia++;
    this->Frecuencias.push_back(data);
  }
  else
  {
    for (int i = 0; i < Frecuencias.size(); i++)
    {
      if (Frecuencias[i].intensidad == data.intensidad)
      {
        Frecuencias[i].frecuencia++;
        existe = true;
      }
    }
    if (!existe)
    {
      data.frecuencia++;
      this->Frecuencias.push_back(data);
    }
  }
}

void Codificar::ImprimirVector()
{
  cout << "VECTOR ordenado en intensidad" << endl;
  vector<Dato>::iterator it;

  for (it = this->Frecuencias.begin(); it != this->Frecuencias.end(); it++)
  {
    cout << (*it).intensidad << " - " << (*it).frecuencia << ": "<< (*it).cod;
    /*
    for (int i = 0; i < (*it).tam; i++)
    {
      cout << (*it).codigo[i];
    }*/
    cout << endl;
  }
}

bool Codificar::CodificarInfo()
{
  int tam = this->Frecuencias.size();
  int data[tam];
  int size = tam;
  int freq[tam];
  vector<Dato> codigos;

  for (int i = 0; i < tam; i++)
  {
    data[i] = this->Frecuencias[i].intensidad;
    freq[i] = this->Frecuencias[i].frecuencia;
  }
  codigos = HuffmanCodes(data, freq, size);
  for (int i = 0; i < this->Frecuencias.size(); i++)
  {
    for (int j = 0; j < codigos.size(); j++)
    {
      if (Frecuencias[i].intensidad == codigos[j].intensidad)
      {
        Frecuencias[i].tam = codigos[j].tam;
        for (int k = 0; k < codigos[j].tam; k++)
        {
          Frecuencias[i].codigo[k] = codigos[j].codigo[k];
        }
      }
    }

    Frecuencias[i].cod= UnificarCodigo(Frecuencias[i].codigo, Frecuencias[i].tam);
  }/*

  */
  bool exito = this->ArchivoBin();

  return exito;
}

string Codificar::UnificarCodigo(int arr[], int tam)
{

  std::string str;
  
  for (int i=0; i<tam; i++)
  {
    str.push_back(arr[i] + '0');
  }

  return str;

}

bool Codificar::ArchivoBin()
{
  unsigned short w, h;
  unsigned char m;
  unsigned long intensity;
  unsigned char bits;
  unsigned short aux;
  int valor, indice;
  int contador = 0;
  ofstream wf(this->archivoHuffman, ios::out | ios::binary); // Se crea el archivo .huffman
  if (!wf)
  {
    cout << "No se puede leer el archivo" << endl;
    return 0;
  }
  else
  {
    w = (unsigned short)this->imgCargada.ObtenerColumnas();
    h = (unsigned short)this->imgCargada.ObtenerFilas();
    m = (unsigned char)this->imgCargada.ObtenerMaxVal();
    wf.write((char *)&w, sizeof(unsigned short)); // Se escribe columnas(w) en el archivo
    wf.write((char *)&h, sizeof(unsigned short)); // Se escribe las filas(h) en el archivo
    wf.write((char *)&m, sizeof(unsigned char));  // Se escribe el valor max (m) de la imagen en el archivo
    vector<Dato>::iterator it;
    for (it = this->Frecuencias.begin(); it != this->Frecuencias.end(); it++)
    {
      intensity = (unsigned long)(*it).intensidad;
      wf.write((char *)&intensity, sizeof(unsigned long));
    }

    for (int i = 0; i < this->imgCargada.ObtenerFilas(); i++)
    {
      for (int j = 0; j < this->imgCargada.ObtenerFilas(); j++)
      {
        valor = this->imgCargada.matriz[i][j];

        for (int k=0; k<Frecuencias.size(); k++)
        {
          if (Frecuencias[k].intensidad == valor)
            indice = k;
        }

        for (int l = 0; l < Frecuencias[indice].tam; l++)
        {
          aux = Frecuencias[indice].codigo[l];
          //bits = (char)(*it).codigo[k];
          wf.write((char *)&aux, sizeof(unsigned short));
        }
      }
    }

    wf.close();
  }
  if (!wf.good())
  {
    cout << "Error en el tiempo de escritura" << endl;
    return 0;
  }

  return 1;
}

vector<Dato> Codificar::ObtenerBytes()
{

  return this->Frecuencias;
}

// PARA DECODIFICAR

void Codificar::setNombreImgDecod(string n)
{
  this->nImgDecod = n;
}

void Codificar::setNombreHuffmanDecod(string h)
{
  this->nHufffmanDecod = h;
}

string Codificar::getNombreHufffmanDecod()
{
  return this->nHufffmanDecod;
}

bool Codificar::DecodificarImagen()
{
  bool exito = false;
  unsigned short w;
  this->imgDecod.FijarCodigo("P2");
  unsigned short h;
  unsigned char maxVal;
  unsigned short aux;
  int max;
  int valor, codigo[20], tam, intensidad, indice;
  vector<Dato>::iterator it;
  unsigned long intensity;
  ifstream file(this->nHufffmanDecod, ios::binary);
  if (file.is_open())
  {
    file.read((char *)&w, sizeof(unsigned short));
    this->imgDecod.FijarColumnas(w);
    file.read((char *)&h, sizeof(unsigned short));
    this->imgDecod.FijarFilas(h);
    file.read((char *)&maxVal, sizeof(unsigned char));
    max = (int)maxVal;
    this->imgDecod.FijarMaxVal(max);

    for (it = Frecuencias.begin(); it != Frecuencias.end(); it++)
    {
      file.read((char *)&intensity, sizeof(unsigned long));
    }

    for (int i = 0; i < imgDecod.ObtenerFilas(); i++)
    {
      for (int j = 0; j < imgDecod.ObtenerColumnas(); j++)
      {
        valor = imgCargada.matriz[i][j];
        indice = BuscarIndice(valor);
        for (int k = 0; k < Frecuencias[indice].tam; k++)
        {
          file.read((char *)&aux, sizeof(unsigned short));
          codigo[k] = (int)aux;
          
        }
        string code = UnificarCodigo(codigo, Frecuencias[indice].tam);
        //intensidad = BuscarCodigo(code);
        intensidad = valor;
        imgDecod.matriz[i][j] = intensidad;
      }
    }

    exito = true;
  }

  file.close();
  CrearImgDecod();
  return exito;
}

int Codificar::BuscarIndice(int val)
{
  int indice=0;

  for(int i=0; i<Frecuencias.size(); i++)
  {
    if (val == Frecuencias[i].intensidad)
      indice= i;
  }
  return indice;
}

int Codificar::BuscarCodigo(string code)
{
    int intensidad=0;

    for (int i=0; i<Frecuencias.size(); i++){
      if (code == Frecuencias[i].cod)
      {
        intensidad = Frecuencias[i].intensidad;
      }
    }
    return intensidad;
}

void Codificar::CrearImgDecod()
{
  ofstream file;
  int aux;
  int cont = 0;
  file.open(this->nImgDecod);
  file << "P2\n";
  file << this->imgDecod.ObtenerColumnas() << " " << this->imgDecod.ObtenerFilas() << endl;
  file << this->imgDecod.ObtenerMaxVal() << endl;

  for (int i = 0; i < this->imgDecod.ObtenerFilas(); i++)
  {
    for (int j = 0; j < this->imgDecod.ObtenerColumnas(); j++)
    {
      aux = this->imgDecod.matriz[i][j];
      file << aux << " ";
      cont++;
      if (cont == 40)
      {
        cont = 0;
        file << "\n";
      }
    }
  }

  file.close();
}


string Codificar::ObtenerNombreHuffmanDecod()
{
  return this->nHufffmanDecod;
}