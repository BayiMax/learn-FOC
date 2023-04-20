#ifndef U_LED_H
#define U_LED_H

#include "main.h"

typedef struct u_led {
    /* data */
    void (*set_Led)(float value);
} U_LED;

extern U_LED myled;

void led_init();

void Led_thread();

#endif /* U_LED_H */
