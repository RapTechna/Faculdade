#include <stdio.h>

// =======================
// FUNÇÕES RECURSIVAS (Nível Mestre)
// =======================

// Torre: 5 casas para a direita (recursivo)
void moverTorre(int passoAtual, int totalPassos) {
    if (passoAtual > totalPassos) return;
    printf("Direita\n");
    moverTorre(passoAtual + 1, totalPassos);
}

// Rainha: 8 casas para a esquerda (recursivo)
void moverRainha(int passoAtual, int totalPassos) {
    if (passoAtual > totalPassos) return;
    printf("Esquerda\n");
    moverRainha(passoAtual + 1, totalPassos);
}

// Bispo: 5 casas na diagonal (cima+direita), recursivo + loops aninhados
void moverBispo(int linha, int total) {
    if (linha > total) return;

    for (int coluna = 1; coluna <= 1; coluna++) {
        printf("Cima Direita\n");
    }

    moverBispo(linha + 1, total);
}

// =======================
// FUNÇÃO COM LOOP COMPLEXO (Cavalo - Nível Mestre)
// =======================

// Cavalo: movimenta em "L" (2 para cima e 1 para direita) com loops aninhados complexos
void moverCavalo() {
    int movimentosVerticais = 2;
    int movimentosHorizontais = 1;

    printf("Movimento do CAVALO (loops complexos):\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0 && j < movimentosVerticais) {
                printf("Cima\n");
                continue;
            }
            if (i == 1 && j == 0) {
                printf("Direita\n");
                break;
            }
        }
        if (i == 1) break;
    }
}

// =======================
// FUNÇÕES SIMPLES (Nível Básico e Intermediário)
// =======================

// Torre (for) - 5 casas para a direita
void torreFor() {
    printf("Movimento da TORRE (for):\n");
    for (int i = 1; i <= 5; i++) {
        printf("Direita\n");
    }
}

// Bispo (while) - 5 casas na diagonal cima-direita
void bispoWhile() {
    printf("Movimento do BISPO (while):\n");
    int j = 1;
    while (j <= 5) {
        printf("Cima Direita\n");
        j++;
    }
}

// Rainha (do-while) - 8 casas para a esquerda
void rainhaDoWhile() {
    printf("Movimento da RAINHA (do-while):\n");
    int k = 1;
    do {
        printf("Esquerda\n");
        k++;
    } while (k <= 8);
}

// Cavalo (for + while) - 2 casas para baixo, 1 para esquerda (nível intermediário)
void cavaloLoops() {
    int passos_para_baixo = 2;
    int passos_para_esquerda = 1;

    printf("Movimento do CAVALO (for + while):\n");

    for (int i = 0; i < passos_para_baixo; i++) {
        printf("Baixo\n");

        if (i == passos_para_baixo - 1) {
            int cont = 0;
            while (cont < passos_para_esquerda) {
                printf("Esquerda\n");
                cont++;
            }
        }
    }
}

// =======================
// FUNÇÃO PRINCIPAL
// =======================
int main() {
    // --- Nível Básico ---
    torreFor();
    printf("--------------------------\n");
    bispoWhile();
    printf("--------------------------\n");
    rainhaDoWhile();
    printf("--------------------------\n");
    cavaloLoops();

    printf("\n==========================\n");
    printf("Movimentos com Recursividade e Loops Complexos (Nível Mestre)\n\n");

    // --- Nível Mestre ---
    printf("Movimento da TORRE (recursivo):\n");
    moverTorre(1, 5);
    printf("\nMovimento do BISPO (recursivo + loops aninhados):\n");
    moverBispo(1, 5);
    printf("\nMovimento da RAINHA (recursivo):\n");
    moverRainha(1, 8);
    printf("\n");
    moverCavalo();

    return 0;
}
