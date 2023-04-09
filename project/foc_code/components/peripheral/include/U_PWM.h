#ifndef U_PWM_H
#define U_PWM_H

#include "main.h"

typedef struct U_PWM
{

  void (*Out)(void);
  /**
   * @brief 设置输出占空比
   *
   * @param duty 占空比值
   */
  void (*Set_duty)(uint32_t duty);
} _U_PWM;

_U_PWM mypwm;

#endif /* U_PWM_H */
