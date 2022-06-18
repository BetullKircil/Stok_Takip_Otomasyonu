#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define URUNTIPI "ADIDAS(1)\n1-Ayakkabi (001)\n2-Esofman (002)\n\nNIKE(2)\n1-Ceket (011)\n2-Tayt (012)\n"   //Magazanin tedarik edecegi urun listesini sabit olarak tanimladik.
enum kategori{    //Urunler icin marka kategorisini enum tipinde belirledik.
	adidas = 1,
	nike
};

enum karar{      //Magaza, tedarikci firmadan urun tedarik ederken urun talebine devam etmek isteyip istemedigini 'karar' enumi araciligi ile aldigimiz cevapla kontrol ettik.
	hayir, 
	evet
};

enum sehir{      //Tedarikci bilgileri arasinda olan sehir kategorisini enum olarak tanimladik.
	izmir = 35,
	ankara = 6,
	mugla = 48,
	istanbul = 34,
	aydin = 9,
	diyarbakir = 21
};

typedef struct{         //Farkli tipteki tedarikci firma bilgilerini struct yapisi ile tanimladik.
	char tedAdi[50];
	int tedNo;
	enum sehir plaka;   //Tedarikci firmanin sehir bilgisini alabilmek icin sehir enumindan plaka degiskenini turettik.
	char adres[50];
}firma;

typedef struct{             //Tedarik edilecek ve satisi gerceklestirilecek olan farkli tipteki urunlerin genel bilgilerini struct yapisi ile tanimladik.
	enum kategori marka;    //Urunlerin marka bilgisini alabilmek icin yukarida tanimladigimiz kategori enumini structin icinde turettik.
	char urunAdi[10];
	int urunKodu;
	float satisFiyati;
	int stokMiktari;
	int tedarikciNo;
	int alisMiktari;
	float alisFiyati;
	char tarih[10];
}urun;

typedef struct{ 
	firma TedarikciFirma;   
	urun TalepEdilenUrun;       
	int tedarikciNo;
	int alisMiktari;
	float alisFiyati;
	char tarih[10];
}stokGirisi;


void sor(urun talep[], int boyut){ 
	char c;
	stokGirisi urun;
	int k = 0, stokMiktari;
	for(;;){
		printf(URUNTIPI);
		printf("Talep ettiginiz %d. urunun markasini giriniz: \n", k+1);
		scanf("%d", &talep[k].marka);
		printf("Talep ettiginiz %d. urunun adini giriniz: \n", k+1);
		scanf("%s", talep[k].urunAdi);
		printf("Talep ettiginiz %d. urunun kodunu giriniz: \n", k+1);
		scanf("%d", &talep[k].urunKodu);
		k++;
		printf("Cikmak icin 'E/e' tusuna basiniz...\n");
		c = getch();
		if(c == 'E' || c == 'e'){
			printf("Sistemden cikiliyor...\n");
			break;
		}
		printf("\n");
	}
	stokMiktari = k;
}

void StokGuncelle(int alinanUrunSayisi){
	int *yeniStok;
	yeniStok = (int*)malloc(alinanUrunSayisi*sizeof(int));
	if(yeniStok==NULL){
		printf("Stok yapilamiyor...\n");
	}
	else{
		printf("Stok guncellenmistir...\n");
	}
} 

 faturaKes( urun a[],int miktar){
 time_t time_1970;
 int k = 0;
    time_1970 = time(NULL);
    /* Yerel zamaný doðrudan ctime() fonksiyonu ile ekrana yazma */
    /* ctime() = localtime() + asctime() */
    printf("Islem hyapilan ürün bilgileri:\n");
    for(k = 0; k< miktar; k++){
        printf("%d %s %s %d\n",a[k].urunKodu,a[k].marka,a[k].urunAdi,a[k].satisFiyati);
    }
    printf("Islem zamani: %s", ctime(&time_1970));
}

void StokAkisKaydet(FILE *pfile, urun urunler[], int boyut){
 	int i, k = 0;
 	if((pfile = fopen("stokHareketleri.txt", "w"))==NULL){
 		exit(1);
	 }
	 else{
	 	for(i= 0;i < 4; i++){
	 		fprintf(pfile, "%d %s %d %f %d %s", urunler[i].marka, urunler[i].urunAdi, urunler[i].urunKodu, urunler[i].satisFiyati, urunler[i].stokMiktari, urunler[i].tarih);
		 }
	 }
 }
 
 void StokAkisListele(FILE *pfile, urun urunler[], int boyut){
 	int i;
 	if((pfile = fopen("stokHareketleri.txt", "r"))==NULL){
 		exit(1);
	 }
	 else{
	 	for(i= 0;i < 4; i++){
	 		fscanf(pfile, "%d %s %d %f %d", &urunler[i].marka, urunler[i].urunAdi, &urunler[i].urunKodu, &urunler[i].satisFiyati, &urunler[i].stokMiktari, urunler[i].tarih);
	 		printf("Urun markasi: %d\nUrun adi: %s\nUrun kodu: %d\nSatis fiyati: %.2f\nStok miktari: %d\nTarih: %s\n", urunler[i].marka, urunler[i].urunAdi, urunler[i].urunKodu, urunler[i].satisFiyati, urunler[i].stokMiktari, urunler[i].tarih);
		 }
	 }
 }
 


