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
- **Code:**
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
> Disini saya menambahkan fungsi agar file tertentu hanya bisa diakses di jam tertentu (file secret). dalam proses ini juga saya menambahkan beberapa subcode pada fungsi yang sudah ada
```
  fren@fren-virtual-machine:~/task_2$ fusermount -u mount_point
  fren@fren-virtual-machine:~/task_2$ gcc -Wall -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags` lawakFS.c -o lawakFS `pkg-config fuse --libs`
  fren@fren-virtual-machine:~/task_2$ ./lawakFS mount_point
  fren@fren-virtual-machine:~/task_2$ ls -l mount_point/
  total 4
  -rw-rw-r-- 1 fren fren 47 Jun 18 14:31 artikel
  -rw-rw-r-- 1 fren fren  0 Jun 18 14:32 gambar
  fren@fren-virtual-machine:~/task_2$ cat mount_point/secret
  cat: mount_point/secret: No such file or directory
  fren@fren-virtual-machine:~/task_2$ ls -l sumber/
  total 8
  -rw-rw-r-- 1 fren fren 47 Jun 18 14:31 artikel.txt
  -rw-rw-r-- 1 fren fren  0 Jun 18 14:32 gambar.jpg
  -rw-rw-r-- 1 fren fren 24 Jun 18 14:32 secret.log

