#include <iostream>
#include "arvoreB.h"

using namespace std;

int main(){
    int t;
    cout<<"Digite o parametro t"<<endl;
    cin>>t;
    arvoreB<int> arvore(t);
    arvore.Insere(5);
    return 0;
}
