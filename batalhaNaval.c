#include <stdio.h>
#include <stdbool.h>

#define TAM 10
#define NAVIO_TAM 3
#define HAB_TAM 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = AGUA;
        }
    }
}

bool validarPosicionamentoReto(int tab[TAM][TAM], int x, int y, bool horizontal) {
    if (x < 0 || x >= TAM || y < 0 || y >= TAM) return false;
    
    if (horizontal) {
        if (y + NAVIO_TAM > TAM) return false;
        for (int j = y; j < y + NAVIO_TAM; j++) {
            if (tab[x][j] == NAVIO) return false;
        }
    } else {
        if (x + NAVIO_TAM > TAM) return false;
        for (int i = x; i < x + NAVIO_TAM; i++) {
            if (tab[i][y] == NAVIO) return false;
        }
    }
    return true;
}

bool validarPosicionamentoDiagonal(int tab[TAM][TAM], int x, int y, bool crescente) {
    if (x < 0 || x >= TAM || y < 0 || y >= TAM) return false;
    
    if (crescente) {
        if (x + NAVIO_TAM > TAM || y + NAVIO_TAM > TAM) return false;
        for (int k = 0; k < NAVIO_TAM; k++) {
            if (tab[x + k][y + k] == NAVIO) return false;
        }
    } else {
        if (x + NAVIO_TAM > TAM || y - NAVIO_TAM + 1 < 0) return false;
        for (int k = 0; k < NAVIO_TAM; k++) {
            if (tab[x + k][y - k] == NAVIO) return false;
        }
    }
    return true;
}

bool posicionarNavioReto(int tab[TAM][TAM], int x, int y, bool horizontal) {
    if (!validarPosicionamentoReto(tab, x, y, horizontal)) return false;
    
    if (horizontal) {
        for (int j = y; j < y + NAVIO_TAM; j++) tab[x][j] = NAVIO;
    } else {
        for (int i = x; i < x + NAVIO_TAM; i++) tab[i][y] = NAVIO;
    }
    return true;
}

bool posicionarNavioDiagonal(int tab[TAM][TAM], int x, int y, bool crescente) {
    if (!validarPosicionamentoDiagonal(tab, x, y, crescente)) return false;
    
    if (crescente) {
        for (int k = 0; k < NAVIO_TAM; k++) tab[x + k][y + k] = NAVIO;
    } else {
        for (int k = 0; k < NAVIO_TAM; k++) tab[x + k][y - k] = NAVIO;
    }
    return true;
}


 //Cria matriz de habilidade em forma de cone (triângulo)
 // O cone se expande para baixo a partir do ponto central superior
 
void criarMatrizCone(int mat[HAB_TAM][HAB_TAM]) {
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            mat[i][j] = 0;
        }
    }
    
    int centro = HAB_TAM / 2;
    for (int i = 0; i < HAB_TAM; i++) {
        int largura = i;
        for (int j = centro - largura; j <= centro + largura; j++) {
            if (j >= 0 && j < HAB_TAM) mat[i][j] = 1;
        }
    }
}


//Cria matriz de habilidade em forma de cruz
//A cruz possui uma linha vertical e horizontal central

void criarMatrizCruz(int mat[HAB_TAM][HAB_TAM]) {
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            mat[i][j] = 0;
        }
    }
    
    int centro = HAB_TAM / 2;
    for (int j = 0; j < HAB_TAM; j++) mat[centro][j] = 1;
    for (int i = 0; i < HAB_TAM; i++) mat[i][centro] = 1;
}


 //Cria matriz de habilidade em forma de losango
//O losango se expande do centro para as bordas e depois contrai

void criarMatrizLosango(int mat[HAB_TAM][HAB_TAM]) {
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            mat[i][j] = 0;
        }
    }
    
    int centro = HAB_TAM / 2;
    int raio = HAB_TAM / 2;
    
    for (int i = 0; i < HAB_TAM; i++) {
        int dist = (i > centro) ? (i - centro) : (centro - i);
        int largura = raio - dist;
        for (int j = centro - largura; j <= centro + largura; j++) {
            if (j >= 0 && j < HAB_TAM) mat[i][j] = 1;
        }
    }
}

void aplicarHabilidade(int tab[TAM][TAM], int mat[HAB_TAM][HAB_TAM], int x, int y) {
    int offset_x = x - (HAB_TAM / 2);
    int offset_y = y - (HAB_TAM / 2);
    
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            int tab_x = offset_x + i;
            int tab_y = offset_y + j;
            
            if (tab_x >= 0 && tab_x < TAM && tab_y >= 0 && tab_y < TAM) {
                if (mat[i][j] == 1 && tab[tab_x][tab_y] != NAVIO) {
                    tab[tab_x][tab_y] = HABILIDADE;
                }
            }
        }
    }
}

void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("\n  ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");
    
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void copiarTabuleiro(int src[TAM][TAM], int dst[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

int main() {
    int tab[TAM][TAM], tab_orig[TAM][TAM];
    inicializarTabuleiro(tab);
    
    // Posicionar navios
    if (!posicionarNavioReto(tab, 2, 3, true)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }
    
    if (!posicionarNavioReto(tab, 5, 7, false)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }
    
    if (!posicionarNavioDiagonal(tab, 1, 1, true)) {
        printf("Erro ao posicionar navio diagonal crescente!\n");
        return 1;
    }
    
    if (!posicionarNavioDiagonal(tab, 6, 4, false)) {
        printf("Erro ao posicionar navio diagonal decrescente!\n");
        return 1;
    }
    
    printf("Tabuleiro com navios (0=água, 3=navio):");
    exibirTabuleiro(tab);
    copiarTabuleiro(tab, tab_orig);
    
    // Criar e aplicar habilidades
    int cone[HAB_TAM][HAB_TAM], cruz[HAB_TAM][HAB_TAM], losango[HAB_TAM][HAB_TAM];
    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizLosango(losango);
    
    // Aplicar cone
    copiarTabuleiro(tab_orig, tab);
    aplicarHabilidade(tab, cone, 3, 3);
    printf("\nTabuleiro com Habilidade Cone (0=água, 3=navio, 5=área de efeito):");
    printf("\nPonto de origem: (3, 3)\n");
    exibirTabuleiro(tab);
    
    // Aplicar cruz
    copiarTabuleiro(tab_orig, tab);
    aplicarHabilidade(tab, cruz, 5, 5);
    printf("\nTabuleiro com Habilidade Cruz (0=água, 3=navio, 5=área de efeito):");
    printf("\nPonto de origem: (5, 5)\n");
    exibirTabuleiro(tab);
    
    // Aplicar losango
    copiarTabuleiro(tab_orig, tab);
    aplicarHabilidade(tab, losango, 7, 7);
    printf("\nTabuleiro com Habilidade Losango (0=água, 3=navio, 5=área de efeito):");
    printf("\nPonto de origem: (7, 7)\n");
    exibirTabuleiro(tab);
    
    return 0;
}