```
##### Fungsi is_secret_and_access_denied
  - **Code:**
    ```
      static int is_secret_and_access_denied(const char *path) {
        char *path_basename = strrchr(path, '/');
        if (path_basename == NULL) {
            path_basename = (char*)path;
        } else {
            path_basename++;
        }
    
        char name_without_ext[256];
        strcpy(name_without_ext, path_basename);
    
        char *last_dot = strrchr(name_without_ext, '.');
        if (last_dot != NULL) {
            *last_dot = '\0';
        }
    
        if (strcmp(name_without_ext, "secret") == 0) {
            time_t now;
            struct tm *local_time;
            time(&now);
            local_time = localtime(&now);
            int current_hour = local_time->tm_hour;
    
            if (current_hour < 8 || current_hour >= 18) {
                return 1; 
            }
        }
    
        return 0; 
    }
    ```
- **Explanation:**
  > Algoritma fungsi ini adalah sebagai pusat pengambilan keputusan untuk aturan akses file rahasia. Saat menerima sebuah path, ia pertama-tama mengekstrak nama dasar file tersebut dan membuang ekstensinya untuk mendapatkan nama inti. Nama inti ini kemudian dibandingkan dengan string "secret" yang sudah di-hardcode. Jika namanya tidak cocok, fungsi ini langsung menyimpulkan bahwa ini bukan file yang diatur oleh aturan waktu dan mengizinkan akses. Namun, jika namanya cocok dengan "secret", fungsi akan melanjutkan ke tahap pengecekan waktu. Ia akan mengambil waktu sistem saat ini, mengonversinya ke waktu lokal, dan mengekstrak jamnya. Jam saat ini kemudian dibandingkan dengan rentang waktu yang diizinkan (antara jam 8 pagi dan sebelum jam 6 sore). Jika waktu saat ini berada di luar rentang tersebut, fungsi akan mengembalikan sinyal bahwa akses ditolak; jika tidak, akses diizinkan.

##### Penambahan subcode di beberapa fungsi 
  - **Code:**
    ```
      if (is_secret_and_access_denied(path)) {
          return -ENOENT;
      }
    ```
  - **Explanation:**
    > Penambahan fungsi ini dilakukan di fungsi lawak_getaatr, lawak_readdir, dan lawak_access
  
#### c. Filtering Konten Dinamis

Kekesalan Teja terhadap hal-hal "lawak" semakin memuncak ketika dia membaca artikel online yang penuh dengan kata-kata yang membuatnya kesal. Tidak hanya itu, gambar-gambar yang dia lihat juga sering kali tidak sesuai dengan ekspektasinya. "Semua konten yang masuk ke sistem saya harus difilter dulu!" serunya sambil mengepalkan tangan.

Ketika sebuah file dibuka dan dibaca, isinya harus *secara dinamis difilter atau diubah* berdasarkan tipe file yang terdeteksi:

| Tipe File      | Perlakuan                                                                                 |
| :------------- | :---------------------------------------------------------------------------------------- |
| *File Teks*  | Semua kata yang dianggap lawak (case-insensitive) harus diganti dengan kata "lawak".    |
| *File Biner* | Konten biner mentah harus ditampilkan dalam *encoding Base64* alih-alih bentuk aslinya. |

> *Catatan:* Daftar "kata-kata lawak" untuk filtering file teks akan didefinisikan secara eksternal, seperti yang ditentukan dalam persyaratan *e. Konfigurasi*.

**Answer:**
> Disini saya menambahkan header luar, membuat file biner acak, menambahkan fungsi baru dan memodifikasi salah satu fungsi yang sudah ada
```
  fren@fren-virtual-machine:~/task_2$ gcc -Wall -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags` lawakFS.c -o lawakFS `pkg-config fuse --libs` -lb64
  fren@fren-virtual-machine:~/task_2$ ./lawakFS mount_point
  fren@fren-virtual-machine:~/task_2$ ls -l mount_point/
  total 4
  -rw-rw-r-- 1 fren fren 47 Jun 18 14:31 artikel
  -rw-rw-r-- 1 fren fren  0 Jun 18 14:32 gambar
  fren@fren-virtual-machine:~/task_2$ cat mount_point/artikel 
  tim sepak bola lawak dan lawak adalah tim lawakfren@fren-virtual-machine:~/task_2$
```
```
  fren@fren-virtual-machine:~/task_2$ dd if=/dev/urandom of=sumber/gambar.jpg bs=1k count=1
  1+0 records in
  1+0 records out
  1024 bytes (1,0 kB, 1,0 KiB) copied, 0,000404429 s, 2,5 MB/s
  fren@fren-virtual-machine:~/task_2$ gcc -Wall -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags` lawakFS.c -o lawakFS `pkg-config fuse --libs` -lb64
  fren@fren-virtual-machine:~/task_2$ ./lawakFS mount_point
  fren@fren-virtual-machine:~/task_2$ cat mount_point/gambar
  A9BERAgU6f2Ewf25uThgtGB+QegGd2p626F1vECnQpkt6w0XQXqQLn84lI4SiV7hJF/Qv79z
  v0KU05Rlt5FMpLtr9xYbbhZsmnULSzhWq+gVBdl6OtBw25tgG1U93J2BMwFMijCPoTbfj1Rl
  Tm9uPGs3OO5yber6MaUo2PQr07PWlDkOiiyQqwRT49LmibfeTdCRWzpLpcj6sz3wYgdiWylZ
  pJasZQH0VXaubDHfAzwSH839LrJjxi4ZIb8n22tzfrMsvTtu29WD4oEpkG0GKxSThAvVoVCB
  WyqMTni2Lm48JbG/8s9WkKqVcovoRk8zv/88KJBNdPDLL4jn5/WmLy8Qvt5GVx3zvUDsC++S
  OJrEvICY978rrzczVMo1GBK5r6HfsW6f0/X9pTOvxyGse/Kzxi9I8ErVumXLvsAdb7q3qFdG
  3kfoTV3vRPatL3mhVavg9NCp9fVuSabPs1VSp5rRUcWJ9hsV7ZemH5ieHhW4K0g/dzP+Fh6j
  FnM3C/52UiHYrDT1HGVGftneOa0kuPXLGv4QFDRNRfCrixGEEjbj/06yqIEcmOWw46l4I+rI
  55xbfhjGvnP3LIWRpMj4qi/hTM0I4b7bfjwZxOhDyd6nTj9E5pdjC0HraAILa8uw7gXTBEbs
  y83Zd7cN5aKQR77+aYaQBOYefy6aolH+sm/muZrqO4sfkvymwjrmRJQYMrZOKyqKKN3w5e2A
  n2PgQHi73p+um9bFbGRRPzQ94eePBbLKRIuPpDd90b+D+dJgM/j0WYWOaEIgefxAR8ohjb/J
  +nXYjuZK5J/8LNvHCHHEhuWKvW6UWILLYmEoU95ow4Qa6VKx6D/0PJfPg1cXTiOwU4Bwmaex
  Fv1TYwLaxpCPy8mSBKOzRj8TuwC9vUbN0+1ua5wa07/irhqsGUXsd58Y2ap+cqnFTFux2jW5
  YOYiQ/WImy0bcaoT2L9WHaBj2az1uIvXhbNMY7DaP66x7tKXWUhsqqRBE6BhItB21ICpCQV9
  Yrfren@fren-virtual-machine:~/task_2$ file mount_point/gambar
  mount_point/gambar: ASCII text
  fren@fren-virtual-machine:~/task_2$ fusermount -u mount_point
