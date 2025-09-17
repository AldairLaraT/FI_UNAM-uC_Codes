; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        24 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 03:    Instrucciones básicas del ARM Cortex-M | LDR
; Descripción:  Uso básico de la instrucción LDR.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

main:
        MOV   R0, #0x20000000                   ; R0 = 0x2000.0000
        LDR   R1, [R0]                          ; R1 = [R0]     = [0x2000.0000]         R0 = 0x2000.0000
        LDR   R2, [R0, #4]                      ; R2 = [R0 + 4] = [0x2000.0004]         R0 = 0x2000.0000
        LDR   R3, [R0, #8]!                     ; R3 = [R0 + 8] = [0x2000.0008]         R0 = 0x2000.0008
        LDR   R4, [R0], #4                      ; R4 = [R0]     = [0x2000.0008]         R0 = 0x2000.000C

end     B     end
        .end
