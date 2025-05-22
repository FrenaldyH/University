|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221000 | Student 1 Name |
| 5025221000 | Student 2 Name |
| 5025221000 | Student 3 Name |

# Praktikum Modul 3 _(Module 3 Lab Work)_

### Laporan Resmi Praktikum Modul 3 _(Module 3 Lab Work Report)_

Di suatu pagi hari yang cerah, Budiman salah satu mahasiswa Informatika ditugaskan oleh dosennya untuk membuat suatu sistem operasi sederhana. Akan tetapi karena Budiman memiliki keterbatasan, Ia meminta tolong kepadamu untuk membantunya dalam mengerjakan tugasnya. Bantulah Budiman untuk membuat sistem operasi sederhana!

_One sunny morning, Budiman, an Informatics student, was assigned by his lecturer to create a simple operating system. However, due to Budiman's limitations, he asks for your help to assist him in completing his assignment. Help Budiman create a simple operating system!_

### Soal 1

> Sebelum membuat sistem operasi, Budiman diberitahu dosennya bahwa Ia harus melakukan beberapa tahap terlebih dahulu. Tahap-tahapan yang dimaksud adalah untuk **mempersiapkan seluruh prasyarat** dan **melakukan instalasi-instalasi** sebelum membuat sistem operasi. Lakukan seluruh tahapan prasyarat hingga [perintah ini](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/Modul3/README-ID.md#:~:text=sudo%20apt%20install%20%2Dy%20busybox%2Dstatic) pada modul!

> _Before creating the OS, Budiman was informed by his lecturer that he must complete several steps first. The steps include **preparing all prerequisites** and **installing** before creating the OS. Complete all the prerequisite steps up to [this command](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/Modul3/README-ID.md#:~:text=sudo%20apt%20install%20%2Dy%20busybox%2Dstatic) in the module!_

**Answer:**

- **Explanation:**

  ```Disini kami sudah mendownload VMWare dan mengalokasikan memori 5GB untuk VMware. Selain itu kami juga menjalankan subcode subcode pada modul dari awal hingga akhir```

- **Screenshot:**

  - [Screenshot VMWare](https://github.com/user-attachments/assets/51e58eac-7dcf-46d7-a52b-2672e5cdf636)
  - [Screenshot Osboot](https://github.com/user-attachments/assets/f2768be3-4d18-4629-81cd-e5586421624e)


### Soal 2

> Setelah seluruh prasyarat siap, Budiman siap untuk membuat sistem operasinya. Dosen meminta untuk sistem operasi Budiman harus memiliki directory **bin, dev, proc, sys, tmp,** dan **sisop**. Lagi-lagi Budiman meminta bantuanmu. Bantulah Ia dalam membuat directory tersebut!

> _Once all prerequisites are ready, Budiman is ready to create his OS. The lecturer asks that the OS should contain the directories **bin, dev, proc, sys, tmp,** and **sisop**. Help Budiman create these directories!_

**Answer:**

- **Code:**

  `mkdir bin dev proc sys tmp sisop`

- **Explanation:**

  `disini kami menggunakan perintah sederhana {mkdir} untuk membuat directorynya`

- **Screenshot:**

  [Hasil Screenshot](https://github.com/user-attachments/assets/899e2e09-cf63-4fc6-9058-07f87b31de12)

### Soal 3

> Budiman lupa, Ia harus membuat sistem operasi ini dengan sistem **Multi User** sesuai permintaan Dosennya. Ia meminta kembali kepadamu untuk membantunya membuat beberapa user beserta directory tiap usernya dibawah directory `home`. Buat pula password tiap user-usernya dan aplikasikan dalam sistem operasi tersebut!

> _Budiman forgot that he needs to create a **Multi User** system as requested by the lecturer. He asks your help again to create several users and their corresponding home directories under the `home` directory. Also set each user's password and apply them in the OS!_

**Format:** `user:pass`

```
root:Iniroot
Budiman:PassBudi
guest:guest
praktikan1:praktikan1
praktikan2:praktikan2
```

**Answer:**



- **Code:**

  ```
    fren@fren-virtual-machine:~/Praktikum$ openssl passwd -1 Iniroot
    $1$T2K6D1rC$gDRgBw5wlnHLprpLNvyai/
    fren@fren-virtual-machine:~/Praktikum$ openssl passwd -1 PassBudi
    $1$59Tr/gKo$oD6c3oeRBwz613P10HvS80
    fren@fren-virtual-machine:~/Praktikum$ openssl passwd -1 guest
    $1$RHZeDuT7$tRMsv..Ws5xhjRJTKmKk5.
    fren@fren-virtual-machine:~/Praktikum$ openssl passwd -1 praktikan1
    $1$iu5qKlk2$Of4hRddumEGNToU2OFe6Y0
    fren@fren-virtual-machine:~/Praktikum$ openssl passwd -1 praktikan2
    $1$ORaET2v7$ZTCLcYXyTC5gLHlJxMFgu.
    fren@fren-virtual-machine:~/Praktikum$ ls
    bin  dev  etc  home  proc  sisop  sys  tmp
    fren@fren-virtual-machine:~/Praktikum$ cd etc/
    fren@fren-virtual-machine:~/Praktikum/etc$ ls
    passwd
    fren@fren-virtual-machine:~/Praktikum/etc$ nano passwd 
    fren@fren-virtual-machine:~/Praktikum/etc$ nano passwd 
    fren@fren-virtual-machine:~/Praktikum/etc$ sudo nano passwd 
    [sudo] password for fren: 
    fren@fren-virtual-machine:~/Praktikum/etc$ ls
    passwd
  ```

  ```
    root:$1$T2K6D1rC$gDRgBw5wlnHLprpLNvyai/:0:0:root:/root:/bin/sh
    Budiman:$1$59Tr/gKo$oD6c3oeRBwz613P10HvS80:1001:100:Budiman:/home/Budiman:/bin/sh
    guest:$1$RHZeDuT7$tRMsv..Ws5xhjRJTKmKk5.:1002:100:guest:/home/guest:/bin/sh
    praktikan1:$1$iu5qKlk2$Of4hRddumEGNToU2OFe6Y0:1003:100:praktikan1:/home/praktikan1:/bin/sh
    praktikan2:$1$ORaET2v7$ZTCLcYXyTC5gLHlJxMFgu.:1004:100:praktikan2:/home/praktikan2:/bin/sh
  ```

- **Explanation:**

  ```
    Beberapa langkah yang saya jalankan:
    1. membuat directory user dan passwd
    2. menggenerate hash dan password user usernya
    3. menyimpan hasil dari generate hash dan password user-usernya di file /etc/passwd
  ```

- **Screenshot:**

  - [Screenshot Terminal](https://github.com/user-attachments/assets/742ec3ad-438e-4467-b9e0-af52017b4cf6)
  - [Screenshot passwd](https://github.com/user-attachments/assets/8a52b6b4-a086-45f6-912e-437ce18fb299)
  - [Screenshot isi directory home](https://github.com/user-attachments/assets/78ec177d-8b6d-4bf6-9d61-9f0348cd8b3a)

### Soal 4

> Dosen meminta Budiman membuat sistem operasi ini memilki **superuser** layaknya sistem operasi pada umumnya. User root yang sudah kamu buat sebelumnya akan digunakan sebagai superuser dalam sistem operasi milik Budiman. Superuser yang dimaksud adalah user dengan otoritas penuh yang dapat mengakses seluruhnya. Akan tetapi user lain tidak boleh memiliki otoritas yang sama. Dengan begitu user-user selain root tidak boleh mengakses `./root`. Buatlah sehingga tiap user selain superuser tidak dapat mengakses `./root`!

> _The lecturer requests that the OS must have a **superuser** just like other operating systems. The root user created earlier will serve as the superuser in Budiman's OS. The superuser should have full authority to access everything. However, other users should not have the same authority. Therefore, users other than root should not be able to access `./root`. Implement this so that non-superuser accounts cannot access `./root`!_

**Answer:**

- **Code:**

  ```
    fren@fren-virtual-machine:~$ ls
    Desktop  Documents  Downloads  modul  Music  Pictures  Praktikum  Public  snap  Templates  Videos
    fren@fren-virtual-machine:~$ cd Praktikum/
    fren@fren-virtual-machine:~/Praktikum$ ls
    bin  dev  etc  home  proc  sisop  sys  tmp
    fren@fren-virtual-machine:~/Praktikum$ mkdir root
    fren@fren-virtual-machine:~/Praktikum$ ls
    bin  dev  etc  home  proc  root  sisop  sys  tmp
    fren@fren-virtual-machine:~/Praktikum$ chmod 700 ./root
    fren@fren-virtual-machine:~/Praktikum$ ls
    bin  dev  etc  home  proc  root  sisop  sys  tmp
    fren@fren-virtual-machine:~/Praktikum$ ls -l
    total 36
    drwxrwxr-x 2 fren fren 4096 Mei 22 19:37 bin
    drwxrwxr-x 2 fren fren 4096 Mei 22 19:37 dev
    drwxrwxr-x 2 fren fren 4096 Mei 23 00:08 etc
    drwxrwxr-x 6 fren fren 4096 Mei 22 23:56 home
    drwxrwxr-x 2 fren fren 4096 Mei 22 19:37 proc
    drwx------ 2 fren fren 4096 Mei 23 00:46 root
    drwxrwxr-x 2 fren fren 4096 Mei 22 19:37 sisop
    drwxrwxr-x 2 fren fren 4096 Mei 22 19:37 sys
    drwxrwxr-x 2 fren fren 4096 Mei 22 19:37 tmp
    fren@fren-virtual-machine:~/Praktikum$ chown root:root ./root
    chown: changing ownership of './root': Operation not permitted
    fren@fren-virtual-machine:~/Praktikum$ sudo chown root:root ./root
    [sudo] password for fren: 
    fren@fren-virtual-machine:~/Praktikum$ ls -ld ./root
    drwx------ 2 root root 4096 Mei 23 00:46 ./root
  ```

- **Explanation:**

  ```
    Disini saya melakukan beberapa langkah:
    1. buat dulu folder root karena sebelumya tidak ada
    2. ubah permissionnya ke 700 -> 111 000 000, artinya hany terbatas pada pemilik
    3. membuat kepemilikan ./root oleh root
    4. memastikan kepemilikan ./root oleh root dengan ls -ld
  ```

- **Screenshot:**

  - [Screenshot terminal](https://github.com/user-attachments/assets/f90559fb-35c8-42d1-ab99-444f6835482e)

### Soal 5

> Setiap user rencananya akan digunakan oleh satu orang tertentu. **Privasi dan otoritas tiap user** merupakan hal penting. Oleh karena itu, Budiman ingin membuat setiap user hanya bisa mengakses dirinya sendiri dan tidak bisa mengakses user lain. Buatlah sehingga sistem operasi Budiman dalam melakukan hal tersebut!

> _Each user is intended for an individual. **Privacy and authority** for each user are important. Therefore, Budiman wants to ensure that each user can only access their own files and not those of others. Implement this in Budiman's OS!_

**Answer:**

- **Code:**

  ```
    fren@fren-virtual-machine:~/Praktikum/home$ ls -l
    total 16
    drwxrwxr-x 2 775 fren 4096 Mei 22 23:56 Budiman
    drwxrwxr-x 2 775 fren 4096 Mei 22 23:56 guest
    drwxrwxr-x 2 775 fren 4096 Mei 22 23:56 praktikan1
    drwxrwxr-x 2 775 fren 4096 Mei 22 23:56 praktikan2
    fren@fren-virtual-machine:~/Praktikum/home$ sudo chmod 700 *
    fren@fren-virtual-machine:~/Praktikum/home$ ls -l
    total 16
    drwx------ 2 775 fren 4096 Mei 22 23:56 Budiman
    drwx------ 2 775 fren 4096 Mei 22 23:56 guest
    drwx------ 2 775 fren 4096 Mei 22 23:56 praktikan1
    drwx------ 2 775 fren 4096 Mei 22 23:56 praktikan2
    fren@fren-virtual-machine:~/Praktikum/home$ sudo chown -R 1001:100 Budiman
    fren@fren-virtual-machine:~/Praktikum/home$ sudo chown -R 1002:100 guest
    fren@fren-virtual-machine:~/Praktikum/home$ sudo chown -R 1003:100 praktikan1
    fren@fren-virtual-machine:~/Praktikum/home$ sudo chown -R 1004:100 praktikan2
    fren@fren-virtual-machine:~/Praktikum/home$ ls -l
    total 16
    drwx------ 2 1001 users 4096 Mei 22 23:56 Budiman
    drwx------ 2 1002 users 4096 Mei 22 23:56 guest
    drwx------ 2 1003 users 4096 Mei 22 23:56 praktikan1
    drwx------ 2 1004 users 4096 Mei 22 23:56 praktikan2
  ```

- **Explanation:**

  ```
    Disini saya melakukan beberapa langkah yaitu:
    1. melihat dulu permission masing-masing dictionary di home/ dengan menggunakan ls -l
    2. mengubah semua permission (*) dictionary di home dengan 700 -> 111 000 000
    3. menyetel kepemilikan masing-masing dictionary
    4. memastikan kembali permission dan kepemilikan masing-masing dictionary 
  ```

- **Screenshot:**
  - [Screenshot terminal](https://github.com/user-attachments/assets/fc4cd3cc-a5a5-4a4b-bbd3-f50bbc77170f)

### Soal 6

> Dosen Budiman menginginkan sistem operasi yang **stylish**. Budiman memiliki ide untuk membuat sistem operasinya menjadi stylish. Ia meminta kamu untuk menambahkan tampilan sebuah banner yang ditampilkan setelah suatu user login ke dalam sistem operasi Budiman. Banner yang diinginkan Budiman adalah tulisan `"Welcome to OS'25"` dalam bentuk **ASCII Art**. Buatkanlah banner tersebut supaya Budiman senang! (Hint: gunakan text to ASCII Art Generator)

> _Budiman wants a **stylish** operating system. Budiman has an idea to make his OS stylish. He asks you to add a banner that appears after a user logs in. The banner should say `"Welcome to OS'25"` in **ASCII Art**. Use a text to ASCII Art generator to make Budiman happy!_ (Hint: use a text to ASCII Art generator)

**Answer:**

- **Code:**

  `put your answer here`

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 7

> Melihat perkembangan sistem operasi milik Budiman, Dosen kagum dengan adanya banner yang telah kamu buat sebelumnya. Kemudian Dosen juga menginginkan sistem operasi Budiman untuk dapat menampilkan **kata sambutan** dengan menyebut nama user yang login. Sambutan yang dimaksud berupa kalimat `"Helloo %USER"` dengan `%USER` merupakan nama user yang sedang menggunakan sistem operasi. Kalimat sambutan ini ditampilkan setelah user login dan setelah banner. Budiman kembali lagi meminta bantuanmu dalam menambahkan fitur ini.

> _Seeing the progress of Budiman's OS, the lecturer is impressed with the banner you created. The lecturer also wants the OS to display a **greeting message** that includes the name of the user who logs in. The greeting should say `"Helloo %USER"` where `%USER` is the name of the user currently using the OS. This greeting should be displayed after user login and after the banner. Budiman asks for your help again to add this feature._

**Answer:**

- **Code:**

  `put your answer here`

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 8

> Dosen Budiman sudah tua sekali, sehingga beliau memiliki kesulitan untuk melihat tampilan terminal default. Budiman menginisiatif untuk membuat tampilan sistem operasi menjadi seperti terminal milikmu. Modifikasilah sistem operasi Budiman menjadi menggunakan tampilan terminal kalian.

> _Budiman's lecturer is quite old and has difficulty seeing the default terminal display. Budiman takes the initiative to make the OS look like your terminal. Modify Budiman's OS to use your terminal appearance!_

**Answer:**

- **Code:**

  `put your answer here`

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 9

> Ketika mencoba sistem operasi buatanmu, Budiman tidak bisa mengubah text file menggunakan text editor. Budiman pun menyadari bahwa dalam sistem operasi yang kamu buat tidak memiliki text editor. Budimanpun menyuruhmu untuk menambahkan **binary** yang telah disiapkan sebelumnya ke dalam sistem operasinya. Buatlah sehingga sistem operasi Budiman memiliki **binary text editor** yang telah disiapkan!

> _When trying your OS, Budiman cannot edit text files using a text editor. He realizes that the OS you created does not have a text editor. Budiman asks you to add the prepared **binary** into his OS. Make sure Budiman's OS has the prepared **text editor binary**!_

**Answer:**

- **Code:**

  `put your answer here`

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 10

> Setelah seluruh fitur yang diminta Dosen dipenuhi dalam sistem operasi Budiman, sudah waktunya Budiman mengumpulkan tugasnya ini ke Dosen. Akan tetapi, Dosen Budiman tidak mau menerima pengumpulan selain dalam bentuk **.iso**. Untuk terakhir kalinya, Budiman meminta tolong kepadamu untuk mengubah seluruh konfigurasi sistem operasi yang telah kamu buat menjadi sebuah **file .iso**.

> After all the features requested by the lecturer have been implemented in Budiman's OS, it's time for Budiman to submit his assignment. However, Budiman's lecturer only accepts submissions in the form of **.iso** files. For the last time, Budiman asks for your help to convert the entire configuration of the OS you created into a **.iso file**.

**Answer:**

- **Code:**

  `put your answer here`

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

---

Pada akhirnya sistem operasi Budiman yang telah kamu buat dengan susah payah dikumpulkan ke Dosen mengatasnamakan Budiman. Kamu tidak diberikan credit apapun. Budiman pun tidak memberikan kata terimakasih kepadamu. Kamupun kecewa tetapi setidaknya kamu telah belajar untuk menjadi pembuat sistem operasi sederhana yang andal. Selamat!

_At last, the OS you painstakingly created was submitted to the lecturer under Budiman's name. You received no credit. Budiman didn't even thank you. You feel disappointed, but at least you've learned to become a reliable creator of simple operating systems. Congratulations!_


