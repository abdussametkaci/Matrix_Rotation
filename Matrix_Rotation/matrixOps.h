/** @file matrixOps.h
  * @description kullanicidan aldigimiz satir, sutun, donus yonu, kaca kadar numaralandirilacagi ve bu dondurme isleminin
  * kac defa tekrarlanacagi gibi bilgilerle heap memory alaninda bir matrix olusturup donme islemi gerceklestirildikten sonra
  * matrisin son hali ekrana bastirir
  * @assignment Odev 1 
  * @date 29.11.2019
  * @author Abdussamet KACI 
 */

#ifndef MATRIXOPS_H
#define MATRIXOPS_H

void rotateMatrixClockWise(int **, int, int); // saat yonunde array dondurur
void rotateMatrixCounterClockWise(int **, int, int); // saat yonunun tersi yononde array dondurur
void rotateMatrix(int **, int, int, int, int); //array i istenilen yonde dondurur
void printMatrix(int **, int, int); // array in elemanlarini basar
int** crate2DMatrix(int, int, int); // 2 boyutlu array'in referansini dondurur
void deleteHeap(int **, int); //heap memory alaninda ayrilan yer serbest birakilir

#endif
