#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cores, definidas previamente como codigo ANSI para facilitar a estilizacao
#define NONE        "\033[0m"
#define Vermelho    "\033[31m"
#define Verde       "\033[32m"
#define Amarelo     "\033[33m"
#define Ciano       "\033[36m"
#define Azul        "\033[34m"
// Fundo laranja
#define Laranja     "\033[48:5:208m"

// Definindo o labirinto como uma variavel global, o acc_menu esta sendo usado apenas para mudar a mensagem do menu.
char labirinto[20][20];
int acc_menu=0;
// Variavel para acumular quantidade de lutas
int acc_luta=0;

//Cria um struct para armazenar posicoes
typedef struct{
    int i;
    int j;
}posicao;

posicao jogador, final;
// Assinatura das funcoes, estao definidas no final do codigo, depois da main.

int menu(int acc_menu);
void armazenar_labirinto(FILE *lab, int m, int n);
void printar_labirinto(int m, int n);
void printar_estilizado(int m, int n);
void salvar_labirinto(int m, int n, char* ordem);
void checagem(int m,int n);
void andar();
int luta(int acc_luta);

// Funcao Main
int main(int argc, char** argv){
    int resp,m,n;
    char ordem[6];

    // Seta a funcao rand conforme o tempo
    srand(time(0));

    FILE* lab = fopen(argv[1],"r");

    if(lab == NULL) {
        printf("Nao foi possivel abrir o arquivo :(\n");
    }
    else{
        //Lendo a ordem da matriz do labirinto, informada na primeira linha.
        // fgets(ordem,sizeof(ordem),lab);
        // sscanf(ordem, "%d %d", &m, &n);
        // armazenar_labirinto(lab, m, n);
        if(acc_menu==0){
            fgets(ordem,sizeof(ordem),lab);
            sscanf(ordem, "%d %d", &m, &n);
            armazenar_labirinto(lab, m, n);
            checagem(m,n);
            printar_labirinto(m,n);
            printf("\n\n");
            printar_estilizado(m,n);
        }
        else{
            fgets(ordem,sizeof(ordem),lab);
            sscanf(ordem, "%d %d", &m, &n);
            printar_labirinto(m,n);
            printf("\n\n");
            printar_estilizado(m,n);
        }
        resp = menu(acc_menu);
        switch (resp) {
            case 1: {
                andar();
                //printar_labirinto(m,n); 
                acc_menu++;
                main(argc,argv);
            }
            case 2: {
                printf("Em breve"); 
                acc_menu++;
                main(argc,argv);
            }
            case 3: {
                salvar_labirinto(m, n, ordem);
                acc_menu++;
                main(argc,argv);
            }
            case 4: exit(0); break;
        }
    }
    fclose(lab);
    return 0;
}

// Funcao para ler o arquivo e armazenar labirinto na matriz
void armazenar_labirinto(FILE *lab, int m, int n){
    int i, j;
    // For para ler e armazenar na matriz os caracteres do arquivo
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            fscanf(lab, " %c", &labirinto[i][j]);
        }
    }
}

// Funcao do menu inicial
int menu(int acc_menu){
    int resposta;
    if(acc_menu == 0){
        printf("%s%s%s",Azul,"\nBEM-VINDO AO SIMULADOR DE LABIRINTOS 2088\n\nVOCE TEM 4 OPCOES:\n\n1-TENTAR RESOLVER O LABIRINTO COM UMA TENTATIVA;",NONE);
    }
    else{
        printf("%s%s%s",Azul,"\nBEM-VINDO DE VOLTA!\n\nVOCE TEM 4 OPCOES:\n\n1-TENTAR RESOLVER O LABIRINTO COM UMA TENTATIVA;",NONE);
    }
    printf("%s%s%s",Azul,"\n2-RESOLVER O LABIRINTO (PODE DEMORAR);\n3-SALVAR O SEU ULTIMO LABIRINTO;\n4-SAIR DO SIMULADOR DE LABIRINTOS 2088.\n\n",NONE);
        do{
            printf("%s%s%s",Azul,"DIGITE A SUA ESCOLHA:\n",NONE);
            scanf("%d",&resposta);
    }while(resposta!=1 && resposta!=2 && resposta!=3 && resposta!=4);
    return resposta;
}

