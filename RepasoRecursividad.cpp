#include<iostream>

using namespace std;

void caminar(int pasos)
{

if(pasos>0){
cout<<"Caminando\n";
caminar(pasos-1);
    }
}

int main(){

caminar(20);

return 0;

 }
