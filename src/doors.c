#include <stdlib.h>
#include <stdio.h>
#include "../include/libgpio.h"

void setup_doors()
{
    exportGPIO("4");
    exportGPIO("17");
    exportGPIO("27");
    exportGPIO("22");
    pinMode("4", "in");
    pinMode("17", "in");
    pinMode("27", "in");
    pinMode("22", "in");
}

void close_doors()
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