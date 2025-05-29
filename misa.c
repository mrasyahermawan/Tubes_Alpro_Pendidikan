#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

struct guru {
    char userguru[100];
    char passguru[100];
};

struct siswa {
    char usersiswa[100];
    char passiswa[100];
};

void guru();//aman
void siswa();//aman
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
    printf("3. Keluar\n");
    printf("Silahkan pilih menu"); scanf("%d", &n);
    switch (n)
    {
    case 1:
        regisGuru();
        break;
    case 2:
        loginGuru();
        break;
    case 3:
        main();
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
    printf("Silahkan pilih menu : "); scanf("%d", &n);
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
    struct guru regis;
    dataAkun_guru = fopen("dataAkun_guru.dat", "ab");

    if ( dataAkun_guru == NULL ){
        printf("File tidak bisa dibuka");
    }
    getchar();
    printf("Masukkan Username : "); gets(regis.userguru);
    printf("Masukkan Password : "); gets(regis.passguru);

    fwrite(&regis , sizeof(struct guru), 1 , dataAkun_guru);
    printf("\n");
    printf("Akun berhasil ditambahkan!!\n");
    system("pause");

    fclose(dataAkun_guru);
    main();

}

void loginGuru(){

}

void regisSiswa(){
    struct siswa regis;
    dataAkun_siswa = fopen("dataAkun_siswa.dat", "a");

    if ( dataAkun_siswa == NULL ){
        printf("File tidak bisa dibuka");
    }

    printf("Masukkan Username : "); gets(regis.usersiswa);
    printf("Masukkan Password : "); gets(regis.passiswa);

     fwrite(&regis , sizeof(struct siswa), 1 , dataAkun_siswa);
    printf("\n");
    printf("Akun berhasil ditambahkan!!\n");
    system("pause");

    fclose(dataAkun_siswa);
    main();
    

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