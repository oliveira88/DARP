#pragma once
#include <string>

#define MAX 1440
#define VEICULOS 6

// Dados de entrada
int veiculos, requisicoes, duracaoRotaMax, tempoViagemMax, tempoEsperaMax,
    capVeiculos[MAX],
    numAssentos[MAX],
    tempoServico[MAX],
    inicioJanelaTempo[MAX],
    fimJanelaTempo[MAX],
    janelaTempoTotal[MAX],
    matrizTempoDeslocamento[MAX][MAX];

// Estruturas de dados
typedef struct Violacoes {
  int numAssentos;
  int duracaoMaximaRota;
  int tempoMaximoViagem;
  int tempoMaximoEspera;
  int horarioSaidaEChegadaGaragens;
} Violacoes;

typedef struct Veiculo {
  int id;
  int requicoesAtendidas;
  int assentosUtilizados;
  int duracaoRota;
  int tempoViagem;
  int tempoEspera;
  int distanciaPercorrida;
  int FO;
  Violacoes violacoes;
  // TODO: sequência de locais que formam a rota do veículo.
} Veiculo;

typedef struct Solucao {
  // int idVeiculoTransportado[MAX];  // -1= nenhum, 1,2,3,4,5,6
  // int pessoasTransportadas[MAX];
  // int tempoTotalMovimento[MAX];
  // int requisicaoAtendidaPor[MAX];
  Veiculo veiculos[VEICULOS];
  int FO;
} Solucao;

int PESO1 = 10, PESO2 = 1;

void lerArquivo(std::string nome);
void escreverDados(std::string nome);
void HCAleatoria(Solucao &s);
void HCGulosa(Solucao &s);
void HCAleatoriaGulosa(Solucao &s);
void calcularFO(Solucao &s);
void clonarSolucao(Solucao &original, Solucao &copia);
void escreverSolucao(Solucao &s);

void breakLine(FILE *f, const int num);