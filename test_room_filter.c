#include "room.h"

int main(void) {
    RoomArray ra;
    init_room_array(&ra);

    /* Data sampel */
    add_room(&ra, "R101", "Gedung A", 1, 40,
             "Proyektor, AC, Whiteboard");

    add_room(&ra, "R102", "Gedung A", 1, 45,
             "Proyektor, AC");

    add_room(&ra, "R201", "Gedung B", 2, 60,
             "Proyektor, Sound System");

    add_room(&ra, "LAB01", "Gedung Lab", 3, 35,
             "35 PC, AC");

    add_room(&ra, "AUD01", "Auditorium", 1, 200,
             "Sound System, Proyektor");

    printf("\n=== UJI FILTER PROYEKTOR ===\n");
    int hasil1 = filter_rooms_by_facility(&ra, "Proyektor");

    printf("\n=== UJI FILTER AC ===\n");
    int hasil2 = filter_rooms_by_facility(&ra, "AC");

    printf("\n=== UJI FILTER FASILITAS TIDAK ADA ===\n");
    int hasil3 = filter_rooms_by_facility(&ra, "Wifi");

    printf("\n=== HASIL PENGUJIAN ===\n");

    if (hasil1 == 4 && hasil2 == 3 && hasil3 == 0) {
        printf("TEST LULUS\n");
    } else {
        printf("TEST GAGAL\n");
    }

    return 0;
}