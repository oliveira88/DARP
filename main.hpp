#pragma once
#include <string>

#define MAX 1440
#define MAX_VEICULOS 6

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
  int numAssentos = 0;
  int duracaoMaximaRota = 0;
  int tempoMaximoViagem = 0;
  int tempoMaximoEspera = 0;
  int horarioSaidaEChegadaGaragens = 0;
} Violacoes;

typedef struct Veiculo {
  int id = -1;
  int requicoesAtendidas = 0;
  int assentosUtilizados = 0;
  int duracaoRota = 0;
  int tempoViagem = 0;
  int tempoEspera = 0;
  int distanciaPercorrida = 0;
  int FO = 0;
  Violacoes violacoes;
  int rotasEmbarque[MAX];
  int rotasDesembarque[MAX];
  // TODO: sequência de locais que formam a rota do veículo.
} Veiculo;

typedef struct Solucao {
  // int idVeiculoTransportado[MAX];  // -1= nenhum, 1,2,3,4,5,6
  // int pessoasTransportadas[MAX];
  // int tempoTotalMovimento[MAX];
  int requisicaoAtendidaPor[MAX];
  Veiculo veiculos[MAX_VEICULOS] = {0};
  int FO;
  int veiculosUtilizados = 0;
} Solucao;

int PESO1 = 10, PESO2 = 1, PESO3 = 0, PESO4 = 0, PESO5 = 0;

int reqVeiculo[MAX];

void lerArquivo(std::string nome);
void escreverDados(std::string nome);
void HCAleatoria(Solucao &s);
void HCGulosa(Solucao &s);
void HCAleatoriaGulosa(Solucao &s);
void calcularFO(Solucao &s);
void clonarSolucao(Solucao &original, Solucao &copia);
void escreverSolucao(Solucao &s, const bool flag);
void verificaViolacoes(Solucao &s);
void breakLine(FILE *f, const int num);
void lerSolucaoQualquer(std::string nome);