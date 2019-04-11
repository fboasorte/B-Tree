#include <iostream>
#include <cstdio>
#include <cstring>
#include "arvoreB.h"

using namespace std;

int t;

void Leitura(arvoreB<int> &arvore) {
    int valor;
    Nodo<int> *no = new Nodo<int>(2 * t);
    char linha[30], comando[20];
    cout << "---------------Digite os comandos---------------" << endl;
    cout << "Comando: ";
    getchar();
    while(scanf("%[^\n]s\n", linha) == 1) {
        sscanf(linha, "%s %d", comando, &valor);
        if(strcmp(comando, "insere") == 0){
            arvore.Insere(valor);
        }
        else if(strcmp(comando, "busca") == 0) {
            no = arvore.Busca(valor);
            if(no == NULL){
                cout << "ERROR: A arvore eh NULA!!!" << endl;
            } 
            else{
                int i;
                for(i = 0; i < no -> Get_Quant_Chave(); i++) {
                    if(no -> Get_Chave(i) == valor) {
                        cout << "Posicao: " << i << endl;
                        cout << "Valor: " << valor << endl;
                        break;
                    }
                }
                if(i == no -> Get_Quant_Chave())
                    cout << "Nao tem esse valor na arvore!!!" << endl;
            }
        } 
        else if(strcmp(comando, "imprime_arvore") == 0) {
            arvore.Imprime();
        } 
        else
            cout << "Comando invalido" << endl;
        Leitura(arvore);
    }
}

int main() {
    cout<<"Digite o parametro t"<<endl;
    cin>>t;
    cout << "------------------Documentacao------------------" << endl;
    cout << "Para inserir digite - 'insere' e o valor " << endl;
    cout << "Para buscar digite - 'busca' e o valor " << endl;
    cout << "Para imprimir a arvore digite - 'imprime_arvore'" << endl;
    cout << "------------------------------------------------" << endl << endl;
    arvoreB<int> arvore(t);
    Leitura(arvore);
    return 0;
}