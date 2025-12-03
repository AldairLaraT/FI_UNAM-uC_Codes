/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          01 de diciembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 58:      Inter-Integrated Circuit (I2C)
 *  Descripción:    Código en lenguaje C que utiliza el módulo I2C0 (PB[3,2]) en velocidad estándar
 *                  (100kbps) para comunicarse con un reloj en tiempo real (RTC) DS1307.
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
#define SYSCTL_RCGCGPIO_R           (*((volatile uint32_t *)0x400FE608))                            /*  pp.382      GPIO Run Mode Clock Gating Control */
#define SYSCTL_RCGCI2C_R            (*((volatile uint32_t *)0x400FE620))                            /*  pp.391      Inter-Integrated Circuit Run Mode Clock Gating Control */
#define SYSCTL_PRGPIO_R             (*((volatile uint32_t *)0x400FEA08))                            /*  pp.499      GPIO Peripheral Ready */
#define SYSCTL_PRI2C_R              (*((volatile uint32_t *)0x400FEA20))                            /*  pp.509      Inter-Integrated Circuit Peripheral Ready */


/**************************************************************************************************
 *  Prototipos de funciones
 */


#endif                                                                                              /*  SYSCTL_H */
