#include <iostream>
#include <cstdio>
#include <cstring>
#include "arvoreB.h"

using namespace std;

void Leitura(arvoreB arvore){
    int valor;
    char linha[30], comando[20];
    while(scanf("%[^\n]%s\n", linha)){
        sscanf(linha, "%s %d", comando, valor);
        if(strcmp(comando, "insere"))
            arvore.Insere(valor);
        else if(strcmp(comando, "busca"))
            arvore.Busca(valor);
        else if(strcmp(comando, "imprime_arvore")){

        }
        else
            cout<<"Comando invalido"<<endl;
    }

}

int main(){
    int t;
    cout<<"Digite o parametro t"<<endl;
    cin>>t;
    arvoreB<int> arvore(t);
    arvore.Insere(5);
    return 0;
}
