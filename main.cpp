#include <stdio.h>
#include <stdlib.h>

char converter(int numero) {
    char letra;
    switch(numero) {
        case 1: letra = 'O'; break;
        case 3: letra = 'X'; break;
        default: letra = ' '; break;
    }
    return letra;
}

void mostrarTabuleiro(int matriz[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (i > 0) printf("-----\n");
        printf("%c|%c|%c\n", converter(matriz[i][0]), converter(matriz[i][1]), converter(matriz[i][2]));
    }
}

void usuarioJoga(int matriz[3][3]) {
    int linha, coluna;
    do {
        printf("Escolha linha e coluna (0-2): ");
        scanf("%d %d", &linha, &coluna);
        if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
            printf("Posição inválida! Escolha uma linha e coluna entre 0 e 2.\n");
        } else if (matriz[linha][coluna] != 2) {
            printf("Posição já ocupada! Escolha outra posição.\n");
        }
    } while (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || matriz[linha][coluna] != 2);
    matriz[linha][coluna] = 1; // O jogador sempre joga com 'O'
}

int verificaSeXGanhou(int matriz[3][3]) {
    int produtos[8] = {1, 1, 1, 1, 1, 1, 1, 1}; // 3 linhas, 3 colunas, 2 diagonais
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            produtos[i] *= matriz[i][j]; // Linhas
            produtos[3 + j] *= matriz[i][j]; // Colunas
            if (i == j) produtos[6] *= matriz[i][j]; // Diagonal principal
            if (i + j == 2) produtos[7] *= matriz[i][j]; // Diagonal secundária
        }
    }
    for (int i = 0; i < 8; i++) {
        if (produtos[i] == 27) return 1; // 3 * 3 * 3 = 27, X ganhou
    }
    return 0;
}

int verificaSeOGanhou(int matriz[3][3]) {
    int produtos[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            produtos[i] *= matriz[i][j];
            produtos[3 + j] *= matriz[i][j];
            if (i == j) produtos[6] *= matriz[i][j];
            if (i + j == 2) produtos[7] *= matriz[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        if (produtos[i] == 1) return 1; // 1 * 1 * 1 = 1, O ganhou
    }
    return 0;
}
void computadorJoga(int matriz[3][3]) {
    int linha, coluna;
    // Verifica se o computador pode ganhar em alguma linha
    for (linha = 0; linha < 3; linha++) {
        int soma = 1; // Começa com 1 para multiplicação
        for (coluna = 0; coluna < 3; coluna++) {
            soma *= matriz[linha][coluna];
        }
        if (soma == 18) { // 2 * 3 * 3 = 18, a linha tem duas casas do computador e uma vazia
            for (coluna = 0; coluna < 3; coluna++) {
                if (matriz[linha][coluna] == 2) {
                    matriz[linha][coluna] = 3; // Faz a jogada para ganhar
                    return;
                }
            }
        }
    }
    // Verifica se o computador pode ganhar em alguma coluna
    for (coluna = 0; coluna < 3; coluna++) {
        int soma = 1;
        for (linha = 0; linha < 3; linha++) {
            soma *= matriz[linha][coluna];
        }
        if (soma == 18) {
            for (linha = 0; linha < 3; linha++) {
                if (matriz[linha][coluna] == 2) {
                    matriz[linha][coluna] = 3;
                    return;
                }
            }
        }
    }
    // Verifica se o computador pode ganhar na diagonal principal
    int somaDiagonalPrincipal = 1;
    for (linha = 0; linha < 3; linha++) {
        somaDiagonalPrincipal *= matriz[linha][linha];
    }
    if (somaDiagonalPrincipal == 18) {
        for (linha = 0; linha < 3; linha++) {
            if (matriz[linha][linha] == 2) {
                matriz[linha][linha] = 3;
                return;
            }
        }
    }
    // Verifica se o computador pode ganhar na diagonal secundária
    int somaDiagonalSecundaria = 1;
    for (linha = 0; linha < 3; linha++) {
        somaDiagonalSecundaria *= matriz[linha][2 - linha];
    }
    if (somaDiagonalSecundaria == 18) {
        for (linha = 0; linha < 3; linha++) {
            if (matriz[linha][2 - linha] == 2) {
                matriz[linha][2 - linha] = 3;
                return;
            }
        }
    }
    // Se não puder ganhar, verifica se pode bloquear o jogador 'O'
    // Verifica se o jogador 'O' pode ganhar em alguma linha
    for (linha = 0; linha < 3; linha++) {
        int soma = 1;
        for (coluna = 0; coluna < 3; coluna++) {
            soma *= matriz[linha][coluna];
        }
        if (soma == 2) { // 1 * 2 * 1 = 2, a linha tem duas casas do jogador 'O' e uma vazia
            for (coluna = 0; coluna < 3; coluna++) {
                if (matriz[linha][coluna] == 2) {
                    matriz[linha][coluna] = 3; // Bloqueia a jogada do jogador 'O'
                    return;
                }
            }
        }
    }
    // Verifica se o jogador 'O' pode ganhar em alguma coluna
    for (coluna = 0; coluna < 3; coluna++) {
        int soma = 1;
        for (linha = 0; linha < 3; linha++) {
            soma *= matriz[linha][coluna];
        }
        if (soma == 2) {
            for (linha = 0; linha < 3; linha++) {
                if (matriz[linha][coluna] == 2) {
                    matriz[linha][coluna] = 3;
                    return;
                }
            }
        }
    }
    // Verifica se o jogador 'O' pode ganhar na diagonal principal
    int somaDiagonalPrincipalO = 1;
    for (linha = 0; linha < 3; linha++) {
        somaDiagonalPrincipalO *= matriz[linha][linha];
    }
    if (somaDiagonalPrincipalO == 2) {
        for (linha = 0; linha < 3; linha++) {
            if (matriz[linha][linha] == 2) {
                matriz[linha][linha] = 3;
                return;
            }
        }
    }
    // Verifica se o jogador 'O' pode ganhar na diagonal secundária
    int somaDiagonalSecundariaO = 1;
    for (linha = 0; linha < 3; linha++) {
        somaDiagonalSecundariaO *= matriz[linha][2 - linha];
    }
    if (somaDiagonalSecundariaO == 2) {
        for (linha = 0; linha < 3; linha++) {
            if (matriz[linha][2 - linha] == 2) {
                matriz[linha][2 - linha] = 3;
                return;
            }
        }
    }
    // Se não puder ganhar nem bloquear, joga em uma posição aleatória
    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (matriz[linha][coluna] != 2);
    matriz[linha][coluna] = 3;
}


int verificaSeTemVitoria(int matriz[3][3]) {
    if (verificaSeXGanhou(matriz)) return 3;
    if (verificaSeOGanhou(matriz)) return 1;

    // Verifica se há posições livres no tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] == 2) {
                return 2; // Jogo continua
            }
        }
    }
    return 0; // Empate
}

int main() {
    int matriz[3][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    int resultado = 2;
    for (int jogada = 0; jogada < 9 && resultado == 2; jogada++) {
        mostrarTabuleiro(matriz);
        usuarioJoga(matriz);
        system("clear");
        resultado = verificaSeTemVitoria(matriz);
        if (resultado != 2) break;
        computadorJoga(matriz);
        mostrarTabuleiro(matriz);
        system("clear");
        resultado = verificaSeTemVitoria(matriz);
        if (resultado != 2) break;
    }
    if (resultado == 1) printf("O ganhou!\n");
    else if (resultado == 3) printf("X ganhou!\n");
    else printf("Empate!\n");
    return 0;
}
