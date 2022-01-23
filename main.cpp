#include "main.hpp"

#include <math.h>
#include <memory.h>
#include <time.h>

#include <iostream>
#include <string>
#define LENGTH(x) (sizeof(x) / sizeof(x)[0])

using namespace std;
int main() {
  string instancia = "txt\\darp1.txt";
  lerArquivo(instancia);
  Solucao s;
  HCAleatoria(s);
  calcularFO(s);
  string arquivoSaida = "";
  escreverDados(arquivoSaida);
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

void HCAleatoria(Solucao &s) {
}

void HCGulosa(Solucao &s) {
}

void HCAleatoriaGulosa(Solucao &s) {}

void calcularFO(Solucao &s) {
  int p1 = PESO1 * veiculos;
  int p2 = 0;
  for (int i = 0; i < veiculos; i++) {
  }
  // Iterando
  for (int i = 1; i < requisicoes * 2 + 1; i++) {
    int embarque = i;
    int desembarque = i + 1;
  }
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