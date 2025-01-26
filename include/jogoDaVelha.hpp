#ifndef JOGODAVELHA_H
#define JOGODAVELHA_H

#include "./jogos.hpp"
#include <iostream>

class JogoDaVelha : public Jogos {
private:
    int jogadaLinha;  // Armazena a linha da jogada atual
    int jogadaColuna; // Armazena a coluna da jogada atual
    int vencedor;     // 0 para empate, 1 para Jogador 1, 2 para Jogador 2

public:
    JogoDaVelha() : Jogos(3, 3), jogadaLinha(-1), jogadaColuna(-1), vencedor(0) {
        std::cout << "Iniciando o Jogo da Velha..." << std::endl;
    }
    ~JogoDaVelha() {};

    // Método para imprimir o tabuleiro
    virtual void exibirPeca(Tabuleiro::Peca peca) const override; 
    
    // Métodos responsáveis pelas jogadas em cada rodada
    virtual void lerJogada() override; 
	virtual bool jogadaEValida() const override; 
	virtual void realizarJogada() override; 

    // Métodos que gerenciam o andamento da partida
	virtual bool partidaAcabou() override; 
	virtual void indicarFimDaPartida() const override;

};

#endif