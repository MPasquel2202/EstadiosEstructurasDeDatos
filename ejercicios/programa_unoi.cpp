#include <iostream>
#include<cstdio>
using namespace std;

int main ()  {

    int a= 5;
    int *p,**q;
    p=&a;
    q=&p;

    printf("el valor de a por medio de p %\n", p);
    printf("La diraccion de a por medio de  %\n", p);

    printf("el valor de a por medio de q %\n", **q);
    printf("el direccion de a por medio de q %\n", *q);
    printf("el direccion de p %p\n", &p);
    printf("el direccion p por medio de q %p\n", q);
    printf("el direccion a por demiod de q %p\n", *q);
    printf("--- %p\n",**q);

    return 0;
}