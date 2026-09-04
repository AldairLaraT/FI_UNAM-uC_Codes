/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          23 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 57:      Universal Asynchronous Receiver/Transmitter (UART)
 *  Descripción:    Código en lenguaje C que utiliza el módulo UART0 (PA[1,0]) con baud rate de
 *                  115200, sin bit de paridad y un bit de parada, para enviar (con SW2) un
 *                  caracter en formato ASCII (ajustable con SW1) y recibir comandos por
 *                  interrupción para el control de los LED de usuario de la tarjeta de desarrollo.
 * 
 *  Archivo:        Archivo fuente del módulo NVIC
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */
#include "UART.h"                                                                                   /*  Archivo de cabecera del módulo UART */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */

extern uint32_t Bounce_Delay;                                                                       /*  Valor de carga del SysTick para el retardo de rebote */
extern uint8_t UART_Message;                                                                        /*  Mensaje enviado por UART */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        UART0_Handler
 * 
 *  Descripción:    Rutina de servicio de interrupción (ISR) del UART0.
 */

void UART0_Handler(void) {

    /** Limpiar la bandera de interrupción. */
    UART0_ICR_R |= 0x10;                                                                            /*  UART0 => RXIC: Receive Interrupt Clear -> RXRIS bit (UARTRIS) and RXMIS bit (UARTMIS) cleared */

    /** Lectura de los datos recibido. */
    int UART_DataReceived[2];
    UART_DataReceived[0] = (UART0_DR_R & 0xFF);                                                     /*  UART0 => DATA: Data Transmitted or Received -> Reads the DATA that was received by the UART */
    UART_DataReceived[1] = (UART0_DR_R & 0xFF);                                                     /*  UART0 => DATA: Data Transmitted or Received -> Reads the DATA that was received by the UART */

    if (UART_DataReceived[0] == 68) {                                                               /*  'D' en ASCII */
        if (UART_DataReceived[1] == 49) {                                                           /*  '1' en ASCII */
            GPIO_PORTN_DATA_R ^= 0x02;                                                              /*  LED D1 -> toggle */
        }
        else if (UART_DataReceived[1] == 50) {                                                      /*  '2' en ASCII */
            GPIO_PORTN_DATA_R ^= 0x01;                                                              /*  LED D2 -> toggle */
        }
        else if (UART_DataReceived[1] == 51) {                                                      /*  '3' en ASCII */
            GPIO_PORTF_AHB_DATA_R ^= 0x10;                                                          /*  LED D3 -> toggle */
        }
        else if (UART_DataReceived[1] == 52) {                                                      /*  '4' en ASCII */
            GPIO_PORTF_AHB_DATA_R ^= 0x01;                                                          /*  LED D4 -> toggle */
        }
    }
}

/************************************************
 *  Función:        GPIO_PortJ_Handler
 * 
 *  Descripción:    Rutina de servicio de interrupción (ISR) del GPIO PortJ.
 */

void GPIO_PortJ_Handler(void) {

    /** Limpiar la bandera de interrupción. */
    GPIO_PORTJ_AHB_ICR_R = (GPIO_PORTJ_AHB_MIS_R & 0x03);                                           /*  PortJ => IC: Interrupt Clear -> Interrupt cleared */

    /** Retardo de rebote. */
    SysTick_Init_OneShot (Bounce_Delay);                                                            /*  Inicialización y configuración del SysTick en modo one-shot */
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                               /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

    /** Confirmar qué botón se presionó. */
    if (!(GPIO_PORTJ_AHB_DATA_R & 0x01)) {                                                          /*  IF (SW1 -> on) */
        if (UART_Message < 127) {
            UART_Message ++;
        } else {
            UART_Message = 32;
        }
    }

    if (!(GPIO_PORTJ_AHB_DATA_R & 0x02)) {                                                          /*  IF (SW2 -> on) */
        UART0_DR_R = (UART_Message & 0xFF);                                                         /*  UART0 => DATA: Data Transmitted or Received -> Loads DATA to be transmitted via UART */
    }

}
