#include <stdio.h>
#include <string.h>

// ---------- DEFINIÇÃO DA STRUCT ----------

struct Carta {
    char estado[30];
    char codigo[10];
    char cidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
};

// ---------- FUNÇÕES AUXILIARES ----------

void calcularAtributos(struct Carta *carta) {
    carta->densidade = carta->populacao / carta->area;
    carta->pibPerCapita = carta->pib / carta->populacao;
}

void imprimirCarta(struct Carta carta) {
    printf("\n--- Carta: %s (%s) ---\n", carta.cidade, carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("População: %d\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidade);
    printf("PIB per capita: %.2f\n", carta.pibPerCapita);
}

void compararAtributo(struct Carta c1, struct Carta c2, int atributo) {
    float valor1, valor2;
    char nomeAtributo[30];

    switch (atributo) {
        case 1: valor1 = c1.populacao; valor2 = c2.populacao; strcpy(nomeAtributo, "População"); break;
        case 2: valor1 = c1.area; valor2 = c2.area; strcpy(nomeAtributo, "Área"); break;
        case 3: valor1 = c1.pib; valor2 = c2.pib; strcpy(nomeAtributo, "PIB"); break;
        case 4: valor1 = c1.pontosTuristicos; valor2 = c2.pontosTuristicos; strcpy(nomeAtributo, "Pontos Turísticos"); break;
        case 5: valor1 = c1.densidade; valor2 = c2.densidade; strcpy(nomeAtributo, "Densidade Populacional"); break;
        case 6: valor1 = c1.pibPerCapita; valor2 = c2.pibPerCapita; strcpy(nomeAtributo, "PIB per capita"); break;
        default: printf("Atributo inválido!\n"); return;
    }

    printf("\n--- Comparação: %s ---\n", nomeAtributo);
    printf("Carta 1: %.2f\n", valor1);
    printf("Carta 2: %.2f\n", valor2);

    if (atributo == 5) {
        if (valor1 < valor2) printf("Resultado: Carta 1 venceu!\n");
        else if (valor2 < valor1) printf("Resultado: Carta 2 venceu!\n");
        else printf("Empate!\n");
    } else {
        if (valor1 > valor2) printf("Resultado: Carta 1 venceu!\n");
        else if (valor2 > valor1) printf("Resultado: Carta 2 venceu!\n");
        else printf("Empate!\n");
    }
}

int escolherAtributoDisponivel(int indisponivel) {
    int escolha;
    printf("\nEscolha o segundo atributo (diferente do anterior):\n");
    for (int i = 1; i <= 6; i++) {
        if (i != indisponivel)
            printf("%d - %s\n", i,
                i==1 ? "População" :
                i==2 ? "Área" :
                i==3 ? "PIB" :
                i==4 ? "Pontos Turísticos" :
                i==5 ? "Densidade Populacional" :
                       "PIB per capita");
    }
    scanf("%d", &escolha);
    return escolha;
}

void compararDoisAtributos(struct Carta c1, struct Carta c2, int a1, int a2) {
    float *atributos1[7] = {NULL, (float*)&c1.populacao, &c1.area, &c1.pib, (float*)&c1.pontosTuristicos, &c1.densidade, &c1.pibPerCapita};
    float *atributos2[7] = {NULL, (float*)&c2.populacao, &c2.area, &c2.pib, (float*)&c2.pontosTuristicos, &c2.densidade, &c2.pibPerCapita};

    float v1_1 = *atributos1[a1], v1_2 = *atributos1[a2];
    float v2_1 = *atributos2[a1], v2_2 = *atributos2[a2];
    int p1 = 0, p2 = 0;

    if ((a1 == 5 && v1_1 < v2_1) || (a1 != 5 && v1_1 > v2_1)) p1++; else if (v1_1 != v2_1) p2++;
    if ((a2 == 5 && v1_2 < v2_2) || (a2 != 5 && v1_2 > v2_2)) p1++; else if (v1_2 != v2_2) p2++;

    printf("\n--- Comparação Avançada ---\n");
    printf("Carta 1: %.2f + %.2f = %.2f\n", v1_1, v1_2, v1_1 + v1_2);
    printf("Carta 2: %.2f + %.2f = %.2f\n", v2_1, v2_2, v2_1 + v2_2);

    (p1 > p2) ? printf("Resultado: Carta 1 venceu!\n") :
    (p2 > p1) ? printf("Resultado: Carta 2 venceu!\n") :
                printf("Resultado: Empate!\n");
}

// ---------- MAIN ----------

int main() {
    struct Carta carta1, carta2;

    // Cadastro manual das cartas
    printf("Cadastro da Carta 1:\n");
    printf("Estado: "); scanf(" %[^\n]", carta1.estado);
    printf("Código: "); scanf("%s", carta1.codigo);
    printf("Cidade: "); scanf(" %[^\n]", carta1.cidade);
    printf("População: "); scanf("%d", &carta1.populacao);
    printf("Área: "); scanf("%f", &carta1.area);
    printf("PIB (em bilhões): "); scanf("%f", &carta1.pib);
    printf("Pontos Turísticos: "); scanf("%d", &carta1.pontosTuristicos);

    printf("\nCadastro da Carta 2:\n");
    printf("Estado: "); scanf(" %[^\n]", carta2.estado);
    printf("Código: "); scanf("%s", carta2.codigo);
    printf("Cidade: "); scanf(" %[^\n]", carta2.cidade);
    printf("População: "); scanf("%d", &carta2.populacao);
    printf("Área: "); scanf("%f", &carta2.area);
    printf("PIB (em bilhões): "); scanf("%f", &carta2.pib);
    printf("Pontos Turísticos: "); scanf("%d", &carta2.pontosTuristicos);

    // Cálculos
    calcularAtributos(&carta1);
    calcularAtributos(&carta2);

    // Exibição
    imprimirCarta(carta1);
    imprimirCarta(carta2);

    // Menu
    int opcao;
    printf("\nEscolha o modo de comparação:\n");
    printf("1 - Modo Básico (População)\n");
    printf("2 - Modo Interativo (1 atributo)\n");
    printf("3 - Modo Avançado (2 atributos)\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            compararAtributo(carta1, carta2, 1);
            break;
        case 2: {
            int atributo;
            printf("Escolha o atributo (1 a 6): ");
            scanf("%d", &atributo);
            compararAtributo(carta1, carta2, atributo);
            break;
        }
        case 3: {
            int a1, a2;
            printf("Escolha o primeiro atributo (1 a 6): ");
            scanf("%d", &a1);
            a2 = escolherAtributoDisponivel(a1);
            compararDoisAtributos(carta1, carta2, a1, a2);
            break;
        }
        default:
            printf("Opção inválida!\n");
    }

    return 0;
}
