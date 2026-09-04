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
 *  Archivo:        Archivo fuente del módulo GPTM
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPTM.h"                                                                                   /*  Archivo de cabecera del módulo GPTM */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        GPTM0A_Periodic_Init
 * 
 *  Descripción:    Inicialización y configuración del temporizador GPTM0 (subtimer A) en modo One-Shot.
 */

void GPTM0A_Periodic_Init(uint32_t LoadValue) {

    /**     Habilitar la señal de reloj del GPTM y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCTIMER_R |= 0x01;                                                                     /*  R0: 16/32-Bit GPTM0 Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRTIMER_R & 0x01)) {}                                                           /*  R0: 16/32-Bit GPTM0 Peripheral Ready -> 16/32-Bit GPTM2 is ready for access */

    /** 1.  Asegurar que el GPTM está deshabilitado. */
    TIMER0_CTL_R &= ~0x01;                                                                          /*  GPTM0 => TAEN: GPTM Timer A Enable -> Disabled */

    /** 2.  Configurar la operación global del GPTM. */
    TIMER0_CFG_R = 0x00;                                                                            /*  GPTM0 => GPTMCFG: GPTM Configuration -> 32-bit timer configuration */

    /** 3.  Seleccionar el modo de operación del GPTM. */
    TIMER0_TAMR_R |= 0x02;                                                                          /*  GPTM0 => TAMR: GPTM Timer A Mode -> Periodic Timer mode */

    /** 4.  De manera opcional, configurar el modo de operación del GPTM. */
    TIMER0_TAMR_R = (TIMER0_TAMR_R & ~0x00F0) | (0x0 << 4);
        /** (TIMER0_TAMR_R & ~0x00F0)   ->  Máscara para limpiar los campos relacionados a la configuración del temporizador en modo one-shot.
         *  (0x0 << 4)      Campos de configuración:
         *      TASNAPS = 0 ->  GPTM0 => TASNAPS: GPTM Timer A Snap-Shot Mode -> Snap-shot mode is disabled
         *      TAWOT   = 0 ->  GPTM0 => TAWOT: GPTM Timer A Wait-on-Trigger -> Timer A begins counting as soon as it is enabled
         *      TAMIE   = 0 ->  GPTM0 => TAMIE: GPTM Timer A Match Interrupt Enable -> The match interrupt is disabled for match events
         *      TACDIR  = 0 ->  GPTM0 => TACDIR: GPTM Timer A Match Count Direction -> The timer counts down
         */

    /** 5.  Cargar el valor inicial del GPTM y el preescalador. */
    TIMER0_TAILR_R = LoadValue;                                                                     /*  GPTM0 => TAILR: GPTM Timer A Interval Load Register -> Loads the counter for Timer A */

    /** 6.  Si se utiliza interrupción, desenmascarar la interrupción local. */
    TIMER0_IMR_R |= 0x01;                                                                           /*  GPTM0 => TATOIM: GPTM Timer A Time-Out Interrupt Mask -> Interrupt unmasked */

    /********************************************
     *  Interrupción
     */

    /** Establecer el nivel de prioridad de la IRQ. */
    NVIC_PRI4_R = ((NVIC_PRI4_R & ~0xE0000000) | (1 << 29));                                        /*  IRQ_19 (16/32-Bit Timer 0A) => INTD: Interrupt Priority -> Cleared and set 1 */

    /** Habilitación de la IRQ en el NVIC. */
    NVIC_EN0_R |= (1 << (19 - 0));                                                                  /*  IRQ_19 (16/32-Bit Timer 0A) => INT: Interrupt Enable -> Enabled */

}
