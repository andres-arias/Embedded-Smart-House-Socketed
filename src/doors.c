#include <stdlib.h>
#include <stdio.h>
#include "../include/libgpio.h"

void setup_lights()
{
    exportGPIO("4");
    exportGPIO("17");
    exportGPIO("27");
    exportGPIO("22");
    pinMode("4", "IN");
    pinMode("17", "IN");
    pinMode("27", "IN");
    pinMode("22", "IN");
}

void close_lights()
{
    unexportGPIO("4");
    unexportGPIO("17");
    unexportGPIO("27");
    unexportGPIO("22");
}

int door_status(int door_num)
{
    switch (door_num)
    {
    case 1:
        return digitalRead("4");
    case 2:
        return digitalRead("17");
    case 3:
        return digitalRead("27");
    case 4:
        return digitalRead("22");
    }
}