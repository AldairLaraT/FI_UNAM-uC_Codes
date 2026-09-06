; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
;
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 16:    Estructuras de control: FOR
; Descripción:  Construcción de la estructura de control FOR en lenguaje ensamblador.
;               Ejecución repetida de un bloque de instrucciones controlada por un contador.
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

    ; Inicializar el contador (i = 0)
        MOV     R0, #0

for_begin                                       ; FOR
    ; Condición (i < 5)
        CMP     R0, #5
        BEQ     for_end

        NOP
        NOP

    ; Actualizar el contador (i++)
        ADD     R0, #1

        B       for_begin

for_end                                         ; Fin de la estructura FOR
        NOP
        NOP


halt    B       halt

        .end
