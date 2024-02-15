// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>

class Process{ //classe que implementa a estrutura de um Process
private:
    int id {}; //guarda um inteiro que identifica um processo específico
    int instante {}; //guarda o instante em que o processo deve entrar no sistema
    int demCPU {}; //guarda a demanda do processo pela CPU no sistema
    int demDisk {}; //guarda a demanda do processo pelo Disco no sistema
    int demRede {}; //guarda a demanda do processo pela Rede no sistema
    int demanda {}; //guarda a demanda do recurso em que o processo ira entrar na fila
    int instanteCom {}; //guarda o instante em que o processo entrou em determinada fila
public:    
    //construtor que cria um processo vazio
    Process(){}
    //construtor que cria um processo de acordo com os parametros passados
    Process(int inst, int cpu, int disk, int rede, int& nextId){
        instante = inst;
        demCPU = cpu;
        demDisk = disk;
        demRede = rede;
        id = nextId++;
    }

    int getInst(){ //função que retorna o instante do processo
        return instante;
    }
    int getDemCPU(){ //função que retorna a demanda do processo por CPU
        return demCPU;
    }
    int getDemDisk(){ //função que retorna a demanda do processo por Disco
        return demDisk;
    }
    int getDemRede(){ //função que retorna a demanda do processo por Rede
        return demRede;
    }
    int getId(){ //função que retorna o identificador do processo
        return id;
    }
    int getDemanda(){ //função que retorna o identificador do processo
        return demanda;
    }
    int getInstCom(){ //função que retorna o identificador do processo
        return instanteCom;
    }

    void setDemanda(int dem){ //função que altera a demanda do processo de quando ele entrou em uma fila
        demanda = dem;
    }
    void setInstCom(int com){ //função que altera o instante do processo de quando ele entrou em uma fila
        instanteCom = com;
    }
    //sobrecarga do operador maior que (que compara duas demandas)
    bool operator>(const Process& other){ 
        return demanda > other.demanda;
    }
    //sobrecarga do operador menor que (que compara duas demandas)
    bool operator<(const Process& other){
        return demanda < other.demanda;
    }

    //declaração da função de sobrecarga do operador <<
    friend std::ostream& operator<< (std::ostream& stream, const Process& p);
};

//função de sobrecarga do operador menor que, menor que(<<)
std::ostream& operator<< (std::ostream& stream, const Process& p){
    stream << p.id << ": " << p.instante << " " << p.demCPU << " " << p.demDisk << " " << p.demRede;
    return stream;
}

#endif