```
##### Penambahan Header baru di Systemfile LawakFS.c
  - **Code:**
    ```
      fren@fren-virtual-machine:~/task_2$ sudo apt-get install libb64-dev
    ```
    ```
      #include <time.h>
      #include <stdlib.h>
      #include <b64/cencode.h> 
    ```
##### Membuat daftar kata-kata yang disensor
  - **Code:**
    ```
      const char* filter_words[] = {"mu", "chelsea", "onic", "sisop"};
      const int num_filter_words = sizeof(filter_words) / sizeof(filter_words[0]);
    ```
##### Menambahkan fungsi is_binary dan memodifikasi lawak_read
  - **Code:**
    ```
      static int is_binary(const void *data, size_t size) {
          const char *bytes = (const char *)data;
          for (size_t i = 0; i < size; i++) {
              if (bytes[i] == '\0') {
                  return 1;
              }
          }
          return 0;
      }
    ```
    > Penambahan fungsi is_binary bertujuan agar FS bisa mengecek jenis file yang dibaca (bin / teks)
    ```
      static int lawak_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
          (void)fi;
          char fpath[1000];
          find_real_path(fpath, path);
      
          int fd = open(fpath, O_RDONLY);
          if (fd == -1) return -errno;
      
          struct stat st;
          fstat(fd, &st);
          size_t file_size = st.st_size;
          if (file_size == 0) {
              close(fd);
              return 0;
          }
          
          char *file_content = (char *)malloc(file_size);
          if (file_content == NULL) {
              close(fd);
              return -ENOMEM;
          }
          read(fd, file_content, file_size);
          close(fd);
      
          char *transformed_content = NULL;
          size_t transformed_size = 0;
      
          if (is_binary(file_content, file_size)) {
              size_t b64_buf_size = file_size * 2; 
              transformed_content = (char *)malloc(b64_buf_size);
              base64_encodestate b64_state;
              base64_init_encodestate(&b64_state);
              int len1 = base64_encode_block(file_content, file_size, transformed_content, &b64_state);
              int len2 = base64_encode_blockend(transformed_content + len1, &b64_state);
              transformed_size = len1 + len2;
          } else {
              transformed_content = (char *)malloc(file_size * 2 + 1); 
              char *current_pos = transformed_content;
              char *input_ptr = file_content;
      
              while (input_ptr < file_content + file_size) {
                  char *found_word = NULL;
                  int word_len = 0;
      
                  for (int i = 0; i < num_filter_words; i++) {
                      if (strncasecmp(input_ptr, filter_words[i], strlen(filter_words[i])) == 0) {
                          found_word = (char*)filter_words[i];
                          word_len = strlen(found_word);
                          break;
                      }
                  }
      
                  if (found_word) {
                      strcpy(current_pos, "lawak");
                      current_pos += 5;
                      input_ptr += word_len;
                  } else {
                      *current_pos = *input_ptr;
                      current_pos++;
                      input_ptr++;
                  }
              }
              *current_pos = '\0'; 
              transformed_size = strlen(transformed_content);
          }
          free(file_content); 
      
          
          int bytes_to_copy = 0;
          if (offset < transformed_size) {
              bytes_to_copy = transformed_size - offset;
              if (bytes_to_copy > size) {
                  bytes_to_copy = size;
              }
              memcpy(buf, transformed_content + offset, bytes_to_copy);
          }
      
          free(transformed_content); 
          return bytes_to_copy;
      }
    ```
    > Fungsi lawak_read perlu dimodifikasi karena perannya berubah dari sekadar fungsi pass-through data menjadi pemroses konten dinamis. Implementasi awal yang menggunakan pread hanya mampu menyalin potongan data secara langsung tanpa memiliki konteks atas keseluruhan isi file. Sementara itu, fitur filtering pada Bagian C mengharuskan program untuk dapat menganalisis konten secara utuh agar bisa membedakan antara file teks dan biner, serta melakukan manipulasi data yang kompleks seperti penggantian kata atau encoding Base64. Operasi semacam ini tidak dapat dilakukan pada potongan data yang terisolasi karena memerlukan pemahaman global terhadap konten. Oleh karena itu, lawak_read harus dirancang ulang dengan algoritma baru: membaca seluruh file ke dalam buffer memori, melakukan analisis dan transformasi pada buffer tersebut, baru kemudian menyajikan data hasil transformasi kepada pengguna.

#### d. Logging Akses

Sebagai seorang yang paranoid, Teja merasa perlu untuk mencatat setiap aktivitas yang terjadi di filesystemnya. "Siapa tahu ada yang mencoba mengakses file-file penting saya tanpa izin," gumamnya sambil menyiapkan sistem logging. Dia ingin setiap gerakan tercatat dengan detail, lengkap dengan waktu dan identitas pelakunya.

Semua operasi akses file yang dilakukan dalam LawakFS++ harus *dicatat* ke file yang terletak di **/var/log/lawakfs.log**.

Setiap entri log harus mematuhi format berikut:


[YYYY-MM-DD HH:MM:SS] [UID] [ACTION] [PATH]


Di mana:

- **YYYY-MM-DD HH:MM:SS**: Timestamp operasi.
- **UID**: User ID pengguna yang melakukan aksi.
- **ACTION**: Jenis operasi FUSE (misalnya, READ, ACCESS, GETATTR, OPEN, READDIR).
- **PATH**: Path ke file atau direktori dalam FUSE mountpoint (misalnya, /secret, /images/photo.jpg).

> *Persyaratan:* Kamu *hanya diwajibkan* untuk mencatat operasi read dan access yang berhasil. Logging operasi lain (misalnya, write yang gagal) bersifat opsional.

**Answer:**
> Disini saya menambahkan fungsi baru untung loging serta menambahkannya ke beberapa fungsi yang lain
```
  fren@fren-virtual-machine:~/task_2$ sudo gcc -Wall -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags` lawakFS.c -o lawakFS `pkg-config fuse --libs` -lb64
  [sudo] password for fren: 
  fren@fren-virtual-machine:~/task_2$ sudo bash
  root@fren-virtual-machine:/home/fren/task_2# sudo ./lawakFS mount_point
  root@fren-virtual-machine:/home/fren/task_2# ls -l mount_point/
  total 8
  -rw-rw-r-- 1 fren fren   47 Jun 18 14:31 artikel
  -rw-rw-r-- 1 fren fren 1024 Jun 22 04:42 gambar
  root@fren-virtual-machine:/home/fren/task_2# cat mount_point/artikel
  tim sepak bola lawak dan lawak adalah tim lawakroot@fren-virtual-machine:/home/fren/task_2# sudo tail -f /var/log/lawakfs.log
  [2025-06-22 05:34:21] [0] [READ] [/artikel]
  ^C
  root@fren-virtual-machine:/home/fren/task_2# sudo fusermount -u mount_point
  root@fren-virtual-machine:/home/fren/task_2# exit
  exit
```
##### Penambahan fungsi loging 
- **Code:**
  ```
    void loging(const char* action, const char* path) {
        FILE *log_file = fopen("/var/log/lawakfs.log", "a");
        if (log_file == NULL) {
            return;
        }
    
        time_t now;
        time(&now);
        struct tm *local_time = localtime(&now);
    
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);
    
        uid_t uid = fuse_get_context()->uid;
    
        fprintf(log_file, "[%s] [%d] [%s] [%s]\n", timestamp, uid, action, path);
    
        fclose(log_file);
    }
  ```
  > Fungsi loging ini dibuat sebagai prosedur terpusat untuk mencatat semua aktivitas penting yang terjadi di dalam filesystem. Setiap kali sebuah aksi yang perlu dicatat (seperti READ atau ACCESS) berhasil dilakukan, fungsi ini akan dipanggil. Secara otomatis, ia akan mengumpulkan empat jenis data: timestamp waktu kejadian yang presisi, User ID (UID) dari pengguna yang melakukan aksi, jenis aksi itu sendiri, serta path dari file yang diakses. Semua informasi ini kemudian dirangkai menjadi satu baris teks dengan format standar yang telah ditentukan dan langsung ditambahkan ke baris paling akhir dari file /var/log/lawakfs.log, sehingga setiap aktivitas tercatat secara kronologis tanpa menghapus data log sebelumnya.

