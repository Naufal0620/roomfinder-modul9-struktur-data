
#include <stdio.h>
#include "room.h"

int main() {
    RoomArray ra;
    char code[STR_LEN_SHORT];
    int berhasil = 0;

    init_room_array(&ra);

    printf("=== TEST BATAS KAPASITAS ROOM ARRAY ===\n");

    // Mengisi 200 ruangan
    for (int i = 1; i <= 200; i++) {
        snprintf(code, sizeof(code), "R%03d", i);

        if (add_room(&ra, code, "Gedung A", 1, 40, "AC")) {
            berhasil++;
        } else {
            printf("Gagal menambahkan ruangan ke-%d\n", i);
            break;
        }
    }

    printf("\n=== HASIL PENGISIAN 200 RUANGAN ===\n");
    printf("Berhasil ditambahkan : %d\n", berhasil);
    printf("Jumlah dalam array   : %d\n", ra.count);

    // Mencoba menambahkan ruangan ke-201
    printf("\n=== TEST RUANGAN KE-201 ===\n");

    int hasil_201 = add_room(
        &ra, "R201", "Gedung B", 2, 50, "Proyektor"
    );

    if (hasil_201) {
        printf("ERROR: Ruangan ke-201 diterima!\n");
    } else {
        printf("Ruangan ke-201 berhasil ditolak.\n");
    }

    printf("\n=== VERIFIKASI AKHIR ===\n");
    printf("Jumlah akhir array : %d\n", ra.count);

    if (berhasil == 200 && !hasil_201 && ra.count == 200) {
        printf("STATUS: TEST LULUS\n");
    } else {
        printf("STATUS: TEST GAGAL\n");
    }

    return 0;
}
