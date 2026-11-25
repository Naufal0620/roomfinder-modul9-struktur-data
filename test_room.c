
#include "room.h"

int main() {

    RoomArray room_array;

    init_room_array(&room_array);

    /* Data sampel */
    add_room(&room_array, "R101", "Gedung A", 1, 40,
             "Proyektor, AC, Whiteboard");

    add_room(&room_array, "R102", "Gedung A", 1, 45,
             "Proyektor, AC");

    add_room(&room_array, "R201", "Gedung B", 2, 60,
             "Proyektor, Sound System");

    add_room(&room_array, "LAB01", "Gedung Lab", 3, 35,
             "35 PC, AC");

    add_room(&room_array, "AUD01", "Auditorium", 1, 200,
             "Sound System, Proyektor");

    printf("\n=== DAFTAR RUANGAN ===\n");

    display_all_rooms(&room_array);

    printf("\n=== UJI DUPLIKASI ===\n");

    add_room(&room_array, "R101", "Gedung A", 1, 50,
             "AC");

    printf("\n=== UJI PERUBAHAN ===\n");

    update_room(&room_array, "R102", "Gedung A", 2, 50,
                "Proyektor, AC, Whiteboard");

    display_all_rooms(&room_array);

    printf("\n=== UJI PENGHAPUSAN ===\n");

    delete_room(&room_array, "R201");

    display_all_rooms(&room_array);

    printf("\n=== UJI RUANGAN TIDAK DITEMUKAN ===\n");

    delete_room(&room_array, "R999");

    printf("\nPengujian Job 1 selesai.\n");

    return 0;
}
