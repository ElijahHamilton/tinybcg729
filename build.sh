#!/bin/sh
gcc -Icodec/ encoder.c codec/*.c -o encoder
gcc -Icodec/ decoder.c codec/*.c -o decoder
