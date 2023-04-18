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
 * @file Foc_init.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "foc_init.h"
#include "main.h"

float cosine = 0;
float sine = 0;
/**
 * @brief foc控制结构体
 *
 */
typedef struct foc
{
  float u_d;   // d轴电压
  float u_q;   // q轴电压
  float theta; // 角度

  float u_alpha; // α电压
  float u_beta;  // β电压

  float t_a;
  float t_b;
  float t_c;

  float i_a; // 电流a
  float i_b; // 电流b
  float i_c; // 电流c

  float i_alpha; // α电流
  float i_beta;  // β电流

  float i_d; // d电流
  float i_q; // q电流

  void (*ipark)(void);

  void (*clarke)(void);

  void (*Park)(void);

  void (*svpwm)(void);
} _FOC_CONTROL;

_FOC_CONTROL myfoc;

/**
 * @brief 反park 变换
 *
 */
static void ipark(void)
{
  sine = sin(myfoc.theta);
  cosine = cos(myfoc.theta);
  myfoc.u_alpha = myfoc.u_d * cosine - myfoc.u_q * sine;
  myfoc.u_beta = myfoc.u_q * cosine - myfoc.u_d * sine;
}

/**
 * @brief clarke 变换
 *
 */
static void clarke(void)
{
  myfoc.i_alpha = myfoc.i_a;
  myfoc.i_beta = (myfoc.i_a + 2 * myfoc.i_b) * 0.5773502691896257f;
}

/**
 * @brief park 变换
 *
 */
static void Park(void)
{
  sine = sin(myfoc.theta);
  cosine = cos(myfoc.theta);
  myfoc.i_d = myfoc.i_alpha * cosine + myfoc.i_beta * sine;
  myfoc.i_q = myfoc.i_beta * cosine - myfoc.i_beta * sine;
}

/**
 * @brief svpwm 输出
 *
 */
static void svpwm(void)
{
  const float ts = 1;
  float t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0;

  float k = 0;
  float sum = 0;

  float u1 = myfoc.u_beta;
  float u2 = -0.8660254037844386f * myfoc.u_alpha - myfoc.u_beta * 0.5f;
  float u3 = 0.8660254037844386f * myfoc.u_alpha - myfoc.u_beta * 0.5f;
  // 扇区判断
  unsigned char sector = (u1 > 0.0) + ((u2 > 0.0) << 1) + ((u3 > 0.0) << 1);
  if (sector == 5)
  {
    t4 = u3;
    t6 = u1;
    sum = t4 + t6;
    // 限制电压矢量
    if (sum > ts)
    {
      k = ts / sum;
      t4 = k * t4;
      t6 = k * t6;
    }
    t7 = (ts - t4 - t6) / 2;
    myfoc.t_a = t4 + t6 + t7;
    myfoc.t_b = t6 + t7;
    myfoc.t_c = t7;
  }
  else if (sector == 1)
  {
    t2 = -u3;
    t6 = -u2;
    // 限制电压矢量
    sum = t2 + t6;
    if (sum > ts)
    {
      k = ts / sum;
      t2 = k * t2;
      t6 = k * t6;
    }
    t7 = (ts - t2 - t6) / 2;
    myfoc.t_a = t6 + t7;
    myfoc.t_b = t2 + t6 + t7;
    myfoc.t_c = t7;
  }
  else if (sector == 3)
  {
    t2 = u1;
    t3 = u2;
    sum = t2 + t3;
    if (sum > ts)
    {
      k = ts / sum;
      t2 = k * t2;
      t3 = k * t3;
    }
    t7 = (ts - t2 - t3) / 2;
    myfoc.t_a = t7;
    myfoc.t_b = t2 + t3 + t7;
    myfoc.t_c = t7 + t3;
  }
  else if (sector == 2)
  {
    t1 = -u1;
    t3 = -u3;
    sum = t1 + t3;
    if (sum > ts)
    {
      k = ts / sum;
      t1 = k * t1;
      t3 = k * t3;
    }
    t7 = (ts - t1 - t3) / 2;
    myfoc.t_a = t7;
    myfoc.t_b = t3 + t7;
    myfoc.t_c = t7 + t3 + t1;
  }
  else if (sector == 6)
  {
    t1 = u2;
    t5 = u3;
    sum = t1 + t5;
    if (sum > ts)
    {
      k = ts / sum;
      t1 = k * t1;
      t5 = k * t5;
    }
    t7 = (ts - t1 - t5) / 2;
    myfoc.t_a = t5 + t7;
    myfoc.t_b = t7;
    myfoc.t_c = t1 + t5 + t7;
  }
  else if (sector == 4)
  {
    t4 = -u2;
    t5 = -u1;
    sum = t4 + t5;
    if (sum > ts)
    {
      k = ts / sum;
      t4 = k * t4;
      t5 = k * t5;
    }
    t7 = (ts - t4 - t5) / 2;
    myfoc.t_a = t4 + t5 + t7;
    myfoc.t_b = t7;
    myfoc.t_c = t5 + t7;
  }
}

/**
 * @brief
 *
 */
void foc_init(void)
{
  myfoc.Park = Park;
  myfoc.ipark = ipark;
  myfoc.clarke = clarke;
  myfoc.svpwm = svpwm;
}