void tedarikEt(urun urunler[], int boyut){    //Magaza urun tedarik etmek istedigi takdirde urun bilgisini alacak olan fonksiyon.									
	enum karar cevap;						
	urun TalepEdilenUrun[4];
	int k = 0, *stoktakiUrun, alinanUrunSayisi = 0;
	for(;;){
		printf(URUNTIPI);
		printf("Firmadan talep ettiginiz %d. urunun markasini giriniz: \n", k+1);
		scanf("%d", &urunler[k].marka);
		printf("Firmadan talep ettiginiz %d. urunun adini giriniz: \n", k+1);
		scanf("%s", &urunler[k].urunAdi);
		printf("Firmadan talep ettiginiz %d. urunun kodunu giriniz: \n", k+1);
		scanf("%d", &urunler[k].urunKodu);
		printf("Firmadan talep ettiginiz %d. urunun alis miktarini giriniz:\n", k+1);
		scanf("%d", &urunler[k].alisMiktari);
		printf("Firmadan talep ettiginiz %d. urunun alis fiyatini giriniz:\n", k+1);
		scanf("%f", &urunler[k].alisFiyati);
		printf("Firmadan tedarik ettiginiz tedarikci firma numarasini giriniz:\n");
		scanf("%d", &urunler[k].tedarikciNo);
		k++;
		printf("Tedarige devam etmek istiyor musunuz? (h = 0/ e = 1)\n");    //Bu fonksiyonda her iterasyonda magazaya tedarige devam etmek isteyip istemeyecegi sorulacak.
		scanf("%d", &cevap);						
		printf("Cevap: %d\n", cevap);
		if(cevap==evet){
			sor(urunler, 4);						//Magaza isleme devam etmek isterse yukaridan sor() fonksiyonu ile urun bilgisi alinmaya devam edilecektir.
			break;
		}
		else if(cevap == hayir){
			printf("Sistemden cikiliyor...\n");
			break;
		}
		else{
			printf("Gecerli bir deger giriniz...\n");
		}
	}
	alinanUrunSayisi = k;
	StokGuncelle(alinanUrunSayisi);
}



void AlisverisYap(urun IstenenUrun[], int boyut){
	int k, *yeniStok;
	enum karar onay;
	while(1){
		printf("Satin almak istediginiz urunun markasini giriniz:\n");
		scanf("%d", &IstenenUrun[k].marka);
		printf("Satin almak istediginiz urunun adini giriniz\n");
		scanf("%s", &IstenenUrun[k].urunAdi);
		printf("Satin almak istediginiz urunun kodunu giriniz:\n");
		scanf("%d", &IstenenUrun[k].urunKodu);	
		k++;
		printf("Alisverise devam etmek ister misiniz?(e = 1/ h = 0)\n");
		scanf("%d", &onay);
		if(onay == hayir){
				break;
			}
		else if(onay == evet){
			printf("Ana menuye yonlendiriliyorsunuz...\n");
			}
		else{
			printf("Gecersiz bir deger girdiniz. Tekrar deneyiniz\n");
		}			
	}	
}


void IadeYap(urun IadeUrun[], int boyut){
	int k = 0, *yeniStok;
	enum karar onay;
	while(k<=4){
		printf("Iade edilecek urunun markasini giriniz:\n");
		scanf("%d", &IadeUrun [k].marka);
		printf("Iade edilecek urunun adini giriniz:\n");
		scanf("%s", &IadeUrun[k].urunAdi);
		printf("Iade edilecek urunun kodunu giriniz:\n");
		scanf("%d", &IadeUrun[k].urunKodu);
		k++;
		printf("Isleme devam etmek istiyor musunuz?(e = 1/ h = 0)\n");
		scanf("%d", &onay);
		if(onay == hayir){
			break;
		}
		else if(onay == evet){
			printf("Ana menuye yonlendiriliyorsunuz...\n");
		}
		else{
			printf("Gecerli bir deger giriniz..\n");
		}
	}
	
	
}

