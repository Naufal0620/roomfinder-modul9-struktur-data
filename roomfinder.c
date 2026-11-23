#include "roomfinder.h"

/* Konversi jam & menit (misal: 08:30) menjadi menit sejak 00:00 (510 menit) */
int time_to_minutes(int hour, int minute) {
    return (hour * 60) + minute;
}

/* Konversi menit ke format string HH:MM */
void minutes_to_time_str(int minutes, char* buffer) {
    int h = minutes / 60;
    int m = minutes % 60;
    sprintf(buffer, "%02d:%02d", h, m);
}

/*
 * Aturan Deteksi Bentrok:
 * Berdasarkan proposal:
 * waktu_mulai_1 < waktu_selesai_2 DAN waktu_mulai_2 < waktu_selesai_1
 * Bersinggungan tepat (misal 10:00 dan 10:00) tidak dianggap bentrok.
 */
bool is_time_overlap(int start1, int end1, int start2, int end2) {
    return (start1 < end2) && (start2 < end1);
}

/* ========================================================
 * 1. MODUL JADWAL (LINKED LIST) - ANGGOTA 2
 * ======================================================== */

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

bool add_schedule(ScheduleNode** head, ScheduleNode* new_schedule) {
    if (!new_schedule) return false;

    // Periksa apakah bentrok dengan jadwal yang sudah ada pada hari yang sama
    ScheduleNode* curr = *head;
    while (curr != NULL) {
        if (strcasecmp(curr->day, new_schedule->day) == 0) {
            if (is_time_overlap(new_schedule->start_min, new_schedule->end_min, curr->start_min, curr->end_min)) {
                printf("[Peringatan] Jadwal bentrok dengan kegiatan: %s (%s)!\n", curr->activity, curr->user_info);
                free(new_schedule);
                return false;
            }
        }
        curr = curr->next;
    }

    // Sisipkan di awal linked list (atau urut waktu jika diperlukan)
    new_schedule->next = *head;
    *head = new_schedule;
    return true;
}

