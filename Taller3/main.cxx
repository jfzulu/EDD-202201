#include <iostream>
#include "Control.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::string nombreArchivo = argv[1];
        Control ctrl;
        ctrl.LeerArchivo(nombreArchivo);
        set<int> s;
        list<int> l;
        list<int>::iterator itl;
        set<int>::iterator its;
        ctrl.LlenarArbol();
        ctrl.LlenarSet();
        cout << "\nEl tiempo del arbol AVL fue  : "<<ctrl.getTiempoAVL()<<endl;
        cout << "El tiempo del set (RN) fue     : "<<ctrl.getTiempoRN()<<endl;
        
        l= ctrl.getListaInOrder();
        s= ctrl.getSet();
        
        cout << "\nEl tamanyo del arbol fue     : "<< l.size()<<endl;
        cout << "El tamanyo d el set (RN) fue   : "<< s.size()<<endl;

        if (ctrl.isEqual())
        {
            cout << "El contenido en ambos es el mismo"<<endl;
        }else{
            cout << "No tienen el mismo contenido"<<endl;
        }
    }
    else
        cout<< "Error, parametros invalidos"<<endl;
}
