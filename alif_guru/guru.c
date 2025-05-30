#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MAHASISWA 100
#define MAX_NAMA 50
#define MAX_PASSWORD 20

struct Mahasiswa {
    char nis[20];
    char nama[MAX_NAMA];
    float nilai;
};

struct Database {
    struct Mahasiswa data[MAX_MAHASISWA];
    int jumlah;
};

void initDatabase(struct Database *db) {
    db->jumlah = 0;
}

void tambahMahasiswa(struct Database *db) {
    if (db->jumlah >= MAX_MAHASISWA) {
        printf("Database penuh! Tidak bisa menambah data lagi.\n");
        return;
    }

    struct Mahasiswa mhs;
    
    printf("\n--- Tambah Data Mahasiswa ---\n");
    
    // Input NIS
    printf("Masukkan NIS: ");
    scanf("%s", mhs.nis);
    
    // Validasi NIS unik
    for (int i = 0; i < db->jumlah; i++) {
        if (strcmp(db->data[i].nis, mhs.nis) == 0) {
            printf("Error: NIS sudah terdaftar!\n");
            return;
        }
    }
    
    // Input Nama
    printf("Masukkan Nama: ");
    scanf(" %[^\n]s", mhs.nama); // Membaca string dengan spasi
    
    // Input Nilai
    printf("Masukkan Nilai: ");
    scanf("%f", &mhs.nilai);
    
    // Validasi nilai antara 0-100
    while (mhs.nilai < 0 || mhs.nilai > 100) {
        printf("Nilai harus antara 0-100. Masukkan kembali: ");
        scanf("%f", &mhs.nilai);
    }
    
    // Tambahkan ke database
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

void menuGuru() {
    struct Database db;
    initDatabase(&db);
    bacaDariFile(&db);
    
    int pilihan;
    
    do {
        printf("\n=== MENU GURU ===\n");
        printf("1. Tambah Data Mahasiswa\n");
        printf("2. Cari Mahasiswa berdasarkan NIS\n");
        printf("3. Tampilkan Statistik Nilai\n");
        printf("4. Simpan Data ke File\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                tambahMahasiswa(&db);
                break;
            case 2:
                cariMahasiswa(&db);
                break;
            case 3:
                tampilkanStatistik(&db);
                break;
            case 4:
                simpanKeFile(&db);
                break;
            case 0:
                printf("Keluar dari menu guru.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

int main() {
    // Contoh penggunaan
    printf("=== Sistem Manajemen Nilai Mahasiswa ===\n");
    printf("Login sebagai guru...\n\n");
    
    menuGuru();
    
    return 0;
}