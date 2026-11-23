#include "roomfinder.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_banner() {
    printf("\n========================================\n");
    printf("              ROOMFINDER\n");
    printf("     SISTEM PENCARIAN RUANGAN KOSONG\n");
    printf("========================================\n");
    printf("1. Tampilkan seluruh ruangan\n");
    printf("2. Cari ruangan berdasarkan kode (BST)\n");
    printf("3. Cari ruangan kosong berdasarkan jadwal\n");
    printf("4. Tambah data ruangan\n");
    printf("5. Ubah data ruangan\n");
    printf("6. Hapus data ruangan\n");
    printf("7. Tambah jadwal penggunaan\n");
    printf("8. Ubah jadwal penggunaan\n");
    printf("9. Hapus jadwal penggunaan\n");
    printf("10. Tampilkan jadwal suatu ruangan\n");
    printf("0. Simpan data dan keluar\n");
    printf("========================================\n");
    printf("Pilih menu: ");
}

int main() {
    RoomArray room_array;
    BSTNode* bst_root = NULL;

    // Inisialisasi dan load data sampel awal
    load_sample_data(&room_array, &bst_root);

    int choice;
    char buffer[STR_LEN_LONG];
    char code[STR_LEN_SHORT], building[STR_LEN_MID], facilities[STR_LEN_LONG], day[STR_LEN_SHORT], activity[STR_LEN_MID], pic[STR_LEN_MID];
    int floor, capacity, start_h, start_m, end_h, end_m, id;

    printf("Inisialisasi sistem RoomFinder selesai.\n");
    printf("Memuat 5 data ruangan sampel...\n");

    while (1) {
        print_banner();
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Input tidak valid! Masukkan angka menu.\n");
            continue;
        }
        clear_input_buffer();

        if (choice == 0) {
            printf("\nMenyimpan data dan membersihkan alokasi memori...\n");
            cleanup_system(&room_array, &bst_root);
            printf("Terima kasih telah menggunakan RoomFinder!\n");
            break;
        }

        switch (choice) {
            case 1: {
                printf("\n--- DAFTAR SELURUH RUANGAN (ARRAY) ---\n");
                display_all_rooms(&room_array);
                break;
            }
            case 2: {
                printf("\n--- CARI RUANGAN BERDASARKAN KODE (BST) ---\n");
                printf("Masukkan Kode Ruangan: ");
                if (fgets(code, sizeof(code), stdin)) {
                    code[strcspn(code, "\r\n")] = '\0';
                }
                Room* found = bst_search(bst_root, code);
                if (found) {
                    display_room_detail(found);
                } else {
                    printf("[Pemberitahuan] Ruangan dengan kode '%s' tidak ditemukan dalam sistem!\n", code);
                }
                break;
            }
            case 3: {
                printf("\n--- CARI RUANGAN KOSONG BERDASARKAN WAKTU ---\n");
                printf("Hari (misal: Senin): ");
                scanf("%31s", day);
                printf("Jam Mulai (HH MM, contoh 08 00): ");
                scanf("%d %d", &start_h, &start_m);
                printf("Jam Selesai (HH MM, contoh 10 00): ");
                scanf("%d %d", &end_h, &end_m);
                printf("Kapasitas Minimum (orang): ");
                scanf("%d", &capacity);
                clear_input_buffer();

                printf("Filter Gedung (- jika ingin semua gedung): ");
                if (fgets(building, sizeof(building), stdin)) {
                    building[strcspn(building, "\r\n")] = '\0';
                }

                int start_min = time_to_minutes(start_h, start_m);
                int end_min = time_to_minutes(end_h, end_m);

                if (start_min >= end_min) {
                    printf("[Error] Jam mulai harus lebih awal dari jam selesai!\n");
                } else {
                    search_available_rooms(&room_array, day, start_min, end_min, capacity, building);
                }
                break;
            }
            case 4: {
                printf("\n--- TAMBAH DATA RUANGAN BARU ---\n");
                printf("Kode Ruangan (misal: R301): ");
                scanf("%31s", code);
                clear_input_buffer();

                printf("Nama Gedung: ");
                if (fgets(building, sizeof(building), stdin)) {
                    building[strcspn(building, "\r\n")] = '\0';
                }

                printf("Lantai: ");
                scanf("%d", &floor);
                printf("Kapasitas (kursi): ");
                scanf("%d", &capacity);
                clear_input_buffer();

                printf("Fasilitas: ");
                if (fgets(facilities, sizeof(facilities), stdin)) {
                    facilities[strcspn(facilities, "\r\n")] = '\0';
                }

                if (add_room(&room_array, code, building, floor, capacity, facilities)) {
                    // Rebuild BST index setelah penambahan
                    bst_free(bst_root);
                    bst_root = rebuild_bst_index(&room_array);
                    printf("[Sukses] Ruangan %s berhasil ditambahkan dan diindeks ke BST!\n", code);
                }
                break;
            }
            case 5: {
                printf("\n--- UBAH DATA RUANGAN ---\n");
                printf("Masukkan Kode Ruangan yang akan diubah: ");
                scanf("%31s", code);
                clear_input_buffer();

                Room* r = bst_search(bst_root, code);
                if (!r) {
                    printf("[Error] Ruangan dengan kode '%s' tidak ditemukan!\n", code);
                    break;
                }

                printf("Nama Gedung Baru: ");
                if (fgets(building, sizeof(building), stdin)) {
                    building[strcspn(building, "\r\n")] = '\0';
                }
                printf("Lantai Baru: ");
                scanf("%d", &floor);
                printf("Kapasitas Baru: ");
                scanf("%d", &capacity);
                clear_input_buffer();

                printf("Fasilitas Baru: ");
                if (fgets(facilities, sizeof(facilities), stdin)) {
                    facilities[strcspn(facilities, "\r\n")] = '\0';
                }

                if (update_room(&room_array, code, building, floor, capacity, facilities)) {
                    printf("[Sukses] Data ruangan %s berhasil diperbarui!\n", code);
                }
                break;
            }
            case 6: {
                printf("\n--- HAPUS DATA RUANGAN ---\n");
                printf("Masukkan Kode Ruangan yang akan dihapus: ");
                scanf("%31s", code);
                clear_input_buffer();

                if (delete_room(&room_array, code)) {
                    // Rebuild BST index
                    bst_free(bst_root);
                    bst_root = rebuild_bst_index(&room_array);
                    printf("[Sukses] Ruangan %s berhasil dihapus dari sistem!\n", code);
                } else {
                    printf("[Error] Ruangan %s tidak ditemukan!\n", code);
                }
                break;
            }
            case 7: {
                printf("\n--- TAMBAH JADWAL PENGGUNAAN RUANGAN ---\n");
                printf("Masukkan Kode Ruangan: ");
                scanf("%31s", code);
                clear_input_buffer();

                Room* r = bst_search(bst_root, code);
                if (!r) {
                    printf("[Error] Ruangan '%s' tidak terdaftar!\n", code);
                    break;
                }

                printf("ID Jadwal (angka unik): ");
                scanf("%d", &id);
                clear_input_buffer();

                printf("Nama Kegiatan / Mata Kuliah: ");
                if (fgets(activity, sizeof(activity), stdin)) {
                    activity[strcspn(activity, "\r\n")] = '\0';
                }

                printf("Hari (misal: Senin): ");
                scanf("%31s", day);
                printf("Jam Mulai (HH MM): ");
                scanf("%d %d", &start_h, &start_m);
                printf("Jam Selesai (HH MM): ");
                scanf("%d %d", &end_h, &end_m);
                clear_input_buffer();

                printf("PIC / Dosen / Kelas: ");
                if (fgets(pic, sizeof(pic), stdin)) {
                    pic[strcspn(pic, "\r\n")] = '\0';
                }

                int s_min = time_to_minutes(start_h, start_m);
                int e_min = time_to_minutes(end_h, end_m);

                if (s_min >= e_min) {
                    printf("[Error] Jam mulai harus lebih awal dari jam selesai!\n");
                    break;
                }

                ScheduleNode* new_s = create_schedule_node(id, activity, day, s_min, e_min, pic);
                if (add_schedule(&r->schedule_head, new_s)) {
                    printf("[Sukses] Jadwal berhasil ditambahkan ke ruangan %s!\n", code);
                }
                break;
            }
            case 8: {
                printf("\n--- UBAH JADWAL PENGGUNAAN ---\n");
                printf("Masukkan Kode Ruangan: ");
                scanf("%31s", code);
                clear_input_buffer();

                Room* r = bst_search(bst_root, code);
                if (!r) {
                    printf("[Error] Ruangan '%s' tidak terdaftar!\n", code);
                    break;
                }

                printf("Jadwal saat ini untuk ruangan %s:\n", code);
                print_schedules(r->schedule_head);

                printf("Masukkan ID Jadwal yang ingin diubah: ");
                scanf("%d", &id);
                clear_input_buffer();

                // Hapus jadwal lama lalu masukkan jadwal baru
                if (!remove_schedule(&r->schedule_head, id)) {
                    printf("[Error] Jadwal dengan ID %d tidak ditemukan!\n", id);
                    break;
                }

                printf("Masukkan Data Baru:\n");
                printf("Nama Kegiatan Baru: ");
                if (fgets(activity, sizeof(activity), stdin)) {
                    activity[strcspn(activity, "\r\n")] = '\0';
                }
                printf("Hari Baru: ");
                scanf("%31s", day);
                printf("Jam Mulai Baru (HH MM): ");
                scanf("%d %d", &start_h, &start_m);
                printf("Jam Selesai Baru (HH MM): ");
                scanf("%d %d", &end_h, &end_m);
                clear_input_buffer();
                printf("PIC Baru: ");
                if (fgets(pic, sizeof(pic), stdin)) {
                    pic[strcspn(pic, "\r\n")] = '\0';
                }

                int s_min = time_to_minutes(start_h, start_m);
                int e_min = time_to_minutes(end_h, end_m);
                ScheduleNode* updated_node = create_schedule_node(id, activity, day, s_min, e_min, pic);

                if (add_schedule(&r->schedule_head, updated_node)) {
                    printf("[Sukses] Jadwal ID %d berhasil diperbarui!\n", id);
                } else {
                    printf("[Peringatan] Perubahan gagal diterapkan karena bentrok jadwal!\n");
                }
                break;
            }
            case 9: {
                printf("\n--- HAPUS JADWAL PENGGUNAAN ---\n");
                printf("Masukkan Kode Ruangan: ");
                scanf("%31s", code);
                clear_input_buffer();

                Room* r = bst_search(bst_root, code);
                if (!r) {
                    printf("[Error] Ruangan '%s' tidak terdaftar!\n", code);
                    break;
                }

                printf("Jadwal ruangan %s:\n", code);
                print_schedules(r->schedule_head);

                printf("Masukkan ID Jadwal yang akan dihapus: ");
                scanf("%d", &id);
                clear_input_buffer();

                if (remove_schedule(&r->schedule_head, id)) {
                    printf("[Sukses] Jadwal ID %d berhasil dihapus dari ruangan %s!\n", id, code);
                } else {
                    printf("[Error] Jadwal dengan ID %d tidak ditemukan!\n", id);
                }
                break;
            }
            case 10: {
                printf("\n--- TAMPILKAN JADWAL RUANGAN ---\n");
                printf("Masukkan Kode Ruangan: ");
                scanf("%31s", code);
                clear_input_buffer();

                Room* r = bst_search(bst_root, code);
                if (r) {
                    printf("\nJadwal Terdaftar untuk Ruangan %s (%s, Lantai %d):\n", r->code, r->building, r->floor);
                    print_schedules(r->schedule_head);
                } else {
                    printf("[Error] Ruangan '%s' tidak ditemukan!\n", code);
                }
                break;
            }
            default:
                printf("[Error] Menu %d tidak tersedia. Silakan pilih 0-10.\n", choice);
                break;
        }

        printf("\nTekan Enter untuk kembali ke menu utama...");
        fgets(buffer, sizeof(buffer), stdin);
    }

    return 0;
}
