#include <xinu.h>
#include <stdio.h>
#include <stdbool.h>
#include "globals.h"
#include "uv_light.h"

bool ventilator_command = false;
bool exhauster_command = false;

int hub_control() {
    int uv_thread = create(uv_light_control, 4096, 10, "Luz UV", 1, true);
    resume(uv_thread);

    while (1) {
        wait(sem);

        kprintf("Leitura: Temperatura = %d°C, Umidade = %d%%\n", temperature, humidity);

        if (temperature > 30) {
            if (!ventilator_command) {
                ventilator_command = true;
            }
        } else if (temperature <= 25) {
            if (ventilator_command) {
                ventilator_command = false;
            }
        }

        if (humidity > 70) {
            if (!exhauster_command) {
                exhauster_command = true;
            }
        } else if (humidity <= 60) {
            if (exhauster_command) {
                exhauster_command = false;
            }
        }

        signal(sem);
        sleepms(5000);
    }
    return OK;
}
