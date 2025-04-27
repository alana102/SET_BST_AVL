#include<iostream>
#include "Set.hpp"
using namespace std;

int main(){

    Set *conjunto = new Set();

    conjunto->insert(4);
    conjunto->insert(6);
    conjunto->insert(1);
    conjunto->insert(9);
    conjunto->insert(7);
    conjunto->insert(0);
    conjunto->insert(3);


    int no = 0;
    cin >> no;
    cout << "Sucessor de " << no << ": " << conjunto->successor(no) << endl;

    cout << "Tamanho do conjunto: " << conjunto->size() << endl;
    cout << "Altura do no " << no << ": " << conjunto->height(no) << endl;
    cout << "Altura total: " << conjunto->total_height() << endl;
    cout << "Menor elemento: " << conjunto->minimum() << endl;
    cout << "Maior elemento: " << conjunto->maximum() << endl;
   

    if(conjunto->empty()){
        cout << "Conjunto esta vazio" << endl;
    } else {
        cout << "Conjunto possui " << conjunto->size() << " elementos" << endl;
    }

    conjunto->show();
    conjunto->printInfix();

    delete conjunto;

}