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

- **Code:**
  ```
    mkdir task_2
    cd task_2
    mkdir sumber
    mkdir mount_point
    touch lawakFS.c
  ```
  ```
    static int lawak_mkdir(const char *path, mode_t mode) { return -EROFS; }
    static int lawak_rmdir(const char *path) { return -EROFS; }
    static int lawak_unlink(const char *path) { return -EROFS; }
    static int lawak_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) { return -EROFS; }
    static int lawak_rename(const char *from, const char *to) { return -EROFS; }
    static int lawak_truncate(const char *path, off_t size) { return -EROFS; }
    static int lawak_create(const char *path, mode_t mode, struct fuse_file_info *fi) { return -EROFS; }
  ```
  
- **Explanation:**
    > Disini saya membuat folder task_2 yang isinya, yaitu file LawakFS.c, dictionary sumber, dan dictionary mount_point. Di dalam dictionary sumber nanti akan diisi file-file yang akan difilter. Di dalam file LawakFS.c saya mematikan beberapa fungsi agar file system LawakFS.c hanya dapat menjalankan mode read-only.
  
#### a. Ekstensi File Tersembunyi

Setelah beberapa hari menggunakan filesystem biasa, Teja menyadari bahwa ekstensi file selalu membuat orang-orang bisa mengetahui jenis file dengan mudah. "Ini terlalu mudah ditebak!" pikirnya. Dia ingin membuat sistem yang lebih misterius, di mana orang harus benar-benar membuka file untuk mengetahui isinya.

Semua file yang ditampilkan dalam FUSE mountpoint harus *ekstensinya disembunyikan*.

- *Contoh:* Jika file asli adalah document.pdf, perintah ls di dalam direktori FUSE hanya menampilkan document.
- *Perilaku:* Meskipun ekstensi disembunyikan, mengakses file (misalnya, cat /mnt/your_mountpoint/document) harus dipetakan dengan benar ke path dan nama aslinya (misalnya, source_dir/document.pdf).

**Answer:**
  > Pada tahap ini saya mengimplementasikan fungsi-fungsi FUSE dan memodifikasinya agar dapat melakukan filter dan me-mounting ke sumber aslinya tanpa extensi
  ```
    fren@fren-virtual-machine:~/task_2$ ls -l mount_point/
    total 0
    fren@fren-virtual-machine:~/task_2$ ./lawakFS mount_point
    fren@fren-virtual-machine:~/task_2$ ls -l mount_point/
    total 4
    -rw-rw-r-- 1 fren fren 47 Jun 18 14:31 artikel
    -rw-rw-r-- 1 fren fren  0 Jun 18 14:32 gambar
    fren@fren-virtual-machine:~/task_2$ cat mount_point/artikel 
    tim sepak bola chelsea dan mu adalah tim lawak
    fren@fren-virtual-machine:~/task_2$ ls -l sumber/
    total 8
    -rw-rw-r-- 1 fren fren 47 Jun 18 14:31 artikel.txt
    -rw-rw-r-- 1 fren fren  0 Jun 18 14:32 gambar.jpg
    -rw-rw-r-- 1 fren fren 24 Jun 18 14:32 secret.log
  ```

##### Fungsi find_real_path
- **Code:**
  ```
    static const char *source_dir = "/home/fren/task_2/sumber";

    static void find_real_path(char fpath[1000], const char *path) {
        char temp_path[1000];   
        sprintf(temp_path, "%s%s", source_dir, path);
    
        struct stat st;
        if (lstat(temp_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            strcpy(fpath, temp_path);
            return;
        }
    
        char parent_path[1000];
        char *last_slash = strrchr(path, '/');
        if (last_slash == NULL) {
            strcpy(parent_path, "/");
        } else {
            strncpy(parent_path, path, last_slash - path + 1);
            parent_path[last_slash - path + 1] = '\0';
        }
        
        char source_parent_path[1000];
        sprintf(source_parent_path, "%s%s", source_dir, parent_path);
    
        char *short_name = (last_slash == NULL) ? (char*)path : last_slash + 1;
        
        DIR *dp = opendir(source_parent_path);
        if (dp == NULL) {
            strcpy(fpath, temp_path);
            return;
        }
    
        struct dirent *de;
        int found = 0;
        while ((de = readdir(dp)) != NULL) {
            if (de->d_type == DT_REG) {
                char real_name_base[256];
                strcpy(real_name_base, de->d_name);
                char *last_dot = strrchr(real_name_base, '.');
                if (last_dot != NULL) {
                    *last_dot = '\0';
                }
    
                if (strcmp(short_name, real_name_base) == 0) {
                    sprintf(fpath, "%s%s", source_parent_path, de->d_name);
                    found = 1;
                    break;
                }
            }
        }
        closedir(dp);
    
        if (!found) {
            strcpy(fpath, temp_path);
        }
    }

  ```
