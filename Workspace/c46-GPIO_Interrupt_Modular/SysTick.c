/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       01 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 46:   Control de un LED con un SW de usuario con interrupción (modular)
 * Descripción: Código en lenguaje C que conmuta el LED D1 de la tarjeta de desarrollo,
 *              dependiendo del botón SW1, empleando interrupciones.
 * 
 * Archivo:     Archivo fuente del módulo SysTick
 * 
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 * Variables externas (parámetros)
 */


/**************************************************************************************************
 * Funciones
 */

/************************************************
 * Función:     SysTick_Init_OneShot
 * 
 * Descripción: Inicialización y configuración del SysTick en modo one-shot.
 * 
 * Parámetros:
 *      SysTick_Reload  : Valor de carga/inicio del SysTick (ST_RELOAD)
 */

void SysTick_Init_OneShot(uint32_t SysTick_Reload) {

    /*  1. Cargar el valor de cuenta del SysTick. */
    NVIC_ST_RELOAD_R = (SysTick_Reload & 0x00FFFFFF);                                               /*  RELOAD: Reload Value */

    /*  2. Limpiar el valor de cuenta actual del SysTick. */
    NVIC_ST_CURRENT_R = 0;                                                                          /*  CURRENT: Current Value -> Cleared */

    /*  3. Configurar el SysTick para la operación requerida. */
    NVIC_ST_CTRL_R |= 0x01;                                                                         /*  Enables SysTick to operate in a multi-shot way (PIOSC divided by 4) */

    /*  Limpiar el valor de carga/inicio del SysTick para deshabilitar el contador en el siguiente ciclo. */
    NVIC_ST_RELOAD_R = 0;                                                                           /*  RELOAD: Reload Value -> Cleared */

}
