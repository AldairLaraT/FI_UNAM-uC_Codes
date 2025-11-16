/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 55:      Módulo temporizador de propósito general (GPTM): 32bits, periodic, interrupción
 *  Descripción:    Código en lenguaje C que utiliza el temporizador TIMER0A en configuración
 *                  concatenada (32 bits) y modo periodic, empleando interrupción por time-out,
 *                  para hacer parpadear un LED de usuario (D1), habilitando/deshabilitando el
 *                  temporizador con los botones (SW1 y SW2) de la tarjeta de desarrollo.
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