void tedarikciKaydet(FILE *pfile,firma tedarikci[], int boyut){
	pfile = fopen("tedarikciBilgileri.txt", "a+");
	if(pfile == NULL){
		printf("Dosya bulunamadi\n");
		exit(1);
	}
	else{
		int k = 0, i = 0;
		for(k=0 ; k<2; k++){
				printf("%d. tedarikci firmanin adini giriniz: \n", k+1);
				scanf("%s", tedarikci[k].tedAdi);
				printf("%d. tedarikci firmanin numarasini giriniz: \n", k+1);   
				scanf("%d", &tedarikci[k].tedNo);
				printf("%d. tedarikcinin sehrini giriniz: \n", k+1);      //Enum yapýsý icerisinde tanýýmlanan sehir degiskenleriyle sehir bilgisi alýnýyor.
				scanf("%d", &tedarikci[k].plaka);
				printf("%d. tedarikcinin adresini giriniz: \n", k+1);
				scanf("%s", tedarikci[k].adres);
				fprintf(pfile, "%s %d %d %s\n", tedarikci[k].tedAdi, tedarikci[k].tedNo, tedarikci[k].plaka, tedarikci[k].adres);			
		}	
	}
	fclose(pfile);
}

void tedarikciListele(FILE *pfile, firma tedarikci[], int boyut){
	int k = 0, i = 0;
	pfile=fopen("tedarikciBilgileri.txt","r");
		for( ;i<2;i++){
  			for(;k<2; k++){
		  		fscanf(pfile,"%s%d%d%s\n ", &tedarikci[k].tedAdi, &tedarikci[k].tedNo, &tedarikci[k].plaka, &tedarikci[k].adres);
			    printf("Tedarikci firma adi: %s\n", tedarikci[k].tedAdi);
			    printf("Tedarikci firma numarasi: %d\n", tedarikci[k].tedNo);
			    printf("Tedarikci firma adresi: %s\n", tedarikci[k].adres);
			    printf("Tedarikci sehri: %d\n", tedarikci[k].plaka);
				printf("\n");
			}
  		}
	fclose(pfile);
 }
 
 void urunKaydet(FILE *pfile, urun kaydedilecekUrun[], int boyut){
	urun urunler[4];
	int i;
	if((pfile = fopen("urunBilgileri.txt", "a+"))==NULL){
		printf("Dosya olusturulamadi\n");
	}
	else{
		printf("Lutfen urun bilgilerini giriniz:(Sirasi ile marka/ urunAdi/ urunKodu/ satisFiyati/ stokMiktari)\n");
		for(i=0;i<4;i++){
			scanf("%d", &kaydedilecekUrun[i].marka);
			scanf("%s", kaydedilecekUrun[i].urunAdi);
			scanf("%d", &kaydedilecekUrun[i].urunKodu);
			scanf("%f",&kaydedilecekUrun[i].satisFiyati);
			scanf("%d", &kaydedilecekUrun[i].stokMiktari);
			fprintf(pfile, "%s   %s    %d    %f   %d", kaydedilecekUrun[i].marka, kaydedilecekUrun[i].urunAdi, kaydedilecekUrun[i].urunKodu, kaydedilecekUrun[i].satisFiyati, kaydedilecekUrun[i].stokMiktari);
		}
	}
}
void urunListele(FILE *pfile, urun kaydedilecekUrun[], int boyut){
	urun urunler[4];
	int x,i;
	if((pfile = fopen("urunBilgileri.txt", "r"))==NULL){
		printf("Dosya bulunamadi\n");
	}
	else{
		for(i = 0; i<4; i++){
			fscanf(pfile, "%d %s %d %f %d", &kaydedilecekUrun[i].marka, kaydedilecekUrun[i].urunAdi, &kaydedilecekUrun[i].urunKodu, &kaydedilecekUrun[i].satisFiyati, &kaydedilecekUrun[i].stokMiktari);
			printf("Urun markasi: %d\nUrun adi: %s\nUrun kodu: %d\nSatis fiyati: %.2f\nStok miktari: %d\n", kaydedilecekUrun[i].marka, kaydedilecekUrun[i].urunAdi, kaydedilecekUrun[i].urunKodu, kaydedilecekUrun[i].satisFiyati, kaydedilecekUrun[i].stokMiktari);
		}
	}
}

 typedef struct{
	char kulAdi[50];
	char pass[50];
}kullanici;

