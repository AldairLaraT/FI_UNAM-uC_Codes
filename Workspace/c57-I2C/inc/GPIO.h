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
 *  Archivo:        Archivo de cabecera del módulo GPIO
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef GPIO_H                                                                                      /*  Verificar si GPIO_H no ha sido definido previamente */
#define GPIO_H                                                                                      /*  Definir GPIO_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  General-Purpose Input/Output (GPIO) registers                                                       pp.757      Register map
 */
    /** GPIO Port B (PortB) */
#define GPIO_PORTB_AHB_AFSEL_R      (*((volatile uint32_t *)0x40059420))                            /*  pp.770      GPIO Alternate Function Select */
#define GPIO_PORTB_AHB_ODR_R        (*((volatile uint32_t *)0x4005950C))                            /*  pp.775      GPIO Open Drain Select */
#define GPIO_PORTB_AHB_DEN_R        (*((volatile uint32_t *)0x4005951C))                            /*  pp.781      GPIO Digital Enable */
#define GPIO_PORTB_AHB_PCTL_R       (*((volatile uint32_t *)0x4005952C))                            /*  pp.787      GPIO Port Control */


/**************************************************************************************************
 *  Prototipos de funciones
 */


#endif                                                                                              /*  GPIO_H */
