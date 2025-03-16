#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cores, definidas previamente como código ANSI para facilitar a estilização

#define NONE        "\033[0m"
#define Vermelho    "\033[31m"
#define Verde       "\033[32m"
#define Amarelo     "\033[33m"
#define Ciano       "\033[36m"
#define Azul        "\033[34m"
//Fundo laranja
#define Laranja     "\033[48:5:208m"

int main(){
    int resp,m,n,i,j;
    char nome_arquivo[64],aux[64],ordem[6];

    printf("%s%s%s",Azul,"BEM-VINDO AO SIMULADOR DE LABIRINTOS 2088\n\nVOCE TEM 4 OPCOES:\n\n1-TENTAR RESOLVER O LABIRINTO COM UMA TENTATIVA;",NONE);
    printf("%s%s%s",Azul,"\n2-RESOLVER O LABIRINTO(PODE DEMORAR);\n3-SALVAR O SEU ULTIMO LABIRINTO;\n4-SAIR DO SIMULADOR DE LABIRINTOS 2088.\n\n",NONE);
    
    do{
        printf("%s%s%s",Azul,"DIGITE A SUA ESCOLHA:\n",NONE);
        scanf("%d",&resp);
    }while(resp!=1 && resp!=2 && resp!=3 && resp!=4);

    if(resp==1){

        //Pedindo para o usuário selecionar o arquivo de labirinto a ser carregado

        printf("%s%s%s",Azul,"Digite o nome do arquivo do labirinto(sem o .txt):\n",NONE);
        scanf("%s",nome_arquivo);
        strcpy(aux,"../labirintos/");
        strcat(aux,nome_arquivo);
        FILE* teste = fopen(strcat(aux,".txt"),"r");
        //FILE* teste = fopen(strcat(nome_arquivo,".txt"),"r"); // para ler no geany
        if(teste==NULL) printf("Nao foi possivel abrir o arquivo\n");

        //Lendo a primeira linha do arquivo, para criar a matriz com a ordem informada
        fgets(ordem,sizeof(ordem),teste);
        sscanf(ordem, "%d %d", &m, &n);
        n = n*2;
        char labirinto[m][n];
        //For para ler e armazenar na matriz os caracteres do arquivo
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                labirinto[i][j] = fgetc(teste);
            }
        }
        //Printando o labirinto, utilizando os códigos ANSI para deixar bonitinho
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                if(labirinto[i][j] =='#') printf("%s%c%s",Laranja,' ',NONE);
                else if(labirinto[i][j] ==' ' && labirinto[i][j+1] =='#' && labirinto[i][j-1] =='#') printf("%s%c%s",Laranja,' ',NONE);
                else if(labirinto[i][j] =='$') printf("%s%c%s",Verde,254,NONE);
                else if(labirinto[i][j] =='%') printf("%s%c%s",Vermelho,254,NONE);
                else if(labirinto[i][j] =='@') printf("%s%c%s",Amarelo,254,NONE);       
                else printf ("%c", labirinto[i][j]);
            }
        }

        fclose(teste);
    }
    return 0;
}
