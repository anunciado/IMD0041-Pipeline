#ifndef __PIPELINE_H__
#define __PIPELINE_H__

void fill (std::vector <std::string> &inputString);
void changeDependecy(std::vector <std::string> &dependecyRegisters,
                     const std::string &newRegister);
int dependecy (const int &cycle,
               const std::vector <std::string> &dependecyRegisters,
               const std::string &register2,
               const std::string &register3,
               const std::string &registerAux);
void reallocateInstruction (std::vector <std::string> &ifStage,
                            std::vector <std::string> &idStage,
                            std::vector <std::string> &exStage,
                            std::vector <std::string> &memStage,
                            std::vector <std::string> &wbStage,
                            const std::string instruction,
                            const int &cycle, const int &i);
void pipeline (std::vector <std::string> &ifStage,
               std::vector <std::string> &idStage,
               std::vector <std::string> &exStage,
               std::vector <std::string> &memStage,
               std::vector <std::string> &wbStage,
               std::vector <std::string> inputString,
               int &cycle);
void stages (std::vector <std::string> ifStage,
            std::vector <std::string> idStage,
            std::vector <std::string> exStage,
            std::vector <std::string> memStage,
            std::vector <std::string> wbStage,
            int cycle);

#endif /* __PIPELINE_H__ */
