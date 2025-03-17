#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Cores, definidas previamente como codigo ANSI para facilitar a estilizacao
#define NONE        "\033[0m"
#define Vermelho    "\033[31m"
#define Verde       "\033[32m"
#define Amarelo     "\033[33m"
#define Ciano       "\033[36m"
#define Azul        "\033[34m"
//Fundo laranja
#define Laranja     "\033[48:5:208m"

//Cria um struct para armazenar posicoes
typedef struct{
    int i;
    int j;
}posicao;

//Funcao Main
int main(){
    int resp,m,n,i,j,a=0,a_anterior;
    char nome_arquivo[64],aux[64],ordem[6];

    //Seta a funcao rand conforme o tempo
    srand(time(0));

    //Cria dois elementos de posicao
    posicao jogador, final;

    //Insere as instrucoes
    printf("%s%s%s",Azul,"BEM-VINDO AO SIMULADOR DE LABIRINTOS 2088\n\nVOCE TEM 4 OPCOES:\n\n1-TENTAR RESOLVER O LABIRINTO COM UMA TENTATIVA;",NONE);
    printf("%s%s%s",Azul,"\n2-RESOLVER O LABIRINTO(PODE DEMORAR);\n3-SALVAR O SEU ULTIMO LABIRINTO;\n4-SAIR DO SIMULADOR DE LABIRINTOS 2088.\n\n",NONE);
    do{
        printf("%s%s%s",Azul,"DIGITE A SUA ESCOLHA:\n",NONE);
        scanf("%d",&resp);
    }while(resp!=1 && resp!=2 && resp!=3 && resp!=4);

    //Executa com base na resposta
    if(resp==1 || resp==2 || resp==3){

        //Pedindo para o usuario selecionar o arquivo de labirinto a ser carregado
        printf("%s%s%s",Azul,"Digite o nome do arquivo do labirinto(sem o .txt):\n",NONE);
        scanf("%s",nome_arquivo);
        
        // VS CODE
        strcpy(aux,"../labirintos/");
        strcat(aux,nome_arquivo);
        FILE* teste = fopen(strcat(aux,".txt"),"r");
        
        // GEANY
        // strcpy(aux,"labirintos/");
        // strcat(aux,nome_arquivo);
        // FILE* teste = fopen(strcat(aux,".txt"),"r"); // para ler no geany
        
        
        
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
        // Printando o labirinto, utilizando os codigos ANSI para deixar bonitinho
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                if(labirinto[i][j] =='#') printf("%s%c%s",Laranja,' ',NONE);
                else if(labirinto[i][j] ==' '&& labirinto[i][j+1] =='#'&& labirinto[i][j-1] =='#'){
                    printf("%s%c%s",Laranja,' ',NONE);
                } 
                else if(labirinto[i][j] =='$'){
                    printf("%s%c%s",Verde,254,NONE);
                    final.i = i;
                    final.j = j;
                } 
                else if(labirinto[i][j] =='%') printf("%s%c%s",Vermelho,254,NONE);
                else if(labirinto[i][j] =='@'){
                    printf("%s%c%s",Amarelo,254,NONE);
                    jogador.i = i;
                    jogador.j = j;
                }        
                else {
                    printf ("%c", labirinto[i][j]);
                }
            }
        }

        //Mostra a posicao inicial e final (Fins de checagem)
        printf("\njogador i:%d jogador j:%d\n",jogador.i,jogador.j);
        printf("\njogador final i:%d jogador final j:%d\n",final.i,final.j);

        //Função que faz o boneco andar
        while(final.i != jogador.i && final.j != jogador.j){
                a = 0 + rand()%4;
                if(a==a_anterior) {
					do{
						a = 0 + rand()%4;
					}while(a==a_anterior);
				}
                printf("a: %d\n",a);
                switch(a){
                    case 1: {
                        //Para cima
                        jogador.i--;
                        a_anterior = 2;
                        break;
                    }
                    case 2: {
                        //Para baixo
                        jogador.i++;
                        a_anterior = 1;
                        break;
                    }
                    case 3: {
                        //Para esquerda
                        jogador.j-=2;
                        a_anterior = 0;
                        break;
                    }
                    case 0: {
                        //Para direita
                        jogador.j+=2;
                        a_anterior = 3;
                        break;
                    }
                }
                
                //Troca a posicao que o jogador passa por *
                labirinto[jogador.i][jogador.j] = '*';

                //Exibe o labirinto com as movimentacoes do grande heroi
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
                if(jogador.i == final.i && jogador.j == final.j) break;
        }

        //Salva o caminho do grande heroi no labirinto final
        if (resp==3){
            FILE* lab_final = fopen("lab_final.txt", "w");
            fputs(ordem, lab_final);
            for (i=0; i<m; i++){
                for (j=0; j<n; j++){
                    fputc(labirinto[i][j], lab_final);
                }
            }
            fclose(lab_final);
        }
        fclose(teste);
    }
    return 0;
}
