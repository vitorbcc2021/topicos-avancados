#include <xinu.h>
#include <stdio.h>
#include <stdbool.h>
#include "globals.h"

int exhauster_control() {
    while (1) {
        if (exhauster_command) {
            kprintf("Exaustor: Ligado\n");
        } else {
            kprintf("Exaustor: Desligado\n");
        }
        sleepms(7000);
    }
    return OK;
}
