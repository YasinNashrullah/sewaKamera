#include <iostream>
#include <string>
#include <iomanip>
#include <limits> 

using namespace std;

// konstanta untuk batasan array
const int max_kamera = 50;
const int max_transaksi = 100;
const int max_pelanggan = 50;

// struct data utama

// struct untuk inventaris kamera
struct Kamera {
    string id;
    string merek;
    string model;
    double harga_sewa_per_hari;
    bool tersedia; // status ketersediaan
};

// struct untuk data pelanggan
struct Pelanggan {
    string id;
    string nama;
    string telepon;
};

// struct untuk transaksi peminjaman
struct Transaksi {
    string id;
    string id_kamera;
    string id_pelanggan;
    int tanggal_sewa; 
    int tanggal_rencana_kembali;
    int tanggal_aktual_kembali;
    double total_biaya;
    bool aktif;
};

// array global sebagai database sederhana

Kamera inventaris[max_kamera];
int jumlahKamera = 0;

Pelanggan daftarPelanggan[max_pelanggan];
int jumlahPelanggan = 0;

Transaksi daftarTransaksi[max_transaksi];
int jumlahTransaksi = 0;

// fungsi utility bantuan

// fungsi untuk mengabaikan input yang tersisa di buffer
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// fungsi untuk menjeda program dan memberi ruang visual
void jedaVisual() {
    cout << "\n\n tekan enter untuk melanjutkan...";
    clearInputBuffer();
    // mencetak banyak baris kosong untuk mendorong output lama ke atas
    for (int i = 0; i < 30; ++i) cout << "\n"; 
}

// fungsi untuk mencari indeks kamera
int cariIndeksKamera(string id) {
    for (int i = 0; i < jumlahKamera; i++) {
        if (inventaris[i].id == id) {
            return i;
        }
    }
    return -1; 
}

// fungsi untuk mencari indeks pelanggan
int cariIndeksPelanggan(string id) {
    for (int i = 0; i < jumlahPelanggan; i++) {
        if (daftarPelanggan[i].id == id) {
            return i;
        }
    }
    return -1; 
}

// fungsi untuk mencari indeks transaksi
int cariIndeksTransaksi(string id) {
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (daftarTransaksi[i].id == id) {
            return i;
        }
    }
    return -1;
}

// fungsi sorting bubble sort berdasarkan harga sewa termurah
void urutkanKameraBerdasarkanHarga() {
    for (int i = 0; i < jumlahKamera - 1; i++) {
        for (int j = 0; j < jumlahKamera - i - 1; j++) {
            if (inventaris[j].harga_sewa_per_hari > inventaris[j + 1].harga_sewa_per_hari) {
                // tukar posisi
                Kamera temp = inventaris[j];
                inventaris[j] = inventaris[j + 1];
                inventaris[j + 1] = temp;
            }
        }
    }
    cout << "\n inventaris berhasil diurutkan berdasarkan harga sewa termurah." << endl;
    jedaVisual();
}

// modul manajemen inventaris

// tambah kamera
void tambahKamera() {
    if (jumlahKamera >= max_kamera) {
        cout << "\n kapasitas inventaris penuh!" << endl;
        return;
    }

    Kamera baru;
    cout << "\n--- tambah kamera baru ---" << endl;
    cout << "id kamera (unik): ";
    cin >> baru.id;

    if (cariIndeksKamera(baru.id) != -1) {
        cout << " id kamera sudah ada!" << endl;
        jedaVisual();
        return;
    }

    cout << "merek: ";
    cin >> baru.merek;
    cout << "model: ";
    cin >> baru.model;
    cout << "harga sewa per hari (rp): ";
    cin >> baru.harga_sewa_per_hari;

    baru.tersedia = true;

    inventaris[jumlahKamera] = baru;
    jumlahKamera++;

    cout << "\n kamera " << baru.model << " berhasil ditambahkan!" << endl;
    clearInputBuffer();
    jedaVisual();
}

// hapus kamera
void hapusKamera() {
    string id_hapus;
    cout << "\n--- hapus kamera ---" << endl;
    cout << "masukkan id kamera yang akan dihapus: ";
    cin >> id_hapus;

    int indeks = cariIndeksKamera(id_hapus);

    if (indeks == -1) {
        cout << " kamera dengan id " << id_hapus << " tidak ditemukan." << endl;
        jedaVisual();
        return;
    }

    // pengecekan ketersediaan
    if (!inventaris[indeks].tersedia) {
        cout << " kamera sedang dipinjam dan tidak bisa dihapus." << endl;
        jedaVisual();
        return;
    }

    // geser elemen array
    for (int i = indeks; i < jumlahKamera - 1; i++) {
        inventaris[i] = inventaris[i + 1];
    }
    jumlahKamera--;
    cout << "\n kamera id " << id_hapus << " berhasil dihapus." << endl;
    clearInputBuffer();
    jedaVisual();
}

