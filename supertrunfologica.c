#include <stdio.h>
#include <string.h>

typedef struct {
    char estado[3];          // Ex: "SP"
    char codigo[10];         // Ex: "C001"
    char nomeCidade[50];     // Ex: "São Paulo"
    char nomePais[50];       // Ex: "Brasil"
    unsigned long populacao;
    float area;              // em km²
    float pib;               // em bilhões
    int pontosTuristicos;
    // Atributos calculados
    float densidadePop;
    float pibPerCapita;
    float superPoder;
} Carta;

// Função para ler dados da carta
void lerCarta(Carta *carta, int numCarta) {
    printf("Digite os dados da Carta %d:\n", numCarta);
    printf("Estado (ex: SP): ");
    scanf(" %2s", carta->estado);
    printf("Código da Carta (ex: C001): ");
    scanf(" %9s", carta->codigo);
    printf("Nome da Cidade: ");
    scanf(" %49[^\n]", carta->nomeCidade);
    printf("Nome do País: ");
    scanf(" %49[^\n]", carta->nomePais);
    printf("População: ");
    scanf("%lu", &carta->populacao);
    printf("Área (km²): ");
    scanf("%f", &carta->area);
    printf("PIB (bilhões): ");
    scanf("%f", &carta->pib);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
    printf("\n");
}

// Função para calcular atributos derivados da carta
void calcularAtributos(Carta *carta) {
    if (carta->area > 0)
        carta->densidadePop = (float)carta->populacao / carta->area;
    else
        carta->densidadePop = 0;

    if (carta->populacao > 0)
        carta->pibPerCapita = (carta->pib * 1e9f) / carta->populacao;  // Convertendo PIB bilhões para reais
    else
        carta->pibPerCapita = 0;

    // Super Poder (soma ponderada dos atributos, pode ser ajustada)
    carta->superPoder = (float)carta->populacao + carta->area + (carta->pib * 1e9f) + (float)carta->pontosTuristicos +
                        carta->pibPerCapita + (carta->densidadePop > 0 ? (1.0f / carta->densidadePop) : 0);
}

// Função para exibir os dados completos da carta
void exibirCarta(const Carta *carta, int numCarta) {
    printf("Carta %d:\n", numCarta);
    printf("Estado: %s\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Cidade: %s\n", carta->nomeCidade);
    printf("País: %s\n", carta->nomePais);
    printf("População: %lu\n", carta->populacao);
    printf("Área: %.2f km²\n", carta->area);
    printf("PIB: %.2f bilhões\n", carta->pib);
    printf("Pontos Turísticos: %d\n", carta->pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta->densidadePop);
    printf("PIB per Capita: %.2f reais\n", carta->pibPerCapita);
    printf("Super Poder: %.2f\n\n", carta->superPoder);
}

// Imprime resumo para os níveis de comparação
void imprimirCartaResumo(Carta c) {
    printf("%s (%s - %s) [%s]:\n", c.nomeCidade, c.estado, c.nomePais, c.codigo);
    printf("População: %lu\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Pontos turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidadePop);
    printf("PIB per capita: %.2f reais/habitante\n\n", c.pibPerCapita);
}

// Função para obter valor do atributo (usada na comparação)
float obterValorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.densidadePop;
        case 6: return c.pibPerCapita;
        case 7: return c.superPoder;
        default: return 0.0f;
    }
}

// Nome dos atributos para exibir no menu e resultados
void obterNomeAtributo(int atributo, char *nome) {
    switch (atributo) {
        case 1: strcpy(nome, "População"); break;
        case 2: strcpy(nome, "Área"); break;
        case 3: strcpy(nome, "PIB"); break;
        case 4: strcpy(nome, "Número de Pontos Turísticos"); break;
        case 5: strcpy(nome, "Densidade Populacional"); break;
        case 6: strcpy(nome, "PIB per Capita"); break;
        case 7: strcpy(nome, "Super Poder"); break;
        default: strcpy(nome, "Desconhecido"); break;
    }
}

// Regra de comparação: para densidade populacional menor é melhor, para PIB per capita e super poder maior é melhor
int compararValores(float v1, float v2, int atributo) {
    if (atributo == 5) { // densidade populacional: menor é melhor
        if (v1 < v2) return 1;
        else if (v1 > v2) return 2;
        else return 0;
    } else { // para os outros, maior é melhor
        if (v1 > v2) return 1;
        else if (v1 < v2) return 2;
        else return 0;
    }
}

// Menu para escolher atributo (com exclusão opcional para o segundo atributo no nível mestre)
int escolherAtributo(int excluir) {
    int opcao;
    printf("Escolha o atributo para comparar:\n");
    if (excluir != 1) printf("1 - População\n");
    if (excluir != 2) printf("2 - Área\n");
    if (excluir != 3) printf("3 - PIB\n");
    if (excluir != 4) printf("4 - Número de Pontos Turísticos\n");
    if (excluir != 5) printf("5 - Densidade Populacional\n");
    if (excluir != 6) printf("6 - PIB per Capita\n");
    if (excluir != 7) printf("7 - Super Poder\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 7 || opcao == excluir) {
        printf("Opção inválida. Tente novamente.\n\n");
        return escolherAtributo(excluir);
    }
    return opcao;
}

