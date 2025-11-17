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
 *  Archivo:        Archivo fuente del módulo GPTM
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
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
 *  Función:        GPTM2A_PWM_Init
 * 
 *  Descripción:    Inicialización y configuración del temporizador GPTM2 (subtimer A) en modo PWM.
 */

void GPTM2A_PWM_Init(uint32_t LoadValue, uint32_t MatchValue) {

    /********************************************
     *  Inicialización y configuración del puerto GPIO.
     */

    /**     Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0800;                                                                    /*  R11: GPIO PortM Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0800)) {}                                                          /*  R11: GPIO PortM Peripheral Ready -> GPIO PortM is ready for access */

    /**     Configurar la dirección del pin del puerto GPIO. */
    GPIO_PORTM_DIR_R |= 0x01;                                                                       /*  PortM[0] => DIR: GPIO Data direction -> Output */

    /**     Habilitar las funciones alternas de hardware del pin del puerto GPIO. */
    GPIO_PORTM_AFSEL_R |= 0x01;                                                                     /*  PortM[0] => AFSEL: GPIO Alternate Function Select -> Alternate hardware function */

    /**     Seleccionar las funciones alternas de hardware del pin del puerto GPIO. */
    GPIO_PORTM_PCTL_R = (GPIO_PORTM_PCTL_R & ~0xFFFFFFFF) | (3 << 0);                               /*  PortM[0] => PMC0: Port Mux Control 0 -> T2CCP0 */

    /**     Habilitar las funciones digitales del pin del puerto GPIO. */
    GPIO_PORTM_DEN_R |= 0x01;                                                                       /*  PortM[0] => DEN: Digital Enable -> Enabled */

    /********************************************
     *  Habilitación y configuración del GPTM
     */

    /**     Habilitar la señal de reloj del GPTM y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCTIMER_R |= 0x04;                                                                     /*  R2: 16/32-Bit GPTM2 Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRTIMER_R & 0x04)) {}                                                           /*  R2: 16/32-Bit GPTM2 Peripheral Ready -> 16/32-Bit GPTM2 is ready for access */

    /** 1.  Asegurar que el GPTM está deshabilitado. */
    TIMER2_CTL_R &= ~0x01;                                                                          /*  GPTM2 => TAEN: GPTM Timer A Enable -> Disabled */

    /** 2.  Configurar la operación global del GPTM como temporizador individual (16 bits). */
    TIMER2_CFG_R = 0x04;                                                                            /*  GPTM2 => GPTMCFG: GPTM Configuration -> 16-bit timer configuration */

    /** 3.  Seleccionar el modo de operación del GPTM (TnAMS=1, TnCMR=0 y TnMR=0x2). */
    TIMER2_TAMR_R = (TIMER2_TAMR_R & ~0xF) | (0xA << 0);
        /** (TIMER2_TAMR_R & ~0xF)      ->  Máscara para limpiar los campos de configuración.
         *  (0xA << 0)      Campos de configuración:
         *      TAAMS = 1   ->  GPTM2 => TAAMS: GPTM Timer A Alternate Mode Select -> PWM mode is enabled
         *      TACMR = 0   ->  GPTM2 => TACMR: GPTM Timer A Capture Mode -> Edge-Count mode
         *      TAMR  = 0x2 ->  GPTM2 => TAMR: GPTM Timer A Mode -> Periodic Timer mode
         */

    /** 4.  Configurar el estado de salida de la señal PWM (TnPWML). */
    TIMER2_CTL_R &= ~(1 << 6);                                                                      /*  GPTM2 => TAPWML: GPTM Timer A PWM Output Level -> Output is unaffected */

    /** 5.  Si se utiliza el preescalador, cargar los bits [23:16] del valor inicial del GPTM. */
    TIMER2_TAPR_R = (LoadValue & 0x00FF0000) >> 16;                                                 /*  GPTM2 => TAPSR: GPTM Timer A Prescale -> Loads the prescaler for Timer A */

    /** 6.  Si se utiliza interrupción, configurar la condición de interrupción. */

    /** 7.  Cargar los bits [15:0] del valor inicial del GPTM. */
    TIMER2_TAILR_R = (LoadValue & 0xFFFF);                                                          /*  GPTM2 => TAILR: GPTM Timer A Interval Load Register -> Loads the counter for Timer A */

    /** 8.  Cargar el valor de comparación. */
    TIMER2_TAPMR_R = (MatchValue & 0x00FF0000) >> 16;                                               /*  GPTM2 => TAPSMR: GPTM Timer A Prescale Match -> Loads the prescaler match value for Timer A */
    TIMER2_TAMATCHR_R = (MatchValue & 0xFFFF);                                                      /*  GPTM2 => TAMR: GPTM TImer A Match -> Loads the match value for Timer A */

    /** 9.  Habilitar el temporizador para que comience con la cuenta. */
    TIMER2_CTL_R |= 0x01;                                                                           /*  GPTM2 => TAEN: GPTM Timer A Enable -> Enabled and begins counting */

}
