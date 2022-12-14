#include <stdio.h>
#include <stdlib.h>


//448.403.418-26 --> size = 14

#define HASH_SIZE 1023
#define DATA_SIZE 1000
#define CPF_SIZE 5     /*  nao conta com o "\n"  numero de digitos = 11 numero de caracteres = 14(contando com . e - )*/

/*__________________________________________________________________________*/
void inicializaTabela(unsigned long *tabelaHash);
int mandaChave(unsigned long cpf, int k);
int buscaElemento(unsigned long *tabelaHash, unsigned long valor);
int achaMax(int *numColisoes_Y, int posicao);
/*__________________________________________________________________________*/

int main(void){
    unsigned long tabelaHash[HASH_SIZE];
    long auxLeitura = 0;
    int chave, numLeituras = 1, numColisoes = 0;
    int numLeituras_X[HASH_SIZE]; //vetores para plotar grafico
    int numColisoes_Y[HASH_SIZE];
    int numColisoesTotal = 0;
    FILE *arquivo_entrada = fopen("cpf.txt", "r");
    FILE *arquivo_graph = fopen("grafico.txt", "w");

    int resultadoBusca = 0;
    unsigned long valorBusca = 44840341826;

    if(!arquivo_entrada){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    inicializaTabela(tabelaHash);

    while(!feof(arquivo_entrada)){
        fscanf(arquivo_entrada, "%ld", &auxLeitura);
        numLeituras++;
        int k = -1;

        do{
            chave = mandaChave(auxLeitura, k++);
            
        }while(tabelaHash[chave] != -1);
        numColisoesTotal += k;

        if(k > 0){
            numColisoes ++;
        }

        numColisoes_Y[numLeituras] = k;
        numLeituras_X[numLeituras] = numLeituras;

        if(numLeituras == 100 || numLeituras == 200 || numLeituras == 300 || numLeituras == 400 || numLeituras == 500 || numLeituras == 600 || numLeituras == 700 || numLeituras == 800 || numLeituras == 900 || numLeituras == 1000){
            printf("Leituras:%d\nColisoes:%d", numLeituras, numColisoes);
            printf("\n--------------\n");
        }   
        tabelaHash[chave] = auxLeitura;
    }

    //Monta o vetor p plotar grafico
    int z = 1;
    for(z = 1; z < HASH_SIZE; z++){
        fprintf(arquivo_graph,"%d\t %d\n",numLeituras_X[z],numColisoes_Y[z]);
    }

    
    resultadoBusca = buscaElemento(tabelaHash, valorBusca);

    if(resultadoBusca == -3){
        printf("Elemento nao encontrado\n");
    }else{
        printf("O valor %ld foi encontrado e esta na posicao %d ta tabela\n", valorBusca, resultadoBusca);
    }
    int maxColisoes = achaMax(numColisoes_Y, z);
    printf("O numero maximo de colisoes foi %d", maxColisoes);
    fclose(arquivo_graph);
    fclose(arquivo_entrada);
    return 0;
}

//funcao coloca tudo com -1 pra facilitar verificacao se ta vazio ou n, ja q -1 nao e um valor possivel
void inicializaTabela(unsigned long *tabelaHash){
    for(int i = 0; i< HASH_SIZE; i++){
        tabelaHash[i] = -1;
    }
}

int buscaElemento(unsigned long *tabelaHash, unsigned long valor){
    int posicao, k = 0;

    posicao = mandaChave(valor, k);
    while(tabelaHash[posicao] != valor){
        posicao = mandaChave(valor, k+=1);

        if(tabelaHash[posicao] == valor){
            return posicao;
        }
        if((posicao+k) > HASH_SIZE){
            break;
            return -3;
        }
    }
    return posicao;
}

int mandaChave(unsigned long cpf, int k){
    int chave = 0;

    chave = (cpf + k) % 1021;

    return chave;
}
int achaMax(int *numColisoes_Y, int posicao){
    int maxColisoes = -1;
    for(int i = 0; i <1000; i++){
        if(numColisoes_Y[i] > maxColisoes){
            maxColisoes = numColisoes_Y[i];
            posicao = i;
        }
    }

    return maxColisoes;
}

/*
PRIMO   COLISOES
1019    566
1021    491
1031    461
1033    779
*/