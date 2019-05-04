# #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h> //pacote pra usar a função q deixa as letras maiúsculas

char** gerarTabela(char carac[], int *tamanho) { //int tamanho é um ponteiro que recebe endereço de um int la no main
    int tam = strlen(carac);
    for (int i = 0; i < tam; i++) { //embaralhar o vetor
        int r = rand() % tam;
        char aux = carac[i];
        carac[i] = carac[r];
        carac[r] = aux;
    }
    int k = 0;
    int tam2 = 6;


    //Malloc = aloca espaços para blocos de bytes consecutivos na memoria
    //Sizeof = retorna a quantidade de bytes um objeto possui
    char **m = (char**) malloc(tam2 * sizeof (char*)); //Como se estivesse fazendo um char m[tam2]
    for (int i = 0; i < tam2; i++) { //Percorre as linhas do Vetor de Ponteiros
        m[i] = (char*) malloc(tam2 * sizeof (char)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (int j = 0; j < tam2; j++) { //Percorre o Vetor de Inteiros atual.
            m[i][j] = carac[k];
            k++;
        }
    }

    *tamanho = tam2; o valor do tam2 eu vou apontar praquele int no main

    return m;
}

void imprimirTabela(char **matriz, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            printf("%c ", matriz[i][j]);
        }
        putchar('\n');
    }
}

char* xInsertion(char msg[]) {
    int pos = 0;
    int tam = strlen(msg);
    char *aux = (char*) malloc(tam * sizeof (char));
    //retira os espaços em branco pra poder ficar mais facil a inserção
    for (int j = 0; j < tam; j++) {
        if (msg[j] == ' ') {
            for (int n = j; n < tam; n++) {
                msg[n] = msg[n + 1];
            }
        }
    }

    for (int i = 0; i < tam;) {
        if (msg[i] == msg[i + 1]) {
            aux[pos] = msg[i];
            aux[pos + 1] = 'X';
            i++;
        } else {
            aux[pos] = msg[i];
            aux[pos + 1] = msg[i + 1];
            i += 2;
        }
        pos = pos + 2;
    }
    int aux_size = strlen(aux);
    //verifica se a string é impar 
    //se sim, adiciona um x na ultima posição
    if ((tam - 2) % 2 != 0) {
        aux[aux_size - 1] = 'X';
    }
    return aux;
}

char* criptografar(char *msg, char **tab) {
    int pos = 0;
    int l1, l2, c1, c2;
    while (pos < strlen(msg) - 2) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (tab[i][j] == msg[pos]) { //Econtra a primeira letra
                    l1 = i;
                    c1 = j;
                } else if (tab[i][j] == msg[pos + 1]) {
                    l2 = i;
                    c2 = j;
                }
            }
        }
        if (l1 == l2) {//Mesma linha
            if (c1 + 1 < 6) {
                msg[pos] = tab[l1][c1 + 1];
            } else {
                msg[pos] = tab[l1][0];
            }
            if (c2 + 1 < 6) {
                msg[pos + 1] = tab[l2][c2 + 1];
            } else {
                msg[pos + 1] = tab[l2][0];
            }
        } else if (c1 == c2) {//Mesma coluna
            if (l1 + 1 < 6) {
                msg[pos] = tab[l1 + 1][c1];
            } else {
                msg[pos] = tab[0][c1];
            }
            if (l2 + 1 < 6) {
                msg[pos + 1] = tab[l2 + 1][c1];
            } else {
                msg[pos + 1] = tab[0][c1];
            }
        } else { //Linhas e Colunas Diferentes
            msg[pos] = tab[l1][c2];
            msg[pos + 1] = tab[l2][c1];
        }
        pos += 2;
    }
    return msg;
}

char* decrip(char *msg, char **tab) {
    int pos = 0;
    int l1, l2, c1, c2;
    while (pos < strlen(msg) - 2) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (tab[i][j] == msg[pos]) { //Econtra a primeira letra
                    l1 = i;
                    c1 = j;
                } else if (tab[i][j] == msg[pos + 1]) { //Encontra a segunda letra
                    l2 = i;
                    c2 = j;
                }
            }
        }
        if (l1 == l2) {//Mesma linha
            if (c1 - 1 < 0) {
                msg[pos] = tab[l1][5];
            } else {
                msg[pos] = tab[l1][c1 - 1];
            }
            if (c2 - 1 < 0) {
                msg[pos + 1] = tab[l2][5];
            } else {
                msg[pos + 1] = tab[l2][c2 - 1];
            }
        } else if (c1 == c2) {//Mesma coluna
            if (l1 - 1 < 0) {
                msg[pos] = tab[5][c1];
            } else {
                msg[pos] = tab[l1 - 1][c1];
            }
            if (l2 - 1 < 0) {
                msg[pos + 1] = tab[5][c1];
            } else {
                msg[pos + 1] = tab[l2 - 1][c1];
            }
        } else { //Linhas e Colunas Diferentes
            msg[pos] = tab[l1][c2];
            msg[pos + 1] = tab[l2][c1];
        }
        pos += 2;
    }

    return msg;
}

int main(int argc, char** argv) {
    int acao, tam;
    char msgm[100];
    char *p_ch;
    char **p;
    char carac[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char carac2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'L', 'M', 'N', 'O', 'P', 'Q',
                        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    bool verify = false; //Verifica a tabela 
    bool verify_crip = false; //Verifica a criptografia - Olhar o case 2
    bool verify_decrip = false; //Verifica a decriptografia - Olhar o case 3

    do {
        printf("\nDigite a ação que deseja fazer:\n");
        printf("1. Gerar tabela;\n");
        printf("2. Introduzir mensagem;\n");
        printf("3. Ver mensagem criptografada;\n");
        printf("4. Decriptografar mensagem;\n");
        printf("5. Editar tabela;\n");
        printf("6. Imprimir tabela;\n");
        printf("7. SAIR.\n");
        printf("_________________________\n");
        scanf("%d", &acao);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        switch (acao) {
            case 1:
                if (verify == false) { //n permite criar outra tabela principal
                    p = gerarTabela(carac, &tam); //aqui to passando o endereço do int tam
                    verify = true;
                }
                break;
            case 2:
                printf("Digite a mensagem: ");
                fgets(msgm, 100, stdin);
                for (int i = 0; i < strlen(msgm); i++) {
                    msgm[i] = toupper(msgm[i]); //transforma letras para maiúsculas
                }
                verify_crip = true;
                break;
            case 3:
                if (verify_crip == true) { //n permite criptografar a mesma mensagem mais de uma vez
                    p_ch = criptografar(p_ch, p);
                    verify_decrip = true;
                }
                verify_crip = false;

                for (int i = 0; i < strlen(p_ch); i++) { //imprime a criptografia dividindo
                    if (i % 5 == 0) {
                        printf(" ");
                    } else {
                        printf("%c", p_ch[i]);
                    }
                }

                break;
            case 4:
                if (verify_decrip == true) { //n permite decriptografar a mesma mensagem mais de uma vez
                    p_ch = decrip(p_ch, p);
                }
                printf("%s\n", p_ch);
                verify_decrip = false;
                break;
            case 5:
                p = gerarTabela(carac2, &tam); //aqui to passando o endereço do int tam
         
                break;
            case 6:
                imprimirTabela(p, tam);
                break;
        }
    } while (acao != 7);

    return (EXIT_SUCCESS);
}


