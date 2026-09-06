; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
;
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 13:    Estructuras de control: SWITCH-CASE
; Descripción:  Construcción de la estructura de control SWITCH-CASE en lenguaje ensamblador.
;               Selección de un bloque de instrucciones entre varias opciones, a partir del valor
;               de una variable.
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

    ; Condición case1 (R0 = 1)
        CMP     R0, #1                          ; NOTA: Asignar manualmente el valor de prueba en R0 durante la depuración
        BEQ     case1

    ; Condición case2 (R0 = 2)
        CMP     R0, #2                          ; NOTA: Asignar manualmente el valor de prueba en R0 durante la depuración
        BEQ     case2

    ; Condición DEFAULT
        B       case_default

case1                                           ; case1
        NOP
        NOP

        B       switch_case_end

case2                                           ; case2
        NOP
        NOP

        B       switch_case_end

case_default                                    ; DEFAULT
        NOP
        NOP

switch_case_end                                 ; Fin de la estructura SWITCH-CASE
        NOP
        NOP


halt    B       halt

        .end