#### e. Konfigurasi

Setelah menggunakan filesystemnya beberapa minggu, Teja menyadari bahwa kebutuhannya berubah-ubah. Kadang dia ingin menambah kata-kata baru ke daftar filter, kadang dia ingin mengubah jam akses file secret, atau bahkan mengubah nama file secret itu sendiri. "Saya tidak mau repot-repot kompilasi ulang setiap kali ingin mengubah pengaturan!" keluhnya. Akhirnya dia memutuskan untuk membuat sistem konfigurasi eksternal yang fleksibel.

Untuk memastikan fleksibilitas, parameter-parameter berikut *tidak boleh di-hardcode* dalam source code lawak.c kamu. Sebaliknya, mereka harus dapat dikonfigurasi melalui file konfigurasi eksternal (misalnya, lawak.conf):

- *Nama file dasar* dari file 'secret' (misalnya, secret).
- *Waktu mulai* untuk mengakses file 'secret'.
- *Waktu berakhir* untuk mengakses file 'secret'.
- *Daftar kata-kata yang dipisahkan koma* yang akan difilter dari file teks.

**Contoh konten lawak.conf:**


FILTER_WORDS=ducati,ferrari,mu,chelsea,prx,onic,sisop
SECRET_FILE_BASENAME=secret
ACCESS_START=08:00
ACCESS_END=18:00


