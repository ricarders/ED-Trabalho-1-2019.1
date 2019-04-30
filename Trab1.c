#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Structs

typedef struct pilha{
    char dado;
    int dado2;
    struct pilha* prox;
}Pilha;

typedef struct header{
    Pilha* inicio;
    int tamanho;
}Header;

//Funcoes

void criapilha (Header *p){
    p->inicio = NULL;
    p->tamanho = 0;
}

int estavazia(Header *p){
    if(p->inicio == NULL){
        return 1;
    }
    return 0;
}

int filaestavazia(Header *p){
    if(p->inicio == NULL){
        return 1;
    }
    return 0;
}


int empilha(char a, int b, Header *p){
    Pilha* topo = (Pilha *)malloc(sizeof(Pilha));
    topo->dado = a;
    topo->dado2 = b;
    topo->prox = p->inicio;
    
    p->inicio = topo;
    p->tamanho++;
    return 0;
}

int criafila(Header *p){
    p->inicio = NULL;
    p->tamanho = 1;
    return 0;
}

int enfileira(char a, int b, Header *p){
    Pilha* ini = (Pilha *)malloc(sizeof(Pilha));
    ini->dado = a;
    ini->dado2 = b;
    ini->prox = NULL;
    int i = 1;
    Pilha *aux = p->inicio;
    while(i < p->tamanho){
        aux = aux->prox;
        i++;
    }
    if(p->inicio != NULL){
    aux->prox = ini;
    p->tamanho++;
    }else{
        p->inicio = ini;
    }
    return 0;
}

char desenfileirachar (Header *p){
    if(filaestavazia(p)){
        return 0;
    }
    char aux = p->inicio->dado;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
    return aux;
}

int desenfileiraint (Header *p){
    if(filaestavazia(p)){
        return 0;
    }
    int aux = p->inicio->dado2;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
    if(p->tamanho == 0){
        p->inicio = NULL;
    }
    return aux;
}

char desempilhachar (Header *p){
    if(estavazia(p)){
        return 0;
    }
    char aux = p->inicio->dado;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
        if(p->tamanho == 0){
            p->inicio = NULL;
        }
    return aux;
}

int desempilhaint (Header *p){
    if(estavazia(p)){
        return 0;
    }
    int aux = p->inicio->dado2;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
    if(p->tamanho == 0){
        p->inicio = NULL;
    }
    return aux;
}

int liberapilha (Header *p){
    if(estavazia(p)){
        free(p);
        return 0;
    }
    while(p->tamanho > 0){
        Pilha* aux = p->inicio;
        p->inicio = p->inicio->prox;
        free(aux);
        p->tamanho--;
    }
    free(p);
    
    return 0;
}

int converte(char a){
    int x;
    
    x=a-'0';
    return x;
}

//main

int main(){
    char entrada[100];
    int i = 0;
    
    printf("Digite a expressao:");

    scanf("%c", &entrada[i]);
    while(entrada[i] != '\n'){
        i++;
        scanf("%c", &entrada[i]);
    }
    
    Header* head = (Header *)(malloc(sizeof(Header)));
    
    criapilha(head);
      
    for(int k = 0; k < i; k++){
        if(entrada[k] == '('){
            empilha(entrada[k], 0, head);
        }

        else if(entrada[k] == ')'){
            if(head->inicio == NULL || head->inicio->dado != '('){
                printf("Expressao invalida\n");
                return 0;
            }

            else{
                desempilhachar(head);
            }
        }
    }

    if(estavazia(head) == 0){
        liberapilha(head);
        printf("Expressao invalida\n");
        return 1;
    }
free(head);

Header* header = (Header *)(malloc(sizeof(Header)));
    
criapilha(head);
    
Header* fila = (Header *)malloc(sizeof(Header));

criafila(fila);
    
    int s = 0, numf = 0;
    
    for(int k = 0; k < i; k++){
        
        if (entrada[k] == '('){
            empilha(entrada[k], 0, header);
            numf = 0;
        }
        
        else if(entrada[k] == '+'|| entrada[k] == '-'){
            if(header->inicio != NULL){
                if(header->inicio->dado == '+' || header->inicio->dado == '-' || header->inicio->dado == '*' || header->inicio->dado == '/'){
                    while(header->tamanho > 0){
                    enfileira(desempilhachar(header), 0, fila);
                    }
                    }
                }
            empilha(entrada[k], 0, header);
            numf = 0;
        }
        else if(entrada[k] == '*' || entrada[k] == '/'){
            if(header->inicio != NULL){
            if(header->inicio->dado == '*'|| header->inicio->dado == '/'){
                enfileira(desempilhachar(header), 0, fila);
                }
            }
            empilha(entrada[k], 0, header);
            numf = 0;
        }
        
        else if(entrada[k] == ')'){
                while(header->inicio->dado != '('){
                    enfileira(desempilhachar(header), 0, fila);
                }
                desempilhachar(header);
            numf = 0;
        }
        
        else{
            while(entrada[k] == '1'|| entrada[k] == '2'|| entrada[k] == '3'|| entrada[k] == '4'|| entrada[k] == '5'|| entrada[k] == '6' || entrada[k] == '7'|| entrada[k] == '8'|| entrada[k] == '9'|| entrada[k] == '0'){
                s++;
                k++;
            }
            while(s > 0){
            numf+=(converte(entrada[k-s]))*pow(10,s-1);
                s--;
            }
            k--;
            enfileira(0, numf, fila);
        }
        
    }
    while(header->inicio != NULL){
         enfileira(desempilhachar(header), 0, fila);
    }
    
    
    free(header);
    
    Header* calculo = (Header *)malloc(sizeof(Header));
    criapilha(calculo);
    int x, z;
    
    while(fila->tamanho > 0){
        
        if(fila->inicio->dado == 0){
            empilha(0, desenfileiraint(fila), calculo);
        }else{
            
            if(fila->inicio->dado == '+'){
                x = desempilhaint(calculo);
                z = desempilhaint(calculo);
                z = z + x;
                empilha(0, z, calculo);
                desenfileirachar(fila);
            }
            
            else if(fila->inicio->dado == '-'){
                x = desempilhaint(calculo);
                z = desempilhaint(calculo);
                z = z - x;
                empilha(0, z, calculo);
                desenfileirachar(fila);
            }
            
            else if(fila->inicio->dado == '*'){
                x = desempilhaint(calculo);
                z = desempilhaint(calculo);
                z = z * x;
                empilha(0, z, calculo);
                desenfileirachar(fila);
            }
            
            else if(fila->inicio->dado == '/'){
                x = desempilhaint(calculo);
                z = desempilhaint(calculo);
                z = z / x;
                empilha(0, z, calculo);
                desenfileirachar(fila);
            }
        }
    }

    printf("Resultado: %d\n", desempilhaint(calculo));
    
    return 0;
}