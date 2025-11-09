/**************************************************************************************************
 * Universidad Nacional Autónoma de México (UNAM)
 * Facultad de Ingeniería | Departamento de Electrónica
 * 
 * Asignatura:  Microprocesadores y Microcontroladores
 * Profesor:    M.I. Christo Aldair Lara Tenorio
 * Fecha:       01 de noviembre de 2025
 * 
 * Tema 09:     Periféricos
 * Código 47:   Control de un contador con los SW de usuario, empleando interrupciones (modular)
 * Descripción: Código en lenguaje C que actualiza el valor de un contador, dependiendo del botón
 *              que se presiona (SW1 y SW2 de la tarjeta de desarrollo), ejecutando una tarea
 *              distinta en el código principal (conmutación de los LED de usuario).
 * 
 *  Archivo:        Archivo fuente del módulo NVIC
 * 
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */

extern uint32_t Bounce_Delay;                                                                       /*  Valor de carga del SysTick para el retardo de rebote */
extern int counter;


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        GPIO_PortJ_Handler
 * 
 *  Descripción:    Rutina de servicio de interrupción (ISR) del GPIO PortJ.
 */

void GPIO_PortJ_Handler(void) {

    /** Limpiar la bandera de interrupción. */
    GPIO_PORTJ_AHB_ICR_R = (GPIO_PORTJ_AHB_MIS_R & 0x03);                                           /*  PortJ => IC: Interrupt Clear -> Interrupt cleared */

    /** Retardo de rebote. */
    SysTick_Init_OneShot (Bounce_Delay);                                                            /*  Inicialización y configuración del SysTick en modo one-shot */
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)) {}                                               /*  SysTick => COUNT: Count Flag -> The SysTick timer has counted to 0 */

    /** Confirmar qué botón se presionó. */
    if (!(GPIO_PORTJ_AHB_DATA_R & 0x01)) {                                                          /*  IF (SW1 -> on) */
        counter++;
    }

    if (!(GPIO_PORTJ_AHB_DATA_R & 0x02)) {                                                          /*  IF (SW2 -> on) */
        counter--;
    }

}
