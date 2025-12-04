#include <stdio.h>
#include <stdlib.h>

typedef struct Nó{
    int x;
    struct Nó *Esquerda;
    struct Nó *Direita;
    int altura;
}nó;

//funções novas implementadas: CriaNó,maiorNó,AlturaNó,FB, rotaçãoDir/Esq/Duplas e balanceamento.

nó *criarNó (int n);
void Inserir (nó **raiz, int n );
void busca (nó *raiz, int n);
void inOrder (nó *raiz);
void preOrder (nó *raiz);
void postOrder (nó *raiz);
void remover (nó **raiz, int n); 
void liberarMemoria (nó *raiz);
int Altura (nó *raiz); 
int AlturaNó (nó *nó);
int maiorNó (int nóA, int nóB);
int FB (nó *nó);
nó *rotaçãoDir(nó *raiz);
nó *rotaçãoEsq(nó *raiz);
nó *rotaçãoDirEsq (nó *raiz);
nó *rotaçãoEsqDir (nó *raiz);
nó *balanceamento(nó *raiz);
  
int main(){
    int escolha, n;
    nó *raiz = NULL;

    do
    {
        printf("1-Inserir Valor\n2-Buscar Valor\n3-Remover Valor\n4-Percorrer Arvore\n0-Sair\n\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("\nInsira um numero inteiro: ");scanf("%d", &n);
             Inserir(&raiz, n);
                break;
        case 2:
            printf("Digiter o valor do nó a ser encontrado\n");scanf("%d", &n);
            busca(raiz, n);
                break;
        case 3:
            printf("Digiter o valor do nó a ser removido\n");scanf("%d", &n);
            remover(&raiz, n);
              break;
        case 4:
            printf("\n\n1-Pré-Ordem\n2-Em Ordemm\n3-Pós-Ordem\n");scanf("%d", &escolha);
            switch (escolha)
            {
            case 1:
                preOrder(raiz);
                printf("\n");
                break;
            case 2:
                inOrder(raiz);
                printf("\n");
                break;
            case 3:
                postOrder(raiz);
                printf("\n");
                break;
            default:
                printf("\nOpção Invalida\n"); }
             break;
        case 0:
             liberarMemoria(raiz);
             return 0;
        default:
            printf("\nOpção invalida\n");
        }
        
    } while (escolha != 0);
    
    return 0;
}
nó *criarNó (int n){ 
   nó *novo = malloc(sizeof(nó)); //função criar nó agora e separada da função de inserir
   
   if(novo){
        novo->x = n;
        novo->Esquerda = NULL;
        novo->Direita = NULL;
        novo->altura = 0;
   }
   else
     printf("ERRO");
   return novo;
}
int AlturaNó (nó *nó){ 
    if (nó == NULL) //função para saber a altura de uma determinada subarvore
        return -1; //espaço vazio tem altura de -1
    else 
       return nó->altura;
}
int maiorNó (int nóA, int nóB){ 
if (nóA > nóB) 
    return nóA; //função vai receber dois numeros (que serão alturas) e retornara o maior dentre eles
else 
    return nóB; //se forem alturas iguais, pode retornar qualquer uma
}
int FB (nó *nó){ //função que calcula o fator de balanceamento
    if(nó) //fator de balanceamento (FB) = altura da esquerda - altura da direita. 
       return AlturaNó(nó->Esquerda) - AlturaNó(nó->Direita); 
    else 
       return 0;
}
nó *rotaçãoEsq(nó *raiz){ 
    nó *y, *x; //função para rotação a esquerda

    y = raiz->Direita; //filho da direita da raiz desbalanceada
    x = y->Esquerda; //filho da esquerda do filho da direita (se ele existir)

    y->Esquerda = raiz; //raiz "desce" para ser o filho da esquerda do seu posteriormente filho da direita
    raiz->Direita = x; //filho da esquerda de y, se ele existir, agora passa a ser filho da esquerda da antiga raiz
    //atualizando a altura dos nó, altura = maior altura das suas subArvores + 1
    raiz->altura = maiorNó(AlturaNó(raiz->Esquerda), AlturaNó(raiz->Direita)) + 1; 
    y->altura = maiorNó(AlturaNó(y->Esquerda), AlturaNó(y->Direita)) + 1;

    return y; //o "y" sera a nova raiz da arvore, por isso ele que sera retornado
}
nó *rotaçãoDir(nó *raiz){
    nó *y, *x; //função para rotação a direita, mesma coisa da anterior porem invertida

    y = raiz->Esquerda;
    x = y->Direita;

    y->Direita = raiz;
    raiz->Esquerda = x;

    raiz->altura = maiorNó(AlturaNó(raiz->Esquerda), AlturaNó(raiz->Direita)) + 1;
    y->altura = maiorNó(AlturaNó(y->Esquerda), AlturaNó(y->Direita)) + 1;

    return y;
}
nó *rotaçãoDirEsq (nó *raiz) { 
    //rotação direita esquerda, primeiro faz uma rotação a direita e depois uma rotação para esquerda
    raiz->Direita = rotaçãoDir(raiz->Direita); 
    return rotaçãoEsq(raiz);
}
nó *rotaçãoEsqDir (nó *raiz){
    //rotação esquerda direita, primeiro faz uma rotação a esquerda e depois uma rotação para direita
    raiz->Esquerda = rotaçãoEsq(raiz->Esquerda);
    return rotaçãoDir(raiz);
}
nó *balanceamento(nó *raiz){
    int fb = FB(raiz);
    //função para balancear a arvore
    if(fb < -1 && FB(raiz->Direita) <= 0 ) //se o fb for negativo e o fb do filho da direita tambem for negativo ou 0
      raiz = rotaçãoEsq(raiz);
    else if (fb > 1 && FB(raiz->Esquerda) >= 0 ) //se o fb for positivo e o fb do filho da esquerda tambem for positivo ou 0
      raiz = rotaçãoDir(raiz);
    else if (fb < -1 && FB(raiz->Direita) > 0)  //se o fb for negativo e o fb do filho da direita for positivo 
      raiz = rotaçãoDirEsq(raiz); 
    else if (fb > 1 && FB(raiz->Esquerda) < 0) //se o fb for positivo e o fb do filho da esquerda for negativo 
      raiz = rotaçãoEsqDir(raiz);
    
    return raiz;
    }
