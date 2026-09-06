; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
;
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 15:    Estructuras de control: DO-WHILE
; Descripción:  Construcción de la estructura de control DO-WHILE en lenguaje ensamblador.
;               Ejecución de un bloque de instrucciones al menos una vez y repetición si se cumple
;               una condición.
;               NOTA: Se usan instrucciones NOP para indicar el cuerpo del código o la estructura
;                     de control.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de datos
; -------------------------------------------------------------------------------------------------

        .data


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------

        .text


; -------------------------------------------------------------------------------------------------
; Apuntadores


; -------------------------------------------------------------------------------------------------
; Subrutinas


; -------------------------------------------------------------------------------------------------
; Código principal

main:

        NOP
        NOP

do_while_begin                                  ; DO-WHILE
        NOP
        NOP

    ; Condición (R0 < 5)
        CMP     R0, #5                          ; NOTA: Asignar manualmente el valor de prueba en R0 durante la depuración
        BMI     do_while_begin

do_while_end                                    ; Fin de la estructura DO-WHILE
        NOP
        NOP


halt    B       halt

        .end
