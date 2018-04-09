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
    pinMode("5", "out");
    pinMode("6", "out");
    pinMode("13", "out");
    pinMode("19", "out");
    pinMode("26", "out");
}

void close_lights()
{
    unexportGPIO("5");
    unexportGPIO("6");
    unexportGPIO("13");
    unexportGPIO("17");
    unexportGPIO("26");
}

void light_on(int light_num)
{
    switch (light_num)
    {
    case 1:
        digitalWrite("5", "1");
        break;
    case 2:
        digitalWrite("6", "1");
        break;
    case 3:
        digitalWrite("13", "1");
        break;
    case 4:
        digitalWrite("19", "1");
        break;
    case 5:
        digitalWrite("26", "1");
        break;
    }
}

void light_off(int light_num)
{
    switch (light_num)
    {
    case 1:
        digitalWrite("5", "0");
        break;
    case 2:
        digitalWrite("6", "0");
        break;
    case 3:
        digitalWrite("13", "0");
        break;
    case 4:
        digitalWrite("19", "0");
        break;
    case 5:
        digitalWrite("26", "0");
        break;
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