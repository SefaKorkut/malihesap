#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void menuGoster(char ad[], char adres[], float gelir, float gider, float gelKdv, float gidKdv);
int tarihAl();
float kdvHesapla(float tutar, int oran);
void raporYazdir(float gelirler[], int gelSayac, float giderler[], int gidSayac, float tGelir, float tGider, float tGelKdv, float tGidKdv);

int main() {
    char ad[50], adres[100];
    float tum_giderler[100], tum_gelirler[100];
    int gelir_sayac = 0, gider_sayac = 0;
    
    float toplam_gider = 0, toplam_gelir = 0;
    float gid_top_kdv_tut = 0, gel_top_kdv_tut = 0;
    
    int secim, kdv_orani;
    float tutar, hesaplananKdv;

    printf("Ad-soyad giriniz: ");
    gets(ad);

    printf("Adres (Sehir) giriniz: ");
    gets(adres);

    while (1) {
        menuGoster(ad, adres, toplam_gelir, toplam_gider, gel_top_kdv_tut, gid_top_kdv_tut);
        printf(" Seciminizi yapiniz: ");
        scanf("%d", &secim);

        if (secim == 4) {
            printf("\nSistemden cikis yapiliyor... Iyi gunler\n");
            break;
        }

        switch (secim) {
            case 1:
                if (gider_sayac < 100) {
                    tarihAl();
                    printf("Giderin (KDV DAHIL) toplam tutarini giriniz: ");
                    scanf("%f", &tutar);
                    printf("KDV oranini giriniz (1, 10, 20): ");
                    scanf("%d", &kdv_orani);

                    hesaplananKdv = kdvHesapla(tutar, kdv_orani);
                    tum_giderler[gider_sayac++] = tutar;
                    toplam_gider += tutar;
                    gid_top_kdv_tut += hesaplananKdv;
                    
                    printf("Kayit Basarili! (KDV: %.2f TL)\n", hesaplananKdv);
                } else {
                    printf("Hata: Gider hafizasi dolu!\n");
                }
                break;

            case 2: 
                if (gelir_sayac < 100) {
                    tarihAl();
                    printf("Gelirin (KDV DAHIL) toplam tutarini giriniz: ");
                    scanf("%f", &tutar);
                    printf("KDV oranini giriniz (1, 10, 20): ");
                    scanf("%d", &kdv_orani);

                    hesaplananKdv = kdvHesapla(tutar, kdv_orani);
                    tum_gelirler[gelir_sayac++] = tutar;
                    toplam_gelir += tutar;
                    gel_top_kdv_tut += hesaplananKdv;

                    printf("Kayit Basarili! (KDV: %.2f TL)\n", hesaplananKdv);
                } else {
                    printf("Hata: Gelir hafizasi dolu!\n");
                }
                break;

            case 3: // Raporlama
                raporYazdir(tum_gelirler, gelir_sayac, tum_giderler, gider_sayac, toplam_gelir, toplam_gider, gel_top_kdv_tut, gid_top_kdv_tut);
                break;

            default:
                printf("\n Gecersiz secim! Lutfen 1-4 arasinda bir deger girin\n");
                break;
        }
    }

    return 0;
}

// --- FONKSÝYON TANIMLARI ---

void menuGoster(char ad[], char adres[], float gelir, float gider, float gelKdv, float gidKdv) {
    printf("\n======================================================\n");
    printf("--- TURKIYE GENEL MUHASEBE SISTEMI ---\n");
    printf(" HOSGELDINIZ %s | Konum: %s\n", ad, adres);
    printf(" Mevcut Durum: Gelir: %.2f | Gider: %.2f\n", gelir, gider);
    printf(" KDV Durumu  : Gelir KDV: %.2f | Gider KDV: %.2f\n", gelKdv, gidKdv);
    printf("------------------------------------------------------\n");
    printf(" 1- Gider Girisi\n 2- Gelir Girisi\n 3- Kar/Zarar ve Vergi Raporu\n 4- Sistemden Cikis\n");
    printf("======================================================\n");
}

int tarihAl() {
    int g, a, y;
    while (1) {
        printf("\nFis tarihini giriniz (GG/AA/YYYY): ");
        
        if (scanf("%d/%d/%d", &g, &a, &y) == 3) {
        	
            if (a >= 1 && a <= 12 && 
			g >= 1 && g <= 31 
			&& y >= 2000 && y <= 2030) {
                return 1;
            }
        }
        printf("Gecersiz tarih! Lutfen tekrar deneyin.\n");
        
    }
}

float kdvHesapla(float tutar, int oran) {
    if (oran == 20 || oran == 10 || oran == 1) {
        return (tutar * oran) / 100.0;
    }
    printf(" Gecersiz KDV orani! KDV 0 kabul edildi\n");
    return 0;
}

void raporYazdir(float gelirler[], int gelSayac, float giderler[], int gidSayac, float tGelir, float tGider, float tGelKdv, float tGidKdv) {
    float karZarar = tGelir - tGider;
    float devredenKdv = tGelKdv - tGidKdv;
    int damgaVergisi = 665;
    float toplamBorc;
    int i;
    printf("\n\n********** AYRINTILI RAPOR **********\n");
    
    printf("\n>> GELIR KAYITLARI:\n");
    for( i = 0; i < gelSayac; i++) printf("   %d. Kayit: %.2f TL\n", i+1, gelirler[i]);

    printf("\n>> GIDER KAYITLARI:\n");
    for( i = 0; i < gidSayac; i++) printf("   %d. Kayit: %.2f TL\n", i+1, giderler[i]);

    printf("\n--------------------------------------\n");
    if (karZarar > 0) printf("DURUM: %.2f TL KAR\n", karZarar);
    else if (karZarar < 0) printf("DURUM: %.2f TL ZARAR\n", -karZarar);
    else printf("DURUM: Kar/Zarar Yok\n");

    if (devredenKdv > 0) {
    toplamBorc = devredenKdv + damgaVergisi;
    } 
	else {
    toplamBorc = damgaVergisi;
    }

    printf("KDV Farki: %.2f TL\n", devredenKdv);
    printf("Odenecek Toplam Vergi (Damga Dahil): %.2f TL\n", toplamBorc);
    printf("*************************************\n");
}
