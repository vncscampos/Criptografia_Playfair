#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>

char** gerarTabela(char carac[], int *size) {
    int tam = strlen(carac);
    for (int i = 0; i < tam; i++) { //embaralha o vetor
        int r = rand() % tam;
        char aux = carac[i];
        carac[i] = carac[r];
        carac[r] = aux;
    }

    int k = 0;
    int tam2 = sqrt(strlen(carac));

    char **m = (char**) malloc(tam2 * sizeof (char*)); //Como se estivesse fazendo um char m[tam2]
    for (int i = 0; i < tam2; i++) { //Percorre as linhas do Vetor de Ponteiros
        m[i] = (char*) malloc(tam2 * sizeof (char)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (int j = 0; j < tam2; j++) { //Percorre o Vetor de Inteiros atual.
            m[i][j] = carac[k];
            k++;
        }
    }

    *size = tam2; //pega o tamanho da matriz

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

char* xInsertion(char msg[], int space[]) {
    int pos = 0;
    int tam = strlen(msg);
    char *aux = (char*) malloc(tam * sizeof (char));

    int k = 0;
    for (int i = 0; i < tam; i++) { //salva os espaços da mensagem
        if (msg[i] == ' ') {
            space[k] = i;
            k++;
        }
    }

    for (int j = 0; j < tam; j++) { //remove os espaços da mensagem
        if (msg[j] == ' ') {
            for (int n = j; n < tam; n++) {
                msg[n] = msg[n + 1];
            }
        }
    }

    for (int i = 0; i < tam;) { //insere o X
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
    int aux_size = strlen(aux) - 1;
    //verifica se a string é impar 
    //se sim, adiciona um x na ultima posição
    if (aux_size % 2 != 0) {
        aux[aux_size] = 'X';
    }

    return aux;
}

char* criptografar(char *msg, char **tab, int tam) {
    int pos = 0;
    int l1, l2, c1, c2;
    while (pos < strlen(msg) - 1) {
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                if (tab[i][j] == msg[pos]) { //Encontra a primeira letra
                    l1 = i;
                    c1 = j;
                } else if (tab[i][j] == msg[pos + 1]) { //encontra a segunda letra
                    l2 = i;
                    c2 = j;
                }
            }
        }
        if (l1 == l2) {//Mesma linha
            if (c1 + 1 < tam) {
                msg[pos] = tab[l1][c1 + 1];
            } else {
                msg[pos] = tab[l1][0];
            }
            if (c2 + 1 < tam) {
                msg[pos + 1] = tab[l2][c2 + 1];
            } else {
                msg[pos + 1] = tab[l2][0];
            }
        } else if (c1 == c2) {//Mesma coluna
            if (l1 + 1 < tam) {
                msg[pos] = tab[l1 + 1][c1];
            } else {
                msg[pos] = tab[0][c1];
            }
            if (l2 + 1 < tam) {
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

char* decrip(char *msg, char **tab, int tam) {
    int pos = 0;
    int l1, l2, c1, c2;
    while (pos < strlen(msg) - 1) {
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                if (tab[i][j] == msg[pos]) { //Encontra a primeira letra
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
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int acao, tam;
    char msgm[100];
    char *p_ch;
    int *space = (int*) calloc(100, sizeof (int));
    char carac[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char **p;
    char carac2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    bool verify_crip = false; //Verifica a criptografia - Olhar o case 2
    bool verify_decrip = false; //Verifica a decriptografia - Olhar o case 3
    do {
        printf("\nDigite a ação que deseja fazer:\n");
        printf("1. Gerar tabela;\n");
        printf("2. Introduzir mensagem;\n");
        printf("3. Ver mensagem criptografada;\n");
        printf("4. Decriptografar mensagem;\n");
        printf("5. Remover número;\n");
        printf("6. Imprimir tabela;\n");
        printf("7. SAIR.\n");
        printf("_________________________\n");
        scanf("%d", &acao);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (acao) {
            case 1:
                p = gerarTabela(carac, &tam);
                break;

            case 2:
                printf("Digite a mensagem:");
                fgets(msgm, 100, stdin);

                for (int i = 0; i < strlen(msgm); i++) {
                    msgm[i] = toupper(msgm[i]); //transforma letras para maiúsculas
                }

                char letras[] = {'A', 'A', 'A', 'A', 'E', 'E', 'I', 'O', 'O', 'O', 'U', 'U', 'C'};
                int letras_Acento[] = {0xc3a1, 0xc3a0, 0xc3a2, 0xc3a3, 0xc3a9, 0xc3aa, 0xc3ad, 0xc3b3, 0xc3b4, 0xc3b5, 0xc3ba, 0xc3bc, 0xc3a7};

                for (int i = 0; i < strlen(msgm); i++) {
                    wchar_t x = msgm[i];
                    wchar_t y = msgm[i + 1];

                    int num1 = x - 0xffffff00; //pega o hex do char X
                    int num2 = y - 0xffffff00; //pega o hex do char Y
                    int num3 = 256 * num1 + num2; //concatena o num hex de x e y

                    for (int j = 0; j < sizeof (letras_Acento); j++) {
                        if (num3 == letras_Acento[j]) {
                            msgm[i] = letras[j]; //a letra com acento vai receber a letra sem acento correspondente ao vetor letras[]
                            for(int k = i+1; k < sizeof (letras_Acento); k++){ //shift
                                msgm[k] = msgm[k+1];
                            }
                            
                        }
                    }
                }

                verify_crip = true;
                break;

            case 3:
                if (verify_crip == true) { //n permite criptografar a mesma mensagem mais de uma vez
                    p_ch = xInsertion(msgm, space);
                    p_ch = criptografar(p_ch, p, tam);
                    verify_decrip = true;
                }
                verify_crip = false;

                for (int i = 0; i < strlen(p_ch); i++) {  //imprime a criptografia 4 por 4
                    printf("%c", p_ch[i]);
                    if ((i+1) % 4 == 0) {
                        printf(" ");
                    }
                    
                }
                break;

            case 4:
                if (verify_decrip == true) { //n permite decriptografar a mesma mensagem mais de uma vez
                    p_ch = decrip(p_ch, p, tam);
                }

                for (int i = 0; i < strlen(p_ch); i++) { // retira o X
                    if (p_ch[i] == 'X') {
                        if (p_ch[i - 1] == p_ch[i + 1]) {
                            for (int k = i; k < strlen(p_ch); k++) { //shift
                                p_ch[k] = p_ch[k + 1];
                            }
                        }
                    }
                }
                
                int aux_size = strlen(p_ch) - 1; //retira o X da ultima posiçao caso a palavra seja ímpar
                if (aux_size % 2 != 0) {
                    p_ch[aux_size] = p_ch[aux_size+1];
                }

                for (int i = 0; i < sizeof (space); i++) { //coloca os espaços
                    int aux = space[i];
                    if (aux != 0) {
                        for (int j = 99; j > aux; j--) {
                            p_ch[j] = p_ch[j - 1];
                        }
                        p_ch[aux] = ' ';
                    }
                }

                printf("%s\n", p_ch);
                verify_decrip = false;
                break;

            case 5:
                p = gerarTabela(carac2, &tam);
                break;

            case 6:
                imprimirTabela(p, tam);
                break;

        }
    } while (acao != 7);

    return (EXIT_SUCCESS);
}


