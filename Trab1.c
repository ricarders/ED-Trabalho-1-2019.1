#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//para char
typedef struct elementoc { 
	char dadoc;
	struct elementoc *proximo;
}t_elementoc;

typedef struct listac {
	t_elementoc *primeiro;
	t_elementoc *ultimo;
}t_listac;

typedef struct pilhac {
	t_listac *l;
}t_pilhac;

t_listac *crialistac() {
    t_listac * l= (t_listac *)malloc(sizeof(t_listac));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}
void insereNoInicioc(char valor, t_listac *l) {
    t_elementoc * novoprimeiro = (t_elementoc *)malloc(sizeof(t_elementoc));
    novoprimeiro->dadoc = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL)
        l->ultimo = novoprimeiro;
}

int removeDoInicioc(t_listac *l) {
    if(estaVaziac(l))
        return -1;
    int t = l->primeiro->dadoc;
    t_elementoc * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL) 
       l->ultimo = NULL;
    return t;
}

int estaVaziac(t_listac *l) {
    if(l->primeiro == NULL)
       return 1;
    return 0;
}

t_pilhac * criapilhac() {
    t_pilhac * p =  (t_pilhac *)malloc(sizeof(t_pilhac));
    p->l = crialistac();
    return p;
}
void empilharc(char valor,t_pilhac *p) {
    insereInicioc(valor, p->l);
}
char desempilharc(t_pilhac *p) {
    return removeInicioc(p->l);
}
int estaVaziaPilhac(t_pilhac *p) {
    return estaVaziac(p->l);
}

//para float
typedef struct elementof { 
	float dado;
	struct elementof *proximo;
}t_elementof;
typedef struct listaf {
	t_elementof *primeiro;
	t_elementof *ultimo;
}t_listaf;
typedef struct pilhaf {
	t_listaf *l;
}t_pilhaf;

t_listaf * criaListaf() {
    t_listaf * l = (t_listaf *)malloc(sizeof(t_listaf));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}
void insereNoIniciof(float valor, t_listaf *l) {
    t_elementof * novoprimeiro = (t_elementof *)malloc(sizeof(t_elementof));
    novoprimeiro->dado = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL) {
        l->ultimo = novoprimeiro;
    }
}
int estaVaziaf(t_listaf *l) {
    if(l->primeiro == NULL)
       return 1;
    return 0;
}
float removeDoIniciof(t_listaf * l) {
    if(estaVaziaf(l))
        return -1;
    float tmp = l->primeiro->dado;
    t_elementof * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL)
       l->ultimo = NULL;
    return tmp;
}
t_pilhaf * criaPilhaf() {
    t_pilhaf * p =  (t_pilhaf *)malloc(sizeof(t_pilhaf));
    p->l = criaListaf();
    return p;
}
void empilharf(float valor, t_pilhaf *p) {
    insereIniciof(valor, p->l);
}
float desempilharf(t_pilhaf * p) {
    return removeIniciof(p->l);
}
int estaVaziaPilhaf(t_pilhaf * p) {
    return estaVaziaf(p->l);
}