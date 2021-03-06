#include "main.hpp"

#include <math.h>
#include <memory.h>
#include <time.h>

#include <algorithm>
#include <cassert>
#include <chrono>
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
  clock_t tempoInicial, tempoFinal;
  tempoInicial = clock();
  string instancia = "txt\\darp3.txt";
  lerArquivo(instancia);
  for (int i = 0; i < 1; i++) {
    Solucao s;
    HCAleatoria(s);
    calcularFO(s);
    escreverSolucao(s, true);
  }

  // tempoFinal = clock() - tempoInicial;
  // double tempoTotal = (double)tempoFinal / CLOCKS_PER_SEC;
  // printf("Tempo total: %.2f\n\n\n", tempoTotal);

  // tempoInicial = clock();
  // for (int i = 0; i < 1000; i++) {
  //   Solucao s;
  //   HCAleatoria(s);
  // }
  // tempoFinal = clock() - tempoInicial;
  // tempoTotal = (double)tempoFinal / CLOCKS_PER_SEC;
  // printf("Tempo total: %.2f\n\n\n", tempoTotal);

  // tempoInicial = clock();
  // for (int i = 0; i < 1000; i++) {
  //   Solucao s;
  //   calcularFO(s);
  // }
  // tempoFinal = clock() - tempoInicial;
  // tempoTotal = (double)tempoFinal / CLOCKS_PER_SEC;
  // printf("Tempo total: %.2f\n\n\n", tempoTotal);
  // // escreverSolucao(s, false);
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
  // auto rng = std::mt19937{std::random_device{}()};
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng(seed);

  std::shuffle(std::begin(arrayLocais), std::end(arrayLocais), rng);
  Veiculo _veiculos[MAX_VEICULOS];

  int divReqVeiculos = requisicoes / veiculos;
  int reqRestantes = requisicoes % veiculos;
  int cont = 0;
  for (int i = 0; i < veiculos; i++) {
    _veiculos[i].assentosUtilizados = divReqVeiculos;
    s.veiculosUtilizados += 1;
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
    _veiculos[i].requicoesAtendidas += 1;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      _veiculos[i].rotasEmbarque[j] = arrayLocais[0];
      _veiculos[i].rotasDesembarque[j] = _veiculos[i].rotasEmbarque[j] + requisicoes;
      arrayLocais.erase(arrayLocais.begin() + 0);  // Remove do vector
    }
    std::shuffle(std::begin(arrayLocais), std::end(arrayLocais), rng);
  }
  int desembarque = 999;
  // Para cada veiculo faz o embarque
  for (int i = 0; i < veiculos; i++) {
    int embarque = 0;  // Embarque da garagem
    int distanciaTotal = 0;
    int tempoTotal = inicioJanelaTempo[0];
    _veiculos[i].horarioDeInicio = tempoTotal;
    _veiculos[i].distanciaPercorrida = 0;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      // PEGA CADA PESSOA EM SEU LOCAL
      int distanciaAtual = matrizTempoDeslocamento[embarque][_veiculos[i].rotasEmbarque[j]];
      tempoTotal += distanciaAtual;
      distanciaTotal += distanciaAtual;

      int horarioAberturaLocal = inicioJanelaTempo[_veiculos[i].rotasEmbarque[j]];
      int horarioChegada = tempoTotal;
      int tempodeEspera = horarioAberturaLocal - horarioChegada;
      if (tempodeEspera > 0) {
        _veiculos[i].tempoEspera += tempodeEspera;
        tempoTotal += tempodeEspera;
      }

      s.horariosEmbarquePPNE[_veiculos[i].rotasEmbarque[j]] = tempoTotal;
      embarque = _veiculos[i].rotasEmbarque[j];
    }
    _veiculos[i].distanciaPercorrida += distanciaTotal;
    _veiculos[i].horarioDeFim = tempoTotal;
    _veiculos[i].duracaoRota += distanciaTotal;
  }

  // Para cada veiculo faz o desembarque
  for (int i = 0; i < veiculos; i++) {
    int embarque = _veiculos[i].rotasEmbarque[_veiculos[i].assentosUtilizados - 1];  // Ultima rota embarcada
    int cont = 0;
    int distanciaTotal = 0;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      // ENTREGA CADA PESSOA EM SEU LOCAL
      int distanciaAtual = matrizTempoDeslocamento[embarque][_veiculos[i].rotasDesembarque[j]];
      distanciaTotal += distanciaAtual;

      int horarioFechamentoLocal = fimJanelaTempo[_veiculos[i].rotasDesembarque[j]];
      int horarioChegada = fimJanelaTempo[embarque] + distanciaAtual;
      int tempoViolado = horarioFechamentoLocal - horarioChegada;
      if (tempoViolado < 0) {
        _veiculos[i].violacoes.horarioSaidaEChegadaGaragens += 1;
      }

      s.horariosDesembarquePPNE[_veiculos[i].rotasDesembarque[j] - requisicoes] = horarioChegada;
      embarque = _veiculos[i].rotasDesembarque[j];
    }
    distanciaTotal += matrizTempoDeslocamento[embarque][requisicoes * 2 + 1];  // Vai pra garagem
    _veiculos[i].distanciaPercorrida += distanciaTotal;
  }
  memcpy(s.veiculos, _veiculos, sizeof(s.veiculos));
  verificaViolacoes(s);
}

