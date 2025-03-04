#ifndef JOYSTICK_H
#define JOYSTICK_H

int joystick_init();
void joystick_read(int *x, int *y);
void process_joystick_data();

#endif // JOYSTICK_H