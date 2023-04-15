#ifndef U_LED_H
#define U_LED_H

#include "main.h"

typedef struct u_led
{
  /* data */
  void (*set_Led)(float value);
} _U_LED;

extern _U_LED myled;

void led_init(void);
void Led_Task(void *pvParameters);
#endif /* U_LED_H */
