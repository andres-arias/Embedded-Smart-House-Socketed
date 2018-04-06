#include <stdlib.h>
#include <stdio.h>

int lights[] = {0, 0, 0, 0, 0};

int light_on(int light_num)
{
    switch (light_num)
    {
    case 1:
        puts("Light 1 on");
        lights[0] = 1;
        return 0;
    case 2:
        puts("Light 2 on");
        lights[1] = 1;
        return 0;
    case 3:
        puts("Light 3 on");
        lights[2] = 1;
        return 0;
    case 4:
        puts("Light 4 on");
        lights[3] = 1;
        return 0;
    case 5:
        puts("Light 5 on");
        lights[4] = 1;
        return 0;
    }
}

int light_off(int light_num)
{
    switch (light_num)
    {
    case 1:
        puts("Light 1 off");
        lights[0] = 0;
        return 0;
    case 2:
        puts("Light 2 off");
        lights[1] = 0;
        return 0;
    case 3:
        puts("Light 3 off");
        lights[2] = 0;
        return 0;
    case 4:
        puts("Light 4 off");
        lights[3] = 0;
        return 0;
    case 5:
        puts("Light 5 off");
        lights[4] = 0;
        return 0;
    }
}

int light_status(int light_num)
{
    switch (light_num)
    {
    case 1:
        return lights[0];
    case 2:
        return lights[1];
    case 3:
        return lights[2];
    case 4:
        return lights[3];
    case 5:
        return lights[4];
    }
}