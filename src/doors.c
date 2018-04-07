#include <stdlib.h>
#include <stdio.h>

int doors[] = {0, 0, 0, 0};

int door_status(int door_num)
{
    switch (door_num)
    {
    case 1:
        return doors[0];
    case 2:
        return doors[1];
    case 3:
        return doors[2];
    case 4:
        return doors[3];
    case 5:
        return doors[4];
    }
}