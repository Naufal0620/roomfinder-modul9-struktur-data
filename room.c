
#include "room.h"

/* Inisialisasi Array ruangan */
void init_room_array(RoomArray* ra) {
    if (ra == NULL) return;

    ra->count = 0;
}

/* Tambah ruangan */
bool add_room(RoomArray* ra, const char* code,
              const char* building, int floor,
              int capacity, const char* facilities) {

    if (ra == NULL || code == NULL || building == NULL ||
        facilities == NULL) {
        return false;
    }

    /* Cek kapasitas Array */
    if (ra->count >= MAX_ROOMS) {
        printf("[Error] Kapasitas penyimpanan ruangan penuh!\n");
        return false;
    }

    /* Validasi data */
    if (strlen(code) == 0 || strlen(building) == 0 ||
        strlen(facilities) == 0 || floor < 0 || capacity <= 0) {
        printf("[Error] Data ruangan tidak valid!\n");
        return false;
    }

    /* Cek kode ruangan duplikat */
    for (int i = 0; i < ra->count; i++) {
        if (strcasecmp(ra->rooms[i].code, code) == 0) {
            printf("[Error] Kode ruangan '%s' sudah terdaftar!\n", code);
            return false;
        }
    }

    /* Ambil slot Array berikutnya */
    Room* r = &ra->rooms[ra->count];

    strncpy(r->code, code, STR_LEN_SHORT - 1);
    r->code[STR_LEN_SHORT - 1] = '\0';

    strncpy(r->building, building, STR_LEN_MID - 1);
    r->building[STR_LEN_MID - 1] = '\0';

    r->floor = floor;
    r->capacity = capacity;

    strncpy(r->facilities, facilities, STR_LEN_LONG - 1);
    r->facilities[STR_LEN_LONG - 1] = '\0';

    /* Ruangan baru belum memiliki jadwal */
    r->schedule_head = NULL;

    ra->count++;

    printf("[Sukses] Ruangan %s berhasil ditambahkan!\n", code);

    return true;
}

/* Ubah data ruangan */
bool update_room(RoomArray* ra, const char* code,
                 const char* building, int floor,
                 int capacity, const char* facilities) {

    if (ra == NULL || code == NULL || building == NULL ||
        facilities == NULL) {
        return false;
    }

    if (strlen(building) == 0 || strlen(facilities) == 0 ||
        floor < 0 || capacity <= 0) {
        printf("[Error] Data perubahan tidak valid!\n");
        return false;
    }

    for (int i = 0; i < ra->count; i++) {

        if (strcasecmp(ra->rooms[i].code, code) == 0) {

            strncpy(ra->rooms[i].building, building,
                    STR_LEN_MID - 1);
            ra->rooms[i].building[STR_LEN_MID - 1] = '\0';

            ra->rooms[i].floor = floor;
            ra->rooms[i].capacity = capacity;

            strncpy(ra->rooms[i].facilities, facilities,
                    STR_LEN_LONG - 1);
            ra->rooms[i].facilities[STR_LEN_LONG - 1] = '\0';

            printf("[Sukses] Data ruangan %s berhasil diperbarui!\n", code);

            return true;
        }
    }

    printf("[Error] Ruangan %s tidak ditemukan!\n", code);
    return false;
}

/* Hapus ruangan */
bool delete_room(RoomArray* ra, const char* code) {

    if (ra == NULL || code == NULL) {
        return false;
    }

    int target_idx = -1;

    /* Cari indeks ruangan */
    for (int i = 0; i < ra->count; i++) {

        if (strcasecmp(ra->rooms[i].code, code) == 0) {
            target_idx = i;
            break;
        }
    }

    if (target_idx == -1) {
        printf("[Error] Ruangan %s tidak ditemukan!\n", code);
        return false;
    }

    /* Bebaskan Linked List jadwal milik ruangan */
    free_schedules(ra->rooms[target_idx].schedule_head);

    ra->rooms[target_idx].schedule_head = NULL;

    /* Geser elemen Array */
    for (int i = target_idx; i < ra->count - 1; i++) {
        ra->rooms[i] = ra->rooms[i + 1];
    }

    ra->count--;

    /* Bersihkan slot terakhir yang tidak lagi digunakan */
    memset(&ra->rooms[ra->count], 0, sizeof(Room));

    printf("[Sukses] Ruangan %s berhasil dihapus!\n", code);

    return true;
}

/* Tampilkan seluruh ruangan */
void display_all_rooms(const RoomArray* ra) {

    if (ra == NULL || ra->count == 0) {
        printf("Belum ada data ruangan.\n");
        return;
    }

    printf("========================================================================================\n");
    printf("%-8s | %-15s | %-7s | %-10s | %-30s\n",
           "Kode", "Gedung", "Lantai", "Kapasitas", "Fasilitas");
    printf("========================================================================================\n");

    for (int i = 0; i < ra->count; i++) {

        printf("%-8s | %-15s | Lt. %-3d | %-4d kursi | %-30s\n",
               ra->rooms[i].code,
               ra->rooms[i].building,
               ra->rooms[i].floor,
               ra->rooms[i].capacity,
               ra->rooms[i].facilities);
    }

    printf("========================================================================================\n");
    printf("Total: %d ruangan terdaftar.\n", ra->count);
}

/* Tampilkan detail ruangan */
void display_room_detail(const Room* room) {

    if (room == NULL) return;

    printf("\n=== DETAIL RUANGAN: %s ===\n", room->code);
    printf("Gedung    : %s (Lantai %d)\n",
           room->building, room->floor);
    printf("Kapasitas : %d orang\n", room->capacity);
    printf("Fasilitas : %s\n", room->facilities);

    printf("Jadwal Penggunaan:\n");
    print_schedules(room->schedule_head);

    printf("===============================\n");
}
