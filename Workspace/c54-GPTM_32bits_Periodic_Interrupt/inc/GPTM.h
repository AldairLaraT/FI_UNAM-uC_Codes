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
 *  Archivo:        Archivo de cabecera del módulo GPTM
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef GPTM_H                                                                                      /*  Verificar si GPTM_H no ha sido definido previamente */
#define GPTM_H                                                                                      /*  Definir GPTM_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */


/**************************************************************************************************
 *  Definiciones y macros
 *  General-Purpose Timer Module (GPTM) registers                                                       pp.974      Register map
 */
    /** GPTM module 0 (TIMER0) */
#define TIMER0_CFG_R                (*((volatile uint32_t *)0x40030000))                            /*  pp.976      GPTM Configuration */
#define TIMER0_TAMR_R               (*((volatile uint32_t *)0x40030004))                            /*  pp.977      GPTM Timer A Mode */
#define TIMER0_CTL_R                (*((volatile uint32_t *)0x4003000C))                            /*  pp.986      GPTM Control */
#define TIMER0_IMR_R                (*((volatile uint32_t *)0x40030018))                            /*  pp.993      GPTM Interrupt Mask */
#define TIMER0_ICR_R                (*((volatile uint32_t *)0x40030024))                            /*  pp.1002     GPTM Interrupt Clear */
#define TIMER0_TAILR_R              (*((volatile uint32_t *)0x40030028))                            /*  pp.1004     GPTM Timer A Interval Load */


/************************************************
 *  Bit fields
 */
    //  Bit fields in the TIMER_RIS register                                                            pp.996
#define TIMER_RIS_TATORIS           0x00000001                                                      /*  GPTM Timer A Time-Out Raw Interrupt */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void GPTM0A_Periodic_Init(uint32_t LoadValue);                                                      /*  Inicialización y configuración del temporizador GPTM0 (subtimer A) en modo periodic */


#endif                                                                                              /*  GPTM_H */
