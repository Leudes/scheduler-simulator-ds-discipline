// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#include <iostream> //usada para
#include <fstream> //usada para ler e criar arquivos
#include <sstream> //usada para ajudar a receber os dados dos processos 
#include <vector> //usada para construir a lista dos computadores
#include "Queue.h" //usada para utilizar a estrutura de dados Queue
#include "OrderedList.h" //usada para utilizar a estrutura de dados OrderedList
#include "Computer.h" //usada para utilizar a classe que implementa o funcionamento de um computador
#include "Rede.h" //usada para utilizar a classe que implementa o funcionamento da rede

using namespace std;

int main(){ 
    srand(123); //seed para geração de números aleatótios
    Queue<Process> processos_arquivo; //fila que guarda os processos a serem lidos
    Queue<Process> processos_andamento; //fila que guarda os processos que estão passando pelo sistema
    Rede<OrderedList<Process>> redeOrdered{}; //rede geral do sistema com lsita ordenada
    Rede<Queue<Process>> redeQueue{}; //rede geral do sistema com fila
    vector<Computer<OrderedList<Process>>> compsOrdered; //vector de computadores com lista ordenada 
    vector<Computer<Queue<Process>>> compsQueue; //vector de computadores com fila
    int politica, saida, nextIdProcess = 0, qntComp = 0;
    double taxaProcessamento = 0, tempoMedioExecucao = 0, tempoMedioEspera = 0;
    int instante1, qntTotalProcess, qntConcluidoProcess = 0;
    unsigned long int somaEspera = 0, somaExecucao = 0, tempoGeral = 0;
    string nomeArquivo;
    cout << "Para calcular o desempenho do sistema, selecione a politica de escalonamento desejada:\n1 - First Come, First Served (FCFS).\n2 - Shortest Job First (SJF).\n";
    cin >> politica;
    cout << "Digite a quantidade de computadores do sistema:\n";
    cin >> qntComp;
    cin.ignore();
    cout << "Digite o nome do arquivo no qual estao os processos:\n";
    getline(cin, nomeArquivo);
    cout << "Selecione o modelo de saida dos dados:\n1 - Acompanhar execucao e estatisticas.\n2 - Apenas estatisticas.\n";
    cin >> saida;
    
    cout << "Executando...\n";
    if(politica == 1){//fifo
        //cria os computadores
        for(int i = 0; i < qntComp; i++){
            Computer<Queue<Process>>* compu = new Computer<Queue<Process>>();
            compsQueue.push_back(*compu);
            delete compu;
        }
    }else{//sjf
        //cria os computadores
        for(int i = 0; i < qntComp; i++){
            Computer<OrderedList<Process>>* compu = new Computer<OrderedList<Process>>();
            compsOrdered.push_back(*compu);
            delete compu;
        }
    }
    //le o arquivo de texto e cria os processos
    ifstream arquivo(nomeArquivo);
    if(arquivo.is_open()){
        while(!arquivo.eof()){
            string line;
            int auxInst, auxCpu, auxDisk, auxRede;
            getline(arquivo, line);
            stringstream ss(line);
            ss >> auxInst >> auxCpu >> auxDisk >> auxRede;
            
            Process p(auxInst, auxCpu, auxDisk, auxRede, nextIdProcess);
            processos_arquivo.push(p);
        }
    arquivo.close();
    }
    //quantidade de processos
    qntTotalProcess = processos_arquivo.size();
    //instante em que o primeiro processo começou a executar
    instante1 = processos_arquivo.front().getInst();
    try{
        while(true){
            //printa o instante atual do processo
            if(saida == 1){
                cout << "Instante: " << tempoGeral << '\n';
            }
            //coloca os porcessos no computador
            if(!processos_arquivo.empty()){
                while(tempoGeral == processos_arquivo.front().getInst()){
                    Process auxPro = processos_arquivo.front();
                    processos_arquivo.pop();
                    auxPro.setDemanda(auxPro.getDemCPU());
                    auxPro.setInstCom(tempoGeral);
                    int numComp = rand()%qntComp;
                    if(politica == 1){
                        compsQueue[numComp].getListaCPU().push(auxPro);
                        compsQueue[numComp].setAtivo(true);
                    }else{
                        compsOrdered[numComp].getListaCPU().push(auxPro);
                        compsOrdered[numComp].setAtivo(true);
                    }
                    if(processos_arquivo.empty()){
                        break;
                    }
                }
            }
            //passa por todos os computadores conferindo os recursos
            for(int i = 0; i < qntComp; i++){
                if(politica == 1){//fifo
                    if(compsQueue[i].getAtivo() == false){
                        continue;
                    }
                    //conferir o estado da CPU:
                    compsQueue[i].conferirCPU(somaEspera, somaExecucao, tempoGeral);
                    //printa a demanda da cpu
                    compsQueue[i].print(compsQueue[i].getCPU(), "CPU", saida, i);
                    //conferir o estado do Disco1:
                    compsQueue[i].conferirDisk(somaEspera, somaExecucao, tempoGeral, redeQueue, compsQueue[i].getDisk1(), compsQueue[i].getListaDisk1());
                    //printa a demanda do disco1
                    compsQueue[i].print(compsQueue[i].getDisk1(), "DISK1", saida, i);
                    //conferir o estado do Disco2:
                    compsQueue[i].conferirDisk(somaEspera, somaExecucao, tempoGeral, redeQueue, compsQueue[i].getDisk2(), compsQueue[i].getListaDisk2());
                    //printa a demanda do disco2
                    compsQueue[i].print(compsQueue[i].getDisk2(), "DISK2", saida, i);
                }else{//sjf
                    if(compsOrdered[i].getAtivo() == false){
                        continue;
                    }
                    //conferir o estado da CPU:
                    compsOrdered[i].conferirCPU(somaEspera, somaExecucao, tempoGeral);
                    //printa a demanda da cpu
                    compsOrdered[i].print(compsOrdered[i].getCPU(), "CPU", saida, i);
                    //conferir o estado do Disco1:
                    compsOrdered[i].conferirDisk(somaEspera, somaExecucao, tempoGeral, redeOrdered, compsOrdered[i].getDisk1(), compsOrdered[i].getListaDisk1());
                    //printa a demanda do disco1
                    compsOrdered[i].print(compsOrdered[i].getDisk1(), "DISK1", saida, i);
                    //conferir o estado do Disco2:
                    compsOrdered[i].conferirDisk(somaEspera, somaExecucao, tempoGeral, redeOrdered, compsOrdered[i].getDisk2(), compsOrdered[i].getListaDisk2());
                    //printa a demanda do disco2
                    compsOrdered[i].print(compsOrdered[i].getDisk2(), "DISK2", saida, i);
                }
            }
            if(politica == 1){//fifo
                //conferir o estado da Rede:
                redeQueue.conferirRede(somaEspera, somaExecucao, tempoGeral, qntConcluidoProcess);
            }else{//sfj
                //conferir o estado da Rede:
                redeOrdered.conferirRede(somaEspera, somaExecucao, tempoGeral, qntConcluidoProcess);
            }
            //printa a demanda da rede
            if (politica == 1){
                redeQueue.print(saida);
            }else{
                redeOrdered.print(saida);
            }
            
            //condição de parada do loop
            if(qntConcluidoProcess == qntTotalProcess){
                //cout << "Acabou\n";
                break;
            }
            tempoGeral++;
        }
        //printa as estatiscas finais do programa
        cout << "Fim da execucao!\n";
        cout << "DADOS ESTATISTICOS:\n";
        cout << "Tempo total: " << tempoGeral << '\n';
        tempoMedioExecucao = (double)(somaEspera+somaExecucao)/(double)qntTotalProcess;
        cout << "Tempo medio de execucao: " << tempoMedioExecucao << '\n';
        tempoMedioEspera =(double) somaEspera/(double)qntTotalProcess;
        cout << "Tempo medio de espera: " << tempoMedioEspera << '\n';
        taxaProcessamento = (double)qntTotalProcess /(double) (tempoGeral - instante1);
        cout << "Taxa de processamento: " << taxaProcessamento << '\n';

        //cria um arquivo de texto e coloca dentro as estatisticas
        ofstream arquivoOut;
        arquivoOut.open("arquivoSaida.txt");
        arquivoOut << "ESTATISTICAS:\n";
        arquivoOut << "Tempo total: " << tempoGeral << '\n';
        arquivoOut << "Tempo médio de execução: " << tempoMedioExecucao << '\n';
        arquivoOut << "Tempo médio de espera: " << tempoMedioEspera << '\n';
        arquivoOut << "Taxa de processamento: " << taxaProcessamento;
        arquivoOut.close(); 
        
        //para o arquivo executavel nao finalizar imediatamente
        char finish;
        cin >> finish;
        return 0;
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
}