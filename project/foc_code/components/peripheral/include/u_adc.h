#ifndef U_ADC_H
#define U_ADC_H

#include "main.h"

typedef struct u_adc
{
  /**
   * @brief 获取ADC的值
   *
   * @return int
   */
  float (*Get_adc1)(void);
  /**
   * @brief 获取ADC的值
   *
   * @return int
   */
  float (*Get_adc2)(void);

} _U_ADC;

extern _U_ADC myadc;

void adc_init(void);

#endif /* U_ADC_H */