// Funcoes para printar o labirinto

void printar_labirinto(int m, int n){
    int i,j;
    // Printando o labirinto sem estilizacao.
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(j==n-1 && i!=m-1){
                printf("%c ", labirinto[i][j]);
                printf("\n");
            }
            else{
                printf ("%c ", labirinto[i][j]);
            }
        }
    }
}

void printar_estilizado(int m, int n){
    int i, j;
    // Printando o labirinto, utilizando os codigos ANSI para deixar bonitinho
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){ 
            if(labirinto[i][j] =='#') printf("%s%c %s",Laranja,' ',NONE);
            else if(labirinto[i][j] =='$'){
                printf("%s%c %s",Verde,254,NONE);
            } 
            else if(labirinto[i][j] =='%') printf("%s%c %s",Vermelho,254,NONE);
            else if(labirinto[i][j] =='@'){
                printf("%s%c %s",Amarelo,254,NONE);
            }
            else if(labirinto[i][j] =='V'){
                printf("%s%c %s",Verde,'V',NONE);
            }
            else if(labirinto[i][j] =='?'){
                printf("%s%c %s",Vermelho,'?',NONE);
            }
            else if(labirinto[i][j] =='*'){
                printf("%s%c %s",Amarelo,'*',NONE);
            }
            else if(labirinto[i][j] =='+'){
                printf("%s%c %s",Vermelho,'+',NONE);
            }
            else if(labirinto[i][j] =='!'){
                printf("%s%c %s",Vermelho,'!',NONE);
            }
            else{
                printf("%c ", labirinto[i][j]);
            }
            if(j==n-1){
                printf("\n");
            }
        }
    }
}

// Funcao para salvar o labirinto final.

void salvar_labirinto(int m, int n, char* ordem){
    int i, j;
    FILE* lab_final = fopen("lab_final.txt", "w");
    if(lab_final==NULL) printf("Nao foi possivel abrir o arquivo\n");
    else{
        fputs(ordem, lab_final);
        fputs("\n", lab_final);
        for (i=0; i<m; i++){
            for (j=0; j<n; j++){
                if(j==n-1){
                    fputc(labirinto[i][j], lab_final);
                }
                else{
                    fputc(labirinto[i][j], lab_final);
                    fputs(" ", lab_final);
                }
            }
            if(i!=m-1)fputs("\n", lab_final);
        }
        printf("O labirinto foi salvo com sucesso!\n");
    }
    fclose(lab_final);
}

// Funcao para armazenar as posicoes inicial e final
void checagem(int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(labirinto[i][j] =='$'){
                final.i = i;
                final.j = j;
            }
            else if(labirinto[i][j] =='@'){
                jogador.i = i;
                jogador.j = j;
            } 
        }
    }
}

