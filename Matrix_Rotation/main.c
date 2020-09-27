/** @file main.c
  * @description kullanicidan aldigimiz satir, sutun, donus yonu, kaca kadar numaralandirilacagi ve bu dondurme isleminin
  * kac defa tekrarlanacagi gibi bilgilerle heap memory alaninda bir matrix olusturup donme islemi gerceklestirildikten sonra
  * matrisin son hali ekrana bastirir
  * @assignment Odev 1 
  * @date 29.11.2019
  * @author Abdussamet KACI
 */

//kutuphaneler include edilir
#include <stdio.h>
#include "matrixops.h"

void executeMenu(int **, int *, int *, int *, int *, int *); //menuyu calistirmak icin bir prototip tanimladim
void showMenu(); //menudeki secenekleri yazdirmak icin bir prototip tanimladim
int hasCharacter(char *); //kullanicidan alinan verilerin karakter olup olmadigini kontrol etmek icin bir prototip

int main(int argc, char *argv[]){

    //command line'dan girilecek verileri saklamak icin degiskenler tanimlandi
    int row;        //atoi(*(argv + 1));
    int column;     //atoi(*(argv + 2));
    int direction;  //atoi(*(argv + 3));
    int maxNumber;  //atoi(*(argv + 4));
    int stepNumber; //atoi(*(argv + 5));
    //----------------------------
    //bu degiskenlerin adreslerini tutmak icin pointer tanimlandi
    //ve ayrica olusturulacak iki boyutlu array icin **arr tanimlandi 
    int **arr; // array'in kisaltilmis hali (matrix)
    int *pRow = &row;
    int *pColumn = &column;
    int *pDirection = &direction;
    int *pMaxNumber = &maxNumber;
    int *pStepNumber = &stepNumber;
    //---------------------------------

    int commandLineSorunVarmi = 0; //command line'dan alinan verilerde problem olup olmadigi bilgisini tutmak icin tanimlandi

    //eger arguman sayisi 6 degilse command line'a eksik arguman girilmistir
    //ve islem yerine getirilemeyip menu acilir
    if(argc != 6){ 
        printf("arguman sayisi uyusmuyor!\n");
        printf("menuden tekrar isleminizi yapabilirsiniz\n");
        commandLineSorunVarmi = 1;
        
    } 

    if (!commandLineSorunVarmi){ // arguman sayisinda problem yok ise sayi disinda bir şey girilmisse islem yapilmaz ve menu calisir
        int i; // sayac
        char *argument; //command line'da girilen argumanlarin adresini tutmak icin degisken
        for(i = 1; i < argc; i++){
            argument = *(argv + i); //i. elemanin adresi atanir
            if(i == 3){ // 3.argumana geldiginde ise yon mu degil mi diye bakiyor
            //burada hasCharacter fonksiyonuna gelen argumanin basi eger - isareti ise bir yandan baslattim cunku - isareti de bir
            //karakter oldugu icin uyari mesaji verir sistemimiz ancak biz bir yaninda baslattik ki sorun olmasin
            //bundan  dolayi 3. arguman icin ekstra bir kontrol yazdim
                if(*(argument + 0) == '-' && hasCharacter(argument + 1)){
                    printf("lutfen sadece sayi kullaniniz!\n");
                    commandLineSorunVarmi = 1;
                    break;
                } else if(*(argument + 0) == '1' && hasCharacter(argument + 1)){
                    //bu blok ise önünde 1 ancak ondan sonra karakter girilebilecek ihtimallere karsi yazilmistir
                    printf("lutfen sadece sayi kullaniniz!\n");
                    commandLineSorunVarmi = 1;
                    break;
                } else if(atoi(argument) != 1 && atoi(argument) != -1){
                    //bu blok ise yukaridaki bloklara girmeyip ancak baska rakamlarin girmesine karsi yazildi
                    printf("yon bilgisi sadece 1 ve -1 olabilir!\n");
                    commandLineSorunVarmi = 1;
                    break;
                }

                continue;
            }

            if(hasCharacter(argument)){ //diger argumanlarda karakter girilmisse uyari verir
                printf("lutfen karakter veya negatif sayi kullanmayiniz\n");
                printf("lutfen menuden isleminizi tekrar deneyiniz\n");
                commandLineSorunVarmi = 1;
                break;
            }
        }

    } 

    if(!commandLineSorunVarmi){ //eger buraya kadar bir sikinti yoksa bu sefer girilen satir ve sutun degerleri kontrol edilir
        if(atoi(*(argv + 1)) < 2 || atoi(*(argv + 2)) < 2){ //matrix olması için minimum 2x2 olmalı
            printf("sutun veya satir sayisi minimum 2 olmalidir.\n");
            printf("menude isleminizi tekrar gercklestirebilirsiniz\n");
            commandLineSorunVarmi = 1;
        }

    }
    
    //eger buraya kadar command line'da bir sorun yok ise program calistirilir
    if(!commandLineSorunVarmi){
        //command line parametreleri atanir
        *pRow = atoi(*(argv + 1));
        *pColumn = atoi(*(argv + 2));
        *pDirection = atoi(*(argv + 3));
        *pMaxNumber = atoi(*(argv + 4));
        *pStepNumber = atoi(*(argv + 5));

        arr = crate2DMatrix(row, column, maxNumber); //2d array olusturulur

        printf("olusturulan dizi: \n");
        printMatrix(arr, row, column); //olusturulan dizi ekrana bastirilir
        printf("donderilen dizi: \n");
        rotateMatrix(arr, row, column, direction, stepNumber); //matris dondurulur
        printMatrix(arr, row, column); //dondurulen matris basilir
        deleteHeap(arr, row); //heap memory alani serbest birakilir
    } 

    printf("menu aciliyor...\n");

    executeMenu(arr, pRow, pColumn, pMaxNumber, pDirection, pStepNumber); //menu calistirilir

    return 0;
}

