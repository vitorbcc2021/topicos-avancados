/*  main.c  - main */

#include <xinu.h>

#define N 5  /* Número de filósofos */
#define PENSANDO 0
#define FOME 1
#define COMENDO 2

/* Semáforos para os garfos */
sid32 garfo[N];

/* Semáforo para exclusão mútua */
sid32 mutex;

/* Estado dos filósofos */
int estado[N];

/* Função para pegar os garfos */
void pegar_garfos(int filosofo);
/* Função para devolver os garfos */
void devolver_garfos(int filosofo);
/* Função para testar se o filósofo pode comer */
void testar(int filosofo);
/* Função para pensar */
void pensar(int filosofo);
/* Função para comer */
void comer(int filosofo);
/* Função do processo de filósofo */
process filosofo_proc(int id);

/* Função principal */
process	main(void) {
	pid32 shpid; /* Shell process ID */
	int i;

	printf("\n\n");

	/* Inicializar o sistema de arquivos local */
	lfscreate(RAM0, 40, 20480);

	/* Inicializar mutex e semáforos dos garfos */
	mutex = semcreate(1);
	for (i = 0; i < N; i++) {
		garfo[i] = semcreate(1);
		estado[i] = PENSANDO;
	}

	/* Criar processos para cada filósofo */
	for (i = 0; i < N; i++) {
		resume(create(filosofo_proc, 1024, 20, "filosofo_proc", 1, i));
	}

	/* Executar o shell do Xinu */
	recvclr();
	resume(shpid = create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Aguardar shell encerrar e recriá-lo */
	while (TRUE) {
		if (receive() == shpid) {
			sleepms(200);
			kprintf("\n\nMain process recreating shell\n\n");
			resume(shpid = create(shell, 4096, 20, "shell", 1, CONSOLE));
		}
	}

	return OK;
}

/* Função para pegar os garfos */
void pegar_garfos(int filosofo) {
	wait(mutex);  /* Exclusão mútua */

	estado[filosofo] = FOME;
	testar(filosofo);

	signal(mutex);  /* Liberar exclusão mútua */
	wait(garfo[filosofo]);  /* Bloquear se os garfos não estiverem disponíveis */
}

/* Função para devolver os garfos */
void devolver_garfos(int filosofo) {
	wait(mutex);  /* Exclusão mútua */

	estado[filosofo] = PENSANDO;
	testar((filosofo + N - 1) % N);  /* Testar filósofo à esquerda */
	testar((filosofo + 1) % N);      /* Testar filósofo à direita */

	signal(mutex);  /* Liberar exclusão mútua */
}

/* Testa se o filósofo pode comer */
void testar(int filosofo) {
	if (estado[filosofo] == FOME &&
		estado[(filosofo + N - 1) % N] != COMENDO &&
		estado[(filosofo + 1) % N] != COMENDO) {

		estado[filosofo] = COMENDO;
		signal(garfo[filosofo]);
	}
}

/* Função para pensar */
void pensar(int filosofo) {
	kprintf("Filosofo %d está pensando\n", filosofo);
	sleepms(1000 + (rand() % 3000));  /* Pensar por um tempo aleatório */
}

/* Função para comer */
void comer(int filosofo) {
	kprintf("Filosofo %d está comendo\n", filosofo);
	sleepms(1000 + (rand() % 2000));  /* Comer por um tempo aleatório */
}

/* Função do processo de filósofo */
process filosofo_proc(int id) {
	while (TRUE) {
		pensar(id);
		pegar_garfos(id);
		comer(id);
		devolver_garfos(id);
	}
	return OK;
}
