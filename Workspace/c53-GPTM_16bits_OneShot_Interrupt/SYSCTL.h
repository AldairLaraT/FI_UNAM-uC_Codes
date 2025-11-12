/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          11 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 53:      Módulo temporizador de propósito general (GPTM): 16bits, one-shot, interrupción
 *  Descripción:    Código en lenguaje C que utiliza los temporizadores TIMER0A y TIMER0B en
 *                  configuración individual (16 bits) y modo one-shot, empleando interrupciones
 *                  por time-out, para generar retardos al presionar un botón (SW1 o SW2) y
 *                  conmutar los LED de usuario (D1 o D2) de la tarjeta de desarrollo.
 * 
 *  Archivo:        Archivo de cabecera del módulo SYSCTL
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef SYSCTL_H                                                                                    /*  Verificar si SYSCTL_H no ha sido definido previamente */
#define SYSCTL_H                                                                                    /*  Definir SYSCTL_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  System Control (SYSCTL) registers                                                                   pp.247      Register map
 */
#define SYSCTL_RCGCTIMER_R          (*((volatile uint32_t *)0x400FE604))                            /*  pp.380      16/32-Bit General-Purpose Timer Run Mode Clock Gating Control */
#define SYSCTL_RCGCGPIO_R           (*((volatile uint32_t *)0x400FE608))                            /*  pp.382      GPIO Run Mode Clock Gating Control */
#define SYSCTL_PRTIMER_R            (*((volatile uint32_t *)0x400FEA04))                            /*  pp.497      16/32-Bit General-Purpose Timer Peripheral Ready */
#define SYSCTL_PRGPIO_R             (*((volatile uint32_t *)0x400FEA08))                            /*  pp.499      GPIO Peripheral Ready */


/**************************************************************************************************
 *  Prototipos de funciones
 */


#endif                                                                                              /*  SYSCTL_H */
