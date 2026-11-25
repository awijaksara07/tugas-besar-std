#include "MLL01.h"

void createListParent(ListParent &LP) {
    LP.first = nullptr;
    LP.last = nullptr;
}

void createListChild(ListChild &LC) {
    LC.first = nullptr;
    LC.last = nullptr;
}

addressLagu createNodeLagu(string id, string jdl, string art, int durasi) {
    addressLagu p = new NodeLagu;
    p->info.idLagu = id;
    p->info.judul = jdl;
    p->info.artis = art;
    p->info.durasiDetik = durasi;
    p->info.totalPutarGlobal = 0;
    p->next = nullptr;
    return p;
}

addressRelasi createNodeRelasi(addressLagu targetLagu) {
    addressRelasi p = new NodeRelasi;
    p->lagu = targetLagu;
    p->jumlahPutarUser = 0;
    p->prev = nullptr;
    p->next = nullptr;
    return p;
}

addressPengguna createNodePengguna(string nama, string mail, string pass) {
    addressPengguna p = new NodePengguna;
    p->info.nama = nama;
    p->info.email = mail;
    p->info.password = pass;
    p->next = nullptr;
    p->firstRelasi = nullptr;
    p->lastRelasi = nullptr;
    p->currentRelasi = nullptr;
    return p;
}

void seedDummyData(ListParent &LP, ListChild &LC) {
    addressPengguna u1 = insertPengguna(LP, "Aji", "aji@mail.com", "1234");
    addressPengguna u2 = insertPengguna(LP, "Nadia", "nadia@mail.com", "1234");
    insertPengguna(LP, "Raka", "raka@mail.com", "1234");

    addressLagu m1 = insertLagu(LC, "M01", "Hati-Hati", "Tulus", 242);
    addressLagu m2 = insertLagu(LC, "M02", "Komang", "Raim_Laode", 221);
    addressLagu m3 = insertLagu(LC, "M03", "Gala_Bunga", "Sal_Priadi", 261);
    insertLagu(LC, "M04", "Lantas", "Juicy_Luicy", 245);

    tambahLaguKePlaylistUser(LC, u1, "M01");
    tambahLaguKePlaylistUser(LC, u1, "M02");
    tambahLaguKePlaylistUser(LC, u1, "M03");

    tambahLaguKePlaylistUser(LC, u2, "M02");
    tambahLaguKePlaylistUser(LC, u2, "M04");

    if (u1 != nullptr && u1->firstRelasi != nullptr) {
        u1->firstRelasi->jumlahPutarUser = 3;
        if (m1 != nullptr) m1->info.totalPutarGlobal += 3;

        if (u1->firstRelasi->next != nullptr) {
            u1->firstRelasi->next->jumlahPutarUser = 5;
            if (m2 != nullptr) m2->info.totalPutarGlobal += 5;
        }
    }

    if (u2 != nullptr && u2->firstRelasi != nullptr) {
        u2->firstRelasi->jumlahPutarUser = 2;
        if (m2 != nullptr) m2->info.totalPutarGlobal += 2;
        if (m3 != nullptr) m3->info.totalPutarGlobal += 1;
    }
}

void hapusSemuaRelasiUser(addressPengguna user) {
    if (user == nullptr) return;
    addressRelasi curr = user->firstRelasi;
    while (curr != nullptr) {
        addressRelasi temp = curr;
        curr = curr->next;
        delete temp;
    }
    user->firstRelasi = nullptr;
    user->lastRelasi = nullptr;
    user->currentRelasi = nullptr;
}

void lepasRelasiTertentu(addressPengguna user, addressRelasi target) {
    if (user == nullptr || target == nullptr) return;

    if (user->currentRelasi == target) {
        user->currentRelasi = nullptr;
    }

    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        user->firstRelasi = target->next;
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    } else {
        user->lastRelasi = target->prev;
    }

    delete target;
}

