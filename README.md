# Curso de microprocesadores y Microcontroladores
Repositorio de apoyo para el curso de Microprocesadores y Microcontroladores, impartido en la Facultad de Ingeniería, UNAM.

---
# Dirigido a
Estudiantes de la Facultad de Ingeniería, UNAM, que cursan las carreras de:
- Ingeniería Eléctrica Electrónica.
- Ingeniería Aeroespacial.
- Ingeniería Mecatrónica.

---
# Contenido
- Códigos de ejemplo y ejercicios relacionados con la asignatura.
- [Manuales, presentaciones y material del curso](MATERIAL.md).

---
# Uso del repositorio
**Requisito previo:** Instalar Git.
- Windows: Descargar e instalar [Git Bash](https://git-scm.com/downloads).
- macOS: Descargar e instalar [Git Bash](https://git-scm.com/downloads/mac) o usar *Homebrew*:
```
brew install git
```
- Linux: Instalar desde el gestor de paquetes (ejemplo para Debian/Ubuntu):
```
sudo apt update && sudo apt install git
```

1. Clonar el repositorio.
```
git clone https://github.com/AldairLaraT/FI_UNAM-uC_Codes.git
```
2. Abrir *Code Composer Studio* y crear un nuevo *Workspace*.
3. Ir a `File` >> `Import` >> `Code Composer Studio` >> `CCS Projects`.
4. Seleccionar la carpeta *FI_UNAM-uC_Codes* y hacer click en `Select All`.
5. Click en `Finish`.

## Actualizar el repositorio a la versión más reciente
Dentro de la carpeta del repositorio, ejecutar:
```
git pull https://github.com/AldairLaraT/FI_UNAM-uC_Codes.git
```

---
# Contacto
**Autor:** M. I. Christo Aldair Lara Tenorio

**Correo:** aldairlara.fi@gmail.com

**Cubículo:** Laboratorio de Instrumentación Electrónica de Sistemas Espaciales (LIESE), 2do piso del edificio P, Conjunto Sur de la Facultad de Ingeniería, UNAM.

**Horario:**
| Horario         |    Lunes     | Martes  |  Miércoles   |    Jueves    | Viernes  |
|:---------------:|:------------:|:-------:|:------------:|:------------:|:--------:|
| 11:00h - 12:00h | -            | -       | -            | -            | -        |
| 12:00h - 13:00h | LIESE        | Reunión | Reunión      | LIESE        | Variable |
| 13:00h - 14:00h | Reunión      | LIESE   | LIESE        | Clase (Q106) | Variable |
| 14:00h - 15:00h | Reunión      | LIESE   | LIESE        | Clase (Q106) | Variable |
| 15:00h - 16:00h | -            | -       | -            | -            | -        |
| 16:00h - 17:00h | LIESE        | Reunión | LIESE        | LIESE        | Reunión  |
| 17:00h - 18:00h | Clase (Q102) | LIESE   | Clase (Q102) | LIESE        | Variable |
| 18:00h - 19:00h | Clase (Q102) | Reunión | Clase (Q102) | LIESE        | Variable |
| 19:00h - 20:00h | LIESE        | LIESE   | LIESE        | LIESE        | Variable |
| 20:00h - 21:00h | -            | -       | -            | -            | -        |

---
# Requisitos del curso
**IDE:** [Code Composer Studio (CCS) de Texas Instruments](https://www.ti.com/tool/download/CCSTUDIO/12.8.1).

**Versión:** 12.8.1 (Sep 30, 2024).

**Tarjeta de desarrollo:** [EK-TM4C1294XL Evaluation board](https://www.ti.com/tool/EK-TM4C1294XL).

---