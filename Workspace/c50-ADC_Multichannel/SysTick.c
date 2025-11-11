/************************************************************************************************** 
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 * 
 *  Asignatura:     Microprocesadores y Microcontroladores
 *  Profesor:       M.I. Christo Aldair Lara Tenorio
 *  Fecha:          06 de noviembre de 2025
 * 
 *  Tema 09:        Periféricos
 *  Código 50:      Convertidor analógico digital (ADC): Multicanal
 *  Descripción:    Código en lenguaje C que configura el módulo ADC_0, empleando el secuenciador
 *                  de muestras SS_1 para leer el valor de dos potenciómetros conectados en las
 *                  entradas analógicas AIN_10 (PB4) y AIN_17 (PK1), usando los LED de usuario de
 *                  la tarjeta de desarrollo como indicador del nivel de voltaje de un
 *                  potenciómetro, dependiendo del último botón (SW1 o SW2) presionado.
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
 *  Función:        SysTick_Init_OneShot
 * 
 *  Descripción:    Inicialización y configuración del SysTick en modo one-shot.
 * 
 *  Parámetros:
 *      SysTick_Reload  : Valor de carga/inicio del SysTick (ST_RELOAD)
 */

void SysTick_Init_OneShot(uint32_t SysTick_Reload) {

    /** 1.  Cargar el valor de cuenta del SysTick. */
    NVIC_ST_RELOAD_R = (SysTick_Reload & 0x00FFFFFF);                                               /*  RELOAD: Reload Value */

    /** 2.  Limpiar el valor de cuenta actual del SysTick. */
    NVIC_ST_CURRENT_R = 0;                                                                          /*  CURRENT: Current Value -> Cleared */

    /** 3.  Configurar el SysTick para la operación requerida. */
    NVIC_ST_CTRL_R |= 0x01;                                                                         /*  Enables SysTick to operate in a multi-shot way (PIOSC divided by 4) */

    /** Limpiar el valor de carga/inicio del SysTick para deshabilitar el contador en el siguiente ciclo. */
    NVIC_ST_RELOAD_R = 0;                                                                           /*  RELOAD: Reload Value -> Cleared */

}