bool isEmailExists(ListParent LP, string email) {
    addressPengguna curr = LP.first;
    while (curr != nullptr) {
        if (curr->info.email == email) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

addressPengguna insertPengguna(ListParent &LP, string nama, string email, string password) {
    if (isEmailExists(LP, email)) {
        return nullptr;
    }

    addressPengguna p = createNodePengguna(nama, email, password);
    if (LP.first == nullptr) {
        LP.first = p;
        LP.last = p;
    } else {
        LP.last->next = p;
        LP.last = p;
    }
    return p;
}

addressPengguna findPenggunaByEmail(ListParent LP, string email) {
    addressPengguna curr = LP.first;
    while (curr != nullptr) {
        if (curr->info.email == email) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

addressPengguna loginPengguna(ListParent LP, string email, string password) {
    addressPengguna curr = LP.first;
    while (curr != nullptr) {
        if (curr->info.email == email && curr->info.password == password) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool deletePengguna(ListParent &LP, string email) {
    addressPengguna curr = LP.first;
    addressPengguna prev = nullptr;

    while (curr != nullptr && curr->info.email != email) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false;

    hapusSemuaRelasiUser(curr);

    if (prev == nullptr) {
        LP.first = curr->next;
    } else {
        prev->next = curr->next;
    }

    if (curr == LP.last) {
        LP.last = prev;
    }

    delete curr;
    return true;
}

void tampilkanSemuaPengguna(ListParent LP) {
    cetakKotakJudul("DAFTAR PENGGUNA TERDAFTAR");
    if (LP.first == nullptr) {
        cetakBarisKotak("Belum ada pengguna terdaftar.", 54);
        cetakGarisHorizontal(54);
        return;
    }

    addressPengguna curr = LP.first;
    int no = 1;
    while (curr != nullptr) {
        int jumlahLagu = 0;
        addressRelasi r = curr->firstRelasi;
        while (r != nullptr) {
            jumlahLagu++;
            r = r->next;
        }
        cout << no << ". Nama: " << curr->info.nama
             << " | Email: " << curr->info.email
             << " | Jumlah Lagu: " << jumlahLagu << endl;
        no++;
        curr = curr->next;
    }
    cetakGarisHorizontal(54);
}

bool isLaguIdExists(ListChild LC, string idLagu) {
    addressLagu curr = LC.first;
    while (curr != nullptr) {
        if (curr->info.idLagu == idLagu) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

addressLagu insertLagu(ListChild &LC, string idLagu, string judul, string artis, int durasiDetik) {
    if (isLaguIdExists(LC, idLagu)) {
        return nullptr;
    }

    addressLagu p = createNodeLagu(idLagu, judul, artis, durasiDetik);
    if (LC.first == nullptr) {
        LC.first = p;
        LC.last = p;
    } else {
        LC.last->next = p;
        LC.last = p;
    }
    return p;
}

addressLagu findLaguById(ListChild LC, string idLagu) {
    addressLagu curr = LC.first;
    while (curr != nullptr) {
        if (curr->info.idLagu == idLagu) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool deleteLagu(ListParent LP, ListChild &LC, string idLagu) {
    addressLagu curr = LC.first;
    addressLagu prev = nullptr;

    while (curr != nullptr && curr->info.idLagu != idLagu) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false;

    addressPengguna p = LP.first;
    while (p != nullptr) {
        addressRelasi r = p->firstRelasi;
        while (r != nullptr) {
            addressRelasi nextR = r->next;
            if (r->lagu == curr) {
                lepasRelasiTertentu(p, r);
            }
            r = nextR;
        }
        p = p->next;
    }

    if (prev == nullptr) {
        LC.first = curr->next;
    } else {
        prev->next = curr->next;
    }

    if (curr == LC.last) {
        LC.last = prev;
    }

    delete curr;
    return true;
}

void tampilkanTabelKatalogLagu(ListChild LC) {
    cetakKotakJudul("KATALOG LAGU");
    if (LC.first == nullptr) {
        cetakBarisKotak("Katalog lagu masih kosong.", 54);
        cetakGarisHorizontal(54);
        return;
    }

    addressLagu curr = LC.first;
    int no = 1;
    while (curr != nullptr) {
        cout << no << ". [" << curr->info.idLagu << "] "
             << curr->info.judul << " - " << curr->info.artis
             << " | Durasi: ";
        formatDurasi(curr->info.durasiDetik);
        cout << " | Putar: " << curr->info.totalPutarGlobal << "x" << endl;
        no++;
        curr = curr->next;
    }
    cetakGarisHorizontal(54);
}

addressRelasi findRelasiByLaguId(addressPengguna user, string idLagu) {
    if (user == nullptr) return nullptr;
    addressRelasi curr = user->firstRelasi;
    while (curr != nullptr) {
        if (curr->lagu != nullptr && curr->lagu->info.idLagu == idLagu) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool tambahLaguKePlaylistUser(ListChild LC, addressPengguna user, string idLagu) {
    if (user == nullptr) return false;

    addressLagu target = findLaguById(LC, idLagu);
    if (target == nullptr) return false;

    if (findRelasiByLaguId(user, idLagu) != nullptr) {
        return false;
    }

    addressRelasi relBaru = createNodeRelasi(target);
    if (user->firstRelasi == nullptr) {
        user->firstRelasi = relBaru;
        user->lastRelasi = relBaru;
    } else {
        relBaru->prev = user->lastRelasi;
        user->lastRelasi->next = relBaru;
        user->lastRelasi = relBaru;
    }
    return true;
}

bool hapusLaguDariPlaylistUser(addressPengguna user, string idLagu) {
    if (user == nullptr) return false;
    addressRelasi target = findRelasiByLaguId(user, idLagu);
    if (target == nullptr) return false;

    lepasRelasiTertentu(user, target);
    return true;
}

void tampilkanTabelPlaylistUser(addressPengguna user) {
    if (user == nullptr) return;

    cetakKotakJudul("PLAYLIST MILIK " + user->info.nama);
    if (user->firstRelasi == nullptr) {
        cetakBarisKotak("Playlist masih kosong.", 54);
        cetakGarisHorizontal(54);
        return;
    }

    addressRelasi curr = user->firstRelasi;
    int no = 1;
    int totalDurasi = 0;
    while (curr != nullptr) {
        string statusPutar = (curr == user->currentRelasi) ? "[SEDANG DIPUTAR]" : "";
        cout << no << ". [" << curr->lagu->info.idLagu << "] "
             << curr->lagu->info.judul << " - " << curr->lagu->info.artis
             << " | Durasi: ";
        formatDurasi(curr->lagu->info.durasiDetik);
        cout << " " << statusPutar << endl;
        totalDurasi += curr->lagu->info.durasiDetik;
        no++;
        curr = curr->next;
    }
    cetakGarisHorizontal(54);
    cout << "Total Lagu: " << (no - 1) << " | Total Durasi: ";
    formatDurasi(totalDurasi);
    cout << endl;
    cetakGarisHorizontal(54);
}

bool putarLaguPertamaUser(addressPengguna user) {
    if (user == nullptr || user->firstRelasi == nullptr) {
        return false;
    }
    user->currentRelasi = user->firstRelasi;
    return putarLaguAktif(user);
}

bool putarLaguAktif(addressPengguna user) {
    if (user == nullptr || user->currentRelasi == nullptr || user->currentRelasi->lagu == nullptr) {
        return false;
    }

    user->currentRelasi->jumlahPutarUser++;
    user->currentRelasi->lagu->info.totalPutarGlobal++;

    cout << endl;
    cetakGarisHorizontal(54);
    cout << "Lagu yang sedang diputar" << endl;
    cetakGarisHorizontal(54);
    cout << user->currentRelasi->lagu->info.judul << " - "
         << user->currentRelasi->lagu->info.artis << " - ";
    formatDurasi(user->currentRelasi->lagu->info.durasiDetik);
    cout << endl;
    cetakGarisHorizontal(54);
    return true;
}

bool pilihLaguUntukDiputar(addressPengguna user, string idLagu) {
    if (user == nullptr) return false;
    addressRelasi target = findRelasiByLaguId(user, idLagu);
    if (target == nullptr) return false;

    user->currentRelasi = target;
    return putarLaguAktif(user);
}

bool nextLaguUser(addressPengguna user) {
    if (user == nullptr || user->currentRelasi == nullptr) return false;
    if (user->currentRelasi->next == nullptr) {
        return false;
    }
    user->currentRelasi = user->currentRelasi->next;
    return putarLaguAktif(user);
}

bool prevLaguUser(addressPengguna user) {
    if (user == nullptr || user->currentRelasi == nullptr) return false;
    if (user->currentRelasi->prev == nullptr) {
        return false;
    }
    user->currentRelasi = user->currentRelasi->prev;
    return putarLaguAktif(user);
}

void tampilkanStatistikLengkap(ListParent LP, ListChild LC) {
    cetakKotakJudul("STATISTIK");

    cout << "1. PLAYLIST & PUTAR PER PENGGUNA" << endl;
    cetakGarisHorizontal(54);
    if (LP.first == nullptr) {
        cout << "Belum ada data pengguna." << endl;
    } else {
        addressPengguna p = LP.first;
        while (p != nullptr) {
            int totalLagu = 0;
            int totalPutarUser = 0;
            addressRelasi r = p->firstRelasi;
            while (r != nullptr) {
                totalLagu++;
                totalPutarUser += r->jumlahPutarUser;
                r = r->next;
            }
            cout << p->info.nama << " (" << p->info.email << ") -> "
                 << totalLagu << " lagu | Total Putar: " << totalPutarUser << "x" << endl;

            r = p->firstRelasi;
            while (r != nullptr) {
                cout << "   - " << r->lagu->info.judul << " (" << r->lagu->info.artis << "): "
                     << r->jumlahPutarUser << "x" << endl;
                r = r->next;
            }
            p = p->next;
        }
    }

    cetakGarisHorizontal(54);
    cout << "2. STATISTIK GLOBAL LAGU" << endl;
    cetakGarisHorizontal(54);

    if (LC.first == nullptr) {
        cout << "Belum ada data lagu." << endl;
        cetakGarisHorizontal(54);
        return;
    }

    addressLagu c = LC.first;
    addressLagu palingBanyakDiputar = LC.first;
    while (c != nullptr) {
        cout << "[" << c->info.idLagu << "] " << c->info.judul << " - " << c->info.artis
             << " | Putar: " << c->info.totalPutarGlobal << "x" << endl;

        if (c->info.totalPutarGlobal > palingBanyakDiputar->info.totalPutarGlobal) {
            palingBanyakDiputar = c;
        }
        c = c->next;
    }
    cetakGarisHorizontal(54);
    cout << "Terpopuler: " << palingBanyakDiputar->info.judul
         << " (" << palingBanyakDiputar->info.totalPutarGlobal << "x)" << endl;
    cetakGarisHorizontal(54);
}

void formatDurasi(int totalDetik) {
    if (totalDetik < 0) {
        totalDetik = 0;
    }
    int menit = totalDetik / 60;
    int detik = totalDetik % 60;
    cout << menit << " menit " << detik << " detik";
}

void cetakKotakJudul(string judul) {
    cout << endl;
    cetakGarisHorizontal(54);
    cout << "| " << judul << endl;
    cetakGarisHorizontal(54);
}

void cetakGarisHorizontal(int lebar) {
    int i = 0;
    while (i < lebar) {
        cout << "-";
        i++;
    }
    cout << endl;
}

void cetakBarisKotak(string teks, int lebar) {
    cout << "| " << teks << endl;
}

void cetakBarisMenu(string kode, string label, int lebar) {
    cout << "| [" << kode << "] " << label << endl;
}
