#include "MLL01.h"

void menuPlaylist(addressPengguna user) {
    int pilih = -1;
    while (pilih != 0) {
        tampilkanTabelPlaylistUser(user);
        if (user->currentRelasi != nullptr && user->currentRelasi->lagu != nullptr) {
            cetakGarisHorizontal(54);
            cout << "Lagu yang sedang diputar" << endl;
            cetakGarisHorizontal(54);
            cout << user->currentRelasi->lagu->info.judul << " - "
                 << user->currentRelasi->lagu->info.artis << " - ";
            formatDurasi(user->currentRelasi->lagu->info.durasiDetik);
            cout << endl;
            cetakGarisHorizontal(54);
        }

        cetakKotakJudul("MENU PLAYLIST - " + user->info.nama);
        cetakBarisMenu("1", "Putar Lagu Pertama", 54);
        cetakBarisMenu("2", "Pilih Lagu untuk Diputar", 54);
        cetakBarisMenu("3", "Next Lagu", 54);
        cetakBarisMenu("4", "Prev Lagu", 54);
        cetakBarisMenu("0", "Kembali ke Menu Pengguna", 54);
        cetakGarisHorizontal(54);
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            if (!putarLaguPertamaUser(user)) {
                cout << "Playlist kosong." << endl;
            }
        } else if (pilih == 2) {
            string idLagu;
            cout << "Masukkan ID Lagu: ";
            cin >> idLagu;
            if (!pilihLaguUntukDiputar(user, idLagu)) {
                cout << "Lagu tidak ditemukan di playlist." << endl;
            }
        } else if (pilih == 3) {
            if (user->currentRelasi == nullptr) {
                cout << "Belum ada lagu yang diputar. Pilih putar lagu pertama atau pilih lagu tertentu dulu." << endl;
            } else if (!nextLaguUser(user)) {
                cout << "Sudah di lagu terakhir." << endl;
            }
        } else if (pilih == 4) {
            if (user->currentRelasi == nullptr) {
                cout << "Belum ada lagu yang diputar. Pilih putar lagu pertama atau pilih lagu tertentu dulu." << endl;
            } else if (!prevLaguUser(user)) {
                cout << "Sudah di lagu pertama." << endl;
            }
        } else if (pilih == 0) {
            cout << "Kembali ke menu pengguna." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

void menuUser(ListParent &LP, ListChild &LC, addressPengguna user) {
    int pilih = -1;
    while (pilih != 0) {
        cetakKotakJudul("MENU PENGGUNA - " + user->info.nama);
        if (user->currentRelasi != nullptr && user->currentRelasi->lagu != nullptr) {
            cetakGarisHorizontal(54);
            cout << "Lagu yang sedang diputar" << endl;
            cetakGarisHorizontal(54);
            cout << user->currentRelasi->lagu->info.judul << " - "
                 << user->currentRelasi->lagu->info.artis << " - ";
            formatDurasi(user->currentRelasi->lagu->info.durasiDetik);
            cout << endl;
            cetakGarisHorizontal(54);
        }

        cetakBarisMenu("1", "Lihat Katalog Lagu", 54);
        cetakBarisMenu("2", "Tambah Lagu ke Playlist", 54);
        cetakBarisMenu("3", "Hapus Lagu dari Playlist", 54);
        cetakBarisMenu("4", "Masuk ke Playlist Saya", 54);
        cetakBarisMenu("0", "Logout", 54);
        cetakGarisHorizontal(54);
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            tampilkanTabelKatalogLagu(LC);
        } else if (pilih == 2) {
            string idLagu;
            tampilkanTabelKatalogLagu(LC);
            cout << "Masukkan ID Lagu: ";
            cin >> idLagu;
            if (tambahLaguKePlaylistUser(LC, user, idLagu)) {
                cout << "Lagu berhasil ditambahkan ke playlist." << endl;
            } else {
                cout << "Gagal menambahkan lagu (ID tidak ada atau sudah ada di playlist)." << endl;
            }
        } else if (pilih == 3) {
            string idLagu;
            tampilkanTabelPlaylistUser(user);
            cout << "Masukkan ID Lagu yang dihapus: ";
            cin >> idLagu;
            if (hapusLaguDariPlaylistUser(user, idLagu)) {
                cout << "Lagu berhasil dihapus dari playlist." << endl;
            } else {
                cout << "Lagu tidak ditemukan di playlist." << endl;
            }
        } else if (pilih == 4) {
            menuPlaylist(user);
        } else if (pilih == 0) {
            cout << "Logout berhasil." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

void menuAdmin(ListParent &LP, ListChild &LC) {
    int pilih = -1;
    while (pilih != 0) {
        cetakKotakJudul("MENU ADMIN");
        cetakBarisMenu("1", "Tambah Lagu ke Katalog", 54);
        cetakBarisMenu("2", "Hapus Lagu dari Katalog", 54);
        cetakBarisMenu("3", "Lihat Katalog Lagu", 54);
        cetakBarisMenu("4", "Lihat Semua Pengguna", 54);
        cetakBarisMenu("5", "Hapus Pengguna", 54);
        cetakBarisMenu("6", "Lihat Statistik Lengkap", 54);
        cetakBarisMenu("0", "Kembali ke Menu Utama", 54);
        cetakGarisHorizontal(54);
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            string idLagu, judul, artis;
            int durasi;
            cout << "ID Lagu      : ";
            cin >> idLagu;
            cout << "Judul Lagu   : ";
            cin >> judul;
            cout << "Artis        : ";
            cin >> artis;
            cout << "Durasi (detik): ";
            cin >> durasi;

            if (insertLagu(LC, idLagu, judul, artis, durasi) != nullptr) {
                cout << "Lagu berhasil ditambahkan." << endl;
            } else {
                cout << "Gagal menambahkan lagu (ID mungkin sudah ada)." << endl;
            }
        } else if (pilih == 2) {
            string idLagu;
            tampilkanTabelKatalogLagu(LC);
            cout << "Masukkan ID Lagu yang dihapus: ";
            cin >> idLagu;
            if (deleteLagu(LP, LC, idLagu)) {
                cout << "Lagu berhasil dihapus dari katalog dan playlist pengguna." << endl;
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }
        } else if (pilih == 3) {
            tampilkanTabelKatalogLagu(LC);
        } else if (pilih == 4) {
            tampilkanSemuaPengguna(LP);
        } else if (pilih == 5) {
            string email;
            tampilkanSemuaPengguna(LP);
            cout << "Masukkan Email pengguna yang dihapus: ";
            cin >> email;
            if (deletePengguna(LP, email)) {
                cout << "Pengguna dan seluruh relasinya berhasil dihapus." << endl;
            } else {
                cout << "Pengguna tidak ditemukan." << endl;
            }
        } else if (pilih == 6) {
            tampilkanStatistikLengkap(LP, LC);
        } else if (pilih == 0) {
            cout << "Kembali ke menu utama." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

int main() {
    ListParent LP;
    ListChild LC;
    createListParent(LP);
    createListChild(LC);
    seedDummyData(LP, LC);

    int pilih = -1;
    while (pilih != 0) {
        cetakKotakJudul("MUSIC STREAMING PLAYLIST SYSTEM");
        cetakBarisMenu("1", "Login Pengguna", 54);
        cetakBarisMenu("2", "Daftar Pengguna Baru", 54);
        cetakBarisMenu("3", "Menu Admin", 54);
        cetakBarisMenu("0", "Keluar", 54);
        cetakGarisHorizontal(54);
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            string email, password;
            cout << "Email    : ";
            cin >> email;
            cout << "Password : ";
            cin >> password;
            addressPengguna user = loginPengguna(LP, email, password);
            if (user != nullptr) {
                cout << "Login berhasil. Halo, " << user->info.nama << "!" << endl;
                menuUser(LP, LC, user);
            } else {
                cout << "Email atau password salah." << endl;
            }
        } else if (pilih == 2) {
            string nama, email, password;
            cout << "Nama     : ";
            cin >> nama;
            cout << "Email    : ";
            cin >> email;
            cout << "Password : ";
            cin >> password;

            if (insertPengguna(LP, nama, email, password) != nullptr) {
                cout << "Registrasi berhasil. Silakan login." << endl;
            } else {
                cout << "Registrasi gagal (email sudah terdaftar)." << endl;
            }
        } else if (pilih == 3) {
            menuAdmin(LP, LC);
        } else if (pilih == 0) {
            cout << "Program selesai." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}

