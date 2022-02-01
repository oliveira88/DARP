#include "main.hpp"

#include <math.h>
#include <memory.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#define LENGTH(x) (sizeof(x) / sizeof(x)[0])
//#define DEBUG
using namespace std;
int main() {
  srand(unsigned(time(0)));
  string instancia = "txt\\darp1.txt";
  lerArquivo(instancia);
  Solucao s;
  // Solucao s2[MAX];
  HCAleatoria(s);
  calcularFO(s);

  // string arquivoSaida = "";
  // escreverDados(arquivoSaida);
  // calcularFO(s);
}

void lerArquivo(string nome) {
  FILE *f = fopen(nome.c_str(), "r");
  fscanf(f, "%d %d %d %d %d", &veiculos, &requisicoes, &duracaoRotaMax, &tempoViagemMax, &tempoEsperaMax);
  int requisicaoTotal = requisicoes * 2 + 2;
  for (int i = 0; i < veiculos; i++) {
    fscanf(f, "%d", &capVeiculos[i]);
  }
  for (int i = 0; i < requisicaoTotal; i++) {
    fscanf(f, "%d", &numAssentos[i]);
  }
  for (int i = 0; i < requisicaoTotal; i++) {
    fscanf(f, "%d", &tempoServico[i]);
  }
  for (int i = 0; i < requisicaoTotal; i++) {
    fscanf(f, "%d", &inicioJanelaTempo[i]);
  }
  for (int i = 0; i < requisicaoTotal; i++) {
    fscanf(f, "%d", &fimJanelaTempo[i]);
  }
  for (int i = 0; i < requisicaoTotal; i++) {
    for (int j = 0; j < requisicaoTotal; j++) {
      fscanf(f, "%d", &matrizTempoDeslocamento[i][j]);
    }
  }
  for (int i = 0; i < requisicaoTotal; i++) {
    janelaTempoTotal[i] = fimJanelaTempo[i] - inicioJanelaTempo[i];
  }
  fclose(f);
}

void escreverDados(string nome) {
  FILE *f;
  if (nome == "") {
    f = stdout;
  } else {
    f = fopen(nome.c_str(), "w");
  }
  fprintf(f, "%d\t%d\t%d\t%d\t%d\n", veiculos, requisicoes,
          duracaoRotaMax, tempoViagemMax, tempoEsperaMax);
  int totalRequisicoes = requisicoes * 2 + 2;
  breakLine(f, 3);
  for (int i = 0; i < veiculos; i++) {
    fprintf(f, "%d\t", capVeiculos[i]);
  }
  breakLine(f, 3);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", numAssentos[i]);
  }
  breakLine(f, 3);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", tempoServico[i]);
  }
  breakLine(f, 3);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", inicioJanelaTempo[i]);
  }
  breakLine(f, 3);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", fimJanelaTempo[i]);
  }
  breakLine(f, 3);
  for (int i = 0; i < totalRequisicoes; i++) {
    for (int j = 0; j < totalRequisicoes; j++) {
      fprintf(f, "%d\t", matrizTempoDeslocamento[i][j]);
    }
    breakLine(f, 3);
  }
}