FUSE kamu harus membaca dan mem-parse file konfigurasi ini saat inisialisasi.

### Ringkasan Perilaku yang Diharapkan

Untuk memastikan kejelasan, berikut adalah tabel konsolidasi perilaku yang diharapkan untuk skenario tertentu:

| Skenario                                                              | Perilaku yang Diharapkan                                                                         |
| :-------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------- |
| Mengakses file di luar waktu yang diizinkan (misalnya, file secret) | Mengembalikan ENOENT (No such file or directory)                                               |
| Membaca file biner                                                    | Konten harus dioutput dalam *encoding Base64*                                                  |
| Membaca file teks                                                     | Kata-kata yang difilter harus diganti dengan "lawak"                                           |
| Melakukan list file di direktori mana pun                                  | Semua ekstensi file harus disembunyikan                                                          |
| Mencoba menulis, membuat, atau mengganti nama file/direktori          | Mengembalikan EROFS (Read-Only File System)                                                    |
| Logging operasi file                                                  | Entri baru harus ditambahkan ke /var/log/lawakfs.log untuk setiap operasi read dan access. |

### Contoh Perilaku

bash
$ ls /mnt/lawak/
secret   image   readme

$ cat /mnt/lawak/secret
cat: /mnt/lawak/secret: No such file or directory
# (Output ini diharapkan jika diakses di luar 08:00-18:00)

$ cat /mnt/lawak/image
<string base64 dari konten gambar>

$ cat /mnt/lawak/readme
"Ini adalah filesystem lawak."
# (Kata "sisop" asli diganti dengan "lawak")

$ sudo tail /var/log/lawakfs.log
[2025-06-10 14:01:22] [1000] [READ] /readme
[2025-06-10 14:01:24] [1000] [ACCESS] /secret



