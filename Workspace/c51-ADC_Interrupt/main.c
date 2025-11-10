/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          06 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 51:      Convertidor analógico digital (ADC): Interrupción
 *  Descripción:    Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador
 *                  de muestras SS_1 para leer el valor de dos potenciómetros conectados en las
 *                  entradas analógicas AIN_10 (PB4) y AIN_17 (PK1), empleando interrupciones,
 *                  usando los LED de usuario de la tarjeta de desarrollo como indicador del nivel
 *                  de voltaje de un potenciómetro, dependiendo del último botón (SW1 o SW2)
 *                  presionado.
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "ADC.h"                                                                                    /*  Archivo de cabecera del módulo ADC */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables globales
 */

uint8_t pot_select = 0;                                                                             /*  Selección del potenciómetro */
uint16_t LED_control_value;                                                                         /*  Valor del potenciómetro que controla los LED de usuario */
uint16_t ADC0_SS1_AIN10;                                                                            /*  Voltaje en la entrada analógica 10 (AIN_10, ADC_0, primera muestra del SS_1) */
uint16_t ADC0_SS1_AIN17;                                                                            /*  Voltaje en la entrada analógica 17 (AIN_17, ADC_0, segunda muestra del SS_1) */
uint32_t Bounce_Delay = 200000;                                                                     /*  Valor de carga del SysTick para un retardo de rebote de 50ms (f = 4MHz) */


/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    GPIO_PortF_Init();                                                                              /*  Inicialización y configuración del puerto GPIO F */
    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */
    ADC0_SS1_Init();                                                                                /*  Inicialización y configuración del ADC_0, SS_1 */

    uint16_t limit1 = 800;
    uint16_t limit2 = 1600;
    uint16_t limit3 = 2400;
    uint16_t limit4 = 3200;

    /** Generar el evento de disparo para iniciar el muestreo de la señal. */
    ADC0_PSSI_R |= 0x02;                                                                            /*  ADC0 => SS1: SS1 Initiate -> Begin sampling on SS1 */

    while (1) {

        if (pot_select == 0) {
            LED_control_value = ADC0_SS1_AIN10;
        } else {
            LED_control_value = ADC0_SS1_AIN17;
        }

        if (LED_control_value < limit1) {
            GPIO_PORTN_DATA_R = 0x00;                                                               /*  LED D1 -> off | LED D2 -> off */
            GPIO_PORTF_AHB_DATA_R = 0x00;                                                           /*  LED D3 -> off | LED D4 -> off */
        }
        else if (LED_control_value < limit2) {
            GPIO_PORTN_DATA_R = 0x02;                                                               /*  LED D1 -> on  | LED D2 -> off */
            GPIO_PORTF_AHB_DATA_R = 0x00;                                                           /*  LED D3 -> off | LED D4 -> off */
        }
        else if (LED_control_value < limit3) {
            GPIO_PORTN_DATA_R = 0x03;                                                               /*  LED D1 -> on  | LED D2 -> on  */
            GPIO_PORTF_AHB_DATA_R = 0x00;                                                           /*  LED D3 -> off | LED D4 -> off */
        }
        else if (LED_control_value < limit4) {
            GPIO_PORTN_DATA_R = 0x03;                                                               /*  LED D1 -> on  | LED D2 -> on  */
            GPIO_PORTF_AHB_DATA_R = 0x10;                                                           /*  LED D3 -> on  | LED D4 -> off */
        } else {
            GPIO_PORTN_DATA_R = 0x03;                                                               /*  LED D1 -> on  | LED D2 -> on  */
            GPIO_PORTF_AHB_DATA_R = 0x11;                                                           /*  LED D3 -> on  | LED D4 -> on  */
        }
    }
}
