#include <stdio.h>
#define MAX 100

//Structs aluno
typedef struct aluno{
	char nome [30];
	int matricula;
	float n1;
	float n2;
	float n3;
}taluno;

//VARIAVEL GLOBAL
int qtd = 0;

//ADICIONAR ALUNO
int addAluno(taluno a[]){
	
	if(qtd == MAX){ //veficar se tem espaço
		return 0;
	}	
	
	printf("Dados para o cadastro do aluno:\n");
	printf("Nome: ");
	fflush(stdin); //Limpa o buffer do teclado
	gets(a[qtd].nome);
	printf("Matricula: ");
	scanf("%d", &a[qtd].matricula);
	printf("Nota 1: ");
	scanf("%f", &a[qtd].n1);
	printf("Nota 2: ");
	scanf("%f", &a[qtd].n2);
	printf("Nota 3: ");
	scanf("%f", &a[qtd].n3);
	qtd++;
	return 1;
}

//BUSCAR ALUNO POR MATRICULA OU NOME
void buscaAluno (taluno a[], char nomeBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(a[i].nome), strupr(nomeBusca)) == 0){
			printf("Aluno %d\n", i + 1);
			printf("Nome: %s\n", a[i].nome);
			printf("Matricula: %d\n", a[i].matricula);
			printf("Nota 1: %f\n", a[i].n1);
			printf("Nota 2: %f\n", a[i].n2);
			printf("Nota 3: %f\n", a[i].n3);
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
	if(!existe){
		printf("Aluno nao encontrado!\n");
	}
}

//CARREGA ALUNOS
void carregaAluno(taluno a[]){
	FILE *arq;
	int i;
	arq = fopen("alunos.txt","r"); // r = leitura
	if(arq==NULL){
		printf("Arquivo nao foi encontrado :(\n");
		return;
	}// fim if
	fscanf(arq,"%d",&qtd);
	printf("Carregando dados");
	for(i=0;i<qtd;i++){
		fscanf(arq,"%s",&a[i].nome);
		fscanf(arq,"%d",&a[i].matricula);
		fscanf(arq,"%f",&a[i].n1);
		fscanf(arq,"%f",&a[i].n2);
		fscanf(arq,"%f",&a[i].n3);
		printf("...");// enfeite
		_sleep(500);// enfeite
	}// fim for
	fclose(arq);
	system("cls"); // enfeite
}


//SALVA ALUNOS
void salvaAluno(taluno a[]){
	int i;
	FILE *arq;
	arq = fopen("alunos.txt","w"); // w = write
	fprintf(arq,"%d\n",qtd); // qtd é variável global da qtde de bandas cadastradas
	for(i=0;i<qtd;i++){
		fprintf(arq,"%s\n",a[i].nome);
		fprintf(arq,"%d\n",a[i].matricula);
		fprintf(arq,"%f\n",a[i].n1);
		fprintf(arq,"%f\n",a[i].n2);
		fprintf(arq,"%f\n",a[i].n3);
	}
	printf("Dados salvos com sucesso :)\n");
	fclose(arq);
}

//BUSCAR ALUNO COM A MAIOR MEDIA GERAL
void mediaAluno (taluno a[]){
	int i, existe = 0, media, n1, n2,n3, mediaAtual = 0;
	for(i = 0; i < qtd; i++){
		n1 = a[i].n1;
		n2 = a[i].n2;
		n3 = a[i].n3;
		media = (n1 + n2 + n3) / 3;
		if(media > mediaAtual){
			printf("O aluno com maior media geral e: %s", a[i].nome);
			mediaAtual = media;
			existe = 1;
			printf("------------------------------------------\n");
		}	
	}
}

//MOSTRAR ALUNOS APROVADOS E REPROVADOS
void resultadoAluno (taluno a[]){
	int i, existe = 0, media, n1, n2,n3;
	for(i = 0; i < qtd; i++){
		n1 = a[i].n1;
		n2 = a[i].n2;
		n3 = a[i].n3;
		media = (n1 + n2 + n3) / 3;
		if(media > 6){
			printf("Aluno %s APROVADO\n", a[i].nome);
			existe = 1;
		} else {
			printf("Aluno %s REPROVADO\n", a[i].nome);
		}	
	}
}

//MOSTRAR ALUNOS
void mostraAlunos (taluno a[]){
	int i;
	printf("Alunos cadastrados\n");
	for(i = 0; i < qtd; i++){
		printf("Aluno %d\n", i + 1);
		printf("Nome: %s\n", a[i].nome);
		printf("Matricula: %d\n", a[i].matricula);
		printf("Nota 1: %f\n", a[i].n1);
		printf("Nota 2: %f\n", a[i].n2);
		printf("Nota 3: %f\n", a[i].n3);
		printf("------------------------------------------\n");
	}
} 

//REMOVE ALUNOS
void removeAluno (taluno a[], char nomeBusca[30]){
	int i, existe = 0;
	for(i = 0; i < qtd; i++){
		if(strcmp(strupr(a[i].nome), strupr(nomeBusca)) == 0){
			a[i] = a[qtd-1];
			qtd--;
			existe = 1;
		}	
	}
	if(!existe){
		printf("Aluno nao encontrada!\n");
	} else {
		printf("Aluno removida com sucesso!\n");
	}
}

//MENU
int menu(){
	int op;
	printf("Sistema de Cadastro de Alunos\n");
	printf("1 - Adicionar Alunos\n");
	printf("2 - Busque um aluno pela matricula ou nome\n");
	printf("3 - Ver o aluno com a maior media geral\n");
	printf("4 - Ver alunos aprovados e reprovados\n");
	printf("5 - Ver alunos\n");
	printf("6 - Remover alunos\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return op;
} 

// PROGRAMA PRINCIPAL
int main(){
	taluno a[MAX];
	char nome[30];
	int op, i;
	carregaAluno(a);
	do{
		op = menu();
		switch(op){
			case 1:
				if(addAluno(a) == 1){
					printf("Aluno adicionado\n");
				} else {
					printf("Limite de alunos atingido\n");
				}
				break;
			case 2: 
				printf("Nome do aluno:\n");
				fflush(stdin);
				gets(nome);
				buscaAluno(a, nome);
				break;
			case 3:
				mediaAluno(a);
				break;
			case 4:
				resultadoAluno(a);
				break;
			case 5:
				mostraAlunos(a);
				break;
			case 6:
				printf("Digite o nome do aluno:\n");
				fflush(stdin);
				gets(nome);
				removeAluno(a, nome);
				break;
			case 0:
				salvaAluno(a);
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


