#include <xinu.h>
#include <stdio.h>
#include <stdbool.h>
#include "globals.h"

int ventilator_control() {
    while (1) {
        if (ventilator_command) {
            kprintf("Ventilador: Ligado\n");
        } else {
            kprintf("Ventilador: Desligado\n");
        }
        sleepms(7000);
    }
    return OK;
}
