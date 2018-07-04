#include <iostream>
#include <string>
#include <vector>
#include "pipeline.h"

int main(int argc, char * argv[]) {
  /* Inicialização de um vetor de strings com todas as instruções alocadas
  atráves de um função */
	std::vector <std::string> inputString;
  fill(inputString);
  /* Inicialização de um vetor de strings cheia de zeros com um total de
  elementos em seu pior caso, onde as instruções serão alocadas atráves
  de um função */
	int cycle = 0, worstCase = 1 + 4*(inputString.size());
  std::vector <std::string> ifStage, idStage, exStage, memStage, wbStage;
  for (int i=0; i<worstCase; i++){
    ifStage.push_back("0");
    idStage.push_back("0");
    exStage.push_back("0");
    memStage.push_back("0");
    wbStage.push_back("0");
  }
  /* Função que irá alocar no vetores de estágios as strings de cada instrução. */
	pipeline(ifStage, idStage, exStage, memStage, wbStage, inputString, cycle);
  /* Função que irá printar na tela a cada estágio as instruções em execução. */
	stages(ifStage, idStage, exStage, memStage, wbStage, cycle);

	return 0;
	}