void executeMenu(int **array, int *row, int *column, int *maxNumber, int *direction, int *stepNumber){
    //2-3-4. secenekteki islemlerin tamamlanip tamamlanmadigi bilgisi tutulur
    int islem2YapildiMi = 0;
    int islem3YapildiMi = 0;
    int islem4YapildiMi = 0;

    while(1){

        char girdi[1000]; //kullanicinin girebilecegi maksimum data buyukluğu 1000 byte'dir diye kabul ediyorum
        showMenu();//menu secenekleri ekrana basilir
        scanf("%s", &girdi);//kullanicidan hangi islemi yapacagi bilgisi alinir
        
        if(hasCharacter(girdi)){ // eger karakter girerse kullaniciya mesaj gosterilir. Sonra tekrar menuye gelir
            printf("gecersiz islem.Lutfen tekrar deneyiniz!\n");
            continue;
        }

        if(atoi(girdi) == 1){ //eger secilen islem 1 ise

            if(!(islem2YapildiMi && islem3YapildiMi && islem4YapildiMi)){ 
                //kullanici 2., 3. ve 4. islemleri yerine getirmediyse eger, mesaj gosterilir ve menu terar acilir
                printf("uygulamayi calistirmak icin matris olusturup direction ve step number bilgilerini girmeniz gerek!\n");
                continue;
            }
            //eger kullanici 2., 3. ve 4. islemleri yerine getirdiyse uygulama calistirilir
            printf("olusturulan matris: \n");
            printMatrix(array, *row, *column);//olusturulan array ekrana basilir
            printf("dondurulen matris: \n");
            rotateMatrix(array, *row, *column, *direction, *stepNumber);//olusturulan array dondurulur
            printMatrix(array, *row, *column);//dondurulen array ekrana basilir
            deleteHeap(array, *row); //heap memory alani serbest birakilir

            //sonra tum islmeler yapildi olarak ayarlanir ki eger kullanici bir daha 1'e basarsa uygulama calismasin diye
            //cunku heap'te yer ayrilan alan serbest birakildi
            islem2YapildiMi = 0;
            islem3YapildiMi = 0;
            islem4YapildiMi = 0;

        } else if(atoi(girdi) == 2){ // eger kullanici 2'yi sectiyse matris olusturulur

            if(islem2YapildiMi){
                 // eger kullanici daha once bir matrix olusturmus ve sonra baska boyutlarda tekrardan
                 //yeni bir matrix tanimlamak istiyorsa onceki heap alanini serbest birakmak gerekir
                 //ve kulanicidan yeniden aldigimiz verilerle yeni metrix olusturulur(bu blogun sonunda)
                deleteHeap(array, *row);
            }

            //bu dongude kullanicidan satir bilgisi alinir
            while(1){
                printf("Lutfen satir sayisini giriniz:\n");
                scanf("%s", girdi);//girdi istenir

                if(hasCharacter(girdi)){ // eger girdi karakter ise mesaj gosterilir ve basa donulur
                    printf("satir sayisi karakter veya negatif bir sayi olamaz!\nLutfen tekrar deneyiniz!\n");
                    continue;
                } else if(atoi(girdi) < 2){ // eger satir sayisi 2 den kucukse mesaj gosterilip basa doner
                    printf("satir sayisi 2 den kucuk olmamali!\nLutfen tekrar deneyiniz!\n");
                    continue;
                } else{ //sorun yoksa satir bilgisi atanir
                    *row = atoi(girdi);
                    break;
                }
            }
            
            //bu dongude kullanicidan sutun bilgisi alinir
            while(1){

                printf("Lutfen sutun sayisini giriniz:\n");
                scanf("%s", girdi);//girdi istenir

                if(hasCharacter(girdi)){ // eger girdi karakter ise mesaj gosterilir ve basa doner
                    printf("sutun sayisi karakter veya negatif bir sayi olamaz!\nLutfen tekrar deneyiniz!\n");
                    continue;
                } else if(atoi(girdi) < 2){ // eger girdi 2 den kucukse mesaj gosterilir ve kullanicidan bir daha istenir
                    printf("sutun sayisi 2 den kucuk olmamali!\nLutfen tekrar deneyiniz!\n");
                    continue;
                } else {//sorun yoksa girdi bilgisi atanir
                    *column = atoi(girdi);
                    break;
                }
            }

           //bu dongude kullanicidan matrixin 0'dan kaca kadar numaralandirilacagi bilgisi istenir 
            while(1){

                printf("Matrisiniz 0 ile kac arasinda olsun:\n");
                scanf("%s", girdi);//girdi istenir

                if(hasCharacter(girdi)){ // eger girdi karakter ise mesaj gosterilir ve kullanicidan tekrar sayi istenir
                    printf("girdi sayisi karakter veya negatif bir sayi olamaz!\nLutfen tekrar deneyiniz!\n");
                    continue;
                } else { //sorun yoksa sayi atanir
                    *maxNumber = atoi(girdi);
                    break;
                }
            }

            //tum bu islemler bittikten sonra matrix olusturulur
            array = crate2DMatrix(*row, *column, *maxNumber);
            islem2YapildiMi = 1; // islem 2 yapildi
            printf("\n");
            printMatrix(array, *row, *column); //matrix ekrana basilir
            printf("matrisiniz olustruruldu!\n");
            
        } else if(atoi(girdi) == 3){ // eger secilen islem 3 ise

            //bu dongude yon bilgisi istenir
            while(1){
                printf("Lutfen yon bilgisini giriniz:\n");
                scanf("%s", girdi);//girdi istenir

                if(*(girdi + 0) == '-' && hasCharacter(girdi + 1)){
                    printf("lutfen sadece sayi kullaniniz!\nYon bilgisi sadece 1 ve -1 olabilir!\n");
                    continue;
                } else if(*(girdi + 0) == '1' && hasCharacter(girdi + 1)){
                    //bu blok ise önünde 1 ancak ondan sonra karakter girilebilecek ihtimallere karsi yazilmistir
                    printf("lutfen sadece sayi kullaniniz!\nYon bilgisi sadece 1 ve -1 olabilir!\n");
                    continue;
                } else if(atoi(girdi) != 1 && atoi(girdi) != -1){ //yon bilgisi 1 veya -1 degilse mesaj bastirilir ve tekar istenir
                    printf("yon bilgisi sadece 1 veya -1 olabilir!\nLutfen tekrar giriniz!\n");
                    continue;
                } else { //sorun yoksa atanir
                    *direction = atoi(girdi);
                    break;
                }
            }
            islem3YapildiMi = 1;//islem 3 yapildi
            printf("yon bilgisi girildi!\n");            

        } else if(atoi(girdi) == 4){ // eger kullanici 4'u sectiyse 
            //bu dongude kullanicidan adim sayisi istenir
            while (1) {
                printf("Lutfen adim sayisini giriniz:\n");
                scanf("%s", girdi); //girdi istenir

                if(hasCharacter(girdi)){ // eger karakter girilmisse mesaj gosterilir ve tekrar istenir
                    printf("adim sayisi karakter veya negatif bir sayi olamaz!\nLutfen tekrar deneyiniz!\n");
                    continue;
                } else {//sorun yoksa atanir
                    *stepNumber = atoi(girdi);
                    break;
                }
            }

            islem4YapildiMi = 1;//islem 4 yapildi
            printf("adim sayisi girildi!\n");

        } else if(atoi(girdi) == 5){ // eger kullanici 5 seceneğini secmisse

            if(islem2YapildiMi){//islem 2 yapilmissa yani matrix olusturulmus ise heap memory alani serbest birakilir
            //bunu yapmamin sebebi kullanici matrixi olusturduktan sonra dondurme islemini yapmayip
            //direkt cikmak isteyebilir
                deleteHeap(array, *row);//heap serbest birakilir
                printf("heap memory alani temizleniyor...\n");
            }

            printf("program kapatiliyor...\n");

            break;

        } else { // eger bu islemler disinda bir sey girilmisse uyari verir ve tekrar secenek secmesi istenir
            printf("gecersiz islem!\nLutfen tekrar deneyiniz!\n");
            continue;
        }
        
    }
}

void showMenu(){ // menuyu bastirmak icin tanimlandi
	printf("Lutfen yapmak istediginiz islemi seciniz!\n");
	printf("1. Uygulamayi calistir\n");
	printf("2. Matris olustur\n");
	printf("3. Direction\n");
	printf("4. Step number\n");
	printf("5. Exit\n");
}

int hasCharacter(char *str){//girilen degerin icinde karakter olup olmadigini kontrol eder
	int i = 0;
	while(*(str + i) != '\0'){
		if(!(*(str + i) >= '0' && *(str + i) <= '9')){
			return 1;
		}
		i++;
	}

	return 0;
}
