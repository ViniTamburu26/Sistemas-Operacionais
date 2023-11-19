#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct {
    int arrivalTime;
    int direction;
} Person;

sem_t mutex; // Semáforo para controlar o acesso à escada
int currentTime = 0; // Variável global para acompanhar o tempo atual
int lastPersonExitTime = 0; // Variável para armazenar o momento em que a última pessoa saiu da escada

void *escalator(void *arg) {
    Person *person = (Person *)arg;

    // Espera até o momento de chegada da pessoa
    sleep(person->arrivalTime - currentTime);

    sem_wait(&mutex); // Bloqueia o acesso à escada

    // Simula a viagem na escada (leva 10 segundos)
    sleep(10);
    currentTime = person->arrivalTime + 10; // Atualiza o tempo atual após a pessoa sair

    sem_post(&mutex); // Libera o acesso à escada
    lastPersonExitTime = currentTime; // Atualiza o momento em que a última pessoa saiu da escada

    pthread_exit(NULL);
}

int main() {
    int numPeople;
    printf("Digite o número de pessoas que usarão a escada rolante: ");
    scanf("%d", &numPeople);

    Person people[numPeople];

    printf("Digite o momento de chegada e a direção (0 para esquerda, 1 para direita) para cada pessoa:\n");
    for (int i = 0; i < numPeople; i++) {
        printf("Pessoa %d: ", i + 1);
        scanf("%d %d", &people[i].arrivalTime, &people[i].direction);
    }

    sem_init(&mutex, 0, 1); // Inicializa o semáforo

    pthread_t threads[numPeople];
    for (int i = 0; i < numPeople; i++) {
        pthread_create(&threads[i], NULL, escalator, (void *)&people[i]);
    }

    for (int i = 0; i < numPeople; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex); // Destrói o semáforo após o uso

    printf("O momento em que a última pessoa saiu da escada é: %d\n", lastPersonExitTime);

    return 0;
}
