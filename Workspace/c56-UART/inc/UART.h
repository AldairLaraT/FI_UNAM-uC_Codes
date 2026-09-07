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
 *  Archivo:        Archivo de cabecera del módulo UART
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef UART_H                                                                                      /*  Verificar si UART_H no ha sido definido previamente */
#define UART_H                                                                                      /*  Definir UART_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  Universal Asynchronous Receiver/Transmitter (UART) registers                                        pp.1173     Register map
 */
    /** UART module 0 (UART0) */
#define UART0_DR_R                  (*((volatile uint32_t *)0x4000C000))                            /*  pp.1175     UART Data */
#define UART0_FR_R                  (*((volatile uint32_t *)0x4000C018))                            /*  pp.1180     UART Flag */
#define UART0_IBRD_R                (*((volatile uint32_t *)0x4000C024))                            /*  pp.1184     UART Integer Baud-Rate Divisor */
#define UART0_FBRD_R                (*((volatile uint32_t *)0x4000C028))                            /*  pp.1185     UART Fractional Baud-Rate Divisor */
#define UART0_LCRH_R                (*((volatile uint32_t *)0x4000C02C))                            /*  pp.1186     UART Line Control */
#define UART0_CTL_R                 (*((volatile uint32_t *)0x4000C030))                            /*  pp.1188     UART Control */
#define UART0_IFLS_R                (*((volatile uint32_t *)0x4000C034))                            /*  pp.1192     UART Interrupt FIFO Level Select */
#define UART0_IM_R                  (*((volatile uint32_t *)0x4000C038))                            /*  pp.1194     UART Interrupt Mask */
#define UART0_ICR_R                 (*((volatile uint32_t *)0x4000C044))                            /*  pp.1206     UART Interrupt Clear */
#define UART0_CC_R                  (*((volatile uint32_t *)0x4000CFC8))                            /*  pp.1213     UART Clock Configuration */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void UART0_Init();                                                                                  /*  Inicialización y configuración del UART0 */


#endif                                                                                              /*  UART_H */
