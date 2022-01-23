#pragma once
#include <string>

#define MAX 1440

// Dados de entrada
typedef struct Entrada {
  int veiculos, requisicoes, duracaoRotaMax;
  int tempoViagemMax, tempoEsperaMax;
} Entrada;

typedef struct Solucao {
  int idVeiculoTransportado[MAX];  // 0= nenhum,1,2,3,4,5,6
  int pessoasTransportadas[MAX];
  int tempoTotalMovimento[MAX];
  int FO;
  Entrada entrada;
} Solucao;

// int veiculos, requisicoes, duracaoRotaMax, tempoViagemMax, tempoEsperaMax;

int capVeiculos[MAX],
    numAssentos[MAX],
    tempoServico[MAX],
    inicioJanelaTempo[MAX],
    fimJanelaTempo[MAX],
    matriz[MAX][MAX];
int PESO1 = 10, PESO2 = 1;

void lerArquivo(std::string nome, Solucao &s);
void escreverDados(std::string nome, Solucao &s);
void HCAleatoria(Solucao &s);
void HCGulosa(Solucao &s);
void HCAleatoriaGulosa(Solucao &s);
void calcularFO(Solucao &s);
void clonarSolucao(Solucao &original, Solucao &copia);

void simulatedAnnealing();
void breakLine(FILE *f, const int num);