void calcularFO(Solucao &s) {
  int p1 = PESO1 * veiculos;
  int distancia = 0;
  for (int i = 0; i < veiculos; i++) {
    distancia += s.veiculos[i].distanciaPercorrida;
  }
  int p2 = PESO2 * distancia;

  int horariosVeiculoChega = 0;
  for (int i = 0; i < veiculos; i++) {
    horariosVeiculoChega += s.veiculos[i].horarioDeFim - s.veiculos[i].horarioDeInicio;
  }
  int p3 = PESO3 * horariosVeiculoChega;

  int horarioEmbDesPPNES = 0;
  for (int i = 0; i < requisicoes; i++) {
    horarioEmbDesPPNES += s.horariosDesembarquePPNE[i] - s.horariosEmbarquePPNE[i];
  }
  int p4 = PESO4 * horarioEmbDesPPNES;

  int p5 = 0;
  s.FO = p1 + p2 + p3 + p4 + p5;
}

void clonarSolucao(Solucao &original, Solucao &copia) {
  memcpy(&copia, &original, sizeof(original));
}

void escreverSolucao(Solucao &s, const bool flag) {
  printf("FO: %d\n", s.FO);
  if (flag) {
    printf("Veiculos usados: %d\n\n", s.veiculosUtilizados);
    for (int i = 0; i < veiculos; i++) {
      printf("Distancia percorrida pelo veiculo[%d]: %d\n", i + 1, s.veiculos[i].distanciaPercorrida);
    }
    printf("\n");
    for (int i = 0; i < veiculos; i++) {
      printf("Num. de requisicoes atendidas pelo veiculo[%d]: %d\n", i + 1, s.veiculos[i].requicoesAtendidas);
    }
    printf("\n");
    for (int i = 0; i < veiculos; i++) {
      printf("Assentos utilizados pelo veiculo[%d]: %d\n", i + 1, s.veiculos[i].assentosUtilizados);
    }
    printf("\n");
    for (int i = 0; i < veiculos; i++) {
      printf("Duracao da rota do veiculo[%d]: %d\n", i + 1, s.veiculos[i].duracaoRota);
    }
    printf("\n");
    for (int i = 0; i < veiculos; i++) {
      printf("Tempo de espera do veiculo[%d]: %d\n", i + 1, s.veiculos[i].tempoEspera);
    }
    printf("\n");
    // for(int i = 0; i < veiculos; i ++) {
    //   printf("Tempo de espera do veiculo[%d]: %d\n", i+1, s.veiculos[i].tempoViagem);
    // }
    breakLine(stdout, 3);
    printf("\t---VIOLACOES---\n");
    int violacoesAssentosTotal = 0;
    int violacoesDurMaxTotal = 0;
    int violacoesHRSaidaeChegadaTotal = 0;
    int violacoesTempoMaximoEsperaTotal = 0;
    for (int i = 0; i < veiculos; i++) {
      violacoesAssentosTotal += s.veiculos[i].violacoes.numAssentos;
      violacoesDurMaxTotal += s.veiculos[i].violacoes.duracaoMaximaRota;
      violacoesTempoMaximoEsperaTotal += s.veiculos[i].violacoes.tempoMaximoEspera;
      violacoesHRSaidaeChegadaTotal += s.veiculos[i].violacoes.horarioSaidaEChegadaGaragens;
    }
    printf("Viola????es de assentos: %d\n", violacoesAssentosTotal);
    printf("Viola????es da dura????o maxima de rotas: %d\n", violacoesDurMaxTotal);
    printf("Viola????es do tempo maximo de espera: %d\n", violacoesTempoMaximoEsperaTotal);
    printf("Viola????es dos horarios de saida e chegada: %d\n", violacoesHRSaidaeChegadaTotal);

    printf("\n\n");

    printf("Sequencia com a rota do veiculo: \n");
    for (int i = 0; i < veiculos; i++) {
      printf("0 ");
      for (int j = 0; j < s.veiculos[i].assentosUtilizados; j++) {
        printf("%d ", s.veiculos[i].rotasEmbarque[j]);
      }
      for (int j = 0; j < s.veiculos[i].assentosUtilizados; j++) {
        printf("%d ", s.veiculos[i].rotasDesembarque[j]);
      }
      printf("%d", requisicoes * 2 + 1);
      printf("\n");
    }
  }
}

void breakLine(FILE *f, const int num) {
  for (int i = 0; i < num; i++) {
    fprintf(f, "\n");
  }
}

void verificaViolacoes(Solucao &s) {
  for (int i = 0; i < veiculos; i++) {
    if (s.veiculos[i].assentosUtilizados > capVeiculos[i]) {
      s.veiculos[i].violacoes.numAssentos += 1;
    }
    if (s.veiculos[i].tempoViagem > duracaoRotaMax) {
      s.veiculos[i].violacoes.duracaoMaximaRota += 1;
    }
    if (s.veiculos[i].assentosUtilizados > capVeiculos[i]) {
      s.veiculos[i].violacoes.numAssentos += 1;
    }
  }
}

void lerSolucaoQualquer(string nome) {
  FILE *f = fopen(nome.c_str(), "r");
  int FO;

  int veiculosUsados;
  int idVeiculo;
  int requisicoesAtendidas;
  int requisicoesAtendidass;
  int vetorIdLocais[MAX][MAX];
  fscanf(f, "%d", &FO);
  fscanf(f, "%d", &veiculosUsados);
  for (int i = 0; i < veiculosUsados; i++) {
    fscanf(f, "%d", &idVeiculo);
    fscanf(f, "%d", &requisicoesAtendidas);
    for (int j = 0; j < requisicoesAtendidas * 2 + 2; j++) {
      fscanf(f, "%d", &vetorIdLocais[i][j]);
    }
  }
}