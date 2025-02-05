#include <xinu.h>
#include <stdlib.h>
#include "globals.h"

int humidity = 0;

int humidity_sensor() {
    while (1) {
        humidity = (rand() % 40) + 40;
	signal(sem);        
	sleepms(5000);
    }
    return OK;
}
