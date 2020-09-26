# @file Makefile
# @description kullanicidan aldigimiz satir, sutun, donus yonu, kaca kadar numaralandirilacagi ve bu dondurme isleminin
# kac defa tekrarlanacagi gibi bilgilerle heap memory alaninda bir matrix olusturup donme islemi gerceklestirildikten sonra
# matrisin son hali ekrana bastirir
# @assignment Odev 1 
# @date 29.11.2019
# @author Abdussamet KACI abdussamet.kaci@stu.fsm.edu.tr 

all: matrixops

matrixops: main.o matrixops.o
	gcc main.o matrixops.o -o matrixops

main.o: main.c
	gcc -c main.c

matrixops.o: matrixOps.c matrixOps.h
	gcc -c matrixOps.c

clean:
	del *.o matrixops.exe

run:
	matrixops.exe 20 30 -1 50 2