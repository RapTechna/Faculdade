#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 8

char tabuleiro[TAM][TAM];

// Inicializa o tabuleiro com peças fixas para teste
void inicializarTabuleiro() {
    // Limpa tabuleiro
    for (int l = 0; l < TAM; l++) {
        for (int c = 0; c < TAM; c++) {
            tabuleiro[l][c] = '.';
        }
    }

    // Peças do jogador 1 (maiúsculas)
    tabuleiro[0][0] = 'T'; // Torre
    tabuleiro[0][2] = 'B'; // Bispo
    tabuleiro[0][4] = 'R'; // Rainha
    tabuleiro[0][6] = 'C'; // Cavalo

    // Peças do jogador 2 (minúsculas)
    tabuleiro[7][0] = 't';
    tabuleiro[7][2] = 'b';
    tabuleiro[7][4] = 'r';
    tabuleiro[7][6] = 'c';
}

void exibirTabuleiro() {
    printf("\n    ");
    for (int c = 0; c < TAM; c++) printf(" %d ", c + 1);
    printf("\n");

    for (int l = 0; l < TAM; l++) {
        printf(" %d |", l + 1);
        for (int c = 0; c < TAM; c++) {
            printf(" %c ", tabuleiro[l][c]);
        }
        printf("|\n");
    }
    printf("\n");
}

// Verifica se a posição está dentro dos limites
int dentroDoTabuleiro(int l, int c) {
    return l >= 0 && l < TAM && c >= 0 && c < TAM;
}

// Função genérica para verificar se movimento é válido
int movimentoValido(char peca, int li, int ci, int lf, int cf) {
    int dl = lf - li;
    int dc = cf - ci;

    switch (toupper(peca)) {
        case 'T':
            return (li == lf || ci == cf); // mesma linha ou coluna
        case 'B':
            return (abs(dl) == abs(dc));   // diagonais
        case 'R':
            return (li == lf || ci == cf || abs(dl) == abs(dc)); // torre + bispo
        case 'C':
            return ((abs(dl) == 2 && abs(dc) == 1) || (abs(dl) == 1 && abs(dc) == 2));
    }
    return 0;
}

// Executa um movimento se for válido
int moverPeca(int jogador) {
    int li, ci, lf, cf;
    char peca;

    printf("Jogador %d - informe a posição da peça que deseja mover (linha coluna): ", jogador);
    scanf("%d %d", &li, &ci);
    li--; ci--;

    if (!dentroDoTabuleiro(li, ci)) {
        printf("Posição de origem inválida!\n");
        return 0;
    }

    peca = tabuleiro[li][ci];
    if ((jogador == 1 && !isupper(peca)) || (jogador == 2 && !islower(peca))) {
        printf("Essa peça não pertence ao jogador %d!\n", jogador);
        return 0;
    }

    printf("Informe a posição de destino (linha coluna): ");
    scanf("%d %d", &lf, &cf);
    lf--; cf--;

    if (!dentroDoTabuleiro(lf, cf)) {
        printf("Destino fora do tabuleiro!\n");
        return 0;
    }

    if (tabuleiro[lf][cf] != '.' &&
        ((jogador == 1 && isupper(tabuleiro[lf][cf])) ||
         (jogador == 2 && islower(tabuleiro[lf][cf])))) {
        printf("Você não pode capturar sua própria peça!\n");
        return 0;
    }

    if (!movimentoValido(peca, li, ci, lf, cf)) {
        printf("Movimento inválido para a peça %c!\n", peca);
        return 0;
    }

    // Executa movimento
    tabuleiro[lf][cf] = peca;
    tabuleiro[li][ci] = '.';
    return 1;
}

int main() {
    int turno = 1;
    inicializarTabuleiro();

    while (1) {
        exibirTabuleiro();
        printf("----- Turno do Jogador %d -----\n", turno);
        if (moverPeca(turno)) {
            turno = (turno == 1) ? 2 : 1;
        }
    }

    return 0;
}
