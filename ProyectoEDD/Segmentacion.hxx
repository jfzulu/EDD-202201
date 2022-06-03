#ifndef SEGMENTACION_HXX
#define SEGMENTACION_HXX

#include "Imagen.hxx"
#include "Semilla.hxx"

using namespace std;

class Segmentacion
{
private:
    int nSemillas;
    vector<Semilla> semillas;
    string nombreImagen;
    Imagen ImgSegmentada;
public:
    void getSemillas(vector<string> parametros);
    void pushSemilla(Semilla semilla);
    void MostrarInfoSemillas();
    void setNombreImagen(string n);
    string obtenerNombreImagen();
    bool segmentarImagen(Imagen img);
    int calcularDistancia( pair<int, int> inicial, pair<int, int> final);
    void crearArchivoImgSegmentada();
};

#endif