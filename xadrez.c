#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define TAM 8

char tabuleiro[TAM][TAM];

void inicializarTabuleiro() {
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
    for (int c = 0; c < TAM; c++) {
        printf(" %d ", c + 1);
    }
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

int dentroDoTabuleiro(int l, int c) {
    return l >= 0 && l < TAM && c >= 0 && c < TAM;
}

int caminhoLivre(int li, int ci, int lf, int cf) {
    int dl = (lf > li) ? 1 : (lf < li) ? -1 : 0;
    int dc = (cf > ci) ? 1 : (cf < ci) ? -1 : 0;

    li += dl;
    ci += dc;

    while (li != lf || ci != cf) {
        if (tabuleiro[li][ci] != '.') {
            return 0; // Caminho bloqueado
        }
        li += dl;
        ci += dc;
    }

    return 1;
}

int movimentoValido(char peca, int li, int ci, int lf, int cf) {
    int dl = lf - li;
    int dc = cf - ci;

    switch (toupper(peca)) {
        case 'T': // Torre
            if ((li == lf || ci == cf) && caminhoLivre(li, ci, lf, cf)) return 1;
            break;
        case 'B': // Bispo
            if (abs(dl) == abs(dc) && caminhoLivre(li, ci, lf, cf)) return 1;
            break;
        case 'R': // Rainha
            if (((li == lf || ci == cf) || abs(dl) == abs(dc)) && caminhoLivre(li, ci, lf, cf)) return 1;
            break;
        case 'C': // Cavalo
            if ((abs(dl) == 2 && abs(dc) == 1) || (abs(dl) == 1 && abs(dc) == 2)) return 1;
            break;
    }

    return 0;
}

int moverPeca(int jogador) {
    int li, ci, lf, cf;
    char peca;

    printf("Jogador %d - Informe a posição da peça que deseja mover (linha coluna): ", jogador);
    if (scanf("%d %d", &li, &ci) != 2) {
        printf("Entrada inválida!\n");
        while (getchar() != '\n'); // Limpa buffer
        return 0;
    }
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
    if (scanf("%d %d", &lf, &cf) != 2) {
        printf("Entrada inválida!\n");
        while (getchar() != '\n'); // Limpa buffer
        return 0;
    }
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

    // Realiza movimento
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
