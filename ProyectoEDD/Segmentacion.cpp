#include "Segmentacion.hxx"

void Segmentacion::getSemillas(vector<string> parametros)
{
    int n_semillas = (parametros.size() - 2) / 3;
    this->nSemillas = n_semillas;
    Semilla aux;
    int cont = 0;
    for (int i = 2; i < parametros.size(); i++)
    {
        int dato = stoi(parametros[i]);
        if (cont == 0)
        {
            aux.SetFila(dato);
        }
        if (cont == 1)
        {
            aux.SetColumna(dato);
        }
        if (cont == 2)
        {
            aux.SetIntensidad(dato);
        }
        cont++;
        if (cont == 3)
        {
            cont = 0;
            this->semillas.push_back(aux);
        }
    }
    cout << "Se recibieron " << n_semillas << " semillas" << endl;
}

void Segmentacion::pushSemilla(Semilla semilla)
{
    this->semillas.push_back(semilla);
}

void Segmentacion::MostrarInfoSemillas()
{
    cout << "Nombre de imagen: " << this->nombreImagen;
    for (int i = 0; i < this->semillas.size(); i++)
    {
        cout << "\tSemilla " << i + 1 << endl;
        cout << "\tX: " << semillas[i].ObtenerFila() << endl;
        cout << "\tY: " << semillas[i].ObtenerColumna() << endl;
        cout << "\tL: " << semillas[i].ObtenerIntesidad() << endl;
        cout << "\n";
    }
}

void Segmentacion::setNombreImagen(string n)
{
    this->nombreImagen = n;
}

string Segmentacion::obtenerNombreImagen()
{
    return this->nombreImagen;
}

bool Segmentacion::segmentarImagen(Imagen img)
{
    bool exito = true;
    int tamColImg = img.ObtenerColumnas();
    int tamFilImg = img.ObtenerFilas();
    int maxValImg = img.ObtenerMaxVal();
    this->ImgSegmentada.FijarCodigo("P2");
    this->ImgSegmentada.FijarColumnas(tamColImg);
    this->ImgSegmentada.FijarFilas(tamFilImg);
    this->ImgSegmentada.FijarMaxVal(maxValImg);
    bool matrizVisitados[tamFilImg][tamColImg];
    int matrizDistancia[tamFilImg][tamColImg];

    // SE INICIALIZA VALORES DE MATRICES
    for (int i = 0; i < this->ImgSegmentada.ObtenerFilas(); i++)
    {
        for (int j = 0; j < this->ImgSegmentada.ObtenerColumnas(); j++)
        {
            this->ImgSegmentada.matriz[i][j] = img.matriz[i][j];
            matrizVisitados[i][j] = false;
            matrizDistancia[i][j] = 255;
        }
    }

    queue<Semilla> queue;
    for (int i = 0; i < semillas.size(); i++)
    {
        queue.push(semillas[i]);
    }

    vector<pair<int, int>> vecinos;
    pair<int, int> aux;
    aux.first = -1;
    aux.second = 0;
    vecinos.push_back(aux);
    aux.first = 0;
    aux.second = -1;
    vecinos.push_back(aux);
    aux.first = 1;
    aux.second = 0;
    vecinos.push_back(aux);
    aux.first = 0;
    aux.second = 1;
    vecinos.push_back(aux);

    while (!queue.empty())
    {
        Semilla actual = queue.front();
        queue.pop();
        pair<int, int> pairActual(actual.ObtenerFila(), actual.ObtenerColumna());

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> vecinoActual((pairActual.first + vecinos[i].first), (pairActual.second + vecinos[i].second));
            if (vecinoActual.first < 0 || vecinoActual.first > tamFilImg - 1 ||
                vecinoActual.second < 0 || vecinoActual.second > tamColImg - 1)
            {
                //NO hace nada , fuera de rango
            }else
            {
                if ( !matrizVisitados[vecinoActual.first][vecinoActual.second] || 
                matrizDistancia[vecinoActual.first][vecinoActual.second]> calcularDistancia(pairActual, vecinoActual))
                {
                    matrizVisitados[vecinoActual.first][vecinoActual.second]=true;
                    matrizDistancia[vecinoActual.first][vecinoActual.second]=calcularDistancia(pairActual, vecinoActual);
                    ImgSegmentada.matriz[vecinoActual.first][vecinoActual.second]= actual.ObtenerIntesidad();
                    Semilla nueva;
                    nueva.SetFila(vecinoActual.first);
                    nueva.SetColumna(vecinoActual.second);
                    nueva.SetIntensidad(actual.ObtenerIntesidad());
                    queue.push(nueva);
                }
            }
        }
    }

    crearArchivoImgSegmentada();
    exito=true;

    this->semillas.clear();
    return exito;
}


int Segmentacion::calcularDistancia(pair<int, int> inicial, pair<int, int> final)
{
    int diff=0;
    int intensidadInicial;
    int intensidadFinal;
    intensidadInicial= ImgSegmentada.matriz[inicial.second][inicial.first];
    intensidadFinal= ImgSegmentada.matriz[final.second][inicial.first];
    diff = intensidadFinal-intensidadInicial;
    return diff;
}

void Segmentacion::crearArchivoImgSegmentada(){
    ofstream file;
    int aux=0;
    int cont=0;
    file.open(this->nombreImagen);
    file << "P2\n";
    file << this->ImgSegmentada.ObtenerColumnas()<<" "<<this->ImgSegmentada.ObtenerFilas()<<endl;
    file << this->ImgSegmentada.ObtenerMaxVal()<<endl;

     for (int i=0; i<this->ImgSegmentada.ObtenerFilas(); i++)
    {
      for (int j=0; j<this->ImgSegmentada.ObtenerColumnas(); j++)
        {
            aux= this->ImgSegmentada.matriz[i][j];
            file << aux<<" ";
            cont++;
            if (cont==40)
            {
                cont=0;
                file<< "\n";
            }
        }
    } 

    file.close();
}