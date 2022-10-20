#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 200

struct Aluno{
	char nome[MAX];
	char email[MAX];
	char telefone[MAX];
};

struct Matricula{
	int num;
	float coe;
	struct Aluno dados;	
};


int pesquisar(struct Matricula *n, int tam, int pesq){
	int i;
	for (i=0; i < tam; i++) {
		if ( n[i].num == pesq ){
			return i;	
		}  
	}
	return -1;  
}

int menu(){
	int op;
	printf("\nSISTEMA ACADÊMICO\n");
	printf("1 - Inserir Aluno\n");
    printf("2 - Pesquisar por Matrícula\n");
    printf("3 - Atualizar\n");
    printf("4 - Maior Coeficiente\n");
    printf("5 - Excluir Aluno\n");
    printf("6 - Listar\n");
    printf("7 - Pesquisar por Nome\n");
    printf("8 - Quick Sort\n");
    printf("9 - Insertion Sort\n");
    printf("0 - Sair\n");
    
    printf("Escolha sua opcao:");
    scanf("%d",&op);
    
    return op;
}

void trocar(struct Matricula *mat, long int i, long int f){
	
	struct Matricula aux;
    aux = mat[i];
    mat[i] = mat[f];
    mat[f]= aux;
}

int particao(struct Matricula *mat, int ini, int fim){
	
	struct Matricula pivo;
	pivo = mat[ini];
	int i, f;

	i = ini + 1;
	f = fim;

	while ( i <= f ) {
		if (strcmp(mat[i].dados.nome,pivo.dados.nome) < 0){
			i++;
		} else if (strcmp(mat[f].dados.nome,pivo.dados.nome) > 0) {
			f--;
		} else {
			trocar(mat,i,f);
			i++;
			f--;
		}
	}
	trocar(mat,ini,f);
	return f;

}


void quickSort(struct Matricula *mat, int ini, int fim){

	int posPivo;  

	if ( ini < fim ) {
		posPivo = particao(mat,ini,fim);
		quickSort(mat,ini,posPivo-1);
		quickSort(mat,posPivo+1,fim);

	}

}

void insertSort(struct Matricula *mat, int n){
 	int i, k;	// Elemento a ser inserido
    struct Matricula elem;
 	
 	for ( i = 1; i < n; i++) {
 		elem= mat[i];
 		k = i - 1;
		while ( ( k >= 0 ) && (strcmp (mat[k].dados.nome,elem.dados.nome) > 0) )  {
			// TROCAR 
			mat[k+1] = mat[k];			
			k--;
		}
		mat[k+1] = elem;
	}
 	
}


int pesquisarNome(struct Matricula *n, int tam, char pesq[]){
	int i;
	for (i=0; i < tam; i++) {
		if ( strcmp(n[i].dados.nome,pesq) == 0 ){
			return i;	
		}  
	}
	return -1;  
}

void listar(struct Matricula *nu,int *tam){
	int i;
	for(i = 0; i < *tam; i++){
		if (nu[i].num != 0){
			printf("\nNome: %s  \nTelefone: %s  \nE-mail: %s  \nMatricula: %d  \nCoeficiente: %.2f\n",nu[i].dados.nome,nu[i].dados.telefone,nu[i].dados.email, nu[i].num,nu[i].coe);
		}
		
	}
	
}

int lerVetor (struct Matricula *coef, int *tam) {
	int n;
	float rendimento;
	int pesq;
	char name[MAX];
	char telefone[MAX];
	char email[MAX];
	
		printf("Digite seu nome:");
		scanf (" %199[^\n]s",name);
		strcpy(coef[*tam].dados.nome,name);
		
		printf("\nDigite seu telefone:");
		scanf (" %199[^\n]s",telefone);
		strcpy(coef[*tam].dados.telefone,telefone);
		
		printf("\nDigite seu email:");
		scanf (" %199[^\n]s",email);
		strcpy(coef[*tam].dados.email,email);
	
		do{	
		printf("\nDigite sua matricula: ");
		scanf("%d", &n );	
		pesq = pesquisar(coef,*tam,n);
		
		if(pesq!=-1){
			printf("\nMatricula já existe!");
		}
		
		}while((pesq!=-1) || n < 0 || n > 500);		
		
		coef[*tam].num = n;
	
		do{
			printf("\nDigite o coeficiente: ");
			scanf("%f", &rendimento );
			if(rendimento < 0 || rendimento > 100){
				printf("Coeficiente Invalido");
			}		
		}while (rendimento < 0 || rendimento > 100);		
			coef[*tam].coe = rendimento;
		(*tam)++;
	
	return *tam;
}


