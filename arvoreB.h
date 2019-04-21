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
private:
    int quant_chaves;
    TIPO *chaves;
    Nodo<TIPO> **pai;
    Nodo<TIPO> **filhos;
    bool eh_folha;
public:
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
private:    
    int t, grau_max;
    Nodo<TIPO> *raiz;
public:
    arvoreB(int t);
    Nodo<TIPO>* Busca(Nodo<TIPO> *no,TIPO valor);
    Nodo<TIPO>* Busca(TIPO valor);
    void Insere(TIPO valor);
    void Insere_No_Sublotado(Nodo<TIPO> *ap, TIPO valor);
    void Insere_Raiz_Nula(TIPO valor);
    void Split(int i, Nodo<TIPO> *y, Nodo<TIPO> *x);
    void Imprime();
    void Imprime(Nodo<TIPO> *ap);
    bool Remove(TIPO valor);
    bool Remove(Nodo<TIPO> *ap, TIPO valor);
    void Remove_De_Folha(Nodo<TIPO> *ap, int posicao);
    void Remove_De_Nao_Folha(Nodo<TIPO> *ap, int posicao);
    int Get_Posicao(Nodo<TIPO> *ap, TIPO valor);
    void Empresta_Do_Anterior(Nodo<TIPO> *ap, int posicao);
    void Empresta_Do_Sucessor(Nodo<TIPO> *ap, int posicao);
    int Get_Antecessor(Nodo<TIPO> *ap, int posicao);
    int Get_Sucessor(Nodo<TIPO> *ap, int posicao);
    void Preenche(Nodo<TIPO> *ap, int posicao);
    void Junta(Nodo<TIPO> *ap, int posicao);
};
template <class TIPO>
arvoreB<TIPO>::arvoreB(int t) {
    this -> t = t;
    this -> grau_max = 2 * t - 1;
    this -> raiz = NULL;
}

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
        if(i != ap -> quant_chaves){
            if(i == 0)
                cout<<ap -> chaves[i];
            else
                cout<<" "<< ap -> chaves[i];
        }
    }
    if(!ap -> eh_folha)
        Imprime(ap -> filhos[i]);
    cout<<")";
}

template <class TIPO>
bool arvoreB<TIPO>::Remove(TIPO valor){
    if(raiz == NULL)
        return false;
    Remove(raiz, valor);
    if(raiz -> quant_chaves == 0){
        Nodo<TIPO> *temporario = raiz;
        if(raiz -> eh_folha)
            raiz = NULL;
        else
            raiz = raiz -> filhos[0];
        delete temporario;
    }
    return true;
}

template <class TIPO>
bool arvoreB<TIPO>::Remove(Nodo<TIPO> *ap, TIPO valor){
    int posicao = Get_Posicao(ap, valor);
    if(posicao < ap -> quant_chaves && ap -> chaves[posicao] == valor){
        if(ap -> eh_folha)
            Remove_De_Folha(ap, posicao);
        else
            Remove_De_Nao_Folha(ap, posicao);
    }
    else{
            if(ap -> eh_folha)
                return false;
            bool flag = ((posicao == ap -> quant_chaves)?true:false);
            if(ap -> filhos[posicao]-> quant_chaves < t)
                Preenche(ap, posicao);
            if(flag && posicao > ap -> quant_chaves)
                Remove(ap -> filhos[posicao - 1], valor);
            else
                Remove(ap -> filhos[posicao], valor);
    }
}

template <class TIPO>
void arvoreB<TIPO>::Remove_De_Folha(Nodo<TIPO> *ap, int posicao){
    for(int i = posicao; i < ap -> quant_chaves - 1; i++){
        ap -> chaves[i] = ap -> chaves[i + 1];
    }
    ap -> quant_chaves -= 1;
}

template <class TIPO>
void arvoreB<TIPO>::Remove_De_Nao_Folha(Nodo<TIPO> *ap, int posicao){
    TIPO k = ap -> chaves[posicao];
    if(ap -> filhos[posicao] -> quant_chaves >= t){
        int antecessor = Get_Antecessor(ap, posicao);
        ap -> chaves[posicao] = antecessor;
        Remove(ap -> filhos[posicao], antecessor);
    }
    else if(ap -> filhos[posicao + 1] -> quant_chaves >= t){
        int sucessor = Get_Sucessor(ap, posicao);
        ap -> chaves[posicao] = sucessor;
        Remove(ap -> filhos[posicao], sucessor);
    }
    else{
        Junta(ap, posicao);
        Remove(ap -> filhos[posicao], k);
    }
}

