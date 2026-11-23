# PROPOSAL PROYEK STRUKTUR DATA

## ROOMFINDER
### Sistem Pencarian Ruangan Kosong Berdasarkan Jadwal di Lingkungan Kampus

**Mata Kuliah:** Struktur Data  
**Bahasa Pemrograman:** C  
**Kelompok:** [Nomor Kelompok]  
**Kelas:** [Kelas]  
**Dosen Pengampu:** [Nama Dosen]

### Anggota Kelompok

| No. | Nama | NIM | Tanggung Jawab Awal |
|---:|---|---|---|
| 1 | [Nama Anggota 1] | [NIM] | Pengelolaan data ruangan menggunakan Array |
| 2 | [Nama Anggota 2] | [NIM] | Pengelolaan jadwal menggunakan Linked List |
| 3 | [Nama Anggota 3] | [NIM] | Indeks pencarian ruangan menggunakan Binary Search Tree |
| 4 | [Nama Anggota 4] | [NIM] | Integrasi program, pengujian, dokumentasi, dan bantuan implementasi modul |

> Sesuaikan jumlah baris dengan jumlah anggota kelompok. Pembagian tugas ini bersifat awal; setiap anggota tetap perlu memahami alur program secara keseluruhan.

---

## 1. Latar Belakang

Kegiatan perkuliahan, diskusi kelompok, praktikum, dan kegiatan organisasi membutuhkan ruangan yang sesuai dengan waktu serta kapasitas peserta. Dalam kondisi tertentu, mahasiswa atau dosen dapat mengalami kesulitan mengetahui ruangan mana yang sedang tidak digunakan. Pengecekan secara manual dengan melihat jadwal satu per satu membutuhkan waktu dan berpotensi menimbulkan kesalahan, terutama ketika jumlah ruangan dan jadwal cukup banyak.

Berdasarkan permasalahan tersebut, kelompok mengusulkan **RoomFinder**, yaitu aplikasi berbasis bahasa C yang membantu pengguna mencari ruangan kosong berdasarkan hari, rentang waktu, kapasitas minimum, dan pilihan gedung. Aplikasi juga menyediakan pengelolaan data ruangan serta jadwal penggunaan agar informasi ketersediaan dapat diperbarui.

Proyek ini dirancang sebagai aplikasi konsol untuk menerapkan konsep struktur data yang dipelajari pada mata kuliah Struktur Data. Array digunakan untuk menyimpan kumpulan data ruangan, Linked List untuk mengelola jadwal pada setiap ruangan, dan Binary Search Tree (BST) untuk membantu pencarian ruangan berdasarkan kode. Dengan menggabungkan struktur data tersebut, proyek tidak hanya menghasilkan aplikasi yang dapat didemonstrasikan, tetapi juga menunjukkan alasan pemilihan struktur data sesuai kebutuhan.

## 2. Rumusan Masalah

Berdasarkan latar belakang tersebut, rumusan masalah proyek ini adalah:

1. Bagaimana menyimpan dan mengelola data ruangan kampus secara terstruktur?
2. Bagaimana mencari ruangan yang tidak memiliki jadwal penggunaan pada hari dan rentang waktu tertentu?
3. Bagaimana menerapkan Array, Linked List, dan Binary Search Tree dalam satu aplikasi bahasa C?
4. Bagaimana menguji ketepatan fungsi dan kinerja aplikasi menggunakan data uji dalam jumlah besar?

## 3. Tujuan Proyek

Proyek RoomFinder bertujuan untuk:

1. Membuat aplikasi sederhana untuk mencari ruangan kosong berdasarkan hari dan rentang waktu.
2. Menyediakan fitur pengelolaan data ruangan dan jadwal penggunaan.
3. Menerapkan sekurang-kurangnya tiga struktur data yang relevan dengan kebutuhan aplikasi.
4. Memahami dan membandingkan kompleksitas operasi pada struktur data yang digunakan.
5. Menguji ketepatan, integrasi, dan kinerja aplikasi menggunakan data uji.

