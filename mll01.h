#ifndef MLL01_H_INCLUDED
#define MLL01_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct NodeLagu *addressLagu;
typedef struct NodeRelasi *addressRelasi;
typedef struct NodePengguna *addressPengguna;

struct infoLagu {
    string idLagu;
    string judul;
    string artis;
    int durasiDetik;
    int totalPutarGlobal;
};

struct infoPengguna {
    string nama;
    string email;
    string password;
};

struct NodeLagu {
    infoLagu info;
    addressLagu next;
};

struct NodeRelasi {
    addressLagu lagu;
    int jumlahPutarUser;
    addressRelasi prev;
    addressRelasi next;
};

struct NodePengguna {
    infoPengguna info;
    addressPengguna next;
    addressRelasi firstRelasi;
    addressRelasi lastRelasi;
    addressRelasi currentRelasi;
};

struct ListParent {
    addressPengguna first;
    addressPengguna last;
};

struct ListChild {
    addressLagu first;
    addressLagu last;
};

void createListParent(ListParent &LP);
void createListChild(ListChild &LC);

addressLagu createNodeLagu(string id, string jdl, string art, int durasi);
addressRelasi createNodeRelasi(addressLagu targetLagu);
addressPengguna createNodePengguna(string nama, string mail, string pass);

void seedDummyData(ListParent &LP, ListChild &LC);

void hapusSemuaRelasiUser(addressPengguna user);
void lepasRelasiTertentu(addressPengguna user, addressRelasi target);

bool isEmailExists(ListParent LP, string email);
addressPengguna insertPengguna(ListParent &LP, string nama, string email, string password);
addressPengguna findPenggunaByEmail(ListParent LP, string email);
addressPengguna loginPengguna(ListParent LP, string email, string password);
bool deletePengguna(ListParent &LP, string email);
void tampilkanSemuaPengguna(ListParent LP);

bool isLaguIdExists(ListChild LC, string idLagu);
addressLagu insertLagu(ListChild &LC, string idLagu, string judul, string artis, int durasiDetik);
addressLagu findLaguById(ListChild LC, string idLagu);
bool deleteLagu(ListParent LP, ListChild &LC, string idLagu);
void tampilkanTabelKatalogLagu(ListChild LC);

addressRelasi findRelasiByLaguId(addressPengguna user, string idLagu);
bool tambahLaguKePlaylistUser(ListChild LC, addressPengguna user, string idLagu);
bool hapusLaguDariPlaylistUser(addressPengguna user, string idLagu);
void tampilkanTabelPlaylistUser(addressPengguna user);

bool putarLaguPertamaUser(addressPengguna user);
bool putarLaguAktif(addressPengguna user);
bool pilihLaguUntukDiputar(addressPengguna user, string idLagu);
bool nextLaguUser(addressPengguna user);
bool prevLaguUser(addressPengguna user);

void tampilkanStatistikLengkap(ListParent LP, ListChild LC);
void formatDurasi(int totalDetik);

void cetakKotakJudul(string judul);
void cetakGarisHorizontal(int lebar);
void cetakBarisKotak(string teks, int lebar);
void cetakBarisMenu(string kode, string label, int lebar);

#endif
