#include <stdio.h>
#include <stdlib.h>  // Para abs()

#define TAB_SIZE 10
#define SHIP_SIZE 3
#define HABILIDADE 5
#define AREA_SIZE 5  // 5x5 para áreas de efeito

// Inicializa tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++)
        for (int j = 0; j < TAB_SIZE; j++)
            tab[i][j] = 0;
}

// Imprime tabuleiro com legendas claras e índices de linha e coluna
void imprimirTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro (0=Agua, 3=Navio, 5=Area de Habilidade):\n\n");
    
    printf("   ");
    for (int col = 0; col < TAB_SIZE; col++) 
        printf("%d ", col);
    printf("\n");

    for (int i = 0; i < TAB_SIZE; i++) {
        printf("%2d ", i);  // Índice da linha
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se pode posicionar navio no tabuleiro, mesma lógica sua
int podePosicionar(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    if (linha < 0 || linha >= TAB_SIZE || coluna < 0 || coluna >= TAB_SIZE)
        return 0;

    if (orientacao == 'H' || orientacao == 'h') {
        if (coluna + tamanho > TAB_SIZE) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha][coluna + i] == 3) return 0;
    } else if (orientacao == 'V' || orientacao == 'v') {
        if (linha + tamanho > TAB_SIZE) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna] == 3) return 0;
    } else if (orientacao == 'D' || orientacao == 'd') {
        if (linha + tamanho > TAB_SIZE || coluna + tamanho > TAB_SIZE) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna + i] == 3) return 0;
    } else if (orientacao == 'A' || orientacao == 'a') {
        if (linha + tamanho > TAB_SIZE || coluna - tamanho + 1 < 0) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna - i] == 3) return 0;
    } else {
        return 0; // Orientação inválida
    }
    return 1;
}

// Posiciona navio no tabuleiro conforme orientação, igual ao seu código
void posicionarNavio(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H' || orientacao == 'h') {
        for (int i = 0; i < tamanho; i++)
            tab[linha][coluna + i] = 3;
    } else if (orientacao == 'V' || orientacao == 'v') {
        for (int i = 0; i < tamanho; i++)
            tab[linha + i][coluna] = 3;
    } else if (orientacao == 'D' || orientacao == 'd') {
        for (int i = 0; i < tamanho; i++)
            tab[linha + i][coluna + i] = 3;
    } else if (orientacao == 'A' || orientacao == 'a') {
        for (int i = 0; i < tamanho; i++)
            tab[linha + i][coluna - i] = 3;
    }
}

// Função para ler uma posição do usuário com validação simples
void lerPosicao(int *linha, int *coluna) {
    printf("Informe linha (0-%d): ", TAB_SIZE - 1);
    scanf("%d", linha);
    printf("Informe coluna (0-%d): ", TAB_SIZE - 1);
    scanf("%d", coluna);
}

// Função para ler orientação do usuário
char lerOrientacao() {
    char ori;
    printf("Informe orientação do navio (H=Horizontal, V=Vertical, D=Diagonal principal, A=Diagonal anti): ");
    scanf(" %c", &ori);
    return ori;
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    inicializarTabuleiro(tabuleiro);

    int naviosQtd = 4;

    printf("Jogo Batalha Naval - Posicione seus %d navios de tamanho %d\n\n", naviosQtd, SHIP_SIZE);
    imprimirTabuleiro(tabuleiro);

    for (int i = 0; i < naviosQtd; i++) {
        int linha, coluna;
        char orientacao;
        int valido = 0;

        printf("Posicionando navio %d:\n", i + 1);

        do {
            lerPosicao(&linha, &coluna);
            orientacao = lerOrientacao();

            if (podePosicionar(tabuleiro, linha, coluna, SHIP_SIZE, orientacao)) {
                posicionarNavio(tabuleiro, linha, coluna, SHIP_SIZE, orientacao);
                valido = 1;
                imprimirTabuleiro(tabuleiro);
            } else {
                printf("Posição ou orientação inválida para o navio. Tente novamente.\n");
            }
        } while (!valido);
    }

    // Aqui você pode continuar com o resto do jogo, aplicar áreas, etc.
    printf("Todos os navios posicionados com sucesso!\n");

    return 0;
}