## 4. Manfaat Proyek

Manfaat yang diharapkan dari proyek ini adalah:

- **Bagi mahasiswa dan dosen:** membantu menemukan pilihan ruangan berdasarkan waktu dan kapasitas yang dibutuhkan.
- **Bagi pengelola ruangan:** memudahkan pencatatan data ruangan dan jadwal penggunaannya.
- **Bagi anggota kelompok:** menjadi sarana menerapkan struktur data, pemrograman modular, pengujian, dan kerja sama tim.

## 5. Deskripsi dan Ruang Lingkup Sistem

RoomFinder merupakan aplikasi konsol yang menerima masukan dari pengguna melalui menu teks. Pengguna dapat mencari ruangan kosong dengan menentukan hari, waktu mulai, waktu selesai, serta kapasitas minimum. Sistem kemudian memeriksa jadwal setiap ruangan dan menampilkan ruangan yang memenuhi kriteria.

### 5.1 Pengguna Sistem

1. **Pengguna umum (mahasiswa atau dosen):** melihat daftar ruangan dan mencari ruangan kosong.
2. **Admin/pengelola data:** menambahkan, mengubah, atau menghapus data ruangan serta jadwal penggunaannya.

### 5.2 Fitur Utama

| No. | Fitur | Keterangan |
|---:|---|---|
| 1 | Menampilkan daftar ruangan | Menampilkan kode, nama gedung, lantai, kapasitas, dan fasilitas ruangan. |
| 2 | Mencari berdasarkan kode | Mencari detail ruangan menggunakan kode ruangan. |
| 3 | Mencari ruangan kosong | Memeriksa ketersediaan ruangan berdasarkan hari dan rentang waktu. |
| 4 | Filter hasil pencarian | Menyaring hasil berdasarkan gedung dan kapasitas minimum. |
| 5 | Mengelola data ruangan | Menambah, mengubah, dan menghapus data ruangan. |
| 6 | Mengelola jadwal | Menambah, mengubah, dan menghapus jadwal penggunaan suatu ruangan. |
| 7 | Menampilkan jadwal ruangan | Menampilkan seluruh jadwal yang tercatat pada ruangan tertentu. |

### 5.3 Batasan Proyek

Agar proyek dapat diselesaikan sesuai waktu pengerjaan, ruang lingkup dibatasi sebagai berikut:

1. Aplikasi dibuat menggunakan bahasa C dan dijalankan melalui terminal atau command prompt.
2. Data awal menggunakan data simulasi yang disusun kelompok. Data tersebut tidak diklaim sebagai jadwal resmi atau ketersediaan ruangan secara langsung.
3. Sistem menentukan ketersediaan berdasarkan jadwal yang telah dimasukkan ke aplikasi.
4. Aplikasi tidak terhubung dengan sistem akademik, sensor ruangan, atau jaringan kampus.
5. Fitur pemesanan ruangan secara resmi, autentikasi akun, dan sinkronisasi jadwal otomatis tidak termasuk dalam ruang lingkup utama.
6. Ruangan dinyatakan kosong pada rentang waktu yang diminta apabila tidak ditemukan jadwal yang bertabrakan pada rentang tersebut.

## 6. Rancangan Struktur Data

Proyek ini menggunakan tiga struktur data utama. Ketiganya diimplementasikan sendiri dalam bahasa C dan tidak digantikan dengan struktur data siap pakai dari library.

