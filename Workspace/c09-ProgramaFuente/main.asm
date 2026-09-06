; -------------------------------------------------------------------------------------------------
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
;
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        31 de agosto de 2025
;
; Tema 04:      Lenguaje ensamblador y el ensamblador
; Código 09:    Programa fuente vs programa objeto
; Descripción:  Comparación entre el programa fuente y el programa objeto.
;
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; -------------------------------------------------------------------------------------------------

        .global main


; -------------------------------------------------------------------------------------------------
; Sección de código ejecutable
; -------------------------------------------------------------------------------------------------

main:

        MOVW    R0, #0x0004
        MOVT    R0, #0x2000                     ; R0 = 0x2000_0004
        MOVW    R1, #0xFFFC
        MOVT    R1, #0x2003                     ; R1 = 0x2003_FFFC
        MOV     R3, #0                          ; R3 = 0

loop    LDR     R2, [R0], #4                    ; R2 = [R0], R0 = R0 + 4
        ADD     R3, R2                          ; R3 = R3 + R2

        CMP     R0, R1                          ; Comparar R0 con R1
        BNE     loop                            ; Saltar si (Z = 0)


halt    B       halt

        .end
