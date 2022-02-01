#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 100

typedef struct e{
	char data[10];
	char pessoa[30];
	char emprestado [1];
}temprestimo;

typedef struct j{
	char titulo [30];
	char console [15];
	int ano;
	int ranking;
	struct e emprestimo;
}tjogo;

int qtd = 0;

void salvarJogos(tjogo j[]){
	int i;
	FILE * arq;
	arq = fopen("Jogos.txt", "w"); // w = write
	fprintf(arq, "%d\n", qtd); // qtd é uma variavel global
	for(i = 0; i < qtd; i++){
		fprintf(arq, "%s\n", j[i].titulo);
		fprintf(arq, "%s\n", j[i].console);
		fprintf(arq, "%d\n", j[i].ano);
		fprintf(arq, "%d\n", j[i].ranking);
		fprintf(arq, "%s\n", j[i].emprestimo.data);
		fprintf(arq, "%s\n", j[i].emprestimo.pessoa);
		fprintf(arq, "%s\n", j[i].emprestimo.emprestado);
	}
	printf("Dados salvos com sucesso\n");
	fclose(arq);
}

//-------------------------------------------------------------

void carregaJogos(tjogo j[]){
	FILE * arq;
	int i;
	arq = fopen("Jogos.txt", "r"); // r = read
	if(arq == NULL){
		printf("Arquivo nao foi encontrado\n");
		return;
	}
	fscanf(arq, "%d", &qtd);
	for(i = 0; i < qtd; i++){
		fscanf(arq, "%s\n", &j[i].titulo);
		fscanf(arq, "%s\n", &j[i].console);
		fscanf(arq, "%d\n", &j[i].ano);
		fscanf(arq, "%d\n", &j[i].ranking);
		fscanf(arq, "%s\n", &j[i].emprestimo.data);
		fscanf(arq, "%s\n", &j[i].emprestimo.pessoa);
		fscanf(arq, "%s\n", &j[i].emprestimo.emprestado);
	}
	printf("Dados carregados com sucesso\n");
	fclose(arq);
}

int addJogo(tjogo j[]){
	
	if(qtd == MAX){ //veficar se tem espaço
		return 0;
	}	
	
	printf("Dados para cadastrar o jogo:\n");
	printf("Titulo: ");
	fflush(stdin); //Limpa o buffer do teclado
	gets(j[qtd].titulo);
	fflush(stdin); //Limpa o buffer do teclado
	printf("Console: ");
	gets(j[qtd].console);
	printf("Ano: ");
	scanf("%d", &j[qtd].ano);
	printf("Ranking: ");
	scanf("%d", &j[qtd].ranking);
	qtd++;
	return 1;
}

void buscarJogo (tjogo j[], char tituloBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(j[i].titulo), strupr(tituloBusca)) == 0 || strcmp(strupr(j[i].console), strupr(tituloBusca)) == 0){
			printf("Jogo %d\n", i + 1);
			printf("Titulo: %s\n", j[i].titulo);
			printf("Console: %s\n", j[i].console);
			printf("ano: %d\n", j[i].ano);
			printf("Ranking: %d\n", j[i].ranking);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Jogo nao encontrada!\n");
	}
}

void emprestarJogo (tjogo j[], char tituloBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(j[i].titulo), strupr(tituloBusca)) == 0){
			printf("Data: ");
			fflush(stdin); //Limpa o buffer do teclado
			gets(j[i].emprestimo.data);
			fflush(stdin); //Limpa o buffer do teclado
			printf("Nome: ");
			gets(j[i].emprestimo.pessoa);
			j[qtd].emprestimo.emprestado[0] = 'S';
			existe = 1;
			printf("Emprestimo realizado com sucesso!\n");
		}	
	}
	if(!existe){
		printf("Jogo nao encontrado!\n");
	}
}

void devolverJogo (tjogo j[], char tituloBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(j[i].titulo), strupr(tituloBusca)) == 0){
			if(j[qtd].emprestimo.emprestado[0] == 'S'){
				j[qtd].emprestimo.emprestado[0] = 'N';
				existe = 1;
				printf("Jogo devolvido com sucesso!\n");
			} else {
				printf("Esse jogo não foi emprestado!\n");
				existe = 1;
			}
		}	
	}
	if(!existe){
		printf("Jogo nao encontrado!\n");
	}
}


void mostrarEmprestimos (tjogo j[]){
	int i, existe = 0;
	printf("Jogos emprestados!\n");
	for(i = 0; i < qtd; i++){
		if(j[qtd].emprestimo.emprestado[0] == 'S'){
			printf("O jogo: %s  ", j[i].titulo);
			printf("Foi emprestado para: %s\n", j[i].emprestimo.pessoa);
		} 
		existe = 1;
	}
	if(!existe){
		printf("Nenhum jogo foi emprestado!");
	}
}

int menu(){
	int op;
	printf("Sistema de Cadastro de jogos\n");
	printf("1 - Adicionar jogos\n");
	printf("2 - Procurar jogo pelo titulo ou console\n");
	printf("3 - realizar emprestimo do jogo\n");
	printf("4 - Devolver jogo\n");
	printf("5 - Ver jogos emprestados\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return op;
}

int main(){
	tjogo j[MAX];
	char titulo[30];
	int op, i;
	carregaJogos(j);
	do{
		op = menu();
		switch(op){
			case 1:
				if(addJogo(j) == 1){
					printf("Jogo adicionada\n");
				} else {
					printf("Limite de jogos atingido\n");
				}
				break;
			case 2: 
				printf("Nome do jogo ou console:\n");
				fflush(stdin);
				gets(titulo);
				buscarJogo(j, titulo);
				break;
			case 3:
				printf("Nome do jogo:\n");
				fflush(stdin);
				gets(titulo);
				emprestarJogo(j, titulo);
				break;
			case 4:
				printf("Nome do jogo:\n");
				fflush(stdin);
				gets(titulo);
				devolverJogo(j, titulo);
				break;
			case 5:
				mostrarEmprestimos(j);
				break;
			case 0:
				salvarJogos(j);
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
