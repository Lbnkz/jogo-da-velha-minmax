#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Função para converter o número em caractere para exibir no tabuleiro
char converter(int numero) {
    char letra;
    switch(numero) {
        case 1: letra = 'O';
                break;
        case 3: letra = 'X';
                break;
        default: letra = ' ';
    }
    return letra;
}

// Função para mostrar o tabuleiro
void mostrarTabuleiro(int matriz[3][3]) {
    printf("%c|%c|%c\n", converter(matriz[0][0]), converter(matriz[0][1]), converter(matriz[0][2]));
    printf("-----\n");
    printf("%c|%c|%c\n", converter(matriz[1][0]), converter(matriz[1][1]), converter(matriz[1][2]));
    printf("-----\n");
    printf("%c|%c|%c\n", converter(matriz[2][0]), converter(matriz[2][1]), converter(matriz[2][2]));
}


// Função para verificar se houve vitória para X ou O
int verificaSeGanhou(int matriz[3][3], int jogador) {
    // Verifica linhas
    for(int i = 0; i < 3; i++) {
        if(matriz[i][0] * matriz[i][1] * matriz[i][2] == jogador*jogador*jogador)
            return 1; // Jogador ganhou
    }
    // Verifica colunas
    for(int i = 0; i < 3; i++) {
        if(matriz[0][i] * matriz[1][i] * matriz[2][i] == jogador*jogador*jogador)
            return 1; // Jogador ganhou
    }
    // Verifica diagonais
    if((matriz[0][0] * matriz[1][1] * matriz[2][2] == jogador*jogador*jogador) || (matriz[0][2] * matriz[1][1] * matriz[2][0] == jogador*jogador*jogador))
        return 1; // Jogador ganhou

    return 0; // Ninguém ganhou
}

// Função para verificar se uma posição está livre
int verificaSeAPosicaoEstaLivre(int matriz[3][3], int linha, int coluna) {
    return (matriz[linha][coluna] == 2); // Retorna 1 se a posição está livre, senão retorna 0
}

// Função para permitir que o usuário jogue
void usuarioJoga(int matriz[3][3]) {
    int linha, coluna;
    do {
        printf("Escolha a linha (1-3) e coluna (1-3) para jogar: ");
        scanf("%d %d", &linha, &coluna);
        linha--; // Ajuste para índice 0-based
        coluna--; // Ajuste para índice 0-based

        if (!verificaSeAPosicaoEstaLivre(matriz, linha, coluna)) {
            printf("A posição escolhida já está ocupada. Escolha uma posição válida.\n");
        }
    } while (!verificaSeAPosicaoEstaLivre(matriz, linha, coluna));
    matriz[linha][coluna] = 1; // Coloca um 'O' na posição escolhida
}

// Função que avalia a pontuação de um determinado estado do tabuleiro
int avaliar(int matriz[3][3]) {
    if (verificaSeGanhou(matriz, 3)) // X ganhou
        return 10;
    else if (verificaSeGanhou(matriz, 1)) // O ganhou
        return -10;
    return 0; // Empate
}

// Função que implementa o algoritmo Minimax
int minimax(int matriz[3][3], int profundidade, int jogador) {
    int pontuacao = avaliar(matriz);

    // Se o jogo já acabou ou atingiu o limite de profundidade, retorna a pontuação
    if (pontuacao == 10 || pontuacao == -10 || profundidade == 0) {
        return pontuacao;
    }

    int melhorPontuacao = jogador == 3 ? INT_MIN : INT_MAX;

    // Percorre todas as células do tabuleiro
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (matriz[linha][coluna] == 2) { // Se a célula estiver vazia
                // Faz uma jogada
                matriz[linha][coluna] = jogador;

                // Recursivamente chama o minimax para avaliar a pontuação desta jogada
                int pontuacaoAtual = minimax(matriz, profundidade - 1, jogador == 3 ? 1 : 3);

                // Desfaz a jogada
                matriz[linha][coluna] = 2;

                // Atualiza a melhor pontuação de acordo com o jogador atual
                if (jogador == 3) { // Maximiza para X
                    melhorPontuacao = melhorPontuacao > pontuacaoAtual ? melhorPontuacao : pontuacaoAtual;
                } else { // Minimiza para O
                    melhorPontuacao = melhorPontuacao < pontuacaoAtual ? melhorPontuacao : pontuacaoAtual;
                }
            }
        }
    }

    return melhorPontuacao;
}

// Função para permitir que o computador jogue usando o algoritmo Minimax
void computadorJoga(int matriz[3][3]) {
    int melhorMovimento = INT_MIN;
    int linhaEscolhida = -1;
    int colunaEscolhida = -1;

    // Percorre todas as células do tabuleiro
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (matriz[linha][coluna] == 2) { // Se a célula estiver vazia
                // Faz uma jogada
                matriz[linha][coluna] = 3;

                // Chama o algoritmo Minimax para avaliar a pontuação desta jogada
                int pontuacao = minimax(matriz, 10, 1);

                // Desfaz a jogada
                matriz[linha][coluna] = 2;

                // Verifica se a pontuação desta jogada é melhor que a atual
                if (pontuacao > melhorMovimento) {
                    melhorMovimento = pontuacao;
                    linhaEscolhida = linha;
                    colunaEscolhida = coluna;
                }
            }
        }
    }

    // Realiza a melhor jogada encontrada pelo algoritmo Minimax
    matriz[linhaEscolhida][colunaEscolhida] = 3;
}

// Função principal
int main() {
    int matriz[3][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}; // Matriz inicial com todas as posições livres
    int jogadas = 0;

    printf("Bem-vindo ao jogo da velha!\n");
    mostrarTabuleiro(matriz);

    while (jogadas < 9) { // Loop para repetir as jogadas até que não haja mais posições livres
        usuarioJoga(matriz);
        jogadas++;
        mostrarTabuleiro(matriz);
        if (verificaSeGanhou(matriz, 1)) {
            printf("O jogador O ganhou!\n");
            return 0;
        }
        if (jogadas == 9) {
            printf("O jogo empatou!\n");
            return 0;
        }

        computadorJoga(matriz);
        jogadas++;
        system("cls");
        mostrarTabuleiro(matriz);
        if (verificaSeGanhou(matriz, 3)) {
            printf("O jogador X ganhou!\n");
            return 0;
        }
    }

    return 0;
}
