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
    char nama[100];
    int nis;
} murid, aseli;

struct Mahasiswa {
    char nis[20];
    char nama[50];
    char username[100];
    float nilai;
};

struct Database {
    struct Mahasiswa data[100];
    int jumlah;
};

void guru();
void siswa();
void admin();
void regisGuru();
int loginGuru(int attempt);
int loginSiswa(int attempt);
void menuGuru();
void menuSiswa();
void menuAdmin();
int main();
void lihatDiri();
void lihatNilai();
void initDatabase(struct Database *db);
void tambahMahasiswa(struct Database *db);
void inputNilaiMahasiswa(struct Database *db);
void lihatSemuaMahasiswa(struct Database *db);
void cariMahasiswa(struct Database *db);
void tampilkanStatistik(struct Database *db);
void simpanKeFile(struct Database *db);
void bacaDariFile(struct Database *db);
void tambahAkunMahasiswa(struct Database *db);

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
    getchar();
    
    for (int i = 0; i < db->jumlah; i++) {
        if (strcmp(db->data[i].nis, mhs.nis) == 0) {
            printf("Error: NIS sudah terdaftar!\n");
            return;
        }
    }
    
    printf("Masukkan Username: ");
    fgets(mhs.username, 100, stdin);
    mhs.username[strcspn(mhs.username, "\n")] = 0;
    
    printf("Masukkan Nama: ");
    fgets(mhs.nama, 50, stdin);
    mhs.nama[strcspn(mhs.nama, "\n")] = 0;
    
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

