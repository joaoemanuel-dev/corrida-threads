# Requisitos para execução

Este programa foi desenvolvido em C utilizando a biblioteca POSIX Threads (pthreads).

Para compilar e executar no Windows, foi utilizado o ambiente MSYS2 UCRT64, pois ele fornece suporte adequado ao compilador gcc e à biblioteca pthread.

Ambiente utilizado
* Windows
* MSYS2 UCRT64
* GCC
* Biblioteca pthreads

## Compilação

No terminal MSYS2 UCRT64, execute:

gcc corrida.c -o corrida.exe -pthread

## Execução

Ainda no terminal MSYS2 UCRT64, execute:

./corrida.exe
