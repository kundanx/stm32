#include"tfmini.hpp"   

/*
@ construtor of class tfmini
@ param- address of data variable of type _UART_Handletype
@ general information:
-communication protocal: UART
-DMA: Rx pin intiallized with DMA
-baud rate: 115200
-Number of bytes in each frame: 9
-data bsit : 8
-stop bit: 1
-parity bit: none
@ Returns None
*/
tfmini mytf;
tfmini::tfmini(UART_HandleTypeDef *huartC, uint16_t *dist)
{
    huart = huartC;
    Distance = dist;

}
/*
    @ Give distance 
    @ param: buffer to store distance
    @ Return None
*/
void tfmini::getDistance()
{  
    printf("getDistance called");
     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_UART_Receive_DMA(huart, Recieve_UART, NO_OF_BYTES);
}

/*
@ Callback function which is called when the requested data is recieved
@ Return None
*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huartB)
{   
    printf("callback function called");
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    if(huartB->Instance == mytf.huart->Instance)
    {
        HAL_UART_Receive_DMA(mytf.huart, mytf.Recieve_UART, NO_OF_BYTES);
        if((mytf.Recieve_UART[0]==TF_HEAD) && (mytf.Recieve_UART[1]==TF_HEAD))
        {
            mytf.hash = mytf.Recieve_UART[0] + mytf.Recieve_UART[1] + mytf.Recieve_UART[2] + mytf.Recieve_UART[3] + mytf.Recieve_UART[4] + mytf.Recieve_UART[5] + mytf.Recieve_UART[6] + mytf.Recieve_UART[7];
            if(mytf.hash == mytf.Recieve_UART[8])
            {
                *mytf.Distance = (uint16_t)mytf.Recieve_UART[3] << 8 + mytf.Recieve_UART[2];
            }

        }

    }

}
void operate_tfmini(UART_HandleTypeDef *huartF, uint16_t *dist)
{ 
    printf("operate_tfmini called");
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    mytf = tfmini(huartF, dist);
    mytf.getDistance();

}