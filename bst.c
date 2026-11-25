/*
 * bst.c - MODUL 3: Binary Search Tree (Indeks Kode Ruangan)
 * Dikelola oleh: Anggota 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #define strcasecmp _stricmp      /* MinGW/MSVC di Windows */
#else
  #include <strings.h>             /* strcasecmp di Linux/macOS */
#endif

#include "bst.h"

/* ---------- helper internal ---------- */

static BSTNode *new_node(Room *room) {
    BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
    if (n == NULL) return NULL;
    n->room  = room;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

/* ---------- INSERT ---------- */

BSTNode *bst_insert(BSTNode *root, Room *room, int *inserted) {
    if (inserted) *inserted = 0;
    if (room == NULL) return root;

    if (root == NULL) {
        BSTNode *n = new_node(room);
        if (n != NULL && inserted) *inserted = 1;
        return n;                       /* NULL jika malloc gagal */
    }

    int cmp = strcasecmp(room->code, root->room->code);
    if (cmp < 0)
        root->left  = bst_insert(root->left,  room, inserted);
    else if (cmp > 0)
        root->right = bst_insert(root->right, room, inserted);
    /* cmp == 0: kode duplikat, tidak disisipkan (inserted tetap 0) */
    return root;
}

/* ---------- SEARCH ---------- */

Room *bst_search_steps(const BSTNode *root, const char *code, int *steps) {
    int count = 0;
    const BSTNode *cur = root;

    while (cur != NULL) {
        count++;
        int cmp = strcasecmp(code, cur->room->code);
        if (cmp == 0) {
            if (steps) *steps = count;
            return cur->room;
        }
        cur = (cmp < 0) ? cur->left : cur->right;
    }
    if (steps) *steps = count;
    return NULL;
}

Room *bst_search(const BSTNode *root, const char *code) {
    return bst_search_steps(root, code, NULL);
}

/* ---------- MIN ---------- */

BSTNode *bst_min(BSTNode *root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

/* ---------- DELETE (3 kasus) ---------- */

BSTNode *bst_delete(BSTNode *root, const char *code, int *deleted) {
    if (root == NULL) return NULL;          /* kode tidak ditemukan */

    int cmp = strcasecmp(code, root->room->code);

    if (cmp < 0) {
        root->left = bst_delete(root->left, code, deleted);
    } else if (cmp > 0) {
        root->right = bst_delete(root->right, code, deleted);
    } else {
        /* node ditemukan */
        if (deleted) *deleted = 1;

        /* Kasus 1: node daun (0 anak) */
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        /* Kasus 2a: hanya anak kanan */
        if (root->left == NULL) {
            BSTNode *child = root->right;
            free(root);
            return child;
        }
        /* Kasus 2b: hanya anak kiri */
        if (root->right == NULL) {
            BSTNode *child = root->left;
            free(root);
            return child;
        }
        /* Kasus 3: dua anak -> pakai in-order successor
         * (node terkecil di subtree kanan). Cukup salin pointer Room-nya,
         * lalu hapus node successor dari subtree kanan. */
        BSTNode *succ = bst_min(root->right);
        root->room = succ->room;
        root->right = bst_delete(root->right, succ->room->code, NULL);
    }
    return root;
}

/* ---------- TRAVERSAL, TINGGI, JUMLAH ---------- */

void bst_inorder(const BSTNode *root) {
    if (root == NULL) return;
    bst_inorder(root->left);
    printf("%s\n", root->room->code);
    bst_inorder(root->right);
}

int bst_height(const BSTNode *root) {
    if (root == NULL) return 0;
    int hl = bst_height(root->left);
    int hr = bst_height(root->right);
    return 1 + (hl > hr ? hl : hr);
}

int bst_count(const BSTNode *root) {
    if (root == NULL) return 0;
    return 1 + bst_count(root->left) + bst_count(root->right);
}

/* ---------- REBUILD ---------- */

BSTNode *rebuild_bst_index(const RoomArray *ra) {
    BSTNode *root = NULL;
    if (ra == NULL) return NULL;
    for (int i = 0; i < ra->count; i++)
        root = bst_insert(root, (Room *)&ra->rooms[i], NULL);
    return root;
}

/* ---------- FREE ---------- */

void bst_free(BSTNode *root) {
    if (root == NULL) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}
