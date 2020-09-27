/** @file matrixOps.c
  * @description kullanicidan aldigimiz satir, sutun, donus yonu, kaca kadar numaralandirilacagi ve bu dondurme isleminin
  * kac defa tekrarlanacagi gibi bilgilerle heap memory alaninda bir matrix olusturup donme islemi gerceklestirildikten sonra
  * matrisin son hali ekrana bastirir
  * @assignment Odev 1 
  * @date 29.11.2019
  * @author Abdussamet KACI 
 */

//kutuphaneler include edilir
#include "matrixops.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { //yon bilgisinin hangi sayiyla tanimli oldugunu unutmamak icin enum tanimlandi
	clockWise = -1, // saat yonu
	counterClockWise = 1    // saat yonun tersi
}direction;

void rotateMatrixClockWise(int **arr, int row, int column){ // saat yonunde matrix dondurur
	int num1, num2;//1. sayi ve 2.sayiyi tutmak icin degisken tanimlandi. Bu sayilar cevirme islemi icin
	//bunlarin adreslerini tutmak icin pointer tanimlandi
	int *p1 = &num1;
	int *p2 = &num2;
	*p1 = *(*(arr + 0) + 0); // 0. dizinin 0. elemani 1. sayiya atandi

	int i;
	//bu dongude 0. dizinin sonuna kadar sirayla degistirme islemi yapar
	for(i = 0; i < column - 1; i++){
		*p2 = *(*(arr + 0) + (i + 1));
		*(*(arr + 0) + (i + 1)) = *p1;
		*p1 = *p2;
	}
	//bu dongude dizilerin son sutunlari arasinda degistirme islemi yapar
	for(i = 0; i < row - 1; i++){
		*p2 = *(*(arr + (i + 1)) + (column - 1));
		*(*(arr + (i + 1)) + (column - 1)) = *p1;
		*p1 = *p2;
	}
	//bu dongude en alt satirdaki dizide degistirme islemi yapar
	//burada i'nin column - 2 de baslama sebebi bir ust dongude
	//son son sutunlarda degistirme islemi yaptigi icin en alttaki dizide de degistirme islemi uyguladi
	//bundan dolayi en alttaki dizinin sonuncu sutunundan degil de bir yanindaki olan column - 2. sutundan basladik
	for(i = column - 2; i >= 0; i--){
		*p2 = *(*(arr + (row - 1)) + i);
		 *(*(arr + (row - 1)) + i) = *p1;
		 *p1 = *p2;
		
	}
	//bu dongude dizilerin ilk sutunlari arasinda bir degistirme islemi yapmis olur
	for(i = row - 1; i > 0; i--){
		*p2 = *(*(arr + (i - 1)) + 0);
		*(*(arr + (i - 1)) + 0) = *p1;
		*p1 = *p2;
	}
	//boylelikle tum kenarlar dolasilmis olur
	
}

void rotateMatrixCounterClockWise(int **arr, int row, int column){//matrix i saat yonunun tersine cevirir
	int num1, num2;//1.sayiyi ve 2.sayiyi tutmak icin degisken tanimlandi
	//degiskenlerin adreslerinin tutulmasi icin pointer tanimlandi
	int *p1 = &num1;
	int *p2 = &num2;
	*p1 = *(*(arr + 0) + 0); // matrixin ilk elemani 1. sayiya atanir
	
	int i;
	//bu dongude dizilerin ilk sutunlari arasinda bir degistirme islemi yapmis olur
	for(i = 0; i < row - 1; i++){
		*p2 = *(*(arr + (i + 1)) + 0);
		*(*(arr + (i + 1)) + 0) = *p1;
		*p1 = *p2;
	}
	//bu dongude en alt satirdaki dizide degistirme islemi yapar
	for(i = 0; i < column - 1; i++){
		*p2 = *(*(arr + (row - 1)) + (i + 1));
		*(*(arr + (row - 1)) + (i + 1)) = *p1;
		*p1 = *p2;
	}
	//bu dongude dizilerin son sutunlari arasinda degistirme islemi yapar
	for(i = row - 1; i > 0; i--){
		*p2 = *(*(arr + (i - 1)) + (column - 1));
		*(*(arr + (i - 1)) + (column - 1)) = *p1;
		*p1 = *p2;
	}
	//bu dongude 0. dizinin basina kadar sirayla degistirme islemi yapar
	//burada column - 2 den baslama sebebi ise bir onceki dongude son sutunlar arasinda
	//degistirme islemi yapildigi icin 0. dizinin sonuncu sutunu yerine column - 2. sutundan basladik
	for(i = column - 2; i >= 0; i--){
		*p2 = *(*(arr + 0) + i);
		*(*(arr + 0) + i) = *p1;
		*p1= *p2;
	}
	//ve boylece tum kenarlarda cevirme islmi yapilmis olur
}

void rotateMatrix(int **arr, int row, int column, direction d, int stepNumber){
	if(d == clockWise){// eger secilen saat yonu ise
		int i;
		for(i = 0; i < stepNumber; i++){
			rotateMatrixClockWise(arr, row, column); // matrixi saat yonunde ceviren fonksiyon istenilen adetce cagirilir
		}

	} else if(d == counterClockWise){ // eger secilen yon saat yonunun tersi ise
		int i;
		for(i = 0; i < stepNumber; i++){
			rotateMatrixCounterClockWise(arr, row, column); // istenilen adetce saat yonunun tersine ceviren fonksiyon cagirilir
		}
		
	}
}

void printMatrix(int **arr, int row, int column){//girilen satir ve sutun bilgisine gore matrix basar
	int i, j; 
    for (i = 0; i < row; i++) {
    	for (j = 0; j < column; j++) {
    		printf("%d\t", *(*(arr + i) + j));
		}
        printf("\n");
	}
}

int** crate2DMatrix(int row, int column, int maxNumber){ // Heap'te 2D matrix olusturur ve onun referansini dondurur
	int **arr = (int **) malloc(row * sizeof(int *));// istenilen satirda yer ayrilir
	int i;
	for (i = 0; i < row; i++) {
		*(arr + i) = (int *) malloc(column * sizeof(int)); //her satir icin istenilen sutun kadar yer ayrilir
	}
         
    srand(time(NULL));
	//0'dan istenilen sayiya kadar rastgele sayi uretilir ve olusturulan matrix uzerinde dolasilip tek tek bu random sayi atilir
    for (i = 0; i < row; i++) {
    	int j;
    	for (j = 0; j < column; j++) {
      		*(*(arr + i) + j) = (rand() % (maxNumber + 1));
	    }
	}
      
	return arr;
}

void deleteHeap(int **arr, int numberOfArrays){ 
	//heap'te ayirdigimiz her satirdaki yeri ve bunlari da tutmak icin ayirdigimiz yer serbest birakilir
	int i;
	for(i = 0; i < numberOfArrays; i++){
		free(*(arr + i));
	}
	free(arr);
}
