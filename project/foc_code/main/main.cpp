/**
 * @file app_main.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "main.h"

#include "u_led.h"

#include "u_adc.h"

#include "u_i2c.h"
#include "u_pwm.h"

#include "AS5600.h"

/*任务句柄定义*/
TaskHandle_t AS5600_Test_Handle;
TaskHandle_t LED_Test_Handle;
/*任务句柄定义*/

/**
 * @brief 初始化
 *
 */
static void All_init(void)
{
    /*驱动初始化*/
    led_init();
    adc_init();
    I2C1_init();
    Pwm_init();
    /*驱动初始化*/
    /*传感器初始化*/
    AS5600_init();
    /*传感器初始化*/
    /*设备初始化*/
    //    foc_init();
    /*设备初始化*/
}

extern "C" void app_main(void)
{
    static char InfoBuffer[512] = {0};
    printf("Hi !\n");
    All_init();
    xTaskCreate(&Led_Task, "Led_Task", 512, NULL, Priority_LED, &LED_Test_Handle);
    xTaskCreate(&AS5600_Task, "AS5600_Task", 1024, NULL, Priority_AS5600, &AS5600_Test_Handle);
    mypwm.Set_duty(mypwm.IN1_channel, 0.5);
    mypwm.Set_duty(mypwm.IN2_channel, 0.25);
    mypwm.Set_duty(mypwm.IN3_channel, 0.75);
    while (1)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        sprintf(InfoBuffer, "AS5600 Angel=%.4f", my_as5600.Raw_angel);
        MY_DEBUG("%s", InfoBuffer);
        // sprintf(InfoBuffer, "ADC 1 =%.4f", myadc.Get_adc1());
        // MY_DEBUG("%s", InfoBuffer);
        // sprintf(InfoBuffer, "ADC 2 =%.4f", myadc.Get_adc2());
        // MY_DEBUG("%s", InfoBuffer);
    }
}