#### **Code LawakFS.c Secara Keseluruhan:**
```
  #define _DEFAULT_SOURCE
  #define FUSE_USE_VERSION 28
  #include <time.h>
  #include <stdlib.h>
  #include <b64/cencode.h>
  #include <fuse.h>
  #include <stdio.h>
  #include <string.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <dirent.h>
  #include <errno.h>
  #include <sys/time.h>
  
  static const char *source_dir = "/home/fren/task_2/sumber";
  
  const char* filter_words[] = {"mu", "chelsea", "onic", "sisop"};
  const int num_filter_words = sizeof(filter_words) / sizeof(filter_words[0]);
  
  static int is_binary(const void *data, size_t size) {
      const char *bytes = (const char *)data;
      for (size_t i = 0; i < size; i++) {
          if (bytes[i] == '\0') {
              return 1;
          }
      }
      return 0;
  }
  
  
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
  
  static int lawak_mkdir(const char *path, mode_t mode) { return -EROFS; }
  static int lawak_rmdir(const char *path) { return -EROFS; }
  static int lawak_unlink(const char *path) { return -EROFS; }
  static int lawak_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) { return -EROFS; }
  static int lawak_rename(const char *from, const char *to) { return -EROFS; }
  static int lawak_truncate(const char *path, off_t size) { return -EROFS; }
  static int lawak_create(const char *path, mode_t mode, struct fuse_file_info *fi) { return -EROFS; }
  
  static int is_secret_and_access_denied(const char *path) {
      char *path_basename = strrchr(path, '/');
      if (path_basename == NULL) {
          path_basename = (char*)path;
      } else {
          path_basename++;
      }
  
      char name_without_ext[256];
      strcpy(name_without_ext, path_basename);
  
      char *last_dot = strrchr(name_without_ext, '.');
      if (last_dot != NULL) {
          *last_dot = '\0';
      }
  
      if (strcmp(name_without_ext, "secret") == 0) {
          time_t now;
          struct tm *local_time;
          time(&now);
          local_time = localtime(&now);
          int current_hour = local_time->tm_hour;
  
          if (current_hour < 8 || current_hour >= 18) {
              return 1; 
          }
      }
  
      return 0; 
  }
  
  static int lawak_getattr(const char *path, struct stat *stbuf) {
      if (is_secret_and_access_denied(path)) {
          return -ENOENT;
      }
  
      int res;
      char fpath[1000];
      find_real_path(fpath, path);
  
      res = lstat(fpath, stbuf);
      if (res == -1) return -errno;
      return 0;
  }
  
  static int lawak_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
      (void) offset;
      (void) fi;
      char fpath[1000];
      
      sprintf(fpath, "%s%s", source_dir, path);
  
      DIR *dp = opendir(fpath);
      if (dp == NULL) return -errno;
  
      struct dirent *de;
      while ((de = readdir(dp)) != NULL) {
          char entry_path[1000];
          sprintf(entry_path, "%s%s%s", path, strcmp(path, "/") == 0 ? "" : "/", de->d_name);
  
          if (is_secret_and_access_denied(entry_path)) {
              continue; 
          }
  
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
  
  static int lawak_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
      (void)fi;
      char fpath[1000];
      find_real_path(fpath, path);
  
      int fd = open(fpath, O_RDONLY);
      if (fd == -1) return -errno;
  
      struct stat st;
      fstat(fd, &st);
      size_t file_size = st.st_size;
      if (file_size == 0) {
          close(fd);
          return 0;
      }
      
      char *file_content = (char *)malloc(file_size);
      if (file_content == NULL) {
          close(fd);
          return -ENOMEM;
      }
      read(fd, file_content, file_size);
      close(fd);
  
      char *transformed_content = NULL;
      size_t transformed_size = 0;
  
      if (is_binary(file_content, file_size)) {
          size_t b64_buf_size = file_size * 2; 
          transformed_content = (char *)malloc(b64_buf_size);
          base64_encodestate b64_state;
          base64_init_encodestate(&b64_state);
          int len1 = base64_encode_block(file_content, file_size, transformed_content, &b64_state);
          int len2 = base64_encode_blockend(transformed_content + len1, &b64_state);
          transformed_size = len1 + len2;
      } else {
          transformed_content = (char *)malloc(file_size * 2 + 1); 
          char *current_pos = transformed_content;
          char *input_ptr = file_content;
  
          while (input_ptr < file_content + file_size) {
              char *found_word = NULL;
              int word_len = 0;
  
              for (int i = 0; i < num_filter_words; i++) {
                  if (strncasecmp(input_ptr, filter_words[i], strlen(filter_words[i])) == 0) {
                      found_word = (char*)filter_words[i];
                      word_len = strlen(found_word);
                      break;
                  }
              }
  
              if (found_word) {
                  strcpy(current_pos, "lawak");
                  current_pos += 5;
                  input_ptr += word_len;
              } else {
                  *current_pos = *input_ptr;
                  current_pos++;
                  input_ptr++;
              }
          }
          *current_pos = '\0'; 
          transformed_size = strlen(transformed_content);
      }
      free(file_content); 
  
      
      int bytes_to_copy = 0;
      if (offset < transformed_size) {
          bytes_to_copy = transformed_size - offset;
          if (bytes_to_copy > size) {
              bytes_to_copy = size;
          }
          memcpy(buf, transformed_content + offset, bytes_to_copy);
      }   
  
      free(transformed_content); 
      return bytes_to_copy;
  }
  
  static int lawak_open(const char *path, struct fuse_file_info *fi) {
      char fpath[1000];
      find_real_path(fpath, path);
      return 0;
  }
  
  static int lawak_access(const char *path, int mask) {
      if (is_secret_and_access_denied(path)) {
          return -ENOENT;
      }
  
      char fpath[1000];
      find_real_path(fpath, path);
      return 0;
  }
  
  static struct fuse_operations lawak_oper = {
      .getattr = lawak_getattr,
      .readdir = lawak_readdir,
      .read = lawak_read,
      .open = lawak_open,
      .access = lawak_access,
      .mkdir = lawak_mkdir,
      .rmdir = lawak_rmdir,
      .unlink = lawak_unlink,
      .write = lawak_write,
      .rename = lawak_rename,
      .truncate = lawak_truncate,
      .create = lawak_create,
  };
  
  int main(int argc, char *argv[]) {
      umask(0);
      return fuse_main(argc, argv, &lawak_oper, NULL);
  }
```