void Inserir (nó **raiz, int n) {
    
    if(*raiz == NULL){     
         *raiz = criarNó(n);
         return; 
        }
     if (n < (*raiz)->x) 
        Inserir(&(*raiz)->Esquerda, n); 
     else if (n > (*raiz)->x)
        Inserir(&(*raiz)->Direita, n); 
        else {
        printf("Valor Já existe na arvore\n"); 
        return;
         } 

     //altura dos filhos 
     int alturaEsq = AlturaNó((*raiz)->Esquerda);
     int alturaDir = AlturaNó((*raiz)->Direita);
     //atualiza altura, pega a maior altura de um dos filhos e soma +1
     (*raiz)->altura = maiorNó(alturaEsq, alturaDir) + 1;
      //balancea (se for preciso) a arvore apos o novo nó inserido
     *raiz = balanceamento(*raiz);
    } 
void remover (nó **raiz, int n){
      if(*raiz == NULL){
        printf("Valor não está na arvore\n"); 
        return;}

      if (n < (*raiz)->x)                 
        remover(&(*raiz)->Esquerda, n); 
     else if (n > (*raiz)->x)
        remover(&(*raiz)->Direita, n);
     else {                               
        
         if((*raiz)->Esquerda == NULL && (*raiz)->Direita == NULL){ 
            free(*raiz);
            *raiz = NULL; 
             return; } 
         else if ((*raiz)->Direita == NULL){ 
            nó *aux = *raiz;              
            *raiz = (*raiz)->Esquerda;       
            free(aux); }                    
         else if ((*raiz)->Esquerda == NULL){ 
            nó *aux = *raiz;                  
            *raiz = (*raiz)->Direita;         
            free(aux); }
         else {                               
            nó *aux = (*raiz)->Esquerda;      
            while (aux->Direita) {        
                aux = aux->Direita; }               
                (*raiz)->x = aux->x;          
                remover(&(*raiz)->Esquerda, aux->x); } }


    int alturaEsq = AlturaNó((*raiz)->Esquerda); 
    int alturaDir = AlturaNó((*raiz)->Direita);        
    
    (*raiz)->altura = maiorNó(alturaEsq, alturaDir) + 1;

    *raiz = balanceamento(*raiz);

}  
void busca (nó *raiz, int n){
     if (raiz == NULL){
        printf("\nValor não se encontra na arvore\n\n");
        return;
     }
     if (raiz->x == n){
         printf("\nO valor se encontra na arvore\n\n");
         return;
     }
     
     if (n < raiz->x)  
         busca(raiz->Esquerda, n);
     else if (n > raiz->x) 
         busca(raiz->Direita, n);
}
void preOrder (nó *raiz){ 
    if(raiz){    
       printf("%d ", raiz->x); 
       preOrder(raiz->Esquerda);
       preOrder(raiz->Direita);
    }
}
void inOrder (nó *raiz){
     if(raiz){ 
        inOrder(raiz->Esquerda);
        printf("%d ", raiz->x);
        inOrder(raiz->Direita);
     }
}
void postOrder (nó *raiz){ 
    if(raiz){  
       postOrder(raiz->Esquerda); 
       postOrder(raiz->Direita);
       printf("%d ", raiz->x);
    }
}
void liberarMemoria (nó *raiz){ 
     if (raiz == NULL)
        return;
     liberarMemoria(raiz->Esquerda);
     liberarMemoria(raiz->Direita);
     free(raiz);
}

