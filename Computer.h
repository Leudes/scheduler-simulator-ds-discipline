// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#ifndef COMP_H
#define COMP_H
#include "Process.h" // usada para ter acesso ao Process
#include "Rede.h" //usada para ter acesso a Rede

template <typename Type> 
class Computer{ //classe que implementa o funcionamento de cada computador do sistema
private:
    Process* CPU {}; //guarda o processo que está executando atualmente na CPU
    Process* Disk1 {}; //guarda o processo que está executando atualmente no Disco 1
    Process* Disk2 {}; //guarda o processo que está executando atualmente na Disco 2
    Type listaCPU {}; //lista que guarda os processos que estão na fila de espera da CPU
    Type listaDisk1 {}; //lista que guarda os processos que estão na fila de espera do Disco 1
    Type listaDisk2 {}; //lista que guarda os processos que estão na fila de espera do Disco 2
    bool ativo {}; //guarda o estado atual do computador
    
public:
    Computer(){ //construtor que cria um computador vazio
        CPU = nullptr;
        Disk1 = nullptr;
        Disk2 = nullptr;
        ativo = false;
    }
    
    Process* getCPU(){ //retorna o estado atual da CPU
        return CPU;
    }
    Process*& getDisk1(){ //retorna o estado atual do disco 1
        return Disk1;
    }
    Process*& getDisk2(){ //retorna o estado atual do disco 2
        return Disk2;
    }
    Type& getListaCPU(){ //retorna uma referencia para ListaCPU
        return listaCPU;
    }
    Type& getListaDisk1(){ //retorna uma referencia para ListaDisco1
        return listaDisk1;
    }
    Type& getListaDisk2(){ //retorna uma referencia para ListaDisco2
        return listaDisk2;
    }
    bool getAtivo(){ //retorna se o computador sendo usado naquele instante
        return ativo;
    }

    void setCPU(Process* p){ //altera o estado atual da CPU
        CPU = p;
    }
    void setDisk1(Process* p){ //altera o estado atual do Disco1
        Disk1 = p;
    }
    void setDisk2(Process* p){ //altera o estado atual do Disco2
        Disk2 = p;
    }
    void setAtivo(bool a){  //altera o estado de uso do computador
        ativo = a;
    }
    //confere se o computador continua ativo, caso contrario desativa
    void confereAtivo(){
        if(listaCPU.empty() && listaDisk1.empty() && listaDisk2.empty() && CPU == nullptr && Disk1 == nullptr && Disk2 == nullptr){
            ativo = false;
        }
    }
    //confere o estado da CPU
    void conferirCPU(unsigned long int& somaEspera, unsigned long int& somaExecucao, unsigned long int& tempoGeral){
        if(CPU != nullptr && (CPU->getDemanda() == 1 || CPU->getDemanda() == 0)){
            int numDisk = rand() % 2 + 1;
            Process* auxCpu = CPU;
            CPU = nullptr;
            auxCpu->setDemanda(auxCpu->getDemDisk());
            auxCpu->setInstCom(tempoGeral);
            if(numDisk == 1){
                listaDisk1.push(*auxCpu);
            }else{
                listaDisk2.push(*auxCpu);
            }
            delete auxCpu;
            if(!listaCPU.empty()){
                Process* auxCPU = new Process(listaCPU.front());
                CPU = auxCPU; //a CPU recebe o primeiro processo da lista de espera da CPU
                listaCPU.pop();
                somaEspera += tempoGeral - CPU->getInstCom();
                somaExecucao += CPU->getDemanda(); 
            }
        }else if(CPU != nullptr){ //se houver um processo na CPU e sua demanda for maior que zero
            CPU->setDemanda(CPU->getDemanda() - 1); //diminui uma unidade de demanda
        }else if(!listaCPU.empty()){ //se não existir processo na CPU, mas houver processos na sua fila de espera
            //preciso alocar um novo espaço de memoria pra ele se não quando eu der pop vai sumir
            Process* auxCPU = new Process(listaCPU.front());
            CPU = auxCPU; //a CPU recebe o primeiro processo da lista de espera da CPU
            listaCPU.pop();
            somaEspera += tempoGeral - CPU->getInstCom();
            somaExecucao += CPU->getDemanda(); 
        }
    }
    //confere o estado do Disco 1 ou 2
    void conferirDisk(unsigned long int& somaEspera, unsigned long int& somaExecucao, unsigned long int& tempoGeral, Rede<Type>& rede, Process*& disk, Type& listadisk){
        if(disk != nullptr && (disk->getDemanda() == 1 || disk->getDemanda() == 0)){ //se tiver algum processo no disco1 e sua demanda for zero
            Process* auxdisk = disk;
            disk = nullptr;
            auxdisk->setDemanda(auxdisk->getDemRede());
            auxdisk->setInstCom(tempoGeral);
            rede.getListaRede().push(*auxdisk);
            delete auxdisk;
            if(!listadisk.empty()){ //se não existir processo no disco1, mas houver processos na sua fila de espera
                Process* auxdisk = new Process(listadisk.front());
                disk = auxdisk; //o disco1 recebe o primeiro processo da lista de espera do disco1
                listadisk.pop(); //remove o processo, que acabou de ser inserido no disco1, da lista do disco1
                somaEspera += tempoGeral - disk->getInstCom();
                somaExecucao += disk->getDemanda();
            }
            confereAtivo();
        }else if(disk != nullptr){ //se tiver algum processo no disco1 e sua demanda for maior que zero
            disk->setDemanda(disk->getDemanda() - 1); //diminui uma unidade de demanda
        }else if(!listadisk.empty()){ //se não existir processo no disco1, mas houver processos na sua fila de espera
            Process* auxdisk = new Process(listadisk.front());
            disk = auxdisk; //o disco1 recebe o primeiro processo da lista de espera do disco1
            listadisk.pop(); //remove o processo, que acabou de ser inserido no disco1, da lista do disco1
            somaEspera += tempoGeral - disk->getInstCom();
            somaExecucao += disk->getDemanda();
        }
    }
    //printa a demanda atual da cpu ou de um dos discos
    void print(Process* p, std::string s, int saida, int i){
        if(saida == 1){
            if(p != nullptr){
                std::cout << i << ": "<< s <<" ID: " << p->getId() << ": "<< s <<" dem: " << p->getDemanda() << "\n";
            }
        }
    }
};

#endif