| Struktur Data | Penerapan dalam RoomFinder | Alasan Pemilihan |
|---|---|---|
| Array | Menyimpan kumpulan data utama ruangan. | Memudahkan penelusuran seluruh ruangan ketika sistem mencari ruangan yang memenuhi kriteria waktu, gedung, dan kapasitas. |
| Linked List | Menyimpan daftar jadwal penggunaan pada setiap ruangan. | Jumlah jadwal pada setiap ruangan dapat bertambah atau berkurang; Linked List memudahkan penyisipan dan penghapusan elemen secara dinamis. |
| Binary Search Tree (BST) | Menyimpan indeks kode ruangan untuk pencarian detail berdasarkan kode. | BST mengatur data berdasarkan urutan kode sehingga pencarian tidak harus memeriksa seluruh data satu per satu pada kondisi pohon yang relatif seimbang. |

### 6.1 Rancangan Data

Secara konseptual, data utama yang digunakan terdiri atas:

**Data Ruangan**

- Kode ruangan, misalnya `R201`.
- Nama atau kode gedung.
- Lantai.
- Kapasitas maksimum.
- Daftar fasilitas, misalnya proyektor atau papan tulis.
- Penunjuk ke awal Linked List jadwal ruangan.

**Data Jadwal**

- ID jadwal.
- Nama kegiatan atau mata kuliah.
- Hari.
- Waktu mulai.
- Waktu selesai.
- Informasi kelas atau pengguna.
- Penunjuk ke jadwal berikutnya.

**Node BST**

- Kode ruangan sebagai nilai kunci.
- Referensi atau indeks menuju data ruangan.
- Penunjuk anak kiri dan anak kanan.

Struktur implementasi dapat disesuaikan ketika tahap perancangan dimulai, selama fungsi dan penggunaan ketiga struktur data utama tetap terpenuhi.

### 6.2 Aturan Pemeriksaan Bentrok Jadwal

Waktu akan diolah menjadi angka menit sejak pukul 00.00 agar mudah dibandingkan. Sebagai contoh, pukul 08.00 menjadi 480 dan pukul 10.00 menjadi 600.

Dua rentang waktu dinyatakan bertabrakan apabila:

```text
waktu_mulai_diminta < waktu_selesai_jadwal
DAN
waktu_mulai_jadwal < waktu_selesai_diminta
```

Jika tidak ditemukan jadwal yang bertabrakan pada hari dan rentang waktu yang dipilih, ruangan dapat ditampilkan sebagai ruangan kosong. Batas waktu yang bersinggungan tepat, misalnya satu kegiatan berakhir pukul 10.00 dan kegiatan lain mulai pukul 10.00, tidak dianggap bertabrakan.

## 7. Alur Kerja Sistem

### 7.1 Alur Pencarian Ruangan Kosong

1. Pengguna membuka menu pencarian ruangan.
2. Pengguna memasukkan hari, waktu mulai, waktu selesai, dan kapasitas minimum.
3. Pengguna dapat memilih gedung atau fasilitas tertentu sebagai filter tambahan.
4. Sistem menelusuri data ruangan pada Array.
5. Untuk setiap ruangan, sistem memeriksa Linked List jadwal pada hari yang dipilih.
6. Sistem mengecek apakah terdapat jadwal yang bertabrakan dengan rentang waktu permintaan.
7. Sistem menampilkan ruangan yang tidak memiliki jadwal bentrok dan memenuhi seluruh filter.
8. Jika tidak ada ruangan yang cocok, sistem menampilkan informasi bahwa ruangan yang sesuai tidak ditemukan.

### 7.2 Alur Pencarian Berdasarkan Kode Ruangan

1. Pengguna memasukkan kode ruangan.
2. Sistem melakukan pencarian pada BST.
3. Jika kode ditemukan, sistem menampilkan detail ruangan dan jadwalnya.
4. Jika kode tidak ditemukan, sistem menampilkan pesan bahwa data ruangan tidak tersedia.

### 7.3 Alur Pengelolaan Jadwal

