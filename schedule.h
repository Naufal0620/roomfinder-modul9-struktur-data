#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "common.h"

/* ========================================================
 * STRUKTUR DATA JADWAL (LINKED LIST) - TUGAS ANGGOTA 2
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
 * PROTOTIPE FUNGSI JADWAL (LINKED LIST) - ANGGOTA 2
 * ======================================================== */
ScheduleNode* create_schedule_node(int id, const char* activity, const char* day, int start_min, int end_min, const char* user_info);
bool add_schedule(ScheduleNode** head, ScheduleNode* new_schedule);
bool remove_schedule(ScheduleNode** head, int schedule_id);
void print_schedules(const ScheduleNode* head);
bool is_room_available(const ScheduleNode* head, const char* day, int start_min, int end_min);
void free_schedules(ScheduleNode* head);

#endif // SCHEDULE_H
