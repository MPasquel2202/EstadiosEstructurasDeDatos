#include<iostream>

using namespace std;

struct Nodo{

int info;
 Nodo *sig;
 Nodo *ant;

};

Nodo *ptr=NULL;

void insertar(int xinfo){
Nodo *nuevo = new Nodo();
nuevo->info=xinfo;
nuevo->sig=NULL;
nuevo->ant=NULL;
if(ptr == NULL){

ptr=nuevo;
}else{

Nodo *p=ptr;
while(p->sig != NULL){

p=p->sig;

}
p->sig=nuevo;
nuevo->ant=p;
}

}

void Mostrar(){

Nodo *p=ptr;
while(p != NULL){
cout<<p->info;
p=p->sig;

}
cout<<endl;
}

void liberarMemoria(){
    Nodo *p = ptr;
    while(p != NULL){
        Nodo *temp = p;
        p = p->sig;
        delete temp;
    }
    ptr = NULL;
}


int main(){

insertar(5);
insertar(4);
insertar(6);

Mostrar();

return 0;
}