- **Explanation:**
  > find_real_path merupakan fungsi yang menerima path tanpa ekstensi kemudian menerjemahkannya ke dalam path asli. Pertama-tama, fungsi ini membuat asumsi awal dengan menggabungkan path direktori sumber dan path virtual untuk membentuk sebuah path tebakan. Sebagai langkah optimasi, kemudian langsung memeriksa apakah path tebakan ini merupakan sebuah direktori yang valid; jika ya, maka path tersebut dianggap benar dan fungsi selesai. Namun, jika path tersebut bukan direktori, maka proses pencarian yang lebih mendalam dimulai dengan memecah path virtual menjadi dua komponen: direktori induknya dan nama dasar filenya (short_name). Selanjutnya, fungsi akan membuka lokasi direktori induk yang sesungguhnya di dalam direktori sumber, lalu melakukan iterasi terhadap setiap file di dalamnya. Untuk setiap file nyata yang ditemukan, ekstensinya akan "dibuang" sementara untuk dibandingkan dengan short_name yang diberikan pengguna. Apabila ditemukan kecocokan, fungsi akan segera membangun path lengkap yang benar ke file nyata tersebut (lengkap dengan ekstensinya) dan menyimpannya sebagai hasil akhir. Namun, jika setelah memeriksa seluruh isi direktori tidak ada satu pun file yang cocok, fungsi akan dengan sengaja mengembalikan path asumsi awal yang salah. Langkah "kegagalan yang disengaja" ini sangat penting, karena memastikan bahwa operasi selanjutnya seperti open atau lstat akan gagal secara alami dengan eror "No such file or directory", yang merupakan perilaku yang benar dan diharapkan.

##### Fungsi lawak_readdir
- **code:**
  ```
    static int lawak_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
        (void) offset;
        (void) fi;
        char fpath[1000];
        
        sprintf(fpath, "%s%s", source_dir, path);
    
        DIR *dp = opendir(fpath);
        if (dp == NULL) return -errno;
    
        struct dirent *de;
        while ((de = readdir(dp)) != NULL) {
            if (de->d_type == DT_REG) { 
                char file_name[256];
                strcpy(file_name, de->d_name); 
                char *last_dot = strrchr(file_name, '.'); 
                if (last_dot != NULL) *last_dot = '\0'; 
                if (filler(buf, file_name, NULL, 0) != 0) break;
            } else { 
                if (filler(buf, de->d_name, NULL, 0) != 0) break;
            }
        }
        closedir(dp);
        return 0;
    }
  ```
- **Explanation:**
  > Algoritma untuk fungsi lawak_readdir bertujuan untuk menyajikan daftar isi sebuah direktori dengan menyembunyikan ekstensi untuk file biasa. Prosesnya dimulai dengan membentuk path absolut ke direktori sumber yang sebenarnya berdasarkan path virtual yang diminta. Setelah direktori sumber berhasil dibuka, fungsi ini akan melakukan iterasi atau perulangan untuk membaca setiap entri di dalamnya. Di dalam setiap iterasi, sebuah logika kondisional penting dijalankan: fungsi akan memeriksa tipe dari setiap entri. Jika entri tersebut adalah sebuah direktori, namanya akan langsung disajikan kepada pengguna tanpa perubahan. Namun, jika entri tersebut adalah sebuah file reguler, fungsi akan membuat salinan dari nama file tersebut, mencari posisi titik terakhir yang menandakan awal ekstensi, dan memotong string nama di titik tersebut. Hanya nama yang sudah dimodifikasi (tanpa ekstensi) inilah yang kemudian disajikan kepada pengguna. Proses ini berlanjut hingga semua entri dalam direktori telah diperiksa dan disajikan dengan format yang sesuai.

##### Fungsi lawak_getattr
- **COde:**
  ```
    static int lawak_getattr(const char *path, struct stat *stbuf) {
        int res;
        char fpath[1000];
        find_real_path(fpath, path);
    
        res = lstat(fpath, stbuf);
        if (res == -1) return -errno;
        return 0;
    }
  ```
- **Explanation:**
  > Algoritma fungsi lawak_getattr dirancang untuk mendapatkan atribut sebuah file atau direktori (seperti ukuran, hak akses, dan waktu modifikasi) dari nama virtual yang mungkin tidak memiliki ekstensi. Karena ia menerima nama yang bisa jadi "palsu", langkah pertamanya yang paling krusial adalah tidak langsung berinteraksi dengan sistem, melainkan mendelegasikan tugas penerjemahan ke fungsi find_real_path. Fungsi ini mengambil nama virtual sebagai input dan mengembalikan path lengkap ke file atau direktori yang sebenarnya di dalam direktori sumber. Setelah path yang benar dan lengkap ini didapatkan, algoritma lawak_getattr menjadi sangat sederhana: ia hanya perlu memanggil fungsi sistem standar lstat pada path nyata tersebut untuk mengisi struktur atribut yang diminta, lalu mengembalikan hasilnya.

