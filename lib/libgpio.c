#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void exportGPIO(char *pin)
{
	char command[50] = "echo ";
	strcat(command, pin);
	strcat(command, " > /sys/class/gpio/export");

	system(command);
}

void unexportGPIO(char *pin)
{
	char command[50] = "echo ";
	strcat(command, pin);
	strcat(command, " > /sys/class/gpio/unexport");
}

void pinMode(char *pin, char *MODE)
{
	char command[50] = "echo ";
	strcat(command, MODE);
	strcat(command, " > /sys/class/gpio/gpio");
	strcat(command, pin);
	strcat(command, "/direction");

	system(command);
}

void digitalWrite(char *pin, char *value)
{
	char command[50] = "echo ";
	strcat(command, value);
	strcat(command, " > /sys/class/gpio/gpio");
	strcat(command, pin);
	strcat(command, "/value");

	system(command);
}

int digitalRead(char *pin)
{
	char command[50] = "cat /sys/class/gpio/gpio";
	char line[10];

	strcat(command, pin);
	strcat(command, "/value");
	FILE *file = popen(command, "r");

	fgets(line, sizeof(line), file);
	fclose(file);
	int read = atoi(line);
	return read;
}

void blink(char *pin, int freq, int duration)
{
	char off[50] = "echo 0 > /sys/class/gpio/gpio";
	char on[50] = "echo 1 > /sys/class/gpio/gpio";

	strcat(off, pin);
	strcat(on, pin);
	strcat(off, "/value");
	strcat(on, "/value");

	int start = 0;

	while (start < duration)
	{
		system(on);
		sleep(freq);
		system(off);
		sleep(freq);
		start += 2 * freq;
	}
}