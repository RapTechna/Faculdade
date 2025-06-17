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

// Imprime tabuleiro com legendas claras
void imprimirTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro (0=Agua, 3=Navio, 5=Area de Habilidade):\n\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se pode posicionar navio de tamanho 'tamanho' na posição (linha, coluna) com orientação 'orientacao'
// Orientações: H (horizontal), V (vertical), D (diagonal principal), A (diagonal anti)
int podePosicionar(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        if (coluna + tamanho > TAB_SIZE) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha][coluna + i] == 3) return 0;
    } else if (orientacao == 'V') {
        if (linha + tamanho > TAB_SIZE) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna] == 3) return 0;
    } else if (orientacao == 'D') {
        if (linha + tamanho > TAB_SIZE || coluna + tamanho > TAB_SIZE) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna + i] == 3) return 0;
    } else if (orientacao == 'A') {
        if (linha + tamanho > TAB_SIZE || coluna - tamanho + 1 < 0) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna - i] == 3) return 0;
    } else {
        return 0; // Orientação inválida
    }
    return 1;
}

// Posiciona navio no tabuleiro conforme orientação
void posicionarNavio(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++)
            tab[linha][coluna + i] = 3;
    } else if (orientacao == 'V') {
        for (int i = 0; i < tamanho; i++)
            tab[linha + i][coluna] = 3;
    } else if (orientacao == 'D') {
        for (int i = 0; i < tamanho; i++)
            tab[linha + i][coluna + i] = 3;
    } else if (orientacao == 'A') {
        for (int i = 0; i < tamanho; i++)
            tab[linha + i][coluna - i] = 3;
    }
}

// Cria matriz de área de efeito CONE (triângulo com ponta para baixo)
void criarAreaCone(int area[AREA_SIZE][AREA_SIZE]) {
    int meio = AREA_SIZE / 2;
    for (int i = 0; i < AREA_SIZE; i++)
        for (int j = 0; j < AREA_SIZE; j++)
            area[i][j] = 0;

    for (int i = 0; i < AREA_SIZE; i++) {
        for (int j = meio - i; j <= meio + i; j++) {
            if (j >= 0 && j < AREA_SIZE) area[i][j] = 1;
        }
    }
}

// Cria matriz de área de efeito CRUZ
void criarAreaCruz(int area[AREA_SIZE][AREA_SIZE]) {
    int meio = AREA_SIZE / 2;
    for (int i = 0; i < AREA_SIZE; i++)
        for (int j = 0; j < AREA_SIZE; j++)
            area[i][j] = 0;

    for (int i = 0; i < AREA_SIZE; i++) {
        area[meio][i] = 1;  // linha central
        area[i][meio] = 1;  // coluna central
    }
}

// Cria matriz de área de efeito OCTAEDRO (losango)
void criarAreaOctaedro(int area[AREA_SIZE][AREA_SIZE]) {
    int meio = AREA_SIZE / 2;
    for (int i = 0; i < AREA_SIZE; i++)
        for (int j = 0; j < AREA_SIZE; j++)
            area[i][j] = 0;

    for (int i = 0; i < AREA_SIZE; i++)
        for (int j = 0; j < AREA_SIZE; j++)
            if (abs(i - meio) + abs(j - meio) <= meio)
                area[i][j] = 1;
}

// Aplica a área de efeito no tabuleiro centralizando em (linhaOrigem, colOrigem)
// Marca células livres com HABILIDADE (5), sem sobrescrever navios (3)
void aplicarAreaEfeito(int tab[TAB_SIZE][TAB_SIZE], int area[AREA_SIZE][AREA_SIZE], int linhaOrigem, int colOrigem) {
    int meio = AREA_SIZE / 2;
    for (int i = 0; i < AREA_SIZE; i++) {
        for (int j = 0; j < AREA_SIZE; j++) {
            if (area[i][j] == 1) {
                int linhaTab = linhaOrigem - meio + i;
                int colTab = colOrigem - meio + j;

                if (linhaTab >= 0 && linhaTab < TAB_SIZE && colTab >= 0 && colTab < TAB_SIZE) {
                    if (tab[linhaTab][colTab] == 0)
                        tab[linhaTab][colTab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas e orientações dos navios
    struct {
        int linha, coluna;
        char orientacao;
    } navios[] = {
        {1, 1, 'H'},
        {4, 7, 'V'},
        {6, 2, 'D'},
        {0, 9, 'A'}
    };

    // Posiciona navios
    for (int i = 0; i < 4; i++) {
        if (podePosicionar(tabuleiro, navios[i].linha, navios[i].coluna, SHIP_SIZE, navios[i].orientacao)) {
            posicionarNavio(tabuleiro, navios[i].linha, navios[i].coluna, SHIP_SIZE, navios[i].orientacao);
        } else {
            printf("Erro: Navio %d nao pode ser posicionado.\n", i+1);
            return 1;
        }
    }

    // Cria as matrizes das áreas de efeito
    int cone[AREA_SIZE][AREA_SIZE], cruz[AREA_SIZE][AREA_SIZE], octaedro[AREA_SIZE][AREA_SIZE];
    criarAreaCone(cone);
    criarAreaCruz(cruz);
    criarAreaOctaedro(octaedro);

    // Posições de origem das habilidades
    int origemConeLinha = 2, origemConeCol = 2;
    int origemCruzLinha = 6, origemCruzCol = 7;
    int origemOctaedroLinha = 8, origemOctaedroCol = 4;

    // Aplica áreas de efeito
    aplicarAreaEfeito(tabuleiro, cone, origemConeLinha, origemConeCol);
    aplicarAreaEfeito(tabuleiro, cruz, origemCruzLinha, origemCruzCol);
    aplicarAreaEfeito(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroCol);

    // Imprime o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
