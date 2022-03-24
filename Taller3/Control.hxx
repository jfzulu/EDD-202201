#include "Control.h"
#include <fstream>
#include <ctime>
#include <math.h>
#include <algorithm>
// Funcion que lee archivo y lo carga a una lista de cadenas
void Control::LeerArchivo(string nombreArchivo)
{
    fstream myFile(nombreArchivo); // Se abre el archivo
    string line;                   // Cadena donde se almacena una linea del archivo
    if (myFile.is_open())
    {                                 // Si se abrió el archivo...
        while (getline(myFile, line)) // Mientras que lea lineas del archivo
        {
            this->lista.push_back(line); // Inserte en la lista de cadenas la cadena leida
        }
    }
    else
    {
        cout << "\nError al leer archivo\n";
    }
}

// Funcion que llena el arbol AVL con la informacion de la lista de cadenas
void Control::LlenarArbol()
{
    if (!this->lista.empty()) // Si la lista no esta vacia
    {
        clock_t init_time = clock(); // Unidad de tiempo inicial
        int mayor = 0;
        list<string>::iterator it;                        // Iterador para la lista de cadenas donde esta almacenada la informacion del archivo
        for (it = lista.begin(); it != lista.end(); it++) // Ciclo que recorre toda la lista de cadenas
        {
            if ((*it)[0] == 'A' || (*it)[0] == 'a') // Si en primer caracter, posicion 0 de la cadena es 'A' o 'a'
            {
                codigo = atoi((*it).substr(1, 7).c_str()); // Convierta la cadena de la posicion 1 a 7, el codigo, a entero
                avl.insertar(codigo);                      // Inserte el codigo al arbol AVL
            }
            else
            {
                if (!avl.esVacio())
                {
                    avl.valorMax(mayor);
                    avl.eliminar(mayor);
                }
            }
        }
        clock_t end_time = clock(); // Unidad de tiempo final
        this->LlenarInOrderLista();
        this->tiempoAVL = (end_time - init_time) / double(CLOCKS_PER_SEC);
    }
}

void Control::LlenarSet()
{
    if (!this->lista.empty())
    {
        clock_t init_time = clock();
        list<string>::iterator it;
        set<int>::reverse_iterator its;
        for (it = lista.begin(); it != lista.end(); it++)
        {
            if ((*it)[0] == 'A' || (*it)[0] == 'a')
            {
                codigo = atoi((*it).substr(1, 7).c_str());
                rn.insert(codigo);
            }
            else
            {
                if (!rn.empty())
                {
                    its = rn.rbegin();
                    rn.erase(*its);
                }
            }
        }
        clock_t end_time = clock();
        this->tiempoRN = (end_time - init_time) / double(CLOCKS_PER_SEC);
    }
}
void Control::LlenarInOrderLista()
{
    if (!avl.esVacio())
    {
        avl.inOrdenL(this->inOrderList);
    }
}

bool Control::isEqual()
{
    list<int>::iterator it = inOrderList.begin();
    set<int>::iterator its = rn.begin();

    if (inOrderList.size() == rn.size())
    {
        for (; it != inOrderList.end(); it++, its++)
        {
            if (*it != *its)
                return false;
        }
        return true;
    }
    return false;
}

list<int> Control::getListaInOrder()
{
    return this->inOrderList;
}

set<int> Control::getSet(){
    return this->rn;
}

double Control::getTiempoAVL()
{
    return this->tiempoAVL;
}

double Control::getTiempoRN()
{
    return this->tiempoRN;
}