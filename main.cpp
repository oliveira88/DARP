#include "main.hpp"

#include <math.h>
#include <memory.h>
#include <time.h>

#include <algorithm>
#include <cassert>
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
  string instancia = "txt\\darp3.txt";
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
  printf("\nTAMANHO VECTOR: %d\n\n", vetor.size());
}

void HCAleatoria(Solucao &s) {
  std::map<int, size_t> dCount;
  std::vector<int> arrayLocais;  // Array para embaralhar com os locais e distribuir entre os veiculos

  for (int i = 1; i < requisicoes + 1; i++) {
    arrayLocais.push_back(i);  // Array Locais com embarques
  }
  auto rng = std::mt19937{std::random_device{}()};

  std::shuffle(std::begin(arrayLocais), std::end(arrayLocais), rng);
  Veiculo _veiculos[MAX_VEICULOS];

  int divReqVeiculos = requisicoes / veiculos;
  int reqRestantes = requisicoes % veiculos;
  int cont = 0;
  for (int i = 0; i < veiculos; i++) {
    _veiculos[i].assentosUtilizados = divReqVeiculos;
  }
  int k = 0;
  while (reqRestantes > 0) {
    _veiculos[k++].assentosUtilizados++;
    reqRestantes--;
  }
  for (int i = 0; i < veiculos; i++) {
    cont += _veiculos[i].assentosUtilizados;
  }

  for (int i = 0; i < veiculos; i++) {
    _veiculos[i].id = i;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      _veiculos[i].rotasEmbarque[j] = arrayLocais[0];
      _veiculos[i].rotasDesembarque[j] = _veiculos[i].rotasEmbarque[j] + requisicoes;
      arrayLocais.erase(arrayLocais.begin() + 0);  // Remove do vector
    }
    std::shuffle(std::begin(arrayLocais), std::end(arrayLocais), rng);
  }
  for (int i = 0; i < veiculos; i++) {
    printf("VEICULO %d\n", i + 1);
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      printf("EMBARQUE[%d] - DESEMBARQUE[%d]\n", _veiculos[i].rotasEmbarque[j], _veiculos[i].rotasDesembarque[j]);
    }
  }
  int desembarque = 999;
  // Para cada veiculo faz o embarque
  for (int i = 0; i < veiculos; i++) {
    int embarque = 0;  // Embarque da garagem
    int distancia = 0;
    _veiculos[i].distanciaPercorrida = 0;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      // PEGA CADA PESSOA EM SEU LOCAL
      // _veiculos[i].assentosUtilizados += numAssentos[requisicaoAtual];
      distancia += matrizTempoDeslocamento[embarque][_veiculos[i].rotasEmbarque[j]];
      embarque = _veiculos[i].rotasEmbarque[j];
      printf("DISTANCIA no embarque: %d\n\n", distancia);
    }
    printf("\n\n");
    _veiculos[i].distanciaPercorrida += distancia;
    // #ifdef DEBUG
    // printf("VEICULO[%d].assentosUtilizados:\t%d\n", i, _veiculos[i].assentosUtilizados);
    // printf("DESEMBARQUE NA MAO:\t%d\n", _veiculos[i].rotasEmbarque[_veiculos[i].assentosUtilizados - 1] + 1);
    // printf("DESEMBARQUE S/ MAO:\t%d\n", _veiculos[i].rotasDesembarque[_veiculos[i].assentosUtilizados - 1] + 1);
    // printf("Requisição atual:\t%d\n", requisicaoAtual);
    // printf("DISTANCIA: %d\n\n", distancia);
    // #endif
  }

  // Para cada veiculo faz o desembarque
  for (int i = 0; i < veiculos; i++) {
    int embarque = _veiculos[i].rotasEmbarque[_veiculos[i].assentosUtilizados - 1];  // Ultima rota embarcada
    int cont = 0;
    int distancia = 0;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      // ENTREGA CADA PESSOA EM SEU LOCAL
      distancia += matrizTempoDeslocamento[embarque][_veiculos[i].rotasDesembarque[j]];
      embarque = _veiculos[i].rotasDesembarque[j];
      // printf("DISTANCIA no desembarque: %d\n\n", distancia);
    }
    printf("\n\n");
    distancia += matrizTempoDeslocamento[embarque][requisicoes * 2 + 1];  // Vai pra garagem
    _veiculos[i].distanciaPercorrida += distancia;
    printf("Veiculo[%d] distancia: %d\n", i + 1, _veiculos[i].distanciaPercorrida);
    // #ifdef DEBUG
    // printf("VEICULO[%d].assentosUtilizados:\t%d\n", i, _veiculos[i].assentosUtilizados);
    // printf("DESEMBARQUE NA MAO:\t%d\n", _veiculos[i].rotasEmbarque[_veiculos[i].assentosUtilizados - 1] + 1);
    // printf("DESEMBARQUE S/ MAO:\t%d\n", _veiculos[i].rotasDesembarque[_veiculos[i].assentosUtilizados - 1] + 1);
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

  /*
    SOLUCAO DO PAPER https://www.scielo.br/j/prod/a/Rjp7trrCwDsRRstVGCLJp8y/?lang=pt#
  */
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