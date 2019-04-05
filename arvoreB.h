#ifndef ARVOVEB_H
#define ARVOREB_H

#include <iostream>
#include <stdlib.h>

using namespace std;

template <class TIPO>
class arvoreB;

template <class TIPO>
class Nodo
{
    friend class arvoreB<TIPO>;
private:
    int quant_chaves;
    TIPO *chaves;
    Nodo<TIPO> **apontadores;
    bool eh_folha;
public:
    Nodo(int grau_max);
    ~Nodo();
};

//contrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::Nodo(int grau_max)
{
    this -> quant_chaves = 0;
    this -> apontadores = new Nodo*[grau_max+1];
    this -> chaves = new TIPO[grau_max];
}

//destrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::~Nodo()
{
    delete [] this -> chaves;
    delete [] this -> apontadores;
}

template <class TIPO>
class arvoreB
{
private:
    int t, grau_max;
    Nodo<TIPO> *raiz = new Nodo<TIPO>(grau_max);
public:
    arvoreB(int t);
    ~arvoreB();
    Nodo<TIPO>* Busca(Nodo<TIPO> *no,TIPO ch);
    Nodo<TIPO>* Busca(TIPO valor);
    void Insere(TIPO valor);
    void Insere(Nodo<TIPO> *ap,TIPO valor);
    void Insere_No_Superlotado(Nodo<TIPO> *ap,TIPO valor,int i);
    void Insere_No_Sublotado(Nodo<TIPO> *ap,TIPO valor,int i);
    void Insere_Raiz_Nula(TIPO valor);
    void Imprime();
    void Imprime(Nodo<TIPO> *ap);
};

template <class TIPO>
arvoreB<TIPO>::arvoreB(int t)
{
    this -> raiz = NULL;
    this -> t = t;
    this -> grau_max = 2 * t;//deixa 2t para poder inserir e depois partir no caso de superlotamento
}

template <class TIPO>
arvoreB<TIPO>::~arvoreB()
{

}

//Comeco das funcoes de inserir
template <class TIPO>
void arvoreB<TIPO>::Insere_Raiz_Nula(TIPO valor)
{
    cout<<"Chegou"<<endl;
    Nodo<TIPO>* novoNo = (Nodo<TIPO>*)malloc(sizeof(Nodo<TIPO>));
    novoNo -> quant_chaves = 1;
    novoNo -> chaves[0] = valor;
    novoNo -> apontadores = NULL;
    cout<<"Inseriu o valor "<<valor<<endl;
    this->raiz = novoNo;
}

template <class TIPO>
void arvoreB<TIPO>::Insere_No_Sublotado(Nodo<TIPO> *ap,TIPO valor,int i)
{

    //Copiar os antigos apontadores daquele no
}

template <class TIPO>
void arvoreB<TIPO>::Insere(TIPO valor)
{
    Nodo<TIPO> *no = Busca(raiz, valor);
    Insere(no, valor);
}

template <class TIPO>
void arvoreB<TIPO>::Insere(Nodo<TIPO> *ap,TIPO valor)
{
    int i;

    if(ap == NULL)
    {
        Insere_Raiz_Nula(valor);
    }
    else
    {
        int max_ch = 2 * t -1;
        if(ap->quant_chaves + 1 == max_ch)  //Superlotado
        {
            for(i=0; i<ap->quant_chaves; i++)
            {
                if(valor < ap->chaves[i])
                    break;
                //Inserir valor no nó
                Insere_No_Superlotado(ap,valor,i);
                //Quebrar e passar a mediana
            }
        }
        else
        {
            for(i=0; i<ap->quant_chaves; i++)
            {
                if(valor < ap->chaves[i])
                    break;
            }
            //Inserir valor no nó
            Insere_No_Sublotado(ap,valor,i);
        }
    }
}

template <class TIPO>
void arvoreB<TIPO>::Insere_No_Superlotado(Nodo<TIPO> *ap,TIPO valor,int i){

}

//Termino da funcoes de insere


template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(TIPO valor){
  return Busca(this -> raiz, valor);
}
/*
Busca: Função para procurar em que nó está ou deve estar um determinado elemento
Retorno: Um nó para ser feita a inserção ou que contém o número passado
*/
template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(Nodo<TIPO> *no,TIPO ch)
{
    int i;
    if(no == NULL)
    {
        cout << "Nao tem esse registro na arvore!!!"<<endl;
        return no;
    }
    else
    {
        for(i = 0; i < no->quant_chaves && ch > no->chaves[i]; i++)
            i++;
        if(ch == no->chaves[i])
            return no;
        if(ch < no->chaves[i])
            Busca(no->apontadores[i-1],ch);
        else
            Busca(no->apontadores[i],ch);
    }
}

template <class TIPO>
void arvoreB<TIPO>::Imprime(){
    Imprime(this->raiz);
}

template <class TIPO>
void arvoreB<TIPO>::Imprime(Nodo<TIPO> *ap){
    for(int i = 0;i < ap->quant_chaves;i++){
        if(ap->apontadores[i] != NULL)
            Imprime(ap->apontadores[i]);
        else
            cout << ap->chaves[i] << " ";
    }
}
#endif //ARVOREB_H
