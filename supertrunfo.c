#include <stdio.h>

int main() {
    // ----------- DECLARAÇÃO DE VARIÁVEIS -----------

    // Carta 1
    char estado1;
    char codigo1[4];
    char nome1[50];
    unsigned long int populacao1;
    float area1, pib1;
    int pontos1;

    // Carta 2
    char estado2;
    char codigo2[4];
    char nome2[50];
    unsigned long int populacao2;
    float area2, pib2;
    int pontos2;

    // Indicadores
    float densidade1, densidade2;
    float pibPerCapita1, pibPerCapita2;
    float superPoder1, superPoder2;

    // Resultados de comparação (1 = Carta 1 venceu, 0 = Carta 2 venceu)
    int resPopulacao, resArea, resPib, resPontos, resDensidade, resPibPC, resSuperPoder;

    // ----------- ENTRADA DE DADOS -----------

    printf("Cadastro da Carta 1:\n");

    printf("Estado (A-H): ");
    scanf(" %c", &estado1);

    printf("Código da Carta (ex: A01): ");
    scanf("%s", codigo1);

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nome1);

    printf("População: ");
    scanf("%lu", &populacao1);

    printf("Área (km²): ");
    scanf("%f", &area1);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib1);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontos1);


    printf("\nCadastro da Carta 2:\n");

    printf("Estado (A-H): ");
    scanf(" %c", &estado2);

    printf("Código da Carta (ex: B02): ");
    scanf("%s", codigo2);

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nome2);

    printf("População: ");
    scanf("%lu", &populacao2);

    printf("Área (km²): ");
    scanf("%f", &area2);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib2);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontos2);

    // ----------- CÁLCULOS -----------

    densidade1 = populacao1 / area1;
    densidade2 = populacao2 / area2;

    pibPerCapita1 = pib1 / populacao1;
    pibPerCapita2 = pib2 / populacao2;

    superPoder1 = populacao1 + area1 + pib1 + pontos1 + pibPerCapita1 + (1.0 / densidade1);
    superPoder2 = populacao2 + area2 + pib2 + pontos2 + pibPerCapita2 + (1.0 / densidade2);

    // ----------- EXIBIÇÃO DAS CARTAS -----------

    printf("\nCarta 1:\n");
    printf("Estado: %c\n", estado1);
    printf("Código: %s\n", codigo1);
    printf("Nome da Cidade: %s\n", nome1);
    printf("População: %lu\n", populacao1);
    printf("Área: %.2f km²\n", area1);
    printf("PIB: %.2f bilhões de reais\n", pib1);
    printf("Número de Pontos Turísticos: %d\n", pontos1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita1);
    printf("Super Poder: %.2f\n", superPoder1);

    printf("\nCarta 2:\n");
    printf("Estado: %c\n", estado2);
    printf("Código: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", nome2);
    printf("População: %lu\n", populacao2);
    printf("Área: %.2f km²\n", area2);
    printf("PIB: %.2f bilhões de reais\n", pib2);
    printf("Número de Pontos Turísticos: %d\n", pontos2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita2);
    printf("Super Poder: %.2f\n", superPoder2);

    // ----------- COMPARAÇÕES -----------

    resPopulacao = populacao1 > populacao2;
    resArea = area1 > area2;
    resPib = pib1 > pib2;
    resPontos = pontos1 > pontos2;
    resDensidade = densidade1 < densidade2;  // menor vence
    resPibPC = pibPerCapita1 > pibPerCapita2;
    resSuperPoder = superPoder1 > superPoder2;

    // ----------- RESULTADOS DAS COMPARAÇÕES -----------

    printf("\nComparação de Cartas:\n");
    printf("População: Carta 1 venceu (%d)\n", resPopulacao);
    printf("Área: Carta 1 venceu (%d)\n", resArea);
    printf("PIB: Carta 1 venceu (%d)\n", resPib);
    printf("Pontos Turísticos: Carta 1 venceu (%d)\n", resPontos);
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", resDensidade);
    printf("PIB per Capita: Carta 1 venceu (%d)\n", resPibPC);
    printf("Super Poder: Carta 1 venceu (%d)\n", resSuperPoder);

    return 0;
}
