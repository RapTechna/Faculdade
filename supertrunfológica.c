#include <stdio.h>
#include <string.h>

// Definição da estrutura da carta
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

// Função para calcular atributos derivados
void calcularAtributos(struct Carta *carta) {
    carta->densidade = carta->populacao / carta->area;
    carta->pibPerCapita = carta->pib / carta->populacao;
}

// Função para imprimir resumo da carta
void imprimirCarta(struct Carta carta) {
    printf("\n%s (%s)", carta.cidade, carta.estado);
    printf("\nPopulação: %d", carta.populacao);
    printf("\nÁrea: %.2f", carta.area);
    printf("\nPIB: %.2f", carta.pib);
    printf("\nPontos Turísticos: %d", carta.pontosTuristicos);
    printf("\nDensidade Populacional: %.2f", carta.densidade);
    printf("\nPIB per capita: %.2f\n", carta.pibPerCapita);
}

// Função para comparar um único atributo (modo básico ou intermediário)
void compararAtributo(struct Carta c1, struct Carta c2, int atributo) {
    float valor1, valor2;
    char nomeAtributo[30];

    switch (atributo) {
        case 1:
            valor1 = c1.populacao;
            valor2 = c2.populacao;
            strcpy(nomeAtributo, "População");
            break;
        case 2:
            valor1 = c1.area;
            valor2 = c2.area;
            strcpy(nomeAtributo, "Área");
            break;
        case 3:
            valor1 = c1.pib;
            valor2 = c2.pib;
            strcpy(nomeAtributo, "PIB");
            break;
        case 4:
            valor1 = c1.pontosTuristicos;
            valor2 = c2.pontosTuristicos;
            strcpy(nomeAtributo, "Pontos Turísticos");
            break;
        case 5:
            valor1 = c1.densidade;
            valor2 = c2.densidade;
            strcpy(nomeAtributo, "Densidade Populacional");
            break;
        case 6:
            valor1 = c1.pibPerCapita;
            valor2 = c2.pibPerCapita;
            strcpy(nomeAtributo, "PIB per capita");
            break;
        default:
            printf("Atributo inválido!\n");
            return;
    }

    printf("\n--- Comparação de Cartas (%s) ---\n", nomeAtributo);
    printf("Carta 1 - %s: %.2f\n", c1.cidade, valor1);
    printf("Carta 2 - %s: %.2f\n", c2.cidade, valor2);

    if (atributo == 5) {  // Densidade → menor vence
        if (valor1 < valor2) printf("Resultado: Carta 1 venceu!\n");
        else if (valor2 < valor1) printf("Resultado: Carta 2 venceu!\n");
        else printf("Empate!\n");
    } else {
        if (valor1 > valor2) printf("Resultado: Carta 1 venceu!\n");
        else if (valor2 > valor1) printf("Resultado: Carta 2 venceu!\n");
        else printf("Empate!\n");
    }
}

// Função para menu dinâmico no nível avançado
int escolherAtributoDisponivel(int indisponivel) {
    int escolha;
    printf("\nEscolha um segundo atributo diferente:\n");
    for (int i = 1; i <= 6; i++) {
        if (i != indisponivel)
            printf("%d - %s\n", i, 
                i==1 ? "População" :
                i==2 ? "Área" :
                i==3 ? "PIB" :
                i==4 ? "Pontos Turísticos" :
                i==5 ? "Densidade Populacional" : "PIB per capita"
            );
    }
    scanf("%d", &escolha);
    return escolha;
}

void compararDoisAtributos(struct Carta c1, struct Carta c2, int a1, int a2) {
    float v1_1, v1_2, v2_1, v2_2;

    float* atributos1[7] = {
        NULL,
        (float*)&c1.populacao,
        &c1.area,
        &c1.pib,
        (float*)&c1.pontosTuristicos,
        &c1.densidade,
        &c1.pibPerCapita
    };
    float* atributos2[7] = {
        NULL,
        (float*)&c2.populacao,
        &c2.area,
        &c2.pib,
        (float*)&c2.pontosTuristicos,
        &c2.densidade,
        &c2.pibPerCapita
    };

    v1_1 = *atributos1[a1];
    v1_2 = *atributos1[a2];
    v2_1 = *atributos2[a1];
    v2_2 = *atributos2[a2];

    float p1 = 0, p2 = 0;

    // Compara primeiro atributo
    if ((a1 == 5 && v1_1 < v2_1) || (a1 != 5 && v1_1 > v2_1)) p1++;
    else if (v1_1 != v2_1) p2++;

    // Compara segundo atributo
    if ((a2 == 5 && v1_2 < v2_2) || (a2 != 5 && v1_2 > v2_2)) p1++;
    else if (v1_2 != v2_2) p2++;

    printf("\n--- Comparação Avançada ---\n");
    printf("Carta 1: %.2f (attr1) + %.2f (attr2) = %.2f\n", v1_1, v1_2, v1_1 + v1_2);
    printf("Carta 2: %.2f (attr1) + %.2f (attr2) = %.2f\n", v2_1, v2_2, v2_1 + v2_2);

    (p1 > p2) ? printf("Resultado: Carta 1 venceu!\n") :
    (p2 > p1) ? printf("Resultado: Carta 2 venceu!\n") :
                printf("Resultado: Empate!\n");
}

int main() {
    struct Carta carta1 = {"SP", "SP01", "São Paulo", 12300000, 1521.11, 750000.0, 25};
    struct Carta carta2 = {"RJ", "RJ01", "Rio de Janeiro", 6700000, 1182.30, 350000.0, 18};

    calcularAtributos(&carta1);
    calcularAtributos(&carta2);

    int opcao;
    printf("Super Trunfo - Modos de Comparação\n");
    printf("1 - Modo Básico (comparação fixa)\n");
    printf("2 - Modo Interativo (1 atributo)\n");
    printf("3 - Modo Avançado (2 atributos)\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            compararAtributo(carta1, carta2, 1); // Comparar População
            break;
        case 2: {
            int atributo;
            printf("\nEscolha um atributo para comparar:\n");
            printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade\n6 - PIB per capita\n");
            scanf("%d", &atributo);
            compararAtributo(carta1, carta2, atributo);
            break;
        }
        case 3: {
            int a1, a2;
            printf("\nEscolha o primeiro atributo:\n1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade\n6 - PIB per capita\n");
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
