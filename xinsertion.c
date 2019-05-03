//To colocando em uma classe separada só pra poder ir testando mais facil
//Podemos por junto com o case da inserção da string,ai já insere e insere o x
//Depois só codificar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main(){
    char msg[100];
    fgets(msg,100,stdin);
    int pos = 0;
    int tam = strlen(msg);
    char aux[tam];
    
    //Retira os espaços em branco pra poder ficar mais facil a inserção
    for(int j = 0; j < tam;j++){
        if(msg[j] == ' '){
           for(int n = j; n < tam; n++){
               msg[n] = msg[n+1];
           }
        }
    }
    
    //Vai armazenando em um segundo vetor
    //Achei mais facil fazer assim
    for(int i = 0; i < tam;){
        if(msg[i] == msg[i+1]){
            aux[pos] = msg[i];
            aux[pos+1] = 'X';
            i++;
        }else{
            aux[pos] = msg[i];
            aux[pos+1] = msg[i+1];
            i += 2;
        }
        pos = pos + 2;
    }
    
    //Verifica se a string é impar 
    //Se sim, adiciona um X na ultima posição
    if((tam-1)  % 2 != 0){
        aux[aux_size-1] = 'X';
    }

}
