/*
Dzaki Imam Fawwaz - 2702367486
Date : 07 - okt - 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Untuk isdigit()

// Constanta
#define MAX_STRING_LENGTH 100

// Struct contact
typedef struct
{
    char nama[MAX_STRING_LENGTH];
    char noHp[MAX_STRING_LENGTH];
    char noKantor[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    char perusahaan[MAX_STRING_LENGTH];
} Contact;

// Header function yang dibutuhkan
void main_menu();
void add_contact(Contact **contacts, int *count);
void display_contacts(Contact *contacts, int count);
void delete_contact(Contact **contacts, int *count);
void clear_screen();
void thank_you();

int main()
{
    int pilihan;
    int count = 0;
    Contact *daftar_kontak = NULL;

    // Process / logika main function
    while (1)
    {
        main_menu();
        printf("\033[36mMasukkan pilihan menu dan tekan Enter: \033[0m");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            add_contact(&daftar_kontak, &count);
            break;
        case 2:
            display_contacts(daftar_kontak, count);
            break;
        case 3:
            delete_contact(&daftar_kontak, &count);
            break;
        case 4:
            clear_screen();
            break;
        case 5:
            free(daftar_kontak); // Membebaskan memori sebelum keluar dari program
            thank_you();
            return 0;
        default:
            printf("\033[31mPilihan tidak valid.\033[0m\n");
            break;
        }

        // Membersihkan buffer stdin
        while (getchar() != '\n')
            ;
    }
}

// Function main menu
void main_menu()
{
    printf("\n==================================================\n");
    printf("        Selamat Datang di Dzaki Contact Book\n");
    printf("==================================================\n\n");
    printf("                   PILIH MENU\n");
    printf("==================================================\n");
    printf("1. Menambahkan data kontak\n");
    printf("2. Menampilkan data kontak\n");
    printf("3. Menghapus data kontak\n");
    printf("4. Clear Screen\n");
    printf("5. Keluar\n");
}

// Fungsi untuk menambahkan kontak baru
void add_contact(Contact **contacts, int *size)
{
    Contact new_contact;

    printf("Masukkan nama            : ");
    scanf(" %[^\n]s", new_contact.nama);

    // Loop untuk meminta input nomor HP yang benar
    do
    {
        printf("Masukkan nomor HP        : ");
        scanf("%s", new_contact.noHp);

        printf("Masukkan nomor kantor    : ");
        scanf("%s", new_contact.noKantor);

        // Pengecekan nomor HP
        int isValidHp = 1; // Untuk menandai apakah nomor HP valid
        for (int i = 0; new_contact.noHp[i] != '\0'; i++)
        {
            if (!isdigit(new_contact.noHp[i]))
            {
                isValidHp = 0; // Nomor kantor tidak valid
                break;
            }
        }

        // Pengecekan nomor kantor
        int isValidKantor = 1; // Untuk menandai apakah nomor kantor valid
        for (int i = 0; new_contact.noKantor[i] != '\0'; i++)
        {
            if (!isdigit(new_contact.noKantor[i]))
            {
                isValidKantor = 0; // Nomor kantor tidak valid
                break;
            }
        }

        if (isValidHp && isValidKantor && strlen(new_contact.noHp) > 0 && strlen(new_contact.noKantor) > 0 &&
            strlen(new_contact.noHp) <= MAX_STRING_LENGTH && strlen(new_contact.noKantor) <= MAX_STRING_LENGTH)
        {
            break; // Keluar dari loop jika nomor HP dan nomor kantor valid
        }
        else
        {
            printf("\033[31mNomor hanya boleh berisi angka.\nSilakan coba lagi.\033[0m\n");
        }
    } while (1);

    printf("Masukkan email           : ");
    scanf(" %99[^\n]s", new_contact.email); //menggunakan 99 untuk membatasi inputan user
    printf("Masukkan nama perusahaan : ");
    scanf(" %99[^\n]s", new_contact.perusahaan);

    (*size)++;                                                            // menambahkan satu nilai setiap kontak ditambahkan
    *contacts = (Contact *)realloc(*contacts, sizeof(Contact) * (*size)); // mengubah ukuran dari array dinamis sesuai dengan jumlah kontak

    if (*contacts == NULL)
    {
        printf("\033[31Error dalam alokasi memori!\033[0m\n");
        exit(1);
    }

    (*contacts)[*size - 1] = new_contact;
    printf("\n\033[32m==================================\n");
    printf("  Kontak berhasil ditambahkan!\n");
    printf("==================================\033[0m\n"); 
}

// Function display
void display_contacts(Contact *contacts, int count)
{
    if (count == 0)
    {
        printf("\nDaftar kontak kosong.\n");
    }
    else
    {
        printf("\n================= DAFTAR KONTAK =================\n");
        for (int i = 0; i < count; i++)
        {
            printf("Kontak ke-%d\n", i + 1);
            printf("Nama            : %s\n", contacts[i].nama);
            printf("Nomor HP        : %s\n", contacts[i].noHp);
            printf("Nomor Kantor    : %s\n", contacts[i].noKantor);
            printf("Email           : %s\n", contacts[i].email);
            printf("Nama Perusahaan : %s\n", contacts[i].perusahaan);
            printf("--------------------------------------\n");
        }
    }
}

// Function delete
void delete_contact(Contact **contacts, int *count)
{
    if (*count > 0)
    {
        printf("\nPilih nomor kontak yang ingin dihapus (1-%d): ", *count);
        int nomor;
        scanf("%d", &nomor);

        if (nomor >= 1 && nomor <= *count)
        {
            // Geser data setelah kontak yang dihapus
            for (int i = nomor - 1; i < *count - 1; i++)
            {
                (*contacts)[i] = (*contacts)[i + 1];
            }

            // Mengurangi ukuran alokasi memori
            *contacts = (Contact *)realloc(*contacts, (*count - 1) * sizeof(Contact));
            (*count)--;
            printf("\nKontak nomor %d telah dihapus.\n", nomor);
        }
        else
        {
            printf("\n\033[31Nomor kontak tidak valid.\033[0m\n");
        }
    }
    else
    {
        printf("\nDaftar kontak kosong. Tidak ada yang bisa dihapus.\n");
    }
}

// Function Clear screen
void clear_screen()
{
    printf("\033[2J");
    printf("\033[H");
}

// Function Terimakasih
void thank_you()
{
    printf("\n\033[32m----------------------------------\n");
    printf("          Terimakasih \n");
    printf("   Semoga harimu menyenangkan :)\n");
    printf("----------------------------------\033[0m\n");
}