void kullaniciBul(FILE *pfile,char nickname[],char pass[]){
	char line[301];
	char aranacak[100]="";
	kullanici k;
	strcat(aranacak,nickname);
	int isFound=0;
	strcat(aranacak,pass);
	pfile = fopen("kullaniciBilgileri.txt", "r");
	if(pfile==NULL){
		printf("Dosya bulunamadý");
	}else{
		while(!feof(pfile)){
			fgets(line,300,pfile);
			if(strncmp(aranacak,line,strlen(aranacak))==0){
				isFound=1;
				break;
			}else{
				isFound=0;

			}
		}
	}
	if(isFound==1){
		printf("Hosgeldiniz !");

	}else{
		printf("\nKullanici bulunamadi. Lutfen kaydolunuz!\n");
		dosyaYaz(pfile,k);
	}
	fclose(pfile);
}
void kullaniciGiris(char nickname[],char pass[]){
	printf("Kullanici adini giriniz :");
	scanf("%s",&nickname);
	printf("Sifre giriniz :");
	scanf("%s",&pass);

}
void dosyaYaz(FILE *pfile,kullanici x[], int boyut){
	pfile = fopen("kullaniciBilgileri.txt", "a+");
	if(pfile == NULL){
		printf("Dosya bulunamadi\n");
		exit(1);
	}
	else{
		int k = 0, i = 0;
		for( ; k<1; k++){
				printf("Kullanici adini giriniz: \n", k+1);
				scanf("%s",x[k].kulAdi);
				printf("Sifre giriniz: \n", k+1);
				scanf("%s",x[k].pass);
				fprintf(pfile, "%s%s\n", x[k].kulAdi, x[k].pass);
		}
	}
	fclose(pfile);
}
void dosyaOku(FILE *pfile, kullanici x[]){
	int k = 0, i = 0;
	pfile=fopen("kullaniciBilgileri.txt","r");
		for( ;i<2;i++){
  			for(;k<4; k++){
		  		fscanf(pfile,"%s%s\n ", x[k].kulAdi, &x[k].pass);
			    printf("Kullanici adi: %s\n", x[k].kulAdi);
			    printf("Kullanici parolasi: %s\n", x[k].pass);
				printf("\n");
			}
  		}
	fclose(pfile);
 }
int main(){
	FILE *pfile;
	urun urunler[4];
	firma tedarikci[4];
	stokGirisi stok;
	char c;
	int islem, stoktakiUrunMiktari;
	char nickname[50], pass[50];
	printf("Kullanici adini giriniz:");
	scanf("%s",&nickname);
	printf("Sifre giriniz:");
	scanf("%s",&pass);
	kullaniciBul(pfile,nickname,pass);
	
	printf("URUN MENUSU\n");
	printf("1-kayit girisi\n");
	printf("2-Kayit listeleme\n");
	printf("3-Urun tedarik et\n");
	printf("4-Alisveris/ Iade yap\n");
	printf("5-Cikis\n");
	printf("Isleminizi seciniz...\n");
	scanf("%d", &islem);
	printf("\n");
	
	while(islem!=5){
		if(islem == 1){
			printf("1-Tedarikci kaydet\n");
			printf("2-Urun kaydet\n");
			scanf("%d",&islem);
			if(islem==1){
				tedarikciKaydet(pfile,tedarikci, 4);
		}
			else if(islem==2){
			  	urunKaydet(pfile, urunler, 4);	
			}
			else{
				printf("Gecerli bir deger giriniz.\n");
			}
		} 
		if(islem == 2){
			printf("1-Tedarikci bilgilerini listele\n");
			printf("2-Urun bilgilerini listele\n");
			scanf("%d",&islem);
			if(islem==1){
				tedarikciListele(pfile,tedarikci, 4);
		}
			else if(islem==2){
			  	urunListele(pfile, urunler, 4);	
			}
			else{
				printf("Gecerli bir deger giriniz.\n");
			}
		} 
		tedarikciListele(pfile,tedarikci, 4);
		if(islem == 3) tedarikEt(urunler, 4);
		if(islem == 4){
			printf("1- Urun satin al\n");
			printf("2- Urun iade et\n");
			printf("Islem seciniz:\n");
			scanf("%d", &islem);
			if(islem == 1){
				AlisverisYap(urunler, 4);
				break;
			}
			if(islem == 2){
				IadeYap(urunler, 4);
				break;
			}
			else{
				printf("Gecerli bir deger giriniz.\n");
			}
		}
	}
	getch();
	printf("Urun tedarik etmek ister misiniz? (E/H)\n");
	c = getch();
	if(c == 'e'|| c== 'E'){
		tedarikEt(urunler, 4);
	}
	else if(c == 'h'|| c == 'H'){
		printf("Urun tedarik edilmeyecektir...\n");
	}
	else{
		printf("Lutfen gecerli bir cevap giriniz\n");
	}
	
    faturaKes(urunler, 4);
	return 0;
}
