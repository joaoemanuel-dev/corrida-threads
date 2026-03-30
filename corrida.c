#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int x; // guarda quantas threads o usuário quer

pthread_barrier_t barreira; // variável do tipo barreira de sincronização -> linha de largada
pthread_mutex_t mutex_vencedor; // não deixa escrever em quem venceu ao mesmo tempo -> 
                               // apenas uma thread entra na seção crítica (variável vencedor, recurso compartilhado)

int vencedor = -1; // guarda o id da thread que ganhou a corrida, vairável compartilhada entre as threads

// isso aqui é uma função que cada thread vai executar (vai jogando na barreira na memória)
void *corrida(void *arg){ // recebe o endereço de um inteiro
    int id = *(int *)arg; // pega o inteiro que está no endereço apontado por arg
    // exemplo: se arg apontava para id[3], então id vai receber (3)

    pthread_barrier_wait(&barreira); // essa função faz a thread esperar na barreira
    // a barreira libera apenas quando x threads chegarem a eles -> libera para executar o restante da função, cada thread executando a sua função

    for(int i = 0; i < MAX; i++){
        printf("Thread %d -> %d\n", id, i); // a thread imprime seu número e o valor atual da contagem 
    }

    pthread_mutex_lock(&mutex_vencedor); // bloqueia para nenhuma thread mexer ao mesmo tempo na variável vencedor (seção crítica)
    // se outra thread já estiver com esse mutex, a thread atual espera

    if(vencedor == -1){ // a thread atual pergunta se alguém já ganhou. se o vencedor é -1 ninguém ganhou então
        vencedor = id; // a thread atual ganhou, atribui o id à variável vencedor
    }
    // como isso acontece dentro de um mutex, apenas a primeira thread que chegar aqui com vencedor == -1 consegue registrar a vitória

    pthread_mutex_unlock(&mutex_vencedor); // libera o mutex, permitindo que outras threads entrem na região crítica

    pthread_exit(NULL); // encerra a execução da thread
}

int main(){
    printf("Digite a quantidade de threads: ");
    scanf("%d", &x);

    pthread_t th[x]; // vetor de threads
    int id[x]; // vetor dos identificadores (ids) de cada thread

    pthread_barrier_init(&barreira, NULL, x); // qual barreira é ligada. só libera quando x threads chegarem
    pthread_mutex_init(&mutex_vencedor, NULL); // liga o mutex_vencedor para bloqueio de simultaneidade da variável compartilhada

    for(int i = 0; i < x; i++){ // cria as threads 
        id[i] = i; // id de cada thread
        pthread_create(&th[i], NULL, corrida, &id[i]); //onde vai guardar, atributos padrão, função que a thread vai executar,
                                                      // argumento passado para a função
    }

    for(int i = 0; i < x; i++){
        pthread_join(th[i], NULL); // espera a thread acabar antes de continuar. Evitar que a main termine antes das threads
    }

    printf("\nVencedora: Thread %d\n", vencedor);

    pthread_barrier_destroy(&barreira); // desmonta a barreira
    pthread_mutex_destroy(&mutex_vencedor); // desmonta o mutex

    return 0;
}