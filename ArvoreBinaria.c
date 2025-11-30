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
        (*raiz)->x = n;
        (*raiz)->Esquerda = NULL;
        (*raiz)->Direita = NULL;
        return;}
     
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
            nó *aux = *raiz;
            *raiz = (*raiz)->Esquerda;
            free(aux); }
         else if ((*raiz)->Esquerda == NULL){ //se o nó tiver um filho e o filho tiver a esquerda
            nó *aux = *raiz;
            *raiz = (*raiz)->Direita;
            free(aux); }
         else { //se o nó tiver 2 filhos
            nó *aux = (*raiz)->Esquerda;
            while (aux->Direita) {
                aux = aux->Direita; }
                (*raiz)->x = aux->x;
                remover(&(*raiz)->Esquerda, aux->x);
         }
     }    
}
