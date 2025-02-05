#include <xinu.h>
#include <stdio.h>
#include <stdbool.h>
#include "uv_light.h"
#include "globals.h"

void uv_light_control(bool initial_state) {
    bool uv_light = initial_state;

    while (1) {
        wait(sem);

        if (uv_light) {
            kprintf("Luz UV: Ligada\n");
        } else {
            kprintf("Luz UV: Desligada\n");
        }

        uv_light = !uv_light;
        signal(sem);
        sleepms(12000);
    }
}
