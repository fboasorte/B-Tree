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
    this -> filhos = new Nodo*[grau_max + 1];
    this -> chaves = new TIPO[grau_max];
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
    Nodo<TIPO>* Busca(Nodo<TIPO> *no,TIPO ch);
    Nodo<TIPO>* Busca(TIPO valor);
    void Empurra(Nodo<TIPO> *ap,int i);
    void Insere(TIPO valor);
    void Insere(Nodo<TIPO> *ap,TIPO valor);
    void Insere_No_Sublotado(Nodo<TIPO> *ap,TIPO valor,int i);
    void Insere_Raiz_Nula(TIPO valor);
    void Imprime();
    void Imprime(Nodo<TIPO> *ap);
    void Split(Nodo<TIPO> *ap);
    bool Remove(TIPO valor);
    bool Remove(TIPO valor, Nodo<TIPO> *ap);
    void Puxa(Nodo<TIPO> *ap, int i);
};

template <class TIPO>
arvoreB<TIPO>::arvoreB(int t) {
    this -> t = t;
    this -> grau_max = 2 * t;//deixa 2t para poder inserir e depois partir no caso de superlotamento
    this -> raiz = NULL;
}

template <class TIPO>
arvoreB<TIPO>::~arvoreB() {

}

/*
Insere_Raiz_Nula: Função para inserir a primeira chave na árvore
Retorno: sem retorno
*/
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
Insere_No_Sublotado: Função que recebe o nó, a chave e a posição em que essa chave
será inserida e por último realiza a inserção 
Retorno: sem retorno
*/
template <class TIPO>
void arvoreB<TIPO>::Insere_No_Sublotado(Nodo<TIPO> *ap,TIPO valor,int i) {
    //Copiar os antigos filhos daquele no
    ap->chaves[i] = valor;
    int aux = ap->quant_chaves;
    ap->quant_chaves = aux+1;
}

template <class TIPO>
void arvoreB<TIPO>::Insere(TIPO valor) {
    Nodo<TIPO> *no = new Nodo<TIPO>(grau_max);
    no = Busca(valor);
    Insere(no, valor);
}

/*
Insere:  Verifca as condições do nó em que chave será inserida, chama as funções Empurra e Insere_No_Sublotado
caso o nó fique superlotado é chamada a função Split
Retorno: sem retorno
*/
template <class TIPO>
void arvoreB<TIPO>::Insere(Nodo<TIPO> *ap,TIPO valor) {
    if(ap == NULL) {
        Insere_Raiz_Nula(valor);
    } else {
        int i = 0;
        while(i < ap -> quant_chaves && valor > ap -> chaves[i])
            i++;
        Empurra(ap, i);
        Insere_No_Sublotado(ap, valor, i);
        int max_ch = 2 * t;
        if(ap -> quant_chaves == max_ch) { //Caso fique superlotado
            Split(ap);
        }
    }
}

/*
Split: Função para quebrar o nó passado
Retorno: sem retorno
*/
template <class TIPO>
void arvoreB<TIPO>::Split(Nodo<TIPO> *ap) {
    //A mediana foi definida como t-1
    int i,j = 0,pos_mediana = t - 1;
    Nodo<TIPO> *novoNo = new Nodo<TIPO>(grau_max);
    Nodo<TIPO> *noDir = new Nodo<TIPO>(grau_max);
    Nodo<TIPO> *noEsq = new Nodo<TIPO>(grau_max);

    if(ap -> pai == NULL) { //Significa que eh raiz
        //Atualizando o no que ficara a direita da raiz
        noDir ->eh_folha = true;
        //Copiar todos as info do antigo nó

        for(i = pos_mediana + 1; i < ap -> quant_chaves; i++) {
            noDir -> chaves[j] = ap -> chaves[i];
            j++;
        }

        noDir -> quant_chaves = j;
        //Atualizando o no que ficara a esquerda da raiz
        j = 0;
        for(i = 0; i <= pos_mediana; i++) {
            noEsq -> chaves[j] = ap -> chaves[i];
            j++;
        }
        noEsq->eh_folha = true;
        //noEsq->quant_chaves = j;
        noEsq->quant_chaves = ap->quant_chaves - (ap->quant_chaves/pos_mediana) - 1;

        //Atualizando o no que sera a raiz
        novoNo -> eh_folha = false;
        novoNo -> chaves[0] = ap -> chaves[pos_mediana];
        novoNo -> filhos[0] = noEsq;
        novoNo -> filhos[1] = noDir;
        novoNo -> pai = NULL;
        novoNo -> quant_chaves = 1;

        noEsq -> pai[0] = novoNo;
        noDir -> pai[0] = novoNo;
        this -> raiz = novoNo;
    }
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(TIPO valor) {
    return Busca(this -> raiz, valor);
}
/*
Busca: Funcao para procurar em que no estar ou deve estar um determinado elemento
Retorno: Um nó para ser feita a inserção ou que contém o número passado
*/
template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(Nodo<TIPO> *no,TIPO ch) {
    if(no == NULL) {
        return no;
    }
    else {
        int i;
        for(i = 0; i < no -> quant_chaves && ch <= no->chaves[i]; i++) {
            if(ch == no -> chaves[i])     
                return no;
            else if(ch < no -> chaves[i]) {
                if(no -> eh_folha)
                    return no;
                else
                    no = Busca(no -> filhos[i], ch);
            } 
        }
        if(ch > no->chaves[i]){
            if(no -> eh_folha)
                return no;
            else
                no = Busca(no -> filhos[i+1], ch);
        }
    }
}



template <class TIPO>
void arvoreB<TIPO>::Imprime() {
    Imprime(this->raiz);
    cout << ")" << endl;
}

/*
Imprime: Imprime os valores que estão presentes na árvore
Retorno: sem retorno
*/
template <class TIPO>
void arvoreB<TIPO>::Imprime(Nodo<TIPO> *ap) {
    for(int i = 0; i < ap->quant_chaves; i++) {
        if(i == 0)
            cout << "(";
        if(!ap->eh_folha)
            Imprime(ap->filhos[i]);
        else{
            cout << ap->chaves[i];
            if(i < ap->quant_chaves - 1)
                cout << " ";
        }
        if(i == ap->quant_chaves - 1 && ap->pai != NULL)
            cout << ")";
    }
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
