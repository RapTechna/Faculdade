#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
    tabuleiro[0][0] = 'T';
    tabuleiro[0][2] = 'B';
    tabuleiro[0][4] = 'R';
    tabuleiro[0][6] = 'C';

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

int dentroDoTabuleiro(int l, int c) {
    return l >= 0 && l < TAM && c >= 0 && c < TAM;
}

// Verifica se o caminho está livre (para Torre, Bispo e Rainha)
int caminhoLivre(int li, int ci, int lf, int cf) {
    int dl = (lf - li) == 0 ? 0 : (lf - li) / abs(lf - li);
    int dc = (cf - ci) == 0 ? 0 : (cf - ci) / abs(cf - ci);

    int l = li + dl;
    int c = ci + dc;

    while (l != lf || c != cf) {
        if (tabuleiro[l][c] != '.') return 0;
        l += dl;
        c += dc;
    }

    return 1;
}

int movimentoValido(char peca, int li, int ci, int lf, int cf) {
    int dl = lf - li;
    int dc = cf - ci;

    switch (toupper(peca)) {
        case 'T':
            if (li == lf || ci == cf)
                return caminhoLivre(li, ci, lf, cf);
            break;
        case 'B':
            if (abs(dl) == abs(dc))
                return caminhoLivre(li, ci, lf, cf);
            break;
        case 'R':
            if ((li == lf || ci == cf || abs(dl) == abs(dc)))
                return caminhoLivre(li, ci, lf, cf);
            break;
        case 'C':
            return (abs(dl) == 2 && abs(dc) == 1) || (abs(dl) == 1 && abs(dc) == 2);
    }
    return 0;
}

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
