/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       04 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 49:   Convertidor analógico digital (ADC): Sensor de temperatura embebido
 * Descripción: Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador de
 *              muestras SS_3 para leer el valor del sensor de temperatura embebido en el
 *              microcontrolador y usar los LED de usuario de la tarjeta de desarrollo como
 *              indicador de la temperatura.
 * 
 * Archivo:     Archivo de cabecera del módulo SYSCTL
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef SYSCTL_H                                                                                    /*  Verificar si SYSCTL_H no ha sido definido previamente */
#define SYSCTL_H                                                                                    /*  Definir SYSCTL_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 * Definiciones y macros
 * System Control (SYSCTL) registers                                                                    pp247   Register map
 */
#define SYSCTL_PLLFREQ0_R           (*((volatile uint32_t *)0x400FE160))                            /*  pp292   PLL Frequency 0 */
#define SYSCTL_PLLSTAT_R            (*((volatile uint32_t *)0x400FE168))                            /*  pp294   PLL Status */
#define SYSCTL_RCGCGPIO_R           (*((volatile uint32_t *)0x400FE608))                            /*  pp382   GPIO Run Mode Clock Gating Control */
#define SYSCTL_RCGCADC_R            (*((volatile uint32_t *)0x400FE638))                            /*  pp396   ADC Run Mode Clock Gating Control */
#define SYSCTL_PRGPIO_R             (*((volatile uint32_t *)0x400FEA08))                            /*  pp499   GPIO Peripheral Ready */
#define SYSCTL_PRADC_R              (*((volatile uint32_t *)0x400FEA38))                            /*  pp515   ADC Peripheral Ready */


/**************************************************************************************************
 * Prototipos de funciones
 */


#endif                                                                                              /*  SYSCTL_H */
