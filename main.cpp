/*
Instituto Federal do Norte de Minas Gerais - Campus Montes Claros
Laboratório 2   Entrega: 15/04/2019

Discentes: André Vinícius Mendes Barros e Felipe Rocha Boa-Sorte
Disciplina: Algoritmos e Estrutura de Dados III
Docente: Alberto Miranda
Ambiente: Ubuntu 18.04.1 LTS
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include "arvoreB.h"

using namespace std;

int t;
/*
Leitura: Função para ler os comandos do usuário e chamar as devidas funções 
Retorno: sem retorno
*/
template <class TIPO>
void Leitura(arvoreB<TIPO> &arvore) {
    TIPO valor;
    char linha[30], comando[20];
    getchar();
    while(scanf("%[^\n]s\n", linha) == 1) {
        Nodo<TIPO> *no = new Nodo<TIPO>(2 * t);
        sscanf(linha, "%s %d", comando, &valor);
        if(strcmp(comando, "insere") == 0){
            arvore.Insere(valor);
            Leitura(arvore);
        }
        else if(strcmp(comando, "busca") == 0) {
            no = arvore.Busca(valor);
            if(no == NULL)
                cout<<valor<<" nao encontrado"<<endl;
            else
                cout<<valor<<" encontrado"<<endl;
            Leitura(arvore);
        }
        else if(strcmp(comando, "imprime_arvore") == 0) {
            arvore.Imprime();
            Leitura(arvore);
        }
        else if(strcmp(comando, "remove") == 0){
            if(arvore.Busca(valor) == NULL){
                cout<<valor<<" nao encontrado"<<endl;
                Leitura(arvore);
            }
            else{
                arvore.Remove(valor);
                Leitura(arvore);
            }
        }
        else{
            cout << "Comando invalido" << endl;
            Leitura(arvore);
        }
    }
}

int main() {
    cin>>t;
    arvoreB<int> arvore(t);
    Leitura(arvore);
    return 0;
}