1. Admin memilih menu pengelolaan jadwal.
2. Admin memasukkan kode ruangan yang akan dikelola.
3. Sistem memeriksa keberadaan ruangan melalui BST.
4. Admin memasukkan data jadwal.
5. Sistem memeriksa validitas hari dan waktu serta kemungkinan bentrok.
6. Jika data valid dan tidak bentrok, jadwal ditambahkan ke Linked List ruangan tersebut.
7. Sistem menampilkan hasil operasi.

## 8. Rancangan Menu Aplikasi

Rancangan menu awal aplikasi adalah sebagai berikut:

```text
========================================
              ROOMFINDER
     SISTEM PENCARIAN RUANGAN KOSONG
========================================
1. Tampilkan seluruh ruangan
2. Cari ruangan berdasarkan kode
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
Pilih menu: 
```

Menu dapat disesuaikan selama fitur inti pencarian ruangan kosong dan pengelolaan jadwal tetap tersedia.

## 9. Rencana Pengujian

Pengujian dilakukan secara bertahap untuk memastikan setiap operasi berjalan dengan benar dan seluruh struktur data dapat bekerja bersama.

| Jenis Pengujian | Data Uji | Tujuan |
|---|---:|---|
| Pengujian fungsi | 3–5 data untuk setiap fungsi yang diuji | Memastikan operasi tambah, ubah, hapus, pencarian, dan pemeriksaan jadwal berjalan benar. |
| Pengujian integrasi | 20 data | Memastikan menu, Array, Linked List, dan BST dapat digunakan bersama. |
| Pengujian kinerja | Minimal 1.000 data | Mengamati waktu atau perilaku kinerja saat data bertambah. |

### 9.1 Skenario Pengujian Fungsional

| No. | Skenario | Hasil yang Diharapkan |
|---:|---|---|
| 1 | Mencari kode ruangan yang tersedia | Detail ruangan ditampilkan. |
| 2 | Mencari kode ruangan yang tidak terdaftar | Sistem menampilkan pesan data tidak ditemukan. |
| 3 | Mencari ruangan pada waktu tanpa jadwal | Ruangan yang memenuhi kriteria ditampilkan. |
| 4 | Mencari ruangan pada waktu yang memiliki jadwal bentrok | Ruangan tersebut tidak ditampilkan sebagai ruangan kosong. |
| 5 | Menambahkan jadwal yang bertabrakan | Sistem menolak jadwal atau meminta admin memperbaiki waktunya. |
| 6 | Menambahkan jadwal yang tidak bertabrakan | Jadwal berhasil disimpan. |
| 7 | Menghapus ruangan yang memiliki jadwal | Sistem menerapkan aturan penghapusan yang ditentukan dan tidak meninggalkan data jadwal tanpa induk. |

### 9.2 Pengujian Kinerja dan Memori

Pengujian kinerja dilakukan dengan menyiapkan sekurang-kurangnya 1.000 data uji yang terdiri atas data ruangan dan jadwal. Waktu operasi yang diuji dapat mencakup pencarian kode ruangan dan pencarian ketersediaan ruangan. Pengukuran waktu dapat menggunakan fungsi `clock()` dari `time.h`.

Hasil pengukuran akan dicatat setelah pengujian benar-benar dilakukan. Proposal ini tidak mencantumkan angka waktu pengujian karena hasilnya harus berasal dari eksekusi program.

Pengelolaan memori juga diperiksa. Setiap alokasi memori dinamis menggunakan `malloc()` atau fungsi alokasi lain harus ditangani dengan benar, dan memori yang tidak lagi digunakan harus dibebaskan menggunakan `free()`.

## 10. Rencana Pembagian Tugas

| Anggota | Tugas Utama | Hasil Pekerjaan |
|---|---|---|
| Anggota 1 | Implementasi Array dan operasi data ruangan | Modul data ruangan beserta pengujiannya. |
| Anggota 2 | Implementasi Linked List dan operasi jadwal | Modul jadwal beserta pemeriksaan bentrok. |
| Anggota 3 | Implementasi BST dan pencarian kode ruangan | Modul indeks dan pencarian ruangan. |
| Anggota 4 | Integrasi menu, pengujian gabungan, dokumentasi, serta membantu pengujian memori | Program terintegrasi, hasil uji, dan laporan. |

