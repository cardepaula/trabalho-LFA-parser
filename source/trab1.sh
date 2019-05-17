#!/bin/bash

mkdir ./binario

gcc -Wall -pedantic ./mel_parser.c ./main.c -o ./binario/main.bin -lm

./binario/main.bin