// Funcao para fazer o grande heroi andar
void andar(){
    // Armazenando a posicao inicial do grande heroi para garantir que o quadrado inicial nao se transforme em '*'
    posicao inicial;
    inicial.i = jogador.i;
    inicial.j = jogador.j;
    //Mostra a posicao inicial e final (Fins de checagem)
    printf("\njogador i:%d jogador j:%d\n",jogador.i,jogador.j);
    printf("\njogador final i:%d jogador final j:%d\n",final.i,final.j);
    //Função que faz o boneco andar
    int num;
    while(1){
        if((jogador.i == final.i) && (jogador.j == final.j)) {
            labirinto[jogador.i][jogador.j] = 'V';
            break;
        }
        // Se o que estiver ao redor do grande heroi nao for chao, inimigo ou chegada, ele se perdeu
        if((labirinto[jogador.i-1][jogador.j] != '.' && labirinto[jogador.i-1][jogador.j] != '%' && labirinto[jogador.i-1][jogador.j] != '$') 
        && (labirinto[jogador.i+1][jogador.j] != '.' && labirinto[jogador.i+1][jogador.j] != '%' && labirinto[jogador.i+1][jogador.j] != '$') 
        && (labirinto[jogador.i][jogador.j-1] != '.' && labirinto[jogador.i][jogador.j-1] != '%' && labirinto[jogador.i][jogador.j-1] != '$') 
        && (labirinto[jogador.i][jogador.j+1] != '.' && labirinto[jogador.i][jogador.j+1] != '%' && labirinto[jogador.i][jogador.j+1] != '$'))
        {
            printf("O grande heroi se perdeu :(\n");
            labirinto[jogador.i][jogador.j] = '?';
            break;
        }

        num = 0 + rand()%4;
        printf("num: %d\n",num);
        switch(num){
            case 1: {
                //Para cima
                if(labirinto[jogador.i-1][jogador.j] == '.' || labirinto[jogador.i-1][jogador.j] == '$' || labirinto[jogador.i-1][jogador.j] == '%'){
                    --jogador.i;
                }
                break;
            }
            case 2: {
                //Para baixo
                if(labirinto[jogador.i+1][jogador.j] == '.' || labirinto[jogador.i+1][jogador.j] == '$' || labirinto[jogador.i+1][jogador.j] == '%'){
                    ++jogador.i;
                }
                break;
            }
            case 3: {
                //Para esquerda
                if(labirinto[jogador.i][jogador.j-1] == '.' || labirinto[jogador.i][jogador.j-1] == '$' || labirinto[jogador.i][jogador.j-1] == '%'){
                    --jogador.j;
                }
                break;
            }
            case 0: {
                //Para direita
                if(labirinto[jogador.i][jogador.j+1] == '.' || labirinto[jogador.i][jogador.j+1] == '$' || labirinto[jogador.i][jogador.j+1] == '%'){
                    ++jogador.j;
                }
                break;
            }
        }

        if(labirinto[jogador.i][jogador.j] == '%'){
            int resultado_luta = luta(acc_luta);
            printf("Luta numero:%d\n",acc_luta);
            if(resultado_luta){
                printf("O grande heroi ganhou a luta :)\n");
                acc_luta++;
                labirinto[jogador.i][jogador.j] = '!';
            }
            else{
                printf("O grande heroi perdeu a luta :(\n");
                labirinto[jogador.i][jogador.j] = '+';
                break;
            }
        }
        //Troca a posicao que o jogador passa por *
        else if(labirinto[jogador.i][jogador.j] == '.') labirinto[jogador.i][jogador.j] = '*';
    }
}

// Funcao de luta, comeca com 50% de chance e vai crescendo 10% conforme o grande heroi ganha batalhas.
int luta(int acc_luta){
    int num;   
    switch (acc_luta){
        case 0: {
            num = 0 + rand()%2;
            printf("num da luta: %d\n",num);
            if(num==1){ // 0 | 1 --> 1/2 == 50%
                return 1;
            }
            else return 0;
            
            break;
        }
        case 1: {
            num = 0 + rand()%10;
            printf("num da luta: %d\n",num); 
            if(num<=5){ // 0 1 2 3 4 5 | 6 7 8 9 --> 6/10 == 60%
                return 1;
            }
            else return 0;
            break;
        }
        case 2: {
            num = 0 + rand()%10;
            printf("num da luta: %d\n",num);
            if(num<=6){ // 0 1 2 3 4 5 6 | 7 8 9 --> 7/10 == 70%
                return 1;
            }
            else return 0;
            break;
        }
        case 3: {
            num = 0 + rand()%10;
            printf("num da luta: %d\n",num);
            if(num<=7){ // 0 1 2 3 4 5 6 7 | 8 9 --> 8/10 == 80%
                return 1;
            }
            else return 0;
            break;
        }
        case 4: { // 0 1 2 3 4 5 6 7 8 | 9 --> 9/10 == 90%
            num = 0 + rand()%10;
            printf("num da luta: %d\n",num);
            if(num<=8){
                return 1;
            }
            else return 0;
            break;
        }
        case 5: { // 100% de chance de ganhar 
            return 1;
            break;
        }
    }
}