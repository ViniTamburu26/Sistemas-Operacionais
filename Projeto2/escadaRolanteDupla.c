#include <stdio.h>

int main() {
    int N;
    int t, d;
    int totalTime = 0;

    printf("Digite o número de pessoas que usarão a escada rolante: ");
    scanf("%d", &N);

    int dValues[N];
    int tValues[N];

    printf("Digite o momento de chegada e a direção (0 para esquerda, 1 para direita) para cada pessoa:\n");

    // Leitura dos valores de d e cálculo inicial do totalTime
    for (int i = 0; i < N; i++) {
        printf("Pessoa %d: ", i + 1);
        scanf("%d %d", &t, &d);

        dValues[i] = d;  // Armazena os valores de d
        tValues[i] = t;  // Armazena os valores de t
    }


    for (int i = 0; i < N; i++) {
        if(dValues[i + 1] == dValues[i]){
            totalTime += tValues[i + 1] - tValues[i];
        }else{
            int soma = tValues[i] - totalTime;
            totalTime += soma + 10;
        }

    }

    printf("O momento em que a última pessoa saiu da escada é: %d\n", totalTime);

    return 0;
}
