; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        17 de septiembre de 2025
;
; Tema 05:      Programación estructurada en lenguaje ensamblador
; Código 12:    Estructuras de control: IF-ELSE
; Descripción:  Construcción de la estructura de control IF-ELSE en lenguaje ensamblador.
;               Selección entre dos bloques de instrucciones, a partir del cumplimiento de una
;               condición.
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

    ; Condición (R0 = 5)
        CMP     R0, #5                          ; NOTA: Asignar manualmente el valor de prueba en R0 durante la depuración
        BNE     else

if_begin                                        ; IF
        NOP
        NOP

        B       if_end

else                                            ; ELSE (R0 != 5)
        NOP
        NOP

if_end                                          ; Fin de la estructura IF-ELSE
        NOP
        NOP


halt    B       halt

        .end