void atualizar(struct Matricula *num, int *tam){
	float coefi;
	int matri,pesq;
	
	printf("Digite a matricula que quer atualizar:");
	scanf("%d",&matri);
	
	pesq = pesquisar(num,*tam,matri);
	
	if(pesq > 0){
		printf("\nDigite o coeficiente novo:");
		scanf("%f",&coefi);
		num[pesq].coe = coefi;
		
		printf("\nCoeficiente Atualizado !!");
	}
	else{
		printf("\nCoeficiente Nao existe !");
	}
}

void MaiorCoeficiente(struct Matricula *n, int *tam){
	int i;
	int matri;
	float maior;
	maior = -999,99;
	matri = 0;
	for(i = 0; i < *tam; i++){
		if (n[i].coe> maior){
			maior = n[i].coe;
			matri = n[i].num;
		}
	}
	printf("Matricula: %d",matri);
	printf("\nMaior Coeficiente: %.2f", maior);
}


void excluir(struct Matricula *n,int *tam){
	int i;
	int pesq;
	int matri;
	printf("Digite a matricula que quer excluir:");
	scanf("%d",&matri);
	
	
	pesq = pesquisar(n,*tam,matri);
	
	for(i=0; i<*tam;i++){
		 if(n[i].num == matri){
		 	n[i].num = n[i+1].num;
		 	n[*tam-1].num = 0;
		 }	
		
	}
}


int main(){
	
	struct Matricula nu[MAX];
	int tam,op = 1;
	int pesq;
	int x;
	tam = 0;
	char p[MAX];
	
	
	
	while (op != 0){
		op = menu();
		
		switch (op){
		case 1:
			lerVetor(nu,&tam);
			
			break;
		case 2:
			printf("\nInforme a matricula que quer pesquisar:");
			scanf("%d",&pesq);
			x = pesquisar(nu,tam,pesq);
			
			if (x >= 0){
				printf("\nMatricula Encontrada!");
				printf("Matricula: %d   Coeficiente: %.2f", nu[x].num,nu[x].coe);	
			}
			
			else{
				printf("Matricula Nao Existe !");
			}
			break;
		
		case 3:
			atualizar(nu, &tam);
			break;
		
		case 4:
			MaiorCoeficiente(nu,&tam);
			break;
		
		case 5:
			excluir(nu,&tam);
			break;
		
		case 6:
			listar(nu,&tam);
			break;
		case 7:
			printf("\nInforme o nome que quer pesquisar:");
			scanf(" %199[^\n]s",&p);
			pesq = pesquisarNome(nu,tam,p);
			
			if (pesq >= 0){
				printf("\nNome Encontrado!");
				printf("\n\nNome: %s  \nTelefone: %s  \nE-mail: %s  \nMatricula: %d  \nCoeficiente: %.2f",nu[pesq].dados.nome,nu[pesq].dados.telefone,nu[pesq].dados.email, nu[pesq].num,nu[pesq].coe);	
			}
			
			else{
				printf("Nome Nao Existe !");
			}
			break;
		case 8:
			quickSort(nu,0,tam - 1);
			listar(nu,&tam);
			break;
			
		case 9:
			insertSort(nu,tam);
			listar(nu,&tam);
			break;
			
		
		default:
			printf("\nFim Do Processo *-*");
		}
	}
}





