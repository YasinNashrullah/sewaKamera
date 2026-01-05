#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// bagian ini menyimpan data dasar dan variabel global

// struktur untuk data kamera
struct DataKamera {
    string nama;
    int harga;
};

// struktur untuk data transaksi
struct Transaksi {
    int id;
    string namaPenyewa;
    string namaKamera;
    int hargaSewa;
    int lamaSewa;
    int status;
};

// variabel global
DataKamera daftarKamera[100];
Transaksi daftarTransaksi[100];

int jumlahKamera = 0;
int jumlahTransaksi = 0;
int totalPendapatan = 0;
int nomorTransaksi = 1;

// fungsi utilitas untuk pause program
void tekanEnter() {
    cout << "tekan enter untuk lanjut...";
    cin.get();
}


// fungsi inisialisasi data awal
void initKamera() {
    daftarKamera[jumlahKamera].nama = "Canon EOS 90D";
    daftarKamera[jumlahKamera].harga = 150000;
    jumlahKamera++;

    daftarKamera[jumlahKamera].nama = "Sony A6400";
    daftarKamera[jumlahKamera].harga = 180000;
    jumlahKamera++;

    daftarKamera[jumlahKamera].nama = "Nikon D7500";
    daftarKamera[jumlahKamera].harga = 160000;
    jumlahKamera++;
}

// fungsi login admin
void login() {
    string user, pass;

    while (true) {
        system("cls");
        cout << "login admin\n";
        cout << "username: ";
        cin >> user;
        cout << "password: ";
        cin >> pass;
        cin.ignore();

        if (user == "admin" && pass == "12") {
            break;
        } else {
            cout << "login gagal\n";
            tekanEnter();
        }
    }
}

// fungsi memproses sewa kamera
void prosesSewa() {
    system("cls");

    if (jumlahTransaksi >= 100) {
        cout << "penyimpanan penuh\n";
        tekanEnter();
        return;
    }

    string nama;
    int pilihan, lama, bayar;

    cout << "nama pelanggan: ";
    getline(cin, nama);

    cout << "\ndaftar kamera\n";
    for (int i = 0; i < jumlahKamera; i++) {
        cout << i + 1 << ". " << daftarKamera[i].nama
             << " - harga: " << daftarKamera[i].harga << " per hari\n";
    }

    cout << "\npilih kamera: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahKamera) {
        cout << "pilihan salah\n";
        cin.ignore();
        tekanEnter();
        return;
    }

    cout << "lama sewa (hari): ";
    cin >> lama;

    int total = daftarKamera[pilihan - 1].harga * lama;
    double diskon = 0;

    if (lama >= 7) diskon = 0.20;
    else if (lama >= 3) diskon = 0.10;

    int potongan = (int)(total * diskon);
    int totalBayar = total - potongan;

    cout << "\nstruk sewa\n";
    cout << "harga normal: rp " << total << endl;
    cout << "diskon: " << (int)(diskon * 100) << "%\n";
    cout << "potongan: rp " << potongan << endl;
    cout << "total bayar: rp " << totalBayar << endl;

    while (true) {
        cout << "uang bayar: rp ";
        cin >> bayar;
        if (bayar >= totalBayar) break;
        cout << "uang kurang\n";
    }

    cout << "kembalian: rp " << bayar - totalBayar << endl;

    daftarTransaksi[jumlahTransaksi].id = nomorTransaksi;
    daftarTransaksi[jumlahTransaksi].namaPenyewa = nama;
    daftarTransaksi[jumlahTransaksi].namaKamera = daftarKamera[pilihan - 1].nama;
    daftarTransaksi[jumlahTransaksi].hargaSewa = daftarKamera[pilihan - 1].harga;
    daftarTransaksi[jumlahTransaksi].lamaSewa = lama;
    daftarTransaksi[jumlahTransaksi].status = 1;

    nomorTransaksi++;
    jumlahTransaksi++;
    totalPendapatan += totalBayar;

    cin.ignore();
    tekanEnter();
}

// fungsi pengembalian dan denda
void prosesPengembalian() {
    system("cls");

    bool adaSewa = false;

    cout << "daftar sewa aktif\n";
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (daftarTransaksi[i].status == 1) {
            cout << i + 1 << ". " << daftarTransaksi[i].namaPenyewa
                 << " - kamera: " << daftarTransaksi[i].namaKamera << endl;
            adaSewa = true;
        }
    }

    if (!adaSewa) {
        cout << "tidak ada sewa aktif\n";
        tekanEnter();
        return;
    }

    int pilih, telat;
    cout << "\npilih nomor: ";
    cin >> pilih;

    if (pilih < 1 || pilih > jumlahTransaksi ||
        daftarTransaksi[pilih - 1].status == 0) {
        cout << "tidak valid\n";
        cin.ignore();
        tekanEnter();
        return;
    }

    cout << "telat (hari): ";
    cin >> telat;

    if (telat > 0) {
        int denda = telat * 50000;
        cout << "denda: rp " << denda << endl;
        totalPendapatan += denda;
    }

    daftarTransaksi[pilih - 1].status = 0;
    cout << "kamera kembali\n";

    cin.ignore();
    tekanEnter();
}

// fungsi sorting harga kamera
void sortKamera() {
    system("cls");

    int tipe;
    cout << "1. termurah ke termahal\n";
    cout << "2. termahal ke termurah\n";
    cout << "pilih: ";
    cin >> tipe;
    cin.ignore();

    for (int i = 0; i < jumlahKamera - 1; i++) {
        for (int j = 0; j < jumlahKamera - i - 1; j++) {
            bool tukar = false;

            if (tipe == 1 && daftarKamera[j].harga > daftarKamera[j + 1].harga)
                tukar = true;

            if (tipe == 2 && daftarKamera[j].harga < daftarKamera[j + 1].harga)
                tukar = true;

            if (tukar) {
                DataKamera temp = daftarKamera[j];
                daftarKamera[j] = daftarKamera[j + 1];
                daftarKamera[j + 1] = temp;
            }
        }
    }

    cout << "\nhasil urut\n";
    for (int k = 0; k < jumlahKamera; k++) {
        cout << daftarKamera[k].nama
             << " - harga: " << daftarKamera[k].harga << endl;
    }

    tekanEnter();
}

// fungsi laporan pendapatan
void laporanPendapatan() {
    system("cls");
    cout << "laporan pendapatan\n";
    cout << "total transaksi: " << nomorTransaksi - 1 << endl;
    cout << "total pendapatan: rp " << totalPendapatan << endl;
    tekanEnter();
}

// fungsi logout
void logout() {
    system("cls");
    cout << "log out berhasil\n";
    tekanEnter();
    login();
}

// fungsi menu utama
void tampilkanMenu() {
    int menu;

    while (true) {
        system("cls");

        cout << "rental kamera digital\n";
        cout << "1. sewa kamera\n";
        cout << "2. pengembalian kamera\n";
        cout << "3. urutkan harga kamera\n";
        cout << "4. laporan pendapatan\n";
        cout << "5. logout\n";
        cout << "pilih menu: ";
        cin >> menu;
        cin.ignore();

        switch (menu) {
            case 1: prosesSewa(); break;
            case 2: prosesPengembalian(); break;
            case 3: sortKamera(); break;
            case 4: laporanPendapatan(); break;
            case 5: logout(); break;
            default:
                cout << "menu tidak ada\n";
                tekanEnter();
        }
    }
}

// program utama
int main() {
    initKamera();
    login();
    tampilkanMenu();
    return 0;
}