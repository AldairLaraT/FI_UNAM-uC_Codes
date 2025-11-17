/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          15 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 56:      Módulo temporizador de propósito general (GPTM): Pulse Width Modulation (PWM)
 *  Descripción:    Código en lenguaje C que utiliza el temporizador TIMER2A en configuración PWM,
 *                  generando una señal de 1 KHz con un ciclo de trabajo del 50% en el puerto GPIO
 *                  M[0] y los botones (SW1 y SW2) de la tarjeta de desarrollo para modificar el
 *                  ciclo de trabajo en saltos del 10%.
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
    /** GPTM module 2 (TIMER2) */
#define TIMER2_CFG_R                (*((volatile uint32_t *)0x40032000))                            /*  pp.976      GPTM Configuration */
#define TIMER2_TAMR_R               (*((volatile uint32_t *)0x40032004))                            /*  pp.977      GPTM Timer A Mode */
#define TIMER2_CTL_R                (*((volatile uint32_t *)0x4003200C))                            /*  pp.986      GPTM Control */
#define TIMER2_TAILR_R              (*((volatile uint32_t *)0x40032028))                            /*  pp.1004     GPTM Timer A Interval Load */
#define TIMER2_TAMATCHR_R           (*((volatile uint32_t *)0x40032030))                            /*  pp.1006     GPTM Timer A Match */
#define TIMER2_TAPR_R               (*((volatile uint32_t *)0x40032038))                            /*  pp.1008     GPTM Timer A Prescale */
#define TIMER2_TAPMR_R              (*((volatile uint32_t *)0x40032040))                            /*  pp.1010     GPTM Timer A Prescale Match */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void GPTM2A_PWM_Init(uint32_t LoadValue, uint32_t MatchValue);                                      /*  Inicialización y configuración del temporizador GPTM2 (subtimer A) en modo PWM */


#endif                                                                                              /*  GPTM_H */
