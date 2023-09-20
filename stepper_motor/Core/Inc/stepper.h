#ifndef STEPPER_H
#define STEPPER_H

#ifdef __cplusplus

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "gpio.h"

class stepper
{
public:
   /*
      motor discription
   */
   uint16_t stepper_FullStepResolution;
   uint16_t stepper_HalfStepResolution;
   uint16_t numberOfCoils;

   /*
      pins connnected to stepper motor driver
   */
   GPIO_TypeDef *port[4];
   uint16_t num[4];

   /*
      control logic
   */
   bool mode; // FALSE for fullstep mode and TRUE for fullstep
   uint16_t angle;
   uint16_t stepsRequired;
   uint32_t delayVariable;
   enum modes
   {
      HALFMODE = 0,
      FULLMODE = 1
   };

   // functions
   stepper(){};
   stepper(GPIO_TypeDef *a, uint16_t num1, GPIO_TypeDef *b, uint16_t num2, GPIO_TypeDef *c,
           uint16_t num3, GPIO_TypeDef *d, uint16_t num4, uint16_t resolution);
   stepper(const stepper &step)
   {
      this->port[0] = step.port[0];
      this->port[1] = step.port[1];
      this->port[2] = step.port[2];
      this->port[3] = step.port[3];
      this->num[0] = step.num[0];
      this->num[1] = step.num[1];
      this->num[2] = step.num[2];
      this->num[3] = step.num[3];
      this->stepper_FullStepResolution = step.stepper_FullStepResolution;
      this->stepper_HalfStepResolution = step.stepper_HalfStepResolution;
   }
   void setSpeed(uint16_t speed);
   void setAngle(uint16_t angle);
   void setMode(int);
   void convetAngelToSteps();
   void start(int a, int b, int c, int d);
   void rotate();
};
#endif

#ifdef __cplusplus

extern "C"
{
#endif
   void initStepper();
   void operateStepper();
#ifdef __cplusplus
}
#endif

#endif