void simulatedAnnealing() {
  clock_t inicio, fim;
  inicio = clock();

  fim = clock();
}
void printVetor(std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    printf("VETOR[%d]\t=\t%d\n", i, vetor[i]);
  }
  printf("\nITERACAO %d\n\n", vetor.size());
}
void HCAleatoria(Solucao &s) {
  std::map<int, size_t> dCount;
  std::vector<int> arrayLocais;  // Array para embaralhar com os locais e distribuir entre os veiculos
  for (int i = 0; i < requisicoes; i++) {
    arrayLocais.push_back(1 + 2 * i);  // Posições impares = embarque
  }

  auto rng = std::mt19937{std::random_device{}()};

  std::shuffle(std::begin(arrayLocais), std::end(arrayLocais), rng);
  Veiculo _veiculos[MAX_VEICULOS];
  // memset(_veiculos, 0, sizeof(Veiculo) * MAX);
  for (int i = 0; i < veiculos; i++) {
    _veiculos[i].id = i;
    // printVetor(arrayLocais);
    for (int j = 0; j < requisicoes / veiculos; j++) {
      _veiculos[i].rotasEmbarque[j] = arrayLocais[j];
      _veiculos[i].rotasDesembarque[j] = _veiculos[i].rotasEmbarque[j] + 1;
      arrayLocais.erase(arrayLocais.begin() + j);  // Remove do array
    }
    std::shuffle(std::begin(arrayLocais), std::end(arrayLocais), rng);
  }
  int embarque = 0;
  int desembarque = 999;
  int requisicaoAtual = 1;
  // Para cada veiculo faz
  for (int i = 0; i < veiculos; i++) {
    int distancia = 0;
    for (int j = 0; j < requisicoes / veiculos; j++) {
      _veiculos[i].assentosUtilizados += numAssentos[requisicaoAtual];
      distancia += matrizTempoDeslocamento[embarque][_veiculos[i].rotasEmbarque[j]];
      embarque = _veiculos[i].rotasEmbarque[j];
      requisicaoAtual++;
      // printf("VEICULO[%d].EMBARQUE[%d]:\t\t%d\n", i, j, _veiculos[i].rotasEmbarque[j]);
    }
    embarque = _veiculos[i].rotasEmbarque[requisicoes / veiculos - 1];
    desembarque = _veiculos[i].rotasDesembarque[requisicoes / veiculos - 1];
    distancia += matrizTempoDeslocamento[embarque][desembarque];
    _veiculos[i].distanciaPercorrida = distancia;
    // #ifdef DEBUG
    // printf("VEICULO[%d].assentosUtilizados:\t%d\n", i, _veiculos[i].assentosUtilizados);
    // printf("DESEMBARQUE NA MAO:\t%d\n", _veiculos[i].rotasEmbarque[requisicoes / veiculos - 1] + 1);
    // printf("DESEMBARQUE S/ MAO:\t%d\n", _veiculos[i].rotasDesembarque[requisicoes / veiculos - 1]);
    // printf("Requisição atual:\t%d\n", requisicaoAtual);
    // printf("DISTANCIA: %d\n\n", distancia);
    // #endif
  }
  memcpy(s.veiculos, _veiculos, sizeof(s.veiculos));
#ifdef DEBUG
  printf("SIZE: %d", arrayLocais.size());
#endif

  // for (int i = 0; i < veiculos; i++) {
  //   for (int j = 0; j < requisicoes; j++) {
  //     printf("veiculo[%d].rotas[%d]\t=\t%d\n", i, j, _veiculos[i].rotasEmbarque[j]);  // PROBLEMA: INICIANDO VEICULO APENAS LOCALMENTE
  //   }
  //   printf("\n");
  // }
  breakLine(stdout, 2);
  // for (const auto elem : s.requisicaoAtendidaPor) {
  //   if (elem < 0 || elem > 100) break;
  //   dCount[elem] += 1;
  // }
  // printf("################FOR NORMAL################\n");
  // for (const auto &elem : dCount) {
  //   cout << "QTD " << elem.first << ": " << elem.second << "\n";
  // }
  // printf("#####################################\n");
  // int distancia = 0;
  // int rota[MAX][MAX];

  /*
    SOLUCAO DO PAPER https://www.scielo.br/j/prod/a/Rjp7trrCwDsRRstVGCLJp8y/?lang=pt#
  */

  // breakLine(stdout, 2);

  // std::map<int, size_t> cCount;
  // const int range_from = 0;
  // const int range_to = veiculos;
  // std::random_device rand_dev;
  // std::mt19937 generator(rand_dev());
  // std::uniform_int_distribution<int> distr(range_from, range_to);
  // for (int i = 0; i < requisicoes; i++) {
  //   s.requisicaoAtendidaPor[i] = distr(generator);
  //   printf("Requisicao %d atendida por: %d\n", i + 1, s.requisicaoAtendidaPor[i]);
  // }
  // breakLine(stdout, 2);
  // for (const auto elem : s.requisicaoAtendidaPor) {
  //   if (elem < 0 || elem > 100) break;
  //   cCount[elem] += 1;
  // }
  // printf("################FOR C++11################\n");
  // for (const auto &elem : cCount) {
  //   cout << "QTD " << elem.first << ": " << elem.second << "\n";
  // }
  // printf("#####################################\n");
}

void calcularFO(Solucao &s) {
  int p1 = PESO1 * veiculos;
  int distancia = 0;
  for (int i = 0; i < veiculos; i++) {
    distancia += s.veiculos[i].distanciaPercorrida;
  }

  int p2 = PESO2 * distancia;

  s.FO = p1 + p2;

  printf("FO: %d\n", s.FO);
}

void clonarSolucao(Solucao &original, Solucao &copia) {
  memcpy(&copia, &original, sizeof(original));
}

void escreverSolucao(Solucao &s, const bool flag) {
  printf("FO: %d\n", s.FO);
  // if (flag) {
  //   printf("Veiculos usados: %d\n");
  //   printf("Distancia percorrida: %d\n");
  //   printf("Duração das rotas: %d\n");
  //   printf("Tempo total de viagem: %d\n");
  //   printf("Tempo total de espera: %d\n");
  //   breakLine(stdout, 3);
  //   printf("Violações de assentos: %d\n");
  //   printf("Violações da duração maxima de rotas: %d\n");
  //   printf("Violações do tempo maximo de espera: %d\n");
  //   printf("Violações dos horarios de saida e chegada: %d\n");
  // }
}

void breakLine(FILE *f, const int num) {
  for (int i = 0; i < num; i++) {
    fprintf(f, "\n");
  }
}