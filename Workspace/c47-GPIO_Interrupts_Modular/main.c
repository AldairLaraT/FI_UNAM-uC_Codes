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
 * Tarjeta de desarrollo:       EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 * Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SysTick.h"                                                                                /*  Archivo de cabecera del módulo SysTick */


/**************************************************************************************************
 * Variables globales
 */

uint32_t Bounce_Delay = 200000;                                                                     /*  Valor de carga del SysTick para un retardo de rebote de 50ms (f = 4MHz) */
int counter = 0;


/**************************************************************************************************
 * Función principal
 */

int main(void) {

    GPIO_PortF_Init();                                                                              /*  Inicialización y configuración del puerto GPIO F */
    GPIO_PortJ_Init();                                                                              /*  Inicialización y configuración del puerto GPIO J */
    GPIO_PortN_Init();                                                                              /*  Inicialización y configuración del puerto GPIO N */

    int i;

    while (1) {
        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTN_DATA_R ^= 0x02;                                                                  /*  LED D1 -> toggle */

        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTN_DATA_R ^= 0x01;                                                                  /*  LED D2 -> toggle */

        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTF_AHB_DATA_R ^= 0x10;                                                              /*  LED D3 -> toggle */

        for (i = 0; i < 700000; i++) {}                                                             /*  Retardo aproximado de 500ms */
        GPIO_PORTF_AHB_DATA_R ^= 0x01;                                                              /*  LED D4 -> toggle */
    }
}
