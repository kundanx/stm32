#ifndef TFMINI_HPP_
#define TFMINI_HPP_

#ifdef __cplusplus
#include "stm32f4xx.h"
#include<stdio.h>

#define TF_HEAD 0x59
#define NO_OF_BYTES 9

class tfmini
{ 
  public:
    uint16_t *Distance;
    UART_HandleTypeDef *huart;
    uint32_t hash;
    uint8_t Recieve_UART[NO_OF_BYTES];
    /*
      @ construtor of class tfmini
      @ param- address of data variable of type _UART_Handletype
      @ general information:
        -communication protocal: UART
        -DMA: Rx pin intiallized with DMA
        -baud rate: 115200
        -Number of bytes in each frame: 9
        -word length : 8
        -stop bit: 1
        -parity bit: none
      @ Returns None
    */
     tfmini(UART_HandleTypeDef *huartC, uint16_t *dist) {};
      /*
         @ Give distance 
         @ param: buffer to store distance
         @ Return None
      */
     void getDistance(){};

    /*
       @ Callback function which is called when the requested data is recieved
       @ Return None
    */
};
#endif

#ifdef __cplusplus

extern "C"
{
#endif

/*
   @ initialize an object  of class tfmini and obtain distance from it
   @ param: address of variable of type __UART_HandleTypeDef
   @ return : uint16_t distance value
*/

void operate_tfmini(UART_HandleTypeDef *huartF, uint16_t *dist){};
#ifdef __cplusplus
}
#endif

#endif