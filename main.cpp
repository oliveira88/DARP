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
  string instancia = "txt\\darp1.txt";
  lerArquivo(instancia);
  int pior = 0;
  int melhor = 5000;
  for (int i = 0; i < 1; i++) {
    Solucao s;
    HCAleatoria(s);
    calcularFO(s);
    escreverSolucao(s, false);
    if (s.FO < melhor) {
      melhor = s.FO;
    }
    if (s.FO > pior) {
      pior = s.FO;
    }
  }
  // cout << "MELHOR " << melhor << "\n";
  // cout << "PIOR " << pior << "\n";
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
#ifdef DEBUG
  for (int i = 0; i < veiculos; i++) {
    printf("VEICULO %d\n", i + 1);
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      printf("EMBARQUE[%d] - DESEMBARQUE[%d]\n", _veiculos[i].rotasEmbarque[j], _veiculos[i].rotasDesembarque[j]);
    }
  }
#endif
  int desembarque = 999;
  // Para cada veiculo faz o embarque
  for (int i = 0; i < veiculos; i++) {
    int embarque = 0;  // Embarque da garagem
    int distanciaTotal = 0;
    _veiculos[i].distanciaPercorrida = 0;
    for (int j = 0; j < _veiculos[i].assentosUtilizados; j++) {
      // PEGA CADA PESSOA EM SEU LOCAL
      int distanciaAtual = matrizTempoDeslocamento[embarque][_veiculos[i].rotasEmbarque[j]];
      distanciaTotal += distanciaAtual;

      int horarioAberturaLocal = inicioJanelaTempo[_veiculos[i].rotasEmbarque[j]];
      int horarioChegada = inicioJanelaTempo[embarque] + distanciaAtual;
      int tempodeEspera = horarioAberturaLocal - horarioChegada;
      if (tempodeEspera > 0) {
        _veiculos[i].tempoEspera += tempodeEspera;
      }
      // cout << "LOCAL " << _veiculos[i].rotasEmbarque[j] << "\n";
      // cout << "HORARIO DE ABERTURA GARAGEM: " << inicioJanelaTempo[0] << "\n";
      // cout << "HORARIO DE ABERTURA LOCAL: " << horarioAberturaLocal << "\n";
      // cout << "HORARIO DE CHEGADA: " << horarioChegada << "\n";
      // cout << "DISTANCIA ATUAL: " << distanciaAtual << "\n";
      // cout << "TEMPO DE ESPERA: " << tempodeEspera << "\n";
      embarque = _veiculos[i].rotasEmbarque[j];
      // printf("DISTANCIA no embarque: %d\n\n", distancia);
      // printf("\n\n");
    }
    printf("\n\n");

    _veiculos[i].distanciaPercorrida += distanciaTotal;
    _veiculos[i].duracaoRota += distanciaTotal;
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
      // cout << "LOCAL " << _veiculos[i].rotasEmbarque[j] << "\n";
      // cout << "HORARIO DE ABERTURA GARAGEM: " << fimJanelaTempo[0] << "\n";
      // cout << "HORARIO DE FECHAMENTP LOCAL: " << horarioFechamentoLocal << "\n";
      // cout << "HORARIO DE CHEGADA: " << horarioChegada << "\n";
      // cout << "DISTANCIA ATUAL: " << distanciaAtual << "\n";
      // cout << "TEMPO DE ESPERA: " << tempodeEspera << "\n";
      embarque = _veiculos[i].rotasDesembarque[j];
      // printf("DISTANCIATotal no desembarque: %d\n\n", distanciaTotal);
      // cout << "TEMPO DE ESPERA: " << tempodeEspera << "\n";
    }
    // printf("\n\n");
    distanciaTotal += matrizTempoDeslocamento[embarque][requisicoes * 2 + 1];  // Vai pra garagem
    _veiculos[i].distanciaPercorrida += distanciaTotal;
    // printf("Veiculo[%d] distancia: %d\n", i + 1, _veiculos[i].distanciaPercorrida);
    // #ifdef DEBUG
    // printf("VEICULO[%d].assentosUtilizados:\t%d\n", i, _veiculos[i].assentosUtilizados);
    // printf("DESEMBARQUE NA MAO:\t%d\n", _veiculos[i].rotasEmbarque[_veiculos[i].assentosUtilizados - 1] + 1);
    // printf("DESEMBARQUE S/ MAO:\t%d\n", _veiculos[i].rotasDesembarque[_veiculos[i].assentosUtilizados - 1] + 1);
    // printf("Requisição atual:\t%d\n", requisicaoAtual);
    // printf("DISTANCIA: %d\n\n", distancia);
    // #endif
  }
  memcpy(s.veiculos, _veiculos, sizeof(s.veiculos));

  // for (int i = 0; i < veiculos; i++) {
  //   for (int j = 0; j < requisicoes; j++) {
  //     printf("veiculo[%d].rotas[%d]\t=\t%d\n", i, j, _veiculos[i].rotasEmbarque[j]);  // PROBLEMA: INICIANDO VEICULO APENAS LOCALMENTE
  //   }
  //   printf("\n");
  // }
  // breakLine(stdout, 2);

  verificaViolacoes(s);
}

void calcularFO(Solucao &s) {
  int p1 = PESO1 * veiculos;
  int distancia = 0;
  for (int i = 0; i < veiculos; i++) {
    distancia += s.veiculos[i].distanciaPercorrida;
  }

  int p2 = PESO2 * distancia;

  s.FO = p1 + p2;

  // printf("FO: %d\n", s.FO);
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
    printf("Violações de assentos: %d\n", violacoesAssentosTotal);
    printf("Violações da duração maxima de rotas: %d\n", violacoesDurMaxTotal);
    printf("Violações do tempo maximo de espera: %d\n", violacoesTempoMaximoEsperaTotal);
    printf("Violações dos horarios de saida e chegada: %d\n", violacoesHRSaidaeChegadaTotal);

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