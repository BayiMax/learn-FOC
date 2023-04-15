#ifndef U_PWM_H
#define U_PWM_H

#include "main.h"

typedef struct U_PWM
{

  const ledc_channel_t IN1_channel;
  const ledc_channel_t IN2_channel;
  const ledc_channel_t IN3_channel;

  void (*Out)(void);
  /**
   * @brief 设置输出占空比
   *
   * @param duty 占空比值
   */
  void (*Set_duty)(const ledc_channel_t channel, float duty);

  // /**
  //  * @brief
  //  *
  //  */
  // void (*stop)(void);
} _U_PWM;

extern _U_PWM mypwm;

/**
 * @brief pwm初始化
 *
 */
void Pwm_init(void);

#endif /* U_PWM_H */
