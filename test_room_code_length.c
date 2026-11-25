#include "room.h"

int main(void) {
    RoomArray ra;
    init_room_array(&ra);

    char kode_valid[STR_LEN_SHORT];
    char kode_invalid[STR_LEN_SHORT + 1];

    /* Membuat kode sepanjang 31 karakter */
    memset(kode_valid, 'A', STR_LEN_SHORT - 1);
    kode_valid[STR_LEN_SHORT - 1] = '\0';

    /* Membuat kode sepanjang 32 karakter */
    memset(kode_invalid, 'B', STR_LEN_SHORT);
    kode_invalid[STR_LEN_SHORT] = '\0';

    printf("=== UJI PANJANG KODE ===\n");

    bool hasil_valid = add_room(
        &ra, kode_valid, "Gedung A", 1, 30, "AC"
    );

    bool hasil_invalid = add_room(
        &ra, kode_invalid, "Gedung A", 1, 30, "AC"
    );

    printf("\nKode 31 karakter: %s\n",
           hasil_valid ? "DITERIMA" : "DITOLAK");

    printf("Kode 32 karakter: %s\n",
           hasil_invalid ? "DITERIMA" : "DITOLAK");

    printf("Jumlah ruangan: %d\n", ra.count);

    if (hasil_valid && !hasil_invalid && ra.count == 1) {
        printf("\nTEST LULUS\n");
    } else {
        printf("\nTEST GAGAL\n");
    }

    return 0;
}   