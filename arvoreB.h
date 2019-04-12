#ifndef ARVOVEB_H
#define ARVOREB_H

#include <iostream>
#include <stdlib.h>

using namespace std;

template <class TIPO>
class arvoreB;

template <class TIPO>
class Nodo {
    friend class arvoreB<TIPO>;
public:
    int quant_chaves;
    TIPO *chaves;
    Nodo<TIPO> **apontadores;
    bool eh_folha;
    Nodo(int grau_max);    ~Nodo();
};

//contrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::Nodo(int grau_max) {
    this -> quant_chaves = 0;
    this -> apontadores = new Nodo*[grau_max + 1];
    this -> chaves = new TIPO[grau_max];
}

//destrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::~Nodo() {
    delete [] this -> chaves;
    delete [] this -> apontadores;
}

template <class TIPO>
class arvoreB {
public:
    int t, grau_max;
    Nodo<TIPO> *raiz = new Nodo<TIPO>(grau_max);
    arvoreB(int t);
    ~arvoreB();
    Nodo<TIPO>* Busca(Nodo<TIPO> *no,TIPO ch);
    Nodo<TIPO>* Busca(TIPO valor);
    void Empurra(Nodo<TIPO> *ap,int i);
    void Insere(TIPO valor);
    void Insere(Nodo<TIPO> *ap,TIPO valor);
    void Insere_No_Sublotado(Nodo<TIPO> *ap,TIPO valor,int i);
    void Insere_Raiz_Nula(TIPO valor);
    void Imprime();
    void Imprime(Nodo<TIPO> *ap);
    void Split(Nodo<TIPO> *pai, Nodo<TIPO> *filho);
};

template <class TIPO>
arvoreB<TIPO>::arvoreB(int t) {
    this -> raiz = NULL;
    this -> t = t;
    this -> grau_max = 2 * t;//deixa 2t para poder inserir e depois partir no caso de superlotamento

}

template <class TIPO>
arvoreB<TIPO>::~arvoreB() {

}

//Comeco das funcoes de inserir
template <class TIPO>
void arvoreB<TIPO>::Insere_Raiz_Nula(TIPO valor) {
    Nodo<TIPO>* novoNo = new Nodo<TIPO>(grau_max);
    novoNo -> quant_chaves = 1;
    novoNo -> chaves[0] = valor;
    novoNo ->eh_folha = true;
    for(int i = 0;i < grau_max;i++)
        novoNo -> apontadores[i] = NULL;
    this->raiz = novoNo;
}

template <class TIPO>
void arvoreB<TIPO>::Empurra(Nodo<TIPO> *ap,int i){
    TIPO aux;
    for(int j = ap->quant_chaves;j > i;j--){
        ap->chaves[j] = ap->chaves[j-1];
    }
}

template <class TIPO>
void arvoreB<TIPO>::Insere_No_Sublotado(Nodo<TIPO> *ap,TIPO valor,int i) {
    //Copiar os antigos apontadores daquele no
    ap->chaves[i] = valor;
    ap->quant_chaves++;
    cout<<"Inseriu "<<valor<<endl;
}

template <class TIPO>
void arvoreB<TIPO>::Insere(Nodo<TIPO> *ap,TIPO valor) {
    int i;
    if(ap == NULL){
        Insere_Raiz_Nula(valor);
    } 
    else{
        int i = 0;
        while(i < ap -> quant_chaves && valor > ap -> chaves[i])
            i++;
        Empurra(ap, i);
        Insere_No_Sublotado(ap, valor, i);
        int max_ch = 2 * t;
        if(ap -> quant_chaves == max_ch) { //Se ficar superlotado
                //Quebrar e passar a mediana
            }
        }
}
//Termino da funcoes de insere

template <class TIPO>
void arvoreB<TIPO>::Split(Nodo<TIPO> *pai, Nodo<TIPO> *filho){
    int pos_mediana = t - 1;
    Nodo<TIPO> *irmao = new Nodo<TIPO>(grau_max);
    for(int i = t; i < grau_max; i++){
        irmao -> chaves[i]
    }
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(TIPO valor) {
    return Busca(this -> raiz, valor);
}
/*
Busca: Função para procurar em que nó está ou deve estar um determinado elemento
Retorno: Um nó para ser feita a inserção ou que contém o número passado
*/
template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(Nodo<TIPO> *no,TIPO ch) {
    if(no == NULL) {
        return no;
    } 
    else{
        for(int i = 0; i < no -> quant_chaves && ch >= no -> chaves[i]; i++) {
            if(ch == no -> chaves[i])
                return no;
            if(ch < no -> chaves[i]){
                if(no -> apontadores[i] == NULL)
                    return no;
                Busca(no -> apontadores[i], ch);
            }else{
                if(no -> apontadores[i+1] == NULL){
                    return no;
                }
                Busca(no -> apontadores[i+1], ch);
            }
        }
        return no;
    }
}

template <class TIPO>
void arvoreB<TIPO>::Insere(TIPO valor) {
    Nodo<TIPO> *no = new Nodo<TIPO>(grau_max);
    no = Busca(valor);
    Insere(no, valor);
}

template <class TIPO>
void arvoreB<TIPO>::Imprime() {
    Imprime(this->raiz);
}

template <class TIPO>
void arvoreB<TIPO>::Imprime(Nodo<TIPO> *ap) {
    for(int i = 0; i < ap->quant_chaves; i++){
        if(i == 0)
            cout << "( ";
        if(ap->apontadores[i] != NULL)
            Imprime(ap->apontadores[i]);
        else
            cout << ap->chaves[i] << " ";
        if(i == ap->quant_chaves - 1)
            cout << ")";
    }
    cout << endl;
}
#endif //ARVOREB_H