// Nível Básico: comparação fixa de um atributo
void nivelBasico(Carta c1, Carta c2, int atributo) {
    char nomeAtr[40];
    obterNomeAtributo(atributo, nomeAtr);

    float val1 = obterValorAtributo(c1, atributo);
    float val2 = obterValorAtributo(c2, atributo);

    printf("\n=== Nível Básico - Comparação fixa (%s) ===\n\n", nomeAtr);
    imprimirCartaResumo(c1);
    imprimirCartaResumo(c2);

    printf("Comparando atributo fixo: %s\n", nomeAtr);
    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, val1);
    printf("Carta 2 - %s: %.2f\n\n", c2.nomeCidade, val2);

    int resultado = compararValores(val1, val2, atributo);
    if (resultado == 1) printf("Resultado: Carta 1 (%s) venceu!\n", c1.nomeCidade);
    else if (resultado == 2) printf("Resultado: Carta 2 (%s) venceu!\n", c2.nomeCidade);
    else printf("Resultado: Empate!\n");
}

// Nível Intermediário: menu para escolher um atributo
void nivelIntermediario(Carta c1, Carta c2) {
    printf("\n=== Nível Intermediário - Escolha um atributo ===\n\n");
    imprimirCartaResumo(c1);
    imprimirCartaResumo(c2);

    int atributo = escolherAtributo(0);
    char nomeAtr[40];
    obterNomeAtributo(atributo, nomeAtr);

    float val1 = obterValorAtributo(c1, atributo);
    float val2 = obterValorAtributo(c2, atributo);

    printf("\nComparando pelo atributo: %s\n", nomeAtr);
    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, val1);
    printf("Carta 2 - %s: %.2f\n\n", c2.nomeCidade, val2);

    int resultado = compararValores(val1, val2, atributo);
    if (resultado == 1) printf("Resultado: Carta 1 (%s) venceu!\n", c1.nomeCidade);
    else if (resultado == 2) printf("Resultado: Carta 2 (%s) venceu!\n", c2.nomeCidade);
    else printf("Resultado: Empate!\n");
}

// Nível Mestre: escolher dois atributos diferentes, comparar e somar
void nivelMestre(Carta c1, Carta c2) {
    printf("\n=== Nível Mestre - Comparação com dois atributos ===\n\n");
    imprimirCartaResumo(c1);
    imprimirCartaResumo(c2);

    int atr1 = escolherAtributo(0);
    int atr2 = escolherAtributo(atr1);

    char nomeAtr1[40], nomeAtr2[40];
    obterNomeAtributo(atr1, nomeAtr1);
    obterNomeAtributo(atr2, nomeAtr2);

    float val1Atr1 = obterValorAtributo(c1, atr1);
    float val2Atr1 = obterValorAtributo(c2, atr1);
    float val1Atr2 = obterValorAtributo(c1, atr2);
    float val2Atr2 = obterValorAtributo(c2, atr2);

    printf("\nComparação por atributos selecionados:\n\n");

    printf("Atributo 1 - %s:\n", nomeAtr1);
    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, val1Atr1);
    printf("Carta 2 - %s: %.2f\n\n", c2.nomeCidade, val2Atr1);

    printf("Atributo 2 - %s:\n", nomeAtr2);
    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, val1Atr2);
    printf("Carta 2 - %s: %.2f\n\n", c2.nomeCidade, val2Atr2);

    // Resultado individual
    int resAtr1 = compararValores(val1Atr1, val2Atr1, atr1);
    int resAtr2 = compararValores(val1Atr2, val2Atr2, atr2);

    // Soma dos valores (para decisão final)
    float somaC1 = val1Atr1 + val1Atr2;
    float somaC2 = val2Atr1 + val2Atr2;

    printf("Soma dos atributos:\n");
    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, somaC1);
    printf("Carta 2 - %s: %.2f\n\n", c2.nomeCidade, somaC2);

    if (somaC1 > somaC2) printf("Resultado final: Carta 1 (%s) venceu!\n", c1.nomeCidade);
    else if (somaC2 > somaC1) printf("Resultado final: Carta 2 (%s) venceu!\n", c2.nomeCidade);
    else printf("Resultado final: Empate!\n");
}

int main() {
    Carta carta1, carta2;

    printf("=== Cadastro da Carta 1 ===\n");
    lerCarta(&carta1, 1);
    calcularAtributos(&carta1);

    printf("=== Cadastro da Carta 2 ===\n");
    lerCarta(&carta2, 2);
    calcularAtributos(&carta2);

    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);

    int opcaoNivel;
    printf("Escolha o nível para comparação:\n");
    printf("1 - Nível Básico (atributo fixo)\n");
    printf("2 - Nível Intermediário (menu escolha um atributo)\n");
    printf("3 - Nível Mestre (escolha dois atributos)\n");
    printf("Opção: ");
    scanf("%d", &opcaoNivel);

    switch (opcaoNivel) {
        case 1: {
            printf("Escolha o atributo fixo para comparar:\n");
            printf("1 - População\n2 - Área\n3 - PIB\n4 - Número de Pontos Turísticos\n5 - Densidade Populacional\n6 - PIB per Capita\n7 - Super Poder\n");
            int atr;
            scanf("%d", &atr);
            nivelBasico(carta1, carta2, atr);
            break;
        }
        case 2:
            nivelIntermediario(carta1, carta2);
            break;
        case 3:
            nivelMestre(carta1, carta2);
            break;
        default:
            printf("Opção inválida. Finalizando.\n");
            break;
    }

    return 0;
}
