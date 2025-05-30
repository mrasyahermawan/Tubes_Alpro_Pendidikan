#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

struct guru {
    char userguru[100];
    char passguru[100];
} user, aktif;

struct siswa {
    char usersiswa[100];
    char passiswa[100];
    char nama[100], alamat[100], ttl[100];
    int nis;
} murid, aseli;

struct Mahasiswa {
    char nis[20];
    char nama[50];
    float nilai;
};

struct Database {
    struct Mahasiswa data[100];
    int jumlah;
};

void guru();
void siswa();
void regisGuru();
int loginGuru(int attempt);
void regisSiswa();
int loginSiswa(int attempt);
void menuGuru();
void menuSiswa();
int main();
void lihatDiri();
void initDatabase(struct Database *db);
void tambahMahasiswa(struct Database *db);
void cariMahasiswa(struct Database *db);
void tampilkanStatistik(struct Database *db);
void simpanKeFile(struct Database *db);
void bacaDariFile(struct Database *db);

FILE *dataAkun_guru;
FILE *dataAkun_siswa;

void initDatabase(struct Database *db) {
    db->jumlah = 0;
}

void tambahMahasiswa(struct Database *db) {
    if (db->jumlah >= 100) {
        printf("Database penuh! Tidak bisa menambah data lagi.\n");
        return;
    }

    struct Mahasiswa mhs;
    
    printf("\n--- Tambah Data Mahasiswa ---\n");
    
    printf("Masukkan NIS: ");
    scanf("%s", mhs.nis);
    getchar(); // Membersihkan buffer
    
    for (int i = 0; i < db->jumlah; i++) {
        if (strcmp(db->data[i].nis, mhs.nis) == 0) {
            printf("Error: NIS sudah terdaftar!\n");
            return;
        }
    }
    
    printf("Masukkan Nama: ");
    fgets(mhs.nama, 50, stdin);
    mhs.nama[strcspn(mhs.nama, "\n")] = 0; // Menghapus newline
    
    printf("Masukkan Nilai: ");
    scanf("%f", &mhs.nilai);
    
    while (mhs.nilai < 0 || mhs.nilai > 100) {
        printf("Nilai harus antara 0-100. Masukkan kembali: ");
        scanf("%f", &mhs.nilai);
    }
    
    db->data[db->jumlah] = mhs;
    db->jumlah++;
    
    printf("Data mahasiswa berhasil ditambahkan!\n");
}

void cariMahasiswa(struct Database *db) {
    char nis[20];
    int found = 0;
    
    printf("\n--- Cari Mahasiswa ---\n");
    printf("Masukkan NIS yang dicari: ");
    scanf("%s", nis);
    
    for (int i = 0; i < db->jumlah; i++) {
        if (strcmp(db->data[i].nis, nis) == 0) {
            printf("\nData ditemukan:\n");
            printf("NIS  : %s\n", db->data[i].nis);
            printf("Nama : %s\n", db->data[i].nama);
            printf("Nilai: %.2f\n", db->data[i].nilai);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Mahasiswa dengan NIS %s tidak ditemukan.\n", nis);
    }
}

void tampilkanStatistik(struct Database *db) {
    if (db->jumlah == 0) {
        printf("Database kosong. Tidak ada statistik yang bisa ditampilkan.\n");
        return;
    }
    
    float total = 0;
    float max = db->data[0].nilai;
    float min = db->data[0].nilai;
    int lulus = 0;
    
    for (int i = 0; i < db->jumlah; i++) {
        total += db->data[i].nilai;
        
        if (db->data[i].nilai > max) {
            max = db->data[i].nilai;
        }
        
        if (db->data[i].nilai < min) {
            min = db->data[i].nilai;
        }
        
        if (db->data[i].nilai >= 60) {
            lulus++;
        }
    }
    
    printf("\n--- Statistik Nilai ---\n");
    printf("Jumlah mahasiswa    : %d\n", db->jumlah);
    printf("Nilai rata-rata     : %.2f\n", total / db->jumlah);
    printf("Nilai tertinggi     : %.2f\n", max);
    printf("Nilai terendah      : %.2f\n", min);
    printf("Persentase kelulusan: %.2f%%\n", (float)lulus / db->jumlah * 100);
}

void simpanKeFile(struct Database *db) {
    FILE *file = fopen("database_mahasiswa.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk penyimpanan.\n");
        return;
    }
    
    for (int i = 0; i < db->jumlah; i++) {
        fprintf(file, "%s;%s;%.2f\n", 
                db->data[i].nis, 
                db->data[i].nama, 
                db->data[i].nilai);
    }
    
    fclose(file);
    printf("Data berhasil disimpan ke file.\n");
}

