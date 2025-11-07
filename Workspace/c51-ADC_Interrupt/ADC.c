/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       06 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 51:   Convertidor analógico digital (ADC): Interrupción
 * Descripción: Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador de
 *              muestras SS_1 para leer el valor de dos potenciómetros conectados en las entradas
 *              analógicas AIN_10 (PB4) y AIN_17 (PK1), empleando interrupciones, usando los LED
 *              de usuario de la tarjeta de desarrollo como indicador del nivel de voltaje de un
 *              potenciómetro, dependiendo del último botón (SW1 o SW2) presionado.
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
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 * Variables externas (parámetros)
 */


/**************************************************************************************************
 * Funciones
 */

/************************************************
 * Función:     ADC0_SS1_Init
 * 
 * Descripción: Inicialización y configuración del ADC_0, SS_1.
 */

void ADC0_SS1_Init(void) {

    /********************************************
     *  Inicialización y configuración del ADC
     */

    /** 1.  Habilitar la señal de reloj del ADC y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCADC_R |= 0x1;                                                                        /*  R0: ADC Module 0 Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRADC_R & 0x1)) {}                                                              /*  R0: ADC Module 0 Peripheral Ready -> ADC module 0 is ready for access */

    /** 2.  Habilitar la señal de reloj de los GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x0002;                                                                    /*  R1: GPIO PortB Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0002)) {}                                                          /*  R1: GPIO PortB Peripheral Ready -> GPIO PortB is ready for access */
    SYSCTL_RCGCGPIO_R |= 0x0200;                                                                    /*  R9: GPIO PortK Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x0200)) {}                                                          /*  R9: GPIO PortK Peripheral Ready -> GPIO PortK is ready for access */

    /** 3.  Habilitar las funciones alternas de hardware de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_AFSEL_R |= 0x10;                                                                 /*  PortB[4] => AFSEL: GPIO Alternate Function Select -> Alternate hardware function */
    GPIO_PORTK_AFSEL_R |= 0x02;                                                                     /*  PortK[1] => AFSEL: GPIO Alternate Function Select -> Alternate hardware function */

    /** 4.  Deshabilitar las funciones digitales de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_DEN_R &= ~0x10;                                                                  /*  PortB[4] => DEN: Digital Enable -> Disabled */
    GPIO_PORTK_DEN_R &= ~0x02;                                                                      /*  PortK[1] => DEN: Digital Enable -> Disabled */

    /** 5.  Deshabilitar el circuito de aislamiento analógico de los pines de los puertos GPIO. */
    GPIO_PORTB_AHB_AMSEL_R |= 0x10;                                                                 /*  PortB[4] => GPIOAMSEL: Analog Mode Select -> Isolation disabled, analog function enabled */
    GPIO_PORTK_AMSEL_R |= 0x02;                                                                     /*  PortK[1] => GPIOAMSEL: Analog Mode Select -> Isolation disabled, analog function enabled */

    /** 6.  Si se requiere, configurar los niveles de prioridad de los secuenciadores de muestras. */

    /********************************************
     *  Configuración del secuenciador de muestras (SS)
     */

    /** 1.  Asegurar que el secuenciador de muestras está deshabilitado. */
    ADC0_ACTSS_R &= ~0x0002;                                                                        /*  ADC0 => ASEN1: ADC SS1 Enable -> Disabled */

    /** 2.  Configurar el evento de disparo para el SS. */
    ADC0_EMUX_R = (ADC0_EMUX_R & ~0x00F0) | (0x0 << 4);                                             /*  ADC0 => EM1: SS1 Trigger Select -> Processor */

    /** 3.  Si se utiliza un generador PWM como fuente de disparo, especificar el módulo PWM. */

    /** 4.  Para cada muestra en el SS, configurar la fuente de entrada de la señal analógica. */
    ADC0_SSMUX1_R = (1 << 4) | (10 << 0);
    ADC0_SSEMUX1_R = (1 << 4) | (0 << 0);
    // ADC0_SSMUX1_R = ((1 << 4) |                                                                     /*  ADC0 => SS1 MUX1: 2nd Sample Input Select -> 17 */
    //                  (10 << 0));                                                                    /*  ADC0 => SS1 MUX0: 1st Sample Input Select -> 10 */
    // ADC0_SSEMUX1_R = ((1 << 4) |                                                                    /*  ADC0 => SS1 EMUX1: 2nd Sample Input Select -> The sample input is selected from AIN[19:16] */
    //                   (0 << 0));                                                                    /*  ADC0 => SS1 EMUX0: 1st Sample Input Select -> The sample input is selected from AIN[15:0] */

    /** 5.  Para cada muestra en el SS, configurar los bits de control correspondientes, asegurando
     *      que el bit END de la última muestra esté habilitado. */
    ADC0_SSCTL1_R = ((ADC0_SSCTL1_R &~0x00FF) | (0x6 << 4) | (0x0 << 0));
        /** (ADC0_SSCTL1_R &~0x00FF)            -> Máscara para limpiar los campos relacionados a la primer y segunda muestra.
         *  (0x6 << 4) Campos relacionados a la segunda muestra:
         *      TS1  = 0    -> ADC0 => SS1 TS1: 2nd Sample Temp Sensor Select -> Analog input specified by the ADCSSMUXn register
         *      IE1  = 1    -> ADC0 => SS1 IE1: 2nd Sample Interrupt Enable -> Raw interrupt signal is asserted at the end of this sample´s conversion
         *      END1 = 1    -> ADC0 => SS1 END1: 2nd End of Sequence -> This is the end of sequence
         *      D1   = 0    -> ADC0 => SS1 D1: 2nd Sample Differential Input Select -> The analog inputs are not differentially sampled
         * (0x0 << 0) Campos relacionados a la primera muestra:
         *      TS0  = 0    -> ADC0 => SS1 TS0: 1st Sample Temp Sensor Select -> Analog input specified by the ADCSSMUXn register
         *      IE0  = 0    -> ADC0 => SS1 IE0: 1st Sample Interrupt Enable -> The raw interrupt is not asserted at the end of this sample's conversion
         *      END0 = 0    -> ADC0 => SS1 END0: 1st End of Sequence -> Another sample in the sequence is the final sample
         *      D0   = 0    -> ADC0 => SS1 D0: 1st Sample Differential Input Select -> The analog inputs are not differentially sampled
         */

    /** 6.  Si se utiliza interrupción, desenmascarar la interrupción local. */
    ADC0_IM_R |= 0x0002;                                                                            /*  ADC0 => MASK1: SS1 Interrupt Mask -> Unmasked */

    /** 7.  Habilitar el SS. */
    ADC0_ACTSS_R |= 0x0002;                                                                         /*  ADC0 => ASEN1: ADC SS1 Enable -> Enabled */

    /********************************************
     *  Interrupción
     */

    /** Establecer el nivel de prioridad de la IRQ. */
    NVIC_PRI3_R = ((NVIC_PRI3_R & ~0xE0000000) | (1 << 29));                                        /*  IRQ_15 (ADC0 SS1) => INTD: Interrupt Priority -> Cleared and set 1 */

    /** Habilitación de la IRQ en el NVIC. */
    NVIC_EN0_R |= (1 << (15 - 0));                                                                  /*  IRQ_15 (ADC0 SS1) => INT: Interrupt Enable -> Enabled */

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
