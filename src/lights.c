#include <stdlib.h>
#include <stdio.h>
#include "../include/libgpio.h"

int lights[] = {0, 0, 0, 0, 0};

void setup_lights()
{
    exportGPIO("5");
    exportGPIO("6");
    exportGPIO("13");
    exportGPIO("19");
    exportGPIO("26");
    pinMode("5", "OUT");
    pinMode("6", "OUT");
    pinMode("13", "OUT");
    pinMode("19", "OUT");
    pinMode("26", "OUT");
}

void close_lights()
{
    unexportGPIO("5");
    unexportGPIO("5");
    unexportGPIO("13");
    unexportGPIO("17");
    unexportGPIO("26");
}

int light_on(int light_num)
{
    switch (light_num)
    {
    case 1:
        digitalWrite("5", "1");
        return 0;
    case 2:
        digitalWrite("6", "1");
        return 0;
    case 3:
        digitalWrite("13", "1");
        return 0;
    case 4:
        digitalWrite("19", "1");
        return 0;
    case 5:
        digitalWrite("26", "1");
        return 0;
    }
}

int light_off(int light_num)
{
    switch (light_num)
    {
    case 1:
        digitalWrite("5", "0");
        return 0;
    case 2:
        digitalWrite("6", "0");
        return 0;
    case 3:
        digitalWrite("13", "0");
        return 0;
    case 4:
        digitalWrite("19", "0");
        return 0;
    case 5:
        digitalWrite("26", "0");
        return 0;
    }
}

int light_status(int light_num)
{
    switch (light_num)
    {
    case 1:
        return digitalRead("5");
    case 2:
        return digitalRead("6");
    case 3:
        return digitalRead("13");
    case 4:
        return digitalRead("19");
    case 5:
        return digitalRead("26");
    }
}