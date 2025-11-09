/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          04 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 49:      Convertidor analógico digital (ADC): Sensor de temperatura embebido
 *  Descripción:    Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador
 *                  de muestras SS_3 para leer el valor del sensor de temperatura embebido en el
 *                  microcontrolador y usar los LED de usuario de la tarjeta de desarrollo como
 *                  indicador de la temperatura.
 * 
 *  Archivo:        Archivo fuente del módulo SysTick
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        SysTick_Init
 * 
 *  Descripción:    Inicialización y configuración del SysTick.
 * 
 *  Parámetros:
 *      SysTick_Reload  : Valor de carga/inicio del SysTick (ST_RELOAD)
 */

void SysTick_Init(uint32_t SysTick_Reload) {

    /** 1.  Cargar el valor de cuenta del SysTick. */
    NVIC_ST_RELOAD_R = (SysTick_Reload & 0x00FFFFFF);                                               /*  RELOAD: Reload Value */

    /** 2.  Limpiar el valor de cuenta actual del SysTick. */
    NVIC_ST_CURRENT_R = 0;                                                                          /*  CURRENT: Current Value -> Cleared */

    /** 3.  Configurar el SysTick para la operación requerida. */
    NVIC_ST_CTRL_R |= 0x01;                                                                         /*  Enables SysTick to operate in a multi-shot way (PIOSC divided by 4) */

}
