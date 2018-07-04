#include <iostream>
#include <string>
#include <vector>
#include "pipeline.h"

/* Função que irá inicializar em um vector de strings as intruções dadas no
arquivo de entrada. */
void fill(std::vector <std::string> &inputString) {
  std::string instruction;
  while ( getline(std::cin, instruction) ) {
    inputString.push_back(instruction);
  }
}
/* Função que irá trocar as dependências a serem vereficadas pela instrução
seguinte, assim não causando conflitos de dados. */
void changeDependecy(std::vector <std::string> &dependecyRegisters,
                     const std::string &newRegister){
  for(int i = 3; i > 0; i--) dependecyRegisters[i] = dependecyRegisters[i-1];
  dependecyRegisters[0] = newRegister;
}
/* Função que baseado nas dependências anteriores sera retornado o ciclo, no
qual começará a ser executado a linha lida.*/
int dependecy (const int &cycle,
               std::vector <std::string> &dependecyRegisters,
               const std::string &register2,
               const std::string &register3,
               const std::string &registerAux = "0"){
  for(int i = 0; i < 4; i++){
    if (cycle == 0) return cycle;
    else if((dependecyRegisters[i].compare(register2) == 0)
         || (dependecyRegisters[i].compare(register3) == 0)
         || (dependecyRegisters[i].compare(registerAux) == 0)) {
      dependecyRegisters[i] = " ";
      return (cycle - i + 4);
    }
  }
  return (cycle + 1);
}
/* Função que irá realocar nos vectors dos estágios as instruções que serão
executadas. */
void reallocateInstruction (std::vector <std::string> &ifStage,
                            std::vector <std::string> &idStage,
                            std::vector <std::string> &exStage,
                            std::vector <std::string> &memStage,
                            std::vector <std::string> &wbStage,
                            const std::string instruction,
                            const int &cycle, const int &i){
  ifStage[cycle - i] = instruction;
  idStage[cycle + 1 - i] = instruction;
  exStage[cycle + 2 - i] = instruction;
  memStage[cycle + 3 - i] = instruction;
  wbStage[cycle + 4 - i] = instruction;
}
/* Função principal que no final irá alocar no vetores de estágios as strings
de cada instrução.*/
void pipeline (std::vector <std::string> &ifStage,
               std::vector <std::string> &idStage,
               std::vector <std::string> &exStage,
               std::vector <std::string> &memStage,
               std::vector <std::string> &wbStage,
               std::vector <std::string> inputString,
               int &cycle){

  std::string instruction, label, operation, rest, register1 = " ", register2, register3, registerAux, noDependecy = " ";
	int sizeCase = inputString.size();
  std::vector <std::string> dependecyRegisters (4);
  bool passLabel = false;
  std::size_t found;

  /* Loop que irá rodar até a última linha, sempre separando o operando e
  identificando a operação, para depois separar os registradores de forma
  correta para testar as dependências de forma a inserir corretamente,
  como em saltos, procurar pelo label posto na instrução. */
  for(int i = 0; i < sizeCase; i++, cycle++) {

		instruction = inputString[i];
		found = instruction.find_first_of(":");

		if (found!=std::string::npos){
			operation = instruction.substr(0,found);
		}
		else{
			found = instruction.find_first_of(" ");
	    operation = instruction.substr(0,found);
	    rest = instruction.substr(found + 1);
		}

    if (operation.compare(label) == 0) passLabel = false;
    else if ((operation.compare("add") == 0 || operation.compare("sub") == 0) && passLabel == false) {
      found = rest.find_last_of(" ");
      register3 = rest.substr(found+1);
      rest = rest.substr(0, found-1);
      found = rest.find_last_of(" ");
      register2 = rest.substr(found+1);
      registerAux = rest.substr(0,found-1);
      cycle = dependecy (cycle, dependecyRegisters, register2, register3, registerAux);
      reallocateInstruction(ifStage, idStage, exStage, memStage, wbStage, instruction, cycle, i);
      register1 = registerAux;
    }
    else if ((operation.compare("beq") == 0 || operation.compare("bne") == 0) && passLabel == false) {
      found = rest.find_first_of(",");
      register2 = rest.substr(0, found);
      rest = rest.substr(found+2);
      found = rest.find_first_of(",");
      register3 = rest.substr(0, found);
      label = rest.substr(found+2);
      cycle = dependecy (cycle, dependecyRegisters, register2, register3);
      reallocateInstruction(ifStage, idStage, exStage, memStage, wbStage, instruction, cycle, i);
      passLabel = true;
      register1 = noDependecy;
    }
    else if (operation.compare("lw") == 0 && passLabel == false){
      found = rest.find_first_of(",");
      register2 = rest.substr(0, found);
      rest = rest.substr(found+2);
      found = rest.find_first_of("(");
      rest = rest.substr(found+1);
      register3 = rest.substr(0, rest.size() - 1);
      cycle = dependecy (cycle, dependecyRegisters, register2, register3);
      reallocateInstruction(ifStage, idStage, exStage, memStage, wbStage, instruction, cycle, i);
      register1 = register2;
    }
    else if (operation.compare("sw") == 0 && passLabel == false){
      found = rest.find_first_of(",");
      register2 = rest.substr(0, found);
      rest = rest.substr(found+2);
      found = rest.find_first_of("(");
      rest = rest.substr(found+1);
      register3 = rest.substr(0, rest.size() - 1);
      cycle = dependecy (cycle, dependecyRegisters, register2, register3);
      reallocateInstruction(ifStage, idStage, exStage, memStage, wbStage, instruction, cycle, i);
      register1 = noDependecy;
    }
    else if (operation.compare("j") == 0 && passLabel == false){
      label = rest;
      if (cycle != 0) cycle++;
      reallocateInstruction(ifStage, idStage, exStage, memStage, wbStage, instruction, cycle, i);
      passLabel = true;
      register1 = noDependecy;
    }
  changeDependecy(dependecyRegisters, register1);
  }
  cycle = cycle - sizeCase + 5;
}
/* Função que irá printar na tela a cada estágio as instruções em execução. */
void stages(std::vector <std::string> ifStage,
            std::vector <std::string> idStage,
            std::vector <std::string> exStage,
            std::vector <std::string> memStage,
            std::vector <std::string> wbStage,
            int cycle) {
  std::cout << "Quantidade de ciclos total: " <<  cycle << std::endl;
	std::cout << std::endl << "-------------------------------------------------------" << std::endl;
	for(int i = 0; i < cycle; i++){
		std::cout << "Ciclo " << (i + 1) << std::endl;
		std::cout << "IF:" << "\t" << ifStage[i] << std::endl;
		std::cout << "ID:" << "\t" << idStage[i] << std::endl;
		std::cout << "EX:" << "\t" << exStage[i] << std::endl;
		std::cout << "MEM:" << "\t" << memStage[i] << std::endl;
		std::cout << "WB:" << "\t" <<  wbStage[i]<< std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
	}
}
