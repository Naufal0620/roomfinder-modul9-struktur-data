/*
 * bst.h - MODUL 3: Binary Search Tree (Indeks Kode Ruangan)
 * Dikelola oleh: Anggota 3
 *
 * BST menyimpan POINTER ke Room (bukan salinan). Data Room dimiliki
 * oleh array milik Anggota 1, jadi BST tidak pernah free() Room.
 * Kunci pengurutan: room->code, dibandingkan tanpa membedakan huruf
 * besar/kecil (strcasecmp).
 */
#ifndef BST_H
#define BST_H

#include "room.h"   /* struct Room (Anggota 1), memakai field "code" */

typedef struct BSTNode {
    Room *room;               /* pointer ke data ruangan di array */
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/* ---- Operasi dasar ---- */

/* Sisipkan room ke pohon. Mengembalikan root baru.
 * *inserted = 1 jika berhasil, 0 jika kode sudah ada / gagal malloc / argumen NULL.
 * (inserted boleh NULL jika tidak dibutuhkan) */
BSTNode *bst_insert(BSTNode *root, Room *room, int *inserted);

/* Cari ruangan berdasarkan kode. Mengembalikan NULL jika tidak ada. */
Room *bst_search(const BSTNode *root, const char *code);

/* Sama seperti bst_search, tapi mencatat jumlah perbandingan ke *steps.
 * Berguna untuk benchmark/analisis (Anggota 4 & bab pengujian). */
Room *bst_search_steps(const BSTNode *root, const char *code, int *steps);

/* Hapus node berdasarkan kode. Mengembalikan root baru.
 * *deleted = 1 jika ada node yang dihapus. Room TIDAK di-free. */
BSTNode *bst_delete(BSTNode *root, const char *code, int *deleted);

/* ---- Fitur pembuktian akademis ---- */

/* In-order traversal: mencetak kode ruangan terurut abjad. */
void bst_inorder(const BSTNode *root);

/* Tinggi pohon. Pohon kosong = 0, satu node = 1. */
int bst_height(const BSTNode *root);

/* Jumlah node. */
int bst_count(const BSTNode *root);

/* Node dengan kode terkecil (NULL jika pohon kosong). */
BSTNode *bst_min(BSTNode *root);

/* Bangun ulang indeks BST dari seluruh isi RoomArray (dipakai main.c).
 * WAJIB dipanggil setelah add_room / delete_room, karena BST menyimpan
 * pointer ke elemen array yang bisa bergeser. Panggil bst_free(root_lama)
 * lebih dulu agar tidak bocor memori. */
BSTNode *rebuild_bst_index(const RoomArray *ra);

/* Bebaskan SEMUA node (post-order). Room tidak di-free.
 * Panggil saat program ditutup / sebelum membangun ulang indeks. */
void bst_free(BSTNode *root);

#endif /* BST_H */