Jika kelompok terdiri dari tiga orang, tugas integrasi dan dokumentasi dibagi bersama. Setiap anggota wajib memahami struktur data dan alur program, bukan hanya bagian yang dikerjakan sendiri.

## 11. Jadwal Pengerjaan

| Tahap | Kegiatan | Target Hasil |
|---|---|---|
| Minggu 12 – Analisis kebutuhan | Menentukan masalah, ruang lingkup, fitur, struktur data, dan sumber data uji. | Proposal proyek. |
| Minggu 13 – Perancangan | Merancang ADT, diagram alur, menu, file header, file implementasi, dan kerangka program. | Dokumen rancangan dan kerangka program yang dapat dikompilasi. |
| Minggu 14 – Implementasi | Mengimplementasikan setiap struktur data dan menguji fungsi menggunakan data kecil. | Modul program yang telah diimplementasikan dan diuji. |
| Minggu 15 – Integrasi dan evaluasi | Mengintegrasikan program, melakukan pengujian integrasi dan kinerja, memeriksa memori, serta menyelesaikan laporan dan presentasi. | Program akhir, laporan, data hasil pengujian, dan slide presentasi. |
| Minggu 16 – UAS | Mendemonstrasikan dan mempertahankan hasil proyek. | Presentasi dan pertanggungjawaban proyek. |

## 12. Hasil yang Diharapkan

Hasil akhir proyek ini adalah aplikasi RoomFinder berbasis bahasa C yang dapat menyimpan data ruangan, mengelola jadwal penggunaan, mencari ruangan kosong berdasarkan hari dan waktu, serta mencari detail ruangan berdasarkan kode. Program diharapkan memiliki struktur kode modular, menerapkan sekurang-kurangnya tiga struktur data yang diimplementasikan sendiri, dan dilengkapi bukti pengujian fungsi, integrasi, kinerja, serta pengelolaan memori.

Melalui proyek ini, kelompok diharapkan dapat menunjukkan bahwa pemilihan struktur data didasarkan pada kebutuhan permasalahan. Array digunakan untuk menelusuri kumpulan ruangan, Linked List digunakan untuk mengelola jadwal yang dinamis, dan BST digunakan untuk mengindeks pencarian berdasarkan kode ruangan.

## 13. Penutup

RoomFinder diusulkan sebagai solusi sederhana untuk membantu pencarian ruangan kosong di lingkungan kampus berdasarkan jadwal penggunaan. Selain memiliki manfaat praktis sebagai simulasi sistem informasi ruangan, proyek ini menjadi sarana penerapan konsep struktur data dalam program yang terintegrasi.

Kelompok berharap proyek ini dapat dikembangkan sesuai tahapan yang telah direncanakan dan memenuhi ketentuan tugas proyek mata kuliah Struktur Data.

---

## Catatan Sebelum Proposal Dikumpulkan

- [ ] Isi nama perguruan tinggi, program studi, kelas, nomor kelompok, nama dosen, dan identitas anggota.
- [ ] Pastikan tema RoomFinder belum digunakan kelompok lain atau telah disetujui dosen.
- [ ] Sesuaikan pembagian tugas dengan jumlah anggota sebenarnya.
- [ ] Tentukan contoh gedung, kode ruangan, kapasitas, fasilitas, dan jadwal simulasi yang akan dipakai.
- [ ] Buat diagram alur untuk proses pencarian ruangan, pencarian kode, dan pengelolaan jadwal jika diminta dalam format proposal dosen.
- [ ] Periksa kembali batas halaman dan format penulisan yang ditetapkan dosen.
- [ ] Jangan mencantumkan hasil pengujian yang belum benar-benar dilakukan.

