#include <stdio.h>
#include <stdlib.h>

typedef struct Nó{
    int x;
    struct Nó *Esquerda;
    struct Nó *Direita;
    int altura;
}nó;

//funções novas implementadas: CriaNó, Altura, maiorNó, AlturaNó,FB, rotaçãoDir/Esq/Duplas.

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
   nó *novo = malloc(sizeof(nó));
   
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
//recebe duas alturas de dois nó e retorna o maior
int maiorNó (int nóA, int nóB){ 
if (nóA > nóB) 
    return nóA;
else 
    return nóB;
}

int Altura (nó *raiz){ //Função para calcular a altura da arvore
    if(raiz == NULL){
        return -1;
    }
    else{
        int left =  Altura(raiz->Esquerda);  
        int right = Altura(raiz->Esquerda);  
        if (left > right)                   
           return left + 1;
        else 
           return right + 1;
    } 
}

int AlturaNó (nó *nó){
    if (nó == NULL)
        return -1;
    else 
       return nó->altura;
}

int FB (nó *nó){ 
    if(nó) //fator de balanceamento (FB) = altura da esquerda - altura da direita. 
       return AlturaNó(nó->Esquerda) - AlturaNó(nó->Direita); 
    else 
       return 0;
}

nó *rotaçãoEsq(nó *raiz){ 
    nó *y, *x;

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
    nó *y, *x;

    y = raiz->Esquerda;
    x = y->Direita;

    y->Direita = raiz;
    raiz->Esquerda = x;

    raiz->altura = maiorNó(AlturaNó(raiz->Esquerda), AlturaNó(raiz->Direita)) + 1;
    y->altura = maiorNó(AlturaNó(y->Esquerda), AlturaNó(y->Direita)) + 1;

    return y;
}
//rotação direita esquerda ou dupla esquerda
nó *rotaçãoDirEsq (nó *raiz) {
    raiz->Direita = rotaçãoDir(raiz->Direita);
    return rotaçãoEsq(raiz);
}
//rotação direita esquerda ou dupla direita
nó *rotaçãoEsqDir (nó *raiz){
    raiz->Esquerda = rotaçãoDir(raiz->Esquerda);
    return rotaçãoDir(raiz);
}

void Inserir (nó **raiz, int n) {
    
    if(*raiz == NULL){     //caso ache um espaço "vazio", cria o novo nó
         criarNó(n);
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
                remove o nó duplicado que é ou uma folha ou um pai com apenas 1 filho na esquerda (
                o que torna mais simples de remover), que se encontra na sub-arvore da  esquerda*/
     }    
}

void liberarMemoria (nó *raiz){ //função de liberar memoria
     if (raiz == NULL)
        return;
     liberarMemoria(raiz->Esquerda);
     liberarMemoria(raiz->Direita);
     free(raiz);
}

