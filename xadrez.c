#include <stdio.h>

#define TAM 8

// Função para mostrar o tabuleiro simples (apenas coordenadas)
void mostrarTabuleiro() {
    printf("  ");
    for (int c = 1; c <= TAM; c++) {
        printf(" %d ", c);
    }
    printf("\n");

    for (int l = 1; l <= TAM; l++) {
        printf("%d ", l);
        for (int c = 1; c <= TAM; c++) {
            printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

// Função para imprimir movimentos da Torre a partir da posição (linha, coluna)
void moverTorre(int linha, int coluna) {
    printf("Movimentos possíveis da TORRE a partir de (%d, %d):\n", linha, coluna);

    // Movimentos na mesma linha (horizontal)
    for (int c = 1; c <= TAM; c++) {
        if (c != coluna) {
            printf("(%d, %d)\n", linha, c);
        }
    }
    // Movimentos na mesma coluna (vertical)
    for (int l = 1; l <= TAM; l++) {
        if (l != linha) {
            printf("(%d, %d)\n", l, coluna);
        }
    }
}

// Função para imprimir movimentos do Bispo a partir da posição (linha, coluna)
void moverBispo(int linha, int coluna) {
    printf("Movimentos possíveis do BISPO a partir de (%d, %d):\n", linha, coluna);

    // Diagonais: cima-esquerda, cima-direita, baixo-esquerda, baixo-direita
    int l, c;

    // Cima-Esquerda
    l = linha - 1; c = coluna - 1;
    while (l >= 1 && c >= 1) {
        printf("(%d, %d)\n", l, c);
        l--; c--;
    }

    // Cima-Direita
    l = linha - 1; c = coluna + 1;
    while (l >= 1 && c <= TAM) {
        printf("(%d, %d)\n", l, c);
        l--; c++;
    }

    // Baixo-Esquerda
    l = linha + 1; c = coluna - 1;
    while (l <= TAM && c >= 1) {
        printf("(%d, %d)\n", l, c);
        l++; c--;
    }

    // Baixo-Direita
    l = linha + 1; c = coluna + 1;
    while (l <= TAM && c <= TAM) {
        printf("(%d, %d)\n", l, c);
        l++; c++;
    }
}

// Função para imprimir movimentos da Rainha (combina torre + bispo)
void moverRainha(int linha, int coluna) {
    printf("Movimentos possíveis da RAINHA a partir de (%d, %d):\n", linha, coluna);

    // Torre (linha e coluna)
    moverTorre(linha, coluna);
    // Bispo (diagonais)
    moverBispo(linha, coluna);
}

// Função para imprimir movimentos do Cavalo a partir da posição (linha, coluna)
void moverCavalo(int linha, int coluna) {
    printf("Movimentos possíveis do CAVALO a partir de (%d, %d):\n", linha, coluna);

    int movimentos[8][2] = {
        {linha - 2, coluna - 1},
        {linha - 2, coluna + 1},
        {linha - 1, coluna - 2},
        {linha - 1, coluna + 2},
        {linha + 1, coluna - 2},
        {linha + 1, coluna + 2},
        {linha + 2, coluna - 1},
        {linha + 2, coluna + 1},
    };

    for (int i = 0; i < 8; i++) {
        int l = movimentos[i][0];
        int c = movimentos[i][1];
        if (l >= 1 && l <= TAM && c >= 1 && c <= TAM) {
            printf("(%d, %d)\n", l, c);
        }
    }
}

int main() {
    int linha, coluna, escolha;

    mostrarTabuleiro();

    printf("Escolha a peça para mover:\n");
    printf("1 - Torre\n");
    printf("2 - Bispo\n");
    printf("3 - Rainha\n");
    printf("4 - Cavalo\n");
    printf("Digite o número da peça: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > 4) {
        printf("Opção inválida.\n");
        return 1;
    }

    printf("Informe a posição da peça (linha e coluna entre 1 e 8):\n");
    printf("Linha: ");
    scanf("%d", &linha);
    printf("Coluna: ");
    scanf("%d", &coluna);

    if (linha < 1 || linha > TAM || coluna < 1 || coluna > TAM) {
        printf("Posição inválida!\n");
        return 1;
    }

    printf("\n");

    switch (escolha) {
        case 1:
            moverTorre(linha, coluna);
            break;
        case 2:
            moverBispo(linha, coluna);
            break;
        case 3:
            moverRainha(linha, coluna);
            break;
        case 4:
            moverCavalo(linha, coluna);
            break;
    }

    return 0;
}
