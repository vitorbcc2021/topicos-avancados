#include <xinu.h>
#include <stdlib.h>
#include "globals.h"

int temperature = 0;

int temperature_sensor() {
    while (1) {
        temperature = (rand() % 20) + 15;
	signal(sem);        
	sleepms(5000);
    }
    return OK;
}
