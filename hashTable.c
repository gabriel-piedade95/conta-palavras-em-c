#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashTable.h"

listaL * criaListaLigada(){
	listaL * inicio = NULL;
	inicio = (listaL*) malloc(sizeof(listaL));
	inicio->conta = 1;
	inicio->linha = 0;
	inicio->proxima = NULL;
}

listaP * criaListaPalavras(){
	listaP * inicio = NULL;
	inicio = (listaP*) malloc(sizeof(listaP));
	inicio->palavra = "";
	inicio->contagem = NULL;
	inicio->proxima = NULL;
}

int hash(char * palavra){

	int i = 0;
	unsigned long aux = 0;
	for(i; i < strlen(palavra); i++){
		aux = palavra[i] + (aux*23); 
	}
	return(aux % tam_max);
}

hash_Tab * criaTabela(void){
	hash_Tab * tabela;
	int i = 0;
	tabela = (hash_Tab*) malloc(tam_max * sizeof(hash_Tab));

	for(i; i < tam_max; i++){
		tabela[i] = malloc(sizeof(hash_Tab));
		tabela[i]->lista_p = NULL;
	}	
	return(tabela);
}

void insereFimListaLigada(listaL * inicio, int lin){

	listaL * aux = inicio;
	listaL * nova = (listaL*)malloc(sizeof(listaL));
	while(aux->proxima != NULL){
		aux = aux->proxima;
	}
	aux->proxima = nova; 
	nova->linha = lin;
	nova->conta = 1;
	nova->proxima = NULL;
}

void insereFimListaPalavras(listaP * inicio, char * plv, int lin){
	
	listaP * aux = inicio;
	listaP * nova = (listaP*)malloc(sizeof(listaP));

	while(aux->proxima != NULL){
		aux = aux->proxima;
	}
	aux->proxima = nova;
	nova->palavra = plv;
	nova->contagem = criaListaLigada();
	nova->contagem->linha = lin;
	nova->proxima = NULL;

}

void insereFimPalavraNo(listaP * inicio, listaP * nova){
	listaP * aux = inicio;
	while(aux->proxima != NULL){
		aux = aux->proxima;
	}
	aux->proxima = nova;
}

listaL * buscaLinha(listaL * inicio, int lin){
	if(inicio == NULL || inicio->linha == lin){
		return(inicio);
	}
	return(buscaLinha(inicio->proxima, lin));
}

listaP * buscaPalavra(listaP * inicio, char * plv){
	if(inicio == NULL || strcmp(inicio->palavra,plv) == 0){
		return(inicio);
	}
	return(buscaPalavra(inicio->proxima, plv));
}

void insereTabela(hash_Tab * tabela, char * plv, int lin){

	int pos = hash(plv);
	listaP * nova = criaListaPalavras();
	if(tabela[pos]->lista_p == NULL){
		nova->palavra = plv;
		nova->contagem = criaListaLigada();
		nova->contagem->linha = lin;
		tabela[pos]->lista_p = nova;
	}
	else{
		if(buscaPalavra(tabela[pos]->lista_p, plv) == NULL){
			insereFimListaPalavras(tabela[pos]->lista_p, plv, lin);
		} 
		else{
			if(buscaLinha(buscaPalavra(tabela[pos]->lista_p, plv)->contagem, lin) == NULL){
				insereFimListaLigada(buscaPalavra(tabela[pos]->lista_p, plv)->contagem, lin);
			}
			else{
				buscaLinha(buscaPalavra(tabela[pos]->lista_p, plv)->contagem, lin)->conta++;
			}
		}
	}
	
}

void imprimeListaLigada(listaL * inicio){
	if(inicio != NULL){
		if(inicio->conta == 1){
			printf(" %d ", inicio->linha);
			imprimeListaLigada(inicio->proxima);
		}
		else{
			printf(" %d(%d)", inicio->linha, inicio->conta);
			imprimeListaLigada(inicio->proxima);
		}	
	} 
	else{
		printf("\n");
	}
}

void imprimeListaPalavras(listaP * inicio){
	
	if(inicio != NULL){
		
		printf("%s: ", inicio->palavra);
		
		imprimeListaLigada(inicio->contagem);
		if(inicio->proxima != NULL){
			imprimeListaPalavras(inicio->proxima);
		}
	} else {
		printf("\n");
	}
}

void imprimeTabela(hash_Tab * tab){
	int i = 0;
	for(i; i < tam_max; i++){
		imprimeListaPalavras(tab[i]->lista_p);
	}
}

