#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// disini saya menggunakan strutur binary seacrh tree tanpa balanced

typedef struct treenode {
    char nama[37];
    int id, warisan;
    struct treenode *le, *ri;
} treenode;

treenode* create_node(int id, int warisan, char *nama) {
    treenode* newnode = (treenode*)malloc(sizeof(treenode));
    newnode->le = newnode->ri = NULL;
    strcpy(newnode->nama, nama);
    newnode->warisan = warisan;
    newnode->id = id;
    return newnode;
}

treenode* insert(treenode* root, int id, int warisan, char *nama) {
    if (!root) 
        return create_node(id, warisan, nama);
    if (id < root->id) 
        root->le = insert(root->le, id, warisan, nama);
    else if (id > root->id) 
        root->ri = insert(root->ri, id, warisan, nama);
    return root;
}

void simulasi_kematian(treenode* root, int id) {
    if (!root) return;

    if (id < root->id) {
        simulasi_kematian(root->le, id);
    } else if (id > root->id) {
        simulasi_kematian(root->ri, id);
    } else {
        if(!root->warisan) {
            printf("Anggota %s (ID %d) sudah meninggal dunia\n", root->nama, root->id);
            return;
        }

        printf("Anggota %s (ID %d) meninggal dunia dengan warisan %d juta\n", root->nama, root->id, root->warisan);
        int warisan = root->warisan;
        root->warisan = 0; 

        if (root->le) {
            int bagi_kiri = warisan * 60 / 100;
            printf("Anak kiri (%s) mendapat %d juta\n", root->le->nama, bagi_kiri);
            root->le->warisan += bagi_kiri;
            simulasi_kematian(root->le, root->le->id); 
        }

        if (root->ri) {
            int bagi_kanan = warisan * 40 / 100;
            printf("Anak kanan (%s) mendapat %d juta\n", root->ri->nama, bagi_kanan);
            root->ri->warisan += bagi_kanan;
            simulasi_kematian(root->ri, root->ri->id); 
        }

        if (!root->le && !root->ri) {
            printf("Tidak ada ahli waris. Warisan hangus.\n");
        }
    }
}

void in_order(treenode* root) {
    if (root) {
        in_order(root->le);
        printf("ID: %d | Nama: %s | Warisan: %d\n", root->id, root->nama, root->warisan);
        in_order(root->ri);
    }
}

int main() {
    treenode* root = NULL;
    int ch, id, warisan; 
    char nama[37];

    do {
        printf("Menu:\n");
        printf("1) Menambahkan anggota baru ke dalam pohon keluarga\n");
        printf("2) Menampilkan struktur pohon keluarga secara inorder\n");
        printf("3) Simulasikan kematian dan membagi hartanya\n");
        printf("4) Keluar dari program\n");
        printf("Input: "), scanf("%d", &ch);
        getchar();
        switch (ch) {
        case 1:
            printf("--> Masukan anggota keluarga <--\n");
            printf("Masukan id: "), scanf("%d", &id); 
            printf("Masukan nama: "), scanf("%s", nama);
            printf("Jumlah warisan: "), scanf("%d", &warisan);
            root = insert(root, id, warisan, nama);
            break;
        case 2:
            in_order(root);
            break;
        case 3:
            printf("Masukan id: "), scanf("%d", &id);
            simulasi_kematian(root, id);
            break;
        case 4:
            printf("Keluar program . . .\n");
            break;
        default:
            printf("Pilihan menu tidak valid  . . .\n");
            break;
        }
    } while(ch != 4);
}
