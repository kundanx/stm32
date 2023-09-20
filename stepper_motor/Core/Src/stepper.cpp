#include "stepper.h"

/*
   function definition of stepper.h

*/

/*
    -intiallize the pin connected to stepper motor driver
    -set the full step resoultion of stepper motor
    -set the mode: half step/full step
*/

stepper:: stepper(GPIO_TypeDef *a,uint16_t num1, GPIO_TypeDef *b,uint16_t num2,  GPIO_TypeDef *c, 
                  uint16_t num3, GPIO_TypeDef *d,uint16_t num4, uint16_t resolution){
    this->port[0]= a;
    this->port[1]= b;
    this->port[2]= c;
    this->port[3]= d;
    this->num[0]=num1;
    this->num[1]=num2;
    this->num[2]=num3;
    this->num[3]=num4;
    this->stepper_FullStepResolution = resolution;
    this->stepper_HalfStepResolution = resolution*2;
}

void stepper::setSpeed(uint16_t speed){
    if(this->mode){
        this->delayVariable = (60000/this->stepper_FullStepResolution)/speed;
    }
    else 
    {
        this->delayVariable =(6000/this->stepper_HalfStepResolution)/speed;
    }
    
}

void stepper::setAngle(uint16_t angle){
    this->angle = angle;
    this->convetAngelToSteps();

}

void stepper::setMode(int check){
     this->mode = check;
}


void stepper::convetAngelToSteps(){
    if(mode){
        this->stepsRequired = (this->angle/360)*this->stepper_FullStepResolution;
    }
    else 
        this->stepsRequired = (this->angle/360)*this->stepper_HalfStepResolution;
}

void stepper::start(int  a, int  b, int c, int d){
   if(a == 1 ){
   HAL_GPIO_WritePin(port[0], num[0], GPIO_PIN_SET);}
   else{ HAL_GPIO_WritePin(port[0], num[0], GPIO_PIN_RESET);}
   if(b == 1 ){
   HAL_GPIO_WritePin(port[1], num[1], GPIO_PIN_SET);}
   else{ HAL_GPIO_WritePin(port[1], num[1], GPIO_PIN_RESET);}
   if(c == 1 ){
   HAL_GPIO_WritePin(port[2], num[2], GPIO_PIN_SET);}
   else{ HAL_GPIO_WritePin(port[2], num[2], GPIO_PIN_RESET);}
   if(d == 1 ){
   HAL_GPIO_WritePin(port[3], num[3], GPIO_PIN_SET);}
   else{ HAL_GPIO_WritePin(port[3], num[3], GPIO_PIN_RESET);}
}

void stepper::rotate(){
    bool exitVariable =0;
    if(this->angle > 0){
        exitVariable = 1;
    //Full step mode
    if(mode){
        for(uint16_t i =0; i< this->stepsRequired/4; i++){
        start(0,1,1,1);
        HAL_Delay(this->delayVariable);
         start(1,0,1,1);
        HAL_Delay(this->delayVariable);
         start(1,1,0,1);
        HAL_Delay(this->delayVariable);
         start(1,1,1,0);
        HAL_Delay(this->delayVariable);
        }
    }
    //Half step mode
    else{
        for(uint16_t i = 0; i< this->stepsRequired/2; i++){
        start(0,1,1,0);
        HAL_Delay(this->delayVariable);
         start(0,0,1,1);
        HAL_Delay(this->delayVariable);
         start(1,0,0,1);
        HAL_Delay(this->delayVariable);
         start(1,1,0,0);
        HAL_Delay(this->delayVariable);

    }
    }
    }
    else if(this->angle < 0){
        exitVariable =1;
     //Full step mode
    if(mode){
        for(uint16_t i =0; i< this->stepsRequired/4; i++){
        start(1,1,1,0);
        HAL_Delay(this->delayVariable);
         start(1,1,0,1);
        HAL_Delay(this->delayVariable);
         start(1,0,1,1);
        HAL_Delay(this->delayVariable);
         start(0,1,1,1);
        HAL_Delay(this->delayVariable);
        }
    }
    //Half step mode
    else{
        for(uint16_t i = 0; i< this->stepsRequired/2; i++){
        start(0,1,1,0);
        HAL_Delay(this->delayVariable);
         start(1,1,0,0);
        HAL_Delay(this->delayVariable);
         start(1,0,0,1);
        HAL_Delay(this->delayVariable);
         start(0,0,1,1);
        HAL_Delay(this->delayVariable);

    }
    }       
    }
    else {return;}

    if(exitVariable){
    return;}
}

stepper mystepper;

void initStepper(){
    mystepper = stepper(GPIOD, GPIO_PIN_12, GPIOD, GPIO_PIN_13, GPIOD, GPIO_PIN_14, GPIOD, GPIO_PIN_15, 2038);
    mystepper.setMode(0);
    mystepper.setSpeed(0.5);
}

void operateStepper(){
   mystepper.setAngle(90);
   mystepper.rotate();
   mystepper.setAngle(-90);
   mystepper.rotate();

}