##### Fungsi lawak_read
- **COde:**
  ```
    static int lawak_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
        (void) fi;
        int res;
        char fpath[1000];
        find_real_path(fpath, path);
    
        int fd = open(fpath, O_RDONLY);
        if (fd == -1) return -errno;
    
        res = pread(fd, buf, size, offset);
        if (res == -1) res = -errno;
    
        close(fd);
        return res;
    }
  ```
- **Explanation:**
  > Algoritma untuk fungsi lawak_read mengikuti pola yang sangat mirip dengan lawak_getattr, di mana tugas utamanya adalah membaca konten dari sebuah file yang diidentifikasi oleh nama virtualnya. Saat dipanggil, fungsi ini tidak bisa langsung membuka path yang diberikan. Sebagai langkah pertama yang wajib, ia memanggil fungsi find_real_path untuk menerjemahkan path virtual (misalnya /artikel) menjadi path absolut yang nyata (.../sumber/artikel.txt). Setelah mendapatkan path yang benar, algoritma ini melanjutkan dengan melakukan urutan operasi file I/O standar: ia memanggil open() pada path nyata untuk mendapatkan file descriptor, kemudian menggunakan pread() untuk membaca sejumlah data dari offset tertentu ke dalam buffer yang disediakan, dan terakhir memanggil close() untuk menutup file. Hasil dari operasi pread inilah yang kemudian dikembalikan ke sistem.
  
##### Fungsi lawak_open dan lawak_accsess
- **COde:**
  ```
    static int lawak_open(const char *path, struct fuse_file_info *fi) {
        char fpath[1000];
        find_real_path(fpath, path);
        return 0;
    }
  ```
  ```
    static int lawak_access(const char *path, int mask) {
        char fpath[1000];
        find_real_path(fpath, path);
        return 0;
    }
  ```
- **Explanation:**
  > Algoritma untuk fungsi lawak_open dan lawak_access dalam konteks ini berfungsi sebagai penangan awal untuk permintaan akses file. Seperti fungsi-fungsi lainnya yang beroperasi pada file individual, algoritma inti mereka juga diawali dengan keharusan untuk menerjemahkan nama virtual. Keduanya menerima path virtual dari sistem dan segera memanggil find_real_path untuk mengidentifikasi file nyata yang sedang dituju. Dalam implementasi saat ini, setelah path nyata ditemukan, logika mereka sangat sederhana dan hanya mengembalikan nilai 0 yang menandakan keberhasilan, karena pengecekan lebih lanjut akan ditangani oleh sistem atau fungsi read. Meskipun terlihat trivial, pemanggilan find_real_path di sini sangat penting sebagai fondasi untuk memastikan logika di masa depan (seperti pengecekan akses berbasis waktu) diterapkan pada file yang benar.

#### b. Akses Berbasis Waktu untuk File Secret

Suatu hari, Teja menemukan koleksi foto-foto memalukan dari masa SMA-nya yang tersimpan dalam folder bernama "secret". Dia tidak ingin orang lain bisa mengakses file-file tersebut kapan saja, terutama saat dia sedang tidur atau tidak ada di rumah. "File rahasia hanya boleh dibuka saat jam kerja!" putusnya dengan tegas.

File yang nama dasarnya adalah **secret** (misalnya, secret.txt, secret.zip) hanya dapat diakses *antara pukul 08:00 (8 pagi) dan 18:00 (6 sore) waktu sistem*.

- *Pembatasan:* Di luar rentang waktu yang ditentukan, setiap percobaan untuk membuka, membaca, atau bahkan melakukan list file secret harus menghasilkan error ENOENT (No such file or directory).
- *Petunjuk:* Kamu perlu mengimplementasikan kontrol akses berbasis waktu ini dalam operasi FUSE access() dan/atau getattr() kamu.

**Answer:** 
```
  ren@fren-virtual-machine:~/task_2$ fusermount -u mount_point
  fren@fren-virtual-machine:~/task_2$ gcc -Wall -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags` lawakFS.c -o lawakFS `pkg-config fuse --libs`
  fren@fren-virtual-machine:~/task_2$ ./lawakFS mount_point
  fren@fren-virtual-machine:~/task_2$ ls -l mount_point/
  total 4
  -rw-rw-r-- 1 fren fren 47 Jun 18 14:31 artikel
  -rw-rw-r-- 1 fren fren  0 Jun 18 14:32 gambar
  fren@fren-virtual-machine:~/task_2$ cat mount_point/secret
  cat: mount_point/secret: No such file or directory
  fren@fren-virtual-machine:~/task_2$ cd mount_point/
```


  



