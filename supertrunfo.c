#include <stdio.h>

typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    unsigned long int populacao;
    float area;
    float pib; // bilhões
    int pontosTuristicos;

    // Atributos calculados
    float densidadePopulacional;
    float pibPerCapita;
    float superPoder;
} Carta;

// Função para ler dados de uma carta
void lerCarta(Carta *carta, int numCarta) {
    printf("Digite os dados da Carta %d:\n", numCarta);
    printf("Estado (A-H): ");
    scanf(" %c", &carta->estado);
    printf("Codigo da Carta (ex: A01): ");
    scanf("%3s", carta->codigo);
    printf("Nome da Cidade: ");
    scanf(" %49[^\n]", carta->nomeCidade);
    printf("Populacao: ");
    scanf("%lu", &carta->populacao);
    printf("Area (km2): ");
    scanf("%f", &carta->area);
    printf("PIB (bilhoes): ");
    scanf("%f", &carta->pib);
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta->pontosTuristicos);
    printf("\n");
}

// Função para calcular atributos derivados da carta
void calcularAtributos(Carta *carta) {
    carta->densidadePopulacional = carta->populacao / carta->area;
    carta->pibPerCapita = (carta->pib * 1e9f) / carta->populacao;  // PIB em reais
    carta->superPoder = (float)carta->populacao + carta->area + carta->pib + (float)carta->pontosTuristicos +
                        carta->pibPerCapita + (1.0f / carta->densidadePopulacional);
}

// Função para exibir os dados da carta
void exibirCarta(const Carta *carta, int numCarta) {
    printf("Carta %d:\n", numCarta);
    printf("Estado: %c\n", carta->estado);
    printf("Codigo: %s\n", carta->codigo);
    printf("Nome da Cidade: %s\n", carta->nomeCidade);
    printf("Populacao: %lu\n", carta->populacao);
    printf("Area: %.2f km²\n", carta->area);
    printf("PIB: %.2f bilhoes de reais\n", carta->pib);
    printf("Numero de Pontos Turisticos: %d\n", carta->pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta->densidadePopulacional);
    printf("PIB per Capita: %.2f reais\n", carta->pibPerCapita);
    printf("Super Poder: %.2f\n\n", carta->superPoder);
}

// Função para comparar atributos e imprimir o vencedor
void compararAtributos(const Carta *c1, const Carta *c2) {
    printf("Comparacao de Cartas:\n");

    int pop1 = (c1->populacao > c2->populacao) ? 1 : 0;
    printf("Populacao: Carta %d venceu (%d)\n", pop1 ? 1 : 2, pop1);

    int area1 = (c1->area > c2->area) ? 1 : 0;
    printf("Area: Carta %d venceu (%d)\n", area1 ? 1 : 2, area1);

    int pib1 = (c1->pib > c2->pib) ? 1 : 0;
    printf("PIB: Carta %d venceu (%d)\n", pib1 ? 1 : 2, pib1);

    int ptur1 = (c1->pontosTuristicos > c2->pontosTuristicos) ? 1 : 0;
    printf("Pontos Turisticos: Carta %d venceu (%d)\n", ptur1 ? 1 : 2, ptur1);

    // Para densidade populacional, menor é melhor
    int dens1 = (c1->densidadePopulacional < c2->densidadePopulacional) ? 1 : 0;
    printf("Densidade Populacional: Carta %d venceu (%d)\n", dens1 ? 1 : 2, dens1);

    int pibpc1 = (c1->pibPerCapita > c2->pibPerCapita) ? 1 : 0;
    printf("PIB per Capita: Carta %d venceu (%d)\n", pibpc1 ? 1 : 2, pibpc1);

    int sp1 = (c1->superPoder > c2->superPoder) ? 1 : 0;
    printf("Super Poder: Carta %d venceu (%d)\n", sp1 ? 1 : 2, sp1);
}

int main() {
    Carta carta1, carta2;

    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);

    calcularAtributos(&carta1);
    calcularAtributos(&carta2);

    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);

    compararAtributos(&carta1, &carta2);

    return 0;
}
