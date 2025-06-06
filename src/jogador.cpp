#include "../include/jogador.hpp"

Jogador::Jogador(const std::string &apelido, const std::string &nome)
    :apelido(apelido), nome(nome){
    //Inicializa o mapa de estatisticas com 0 vitórias e 0 derrotas para todos os jogos
    for (int i=REVERSI; i<TOTAL_DE_JOGOS; i++){
        estatisticas_map[static_cast<TipoDeJogo>(i)] = {0, 0}; 
    }
}
Jogador::~Jogador(){};
//Métodos de acesso
std::string Jogador::getApelido() const{
    return this->apelido;
}
std::string Jogador::getNome() const{
    return this->nome;
}

//É importante sempre passar o número do jogo (TipoDeJogo) e a quantidade de vitórias ou derrotas. 
//Este método foi projetado para ser utilizado tanto durante os jogos quanto ao processar dados carregados do arquivo.
void Jogador::adicionarVitoria(TipoDeJogo jogo_enum, int quantidade){
    if(jogo_enum >= REVERSI && jogo_enum < TOTAL_DE_JOGOS){
        estatisticas_map[jogo_enum].first += quantidade;
    }else{
        throw std::out_of_range("TipoDeJogo esta fora do intervalo valido para adicionar vitoria");
    }
}
//É importante sempre passar o número do jogo (TipoDeJogo) e a quantidade de vitórias ou derrotas. 
//Este método foi projetado para ser utilizado tanto durante os jogos quanto ao processar dados carregados do arquivo.
void Jogador::adicionarDerrota(TipoDeJogo jogo_enum, int quantidade){
    if(jogo_enum >= REVERSI && jogo_enum < TOTAL_DE_JOGOS){
        estatisticas_map[jogo_enum].second += quantidade;
    }else{
        throw std::out_of_range("TipoDeJogo esta fora do intervalo valido para adicionar derrota.");
    }
}

//É importante sempre passar o número do jogo (TipoDeJogo).
//Este método foi projetado para obter as estatísticas (vitórias e derrotas) de um jogador em um jogo específico.
std::pair<int, int>Jogador::getEstatisticasDoJogo(TipoDeJogo jogo_enum)const{
    if(jogo_enum >= REVERSI && jogo_enum < TOTAL_DE_JOGOS){
        return estatisticas_map.at(jogo_enum); //retorna as estatisticas que estão em tal jogo
    }else{
        throw std::out_of_range("TipoDeJogo esta fora do intervalo valido para pegar estatisticas do jogo.");
    }
}
//Este método converte as informações do objeto Jogador em uma string formatada no estilo CSV.
//A string resultante contém o apelido, nome e as estatísticas de cada jogo (vitorias e derrotas), separados por vírgulas.
std::string Jogador::formatarJogadorComoCSV()const{
    std::ostringstream buffer;
    buffer << this->apelido << "," << this->nome;
    for(int i=REVERSI;i<TOTAL_DE_JOGOS;i++){
        auto estatisticas = getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
        buffer << "," << estatisticas.first << "," << estatisticas.second;
    }
    buffer << "\n";
    return buffer.str();
}