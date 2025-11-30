#include <stdio.h>
#include <stdlib.h>

typedef struct Nó{
    int x;
    struct Nó *Esquerda;
    struct Nó *Direita;
}nó;

void Inserir (nó **raiz, int n );
void busca (nó *raiz, int n);

int main (){
      
    int escolha, n;
    nó *raiz = NULL;

    do
    {
        printf("\n\n1.Inserir Valor\n2.Buscar Valor\n3.Busca\n4.Listagem\n0.Sair\n\n");
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
            
              break;
        case 4:
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
        printf("Valor Já existe na arvore"); //Caso seja um valor que ja está na arvore, nada é inserido
        return; } 
    } 

void busca (nó *raiz, int n){
     if (raiz == NULL){
        printf("\nValor não se encontra na arvore\n");
        return;
     }
     if (raiz->x == n){
         printf("\nO valor se encontra na arvore\n");
         return;
     }
     
     if (n < raiz->x) 
         busca(raiz->Esquerda, n);
     else if (n > raiz->x) 
         busca(raiz->Direita, n);
}
