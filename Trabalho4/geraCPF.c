//================================================================
// Nome Do Arquivo: cpf.c
// File Name: cpf.c
//
// Descri��o: Implementa��o do algoritmo gerador de cpf
//================================================================
 
// Libs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
// Prot�tipo da fun��o geradora de CPF
int* cpf_generator();
 
// Fun��o main
// Main Function
int main(int argc, char** argv){
    int *cpf, i;
    FILE *arquivo_saida;
    arquivo_saida = fopen("cpf.txt", "w");
    if(!arquivo_saida){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    // Inicia o gerador de n�meros aleat�rios
    srand(time(NULL));
    for(i = 0; i <1000; i++){
        cpf = cpf_generator();
        fwrite(cpf, sizeof(cpf), 1, arquivo_saida);
    }
    system("read -p 'Press Enter to continue...' var");
    fclose(arquivo_saida);
    // Libera a mem�ria usada para o cpf
    free(cpf);
    return 0;
}
 
// Fun��o Geradora de CPF
int* cpf_generator() {
    int *cpf, pesos[11], vetSoma[11], soma, resto, digito,  i;
     
    // Aloca mem�ria para o cpf
    cpf = (int *) malloc(sizeof(int) * 11);
     
    // Gera 9 n�meros aleat�rios
    for(i = 0; i < 9; i++) {
        cpf[i] = rand() % 10;
    }
     
    // C�lculo do primeiro d�gito verificador
     
    // Gera os 9 pesos
    for(i = 0; i < 9; i++) {
        pesos[i] = 10 - i;
    }
     
    // Multiplica os valores de cada coluna
    for(i = 0; i < 9; i++) {
        vetSoma[i] = cpf[i] * pesos[i];
    }
     
    // Calcula o somat�rio dos resultados
    soma = 0;
    for(i = 0; i < 9; i++) {
        soma += vetSoma[i];
    }
     
    // Realiza-se a divis�o inteira do resultado por 11
    resto = soma % 11;
     
    // Verifica o resto da divis�o
    if(resto < 2) {
        digito = 0;
    } else {
        digito = 11 - resto;
    }
     
    // Adiciona o 1� d�gito verificador ao cpf
    cpf[9] = digito;
     
    // C�lculo do segundo d�gito verificador
     
    // Gera os 10 pesos
    for(i = 0; i < 10; i++) {
        pesos[i] = 11 - i;
    }
     
    // Multiplica os valores de cada coluna
    for(i = 0; i < 10; i++) {
        vetSoma[i] = cpf[i] * pesos[i];
    }
     
    // Calcula o somat�rio dos resultados
    soma = 0;
    for(i = 0; i < 10; i++) {
        soma += vetSoma[i];
    }
     
    // Realiza-se a divis�o inteira do resultado por 11
    resto = soma % 11;
     
    // Verifica o resto da divis�o
    if(resto < 2) {
        digito = 0;
    } else {
        digito = 11 - resto;
    }
     
    // Adiciona o 2� d�gito verificador ao cpf
    cpf[10] = digito;
     
    return cpf;
}