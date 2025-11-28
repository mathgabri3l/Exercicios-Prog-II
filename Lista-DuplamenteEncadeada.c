/*Objetivo: Desenvolver uma lista duplamente encadeada em linguagem 
C com as operações básicas de inserção, remoção, busca e listagem.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Nó{
    int x;
    struct Nó *proximoNó;
    struct Nó *anteriorNó;
}nó;

void insercaoInicio (nó **lista, int n );
void insercaoPosicao(nó **lista, int n, int posição);
void insercaoFinal  (nó **lista, int n );
void listagemLista  (nó *nóPtr);
nó*  removerNó      (nó **lista, int posição);
int  buscarPosição  (nó **lista, int valor);

int main (){
      
    int escolha, n, posição, valor;
    nó *remover, *lista = NULL;

    do
    {
        printf("\n0.Sair\n1.Inserir\n2.Remover\n3.Busca\n4.Listagem\n\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
        printf("\n1.Inserir no inicio\n2.Inserir no final\n3.Inserir em uma posição\n\n");
        scanf("%d", &escolha);
            switch (escolha)
            {
            case 1:
             printf("\nInsira um numero inteiro: ");scanf("%d", &n);
             insercaoInicio(&lista, n);
                break;
            case 2:
             printf("\nInsira um numero inteiro:");scanf("%d", &n);
             insercaoFinal(&lista, n);
                break;
            case 3:
             printf("\nInsira um numero inteiro: ");scanf("%d", &n);
             printf("Insira a posição: ");scanf("%d", &posição);
             insercaoPosicao(&lista, n, posição);
                break;
            default:
                printf("\nOpção invalida\n");
                break;
            }
             break;
        case 2:
            printf("Insira a posição: ");scanf("%d", &posição);
            remover = removerNó(&lista, posição);
            if(remover){
               free(remover);
            }
             break;
        case 3:
            printf("Digiter o valor do nó a ser encontrado\n");scanf("%d", &valor);
            posição = buscarPosição(&lista, valor);
            if(posição != 0){
                printf("\no elemento esta na posição %d da lista\n", posição);
            }
            else
              printf("\nValor inexistente\n");
              break;
        case 4:
            listagemLista(lista);
             break;
        case 0:
             return 0;
        default:
            printf("\nOpção invalida\n");
        }
        
    } while (escolha != 0);
    
    return 0;
}
void insercaoInicio (nó **lista, int n) {
    nó *novo = malloc(sizeof(nó));

    if (!novo){
        printf("ERRO"); //erro na alocação de memoria 
        return;}

     novo->x = n;
     novo->anteriorNó = NULL;
     novo->proximoNó = *lista;

     if(*lista)
        (*lista)->anteriorNó = novo;

    *lista = novo; 
}

void insercaoPosicao (nó **lista, int n, int posição ) {
    if (posição <= 0){
        printf("\nPosição invalida\n");
        return;
    }
     nó *aux, *novo = malloc(sizeof(nó));

     if (!novo){
         printf("ERRO");
         return; }

    novo->x = n;

     if(posição == 1){
        novo->anteriorNó = NULL;
        novo->proximoNó = *lista;
        if(*lista)
            (*lista)->anteriorNó = novo;    
       *lista = novo; 
     }
     else {
     aux = *lista;
     
        if (*lista == NULL){  //caso a lista esteja vazia
           novo->proximoNó = NULL;
           novo->anteriorNó = NULL;
           *lista = novo; }
        else {
            for(int i = 1;i < posição - 1 ;i++){
                if(aux->proximoNó == NULL)
                   break;
                aux = aux->proximoNó;
            }
            novo->proximoNó = aux->proximoNó;
            novo->anteriorNó = aux;

            if(aux->proximoNó)
               aux->proximoNó->anteriorNó = novo;
            aux->proximoNó = novo; } }

}

void insercaoFinal  (nó **lista, int n ) {
    nó *aux, *novo = malloc(sizeof(nó));
 
    if(!novo){
        printf("ERRO");
        return;
    }
      
       novo->x = n;
       novo->proximoNó = NULL;

       if(*lista == NULL) {
          *lista = novo; 
          novo->anteriorNó = NULL;
        }
       else{
          aux = *lista;
          while(aux->proximoNó){
                aux = aux->proximoNó;} 
            aux->proximoNó = novo; 
            novo->anteriorNó = aux;} 

}

void listagemLista (nó *nó){
    printf("\nLista:");
    int contador = 1;
    while(nó){
          printf("\n\nnó: %d\n",contador);
          printf("\nconteudo do nó: %d", nó->x);
          printf("\nEndereço atual: %p",(void*)nó);
          if (nó->proximoNó){
              printf("\nconteudo do proximo nó: %d", nó->proximoNó->x); 
              printf("\nProximo Endereço: %p",(void*)nó->proximoNó);
              }
          if (nó->anteriorNó){
              printf("\nconteudo do nó anterior: %d", nó->anteriorNó->x);  
               printf("\nEndereço Anterior: %p",(void*)nó->anteriorNó);}
         
          nó = nó->proximoNó;
          contador++;
    }
    printf("\n\n");
}

nó*  removerNó  (nó **lista, int posição){
     if(posição <= 0){
        printf("\ninsira uma posição existente\n");
        return NULL;
     }

     if(*lista == NULL){
        printf("\nLista Vazia\n");
        return NULL;
     }

     nó *aux = *lista;

     if(posição == 1){
        *lista = aux->proximoNó;
        if(*lista)
           (*lista)->anteriorNó = NULL;
        return aux;
     }

     for(int i = 1;i < posição ;i++){
         if(aux == NULL){
            printf("\nPosição não existe\n");
            return NULL;
         }
        aux = aux->proximoNó;
     }

     if(aux->anteriorNó)
        aux->anteriorNó->proximoNó = aux->proximoNó;
     if(aux->proximoNó)
        aux->proximoNó->anteriorNó = aux->anteriorNó;
     return aux;

}

int  buscarPosição  (nó **lista, int valor){
    int posição = 1;
    nó *aux = *lista;
    
    while(aux  != NULL){
        if(aux->x == valor){
           return posição;
        }
        aux = aux->proximoNó;
        posição++;
    }

    return 0;
}