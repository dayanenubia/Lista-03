#include <stdio.h>
#define MAX 10

typedef struct livro{
	char titulo [30];
	char autor [15];
	int ano;
	int prateleira;
}tlivro;

//--------------------

int qtd = 0;

//----------------------

int addLivro(tlivro l[]){
	
	if(qtd == MAX){ //veficar se tem espaço
		return 0;
	}	
	
	printf("Dados para o livro:\n");
	printf("Titulo: ");
	fflush(stdin); //Limpa o buffer do teclado
	gets(l[qtd].titulo);
	fflush(stdin); //Limpa o buffer do teclado
	printf("Autor: ");
	gets(l[qtd].autor);
	printf("ano: ");
	scanf("%d", &l[qtd].ano);
	printf("Prateleira: ");
	scanf("%d", &l[qtd].prateleira);
	qtd++;
	return 1;
} 

//------------------------------------------------


void buscaLivro (tlivro l[], char tituloBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(l[i].titulo), strupr(tituloBusca)) == 0){
			printf("Livro %d\n", i + 1);
			printf("Titulo: %s\n", l[i].titulo);
			printf("Prateleira: %d\n", l[i].prateleira);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Livro nao encontrado!\n");
	}
} 

//-----------------------------------------------------

void mostraLivros (tlivro l[]){
	int i;
	printf("Livros cadastrados\n");
	for(i = 0; i < qtd; i++){
		printf("Livro %d\n", i + 1);
		printf("Titulo: %s\n", l[i].titulo);
		printf("Autor: %s\n", l[i].autor);
		printf("Ano: %d\n", l[i].ano);
		printf("Prateleira: %d\n", l[i].prateleira);
		printf("------------------------------------------\n");
	}
} 

//-----------------------------------------------------

void buscarAno (tlivro l[], int aux){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(l[i].ano > aux){
			printf("Livro %d\n", i + 1);
			printf("Titulo: %s\n", l[i].titulo);
			printf("Ano: %d\n", l[i].ano);
			existe = 1;
			printf("------------------------------------------\n");
		} 	
	}
	if(!existe){
		printf("Nao ha livro mais novo que o ano inserido!\n");
	}
} 

//-------------------------------------------------------------------

void salvaLivros(tlivro l[]){
	int i;
	FILE * arq;
	arq = fopen("Livros.txt", "w"); // w = write
	fprintf(arq, "%d\n", qtd); // qtd é uma variavel global
	for(i = 0; i < qtd; i++){
		fprintf(arq, "%s\n", l[i].titulo);
		fprintf(arq, "%s\n", l[i].autor);
		fprintf(arq, "%d\n", l[i].ano);
		fprintf(arq, "%d\n", l[i].prateleira);
	}
	printf("Dados salvos com sucesso\n");
	fclose(arq);
} 

//-------------------------------------------------------------

void carregaLivros(tlivro l[]){
	FILE * arq;
	int i;
	arq = fopen("Livros.txt", "r"); // r = read
	if(arq == NULL){
		printf("Arquivo nao foi encontrado\n");
		return;
	}
	fscanf(arq, "%d", &qtd);
	for(i = 0; i < qtd; i++){
		fscanf(arq, "%s", &l[i].titulo);
		fscanf(arq, "%s", &l[i].autor);
		fscanf(arq, "%d", &l[i].ano);
		fscanf(arq, "%d", &l[i].prateleira);
	}
	printf("Dados carregados com sucesso\n");
	fclose(arq);
} 

//-------------------------------------------------------------

int menu(){
	int op;
	printf("Sistema de Cadastro de Livros\n");
	printf("1 - Adicionar Livros\n");
	printf("2 - Busque um livro pelo o titulo\n");
	printf("3 - Ver todos os livros\n");
	printf("4 - Verificar livros apartir de um ano\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return op;
} 

//------------------------------------------------------------

int main(){
	tlivro l[MAX];
	char titulo[30];
	int op, i;
	carregaLivros(l);
	do{
		op = menu();
		switch(op){
			case 1:
				if(addLivro(l) == 1){
					printf("Livro adicionado\n");
				} else {
					printf("Limite de livros atingido\n");
				}
				break;
			case 2: 
				printf("Nome do livro:\n");
				fflush(stdin);
				gets(titulo);
				buscaLivro(l, titulo);
				break;
			case 3:
				mostraLivros(l);
				break;
			case 4:
				printf("Ano:\n");
				scanf("%d", &i);
				buscarAno(l, i);
				break;
			case 0:
				salvaLivros(l);
				printf("Saindo...\n");
				break;
			default: 
				printf("Opcao invalida\n");
		}
		getch(); // esperar digitar uma tecla
		system("cls");
	}while(op != 0); 
	
	return 0;
}
