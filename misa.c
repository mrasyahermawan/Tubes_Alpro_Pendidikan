#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

struct Data_guru
{
    
};

struct Data_siswa
{

};

void guru();
void siswa();
void regisGuru();
void loginGuru();
void regisSiswa();
void loginSiswa();
void menuGuru();
void menuSiswa();


//file Guru
FILE *dataAkun_guru;
FILE *dataAkun_siswa;

void guru(){
    system("cls");
    int n;
    printf("Selamat datang beach!!\n");
    printf("Pilih Menu : \n");
    printf("1. Registrasi Guru\n");
    printf("2. Login Guru\n");
    printf("Silahkan pilih menu"); scanf("%d", &n);
    switch (n)
    {
    case 1:
        regisGuru();
        break;
    case 2:
        loginGuru();
        break;
    default:
        printf("Pilihan tidak valid!! Silahkan direfresh ulang..");
        break;
    }

}

void siswa(){
    system("cls");
    int n;
    printf("Selamat datang beach!!\n");
    printf("Pilih Menu : \n");
    printf("1. Registrasi Siswa\n");
    printf("2. Login Siswa\n");
    printf("Silahkan pilih menu"); scanf("%d", &n);
    switch (n)
    {
    case 1:
        regisSiswa();
        break;
    case 2:
        loginSiswa(); 
        break;
    default:
        break;
    }
}

void regisGuru(){
    dataAkun_guru = fopen("dataAkun_guru.txt", "a");

    if ( dataAkun_guru == NULL ){
        printf("File tidak bisa dibuka");
    }
}

void loginGuru(){

}

void regisSiswa(){
    dataAkun_siswa = fopen("dataAkun_siswa.txt", "ab");

    

}

void loginSiswa(){

}

void menuGuru(){

}

void menuSiswa(){
    
}


int main(){
    int pilihan;

    printf("Selamat datang Civitas Akademia SMA Ngawi\n");
    printf("1. Guru\n");
    printf("2. Siswa\n");
    printf("Silahkan pilih user : "); scanf("%d", &pilihan);
    switch (pilihan)
    {
    case 1:
        guru();
        break;
    case 2:
        siswa();
        break;
    case 3:
        exit(0);
        break;
    default:
        printf("Pilihan tidak valid!! Silahkan refresh.");
        break;
    }
}