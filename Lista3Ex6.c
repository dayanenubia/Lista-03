#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 100

typedef struct n{
	char mes [10];
	int ano;
}tnascimento;

typedef struct g{
	char codigo [15], abate [1];
	float leite, alimento;
	struct n datanasc;
}tgado;

anoAtual = 2022;
qtd = 0;

//ADICIONAR GADO
int addGado(tgado g[]){
	
	if(qtd == MAX){ //veficar se tem espaço
		return 0;
	}	
	
	printf("Dados para o cadastro de gado:\n");
	printf("Codigo:\n ");
	fflush(stdin); //Limpa o buffer do teclado
	gets(g[qtd].codigo);
	printf("Litros de leite por semana:\n ");
	scanf("%f", &g[qtd].leite);
	printf("Quantidade de alimento por semana:\n ");
	scanf("%f", &g[qtd].alimento);
	printf("Data de nascimento - mes:\n ");
	fflush(stdin);
	gets(g[qtd].datanasc.mes);
	printf("Data de nascimento - ano:\n");
	scanf("%d", &g[qtd].datanasc.ano);
	
	int idade = anoAtual - g[qtd].datanasc.ano;
	
	if(idade > 5 || g[qtd].leite < 40){
		g[qtd].abate[0] = 's';
	} else {
		g[qtd].abate[0] = 'n';
	}
	
	printf("Abate: %s\n", g[qtd].abate);
	
	qtd++;
	return 1;
}

void mostraGado (tgado g[]){
	int i;
	printf("Gado cadastrados\n");
	for(i = 0; i < qtd; i++){
		printf("Gado %d\n", i + 1);
		printf("Codigo: %s\n", g[i].codigo);
		printf("Litros de leite por semana: %f\n", g[i].leite);
		printf("Quantidade de alimento por semana: %f\n", g[i].alimento);
		printf("Data de nascimento: %s%d\n", g[i].datanasc.mes, g[i].datanasc.ano);
		printf("Abate: %s\n", g[i].abate);
		printf("------------------------------------------\n");
	}
} 

float mostraLeite (tgado g[]){
	int i;
	float total = 0;
	for(i = 0; i < qtd; i++){
		total += g[i].leite;
	}
	printf("total de leite %f", total);
} 

float mostraAlimento (tgado g[]){
	int i;
	float total = 0;
	for(i = 0; i < qtd; i++){
		total += g[i].alimento;
	}
	printf("total de alimento %f", total);
}

void carregaGado(tgado g[]){
	FILE *arq;
	int i;
	arq = fopen("gado.txt","r"); // r = leitura
	if(arq==NULL){
		printf("Arquivo nao foi encontrado :(\n");
		return;
	}// fim if
	fscanf(arq,"%d",&qtd);
	printf("Carregando dados");
	for(i=0;i<qtd;i++){
		fscanf(arq,"%s",&g[i].codigo);
		fscanf(arq,"%f",&g[i].leite);
		fscanf(arq,"%f",&g[i].alimento);
		fscanf(arq,"%s",&g[i].datanasc.mes);
		fscanf(arq,"%d",&g[i].datanasc.ano);
		printf("...");// enfeite
		_sleep(500);// enfeite
	}// fim for
	fclose(arq);
	system("cls"); // enfeite
}

//SALVA ELETRO
void salvaGado(tgado g[]){
	int i;
	FILE *arq;
	arq = fopen("gado.txt","w"); // w = write
	fprintf(arq,"%d\n",qtd); // qtd é variável global da qtde de bandas cadastradas
	for(i=0;i<qtd;i++){
		fprintf(arq,"%s", g[i].codigo);
		fprintf(arq,"%f", g[i].leite);
		fprintf(arq,"%f", g[i].alimento);
		fprintf(arq,"%s", g[i].datanasc.mes);
		fprintf(arq,"%d", g[i].datanasc.ano);
	}
	printf("Dados salvos com sucesso :)\n");
	fclose(arq);
}

//MENU
int menu(){
	int op;
	printf("Sistema de Controle de Gado\n");
	printf("1 - Adicionar gado\n");
	printf("2 - Animais cadastrado\n");
	printf("3 - Leite produzido por semana\n");
	printf("4 - Alimento ingerido na semana\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return op;
} 

int main(){
	tgado g[MAX];
	char nome[30];
	int op, i;
	float aux;
	carregaGado(g);
	do{
		op = menu();
		switch(op){
			case 1:
				if(addGado(g) == 1){
					printf("Gado adicionado\n");
				} else {
					printf("Limite de gado atingido\n");
				}
				break;
			case 2: 
				mostraGado(g);
				break;
			case 3:
				mostraLeite(g);
				break;
			case 4:
				mostraAlimento(g);
				break;
			case 0:
				salvaGado(g);
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