void inputNilaiMahasiswa(struct Database *db) {
    char nis[20];
    int found = 0;
    
    printf("\n--- Input Nilai Mahasiswa ---\n");
    printf("Masukkan NIS: ");
    scanf("%s", nis);
    
    for (int i = 0; i < db->jumlah; i++) {
        if (strcmp(db->data[i].nis, nis) == 0) {
            printf("Data ditemukan:\n");
            printf("NIS  : %s\n", db->data[i].nis);
            printf("Nama : %s\n", db->data[i].nama);
            printf("Masukkan Nilai Baru: ");
            scanf("%f", &db->data[i].nilai);
            
            while (db->data[i].nilai < 0 || db->data[i].nilai > 100) {
                printf("Nilai harus antara 0-100. Masukkan kembali: ");
                scanf("%f", &db->data[i].nilai);
            }
            
            printf("Nilai berhasil diperbarui!\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Mahasiswa dengan NIS %s tidak ditemukan.\n", nis);
    }
}

void lihatSemuaMahasiswa(struct Database *db) {
    if (db->jumlah == 0) {
        printf("Database kosong. Tidak ada data siswa.\n");
        return;
    }
    
    printf("\n--- Daftar Semua Mahasiswa ---\n");
    for (int i = 0; i < db->jumlah; i++) {
        printf("Data ke-%d:\n", i + 1);
        printf("NIS     : %s\n", db->data[i].nis);
        printf("Username: %s\n", db->data[i].username);
        printf("Nama    : %s\n", db->data[i].nama);
        printf("Nilai   : %.2f\n", db->data[i].nilai);
        printf("\n");
    }
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
            printf("NIS     : %s\n", db->data[i].nis);
            printf("Username: %s\n", db->data[i].username);
            printf("Nama    : %s\n", db->data[i].nama);
            printf("Nilai   : %.2f\n", db->data[i].nilai);
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
        fprintf(file, "%s;%s;%s;%.2f\n", 
                db->data[i].nis, 
                db->data[i].username,
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
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        struct Mahasiswa mhs;
        char *token;
        
        token = strtok(line, ";");
        strcpy(mhs.nis, token);
        
        token = strtok(NULL, ";");
        strcpy(mhs.username, token);
        
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

void tambahAkunMahasiswa(struct Database *db) {
    struct siswa daftar;
    dataAkun_siswa = fopen("dataAkun_siswa.dat", "ab");
    
    printf("\n--- Tambah Akun Mahasiswa ---\n");
    printf("Masukkan Username: ");
    fgets(daftar.usersiswa, 100, stdin);
    daftar.usersiswa[strcspn(daftar.usersiswa, "\n")] = 0;
    
    printf("Masukkan Nama: ");
    fgets(daftar.nama, 100, stdin);
    daftar.nama[strcspn(daftar.nama, "\n")] = 0;
    
    printf("Masukkan NIS: ");
    scanf("%d", &daftar.nis);
    getchar();
    
    // Validasi NIS unik di database_mahasiswa.txt
    struct Database temp_db;
    initDatabase(&temp_db);
    bacaDariFile(&temp_db);
    char nisString[20];
    sprintf(nisString, "%d", daftar.nis);
    for (int i = 0; i < temp_db.jumlah; i++) {
        if (strcmp(temp_db.data[i].nis, nisString) == 0) {
            printf("Error: NIS sudah terdaftar!\n");
            fclose(dataAkun_siswa);
            return;
        }
    }
    
    // Simpan ke database_mahasiswa.txt
    struct Mahasiswa mhs;
    strcpy(mhs.nis, nisString);
    strcpy(mhs.username, daftar.usersiswa);
    strcpy(mhs.nama, daftar.nama);
    mhs.nilai = 0.0; // Nilai default
    db->data[db->jumlah] = mhs;
    db->jumlah++;
    simpanKeFile(db);
    
    // Simpan ke dataAkun_siswa.dat (password = NIS)
    strcpy(daftar.passiswa, nisString);
    fwrite(&daftar, sizeof(struct siswa), 1, dataAkun_siswa);
    printf("Akun mahasiswa berhasil ditambahkan!\n");
    
    fclose(dataAkun_siswa);
}

void guru() {
    system("cls");
    int n;
    int coba = 3;

    printf("Selamat datang Guru SMA Ngawi\n");
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
    printf("Selamat datang Siswa SMA Ngawi\n");
    printf("Pilih Menu : \n");
    printf("1. Login Siswa\n");
    printf("2. Keluar\n");
    printf("Silahkan pilih menu : "); scanf("%d", &n);
    getchar();
    switch (n) {
    case 1:
        loginSiswa(coba);
        break;
    case 2:
        main();
        break;
    default:
        printf("Pilihan tidak valid!! Silahkan direfresh ulang..");
        break;
    }
}

void admin() {
    system("cls");
    int coba = 3;
    char username[100], password[100];
    
    printf("=== Login Admin ===\n");
    printf("Masukkan Username: "); gets(username);
    printf("Masukkan Password: "); gets(password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Selamat Datang Admin di Pusat Pendataan SMA Ngawi!!\n");
        menuAdmin();
    } else {
        coba--;
        if (coba > 0) {
            printf("Username atau password salah, silahkan coba lagi!\n");
            printf("Kesempatan anda tersisa %d \n", coba);
            system("pause");
            system("cls");
            admin();
        } else {
            printf("Kesempatan anda sudah habis, silahkan refresh.\n");
            system("pause");
            system("cls");
            main();
        }
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

int loginSiswa(int attempt) {
    system("cls");
    dataAkun_siswa = fopen("dataAkun_siswa.dat", "rb");
    char usnsiswa[100], passiswa[100];

    printf("=== Silahkan Login ===\n");
    printf("Masukkan Username Siswa : "); gets(usnsiswa);
    printf("Masukkan Password (NIS) : "); gets(passiswa);

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
    printf("1. Lihat Data Siswa\n");
    printf("2. Input Nilai Siswa\n");
    printf("3. Cari Data Siswa\n");
    printf("4. Statistik Nilai\n");
    printf("5. Kembali ke Menu Utama\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();

    switch (n) {
    case 1:
        lihatSemuaMahasiswa(&db);
        system("pause");
        menuGuru();
        break;
    case 2:
        inputNilaiMahasiswa(&db);
        simpanKeFile(&db);
        system("pause");
        menuGuru();
        break;
    case 3:
        cariMahasiswa(&db);
        system("pause");
        menuGuru();
        break;
    case 4:
        tampilkanStatistik(&db);
        system("pause");
        menuGuru();
        break;
    case 5:
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
        lihatNilai();
        break;
    case 3:
        main();
        break;
    default:
        printf("Pilihan tidak valid!\n");
        system("pause");
        menuSiswa();
        break;
    }
}

void menuAdmin() {
    system("cls");
    struct Database db;
    initDatabase(&db);
    bacaDariFile(&db);
    
    int n;
    printf("=== Menu Admin ===\n");
    printf("1. Tambah Akun Mahasiswa\n");
    printf("2. Lihat Data Siswa\n");
    printf("3. Kembali ke Menu Utama\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();

    switch (n) {
    case 1:
        tambahAkunMahasiswa(&db);
        system("pause");
        menuAdmin();
        break;
    case 2:
        lihatSemuaMahasiswa(&db);
        system("pause");
        menuAdmin();
        break;
    case 3:
        simpanKeFile(&db);
        main();
        break;
    default:
        printf("Pilihan tidak valid!\n");
        system("pause");
        menuAdmin();
        break;
    }
}

int main() {
    int pilihan;
    
    printf("Selamat datang Civitas Akademia SMA Ngawi\n");
    printf("1. Guru\n");
    printf("2. Siswa\n");
    printf("3. Admin\n");
    printf("4. Keluar\n");
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
        admin();
        break;
    case 4:
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
    printf("=== Data Diri %s ===\n", aseli.usersiswa);
    printf("Nama Lengkap : %s\n", aseli.nama);
    printf("NIS : %d\n", aseli.nis);
    printf("\n");
    printf("Tekan enter untuk kembali ke menu siswa...\n");
    system("pause");
    system("cls");
    menuSiswa();
}

void lihatNilai() {
    system("cls");
    struct Database db;
    initDatabase(&db);
    bacaDariFile(&db);

    int found = 0;
    printf("=== Lihat Nilai %s ===\n", aseli.usersiswa);
    for (int i = 0; i < db.jumlah; i++) {
        if (strcmp(db.data[i].username, aseli.usersiswa) == 0) {
            printf("NIS  : %s\n", db.data[i].nis);
            printf("Nama : %s\n", db.data[i].nama);
            printf("Nilai: %.2f\n", db.data[i].nilai);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Nilai belum tersedia untuk siswa ini.\n");
    }

    printf("\n");
    printf("Tekan enter untuk kembali ke menu siswa...\n");
    system("pause");
    system("cls");
    menuSiswa();
}