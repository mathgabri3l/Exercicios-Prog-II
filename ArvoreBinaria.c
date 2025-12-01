#include <stdio.h>
#include <stdlib.h>

typedef struct Nó{
    int x;
    struct Nó *Esquerda;
    struct Nó *Direita;
}nó;

void Inserir (nó **raiz, int n );
void busca (nó *raiz, int n);
void inOrder (nó *raiz);
void preOrder (nó *raiz);
void postOrder (nó *raiz);
void remover (nó **raiz, int n); 
void liberarMemoria (nó *raiz);

int main (){
      
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


void Inserir (nó **raiz, int n) {
    
    if(*raiz == NULL){     //caso ache um espaço "vazio", cria o novo nó
        *raiz = malloc(sizeof(nó));
         if(*raiz == NULL){ //confirmação se a memoria foi alocada
         printf("ERRO"); 
         return; 
        }
        (*raiz)->x = n;
        (*raiz)->Esquerda = NULL;
        (*raiz)->Direita = NULL;
         return;
        }
    
     if (n < (*raiz)->x) 
        Inserir(&(*raiz)->Esquerda, n); 
     else if (n > (*raiz)->x)
        Inserir(&(*raiz)->Direita, n); 
     else {
        printf("Valor Já existe na arvore\n"); //Caso seja um valor que ja está na arvore, nada é inserido
        return; } 
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
    if(raiz){    //imprime o valor, depois vai para a esquerda, se não tiver nada a esquerda, vai para a direita
       printf("%d ", raiz->x); 
       preOrder(raiz->Esquerda);
       preOrder(raiz->Direita);
    }
}
void inOrder (nó *raiz){
     if(raiz){  //vai para a esquerda, se não tiver mais nada a esquerda imprime o valor, e depois vai para a direita
        inOrder(raiz->Esquerda);
        printf("%d ", raiz->x);
        inOrder(raiz->Direita);
     }
}
void postOrder (nó *raiz){ 
    if(raiz){   //vai para a esquerda se não tiver nada a esquerda vai para a direita, se não tiver nada a direita, imprime o valor
       postOrder(raiz->Esquerda); 
       postOrder(raiz->Direita);
       printf("%d ", raiz->x);
    }
}

void remover (nó **raiz, int n){
      if(*raiz == NULL){
        printf("Valor não está na arvore\n"); //Validação para ver se o valor esta na arvore
        return;}

      if (n < (*raiz)->x)                 //Preocurando o valor informado
        remover(&(*raiz)->Esquerda, n); 
     else if (n > (*raiz)->x)
        remover(&(*raiz)->Direita, n);
     else {                               //nó encontrado
        
         if((*raiz)->Esquerda == NULL && (*raiz)->Direita == NULL){ //se o nó a ser removido não tem nenhum filho
            free(*raiz);
            *raiz = NULL; }
         else if ((*raiz)->Direita == NULL){ //se o nó tiver um filho e o filho tiver a direita
            nó *aux = *raiz;                 //nó auxiliar para receber o nó a ser removido
            *raiz = (*raiz)->Esquerda;       //filho da esquerda assume o lugar do pai na arvore
            free(aux); }                     //nó removido
         else if ((*raiz)->Esquerda == NULL){ //se o nó tiver um filho e o filho tiver a esquerda
            nó *aux = *raiz;                  //mesma coisa, so que agora com o filho na direita
            *raiz = (*raiz)->Direita;         
            free(aux); }
         else {                               //se o nó tiver 2 filhos
            nó *aux = (*raiz)->Esquerda;      //nó auxiliar recebe o filho da esquerda para pecorrer a sub-arvore da esquerda
            while (aux->Direita) {            //preocura o valor mais a direita da sub-arvore da esquerda
                aux = aux->Direita; }               
                (*raiz)->x = aux->x;          //substitui o valor do nó que quer ser removido pelo seu sucessor in order
                remover(&(*raiz)->Esquerda, aux->x); } /*como o valor que foi removido agora assumiu o valor
                de seu sucessor, no momento tem 2 nó com o mesmo valor na arvore, então essa chamada recursiva
                remove o nó duplicado que é uma folha (o que torna mais simples de remover) que se encontra na sub-arvore da 
                esquerda*/
     }    
}

void liberarMemoria (nó *raiz){ //função de liberar memoria
     if (raiz == NULL)
        return;
     liberarMemoria(raiz->Esquerda);
     liberarMemoria(raiz->Direita);
     free(raiz);
}


