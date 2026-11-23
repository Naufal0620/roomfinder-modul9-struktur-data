#ifndef ROOMFINDER_H
#define ROOMFINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROOMS 200
#define STR_LEN_SHORT 32
#define STR_LEN_MID 64
#define STR_LEN_LONG 128

/* ========================================================
 * 1. STRUKTUR DATA JADWAL (LINKED LIST) - TUGAS ANGGOTA 2
 * ======================================================== */
typedef struct ScheduleNode {
    int id;                                 // ID Unik jadwal
    char activity[STR_LEN_MID];             // Nama kegiatan / mata kuliah
    char day[STR_LEN_SHORT];                // Hari: Senin, Selasa, dll.
    int start_min;                          // Waktu mulai (menit sejak 00:00)
    int end_min;                            // Waktu selesai (menit sejak 00:00)
    char user_info[STR_LEN_MID];            // Dosen / kelas / penanggung jawab
    struct ScheduleNode* next;              // Pointer ke jadwal berikutnya
} ScheduleNode;

/* ========================================================
 * 2. STRUKTUR DATA RUANGAN (ARRAY) - TUGAS ANGGOTA 1
 * ======================================================== */
typedef struct {
    char code[STR_LEN_SHORT];               // Kode unik ruangan (misal: R201, LAB-01)
    char building[STR_LEN_MID];             // Nama atau kode gedung
    int floor;                              // Lantai
    int capacity;                           // Kapasitas maksimum orang
    char facilities[STR_LEN_LONG];          // Fasilitas (misal: Proyektor, AC, Papan Tulis)
    ScheduleNode* schedule_head;            // Pointer ke Linked List jadwal ruangan ini
} Room;

typedef struct {
    Room rooms[MAX_ROOMS];
    int count;
} RoomArray;

/* ========================================================
 * 3. STRUKTUR DATA INDEKS (BST) - TUGAS ANGGOTA 3
 * ======================================================== */
typedef struct BSTNode {
    char code[STR_LEN_SHORT];               // Kunci pencarian: kode ruangan
    Room* room_ptr;                         // Referensi ke struct Room di Array
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

/* ========================================================
 * PROTOTIPE FUNGSI UMUM & HELPER WAKTU
 * ======================================================== */
int time_to_minutes(int hour, int minute);
void minutes_to_time_str(int minutes, char* buffer);
bool is_time_overlap(int start1, int end1, int start2, int end2);

/* ========================================================
 * PROTOTIPE FUNGSI JADWAL (LINKED LIST) - ANGGOTA 2
 * ======================================================== */
ScheduleNode* create_schedule_node(int id, const char* activity, const char* day, int start_min, int end_min, const char* user_info);
bool add_schedule(ScheduleNode** head, ScheduleNode* new_schedule);
bool remove_schedule(ScheduleNode** head, int schedule_id);
void print_schedules(const ScheduleNode* head);
bool is_room_available(const ScheduleNode* head, const char* day, int start_min, int end_min);
void free_schedules(ScheduleNode* head);

/* ========================================================
 * PROTOTIPE FUNGSI RUANGAN (ARRAY) - ANGGOTA 1
 * ======================================================== */
void init_room_array(RoomArray* ra);
bool add_room(RoomArray* ra, const char* code, const char* building, int floor, int capacity, const char* facilities);
bool update_room(RoomArray* ra, const char* code, const char* building, int floor, int capacity, const char* facilities);
bool delete_room(RoomArray* ra, const char* code);
void display_all_rooms(const RoomArray* ra);
void display_room_detail(const Room* room);

/* ========================================================
 * PROTOTIPE FUNGSI BST (INDEKS PENCARIAN) - ANGGOTA 3
 * ======================================================== */
BSTNode* create_bst_node(const char* code, Room* room_ptr);
BSTNode* bst_insert(BSTNode* root, const char* code, Room* room_ptr);
Room* bst_search(BSTNode* root, const char* code);
BSTNode* bst_delete(BSTNode* root, const char* code);
void bst_free(BSTNode* root);
BSTNode* rebuild_bst_index(const RoomArray* ra);

/* ========================================================
 * PROTOTIPE INTEGRASI & PENCARIAN (INTEGRATOR) - ANGGOTA 4
 * ======================================================== */
void search_available_rooms(const RoomArray* ra, const char* day, int start_min, int end_min, int min_capacity, const char* building_filter);
void load_sample_data(RoomArray* ra, BSTNode** bst_root);
void cleanup_system(RoomArray* ra, BSTNode** bst_root);

#endif // ROOMFINDER_H
