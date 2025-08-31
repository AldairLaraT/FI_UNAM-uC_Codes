; *************************************************************************************************
; Universidad Nacional Autónoma de México (UNAM)
; Facultad de Ingeniería | Departamento de Electrónica
; 
; Asignatura:   Microprocesadores y Microcontroladores
; Profesor:     M.I. Christo Aldair Lara Tenorio
; Fecha:        24 de agosto de 2025
; 
; Tema 03:      Modos de direccionamiento y conjunto de instrucciones
; Código 02:    Instrucciones básicas del ARM Cortex-M | ADD
; Descripción:  Uso básico de la instrucción ADD.
; 
; Tarjeta de desarrollo:        EK-TM4C1294XL Evaluation board
; ***********************************************


; *************************************************************************************************
; Sección de directivas
; ***********************************************

        .global main


; *************************************************************************************************
; Sección del código principal
; ***********************************************

main:

        MOV   R0, #100                          ; R0 = 100
        ADD   R1, R0, #28                       ; R1 = R0 + 28 = 100 + 28 = 128
        ADD   R2, R1, R0                        ; R2 = R1 + R0 = 128 + 100 = 228
        ADD   R3, R2, #0x03FF                   ; R3 = R2 + 0x03FF = 228 + 0x03FF = 1251

end     B     end
        .end
