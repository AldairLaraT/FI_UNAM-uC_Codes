; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        24 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 01:    Instrucciones básicas del ARM Cortex-M | MOV
; Descripción:  Uso básico de la instrucción MOV.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************

        .global main


; *************************************************************************************************
; Sección de código ejecutable
; ***********************************************

main:
        MOV   R0, #100                          ; R0 = 100
        MOV   R1, #0x64                         ; R1 = 0x64 = 100
        MOV   R2, R1                            ; R2 = 100
        MOV   R3, #65535                        ; R3 = 65,535
        MOV   R4, #0xF41A                       ; R4 = 0xF41A = 62,490

end     B     end
        .end