// tampilkan inventaris
void tampilkanInventaris(bool hanyaTersedia = false) {
    cout << "\n--- daftar inventaris kamera ---" << endl;
    if (jumlahKamera == 0) {
        cout << "inventaris kosong." << endl;
        jedaVisual();
        return;
    }

    // header tabel
    cout << left << setw(10) << "id"
         << setw(15) << "merek"
         << setw(20) << "model"
         << right << setw(15) << "harga/hari"
         << setw(15) << "status" << endl;
    cout << string(75, '-') << endl;

    // data tabel
    for (int i = 0; i < jumlahKamera; i++) {
        if (hanyaTersedia && !inventaris[i].tersedia) {
            continue;
        }
        cout << left << setw(10) << inventaris[i].id
             << setw(15) << inventaris[i].merek
             << setw(20) << inventaris[i].model
             << right << setw(15) << fixed << setprecision(0) << inventaris[i].harga_sewa_per_hari
             << setw(15) << (inventaris[i].tersedia ? "tersedia" : "disewa") << endl;
    }
    cout << string(75, '-') << endl;
    jedaVisual();
}

// modul manajemen pelanggan

// tambah pelanggan
void tambahPelanggan() {
    if (jumlahPelanggan >= max_pelanggan) {
        cout << "\n kapasitas data pelanggan penuh!" << endl;
        jedaVisual();
        return;
    }

    Pelanggan baru;
    cout << "\n--- tambah pelanggan baru ---" << endl;
    cout << "id pelanggan (unik): ";
    cin >> baru.id;

    if (cariIndeksPelanggan(baru.id) != -1) {
        cout << " id pelanggan sudah ada!" << endl;
        jedaVisual();
        return;
    }

    cout << "nama: ";
    clearInputBuffer();
    getline(cin, baru.nama);
    cout << "nomor telepon: ";
    cin >> baru.telepon;

    daftarPelanggan[jumlahPelanggan] = baru;
    jumlahPelanggan++;

    cout << "\n pelanggan " << baru.nama << " berhasil ditambahkan!" << endl;
    jedaVisual();
}

// modul manajemen transaksi

// proses penyewaan
void prosesSewa() {
    if (jumlahKamera == 0) {
        cout << "\n inventaris kosong. tidak dapat melakukan penyewaan." << endl;
        jedaVisual();
        return;
    }
    if (jumlahPelanggan == 0) {
        cout << "\n data pelanggan kosong. tambahkan pelanggan terlebih dahulu." << endl;
        jedaVisual();
        return;
    }
    if (jumlahTransaksi >= max_transaksi) {
        cout << "\n batas transaksi tercapai!" << endl;
        jedaVisual();
        return;
    }

    Transaksi baru;
    string id_kamera_sewa, id_pelanggan_sewa;

    cout << "\n--- proses penyewaan ---" << endl;
    cout << "id transaksi baru: ";
    cin >> baru.id;

    cout << "id pelanggan: ";
    cin >> id_pelanggan_sewa;
    int indeksPelanggan = cariIndeksPelanggan(id_pelanggan_sewa);
    if (indeksPelanggan == -1) {
        cout << " pelanggan tidak ditemukan. mohon daftarkan pelanggan terlebih dahulu." << endl;
        jedaVisual();
        return;
    }
    baru.id_pelanggan = id_pelanggan_sewa;

    tampilkanInventaris(true);
    cout << "id kamera yang disewa: ";
    cin >> id_kamera_sewa;
    int indeksKamera = cariIndeksKamera(id_kamera_sewa);

    if (indeksKamera == -1 || !inventaris[indeksKamera].tersedia) {
        cout << " kamera tidak ditemukan atau sedang tidak tersedia." << endl;
        jedaVisual();
        return;
    }
    baru.id_kamera = id_kamera_sewa;

    cout << "tanggal sewa (1-30): ";
    cin >> baru.tanggal_sewa;
    cout << "tanggal rencana pengembalian (1-30): ";
    cin >> baru.tanggal_rencana_kembali;

    if (baru.tanggal_rencana_kembali < baru.tanggal_sewa) {
         cout << " tanggal rencana kembali harus setelah tanggal sewa." << endl;
         jedaVisual();
        return;
    }

    // hitung hari sewa
    int totalHari = baru.tanggal_rencana_kembali - baru.tanggal_sewa;
    double estimasiBiaya = totalHari * inventaris[indeksKamera].harga_sewa_per_hari;

    cout << "\n estimasi biaya sewa (" << totalHari << " hari): rp " << fixed << setprecision(0) << estimasiBiaya << endl;
    
    // update status kamera
    inventaris[indeksKamera].tersedia = false;

    // simpan transaksi
    baru.aktif = true;
    baru.total_biaya = 0; // biaya akhir dihitung saat pengembalian
    daftarTransaksi[jumlahTransaksi] = baru;
    jumlahTransaksi++;

    cout << "\n penyewaan berhasil dicatat!" << endl;
    clearInputBuffer();
    jedaVisual();
}

