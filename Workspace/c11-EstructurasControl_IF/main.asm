; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
; 
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 12:    Estructuras de control: IF
; Descripción:  Construcción de la estructura de control IF en lenguaje ensamblador.
;               Ejecución de un bloque de instrucciones solo si se cumple una condición.
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
        CMP   R0, #5                            ; Condición (R0 = 5)
        BNE   if_end

if_block                                        ; Bloque IF
        NOP
        NOP

if_end                                          ; Fin del bloque IF
        NOP
        NOP

end     B     end
        .end
