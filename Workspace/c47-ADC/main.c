/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          04 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 48:      Convertidor analógico digital (ADC)
 *  Descripción:    Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador
 *                  de muestras SS_3 para leer el valor de un potenciómetro conectado en la entrada
 *                  analógica AIN_10 (PB4) y usar los LED de usuario de la tarjeta de desarrollo
 *                  como indicador del nivel de voltaje.
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "ADC.h"                                                                                    /*  Archivo de cabecera del módulo ADC */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables globales
 */

uint16_t ADC0_SS3_AIN10;                                                                            /*  Voltaje en la entrada analógica 10 (AIN_10, ADC_0, SS_3) */


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    GPIO_PortF_Init();                                                                              /*  Inicialización y configuración del puerto GPIO F */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */
    ADC0_SS3_Init();                                                                                /*  Inicialización y configuración del ADC_0, SS_3 */

    uint16_t limit1 = 800;
    uint16_t limit2 = 1600;
    uint16_t limit3 = 2400;
    uint16_t limit4 = 3200;

    // uint32_t Delay = 16000000;                                                                      /*  Valor de carga del SysTick para un retardo de 4s (f = 4MHz) */
    // SysTick_Init (Delay);                                                                           /*  Inicialización y configuración del SysTick */

    while (1) {

        // while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                           /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

        /** Generar el evento de disparo para iniciar el muestreo de la señal. */
        ADC0_PSSI_R |= 0x08;                                                                        /*  ADC0 => SS3: SS3 Initiate -> Begin sampling on SS3 */

        /** Esperar a que termine la conversión de la señal. */
        while (!(ADC0_RIS_R & 0x08)) {}                                                             /*  ADC0 => INR3: SS3 Raw Interrupt Status -> A sample has completed conversion */

        /** Leer el resultado de la conversión almacenado en la FIFO. */
        ADC0_SS3_AIN10 = (ADC0_SSFIFO3_R & 0x0FFF);                                                 /*  ADC0 SS3 => DATA: Conversion Result Data */

        /** Limpiar la bandera de estado de interrupción cruda. */
        ADC0_ISC_R |= 0x08;                                                                         /*  ADC0 => IN3: SS3 Interrupt Status and Clear -> IN3 bit (ADC0_ISC_R) and INR3 bit (ADC0_RIS_R) cleared */

        if (ADC0_SS3_AIN10 < limit1) {
            GPIO_PORTN_DATA_R = 0x00;                                                               /*  LED D1 -> off | LED D2 -> off */
            GPIO_PORTF_AHB_DATA_R = 0x00;                                                           /*  LED D3 -> off | LED D4 -> off */
        }
        else if (ADC0_SS3_AIN10 < limit2) {
            GPIO_PORTN_DATA_R = 0x02;                                                               /*  LED D1 -> on  | LED D2 -> off */
            GPIO_PORTF_AHB_DATA_R = 0x00;                                                           /*  LED D3 -> off | LED D4 -> off */
        }
        else if (ADC0_SS3_AIN10 < limit3) {
            GPIO_PORTN_DATA_R = 0x03;                                                               /*  LED D1 -> on  | LED D2 -> on  */
            GPIO_PORTF_AHB_DATA_R = 0x00;                                                           /*  LED D3 -> off | LED D4 -> off */
        }
        else if (ADC0_SS3_AIN10 < limit4) {
            GPIO_PORTN_DATA_R = 0x03;                                                               /*  LED D1 -> on  | LED D2 -> on  */
            GPIO_PORTF_AHB_DATA_R = 0x10;                                                           /*  LED D3 -> on  | LED D4 -> off */
        } else {
            GPIO_PORTN_DATA_R = 0x03;                                                               /*  LED D1 -> on  | LED D2 -> on  */
            GPIO_PORTF_AHB_DATA_R = 0x11;                                                           /*  LED D3 -> on  | LED D4 -> on  */
        }
    }
}
