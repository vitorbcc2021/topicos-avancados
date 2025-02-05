#include <xinu.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int tempo;
    int potencia;
    char tipoPrato[20];
    bool portaAberta;
    bool luzLigada;
    bool ventilacao;
    bool pratoGirando;
} Microondas;

Microondas microondas;

void inicializarMicroondas() {
    microondas.tempo = 0;
    microondas.potencia = 0;
    strcpy(microondas.tipoPrato, "Desconhecido");
    microondas.portaAberta = false;
    microondas.luzLigada = false;
    microondas.ventilacao = false;
    microondas.pratoGirando = false;
}

void especificarCiclo(int tempo, int potencia) {
    microondas.tempo = tempo;
    microondas.potencia = potencia;
    printf("Ciclo especificado: Tempo = %d segundos, Potência = %d%%\n", tempo, potencia);
}

void controlarKlystron() {
    if (microondas.portaAberta) {
        printf("Porta aberta! Cancelando ciclo.\n");
        return;
    }
    printf("Iniciando aquecimento com potência de %d%% por %d segundos.\n", microondas.potencia, microondas.tempo);
    sleep(microondas.tempo);
    printf("Aquecimento concluído.\n");
}

void programaCozimento(char *prato) {
    if (strcmp(prato, "Carne") == 0) {
        especificarCiclo(300, 80);
    } else if (strcmp(prato, "Peixe") == 0) {
        especificarCiclo(200, 70);
    } else if (strcmp(prato, "Frango") == 0) {
        especificarCiclo(250, 75);
    } else if (strcmp(prato, "Lasanha") == 0) {
        especificarCiclo(400, 90);
    } else if (strcmp(prato, "Pipoca") == 0) {
        especificarCiclo(120, 100);
    } else {
        printf("Programa de cozimento desconhecido.\n");
        return;
    }
    strcpy(microondas.tipoPrato, prato);
    controlarKlystron();
}

void bip() {
    printf("Bip! Aquecimento concluído.\n");
}

void emergencia() {
    printf("Emergência! Porta aberta ou cancelamento manual.\n");
    microondas.portaAberta = true;
}

void refrigeracao() {
    printf("Iniciando resfriamento...\n");
    microondas.ventilacao = true;
    sleep(10);
    microondas.ventilacao = false;
    printf("Resfriamento concluído.\n");
}

void tracaoPrato(bool girar) {
    microondas.pratoGirando = girar;
    if (girar) {
        printf("Prato girando...\n");
    } else {
        printf("Prato parado.\n");
    }
}

void controlarLuz(bool ligar) {
    microondas.luzLigada = ligar;
    if (ligar) {
        printf("Luz interna ligada.\n");
    } else {
        printf("Luz interna desligada.\n");
    }
}

void relogioCortesia() {
    time_t agora;
    agora = time(NULL);
    printf("Hora atual: %s", ctime(&agora));
}

process main() {
    inicializarMicroondas();
    printf("Sistema de Microondas Iniciado.\n");

    controlarLuz(true);
    tracaoPrato(true);
    programaCozimento("Pipoca");
    bip();
    refrigeracao();
    controlarLuz(false);
    tracaoPrato(false);
    relogioCortesia();

    return OK;
}
