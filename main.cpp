#include "main.hpp"

#include <math.h>
#include <memory.h>
#include <time.h>

#include <iostream>
#include <string>

using namespace std;
int main() {
  Solucao s;
  lerArquivo("txt\\darp1.txt", s);
  escreverDados("", s);
  // calcularFO();
}

void lerArquivo(string nome, Solucao &s) {
  FILE *f = fopen(nome.c_str(), "r");
  fscanf(f, "%d %d %d %d %d", &s.entrada.veiculos, &s.entrada.requisicoes, &s.entrada.duracaoRotaMax,
         &s.entrada.tempoViagemMax, &s.entrada.tempoEsperaMax);
  int requisicaoTotal = s.entrada.requisicoes * 2 + 2;
  for (int i = 0; i < s.entrada.veiculos; i++) {
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
      fscanf(f, "%d", &matriz[i][j]);
    }
  }
  fclose(f);
}

void escreverDados(string nome, Solucao &s) {
  FILE *f;
  if (nome == "") {
    f = stdout;
  } else {
    f = fopen(nome.c_str(), "w");
  }
  fprintf(f, "%d\t%d\t%d\t%d\t%d\n", s.entrada.veiculos, s.entrada.requisicoes,
          s.entrada.duracaoRotaMax, s.entrada.tempoViagemMax, s.entrada.tempoEsperaMax);
  int totalRequisicoes = s.entrada.requisicoes * 2 + 2;
  breakLine(f, 5);
  for (int i = 0; i < s.entrada.veiculos; i++) {
    fprintf(f, "%d\t", capVeiculos[i]);
  }
  breakLine(f, 5);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", numAssentos[i]);
  }
  breakLine(f, 5);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", tempoServico[i]);
  }
  breakLine(f, 5);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", inicioJanelaTempo[i]);
  }
  breakLine(f, 5);
  for (int i = 0; i < totalRequisicoes; i++) {
    fprintf(f, "%d\t", fimJanelaTempo[i]);
  }
  breakLine(f, 5);
  for (int i = 0; i < totalRequisicoes; i++) {
    for (int j = 0; j < totalRequisicoes; j++) {
      fprintf(f, "%d\t", matriz[i][j]);
    }
    breakLine(f, 3);
  }
}

void simulatedAnnealing() {
  clock_t inicio, fim;
  inicio = clock();

  fim = clock();
}

void HCAleatoria(Solucao &s) {}

void HCGulosa(Solucao &s) {}

void HCAleatoriaGulosa(Solucao &s) {}

void calcularFO(Solucao &s) {
  int p1 = PESO1 * s.entrada.veiculos;
  int p2 = 0;
}

void clonarSolucao(Solucao &original, Solucao &copia) {
  memcpy(&copia, &original, sizeof(original));
}

void breakLine(FILE *f, const int num) {
  for (int i = 0; i < num; i++) {
    fprintf(f, "\n");
  }
}