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
    Nodo<TIPO> **pai;
    Nodo<TIPO> **filhos;
    bool eh_folha;
    Nodo(int grau_max);
    ~Nodo();
};

//contrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::Nodo(int grau_max) {
    this -> quant_chaves = 0;
    this -> pai = new Nodo*[1];
    this -> filhos = new Nodo*[grau_max];
    this -> chaves = new TIPO[grau_max - 1];
}

//destrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::~Nodo() {
    delete [] this -> chaves;
    delete [] this -> pai;
    delete [] this -> filhos;
}

template <class TIPO>
class arvoreB {
public:
    int t, grau_max;
    Nodo<TIPO> *raiz;
    arvoreB(int t);
    ~arvoreB();
    Nodo<TIPO>* Busca(Nodo<TIPO> *no,TIPO valor);
    Nodo<TIPO>* Busca(TIPO valor);
    void Empurra(Nodo<TIPO> *ap,int i);
    void Insere(TIPO valor);
    void Insere_No_Sublotado(Nodo<TIPO> *ap, TIPO valor);
    void Insere_Raiz_Nula(TIPO valor);
    void Split(int i, Nodo<TIPO> *y, Nodo<TIPO> *x);
    void Imprime();
    void Imprime(Nodo<TIPO> *ap);
    bool Remove(TIPO valor);
    bool Remove(TIPO valor, Nodo<TIPO> *ap);
    void Puxa(Nodo<TIPO> *ap, int i);
};

template <class TIPO>
arvoreB<TIPO>::arvoreB(int t) {
    this -> t = t;
    this -> grau_max = 2 * t - 1;
    this -> raiz = NULL;
}

template <class TIPO>
arvoreB<TIPO>::~arvoreB() {

}


/*
Empurra: Função para empurrar as chaves do nó, abrindo espaço para a chave que será inserida
Retorno: sem retorno
*/
template <class TIPO>
void arvoreB<TIPO>::Empurra(Nodo<TIPO> *ap,int i) {
    for(int j = ap->quant_chaves; j > i; j--) {
        ap->chaves[j] = ap->chaves[j-1];
    }
}

/*
Insere:  Verifca as condições do nó em que chave será inserida, chama as funções Empurra e Insere_No_Sublotado
caso o nó fique superlotado é chamada a função Split
Retorno: sem retorno
*/
template <class TIPO>
void arvoreB<TIPO>::Insere(TIPO valor) {
    if(raiz == NULL) {
        Insere_Raiz_Nula(valor);
    }
    else {
        if(raiz -> quant_chaves == grau_max){
            Nodo<TIPO> *novaRaiz = new Nodo<TIPO>(grau_max);
            novaRaiz -> eh_folha = false;
            novaRaiz -> filhos[0] = raiz;
            Split(0, raiz, novaRaiz);
            int i = 0;
            if(novaRaiz -> chaves[0] < valor)
                i++;
            Insere_No_Sublotado(novaRaiz -> filhos[i], valor);
            raiz = novaRaiz;
        }
        else{
            Insere_No_Sublotado(raiz, valor);
        }
    }
}

template <class TIPO>
void arvoreB<TIPO>::Insere_No_Sublotado(Nodo<TIPO> *ap, TIPO valor){
    int i = ap -> quant_chaves - 1;
    if(ap -> eh_folha){
        while(i >= 0 && ap -> chaves[i] > valor){
            ap -> chaves[i + 1] = ap -> chaves[i];
            i--;
        }
        ap -> chaves[i + 1] = valor;
        ap -> quant_chaves += 1;
    }
    else{
        while(i >= 0 && ap -> chaves[i] > valor)
            i--;
        if(ap -> filhos[i + 1] -> quant_chaves == grau_max){
            Split(i + 1, ap -> filhos[i + 1], ap);
            if(ap -> chaves[i + 1] < valor)
                i++;
        }
        Insere_No_Sublotado(ap -> filhos[i + 1], valor);
    }
}

template <class TIPO>
void arvoreB<TIPO>::Insere_Raiz_Nula(TIPO valor) {
    Nodo<TIPO>* novoNo = new Nodo<TIPO>(grau_max);
    novoNo -> quant_chaves = 1;
    novoNo -> chaves[0] = valor;
    novoNo ->eh_folha = true;
    for(int i = 0; i < grau_max; i++)
        novoNo -> filhos[i] = NULL;
    novoNo -> pai = NULL;
    this->raiz = novoNo;
}

template <class TIPO>
void arvoreB<TIPO>::Split(int i, Nodo<TIPO> *y, Nodo<TIPO> *x){
    Nodo<TIPO> *z = new Nodo<TIPO>(grau_max);
    z -> eh_folha = y -> eh_folha;
    z -> quant_chaves = t - 1;

    for(int j = 0; j < t - 1; j++)
        z -> chaves[j] = y -> chaves[j + t];
    if(!y -> eh_folha){
        for(int j = 0; j < t; j++)
            z -> filhos[j] = y -> filhos[j + t];
    }
    y -> quant_chaves = t - 1;
    for(int j = x -> quant_chaves; j >= i + 1; j--)
        x -> filhos[j + 1] = x -> filhos[j];

    x -> filhos[i + 1] = z;
    for(int j = x -> quant_chaves - 1; j >= i; j--)
        x -> chaves[j + 1] = x -> chaves[j];

    x -> chaves[i] = y -> chaves[t - 1];
    x -> quant_chaves += 1;
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(TIPO valor) {
    return Busca(this -> raiz, valor);
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(Nodo<TIPO> *no,TIPO valor) {
    if(no == NULL) {
        return no;
    }
    else {
        int i = 0;
        while(i < no -> quant_chaves && valor > no -> chaves[i])
            i++;
        if(no -> chaves[i] == valor)
            return no;
        if(no -> eh_folha)
            return NULL;
        return Busca(no -> filhos[i], valor);
    }
}

template <class TIPO>
void arvoreB<TIPO>::Imprime() {
    if(raiz != NULL){
        Imprime(raiz);
    }
    cout<<endl;
}

template <class TIPO>
void arvoreB<TIPO>::Imprime(Nodo<TIPO> *ap) {
    int i;
    cout<<"(";
    for(i = 0; i < ap -> quant_chaves; i++){
        if(!ap -> eh_folha)
            Imprime(ap -> filhos[i]);
        if(i != ap -> quant_chaves)
            cout<<" "<< ap -> chaves[i]<<" ";
    }
    if(!ap -> eh_folha)
        Imprime(ap -> filhos[i]);
    cout<<")";
}

template <class TIPO>
void arvoreB<TIPO>::Puxa(Nodo<TIPO> *ap, int i){
    int j;
    for(j = ap -> quant_chaves - 1; i < j; i++){
        ap -> chaves[i] = ap -> chaves[i + 1];
    }
    ap -> quant_chaves -= 1; 
}

template <class TIPO>
bool arvoreB<TIPO>::Remove(TIPO valor){
    Nodo<TIPO> *no = new Nodo<TIPO>(grau_max);
    no = Busca(valor); 
    return Remove(valor, no);
}

template <class TIPO>
bool arvoreB<TIPO>::Remove(TIPO valor, Nodo<TIPO> *ap){
    if(ap == NULL)    
        return false;
    else{
        int i, posicao;
        for(i = 0; i < ap -> quant_chaves; i++){
            if(ap -> chaves[i] == valor){
                posicao = i;
                break;
            }
        }
        Puxa(ap, posicao);
        if(ap -> eh_folha){
            if(ap -> quant_chaves > t){
                       
            }
            else{

            }            
        }
    }
}


#endif //ARVOREB_H
