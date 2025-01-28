#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "jogos.hpp"
#include "tabuleiro.hpp"
#include <iostream>
#include <utility>

class Reversi : public Jogos {
public:
    Reversi();

    void exibirTabuleiro() const override;
    void fraseInicial() override;
    void exibirPeca(Tabuleiro::Peca peca) const override;
    void lerJogada() override;
    bool jogadaEValida() const override;
    void realizarJogada() override;
    bool partidaAcabou() override;
    int indicarFimDaPartida() override;
    void indicarPossiveisJogadas();

private:
    int jogadaLinha;
    int jogadaColuna;

    std::pair<int, int> contarPecas() const; // Adicione a declaração da função aqui
    bool dentroDosLimites(int linha, int coluna) const;
    bool direcaoValida(int linha, int coluna, int deltaLinha, int deltaColuna, Tabuleiro::Peca peca) const;
    bool capturarPecas(int linha, int coluna, Tabuleiro::Peca peca);
    bool haJogadasPossiveis();
    std::string cor (int jogador);
};

#endif

