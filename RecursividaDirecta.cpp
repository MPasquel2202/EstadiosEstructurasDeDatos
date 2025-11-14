#include <iostream>

using namespace std;

void contar (int n){

if (n==0)return;
cout<<n<<"";

contar (n-1);

}

int main(){

cout<<"Recursividad Directa:\n";
contar(5);
cout<<endl;
return 0;
}


