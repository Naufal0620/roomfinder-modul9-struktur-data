# RoomFinder

**Sistem Pencarian Ruangan Kosong Berdasarkan Jadwal di Lingkungan Kampus**  
Aplikasi konsol berbasis bahasa C untuk membantu mahasiswa, dosen, dan pengelola ruangan dalam mencari ruangan yang tersedia tanpa bentrok jadwal, sekaligus mengelola data ruangan dan jadwal kegiatan.

Proyek ini dikembangkan sebagai tugas besar mata kuliah **Struktur Data**.

---

## 📌 Fitur Utama

1. **Pencarian Ruangan Kosong:** Menyaring ruangan yang tidak memiliki jadwal bentrok berdasarkan hari, rentang jam (waktu mulai & selesai), kapasitas minimum, serta gedung.
2. **Pencarian Detail via Kode Ruangan:** Menemukan informasi detail ruangan dan jadwalnya secara cepat menggunakan indeks pohon biner.
3. **Pengelolaan Data Ruangan (CRUD):** Menambah, melihat daftar, mengubah, dan menghapus master data ruangan kampus.
4. **Pengelolaan Jadwal Ruangan (CRUD):** Menambah, mengubah, menghapus, serta melihat jadwal penggunaan pada masing-masing ruangan.
5. **Algoritma Deteksi Bentrok Waktu:** Mencegah terjadinya pemesanan atau jadwal ganda pada ruangan dan waktu yang sama.

---

## 🧱 Struktur Data yang Diterapkan

Sesuai ketentuan akademis, seluruh struktur data diimplementasikan secara mandiri tanpa menggunakan pustaka siap pakai:

| Struktur Data | Implementasi di RoomFinder | Alasan Penggunaan |
| :--- | :--- | :--- |
| **Array** | Penyimpanan master data ruangan (`RoomArray`) | Memudahkan penelusuran (*traversal*) seluruh koleksi ruangan saat pencarian filter waktu & kapasitas. |
| **Linked List** | Daftar jadwal kegiatan per ruangan (`ScheduleNode`) | Alokasi memori dinamis yang efisien untuk penambahan atau penghapusan jadwal pada setiap ruangan. |
| **Binary Search Tree (BST)** | Indeks pencarian kode ruangan (`BSTNode`) | Mengoptimalkan pencarian ruangan berdasarkan kode menjadi $\mathcal{O}(\log n)$ pada kondisi pohon seimbang. |

---

## 👥 Tim Pengembang

| No. | Peran / Anggota | Tanggung Jawab Utama |
| :---: | :--- | :--- |
| 1 | **Anggota 1** | Pengelolaan master data ruangan menggunakan Array & penyaringan data. |
| 2 | **Anggota 2** | Pengelolaan jadwal penggunaan menggunakan Linked List & algoritma anti-bentrok. |
| 3 | **Anggota 3** | Indeks pencarian kode ruangan menggunakan Binary Search Tree (BST). |
| 4 | **Anggota 4** | Integrasi sistem, antarmuka menu CLI, generator data uji, dan pengujian kinerja. |

> *Detail panduan teknis implementasi masing-masing anggota dapat dilihat pada [PANDUAN_TUGAS_ANGGOTA.md](PANDUAN_TUGAS_ANGGOTA.md).*

---

## 🚀 Panduan Menjalankan Program

### Prasyarat
* Kompiler C (GCC / MinGW / Clang).
* Terminal / Command Prompt / PowerShell.

### Kompilasi
Buka terminal pada direktori proyek, lalu jalankan:

```powershell
gcc -Wall -Wextra main.c roomfinder.c -o roomfinder.exe
```

### Menjalankan Aplikasi
Setelah proses kompilasi selesai, jalankan file biner:

```powershell
.\roomfinder.exe
```

---

## 📖 Panduan Penggunaan Menu

Saat aplikasi dijalankan, menu interaktif berikut akan ditampilkan di konsol:

```text
========================================
              ROOMFINDER
     SISTEM PENCARIAN RUANGAN KOSONG
========================================
1. Tampilkan seluruh ruangan
2. Cari ruangan berdasarkan kode (BST)
3. Cari ruangan kosong berdasarkan jadwal
4. Tambah data ruangan
5. Ubah data ruangan
6. Hapus data ruangan
7. Tambah jadwal penggunaan
8. Ubah jadwal penggunaan
9. Hapus jadwal penggunaan
10. Tampilkan jadwal suatu ruangan
0. Simpan data dan keluar
========================================
```

### Contoh Alur Pencarian Ruangan Kosong (Menu 3)
1. Pilih menu `3`.
2. Masukkan hari (contoh: `Senin`).
3. Masukkan jam mulai dalam format jam dan menit (contoh: `08 30`).
4. Masukkan jam selesai dalam format jam dan menit (contoh: `10 00`).
5. Masukkan kapasitas minimum (contoh: `30`).
6. Masukkan nama gedung atau ketik `-` jika ingin mencari di semua gedung.
7. Sistem akan menampilkan daftar ruangan yang tersedia tanpa jadwal bentrok.
