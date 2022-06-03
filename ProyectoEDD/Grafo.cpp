#include "Grafo.hxx"
#include <iostream>

template <class T, class U>
int Grafo<T, U>::CantidadVertices()
{
    return this->numVertices;
}

template <class T, class U>
int Grafo<T, U>::CantidadAristas()
{
    int total = 0;
    vector<pair<long, U>> temp;

    for (int i = 0; i < this->aristas.size(); i++)
    {
        temp = aristas[i];
        total = total + temp.size();
    }

    return total;
}

template <class T, class U>
void Grafo<T, U>::InsertarVertice(T vertice)
{
    if (numVertices == 0 || BuscarVertice(vertice) == -1)
    {
        this->vertices.push_back(vertice);
        vector<pair<ll, U>> aux;
        this->aristas.push_back(aux);
        numVertices = this->vertices.size();
    }
}

template <class T, class U>
void Grafo<T, U>::InsertarArista(T origen, T destino, U peso)
{
    ll ori= BuscarVertice(origen);
    ll des= BuscarVertice(destino);

    if ( ori != -1 && des != -1)
    {
        if (BuscarArista(ori, des) == -1)
        {
            vector< pair< ll, U>> *aux = &aristas[ori];
            pair<ll, U> nAri(des, peso);
            aux->push_back(nAri);
        }
    }
}

template <class T, class U>
ll Grafo<T, U>::BuscarVertice(T vertice)
{
    ll indice = -1;
    for (int i=0; i<numVertices && indice == -1; i++)
    {
        if (vertice == vertices[i])
            indice=i;

    }

    return indice;
}

template <class T, class U>
ll Grafo<T, U>::BuscarArista(ll origen, ll destino)
{
    ll encontrado = -1;
    vector<pair<ll, U>> aux = aristas[origen];
    for (int i = 0; i < aux.size() && encontrado == -1; i++)
    {
        pair<ll, U> temp = aux[i];
        if (temp.first == destino)
            encontrado = i;
    }
    return encontrado;
}

template <class T, class C>
void Grafo<T, C>::EliminarVertice(T vertice)
{
    ll ver = BuscarVertice(vertice);
    if (ver != -1)
    {
        vector<pair<ll, C>> *aux = &aristas[ver];
        aux->clear();
        aristas.erase(aristas.begin() + ver);
        for (int i = 0; i < aristas.size(); i++)
        {
            aux = &aristas[i];
            for (int j = 0; j < aux->size(); j++)
            {
                pair<ll, C> temp = (*aux)[j];
                if (temp.first == ver)
                {
                    aux->erase(aux->begin() + j);
                }
            }
            // eliminarArista(vertice,vertices[i]);
        }
        vertices.erase(vertices.begin() + ver);
        numVertices = vertices.size();
    }
}

template <class T, class C>
void Grafo<T, C>::EliminarArista(T origen, T destino)
{
    ll ori = BuscarVertice(origen);
    ll des = BuscarVertice(destino);
    if (ori != -1 && des != -1)
    {

        ll ariIn = BuscarArista(ori, des);
        if (ariIn != -1)
        {
            vector<pair<ll, C>> *aux = &aristas[ori];
            aux->erase(aux->begin() + ariIn);
        }
    }
}
template <class T, class C>
void Grafo<T, C>::RecorridoPlano()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i] << ", ";
    }
    cout << endl;
}
template <class T, class C>
void Grafo<T, C>::ImprimirGrafo()
{
    cout << endl;
    for (int i = 0; i < vertices.size(); ++i)
    {
        cout << vertices[i] << "-> ";
        vector<pair<ll, C>> aux = aristas[i];
        for (int j = 0; j < aux.size(); j++)
        {
            pair<ll, C> temp = aux[j];
            cout << vertices[temp.first] << " " << temp.first << " " << temp.second << ", ";
        }
        cout << endl;
    }
    cout << endl;
}
template <class T, class C>
void Grafo<T, C>::RecorridoDFS(T inicio)
{
    bool visitados[vertices.size()] = {0};
    ll in = BuscarVertice(inicio);
    if (in != -1)
        recorridoDFS(in, visitados);
    else
        cout << "El dato no existe" << endl;
}
template <class T, class C>
void Grafo<T, C>::RecorridoDFS(ll nodo, bool *visitados)
{
    visitados[nodo] = true;
    cout << vertices[nodo] << ", ";
    vector<pair<ll, C>> aux = aristas[nodo];
    for (int i = 0; i < aux.size(); ++i)
    {
        pair<ll, C> temp = aux[i];
        if (!visitados[temp.first])
            RecorridoDFS(temp.first, visitados);
    }
}
template <class T, class C>
void Grafo<T, C>::RecorridoBFS(T inicio)
{
    bool visitados[vertices.size()] = {0};
    ll nodo = BuscarVertice(inicio);
    queue<ll> colaV;
    colaV.push(nodo);
    if (nodo != -1)
    {
        while (!colaV.empty())
        {
            nodo = colaV.front();
            colaV.pop();

            if (!visitados[nodo])
            {
                cout << vertices[nodo] << ", ";
                visitados[nodo] = true;
                vector<pair<ll, C>> aux = aristas[nodo];
                for (int i = 0; i < aux.size(); ++i)
                {
                    pair<ll, C> temp = aux[i];
                    colaV.push(temp.first);
                }
            }
        }
    }
    else
        cout << "El dato no existe" << endl;
}