// proses pengembalian dan cetak nota
void prosesKembali() {
    string id_transaksi;
    cout << "\n--- proses pengembalian ---" << endl;
    cout << "masukkan id transaksi: ";
    cin >> id_transaksi;

    int indeksTransaksi = cariIndeksTransaksi(id_transaksi);

    if (indeksTransaksi == -1 || !daftarTransaksi[indeksTransaksi].aktif) {
        cout << " transaksi tidak ditemukan atau sudah selesai." << endl;
        jedaVisual();
        return;
    }

    int tgl_aktual;
    cout << "tanggal pengembalian aktual (1-30): ";
    cin >> tgl_aktual;

    int tgl_rencana = daftarTransaksi[indeksTransaksi].tanggal_rencana_kembali;
    int tgl_sewa = daftarTransaksi[indeksTransaksi].tanggal_sewa;
    
    int indeksKamera = cariIndeksKamera(daftarTransaksi[indeksTransaksi].id_kamera);
    int indeksPelanggan = cariIndeksPelanggan(daftarTransaksi[indeksTransaksi].id_pelanggan);

    double harga_sewa = inventaris[indeksKamera].harga_sewa_per_hari;

    // perhitungan biaya
    int totalHariSewa = tgl_rencana - tgl_sewa;
    double biayaSewaPokok = totalHariSewa * harga_sewa;
    double denda = 0;
    int hariTerlambat = 0;

    // perhitungan denda
    if (tgl_aktual > tgl_rencana) {
        hariTerlambat = tgl_aktual - tgl_rencana;
        double dendaPerHari = 0.10 * harga_sewa;
        denda = hariTerlambat * dendaPerHari;
    }

    double totalBiayaAkhir = biayaSewaPokok + denda;

    // update data transaksi
    daftarTransaksi[indeksTransaksi].tanggal_aktual_kembali = tgl_aktual;
    daftarTransaksi[indeksTransaksi].total_biaya = totalBiayaAkhir;
    daftarTransaksi[indeksTransaksi].aktif = false; // transaksi selesai

    // update status kamera
    inventaris[indeksKamera].tersedia = true;

    // --- cetak nota pembayaran ---
    cout << "\n==========================================" << endl;
    cout << left << setw(40) << "NOTA PEMBAYARAN RENTAL KAMERA" << endl;
    cout << string(42, '-') << endl;
    
    // detail transaksi dan pelanggan
    cout << left << setw(15) << "transaksi id" << ": " << daftarTransaksi[indeksTransaksi].id << endl;
    cout << left << setw(15) << "nama pelanggan" << ": " << daftarPelanggan[indeksPelanggan].nama << endl;
    cout << string(42, '-') << endl;

    // detail kamera
    cout << left << setw(15) << "kamera" << ": " << inventaris[indeksKamera].merek << " " << inventaris[indeksKamera].model << endl;
    cout << left << setw(15) << "harga sewa" << ": rp " << fixed << setprecision(0) << harga_sewa << " / hari" << endl;
    cout << string(42, '-') << endl;

    // rincian perhitungan tanggal
    cout << left << setw(25) << "tgl sewa" << ": " << daftarTransaksi[indeksTransaksi].tanggal_sewa << endl;
    cout << left << setw(25) << "tgl rencana kembali" << ": " << daftarTransaksi[indeksTransaksi].tanggal_rencana_kembali << endl;
    cout << left << setw(25) << "tgl aktual kembali" << ": " << daftarTransaksi[indeksTransaksi].tanggal_aktual_kembali << endl;
    cout << left << setw(25) << "total hari sewa" << ": " << totalHariSewa << " hari" << endl;
    cout << string(42, '-') << endl;

    // rincian biaya
    cout << left << setw(25) << "biaya sewa pokok" << right << "rp " << setw(15) << fixed << setprecision(0) << biayaSewaPokok << endl;
    
    if (denda > 0) {
        cout << left << setw(25) << "denda (" << hariTerlambat << " hari)" << right << "rp " << setw(15) << fixed << setprecision(0) << denda << endl;
    } else {
         cout << left << setw(25) << "denda" << right << "rp " << setw(15) << "0" << endl;
    }

    cout << string(42, '=') << endl;
    cout << left << setw(25) << "total biaya akhir" << right << "rp " << setw(15) << fixed << setprecision(0) << totalBiayaAkhir << endl;
    cout << "==========================================" << endl;

    cout << "\n kamera berhasil dikembalikan dan nota telah dicetak." << endl;
    clearInputBuffer();
    jedaVisual();
}

