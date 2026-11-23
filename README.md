# PANDUAN PENGEMBANGAN & PEMBAGIAN TUGAS PROYEK ROOMFINDER

Proyek ini telah dibuatkan kerangka dasar (*skeleton code*) modular dalam bahasa C yang siap dikembangkan bersama oleh 4 anggota kelompok sesuai dengan proposal Struktur Data.

---

## 📁 Struktur Berkas

- [roomfinder.h]: Deklarasi struct data (`Room`, `ScheduleNode`, `BSTNode`) dan prototipe fungsi.
- [roomfinder.c]: Implementasi fungsi-fungsi Array, Linked List, BST, dan deteksi bentrok jadwal.
- [main.c]: Antarmuka menu interaktif CLI (Menu 0-10) serta penanganan input pengguna.

---

## 👥 Rincian Tugas untuk 4 Anggota Kelompok

### 1. Anggota 1: Master Data Ruangan (Array)
- **Fokus File:** `roomfinder.c` (bagian `MODUL RUANGAN (ARRAY)`).
- **Tugas:**
  1. Optimasi fungsi CRUD ruangan (`add_room`, `update_room`, `delete_room`).
  2. Menambahkan fitur filter atau sorting data ruangan jika diperlukan (misal urut kapasitas atau lantai).
  3. Memastikan batasan array (`MAX_ROOMS`) aman dari overflow.

### 2. Anggota 2: Pengelolaan Jadwal & Algoritma Anti-Bentrok (Linked List)
- **Fokus File:** `roomfinder.c` (bagian `MODUL JADWAL (LINKED LIST)`).
- **Tugas:**
  1. Menyempurnakan validasi bentrok waktu:
     `is_time_overlap(s1, e1, s2, e2) -> (start1 < end2) && (start2 < end1)`.
  2. Implementasi pengurutan jadwal otomatis (misal jadwal di-insert terurut berdasarkan jam mulai).
  3. Validasi batasan jam operasional kampus (misal 07:00 - 21:00).

### 3. Anggota 3: Indeks & Pencarian Cepat Kode Ruangan (BST)
- **Fokus File:** `roomfinder.c` (bagian `MODUL INDEKS PENCARIAN (BST)`).
- **Tugas:**
  1. Mengembangkan fungsi traversal pohon (In-order, Pre-order, Post-order) untuk demonstrasi pemahaman BST saat ujian/presentasi.
  2. Implementasi penghapusan node BST langsung (`bst_delete` dengan penanganan 0, 1, atau 2 child).
  3. Menghitung kedalaman/tinggi pohon (*height of tree*) untuk analisis kompleksitas $O(\log n)$.

### 4. Anggota 4: Integrasi Sistem, Pengujian Kinerja & Memori (Anda)
- **Fokus File:** `main.c`, file uji, dan dokumentasi laporan.
- **Tugas:**
  1. Menghubungkan semua fungsi anggota ke Menu CLI dan menangani validasi input teks/angka.
  2. Membuat script generator data uji minimal **1.000 data** (sesuai Bab 9.2 Proposal).
  3. Melakukan benchmark waktu eksekusi menggunakan `clock()` dari `<time.h>` untuk membandingkan kecepatan pencarian BST vs Linear Search Array.
  4. Memastikan pembersihan memori (`free()`) agar tidak terjadi kebocoran memori (*memory leak*).

---

## 🛠️ Cara Kompilasi dan Menjalankan Program

Gunakan compiler GCC di PowerShell:

```powershell
gcc -Wall -Wextra main.c roomfinder.c -o roomfinder.exe
.\roomfinder.exe
```
