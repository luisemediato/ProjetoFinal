#include "../include/lig4.hpp"

std::string lig4::cor(Tabuleiro::Peca jogador){
    if (jogador == Tabuleiro::Peca::JOGADOR1){
        return "\033[31m"; // Vermelho
    } else if (jogador == Tabuleiro::Peca::JOGADOR2){
        return "\033[34m"; // Azul
    }
}

void lig4::fraseInicial() {
    std::cout << "Iniciando partida de Lig4 entre " 
              << cor(Tabuleiro::Peca::JOGADOR1) << apelidoJogador1 << "\033[0m" << " e " 
              << cor(Tabuleiro::Peca::JOGADOR2) << apelidoJogador2 << "\033[0m" << "..." << std::endl;
}

void lig4::exibirTabuleiro() const{
    for(const auto& linha : tabuleiro->getTabuleiro()){
        for(const auto& celula : linha){
            exibirPeca(celula);
            std::cout << " | ";
        }
        std::cout << "\n";
    }
    std::cout << std::string(29, '-') << "\n"; // separador visual
    for(int i = 0; i < 7; ++i){
        std::cout << "  " << i + 1 << "  ";
    }
    std::cout << "\n";
}

void lig4::exibirPeca(Tabuleiro::Peca peca) const{
    switch(peca) {
        case Tabuleiro::Peca::VAZIO:
        std::cout << "   ";
        break;
        case Tabuleiro::Peca::JOGADOR1:
        std::cout << "\033[31m O \033[0m"; // O em vermelho
        break;
        case Tabuleiro::Peca::JOGADOR2:
        std::cout << "\033[34m O \033[0m"; // O em azul
        break;
    }
}

void lig4::lerJogada() {
    bool entradaValida = false;

    while (!entradaValida) {
        if (jogadorAtual == Tabuleiro::Peca::JOGADOR1) {
            std::cout << "Turno de " << cor(Tabuleiro::Peca::JOGADOR1) 
                      << apelidoJogador1 << "\033[0m" << std::endl;
        } else if (jogadorAtual == Tabuleiro::Peca::JOGADOR2) {
            std::cout << "Turno de " << cor(Tabuleiro::Peca::JOGADOR2) 
                      << apelidoJogador2 << "\033[0m" << std::endl;
        }
        std::cout << "Escolha uma coluna (1-7): ";

        std::cin >> colunaEscolhida;

        if (std::cin.fail()) {
            // Limpa o estado de erro e esvazia o buffer
            std::cin.clear();
            std::cin.ignore(10000, '\n'); // Valor grande para garantir que o buffer seja limpo
            std::cout << "Entrada invalida. Tente novamente.\n";
        } else {
            // Esvazia o buffer para descartar entradas extras
            std::cin.ignore(10000, '\n');
            entradaValida = true;
        }
    }
    --colunaEscolhida; // ajusta para indice zero
}

bool lig4::jogadaEValida() const {
    // Verifica se a coluna está dentro dos limites do tabuleiro
    if (colunaEscolhida < 0 || colunaEscolhida >= tabuleiro->getColunas()) {
        std::cout << "Jogada invalida: coluna fora dos limites.\n";
        return false;
    }

    // Verifica se a coluna tem espaço disponível
    if (tabuleiro->getPosicao(0, colunaEscolhida) != Tabuleiro::Peca::VAZIO) {
        std::cout << "Jogada invalida: coluna cheia.\n";
        return false;
    }

    return true;
}


void lig4::realizarJogada(){
    for (int i = 5; i >= 0; --i){
        if (tabuleiro->getPosicao(i, colunaEscolhida) == Tabuleiro::Peca::VAZIO){
            tabuleiro->setPosicao(i, colunaEscolhida, jogadorAtual);
            break;
        }
    }
    exibirTabuleiro();
    trocarJogador();
}

bool lig4::partidaAcabou() {
    // Verifica se algum jogador venceu
    for (int linha = 0; linha < 6; ++linha) {
        for (int coluna = 0; coluna < 7; ++coluna) {
            if (tabuleiro->getPosicao(linha, coluna) != Tabuleiro::Peca::VAZIO &&
                verificarVitoria(linha, coluna)) {
                vencedor = (tabuleiro->getPosicao(linha, coluna) == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
                return true;
            }
        }
    }

    // Verifica se o tabuleiro está completamente cheio (empate)
    for (int linha = 0; linha < 6; ++linha) {
        for (int coluna = 0; coluna < 7; ++coluna) {
            if (tabuleiro->getPosicao(linha, coluna) == Tabuleiro::Peca::VAZIO) {
                return false; // Ainda há espaço vazio, o jogo continua
            }
        }
    }

    vencedor = 0; // Empate
    return true;
}

void lig4::indicarFimDaPartida() {
    exibirTabuleiro();
    std::cout << "PARTIDA ENCERRADA!\n" << std::endl;
    if (vencedor == 0) {
        std::cout << "A partida terminou em empate!" << std::endl;
    } else {
        std::cout << "Parabens, " 
          << ((vencedor == 1) ? cor(Tabuleiro::Peca::JOGADOR1) : cor(Tabuleiro::Peca::JOGADOR2))
          << " "
          << ((vencedor == 1) ? apelidoJogador1 : apelidoJogador2)
          << "! Voce venceu!" << std::endl;
    }
}


bool lig4::verificarVitoria(int linha, int coluna) const {
    static const int direcoes[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    Tabuleiro::Peca peca = tabuleiro->getPosicao(linha, coluna);

    for (const auto& dir : direcoes) {
        int contagem = 1;

        // Verifica na direção positiva
        for (int i = 1; i < 4; ++i) {
            int novaLinha = linha + i * dir[0];
            int novaColuna = coluna + i * dir[1];
            if (dentroDosLimites(novaLinha, novaColuna) &&
                tabuleiro->getPosicao(novaLinha, novaColuna) == peca) {
                ++contagem;
            } else {
                break;
            }
        }

        // Verifica na direção negativa
        for (int i = 1; i < 4; ++i) {
            int novaLinha = linha - i * dir[0];
            int novaColuna = coluna - i * dir[1];
            if (dentroDosLimites(novaLinha, novaColuna) &&
                tabuleiro->getPosicao(novaLinha, novaColuna) == peca) {
                ++contagem;
            } else {
                break;
            }
        }

        // Se encontrou 4 ou mais peças alinhadas, há vitória
        if (contagem >= 4) {
            return true;
        }
    }

    return false;
}

bool lig4::dentroDosLimites(int linha, int coluna) const{
    return linha >= 0 && linha < 6 && coluna >= 0 && coluna < 7;
}