// modul pelaporan

// tampilkan laporan transaksi
void tampilkanLaporanTransaksi(bool aktifSaja = true) {
    string judul = aktifSaja ? "aktif" : "selesai";
    cout << "\n--- laporan transaksi " << judul << " ---" << endl;

    // header tabel dengan label yang jelas
    cout << left << setw(10) << "id trans"
         << setw(10) << "kamera"
         << setw(10) << "pelanggan"
         << setw(8) << "tgl sewa"
         << setw(8) << "tgl rencana"
         << setw(8) << "tgl aktual"
         << right << setw(15) << "total biaya"
         << setw(10) << "status" << endl;
    cout << string(83, '-') << endl; 

    bool ditemukan = false;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (daftarTransaksi[i].aktif == aktifSaja) {
            ditemukan = true;
            // jika transaksi aktif, tgl aktual ditampilkan "-"
            string tgl_a = daftarTransaksi[i].aktif ? "-" : to_string(daftarTransaksi[i].tanggal_aktual_kembali);

            cout << left << setw(10) << daftarTransaksi[i].id
                 << setw(10) << daftarTransaksi[i].id_kamera
                 << setw(10) << daftarTransaksi[i].id_pelanggan
                 << setw(8) << daftarTransaksi[i].tanggal_sewa
                 << setw(8) << daftarTransaksi[i].tanggal_rencana_kembali
                 << setw(8) << tgl_a
                 << right << setw(15) << fixed << setprecision(0) << daftarTransaksi[i].total_biaya
                 << setw(10) << (daftarTransaksi[i].aktif ? "aktif" : "selesai") << endl;
        }
    }
    if (!ditemukan) {
        cout << "tidak ada transaksi " << judul << "." << endl;
    }
    cout << string(83, '-') << endl;
    jedaVisual();
}

// menu navigasi

void tampilkanMenu() {
    cout << "\n==========================================" << endl;
    cout << "  sistem manajemen rental kamera (c++)" << endl;
    cout << "==========================================" << endl;
    cout << "1. manajemen inventaris kamera" << endl;
    cout << "2. manajemen data pelanggan" << endl;
    cout << "3. proses penyewaan" << endl;
    cout << "4. proses pengembalian & nota" << endl;
    cout << "5. laporan dan utilitas" << endl;
    cout << "0. keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "pilih menu (0-5): ";
}

void menuInventaris() {
    int pilihan;
    do {
        cout << "\n--- menu inventaris ---" << endl;
        cout << "1. tambah kamera" << endl;
        cout << "2. hapus kamera" << endl;
        cout << "3. tampilkan semua inventaris" << endl;
        cout << "4. tampilkan kamera tersedia saja" << endl;
        cout << "5. urutkan berdasarkan harga sewa" << endl;
        cout << "0. kembali ke menu utama" << endl;
        cout << "pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahKamera(); break;
            case 2: hapusKamera(); break;
            case 3: tampilkanInventaris(false); break;
            case 4: tampilkanInventaris(true); break;
            case 5: urutkanKameraBerdasarkanHarga(); break;
            case 0: break;
            default: cout << "pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);
}

void menuLaporan() {
    int pilihan;
    do {
        cout << "\n--- menu laporan & utilitas ---" << endl;
        cout << "1. laporan transaksi aktif" << endl;
        cout << "2. laporan transaksi selesai" << endl;
        cout << "0. kembali ke menu utama" << endl;
        cout << "pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilkanLaporanTransaksi(true); break;
            case 2: tampilkanLaporanTransaksi(false); break;
            case 0: break;
            default: cout << "pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);
}

// fungsi utama

int main() {
    // data dummy untuk mempermudah testing
    inventaris[0] = {"C001", "Canon", "EOS 80D", 150000.0, true};
    inventaris[1] = {"S002", "Sony", "A6400", 200000.0, true};
    inventaris[2] = {"N003", "Nikon", "D7500", 180000.0, true};
    jumlahKamera = 3;

    daftarPelanggan[0] = {"P001", "budi santoso", "08123456789"};
    daftarPelanggan[1] = {"P002", "rina dewi", "08987654321"};
    jumlahPelanggan = 2;

    int pilihan;
    do {
        tampilkanMenu();
        if (!(cin >> pilihan)) {
            cout << "input tidak valid. silakan masukkan angka." << endl;
            cin.clear();
            clearInputBuffer();
            pilihan = -1;
            continue;
        }

        switch (pilihan) {
            case 1: menuInventaris(); break;
            case 2: tambahPelanggan(); break;
            case 3: prosesSewa(); break;
            case 4: prosesKembali(); break;
            case 5: menuLaporan(); break;
            case 0: cout << "\nterima kasih, program selesai." << endl; break;
            default: cout << "pilihan tidak valid. silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}