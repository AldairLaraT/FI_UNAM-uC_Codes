; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
; 
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 16:    Estructuras de control: DO-WHILE
; Descripción:  Construcción de la estructura de control DO-WHILE en lenguaje ensamblador.
;               Ejecución de un bloque de instrucciones al menos una vez y repetición si se cumple una condición.
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
        NOP
        NOP

do_while_block                                  ; Bloque DO-WHILE
        NOP
        NOP
        CMP   R0, #5                            ; Condición (R0 < 5)
        BMI   do_while_block

        NOP                                     ; Fin del bloque DO-WHILE
        NOP

end     B     end
        .end
