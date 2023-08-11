#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct nomes{
	char nome[60];
	char sobrenome[60];
	nomes *prox;
};

struct Autor_lista{
	nomes * nome;
	Autor_lista *prox;
};
//typedef struct Autor_lista ListaAutor;

struct Livros_lista{
	
		Livros_lista *prox;
		Livros_lista *ant;
		char titulo[60];
		int ano;
		int pag;
		Autor_lista **C;
	
};
//typedef struct Livros_lista ListaLivros;

struct editora{
	
	Livros_lista *C;
	char nome[60];
	editora *prox;
	
};
//typedef struct editora Editora;

struct TpRegistro 
{
	char autores[100],titulo_livro[100], editora[50];
	int ano, paginas;
};


editora *criaEditora(char editor[], editora *C)
{
		C = (editora*) malloc(sizeof(editora));
		strcpy(C->nome,editor);
		C->prox = NULL;
		C->C =NULL;
		return C;
}

Livros_lista *criaLivros(TpRegistro A, Livros_lista *C)
{
	C = (Livros_lista*)malloc(sizeof(Livros_lista));
	C->ano = A.ano;
	C->ant= NULL;
	C->prox = NULL;
	C->C=NULL;
	C->pag= A.paginas;
	strcpy(C->titulo,A.titulo_livro);
	// possivel função para colocar autores aqui
	return C;
}

editora *InsereEdit(TpRegistro A,editora *C)
{
	editora *aux = (editora*)malloc(sizeof(editora));
	
	if(C == NULL)
		C = criaEditora(A.editora,C);
	else
	{
		while(aux->prox != NULL & stricmp(aux->prox->nome,A.editora)!= 0) aux = aux->prox;
		
		if(aux->prox == NULL && stricmp(aux->prox->nome,A.editora)!= 0)
		{
			aux->prox = criaEditora(A.editora,aux->prox);
		//pulo pra caixa da frente, agora parto para a lista de livros trabalho aux agora
			aux = aux->prox;
		}
		
		
	}
	if(C->C == NULL)// editora sem livros
		C->C = criaLivros(A,C->C);
	else
	{
		
	}
	
	
	
	
	
	return C;
}

void imprime()
{
	FILE *arqBin = fopen("livros.dat","rb");
    TpRegistro reg;
    fread(&reg,sizeof(TpRegistro),1,arqBin);
    while (!feof(arqBin))
	{	
    	printf("%s\n%s\n%s\t%d\t%d\n\n",reg.autores, reg.titulo_livro, reg.editora, reg.ano, reg.paginas);
        fread(&reg,sizeof(TpRegistro),1,arqBin);
    }  
}

void gera_arq_bin()
{
	FILE *arq = fopen("livros.txt","r");
    TpRegistro reg;
    FILE *arqBin = fopen("livros.dat","wb");
    fscanf(arq,"%[^|]|%[^|]|%[^|]|%d|%d", &reg.autores, &reg.titulo_livro, &reg.editora, &reg.ano, &reg.paginas);
    while(!feof(arq))
	{
    //	printf("%s\t%s\t%s\t%d\t%d\n",reg.autores, reg.titulo, reg.editora, reg.ano, reg.pag );
    	fwrite(&reg,sizeof(TpRegistro),1,arqBin);
    	fscanf(arq,"%[^|]|%[^|]|%[^|]|%d|%d", &reg.autores, &reg.titulo_livro, &reg.editora, &reg.ano, &reg.paginas);
    };
    fclose(arq);
    fclose(arqBin);
    printf("\n\nConcluido\n");
		
}

int main(void)
{
	editora *CabecaEditora = (editora*)malloc(sizeof(editora));
	CabecaEditora = NULL;
	
	gera_arq_bin();
	imprime();
	return 0;
}
