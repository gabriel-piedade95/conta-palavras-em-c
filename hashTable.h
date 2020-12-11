#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define nam_max 256
#define tam_max 5000

typedef struct l_linhas{

	int linha;
	int conta;
	struct l_linhas * proxima;

}listaL;

typedef struct l_palavras{

	char * palavra;
	listaL * contagem;
	struct l_palavras * proxima;
	
}listaP;

typedef struct h_T{

	listaP * lista_p;

}*hash_Tab;

listaL * criaListaLigada();
listaP * criaListaPalavras();
int hash(char * palavra);
hash_Tab * criaTabela(void);
void insereFimListaLigada(listaL * inicio, int lin);
listaL * buscaListaLigada(listaL * inicio, int lin);
listaP * buscaListaPalavras(listaP * inicio, char * plv);
void insereFimListaPalavras(listaP * inicio, char * plv, int lin);
void insereTabela(hash_Tab * tabela, char * plv, int lin);
void imprimeListaPalavras(listaP * inicio);
void imprimeTabela(hash_Tab * tab);
void insereFimPalavraNo(listaP * inicio, listaP * nova);



