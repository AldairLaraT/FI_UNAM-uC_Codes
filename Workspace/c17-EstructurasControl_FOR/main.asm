; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
; 
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 17:    Estructuras de control: FOR
; Descripción:  Construcción de la estructura de control FOR en lenguaje ensamblador.
;               Ejecución repetida de un bloque de instrucciones controlada por un contador.
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
        MOV   R0, #0                            ; Inicialización (i = 0)

for_block                                       ; Bloque FOR
        CMP   R0, #5                            ; Condición (i < 5)
        BEQ   for_end
        ADD   R0, #1                            ; Actualización (i++)
        NOP
        NOP
        B     for_block

for_end                                         ; Fin del bloque FOR
        NOP
        NOP

end     B     end
        .end
