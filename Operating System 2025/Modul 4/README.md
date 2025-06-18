[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/V7fOtAk7)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221000 | Student 1 Name |
| 5025221000 | Student 2 Name |
| 5025221000 | Student 3 Name |

# Praktikum Modul 4 (Module 4 Lab Work)

</div>

## Daftar Soal (Task List)

- [Task 1 - FUSecure](/task-1/)

- [Task 2 - LawakFS++](/task-2/)

- [Task 3 - Drama Troll](/task-3/)

- [Task 4 - LilHabOS](/task-4/)

## Laporan Resmi Praktikum Modul 4 (Module 4 Lab Work Report)

### Laporan task 2 - LawakFS++

Teja adalah seorang penggemar sepak bola yang sangat bersemangat. Namun, akhir-akhir ini, tim kesayangannya selalu tampil kurang memuaskan di setiap pertandingan. Kekalahan demi kekalahan membuat Teja muak dan kesal. "Tim lawak!" begitu umpatnya setiap kali timnya gagal meraih kemenangan. Kekecewaan Teja yang mendalam ini menginspirasi sebuah ide: bagaimana jika ada sebuah filesystem yang bisa menyensor hal-hal "lawak" di dunia ini?

Untuk mengatasi hal tersebut, kami membuat filesystem terkutuk bernama *LawakFS++* yang mengimplementasikan kebijakan akses yang ketat, filtering konten dinamis, dan kontrol akses berbasis waktu untuk file tertentu. Filesystem ini dirancang sebagai read-only dan akan menerapkan perilaku khusus untuk akses file, termasuk logging dan manajemen konfigurasi.

- Kamu boleh memilih direktori sumber dan mount point apa pun untuk filesystem kamu.

- Kamu *wajib* mengimplementasikan setidaknya fungsi-fungsi berikut dalam struct fuse_operations kamu:

  - getattr
  - readdir
  - read
  - open
  - access

- Kamu diperbolehkan menyertakan fungsi tambahan seperti init, destroy, atau readlink jika diperlukan untuk implementasi kamu.

- *LawakFS++ harus benar-benar read-only.* Setiap percobaan untuk melakukan operasi tulis dalam FUSE mountpoint harus *gagal* dan mengembalikan error EROFS (Read-Only File System).

- System call berikut, dan perintah yang bergantung padanya, harus diblokir secara eksplisit:

  - write()
  - truncate()
  - create()
  - unlink()
  - mkdir()
  - rmdir()
  - rename()

> *Catatan:* Ketika pengguna mencoba menggunakan perintah seperti touch, rm, mv, atau perintah lain yang melakukan operasi tulis, mereka harus menerima error "Permission denied" atau "Read-only file system" yang jelas.

**Answer:**
- **Explanation:**
    > Disini saya membuat folder task_2 yang isinya, yaitu file LawakFS.c, dictionary sumber, dan dictionary mount_point. Di dalam dictionary sumber nanti akan diisi file-file yang akan difilter

- **Code:**
  ```
    mkdir task_2
    cd task_2
    mkdir sumber
    mkdir mount_point
    touch lawakFS.c
  ```





