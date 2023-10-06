#include <stdio.h>
#include <string.h>

// Menggunakan typedef mengubah tag struct mahasiswa menjadi mhs 
typedef struct mahasiswa
{
    char nama[100];
    double nik;
} mhs;

// Tidak menggunakan typedef
struct dosen
{
    char nama[100];
    char nip[10];
};

int main()
{
	// menggunakan typedef lebih mudah dipahami dan lebih efisien
    mhs mahasiswa1; 
    strcpy(mahasiswa1.nama, "Dzaki Imam F");
    mahasiswa1.nik = 2702367486;

	// tidak menggunakan typedef sedikit sulit dipahami dan tidak efisien
    struct dosen dosen1; 
    strcpy(dosen1.nama, "Pak Tri Asih");
    strcpy(dosen1.nip, "D3783");

    printf("Nama mahasiswa : %s\n", mahasiswa1.nama);
    printf("Nik  mahasiswa : %0.f\n", mahasiswa1.nik);
    printf("\n");

    printf("Nama Dosen : %s\n", dosen1.nama);
    printf("Nip  Dosen : %s\n", dosen1.nip);
    printf("\n");

    return 0;
}

