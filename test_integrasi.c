/*
 * test_integrasi.c - Uji BST bersama modul asli Anggota 1 (room.c) & Anggota 2 (schedule.c)
 * Kompilasi:
 *   gcc -Wall -Wextra test_integrasi.c room.c schedule.c bst.c -o test_integrasi
 */
#include <stdio.h>
#include "room.h"
#include "bst.h"

static int pass = 0, fail = 0;
#define CHECK(d, c) do { if (c) { printf("  [PASS] %s\n", d); pass++; } \
                         else   { printf("  [FAIL] %s\n", d); fail++; } } while (0)

int main(void) {
    static RoomArray ra;
    init_room_array(&ra);
    add_room(&ra, "R101", "Gedung A", 1, 40, "Proyektor");
    add_room(&ra, "R102", "Gedung A", 1, 45, "Proyektor");
    add_room(&ra, "R201", "Gedung B", 2, 60, "AC");
    add_room(&ra, "LAB-01", "Gedung Lab", 3, 35, "PC");
    add_room(&ra, "AUD-01", "Auditorium", 1, 200, "Stage");

    BSTNode *root = rebuild_bst_index(&ra);
    CHECK("indeks berisi 5 ruangan", bst_count(root) == 5);
    CHECK("search R201 menunjuk elemen array yang benar", bst_search(root, "r201") == &ra.rooms[2]);

    /* hapus ruangan di tengah array -> elemen bergeser -> WAJIB rebuild */
    delete_room(&ra, "R102");
    bst_free(root);
    root = rebuild_bst_index(&ra);
    CHECK("setelah hapus R102: 4 node", bst_count(root) == 4);
    CHECK("R102 sudah tidak ditemukan", bst_search(root, "R102") == NULL);
    Room *r = bst_search(root, "LAB-01");
    CHECK("LAB-01 tetap menunjuk data yang benar setelah array bergeser", r != NULL && r->capacity == 35);

    add_room(&ra, "R301", "Gedung C", 3, 50, "AC");
    bst_free(root);
    root = rebuild_bst_index(&ra);
    CHECK("setelah tambah R301: 5 node", bst_count(root) == 5 && bst_search(root, "R301") != NULL);

    printf("-- in-order --\n");
    bst_inorder(root);

    CHECK("rebuild(NULL) aman", rebuild_bst_index(NULL) == NULL);

    bst_free(root);
    for (int i = 0; i < ra.count; i++) free_schedules(ra.rooms[i].schedule_head);
    printf("\nHASIL: %d lulus, %d gagal\n", pass, fail);
    return fail ? 1 : 0;
}
