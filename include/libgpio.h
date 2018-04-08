#ifndef LIBGPIO_H
#define _LIBGPIO_H

void exportGPIO(char *);
void unexportGPIO(char *);
void pinMode(char *pin, char *MODE);
void digitalWrite(char *pin, char *value);
int digitalRead(char *pin);
void blink(char *pin, int freq, int duration);

#endif