bool remove_schedule(ScheduleNode** head, int schedule_id) {
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

/* ========================================================
 * 2. MODUL RUANGAN (ARRAY) - ANGGOTA 1
 * ======================================================== */

void init_room_array(RoomArray* ra) {
    ra->count = 0;
}

bool add_room(RoomArray* ra, const char* code, const char* building, int floor, int capacity, const char* facilities) {
    if (ra->count >= MAX_ROOMS) {
        printf("[Error] Kapasitas penyimpanan ruangan penuh!\n");
        return false;
    }

    // Cek duplikasi kode
    for (int i = 0; i < ra->count; i++) {
        if (strcasecmp(ra->rooms[i].code, code) == 0) {
            printf("[Error] Kode ruangan '%s' sudah terdaftar!\n", code);
            return false;
        }
    }

    Room* r = &ra->rooms[ra->count];
    strncpy(r->code, code, STR_LEN_SHORT - 1);
    r->code[STR_LEN_SHORT - 1] = '\0';
    strncpy(r->building, building, STR_LEN_MID - 1);
    r->building[STR_LEN_MID - 1] = '\0';
    r->floor = floor;
    r->capacity = capacity;
    strncpy(r->facilities, facilities, STR_LEN_LONG - 1);
    r->facilities[STR_LEN_LONG - 1] = '\0';
    r->schedule_head = NULL;

    ra->count++;
    return true;
}

bool update_room(RoomArray* ra, const char* code, const char* building, int floor, int capacity, const char* facilities) {
    for (int i = 0; i < ra->count; i++) {
        if (strcasecmp(ra->rooms[i].code, code) == 0) {
            strncpy(ra->rooms[i].building, building, STR_LEN_MID - 1);
            ra->rooms[i].floor = floor;
            ra->rooms[i].capacity = capacity;
            strncpy(ra->rooms[i].facilities, facilities, STR_LEN_LONG - 1);
            return true;
        }
    }
    return false;
}

bool delete_room(RoomArray* ra, const char* code) {
    int target_idx = -1;
    for (int i = 0; i < ra->count; i++) {
        if (strcasecmp(ra->rooms[i].code, code) == 0) {
            target_idx = i;
            break;
        }
    }

    if (target_idx == -1) return false;

    // Bersihkan linked list jadwal ruangan sebelum dihapus
    free_schedules(ra->rooms[target_idx].schedule_head);

    // Geser elemen array
    for (int i = target_idx; i < ra->count - 1; i++) {
        ra->rooms[i] = ra->rooms[i + 1];
    }
    ra->count--;
    return true;
}

void display_all_rooms(const RoomArray* ra) {
    if (ra->count == 0) {
        printf("Belum ada data ruangan.\n");
        return;
    }
    printf("========================================================================================\n");
    printf("%-8s | %-15s | %-7s | %-10s | %-30s\n", "Kode", "Gedung", "Lantai", "Kapasitas", "Fasilitas");
    printf("========================================================================================\n");
    for (int i = 0; i < ra->count; i++) {
        printf("%-8s | %-15s | Lt. %-3d | %-4d kursi | %-30s\n",
               ra->rooms[i].code, ra->rooms[i].building, ra->rooms[i].floor,
               ra->rooms[i].capacity, ra->rooms[i].facilities);
    }
    printf("========================================================================================\n");
    printf("Total: %d ruangan terdaftar.\n", ra->count);
}

void display_room_detail(const Room* room) {
    if (!room) return;
    printf("\n=== DETAIL RUANGAN: %s ===\n", room->code);
    printf("Gedung    : %s (Lantai %d)\n", room->building, room->floor);
    printf("Kapasitas : %d orang\n", room->capacity);
    printf("Fasilitas : %s\n", room->facilities);
    printf("Jadwal Penggunaan:\n");
    print_schedules(room->schedule_head);
    printf("===============================\n");
}

/* ========================================================
 * 3. MODUL INDEKS PENCARIAN (BST) - ANGGOTA 3
 * ======================================================== */

BSTNode* create_bst_node(const char* code, Room* room_ptr) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    strncpy(node->code, code, STR_LEN_SHORT - 1);
    node->code[STR_LEN_SHORT - 1] = '\0';
    node->room_ptr = room_ptr;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* bst_insert(BSTNode* root, const char* code, Room* room_ptr) {
    if (root == NULL) {
        return create_bst_node(code, room_ptr);
    }
    int cmp = strcasecmp(code, root->code);
    if (cmp < 0) {
        root->left = bst_insert(root->left, code, room_ptr);
    } else if (cmp > 0) {
        root->right = bst_insert(root->right, code, room_ptr);
    } else {
        // Jika kunci sama, update pointer ruangan
        root->room_ptr = room_ptr;
    }
    return root;
}

Room* bst_search(BSTNode* root, const char* code) {
    if (root == NULL) return NULL;
    int cmp = strcasecmp(code, root->code);
    if (cmp == 0) {
        return root->room_ptr;
    } else if (cmp < 0) {
        return bst_search(root->left, code);
    } else {
        return bst_search(root->right, code);
    }
}

void bst_free(BSTNode* root) {
    if (root == NULL) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

BSTNode* rebuild_bst_index(const RoomArray* ra) {
    BSTNode* root = NULL;
    for (int i = 0; i < ra->count; i++) {
        root = bst_insert(root, ra->rooms[i].code, (Room*)&ra->rooms[i]);
    }
    return root;
}

/* ========================================================
 * 4. INTEGRASI & PENCARIAN RUANGAN KOSONG - ANGGOTA 4
 * ======================================================== */

void search_available_rooms(const RoomArray* ra, const char* day, int start_min, int end_min, int min_capacity, const char* building_filter) {
    char start_str[10], end_str[10];
    minutes_to_time_str(start_min, start_str);
    minutes_to_time_str(end_min, end_str);

    printf("\n>>> Hasil Pencarian Ruangan Kosong <<<\n");
    printf("Kriteria: Hari %s, Pukul %s - %s, Min. Kapasitas: %d\n", day, start_str, end_str, min_capacity);
    if (strlen(building_filter) > 0 && strcmp(building_filter, "-") != 0) {
        printf("Filter Gedung: %s\n", building_filter);
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-8s | %-15s | %-7s | %-10s | %-30s\n", "Kode", "Gedung", "Lantai", "Kapasitas", "Fasilitas");
    printf("----------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < ra->count; i++) {
        const Room* r = &ra->rooms[i];

        // 1. Filter Kapasitas
        if (r->capacity < min_capacity) continue;

        // 2. Filter Gedung (jika dispesifikasikan)
        if (strlen(building_filter) > 0 && strcmp(building_filter, "-") != 0) {
            if (strcasecmp(r->building, building_filter) != 0) continue;
        }

        // 3. Filter Ketersediaan Jadwal (Linked List conflict check)
        if (is_room_available(r->schedule_head, day, start_min, end_min)) {
            printf("%-8s | %-15s | Lt. %-3d | %-4d kursi | %-30s\n",
                   r->code, r->building, r->floor, r->capacity, r->facilities);
            found++;
        }
    }
    printf("----------------------------------------------------------------------------------------\n");
    if (found == 0) {
        printf("Tidak ada ruangan kosong yang memenuhi kriteria pencarian.\n");
    } else {
        printf("Ditemukan %d ruangan yang tersedia dan siap digunakan.\n", found);
    }
}

void load_sample_data(RoomArray* ra, BSTNode** bst_root) {
    init_room_array(ra);

    // Tambah ruangan sampel
    add_room(ra, "R101", "Gedung Kuliah A", 1, 40, "Proyektor, AC, Whiteboard");
    add_room(ra, "R102", "Gedung Kuliah A", 1, 45, "Proyektor, AC, Whiteboard");
    add_room(ra, "R201", "Gedung Kuliah B", 2, 60, "Proyektor, AC, Sound System");
    add_room(ra, "LAB-01", "Gedung Lab Terpadu", 3, 35, "35 PC, AC, Proyektor");
    add_room(ra, "AUD-01", "Auditorium Pusat", 1, 200, "Stage, Sound System, Proyektor Ganda");

    // Rebuild indeks BST
    *bst_root = rebuild_bst_index(ra);

    // Tambah beberapa sampel jadwal
    // R101 jadwal: Senin 08:00 - 10:00 (Struktur Data)
    Room* r101 = bst_search(*bst_root, "R101");
    if (r101) {
        add_schedule(&r101->schedule_head, create_schedule_node(1, "Struktur Data", "Senin", 480, 600, "Kelas IK-2B"));
        add_schedule(&r101->schedule_head, create_schedule_node(2, "Matematika Diskrit", "Senin", 660, 780, "Kelas IK-2A"));
    }

    // R201 jadwal: Senin 09:00 - 11:30 (Basis Data)
    Room* r201 = bst_search(*bst_root, "R201");
    if (r201) {
        add_schedule(&r201->schedule_head, create_schedule_node(3, "Basis Data", "Senin", 540, 690, "Kelas SI-2A"));
    }
}

void cleanup_system(RoomArray* ra, BSTNode** bst_root) {
    // 1. Bebaskan memori linked list jadwal di tiap ruangan
    for (int i = 0; i < ra->count; i++) {
        free_schedules(ra->rooms[i].schedule_head);
        ra->rooms[i].schedule_head = NULL;
    }
    ra->count = 0;

    // 2. Bebaskan memori BST
    if (*bst_root) {
        bst_free(*bst_root);
        *bst_root = NULL;
    }
}
