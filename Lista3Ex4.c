#include <stdio.h>
#define MAX 100

//Structs eletrodomesticos
typedef struct eletro{
	char nome [30];
	float potencia;
	float tempo;
}teletro;

//VARIAVEL GLOBAL
int qtd = 0;

//CARREGA ELETRO
void carregaEletro(teletro e[]){
	FILE *arq;
	int i;
	arq = fopen("consumo.txt","r"); // r = leitura
	if(arq==NULL){
		printf("Arquivo nao foi encontrado :(\n");
		return;
	}// fim if
	fscanf(arq,"%d",&qtd);
	printf("Carregando dados");
	for(i=0;i<qtd;i++){
		fscanf(arq,"%s",&e[i].nome);
		fscanf(arq,"%f",&e[i].potencia);
		fscanf(arq,"%f",&e[i].tempo);
		printf("...");// enfeite
		_sleep(500);// enfeite
	}// fim for
	fclose(arq);
	system("cls"); // enfeite
}

//SALVA ELETRO
void salvaEletro(teletro e[]){
	int i;
	FILE *arq;
	arq = fopen("consumo.txt","w"); // w = write
	fprintf(arq,"%d\n",qtd); // qtd é variável global da qtde de bandas cadastradas
	for(i=0;i<qtd;i++){
		fprintf(arq,"%s\n",e[i].nome);
		fprintf(arq,"%f\n",e[i].potencia);
		fprintf(arq,"%f\n",e[i].tempo);
	}
	printf("Dados salvos com sucesso :)\n");
	fclose(arq);
}

//ADICIONAR ELETRO
int addEletro(teletro e[]){
	
	if(qtd == MAX){ //veficar se tem espaço
		return 0;
	}	
	
	printf("Dados para o cadastro do eletrodomestico:\n");
	printf("Nome: ");
	fflush(stdin); //Limpa o buffer do teclado
	gets(e[qtd].nome);
	printf("Potencia: ");
	scanf("%f", &e[qtd].potencia);
	printf("Tempo: ");
	scanf("%f", &e[qtd].tempo);
	qtd++;
	return 1;
}

//BUSCAR ELETRO NOME
void buscaEletro (teletro e[], char nomeBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(e[i].nome), strupr(nomeBusca)) == 0){
			printf("Eletrodomestico %d\n", i + 1);
			printf("Nome: %s\n", e[i].nome);
			printf("Potencia: %f\n", e[i].potencia);
			printf("Tempo: %f\n", e[i].tempo);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Aluno nao encontrado!\n");
	}
}

//BUSCAR ELETRO POR VALOR
void buscaGasto (teletro e[], float x){
	int i, existe = 0;
	float gasto, p, t;
	for(i = 0; i < qtd; i++){
		p = e[i].potencia;
		t = e[i].tempo;
		gasto = p * t;
		if(gasto > x){
			printf("Eletrodomestico %d\n", i + 1);
			printf("Nome: %s\n", e[i].nome);
			printf("Potencia: %f\n", e[i].potencia);
			printf("Tempo: %f\n", e[i].tempo);
			printf("Gasto total: %f\n", gasto);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Eletrodomestico nao encontrada!\n");
	} 
}

//CALCULO DO GASTO MENSAL
void consumoEnergia (teletro e[], float x){
	int i, existe = 0;
	float gastoD, gastoM, p, t, valorD, valorM;
	for(i = 0; i < qtd; i++){
		p = e[i].potencia;
		t = e[i].tempo;
		gastoD = p * t;
		gastoM = gastoD * 30;
		valorD = gastoD * x;
		valorM = gastoM * x;
		printf("Eletrodomestico %d\n", i + 1);
		printf("Nome: %s\n", e[i].nome);
		printf("Potencia: %f\n", e[i].potencia);
		printf("Tempo: %f\n", e[i].tempo);
		printf("Gasto diario: %f kWh\n", gastoD);
		printf("Gasto mensal: %f kWh\n", gastoM);
		printf("Gasto diario: %f reais\n", valorD);
		printf("Gasto mensal: %f reais\n", valorM);
		existe = 1;
		printf("------------------------------------------\n");
			
	}
	if(!existe){
		printf("Eletrodomestico nao encontrada!\n");
	} 
}

//MENU
int menu(){
	int op;
	printf("Sistema de Controle de Consumo de Energia\n");
	printf("1 - Adicionar Eletrodomesticos\n");
	printf("2 - Busque o eletrodomestico pelo nome\n");
	printf("3 - Ver os eletrodomesticos que gastam mais\n");
	printf("4 - Ver consumo diario e mensal\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return op;
} 

// PROGRAMA PRINCIPAL
int main(){
	teletro e[MAX];
	char nome[30];
	int op, i;
	float aux;
	carregaEletro(e);
	do{
		op = menu();
		switch(op){
			case 1:
				if(addEletro(e) == 1){
					printf("Eletrodomestico adicionado\n");
				} else {
					printf("Limite de eletrodomesticos atingido\n");
				}
				break;
			case 2: 
				printf("Nome do Eletrodomestico:\n");
				fflush(stdin);
				gets(nome);
				buscaEletro(e, nome);
				break;
			case 3:
				printf("Digite um valor: ");
				scanf("%f", &aux);
				buscaGasto(e, aux);
				break;
			case 4:
				printf("Digite o valor em reais do kWh:\n ");
				scanf("%f", &aux);
				consumoEnergia(e, aux);
				break;
			case 0:
				salvaEletro(e);
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


