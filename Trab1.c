#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaracoes
float vet_num[30];
char posfixa[50];
void resolve();

//structs
typedef struct elemento{
	char dado;
	float dadof;
	struct  elemento * proximo;

}t_elemento;

typedef struct pilha{
	t_elemento * topo;

}t_pilha;

//funcoes
t_pilha * criarPilha(){ //inicia uma pilha vazia
	t_pilha * p =(t_pilha * )malloc(sizeof(t_pilha));
	p->topo=NULL;
	return p;
}

int estaVazia(t_pilha * p){ //retorna 0 para vazia e 1 para nao vazia
	if(p->topo==NULL){
		return 0;
	}
	else{
		return 1;
	}
}

void empilhaF(float dado, t_pilha * p){ //empilha um float
	t_elemento * novoElemento= (t_elemento *) malloc(sizeof(t_elemento));
	novoElemento->dadof=dado;
	if(p->topo==NULL){
		p->topo=novoElemento;
		p->topo->proximo=NULL;
	}
	else{
		novoElemento->proximo=p->topo;
		p->topo=novoElemento;		
	}

}
void empilhaC(char dado, t_pilha * p){ //empilha um char
	t_elemento * novoElemento= (t_elemento *) malloc(sizeof(t_elemento));
	novoElemento->dado=dado;
	if(p->topo==NULL){
		p->topo=novoElemento;
		p->topo->proximo=NULL;
	}
	else{
		novoElemento->proximo=p->topo;
		p->topo=novoElemento;		
	}

}
float desempilhaF(t_pilha * p){ //desempilha um float
	float retorno;
	t_elemento * removido;
	if(p->topo== NULL){
		return -1;
	}
	else{
		retorno=p->topo->dadof;
		removido=p->topo;
		p->topo=p->topo->proximo;
	}
	free(removido);
	return retorno;
}
char desempilhaC(t_pilha * p){ //desempilha um char
	char retorno;
	t_elemento * removido;
	if(p->topo== NULL){
		return -1;
	}
	else{
		retorno=p->topo->dado;
		removido=p->topo;
		p->topo=p->topo->proximo;
	}
	free(removido);
	return retorno;
}

int ehValida(t_pilha * p, char exp[]){ // retorna 1 para expressao valida e 0 para expressao invalida
	int caracter,i=0,r;
	while(exp[i] != '\0'){
		caracter=exp[i];
		if(caracter>=40 && caracter<=57 && caracter!=46 && caracter!= 44){ 
			if(caracter==40){ // (
				empilhaC('(',p); 
			}else if(caracter == 41){ // )
				r=desempilhaC(p);
				if(r==-1){
					return 0;
				}
			}
		}else{
			return 0;
		}
		i++;
	}
	caracter=exp[0];
	if(caracter>=42 && caracter<=45)return 0;
	caracter=exp[i-1];
	if(caracter>=42 && caracter<=45){
		return 0;
	}
	r=estaVazia(p);
	if(r==1){
		return 0;
	}else{
		return 1;
	}

}
int prioridade(char sinal){ // retorna 2 para operacoes de maior prioridade e 1 para operacoes de menor prioridade
	if(sinal=='+' || sinal=='-'){
		return 1;
	}
	else if(sinal=='/' || sinal=='*'){
		return 2;
	}
	return 0;
}
void guardarNumeros(char exp[]){
	int i=0,caracter,j=0,h=0;
	char aux[20];
	while(exp[i] != '\0'){
		caracter=exp[i];
		while(caracter>=48 && caracter<=57){ //0 a 9
			aux[j]=exp[i];
			j++;
			i++;
			caracter=exp[i];
		}
		if(j!=0){
			aux[j]='\0';
			vet_num[h]=atof(aux);
			h++;
			j=0;
		}
		i++;
	}
}
void posFixa(char exp[]){
	t_pilha * pilha=criarPilha();
	int i=0, caracter, j=0, prio_p, prio, p_vazia;
	char aux_pos;
	while(exp[i] !='\0'){
		caracter=exp[i];
		if(caracter>=48 && caracter<=57){
			posfixa[j]=exp[i];
			j++;
		}
		else{
			if(caracter==41){ // )
				aux_pos=desempilhaC(pilha);
				while(aux_pos!='('){
						posfixa[j]=aux_pos;
						j++;
					aux_pos=desempilhaC(pilha);
				}
			}
			else{
				if(caracter==40){ // (
					empilhaC(exp[i], pilha);
				}
				else{ // sinal
					do{
							p_vazia=estaVazia(pilha);
							if(p_vazia==1){
								prio_p=prioridade(pilha->topo->dado);
								prio=prioridade(exp[i]);
								if(prio_p>=prio){
									aux_pos=desempilhaC(pilha);
									posfixa[j]=aux_pos;
									j++;
								}
							}
							p_vazia=estaVazia(pilha);
							if(p_vazia==1){
								prio_p=prioridade(pilha->topo->dado);
								prio=prioridade(exp[i]);
							}

                    }while(p_vazia==1 && prio_p>=prio);
					empilhaC(exp[i],pilha);
				}
			}
		}
		i++;
	}
	p_vazia=estaVazia(pilha);
	while(p_vazia == 1){ // desmpilhaos sinais
		aux_pos=desempilhaC(pilha);
		posfixa[j]=aux_pos;
		j++;
		p_vazia=estaVazia(pilha);
	}
	posfixa[j]='\0';
	//printf("Expressao posfixa: %s\n",posfixa); //debug
	resolve();
}
int contDigitos(float valor){
	int count=0,valor_int;
	valor_int=valor;
	if(valor_int==0){
		count=1;
	}
	else{
		while(valor_int!= 0){
			count++;
			valor_int=valor_int/10;
		}
	}
	return count;
}
float calcular(float termo1, float termo2, char sinal){
	float resultado;
	switch(sinal){
		case '+' :
			resultado=termo1+termo2;
		break;
		case '-':
			resultado=termo1-termo2;
		break;
		case '*':
			resultado=termo1*termo2;
		break;
		case '/':
			resultado=termo1/termo2;
		break;
	}
	return resultado;
}
void resolve(){
	t_pilha * pilha=criarPilha();
	float termo1,termo2,aux_vet,resul;
	int i=0,j=0,caracter,count;
	while(posfixa[i] != '\0'){
		caracter=posfixa[i];
		if(caracter>=48 && caracter<=57){
			aux_vet=vet_num[j];
			empilhaF(aux_vet,pilha);
			count=contDigitos(aux_vet);
			i=count+i;
			j++;
		}
		else{
			termo2=desempilhaF(pilha);
			termo1=desempilhaF(pilha);
			resul=calcular(termo1,termo2,posfixa[i]);
			empilhaF(resul,pilha);
			i++;
		}
	}
	resul=desempilhaF(pilha);
	printf("Resultado =  %.1f \n", resul);
}
int main(){
	char exp[50];
	t_pilha * pilha=criarPilha();
	do{
		printf("Digite a expressao: ");
		scanf("%s", exp);
		if(ehValida(pilha,exp)==1){
			guardarNumeros(exp);
			posFixa(exp);
		}else{
			printf("Expressa invalida\n");
			break;
		}
	}while(ehValida(pilha,exp)!=1);
	return 0;
}