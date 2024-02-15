// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#ifndef REDE_H
#define REDE_H
#include "Process.h" //usado para utilizar a classe Process
#include "Queue.h" //usado para utilizar a classe Queue
#include "OrderedList.h" //usado para utilizar a classe OrderedList

template <typename Type>
class Rede{ //classe que implementa a lógica da rede geral do sistema distribuído
private:
    Type listaRede {}; //guarda os processos que estão na fila de espera da rede
    Process* rede {}; //guarda o processo que está executando atualmente na rede
public:
    Rede(){} //construtor que cria uma rede vazia

    Type& getListaRede(){ //retorna uma referencia para filaRede
        return listaRede;
    }
    Process* getRede(){ //retorna o estado atual da rede
        return rede;
    }

    void setRede(Process* r){ //altera o estado atual da rede
        rede = r;
    }
    //confere o estado da Rede
    void conferirRede(unsigned long int& somaEspera, unsigned long int& somaExecucao, unsigned long int& tempoGeral, int& qntConcluidoProcess ){
        if(rede != nullptr && (rede->getDemanda() == 1 || rede->getDemanda() == 0)){
            Process* auxRede = rede;
            rede = nullptr;
            delete auxRede;
            qntConcluidoProcess++;
            if(!listaRede.empty()){
                Process* auxRede = new Process(listaRede.front());
                rede = auxRede;
                listaRede.pop();
                somaEspera += tempoGeral - rede->getInstCom();
                somaExecucao += rede->getDemanda();
            }    
        }else if(rede != nullptr){
            rede->setDemanda(rede->getDemanda() - 1);
        }else if(!listaRede.empty()){
            Process* auxRede = new Process(listaRede.front());
            rede = auxRede;
            listaRede.pop();
            somaEspera += tempoGeral - rede->getInstCom();
            somaExecucao += rede->getDemanda();
        }
    }
    //printa a demanda da Rede
    void print(int& saida){
        if(saida == 1){
            if(rede != nullptr){
                std::cout << "REDE ID: " << rede->getId() << ": REDE dem: " << rede->getDemanda() << "\n";
            }
        }
    }
};

#endif