void bacaDariFile(struct Database *db) {
    FILE *file = fopen("database_mahasiswa.txt", "r");
    if (file == NULL) {
        printf("File database tidak ditemukan. Akan dibuat yang baru.\n");
        return;
    }
    
    initDatabase(db);
    
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        struct Mahasiswa mhs;
        char *token;
        
        token = strtok(line, ";");
        strcpy(mhs.nis, token);
        
        token = strtok(NULL, ";");
        strcpy(mhs.nama, token);
        
        token = strtok(NULL, ";");
        mhs.nilai = atof(token);
        
        db->data[db->jumlah] = mhs;
        db->jumlah++;
    }
    
    fclose(file);
    printf("Data berhasil dimuat dari file.\n");
}

void guru() {
    system("cls");
    int n;
    int coba = 3;

    printf("Selamat datang beach!!\n");
    printf("Pilih Menu : \n");
    printf("1. Registrasi Guru\n");
    printf("2. Login Guru\n");
    printf("3. Keluar\n");
    printf("Silahkan pilih menu : "); scanf("%d", &n);
    getchar();
    switch (n) {
    case 1:
        regisGuru();
        break;
    case 2:
        loginGuru(coba);
        break;
    case 3:
        main();
        break;
    default:
        printf("Pilihan tidak valid!! Silahkan direfresh ulang..");
        break;
    }
}

void siswa() {
    int coba = 3;
    system("cls");
    int n;
    printf("Selamat datang beach!!\n");
    printf("Pilih Menu : \n");
    printf("1. Registrasi Siswa\n");
    printf("2. Login Siswa\n");
    printf("3. Keluar\n");
    printf("Silahkan pilih menu : "); scanf("%d", &n);
    getchar();
    switch (n) {
    case 1:
        regisSiswa();
        break;
    case 2:
        loginSiswa(coba);
        break;
    case 3:
        main();
        break;
    default:
        break;
    }
}

void regisGuru() {
    int n;
    int coba = 3;
    struct guru regis;
    dataAkun_guru = fopen("dataAkun_guru.dat", "ab");

    if (dataAkun_guru == NULL) {
        printf("File tidak bisa dibuka");
    }
    getchar();
    printf("Masukkan Username : "); gets(regis.userguru);
    printf("Masukkan Password : "); gets(regis.passguru);

    fwrite(&regis, sizeof(struct guru), 1, dataAkun_guru);
    printf("\n");
    printf("Akun berhasil ditambahkan!!\n");
    system("pause");

    fclose(dataAkun_guru);

    printf("\n");
    
    printf("1. Login Guru\n");
    printf("2. Kembali ke Menu Utama\n");
    printf("Pilih Menu : \n"); scanf("%d", &n);
    getchar();
    switch (n) {
    case 1:
        loginGuru(coba);
        break;
    case 2:
        main();
        break;
    default:
        printf("pilihan tidak valid, silahkan direfresh!!\n");
        break;
    }
}

int loginGuru(int attempt) {
    dataAkun_guru = fopen("dataAkun_guru.dat", "rb");
    char usnguru[100], passguru[100];

    printf("=== Silahkan Login ===\n");
    printf("Masukkan Username Guru : "); gets(usnguru);
    printf("Masukkan Password : "); gets(passguru);

    while (fread(&user, sizeof(struct guru), 1, dataAkun_guru)) {
        if (strcmp(user.userguru, usnguru) == 0 && strcmp(user.passguru, passguru) == 0) {
            aktif = user;
            printf("Selamat Datang %s di Pusat Pendataan SMA Ngawi!!\n", usnguru);
            fclose(dataAkun_guru);
            menuGuru();
            return 0;
        }
    }

    attempt--;
    fclose(dataAkun_guru);

    if (attempt > 0) {
        system("cls");
        printf("Username atau password salah, silahkan coba lagi!\n");
        printf("Kesempatan anda tersisa %d \n", attempt);
        system("pause");
        system("cls");
        loginGuru(attempt);
    } else {
        printf("Kesempatan anda sudah habis, silahkan refresh. \n");
        system("pause");
        system("cls");
        main();
    }
}

