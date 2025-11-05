/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       04 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 48:   Convertidor analógico digital (ADC)
 * Descripción: Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador de
 *              muestras SS_3 para leer el valor de un potenciómetro conectado en la entrada
 *              analógica AIN_10 (PB4) y usar los LED de usuario de la tarjeta de desarrollo como
 *              indicador del nivel de voltaje.
 * 
 * Archivo:     Archivo fuente del módulo ADC
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include "ADC.h"                                                                                    /*  Archivo de cabecera del módulo ADC */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 * Variables externas (parámetros)
 */


/**************************************************************************************************
 * Funciones
 */

/************************************************
 * Función:     ADC0_SS3_Init
 * 
 * Descripción: Inicialización y configuración del ADC_0, SS_3.
 */

void ADC0_SS3_Init(void) {

    /********************************************
     *  Inicialización y configuración del ADC
     */

    /** 1.  Habilitar la señal de reloj del ADC y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCADC_R |= 0x1;                                                                        /*  R0: ADC Module 0 Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRADC_R & 0x1)) {}                                                              /*  R0: ADC Module 0 Peripheral Ready -> ADC module 0 is ready for access */

    /** 2.  Habilitar la señal de reloj de los GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0002;                                                                    /*  R1: GPIO PortB Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0002)) {}                                                          /*  R1: GPIO PortB Peripheral Ready -> GPIO PortB is ready for access */

    /** 3.  Habilitar las funciones alternas de hardware de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_AFSEL_R |= 0x10;                                                                 /*  PortB[4] => AFSEL: GPIO Alternate Function Select -> Alternate hardware function */

    /** 4.  Deshabilitar las funciones digitales de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_DEN_R &= ~0x10;                                                                  /*  PortB[4] => DEN: Digital Enable -> Disabled */

    /** 5.  Deshabilitar el circuito de aislamiento analógico de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_AMSEL_R |= 0x10;                                                                 /*  PortB[4] => GPIOAMSEL: Analog Mode Select -> Isolation disabled, analog function enabled */

    /** 6.  Si se requiere, configurar los niveles de prioridad de los secuenciadores de muestras. */

    /********************************************
     *  Configuración del secuenciador de muestras (SS)
     */

    /** 1.  Asegurar que el secuenciador de muestras está deshabilitado. */
    ADC0_ACTSS_R &= ~0x0008;                                                                        /*  ADC0 => ASEN3: ADC SS3 Enable -> Disabled */

    /** 2.  Configurar el evento de disparo para el SS. */
    ADC0_EMUX_R = (ADC0_EMUX_R & ~0xF000) | (0x0 << 12);                                            /*  ADC0 => EM3: SS3 Trigger Select -> Processor */

    /** 3.  Si se utiliza un generador PWM como fuente de disparo, especificar el módulo PWM. */

    /** 4.  Para cada muestra en el SS, configurar la fuente de entrada de la señal analógica. */
    ADC0_SSMUX3_R = (10 << 0);                                                                      /*  ADC0 => SS3 MUX0: 1st Sample Input Select -> 10 */
    ADC0_SSEMUX3_R = (0 << 0);                                                                      /*  ADC0 => SS3 EMUX0: 1st Sample Input Select -> The sample input is selected from AIN[15:0] */

    /** 5.  Para cada muestra en el SS, configurar los bits de control correspondientes, asegurando
     *      que el bit END de la última muestra esté habilitado. */
    ADC0_SSCTL3_R = (ADC0_SSCTL3_R & ~0xF) |
                    ((0 << 3) |                                                                     /*  ADC0 => SS3 TS0: 1st Sample Temp Sensor Select -> Analog input specified by the ADCSSMUXn register */
                     (1 << 2) |                                                                     /*  ADC0 => SS3 IE0: Sample Interrupt Enable -> Raw interrupt signal is asserted at the end of this sample´s conversion */
                     (1 << 1) |                                                                     /*  ADC0 => SS3 END0: End of Sequence -> This is the end of sequence */
                     (0 << 0));                                                                     /*  ADC0 => SS3 D0: Sample Differential Input Select -> The analog inputs are not differentially sampled */

    /** 6.  Si se utiliza interrupción, desenmascarar la interrupción local. */

    /** 7.  Habilitar el SS. */
    ADC0_ACTSS_R |= 0x0008;                                                                         /*  ADC0 => ASEN3: ADC SS3 Enable -> Enabled */

    /********************************************
     *  Habilitación del PLL
     *  NOTA: Si se utiliza el PIOSC de 16MHz como fuente de reloj, es necesario habilitar y 
     *        deshabilitar el PLL.
     */

    /** 1.  Habilitar el PLL y esperar a que esté retroalimentado. */
    SYSCTL_PLLFREQ0_R |= (1 << 23);                                                                 /*  PLL => PLLPWR: PLL Power -> Enabled and oscillate based on (PLLFREQ0, PLLFREQ1) */
    while (!(SYSCTL_PLLSTAT_R & 0x1)) {}                                                            /*  PLL => LOCK: Lock -> PLL powered and locked */

    /** 2.  Habilitar el PIOSC. */
    ADC0_CC_R = ((ADC0_CC_R & ~0x000F) | 0x0001);                                                   /*  ADC0 => CS: Clock Source -> Alternate clock source as defined by ALTCLKCFG (default: PIOSC) */

    /** 3.  Deshabilitar el PLL. */
    SYSCTL_PLLFREQ0_R &= ~(1 << 23);                                                                /*  PLL => PLLPWR: PLL Power -> Disabled */

}
