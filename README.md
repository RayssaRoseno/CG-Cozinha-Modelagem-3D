# Modelo de Cozinha em computação gráfica

## Trabalho de computação gráfica sobre a modelagem de uma cozinha.

Para compilar, por padrão com o uso de 4 threads, utilize o comando `make build`.
Utilize `make compile` para compilar com um único thread.
Para compilar o arquivos e logo após executar o binário, utilize o comando `make run`.
Para compilar sem mensagens de log, utilize o comand `make silent <comando>`.

O programa funciona tanto no Windows quanto no Linux, mas no linux as bibliotecas devem ser instaladas utilizando o comando `sudo apt install freeglut3 freeglut3-dev`.

Os controles de movimento são com as teclas `wasd`, e o mouse.

Para movimentação vertical, utilize `barra de espaço` para ir para cima e `b` para ir para baixo.

Para abrir e fechar a portas, pressione a tecla `p` para abrir, `o` para fechar, e para abrir e fechar as janelas, pressione `l` para abrir e `m` para fechar.
    No total são 3 objetos que podem ser abertos/fechados, sendo eles duas janelas e uma porta.

Para ligar ou desligar a luminária, utilize a tecla `k`.

## Requisitos da reav. AB1

 - [:heavy_check_mark:] Poder navegar pela cozinha utilizando o mouse e teclado;
 - [:heavy_check_mark:] A cozinha deverá ter no mínimo 10 objetos (Programa usando para modelagem "Blender");
 - [:heavy_check_mark:] Uma porta deverá poder abrir e fechar com o teclado;
 - [:heavy_check_mark:] Uma janela deverá abrir e fechar como teclado;
 - [:heavy_check_mark:] 1 relógio de parede com transformações geométricas, marcando a hora, minutos e segundos;
 - [:heavy_check_mark:] Modelar o exterior da casa (cerca, árvore, jardim, mais 5 objetos);
 - [:heavy_check_mark:] Integrar a cozinha ao exterior da casa;
 - [:heavy_check_mark:] Criar um Sol e uma Lua para simular o dia e a noite usando o teclado;
 - [:heavy_check_mark:] Qualidade da modelagem.



## Referências:

* [Referência do monitor da disciplina](https://github.com/valeriojr/COMP269/blob/master/opengl.c)
* [Básicos do opengl](https://github.com/valeriojr/monitoria-cg/blob/master/material/book.pdf)
* [Camera - Getting started](https://learnopengl.com/Getting-started/Camera)
* [Viewing obj file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file)
* [Applying MSAA](https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing)
* [Textures in OpenGL](https://www.youtube.com/watch?v=n4k7ANAFsIQ)
* [Download Blender](https://www.blender.org/download/)
