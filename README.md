![Static Badge](https://img.shields.io/badge/estabilidad-ALPHA-3314333)

# <p align="center"> Salero MdN </p>

<div align="center">

_Hecho con_

[![made-for-VSCode](https://img.shields.io/badge/Hecho%20con-VSCode-1f425f.svg)](https://code.visualstudio.com/) [![Build with PlatformIO](https://img.shields.io/badge/Compilado%20con-PlatformIO-orange?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzkzLjgxIDAgNjEuNjY2IDEzLjMxNCAzNy40OSAzNy40OSAxMy4zMTQgNjEuNjY2IDAgOTMuODEgMCAxMjhjMCAzNC4xOSAxMy4zMTQgNjYuMzM0IDM3LjQ5IDkwLjUxQzYxLjY2NiAyNDIuNjg2IDkzLjgxIDI1NiAxMjggMjU2YzM0LjE5IDAgNjYuMzM0LTEzLjMxNCA5MC41MS0zNy40OUMyNDIuNjg2IDE5NC4zMzQgMjU2IDE2Mi4xOSAyNTYgMTI4YzAtMzQuMTktMTMuMzE0LTY2LjMzNC0zNy40OS05MC41MUMxOTQuMzM0IDEzLjMxNCAxNjIuMTkgMCAxMjggMCIgZmlsbD0iI0ZGN0YwMCIvPjxwYXRoIGQ9Ik0yNDkuMzg2IDEyOGMwIDY3LjA0LTU0LjM0NyAxMjEuMzg2LTEyMS4zODYgMTIxLjM4NkM2MC45NiAyNDkuMzg2IDYuNjEzIDE5NS4wNCA2LjYxMyAxMjggNi42MTMgNjAuOTYgNjAuOTYgNi42MTQgMTI4IDYuNjE0YzY3LjA0IDAgMTIxLjM4NiA1NC4zNDYgMTIxLjM4NiAxMjEuMzg2IiBmaWxsPSIjRkZGIi8+PHBhdGggZD0iTTE2MC44NjkgNzQuMDYybDUuMTQ1LTE4LjUzN2M1LjI2NC0uNDcgOS4zOTItNC44ODYgOS4zOTItMTAuMjczIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzJzLTEwLjMyIDQuNjItMTAuMzIgMTAuMzJjMCAzLjc1NSAyLjAxMyA3LjAzIDUuMDEgOC44MzdsLTUuMDUgMTguMTk1Yy0xNC40MzctMy42Ny0yNi42MjUtMy4zOS0yNi42MjUtMy4zOWwtMi4yNTggMS4wMXYxNDAuODcybDIuMjU4Ljc1M2MxMy42MTQgMCA3My4xNzctNDEuMTMzIDczLjMyMy04NS4yNyAwLTMxLjYyNC0yMS4wMjMtNDUuODI1LTQwLjU1NS01Mi4xOTd6TTE0Ni41MyAxNjQuOGMtMTEuNjE3LTE4LjU1Ny02LjcwNi02MS43NTEgMjMuNjQzLTY3LjkyNSA4LjMyLTEuMzMzIDE4LjUwOSA0LjEzNCAyMS41MSAxNi4yNzkgNy41ODIgMjUuNzY2LTM3LjAxNSA2MS44NDUtNDUuMTUzIDUxLjY0NnptMTguMjE2LTM5Ljc1MmE5LjM5OSA5LjM5OSAwIDAgMC05LjM5OSA5LjM5OSA5LjM5OSA5LjM5OSAwIDAgMCA5LjQgOS4zOTkgOS4zOTkgOS4zOTkgMCAwIDAgOS4zOTgtOS40IDkuMzk5IDkuMzk5IDAgMCAwLTkuMzk5LTkuMzk4em0yLjgxIDguNjcyYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDkgMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OXoiIGZpbGw9IiNFNTcyMDAiLz48cGF0aCBkPSJNMTAxLjM3MSA3Mi43MDlsLTUuMDIzLTE4LjkwMWMyLjg3NC0xLjgzMiA0Ljc4Ni01LjA0IDQuNzg2LTguNzAxIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzItNS42OTkgMC0xMC4zMTkgNC42Mi0xMC4zMTkgMTAuMzIgMCA1LjY4MiA0LjU5MiAxMC4yODkgMTAuMjY3IDEwLjMxN0w5NS44IDc0LjM3OGMtMTkuNjA5IDYuNTEtNDAuODg1IDIwLjc0Mi00MC44ODUgNTEuODguNDM2IDQ1LjAxIDU5LjU3MiA4NS4yNjcgNzMuMTg2IDg1LjI2N1Y2OC44OTJzLTEyLjI1Mi0uMDYyLTI2LjcyOSAzLjgxN3ptMTAuMzk1IDkyLjA5Yy04LjEzOCAxMC4yLTUyLjczNS0yNS44OC00NS4xNTQtNTEuNjQ1IDMuMDAyLTEyLjE0NSAxMy4xOS0xNy42MTIgMjEuNTExLTE2LjI4IDMwLjM1IDYuMTc1IDM1LjI2IDQ5LjM2OSAyMy42NDMgNjcuOTI2em0tMTguODItMzkuNDZhOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTkgOS4zOTggOS4zOTkgOS4zOTkgMCAwIDAgOS40IDkuNCA5LjM5OSA5LjM5OSAwIDAgMCA5LjM5OC05LjQgOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTktOS4zOTl6bS0yLjgxIDguNjcxYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDggMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OHoiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=)](https://platformio.org/)

## Salero que detecta su propio uso y enciende un LED durante un tiempo de cortesía para recordar no añadir más sal a la comida

</div>

<div align="justify">

___

## Modo de funcionamiento
1. Se enciende el salero
1. El LED estará apagado, esperando a que el salero sea agitado
1. Cuando se haga uso, el LED se encenderá y se activará el modo sleep durante el tiempo que el usuario vea conveniente
1. Se apaga el LED y vuelta a esperar a ser usado

___

</div>

## <p align="justify">  Lista de componentes </p>

<div align="center">

| Componente | Unidades |
| ------------- | ------------- |
| Arduino NANO | 1 |
| Protoboard | 1 |
| Botón de inclinación | 1 |
| Botón | 1 |
| LED verde | 1 |
| LED amarillo | 1 |
| LED rojo | 1 |
| Resistencias 2K2 | 3 |
| Batería 18650 | 1 |
| Porta-batería | 1 |
| TP4056 | 1 |
| Jumpers | Los que hagan falta |

</div>

<div align="justify">

___

## Diagrama de conexiones

A continuación, se muestra el diagrama de conexiones:

</div>

<div align="center">
  <img src="https://github.com/99danirmoya/Salero-MdN/blob/main/pics/salero_schematic.jpg" width="750"  style="margin: 10px;"/>
  
  <em>Salero memorístico</em>
</div>
<br/>

<div align="justify">

___

### <p align="justify"> Flujograma (¡Simplificado!) [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/droneloraminiairqualitystation/blob/main/README.md#%C3%ADndice) </p>

```mermaid
graph TD;
  A[Configuración inicial] -->|1| B(LEDs apagados)
  B -->|2| C(¿Eché sal?)
  C -->|3| D(Sí)
  C -->|4| E(No)
  E -->|5| G(Me voy a dormir)
  G -->|6| B
  D -->|6| H(Enciendo el primer LED)
  H -->|7| I(¿Eché sal en menos de 1 hora?)
  I -->|8| J(Sí)
  I -->|9| K(No)
  K -->|10| G
  J -->|11| L(Enciendo el primer y segundo LED)
  L -->|12| M(¿Eché sal en menos de 1 hora?)
  M -->|13| N(Sí)
  M -->|14| O(No)
  N -->|15| P(Enciendo los 3 LEDs)
  O -->|16| G
  P -->|17| R(Pasa 1 hora)
  R -->|18| B
  
```

___

## Carcasa a medida

  <div align="center">
    <img src="https://github.com/99danirmoya/Salero-MdN/blob/main/pics/Screenshot%202024-03-11%20191934.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>
  <div align="center">
    <img src="https://github.com/99danirmoya/Salero-MdN/blob/main/pics/Screenshot%202024-03-11%20191914.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>
  <div align="center">
    <img src="https://github.com/99danirmoya/Salero-MdN/blob/main/pics/Screenshot%202024-03-11%20191955.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

___

## <p align="justify"> Modo de implementación </p>

<div align="justify">

Toda la explicación del código de Arduino viene dada en el propio código en formato de comentarios al lado de cada línea, [`99danirmoya/Salero-MdN/blob/main/src/main.cpp`](https://github.com/99danirmoya/Salero-MdN/blob/main/src/main.cpp), en formato de comentarios al lado de cada línea

</div>

___
___

## <p align="justify"> Licencia </p>

<div align="justify">

Este proyecto está licenciado bajo la [GPL-3.0 license](https://github.com/99danirmoya/turtle-bot-neo?tab=GPL-3.0-1-ov-file).

</div>

___

## <p align="justify"> Contacto </p>

> [!IMPORTANT]
> Respondo amablemente a dudas y leo sugerencias: [![Gmail Badge](https://img.shields.io/badge/-Gmail-c14438?style=for-the-badge&logo=Gmail&logoColor=white&link=mailto:daniel.rodriguezm99@gmail.com)](mailto:daniel.rodriguezm99@gmail.com)
> 
> Más información sobre mis proyectos: [![Linkedin Badge](https://img.shields.io/badge/-LinkedIn-blue?style=for-the-badge&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/daniel-rodr%C3%ADguez-moya-510a35167)](https://www.linkedin.com/in/daniel-rodr%C3%ADguez-moya-510a35167)

_<p align="justify"> Autor: Daniel Rodríguez Moya :shipit: </p>_
