#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int choice = 0;
int fisNo = 0;
int raporNo = 0;
char title1[] = " AYLIK RAPOR KOPYASI";
char horbar[] = "* * * * * * * * * * *";
char title2[] = "* MALI islem DISI *";

struct tm* current_timeAndDate();

struct urun {
    char name[15];
    float price;
    float KDV;
    int quantity;
};

void slip(struct urun products[], int numProducts);
void menu();
void urunler();
void satisyap(struct urun products[], int numProducts);
void kdvModify(struct urun products[], int numProducts);

int main() {
    menu();
    return 0;
}

void slip(struct urun products[], int numProducts) {
    fisNo++;
    raporNo++;
    printf("%s\n\n", title1);
    printf("%s\n", horbar);
    printf("%s\n", title2);
    printf("\nTestAmacli\nMaliDegeriYok\nAlemdag\n\n");

    struct tm* local_time = current_timeAndDate();
    printf("Fis No: %d\n", fisNo);
    printf("***OKC AYLIK SATIS RAPORU***\n");
    printf("Rapor Donemi: %02d/%04d\n", local_time->tm_mon + 1, local_time->tm_year + 1900);
    printf("Rapor No: %d\n", raporNo);
    printf("%s\n", horbar);
    printf("KDV ORANLARI ITIBARIYLE \n SATISLAR GENEL BILGISI \n (BILGI FISLERI HARIC)\n");

    float totalPrice = 0.0;
    float totalVAT = 0.0;
    
    for (int i = 0; i < numProducts; i++) {
        if (products[i].quantity > 0) {
            float productVAT = products[i].price * (products[i].KDV / 100);
            float productTotalVAT = productVAT * products[i].quantity;
            float productTotalPrice = products[i].price * products[i].quantity;

            totalPrice += productTotalPrice;
            totalVAT += productTotalVAT;

            printf("%s - Fiyat: %.2f TL - KDV Orani: %.2f%% - KDV Tutari: %.2f TL - Miktar: %d\n",
                   products[i].name, products[i].price, products[i].KDV, productTotalVAT, products[i].quantity);
        }
    }

    printf("\nToplam Fiyat: %.2f TL\n", totalPrice);
    printf("Toplam KDV Tutar: %.2f TL\n", totalVAT);
}

void menu() {
    struct urun products[3]; 
    int numProducts = 3;

    strcpy(products[0].name, "Su");
    products[0].price = 100.0;
    products[0].KDV = 18.0;
    products[0].quantity = 0;

    strcpy(products[1].name, "Kola");
    products[1].price = 50.0;
    products[1].KDV = 8.0;
    products[1].quantity = 0;

    strcpy(products[2].name, "Sut");
    products[2].price = 50.0;
    products[2].KDV = 8.0;
    products[2].quantity = 0;

    while(1) {
        printf("\n\tMENU\n");
        printf("%s\n", horbar);
        printf("\n\n 1. SLIP GORUNTULE");
        printf("\n 2. SATIS YAP");
        printf("\n 3. KDV ORANI DEGISTIR");
        printf("\n 4. EXIT");
        printf("\n\n Seciminizi yapiniz: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                slip(products, numProducts); 
                break;
            case 2:
                satisyap(products, numProducts); 
                break;
            case 3:
                kdvModify(products, numProducts);
                break;
            case 4:
                printf("Cikis yapiliyor...\n");
                exit(0);
            default:
                printf("Gecersiz giris\n");
                break;
        }
    }
}

struct tm* current_timeAndDate() {
    time_t current_time;
    struct tm* local_time;

    time(&current_time);
    local_time = localtime(&current_time);

    printf("Tarih: %02d/%02d/%04d\n", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);
    printf("Saat: %02d:%02d:%02d\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    return local_time;
}

void urunler() {
    struct urun products[3]; 
    int numProducts = 3;

    strcpy(products[0].name, "Su");
    products[0].price = 100.0;
    products[0].KDV = 18.0;
    products[0].quantity = 0;

    strcpy(products[1].name, "Kola");
    products[1].price = 50.0;
    products[1].KDV = 8.0;
    products[1].quantity = 0;

    strcpy(products[2].name, "Sut");
    products[2].price = 50.0;
    products[2].KDV = 8.0;
    products[2].quantity = 0;

    satisyap(products, numProducts); 
}

void satisyap(struct urun products[], int numProducts) {
    int selection = 0;
    int quantity = 0;
    char another = 'Y';

    while (another == 'Y' || another == 'y') {
        printf("\nSatmak istediginiz urunun numarasini seciniz:\n");
        for (int i = 0; i < numProducts; i++) {
            printf("%d. %s - Fiyat: %.2f TL\n", i + 1, products[i].name, products[i].price);
        }
        printf("Seciminiz: ");
        scanf("%d", &selection);

        if (selection < 1 || selection > numProducts) {
            printf("Gecersiz secim.\n");
            continue;
        }

        printf("Kac adet satacaksiniz? ");
        scanf("%d", &quantity);

        products[selection - 1].quantity += quantity;

        printf("Baska bir urun satmak istiyor musunuz? (Y/N): ");
        scanf(" %c", &another);
    }

    slip(products, numProducts);

    printf("\n***ODEME FIsI***\n");
    float totalPrice = 0.0;
    float totalVAT = 0.0;
    for (int i = 0; i < numProducts; i++) {
        if (products[i].quantity > 0) {
            float productTotalPrice = products[i].price * products[i].quantity;
            float productTotalVAT = productTotalPrice * (products[i].KDV / 100);

            totalPrice += productTotalPrice;
            totalVAT += productTotalVAT;

            printf("Urun: %s\n", products[i].name);
            printf("Miktar: %d adet\n", products[i].quantity);
            printf("Toplam Fiyat: %.2f TL\n", productTotalPrice);
            printf("KDV Tutar: %.2f TL\n", productTotalVAT);
            printf("\n");
        }
    }

    printf("Genel Toplam Fiyat: %.2f TL\n", totalPrice);
    printf("Genel Toplam KDV Tutar: %.2f TL\n", totalVAT);
}

void kdvModify(struct urun products[], int numProducts) {
    int selection = 0;
    float newKDV = 0.0;

    printf("\nKDV oranini degistirmek istediginiz urunun numarasini seciniz:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%d. %s - Mevcut KDV Orani: %.2f%%\n", i + 1, products[i].name, products[i].KDV);
    }
    printf("Seciminiz: ");
    scanf("%d", &selection);

    if (selection < 1 || selection > numProducts) {
        printf("Gecersiz secim.\n");
        return;
    }

    printf("Yeni KDV oranini giriniz (%%): ");
    scanf("%f", &newKDV);

    products[selection - 1].KDV = newKDV;

    printf("%s urununun yeni KDV orani: %.2f%%\n", products[selection - 1].name, newKDV);
}

