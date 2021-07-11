//inputs e outputs
#include <stdio.h> 
//malloc
#include <stdlib.h> 
//medir o tempo de execução 
#include <time.h>
//Utilizar threads
#include <pthread.h> 
//declaração da função chamada por cada thread para gerar pontos
void *gerarpontos(void *pontosT);
//Função main - por onde o programa inicia
int main(int argc, char* argv[]) { 	
	//numero de threads a serem utilizadas
	int nThreads;
	//pontos totais, pontos a gerar por thread, resultado Thread final, pontos dentro do circulo
	long int pontos, pontosT, resultadoTF,pontosC = 0;
	//tempo final total
	double tempoFT;
	//resultado por thread
	void *resultadoT;
	//Struct com um conjunto de variáveis que servirão para registar tempo de execução de programa
	struct timespec inicioT, fimT;
  	
	system("clear");
	printf("\n");
	printf("Simulação de Monte Carlo para cálculo aproximado do valor de 𝛑 (Pi)\n\n");
	printf ("Introduza quantos pontos pretende gerar para calcular 𝛑 (Pi): ");
	//input de dados (numero de pontos)
	scanf ("%ld",&pontos);

	printf ("Introduza o número de threads a criar: ");
	//input de dados (numero de threads)
	scanf ("%d",&nThreads);

	//registo de tempo inicial programa
	clock_gettime(CLOCK_MONOTONIC, &inicioT);
	
	//pontos a gerar por thread
	pontosT = pontos / nThreads;
	
	//contador de threads
	int id = 0;
	
	//array para receber threads criadas
	pthread_t tid[nThreads];

	system("clear");
	printf("\n\nCálculo iniciado:\n");
	printf("Estão a ser gerados %ld pontos aleatórios, por favor aguarde...\n\n", pontos);
	
	//Ciclo para criar as Threads com base no numero de threads e por cada thread é chamada a função gerarpontos, passando o numero de pontos a gerar por cada thread (pontoT) do tipo Void
    for (;i i < nThreads; i++) {
    	id++;   
        pthread_create(&tid[i], NULL, gerarpontos,(void *)pontosT); 
		printf("%dª Thread criada, com numero ID: %ld \n", id, tid[i]);
		}
	
	//Ciclo para que cada thread criada, as mesmas esperem por todas terminarem a execução e utilizar o resultado de cada thread para incremento dos pontos gerados dentro do circulo
	printf("\n");
	
	for (i=0; i < nThreads; i++){
		pthread_join(tid[i], (void **)&resultadoT);
		resultadoTF = (long int)resultadoT;
		pontosC = pontosC + resultadoTF;
		} 

	//Após todas as threads terminarem segue-se a mensagem que informa do total de pontos gerados dentro do circulo e calcula-se o valor aprox de pi
	printf("\nNo total foram gerados %ld pontos dentro do círculo.\n", pontosC);    
	long double pi = (long double)pontosC / (long double)pontos * 4.0;
	
	//Output do valor aprox de pi e regista o tempo no final após a operação
	printf("\nValor aproximado de 𝛑 (Pi) = %0.10Lf\n\n", pi);
	clock_gettime(CLOCK_MONOTONIC, &fimT);

	//Calculo do tempo subtraindo ao tempo final o tempo inicialmente registado e conversão para valor com precisão em nanosegundos
	tempoFT = (fimT.tv_sec - inicioT.tv_sec);
	tempoFT += (fimT.tv_nsec - inicioT.tv_nsec) / 1000000000.0;
	
	printf("Terminado - Tempo de execução do programa: %.10f segundos.\n\n", tempoFT);
	//fim do programa e da função main
	return 0;
	}
//Função utilizada por cada thread para gerar pontos
void *gerarpontos(void *pontosT) {

	//Variáveis para o ciclo for com base no numero de pontos já divididos pelo numero de threads (parametro recebido através da função do tipo void e com cast para long int) 
	long int ciclo = (long int)pontosT;
	long int resultadoT, contador;
	
	//alocação de memória para o número de pontos gerados dentro do círculo para evitar falta de memória no Stack alocamos no Heap que tem mais memória
	long int *pontosCT = malloc(sizeof(long int));
	*pontosCT = 0;
	
	//Identificador de cada thread
	pthread_t idThread;  
	idThread = pthread_self();

   	//variáveis para gerar coordenadas X e Y, e variáveis para registo de tempo final/total de cada thread
	double x, y, tempoF;
  	struct timespec inicio, fim;

	//registo do tempo inicial por cada thread e ciclo para gerar pontos aleatórios negativos e positivos com a função rand()
	clock_gettime(CLOCK_MONOTONIC, &inicio);  	
  	for ( contador; contador < ciclo; contador++) { 
		x = (double) rand() / (RAND_MAX / 2) - 1;
        y = (double) rand() / (RAND_MAX / 2) - 1;
        if(x * x + y * y <= 1.0) 
			*pontosCT = *(long int *)pontosCT + 1;
  		}
	
	clock_gettime(CLOCK_MONOTONIC, &fim);//Registo do tempo final
	
	//Calculo do tempo de execução de cada thread subtraindo ao tempo final o tempo inicialmente registado e conversão para valor com precisão em nanosegundos
	tempoF = (fim.tv_sec - inicio.tv_sec);
	tempoF += (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
  	
	//Mensagem com informação de termino da thread e tempo de execução da mesma
  	printf("Thread %ld terminada - Tempo de execução: %.10f segundos\n", idThread, tempoF);
  	
	//cast para long int do apontador da memória com registo de pontos totais gerados dentro do circulo
  	resultadoT = *((long int *)pontosCT);
  	
	//libertação do espaço alocado em memória por cada thread, cast da variável long int para o tipo void *(apontador para void) e fim da thread com o retorno da varialvel
  	free(pontosCT);
	pthread_exit((void *)resultadoT);
	} 
