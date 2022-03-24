#ifndef __CONTROL__H__
#define __CONTROL__H__

#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <list>
#include <algorithm>
#include "ArbolAVL.h"
using namespace std;


class Control
{
    private:
        std::list < std::string > lista;
        ArbolAVL <int> avl;
        set<int> rn;
        list<int> inOrderList;
        int codigo;
        double tiempoRN = 0;
        double tiempoAVL=0;
    public:
        void LeerArchivo (std::string nombreArchivo);
        std::list< int > getListaInOrder();
        void LlenarArbol();
        void LlenarSet();
        void LlenarInOrderLista();
        double getTiempoAVL();
        double getTiempoRN();
        set<int> getSet();
        bool isEqual();
};

#include "Control.hxx"
#endif