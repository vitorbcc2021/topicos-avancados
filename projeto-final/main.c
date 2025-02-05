#include <xinu.h>
#include <stdio.h>

sid32 sem;

extern int temperature_sensor();
extern int humidity_sensor();
extern int ventilator_control();
extern int exhauster_control();
extern int hub_control();

int main() {
    
    sem = semcreate(1);

    resume(create(temperature_sensor, 1024, 20, "Temperature Sensor", 0));
    resume(create(humidity_sensor, 1024, 20, "Humidity Sensor", 0));
    resume(create(ventilator_control, 1024, 20, "Ventilator Control", 0));
    resume(create(exhauster_control, 1024, 20, "Exhauster Control", 0));
    resume(create(hub_control, 1024, 20, "Hub Control", 0));

    while (1) {
        sleepms(10000);
    }
    return OK;
}