template <class TIPO>
int arvoreB<TIPO>::Get_Posicao(Nodo<TIPO> *ap, TIPO valor){
    int i = 0;
    while(i < ap -> quant_chaves && valor > ap -> chaves[i])
        i++;
    return i;
}

template <class TIPO>
int arvoreB<TIPO>::Get_Antecessor(Nodo<TIPO> *ap, int posicao){
    Nodo<TIPO> *cur = ap -> filhos[posicao];
    while(!cur -> eh_folha)
        cur = cur -> filhos[cur -> quant_chaves];
    return cur -> chaves[cur -> quant_chaves - 1];
}

template <class TIPO>
int arvoreB<TIPO>::Get_Sucessor(Nodo<TIPO> *ap, int posicao){
    Nodo<TIPO> *cur = ap -> filhos[posicao + 1];
    while(!cur -> eh_folha)
        cur = cur -> filhos[0];
    return cur -> chaves[0];
}

template <class TIPO>
void arvoreB<TIPO>::Empresta_Do_Anterior(Nodo<TIPO> *ap, int posicao){
    Nodo<TIPO> *filho = ap -> filhos[posicao];
    Nodo<TIPO> *irmao = ap -> filhos[posicao - 1];
    for(int i = filho -> quant_chaves - 1; i >= 0; i--)
        filho -> chaves[i + 1] = filho -> chaves[i];
    if(!filho -> eh_folha){
        for(int i = filho -> quant_chaves; i >= 0; i--)
            filho -> filhos[i + 1] = filho -> filhos[i];
    }
    filho -> chaves[0] = ap -> chaves[posicao - 1];
    if(!filho -> eh_folha)
        filho -> filhos[0] = irmao -> filhos[irmao -> quant_chaves];
    ap -> chaves[posicao - 1] = irmao -> chaves[irmao -> quant_chaves - 1];
    filho -> quant_chaves += 1;
    irmao -> quant_chaves -= 1;
}

template <class TIPO>
void arvoreB<TIPO>::Empresta_Do_Sucessor(Nodo<TIPO> *ap, int posicao){
    Nodo<TIPO> *filho = ap -> filhos[posicao];
    Nodo<TIPO> *irmao = ap -> filhos[posicao + 1];
    filho -> chaves[filho -> quant_chaves] = ap -> chaves[posicao];
    if(!filho -> eh_folha)
        filho -> filhos[filho -> quant_chaves + 1] = irmao -> filhos[0];
    ap -> chaves[posicao] = irmao -> chaves[0];
    for(int i = 1; i < irmao -> quant_chaves; i++)
        irmao -> chaves[i - 1] = irmao -> chaves[i];
    if(!irmao -> eh_folha){
        for(int i = 1; i <= irmao -> quant_chaves; i++)
            irmao -> chaves[i - 1] = irmao -> chaves[i];
    }
    filho -> quant_chaves += 1;
    irmao -> quant_chaves -= 1;
}

template <class TIPO>
void arvoreB<TIPO>::Preenche(Nodo<TIPO> *ap, int posicao){
    if(posicao != 0 && ap -> filhos[posicao - 1] -> quant_chaves >= t)
        Empresta_Do_Anterior(ap, posicao);
    else if(posicao != ap ->quant_chaves && ap -> filhos[posicao + 1] -> quant_chaves >= t)
        Empresta_Do_Sucessor(ap, posicao);
    else{
        if(posicao != 0)
            Junta(ap, posicao - 1);
        else
            Junta(ap, posicao);
    }
}

template <class TIPO>
void arvoreB<TIPO>::Junta(Nodo<TIPO> *ap, int posicao){
    Nodo<TIPO> *filho = ap -> filhos[posicao];
    Nodo<TIPO> *irmao = ap -> filhos[posicao + 1];
    filho -> chaves[t - 1] = ap -> chaves[posicao];
    for(int i = 0; i < irmao -> quant_chaves; i++)
        filho -> chaves[i + t] = irmao -> chaves[i];
    if(!filho -> eh_folha){
        for(int i = 0; i <= irmao -> quant_chaves; i++)
            filho -> filhos[i + t] = irmao -> filhos[i];
    }
    for(int i = posicao + 1; i < ap ->quant_chaves; i++)
        ap -> chaves[i - 1] = ap -> chaves[i];
    for(int i = posicao + 2; i <= ap -> quant_chaves; i++)
        ap -> filhos[i - 1] = ap -> filhos[i];
    filho -> quant_chaves += irmao -> quant_chaves + 1;
    ap -> quant_chaves -= 1;
    delete(irmao);
}

#endif //ARVOREB_H
