/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 *
 *
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            佛祖保佑     永不宕机     永无BUG
 */

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

#include "U_I2C.h"

#include "AS5600.h"

/*任务句柄定义*/
TaskHandle_t AS5600_Test_Handle;

/*任务句柄定义*/

/**
 * @brief 初始化
 *
 */
static void All_init(void)
{
    /*驱动初始化*/
    I2C1_init();
    /*驱动初始化*/
    /*传感器初始化*/
    AS5600_init();
    /*传感器初始化*/
    /*设备初始化*/
    foc_init();
    /*设备初始化*/
}

void app_main(void)
{
    static char InfoBuffer[512] = {0};
    printf("Hi !\n");
    All_init();
    xTaskCreate(&AS5600_Task, "AS5600_Task", 1024, NULL, Priority_AS5600, &AS5600_Test_Handle);

    while (1)
    {
        vTaskDelay(10 / portTICK_RATE_MS);
        sprintf(InfoBuffer, "AS5600 Angel=%.4f", my_as5600.Raw_angel);

        MY_DEBUG("%s", InfoBuffer);
    }
}
