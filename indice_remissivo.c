#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashTable.h"

char texto[50000][100];
char nome[100000];

int ehLetra(char letra){
	char * pontuacao = "!@#$%*()_-+='\\|,<.>;:´`{[/°?}]º\"";
	int i = 0;
	if(letra == ' ' || letra == '\n' || letra == '\t'){
		return (0);
	}
	for(i; i < strlen(pontuacao); i++){
		if(letra == pontuacao[i]){
			return(0);
		}
	}
	return(1);
}

void leTexto(hash_Tab * tab){

	printf("Digite o nome do arquivo: ");
	scanf("%s", nome);

	FILE* arq;
	char letra;
	int p;
	int l;

	arq = fopen(nome, "r");

	if(arq == 0) {
		printf("Não foi encontrado o arquivo: %s\n", nome);
		//fclose(arq);
	}
	
	letra = getc(arq);
	p = 0;
	l = 0;
	int nova = 1;
	int linha = 0;
	while(!feof(arq)){
		if(ehLetra(letra)){
			if(nova == 0){
				nova = 1;
				insereTabela(tab, texto[p], linha);
				p++;
			}
			texto[p][l] = letra;		
			l++;
		} else if(letra == '-' && nova == 1) {
				nova = 2;
				texto[p][l] = letra;
				l++;
		} else{
			if(texto[p][l-1] == '-'){
				texto[p][l-1] = '\0';
			}
				nova = 0;
				l = 0;
			}
		if(letra == '\n'){
			linha++;
		}
		letra = getc(arq);
	}
	insereTabela(tab, texto[p], linha);
	fclose(arq);
	
	printf("%d\n", p);				
}

listaP * puxaListaPalavras(hash_Tab * tabela){

	int i = 0;
	listaP * nova = (listaP*)malloc(sizeof(listaP));
	nova = NULL;
	for(i; i < tam_max; i++){
		if(tabela[i]->lista_p != NULL){
			if(nova == NULL){
				nova = tabela[i]->lista_p;
			}
			else{
				insereFimPalavraNo(nova, tabela[i]->lista_p);
			}
		}
	}
	return(nova);
}

int comaparaPalavras(char * plv1, char * plv2){
	if(strcmp(plv1, plv2) == 0){
		return(0);
	}
}

void divideListaPalavras(listaP * inicio, listaP **a, listaP **b){

	listaP * rapido = (listaP*)malloc(sizeof(listaP));
	listaP * lento = (listaP*)malloc(sizeof(listaP));

	lento = inicio;
	rapido = inicio->proxima;

	while(rapido != NULL){
		
		rapido = rapido->proxima;

		if(rapido != NULL){
			lento = lento->proxima;
			rapido = rapido->proxima;
		}
	}

	*a = inicio;
	*b = lento->proxima;
	lento->proxima = NULL;

}

listaP * merge(listaP * a, listaP * b){

	listaP * aux = (listaP*)malloc(sizeof(listaP));

	if(a == NULL){
		return(b);
	}
	if(b == NULL){
		return(a);
	}

	if(strcmp(a->palavra, b->palavra) <= 0){
		aux = a;
		aux->proxima = merge(a->proxima, b);
	}
	else{
		aux = b;
		aux->proxima = merge(a, b->proxima);
	}

	return(aux);
}

void mergeSort(listaP ** inicio){

	listaP * aux = *inicio;
	listaP * a = (listaP*)malloc(sizeof(listaP));
	listaP * b = (listaP*)malloc(sizeof(listaP));

	if(aux == NULL  || aux->proxima == NULL){
		return;
	}

	divideListaPalavras(aux, &a, &b);
	mergeSort(&a);
	mergeSort(&b);

	*inicio = merge(a, b);
}

int main(){

	hash_Tab * tab = criaTabela();
	leTexto(tab);
	listaP * plvs = puxaListaPalavras(tab);
	mergeSort(&plvs);
	imprimeListaPalavras(plvs);

	return(0);
}