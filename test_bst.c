/*
 * test_bst.c - Pengujian modul BST (Anggota 3)
 * Kompilasi (di folder proyek, memakai room.h & common.h asli tim):
 *   gcc -Wall -Wextra test_bst.c bst.c -o test_bst -lm
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

static int pass = 0, fail = 0;
#define CHECK(desc, cond) do { \
    if (cond) { printf("  [PASS] %s\n", desc); pass++; } \
    else      { printf("  [FAIL] %s\n", desc); fail++; } } while (0)

static void make_room(Room *r, const char *code) {
    memset(r, 0, sizeof(*r));
    strncpy(r->code, code, sizeof(r->code) - 1);
    strcpy(r->building, "Gedung A");
    r->floor = 1; r->capacity = 30;
}

/* ambil kode in-order ke satu string untuk dicek urutannya */
static void collect(const BSTNode *n, char *out) {
    if (!n) return;
    collect(n->left, out);
    strcat(out, n->room->code); strcat(out, " ");
    collect(n->right, out);
}

int main(void) {
    Room rooms[7];
    const char *codes[7] = {"D101", "B202", "F303", "A101", "C105", "E404", "G505"};
    for (int i = 0; i < 7; i++) make_room(&rooms[i], codes[i]);

    BSTNode *root = NULL;
    int ok;

    printf("== 1. Insert ==\n");
    for (int i = 0; i < 7; i++) root = bst_insert(root, &rooms[i], &ok);
    CHECK("7 node masuk", bst_count(root) == 7);
    Room dup; make_room(&dup, "d101");              /* beda huruf besar/kecil */
    root = bst_insert(root, &dup, &ok);
    CHECK("duplikat (case-insensitive) ditolak", ok == 0 && bst_count(root) == 7);
    root = bst_insert(root, NULL, &ok);
    CHECK("insert NULL aman", ok == 0 && bst_count(root) == 7);

    printf("== 2. Search ==\n");
    Room *f = bst_search(root, "C105");
    CHECK("cari C105 ketemu", f == &rooms[4]);
    CHECK("cari c105 (huruf kecil) ketemu", bst_search(root, "c105") == &rooms[4]);
    CHECK("cari Z999 -> NULL", bst_search(root, "Z999") == NULL);
    CHECK("search pada pohon kosong -> NULL", bst_search(NULL, "A101") == NULL);
    int steps = 0; bst_search_steps(root, "G505", &steps);
    CHECK("G505 (daun terdalam) = 3 langkah (D101->F303->G505)", steps == 3);

    printf("== 3. In-order (harus terurut abjad) ==\n");
    char buf[256] = "";
    collect(root, buf);
    printf("  hasil: %s\n", buf);
    CHECK("urutan benar", strcmp(buf, "A101 B202 C105 D101 E404 F303 G505 ") == 0);
    printf("  cetak bst_inorder():\n");
    bst_inorder(root);

    printf("== 4. Tinggi pohon ==\n");
    CHECK("tinggi = 3 (seimbang sempurna)", bst_height(root) == 3);
    CHECK("tinggi pohon kosong = 0", bst_height(NULL) == 0);

    printf("== 5. Delete 3 kasus ==\n");
    int del;
    del = 0; root = bst_delete(root, "A101", &del);          /* daun */
    CHECK("hapus daun A101", del == 1 && bst_search(root, "A101") == NULL && bst_count(root) == 6);

    del = 0; root = bst_delete(root, "B202", &del);          /* kini 1 anak (C105) */
    CHECK("hapus node 1 anak B202", del == 1 && bst_search(root, "B202") == NULL
                                    && bst_search(root, "C105") != NULL && bst_count(root) == 5);

    del = 0; root = bst_delete(root, "D101", &del);          /* root, 2 anak */
    CHECK("hapus root 2 anak D101", del == 1 && bst_search(root, "D101") == NULL && bst_count(root) == 4);
    buf[0] = 0; collect(root, buf);
    CHECK("urutan tetap benar setelah delete", strcmp(buf, "C105 E404 F303 G505 ") == 0);
    CHECK("successor E404 jadi root", root->room == &rooms[5]);

    del = 0; root = bst_delete(root, "Z999", &del);
    CHECK("hapus kode tak ada -> deleted=0", del == 0 && bst_count(root) == 4);
    del = 0; BSTNode *e = bst_delete(NULL, "A", &del);
    CHECK("hapus di pohon kosong aman", e == NULL && del == 0);

    bst_free(root);

    printf("== 6. Skala besar & keseimbangan (n = 1000) ==\n");
    static Room big[1000];
    BSTNode *acak = NULL, *urut = NULL;
    srand(42);
    /* kode unik KRxxxx; urutan acak lewat Fisher-Yates */
    int idx[1000];
    for (int i = 0; i < 1000; i++) idx[i] = i;
    for (int i = 999; i > 0; i--) { int j = rand() % (i + 1); int t = idx[i]; idx[i] = idx[j]; idx[j] = t; }
    for (int i = 0; i < 1000; i++) { char c[16]; sprintf(c, "R%04d", i); make_room(&big[i], c); }
    for (int i = 0; i < 1000; i++) acak = bst_insert(acak, &big[idx[i]], &ok);
    for (int i = 0; i < 1000; i++) urut = bst_insert(urut, &big[i], &ok);   /* data sudah terurut */
    int h_acak = bst_height(acak), h_urut = bst_height(urut);
    printf("  Insert ACAK   : tinggi = %d  (tinggi minimum teoritis = %d)\n", h_acak, (int)ceil(log2(1000)) );
    printf("  Insert TERURUT: tinggi = %d  (kasus terburuk = n)\n", h_urut);
    CHECK("pohon acak jauh lebih rendah dari 1000", h_acak < 40);
    CHECK("pohon terurut degenerate (tinggi = 1000)", h_urut == 1000);
    int s1, s2;
    bst_search_steps(acak, "R0999", &s1);
    bst_search_steps(urut, "R0999", &s2);
    printf("  Cari R0999: BST acak = %d perbandingan, BST terurut = %d, array sekuensial <= 1000\n", s1, s2);
    bst_free(acak); bst_free(urut);

    printf("\nHASIL: %d lulus, %d gagal\n", pass, fail);
    return fail ? 1 : 0;
}
