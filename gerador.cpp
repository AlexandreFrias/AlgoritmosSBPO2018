#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cria_instancia(char nomearq[], int n, int k, int p){

  FILE *arquivo;
  int j, l, i, x;

  arquivo = fopen(nomearq,"w");
  if (!arquivo) {
    printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
    getchar();
    exit(1);
  }

  fprintf(arquivo, "%d\n%d\n", n, k);

  for(l=0; l<n; l++){
    for(j=0; j<p; j++){
      x=rand()%10;
      fprintf(arquivo, "%d", x);
    }
    fprintf(arquivo, "\n");
  }

  fclose(arquivo);
}

int main(){

  srand(time(NULL));

  int N=5; //número de instâncias com uma característica ()
	int i=1;
	char nome_arquivo[25];
	int n[]={100, 200, 400, 800}; //cardinalidade do conjunto de vetores
  //int k=3 
	int k[]={3,4,5,6}; //número de subconjuntos da partição
	int p=12; //precisão: número de algarismos máximo dos elementos

  
  for(int i0=0; i0<4; i0++){
    for(int i1=0; i1<4; i1++){
      for(int i2=0; i2<N; i2++){
        sprintf(nome_arquivo, "inst%i.txt", i);
        cria_instancia(nome_arquivo, n[i1], k[i2], p);
        i++;
      }
    }
  }
	
	return 0;
}