void regisSiswa() {
    system("cls");
    int n;
    int coba = 3;
    dataAkun_siswa = fopen("dataAkun_siswa.dat", "ab");
    struct siswa daftar;

    printf("=== Registrasi Akun Siswa ===\n");
    printf("Masukkan Username : "); gets(daftar.usersiswa);
    printf("Masukkan Password : "); gets(daftar.passiswa);
    printf("Nama Lengkap : "); gets(daftar.nama);
    printf("NIS :"); scanf("%d", &daftar.nis);
    getchar();
    printf("Tempat Tanggal Lahir : "); gets(daftar.ttl);
    printf("Alamat Tempat Tinggal : "); gets(daftar.alamat);

    fwrite(&daftar, sizeof(struct siswa), 1, dataAkun_siswa);
    printf("\n");
    printf("Akun berhasil ditambahkan!!\n");
    system("pause");

    fclose(dataAkun_siswa);

    printf("\n");
    printf("1. Login Siswa\n");
    printf("2. Kembali ke Menu Utama\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();
    switch (n) {
    case 1:
        loginSiswa(coba);
        break;
    case 2:
        main();
        break;
    default:
        printf("pilihan tidak valid, silahkan direfresh!!\n");
        break;
    }
}

int loginSiswa(int attempt) {
    system("cls");
    dataAkun_siswa = fopen("dataAkun_siswa.dat", "rb");
    char usnsiswa[100], passiswa[100];

    printf("=== Silahkan Login ===\n");
    printf("Masukkan Username Siswa : "); gets(usnsiswa);
    printf("Masukkan Password : "); gets(passiswa);

    while (fread(&murid, sizeof(struct siswa), 1, dataAkun_siswa)) {
        if (strcmp(murid.usersiswa, usnsiswa) == 0 && strcmp(murid.passiswa, passiswa) == 0) {
            aseli = murid;
            printf("Selamat Datang %s di Pusat Pendataan SMA Ngawi!!\n", usnsiswa);
            fclose(dataAkun_siswa);
            menuSiswa();
            return 0;
        }
    }

    attempt--;
    fclose(dataAkun_siswa);

    if (attempt > 0) {
        system("cls");
        printf("Username atau password salah, silahkan coba lagi!\n");
        printf("Kesempatan anda tersisa %d \n", attempt);
        system("pause");
        system("cls");
        loginSiswa(attempt);
    } else {
        printf("Kesempatan anda sudah habis, silahkan refresh. \n");
        system("pause");
        system("cls");
        main();
    }
}

void menuGuru() {
    system("cls");
    struct Database db;
    initDatabase(&db);
    bacaDariFile(&db);
    
    int n;

    printf("=== Menu Guru ===\n");
    printf("1. Tambah Data Siswa\n");
    printf("2. Lihat Data Siswa\n");
    printf("3. Input Nilai Siswa\n");
    printf("4. Cari Data Siswa\n");
    printf("5. Statistik Nilai\n");
    printf("6. Kembali ke Menu Utama\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();

    switch (n) {
    case 1:
        tambahMahasiswa(&db);
        simpanKeFile(&db);
        system("pause");
        menuGuru();
        break;
    case 2:
        printf("Fitur Lihat Data Siswa belum diimplementasikan.\n");
        system("pause");
        menuGuru();
        break;
    case 3:
        tambahMahasiswa(&db);
        simpanKeFile(&db);
        system("pause");
        menuGuru();
        break;
    case 4:
        cariMahasiswa(&db);
        system("pause");
        menuGuru();
        break;
    case 5:
        tampilkanStatistik(&db);
        system("pause");
        menuGuru();
        break;
    case 6:
        simpanKeFile(&db);
        main();
        break;
    default:
        printf("Pilihan tidak valid!\n");
        system("pause");
        menuGuru();
        break;
    }
}

void menuSiswa() {
    system("cls");
    int n;

    printf("=== Menu Siswa ===\n");
    printf("1. Lihat Data Diri\n");
    printf("2. Lihat Nilai\n");
    printf("3. Kembali ke Menu Utama\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();

    switch (n) {
    case 1:
        lihatDiri();
        break;
    case 2:
        break;
    case 3:
        main();
        break;
    default:
        break;
    }
}

int main() {
    int pilihan;
    
    printf("Selamat datang Civitas Akademia SMA Ngawi\n");
    printf("1. Guru\n");
    printf("2. Siswa\n");
    printf("3. Keluar\n");
    printf("Silahkan pilih user : "); scanf("%d", &pilihan);
    getchar();
    switch (pilihan) {
    case 1:
        guru();
        break;
    case 2:
        siswa();
        break;
    case 3:
        printf("Terimakasih, Sampai jumpa kembali!!\n");
        exit(0);
        break;
    default:
        printf("Pilihan tidak valid!! Silahkan refresh.");
        break;
    }
}

void lihatDiri() {
    system("cls");
    dataAkun_siswa = fopen("dataAkun_siswa.dat", "rb");

    if (dataAkun_siswa == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }
    printf("=== Data Diri %s ===\n", aseli.usersiswa);
    while (fread(&murid, sizeof(struct siswa), 1, dataAkun_siswa)) {
        printf("Nama Lengkap : %s \n", aseli.nama);
        printf("NIS : %d \n", aseli.nis);
        printf("Alamat : %s \n", aseli.alamat);
        printf("Tempat Tanggal Lahir : %s \n", aseli.ttl);
    }
    fclose(dataAkun_siswa);
    printf("\n");

    printf("Tekan enter untuk kembali ke menu siswa...\n");
    system("pause");
    system("cls");
    menuSiswa();
}