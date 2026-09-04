; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
; 
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 14:    Estructuras de control: SWITCH-CASE
; Descripción:  Construcción de la estructura de control SWITCH-CASE en lenguaje ensamblador.
;               Selección de un bloque de instrucciones entre varias opciones, a partir del valor de una variable.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de datos
; ***********************************************

        .data


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

        .text


; ***********************************************
; Apuntadores


; ***********************************************
; Subrutinas


; ***********************************************
; Código principal

main:
        CMP   R0, #1                            ; Condición del case1 (R0 = 1)
        BEQ   case1
        CMP   R0, #2                            ; Condición del case2 (R0 = 2)
        BEQ   case2
        B     case_default

case1                                           ; Bloque case1
        NOP
        NOP
        B     switch_end

case2                                           ; Bloque case2
        NOP
        NOP
        B     switch_end

case_default                                    ; Bloque DEFAULT
        NOP
        NOP

switch_end                                      ; Fin del bloque CASE
        NOP
        NOP

end     B     end
        .end
