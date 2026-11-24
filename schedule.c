#include "schedule.h"

/* Helper internal untuk mengurutkan hari Senin - Minggu */
static int get_day_order(const char* day) {
    if (strcasecmp(day, "Senin") == 0) return 1;
    if (strcasecmp(day, "Selasa") == 0) return 2;
    if (strcasecmp(day, "Rabu") == 0) return 3;
    if (strcasecmp(day, "Kamis") == 0) return 4;
    if (strcasecmp(day, "Jumat") == 0) return 5;
    if (strcasecmp(day, "Sabtu") == 0) return 6;
    if (strcasecmp(day, "Minggu") == 0) return 7;
    return 8;
}

/* Konversi jam & menit (misal: 08:30) menjadi menit sejak 00:00 (510 menit) */
int time_to_minutes(int hour, int minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return -1;
    }
    return (hour * 60) + minute;
}

/* Konversi menit ke format string HH:MM */
void minutes_to_time_str(int minutes, char* buffer) {
    if (buffer == NULL) return;
    if (minutes < 0 || minutes > 1440) {
        sprintf(buffer, "--:--");
        return;
    }
    int h = minutes / 60;
    int m = minutes % 60;
    sprintf(buffer, "%02d:%02d", h, m);
}

/*
 * Aturan Deteksi Bentrok:
 * (start1 < end2) && (start2 < end1)
 * Bersinggungan tepat (misal 10:00 dan 10:00) menghasilkan FALSE (tidak bentrok).
 */
bool is_time_overlap(int start1, int end1, int start2, int end2) {
    return (start1 < end2) && (start2 < end1);
}

ScheduleNode* create_schedule_node(int id, const char* activity, const char* day, int start_min, int end_min, const char* user_info) {
    ScheduleNode* node = (ScheduleNode*)malloc(sizeof(ScheduleNode));
    if (!node) {
        printf("[Error] Gagal mengalokasikan memori untuk jadwal!\n");
        return NULL;
    }
    node->id = id;
    strncpy(node->activity, activity, STR_LEN_MID - 1);
    node->activity[STR_LEN_MID - 1] = '\0';
    strncpy(node->day, day, STR_LEN_SHORT - 1);
    node->day[STR_LEN_SHORT - 1] = '\0';
    node->start_min = start_min;
    node->end_min = end_min;
    strncpy(node->user_info, user_info, STR_LEN_MID - 1);
    node->user_info[STR_LEN_MID - 1] = '\0';
    node->next = NULL;
    return node;
}

/*
 * Tambah jadwal dengan Validasi Bentrok + Sorted Insert (urut hari & jam mulai)
 */
bool add_schedule(ScheduleNode** head, ScheduleNode* new_schedule) {
    if (!head || !new_schedule) return false;

    // 1. Validasi rentang waktu
    if (new_schedule->start_min < 0 || new_schedule->end_min > 1440 ||
        new_schedule->start_min >= new_schedule->end_min) {
        printf("[Error] Rentang waktu jadwal tidak valid!\n");
        free(new_schedule);
        return false;
    }

    // 2. Periksa duplikasi ID dan bentrok jadwal pada hari yang sama
    ScheduleNode* curr = *head;
    while (curr != NULL) {
        if (curr->id == new_schedule->id) {
            printf("[Peringatan] ID jadwal %d sudah terdaftar pada ruangan ini!\n", new_schedule->id);
            free(new_schedule);
            return false;
        }
        if (strcasecmp(curr->day, new_schedule->day) == 0) {
            if (is_time_overlap(new_schedule->start_min, new_schedule->end_min, curr->start_min, curr->end_min)) {
                char s_str[10], e_str[10];
                minutes_to_time_str(curr->start_min, s_str);
                minutes_to_time_str(curr->end_min, e_str);
                printf("[Peringatan] Jadwal bentrok dengan kegiatan: %s (%s %s-%s, PIC: %s)!\n",
                       curr->activity, curr->day, s_str, e_str, curr->user_info);
                free(new_schedule);
                return false;
            }
        }
        curr = curr->next;
    }

    // 3. Sorted Insert: urutkan berdasarkan hari, lalu jam mulai (start_min)
    int new_day_order = get_day_order(new_schedule->day);
    int head_day_order = (*head != NULL) ? get_day_order((*head)->day) : 99;

    if (*head == NULL || new_day_order < head_day_order ||
        (new_day_order == head_day_order && new_schedule->start_min < (*head)->start_min)) {
        new_schedule->next = *head;
        *head = new_schedule;
        return true;
    }

    curr = *head;
    while (curr->next != NULL) {
        int next_day_order = get_day_order(curr->next->day);
        if (next_day_order < new_day_order) {
            curr = curr->next;
        } else if (next_day_order == new_day_order && curr->next->start_min < new_schedule->start_min) {
            curr = curr->next;
        } else {
            break;
        }
    }

    new_schedule->next = curr->next;
    curr->next = new_schedule;
    return true;
}

bool remove_schedule(ScheduleNode** head, int schedule_id) {
    if (!head || !*head) return false;

    ScheduleNode* curr = *head;
    ScheduleNode* prev = NULL;

    while (curr != NULL) {
        if (curr->id == schedule_id) {
            if (prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void print_schedules(const ScheduleNode* head) {
    if (!head) {
        printf("    (Tidak ada jadwal tercatat / Ruangan kosong penuh)\n");
        return;
    }
    const ScheduleNode* curr = head;
    char start_str[10], end_str[10];
    while (curr != NULL) {
        minutes_to_time_str(curr->start_min, start_str);
        minutes_to_time_str(curr->end_min, end_str);
        printf("    - [ID:%d] %-8s | %s - %s | %-20s | PIC: %s\n",
               curr->id, curr->day, start_str, end_str, curr->activity, curr->user_info);
        curr = curr->next;
    }
}

bool is_room_available(const ScheduleNode* head, const char* day, int start_min, int end_min) {
    const ScheduleNode* curr = head;
    while (curr != NULL) {
        if (strcasecmp(curr->day, day) == 0) {
            if (is_time_overlap(start_min, end_min, curr->start_min, curr->end_min)) {
                return false; // Ditemukan jadwal yang bentrok
            }
        }
        curr = curr->next;
    }
    return true; // Ruangan kosong
}

void free_schedules(ScheduleNode* head) {
    ScheduleNode* curr = head;
    while (curr != NULL) {
        ScheduleNode* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}
