/*
DZAKI IMAM FAWWAZ - 2702367486
Date    : 07 - okt - 2023
version : 001.01.002

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constanta
#define MAX_BUKU 100
#define MAX_STRING_LENGTH 100

//enum penerbit
typedef enum
{
    GRAMEDIA,
    ELEXMEDIA,
    ANDI_OFFSET,
    PUSTAKA,
} PenerbitChoice;

//enum kategori
typedef enum
{
	Buku_Fiksi,
	Buku_Teks, 
	Buku_Sejarah, 
	Buku_Novel
    
} KategoriChoice;

// struct buku
typedef struct
{
    int isbn;
    char judul[MAX_STRING_LENGTH];
    char pengarang[MAX_STRING_LENGTH];
    int tahun_terbit;
    PenerbitChoice penerbit;
    KategoriChoice kategori;
} Buku;

// header function yang diperlukan program 
void main_menu();
void add_book(Buku buku[], int *count);
void display_books(Buku buku[], int count);
void delete_book(Buku buku[], int *count);
void clear_screen();
void thank_you();

// main function 
int main()
{
    int pilihan;
    int count = 0;
    Buku daftar_buku[MAX_BUKU];
	
	// process atau logika untuk main menu
    while (1)
    {
        main_menu();
        printf("\033[36mMasukkan pilihan menu dan tekan Enter: \033[0m");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            add_book(daftar_buku, &count);
            break;
        case 2:
            display_books(daftar_buku, count);
            break;
        case 3:
            delete_book(daftar_buku, &count);
            break;
        case 4:
            clear_screen();
            break;
        case 5:
            thank_you();
            exit(0);
        default:
            printf("\033[31mPilihan tidak valid.\033[0m\n");
            break;
        }
    }
    return 0;
}

// function main menu
void main_menu()
{
    printf("\n==================================================\n");
    printf("        Selamat Datang di Dzaki Library\n");
    printf("==================================================\n\n");
    printf("                   PILIH MENU\n");
    printf("==================================================\n");
    printf("1. Menambahkan data buku\n");
    printf("2. Menampilkan data buku\n");
    printf("3. Menghapus data buku\n");
    printf("4. Clear Screen\n");
    printf("5. Keluar\n");
}

// function add book
void add_book(Buku buku[], int *count)
{
    if (*count < MAX_BUKU)
    {
        printf("\n--------------------------------------\n");
        printf("Masukkan ISBN buku ke-%d : ", *count + 1);
        while (scanf("%d", &buku[*count].isbn) != 1)
        {
            printf("\033[31mPilihan tidak valid.\nMasukkan kembali ISBN buku ke-%d : \033[0m", *count + 1);
            while (getchar() != '\n')
                ;
        }
        // menggunakan fgets, agar semua karakter yang diinput user sebelum enter dapat di terima program 
        printf("Masukkan judul buku ke-%d : ", *count + 1);
        getchar();
        fgets(buku[*count].judul, sizeof(buku[*count].judul), stdin);
        buku[*count].judul[strlen(buku[*count].judul) - 1] = '\0'; // untuk memberi tahu program, jika user mamasukkan enter maka = '\0'. yaitu tanda akhir dari string.
        
        // menggunakan fgets, agar semua karakter yang diinput user sebelum enter dapat di terima program
        printf("Masukkan pengarang buku ke-%d : ", *count + 1);
        fgets(buku[*count].pengarang, sizeof(buku[*count].pengarang), stdin);
        buku[*count].pengarang[strlen(buku[*count].pengarang) - 1] = '\0';// untuk memberi tahu program, jika user mamasukkan enter maka = '\0'. yaitu tanda akhir dari string.
        
        // menggunakan scanf untuk tahun terbit
        printf("Masukkan tahun terbit buku ke-%d : ", *count + 1);
        while (scanf("%d", &buku[*count].tahun_terbit) != 1 || buku[*count].tahun_terbit < 0)
        {
            printf("\033[31mInput tahun terbit tidak valid.\nMasukkan kembali tahun terbit buku ke-%d : \033[0m", *count + 1);
            while (getchar() != '\n')
                ;
        }
		
		// menggunakan do while dan menu, agar jika user memasukkan kode yang salah maka akan diulang
        do
        {
            printf("\nPilihan Penerbit:\n");
            printf("0. Gramedia\n");
            printf("1. Elexmedia\n");
            printf("2. Andi Offset\n");
            printf("3. Pustaka\n");
            printf("\033[36mMasukkan penerbit buku ke-%d (0-3): \033[0m", *count + 1);
            scanf("%d", (int *)&buku[*count].penerbit);

            if (buku[*count].penerbit < GRAMEDIA || buku[*count].penerbit > PUSTAKA)
            {
                printf("\033[31mPilihan penerbit tidak valid.\nHarap masukkan pilihan (0-3).\033[0m\n");
            }
        } while (buku[*count].penerbit < GRAMEDIA || buku[*count].penerbit > PUSTAKA);
		
		// menggunakan do while dan menu, agar jika user memasukkan kode yang salah maka akan diulang
        do
        {
            printf("\nPilihan Kategori:\n");
            printf("0. Buku Fiksi\n");
            printf("1. Buku Teks\n");
            printf("2. Buku Sejarah\n");
            printf("3. Buku Novel\n");
            printf("\033[36mMasukkan kategori buku ke-%d (0-3):\033[0m", *count + 1);
            scanf("%d", (int *)&buku[*count].kategori);

            if (buku[*count].kategori < Buku_Fiksi || buku[*count].kategori > Buku_Novel)
            {
                printf("\033[31mPilihan penerbit tidak valid.\nHarap masukkan pilihan (0-3).\033[0m\n");
            }
        } while (buku[*count].kategori < Buku_Fiksi || buku[*count].kategori > Buku_Novel);

        (*count)++;
        printf("\n-----------------------------------");
        printf("\n\033[32mBuku telah ditambahkan.\033[0m\n");
        printf("-----------------------------------\n");
    }
    else
    {
        printf("Daftar buku sudah penuh. Tidak bisa menambahkan lebih banyak buku.\n"); // max 100 buku
    }
}

// function display book
void display_books(Buku buku[], int count)
{
    if (count == 0)
    {
        printf("\nDaftar buku kosong.\n");
    }
    else
    {
        printf("\n================= DAFTAR BUKU =================\n");
        for (int i = 0; i < count; i++)
        {
            printf("Buku ke-%d\n", i + 1);
            printf("ISBN: %d\n", buku[i].isbn);
            printf("Judul: %s\n", buku[i].judul);
            printf("Pengarang: %s\n", buku[i].pengarang);
            printf("Tahun Terbit: %d\n", buku[i].tahun_terbit);
            printf("Penerbit: ");

            switch (buku[i].penerbit)
            {
            case GRAMEDIA:
                printf("Gramedia\n");
                break;
            case ELEXMEDIA:
                printf("Elexmedia\n");
                break;
            case ANDI_OFFSET:
                printf("Andi Offset\n");
                break;
            case PUSTAKA:
                printf("Pustaka\n");
                break;
            default:
                printf("Tidak Diketahui\n");
                break;
            }
            
            printf("kategori: ");

            switch (buku[i].kategori)
            {
            case Buku_Fiksi:
                printf("Buku Fiksi\n");
                break;
            case Buku_Teks:
                printf("Buku Teks\n");
                break;
            case Buku_Sejarah:
                printf("Buku Sejarah\n");
                break;
            case Buku_Novel:
                printf("Buku Novel\n");
                break;
            default:
                printf("Tidak Diketahui\n");
                break;
            }
            printf("--------------------------------------\n");
        }
    }
}

// function delete book
void delete_book(Buku buku[], int *count)
{
    if (*count > 0)
    {
        printf("\nPilih nomor buku yang ingin dihapus (1-%d): ", *count);
        int nomor;
        scanf("%d", &nomor);

        if (nomor >= 1 && nomor <= *count)
        {
            for (int i = nomor - 1; i < *count - 1; i++)
            {
                buku[i] = buku[i + 1];
            }
            (*count)--;
            printf("\nBuku nomor %d telah dihapus.\n", nomor);
        }
        else
        {
            printf("\nNomor buku tidak valid.\n");
        }
    }
    else
    {
        printf("\nDaftar buku kosong. Tidak ada yang bisa dihapus.\n");
    }
}

// function clear screen
void clear_screen()
{
    printf("\033[2J");
    printf("\033[H");
}

// function terima kasih
void thank_you()
{
    printf("\n----------------------------------\n");
    printf("          Terimakasih :)\n");
    printf("   Semoga harimu menyenangkan :)\n");
    printf("----------------------------------\n");
}
