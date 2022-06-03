#ifndef _GRAFO_HXX_
#define _GRAFO_HXX_
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
typedef long long ll;

template <class T, class U>
class Grafo{
    protected:
        vector<T> vertices;
        vector< vector< pair<ll, U> > >aristas;
        ll numVertices;
    private:
        int CantidadVertices();
        int CantidadAristas();
        void InsertarVertice(T vertice);
        void InsertarArista(T origen, T destino, U peso);
        ll BuscarVertice(T vertice);
        ll BuscarArista(ll origen, ll destino);
        void EliminarVertice(T vertice);
        void EliminarArista(T origen, T destino);
        void RecorridoPlano();
        void ImprimirGrafo();
        void RecorridoDFS(T inicio);
        void RecorridoDFS(ll inicio, bool *visitados);
        void RecorridoBFS(T inicio);
};

#endif