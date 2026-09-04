; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
; 
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 15:    Estructuras de control: WHILE
; Descripción:  Construcción de la estructura de control WHILE en lenguaje ensamblador.
;               Ejecución repetida de un bloque de instrucciones mientras se cumpla una condición previa.
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

while_block                                     ; Bloque WHILE
        CMP   R0, #5                            ; Condición (R0 < 5)
        BPL   while_end
        NOP
        NOP
        B     while_block

while_end                                       ; Fin del bloque WHILE
        NOP
        NOP

end     B     end
        .end
