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
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */
#include "UART.h"                                                                                   /*  Archivo de cabecera del módulo UART */


/**************************************************************************************************
 *  Variables globales
 */

uint32_t Bounce_Delay = 200000;                                                                     /*  Valor de carga del SysTick para un retardo de rebote de 50ms (f = 4MHz) */
uint8_t UART_Message = 32;                                                                          /*  Mensaje enviado por UART */


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    GPIO_PortF_Init();                                                                              /*  Inicialización y configuración del puerto GPIO F */
    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */
    UART0_Init();                                                                                   /*  Inicialización y configuración del UART0 */

    while (1) {}
}
