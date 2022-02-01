#include <stdio.h>
#define MAX 10

typedef struct banda{
	char nome [40];
	char genero [40];
	int integrantes;
	int ranking;
}tbanda;

//---------------

int qtd = 0;

//-----------------------

int addBanda(tbanda b[]){
	
	if(qtd == MAX){ //veficar se tem espaço
		return 0;
	}	
	
	printf("Dados para banda:\n");
	printf("Nome: ");
	fflush(stdin); //Limpa o buffer do teclado
	gets(b[qtd].nome);
	fflush(stdin); //Limpa o buffer do teclado
	printf("Genero: ");
	gets(b[qtd].genero);
	printf("Integrantes: ");
	scanf("%d", &b[qtd].integrantes);
	printf("Ranking: ");
	scanf("%d", &b[qtd].ranking);
	qtd++;
	return 1;
}

//-----------------------------------------------

void mostraBandas (tbanda b[]){
	int i;
	printf("Bandas cadastradas\n");
	for(i = 0; i < qtd; i++){
		printf("Banda %d\n", i + 1);
		printf("Nome: %s\n", b[i].nome);
		printf("Genero: %s\n", b[i].genero);
		printf("Integrantes: %d\n", b[i].integrantes);
		printf("Ranking: %d\n", b[i].ranking);
		printf("------------------------------------------\n");
	}
}

//-----------------------------------------------------

void alteraBanda (tbanda b[], char nomeBusca[40]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(b[i].nome), strupr(nomeBusca)) == 0){
			printf("Novos dados para banda %s:\n", b[i].nome);
			printf("Novo nome: ");
			fflush(stdin); //Limpa o buffer do teclado
			gets(b[i].nome);
			fflush(stdin); //Limpa o buffer do teclado
			printf("Novo genero: ");
			gets(b[i].genero);
			printf("Novo integrantes: ");
			scanf("%d", &b[i].integrantes);
			printf("Novo Ranking: ");
			scanf("%d", &b[i].ranking);
			existe = 1;
			printf("Dados alterados\n");
		}	
	}
	if(!existe){
		printf("Banda nao encontrada!\n");
	}
}


//-----------------------------------------------------

void removeBanda (tbanda b[], char nomeBusca[40]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(b[i].nome), strupr(nomeBusca)) == 0){
			b[i] = b[qtd-1];
			qtd--;
			existe = 1;
		}	
	}
	if(!existe){
		printf("Banda nao encontrada!\n");
	} else {
		printf("Banda removida com sucesso!\n");
	}
}


//-----------------------------------------------------

void buscaGenero (tbanda b[], char generoBusca[40]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(b[i].genero), strupr(generoBusca)) == 0){
			printf("Banda %d\n", i + 1);
			printf("Nome: %s\n", b[i].nome);
			printf("Genero: %s\n", b[i].genero);
			printf("Integrantes: %d\n", b[i].integrantes);
			printf("Ranking: %d\n", b[i].ranking);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Banda nao encontrada!\n");
	}
}

//-----------------------------------------------------

void buscaRanking (tbanda b[], int aux){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(b[i].ranking == aux){
			printf("Banda %d\n", i + 1);
			printf("Nome: %s\n", b[i].nome);
			printf("Genero: %s\n", b[i].genero);
			printf("Integrantes: %d\n", b[i].integrantes);
			printf("Ranking: %d\n", b[i].ranking);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Banda nao encontrada!\n");
	} 
}

//-------------------------------------------------------------------

void buscarFavorita (tbanda b[], char favoritaBusca[40]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(b[i].nome), strupr(favoritaBusca)) == 0){
			if(b[i].ranking == 1 || b[i].ranking == 2 || b[i].ranking == 3){
				printf("A banda %s e uma das suas favoritas!\n", b[i].nome);
			} else {
				printf("A banda %s não e uma das suas favoritas!\n", b[i].nome);
			}
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Banda nao encontrada!\n");
	}
}

//-------------------------------------------------------------------

void buscarBanda (tbanda b[], char nomeBusca[40]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(b[i].nome), strupr(nomeBusca)) == 0){
			printf("Banda %d\n", i + 1);
			printf("Nome: %s\n", b[i].nome);
			printf("Genero: %s\n", b[i].genero);
			printf("Integrantes: %d\n", b[i].integrantes);
			printf("Ranking: %d\n", b[i].ranking);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Banda nao encontrada!\n");
	}
}

//=================================================================

void salvarBandas(tbanda b[]){
	int i;
	FILE * arq;
	arq = fopen("Bandas.txt", "w"); // w = write
	fprintf(arq, "%d\n", qtd); // qtd é uma variavel global
	for(i = 0; i < qtd; i++){
		fprintf(arq, "%s\n", b[i].nome);
		fprintf(arq, "%s\n", b[i].genero);
		fprintf(arq, "%d\n", b[i].integrantes);
		fprintf(arq, "%d\n", b[i].ranking);
	}
	printf("Dados salvos com sucesso\n");
	fclose(arq);
}

//-------------------------------------------------------------

void carregaBandas(tbanda b[]){
	FILE * arq;
	int i;
	arq = fopen("bandas.txt", "r"); // r = read
	if(arq == NULL){
		printf("Arquivo nao foi encontrado\n");
		return;
	}
	fscanf(arq, "%d", &qtd);
	for(i = 0; i < qtd; i++){
		fscanf(arq, "%s", &b[i].nome);
		fscanf(arq, "%s", &b[i].genero);
		fscanf(arq, "%d", &b[i].integrantes);
		fscanf(arq, "%d", &b[i].ranking);
	}
	printf("Dados carregados com sucesso\n");
	fclose(arq);
}

//-------------------------------------------------------------

int menu(){
	int op;
	printf("Sistema de Cadastro de Bandas Rock4u\n");
	printf("1 - Adicionar Bandas\n");
	printf("2 - Mostrar Bandas\n");
	printf("3 - Buscar Bandas\n");
	printf("4 - Remove banda\n");
	printf("5 - Altera banda\n");
	printf("6 - Busca por Genero\n");
	printf("7 - Busca por ranking\n");
	printf("8 - Buscar por banda favorita\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return op;
}

//------------------------------------------------------------

int main(){
	tbanda b[MAX];
	char nome[40];
	int op, i;
	carregaBandas(b);
	do{
		op = menu();
		switch(op){
			case 1:
				if(addBanda(b) == 1){
					printf("Banda adicionada\n");
				} else {
					printf("Limite de bandas atingido\n");
				}
				break;
			case 2: 
				mostraBandas(b);
				break;
			case 3:
				printf("Nome da banda:\n");
				fflush(stdin);
				gets(nome);
				buscarBanda(b,nome);
				break;
			case 4:
				printf("Nome da banda:\n");
				fflush(stdin);
				gets(nome);
				removeBanda(b,nome);
				break;
			case 5:
				printf("Nome da banda:\n");
				fflush(stdin);
				gets(nome);
				alteraBanda(b,nome);
				break;
			case 6:
				printf("Genero da banda:\n");
				fflush(stdin);
				gets(nome);
				buscaGenero (b,nome);
				break;
			case 7:
				printf("Ranking da banda:\n");
				scanf("%d", &i);
				buscaRanking (b,i);
				break;
			case 8:
				printf("Nome da banda:\n");
				fflush(stdin);
				gets(nome);
				buscarFavorita (b,nome);
				break;
			case 0:
				salvarBandas(b);
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
