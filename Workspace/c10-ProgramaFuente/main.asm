; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        31 de agosto de 2025
; 
; Tema 04:      Lenguaje ensamblador y el ensamblador
; Código 10:    Programa fuente vs programa objeto
; Descripción:  Comparación entre el programa fuente y el programa objeto.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

main:
        MOVW  R0, #0x0004
        MOVT  R0, #0x2000                       ; R0 = 0x2000.0004
loop    LDR   R1, [R0], #4                      ; R1 = [R0], R0 = R0 + 4
        ADD   R2, R1                            ; R2 = R2 + R1
        B     loop                              ; Saltar a loop

        .end
