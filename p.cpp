#include <iostream>
#include <string>
#include <iomanip> // Untuk merapikan tampilan tabel (setw)
#include <cstdlib> // Untuk system("cls")

using namespace std;

// ==========================================
// 1. STRUKTUR DATA & KONSTANTA
// ==========================================

const int MAX_KAMERA = 100;
const int MAX_PELANGGAN = 100;
const int MAX_TRANSAKSI = 100;

struct Kamera {
    string id;
    string merek;
    string model;
    double hargaSewa;
    string status; // "Tersedia" atau "Disewa"
};

struct Pelanggan {
    string id;
    string nama;
    string noHP;
};

struct Transaksi {
    string idTransaksi;
    string idPelanggan;
    string idKamera;
    int tglSewa;
    int tglRencanaKembali;
    int tglAktualKembali;
    double totalBiaya;
    string status; // "Aktif" atau "Selesai"
};

// ==========================================
// VARIABEL GLOBAL (DATABASE SEDERHANA)
// ==========================================

Kamera daftarKamera[MAX_KAMERA];
int jumlahKamera = 0;

Pelanggan daftarPelanggan[MAX_PELANGGAN];
int jumlahPelanggan = 0;

Transaksi daftarTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

// ==========================================
// FUNGSI BANTUAN (UTILITY)
// ==========================================

void bersihkanLayar() {
    // Gunakan "cls" untuk Windows, "clear" untuk Linux/Mac
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// ==========================================
// 2. MODUL MANAJEMEN INVENTARIS (KAMERA)
// ==========================================

// Cek apakah ID Kamera sudah ada
bool cekIdKamera(string id) {
    for (int i = 0; i < jumlahKamera; i++) {
        if (daftarKamera[i].id == id) {
            return true;
        }
    }
    return false;
}

void tambahKamera() {
    bersihkanLayar();
    cout << "=== TAMBAH DATA KAMERA ===\n";
    
    if (jumlahKamera >= MAX_KAMERA) {
        cout << "Penyimpanan penuh!\n";
        return;
    }

    Kamera kBaru;
    cout << "Masukkan ID Kamera (Unik): ";
    cin >> kBaru.id;

    if (cekIdKamera(kBaru.id)) {
        cout << "Error: ID Kamera sudah ada!\n";
        return;
    }

    cout << "Masukkan Merek: ";
    cin.ignore();
    getline(cin, kBaru.merek);
    cout << "Masukkan Model: ";
    getline(cin, kBaru.model);
    cout << "Harga Sewa per Hari (Rp): ";
    cin >> kBaru.hargaSewa;
    kBaru.status = "Tersedia";

    daftarKamera[jumlahKamera] = kBaru;
    jumlahKamera++;

    cout << "Data kamera berhasil ditambahkan!\n";
}

void hapusKamera() {
    bersihkanLayar();
    cout << "=== HAPUS DATA KAMERA ===\n";
    string id;
    cout << "Masukkan ID Kamera yang akan dihapus: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < jumlahKamera; i++) {
        if (daftarKamera[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Kamera tidak ditemukan.\n";
    } else {
        if (daftarKamera[index].status == "Disewa") {
            cout << "Gagal: Kamera sedang disewa, tidak bisa dihapus.\n";
        } else {
            // Geser elemen array untuk menghapus
            for (int i = index; i < jumlahKamera - 1; i++) {
                daftarKamera[i] = daftarKamera[i + 1];
            }
            jumlahKamera--;
            cout << "Kamera berhasil dihapus.\n";
        }
    }
}

// Algoritma Bubble Sort untuk mengurutkan berdasarkan harga termurah
void urutkanKamera() {
    for (int i = 0; i < jumlahKamera - 1; i++) {
        for (int j = 0; j < jumlahKamera - i - 1; j++) {
            if (daftarKamera[j].hargaSewa > daftarKamera[j + 1].hargaSewa) {
                // Tukar posisi
                Kamera temp = daftarKamera[j];
                daftarKamera[j] = daftarKamera[j + 1];
                daftarKamera[j + 1] = temp;
            }
        }
    }
    cout << "Inventaris berhasil diurutkan berdasarkan harga termurah.\n";
}

void tampilkanKamera(bool hanyaTersedia) {
    bersihkanLayar();
    if (hanyaTersedia) cout << "=== DAFTAR KAMERA TERSEDIA ===\n";
    else cout << "=== SEMUA INVENTARIS KAMERA ===\n";

    cout << left << setw(10) << "ID" 
         << setw(15) << "Merek" 
         << setw(15) << "Model" 
         << setw(15) << "Harga/Hari" 
         << setw(15) << "Status" << endl;
    cout << "------------------------------------------------------------------\n";

    bool adaData = false;
    for (int i = 0; i < jumlahKamera; i++) {
        if (hanyaTersedia && daftarKamera[i].status == "Disewa") {
            continue; // Lewati jika kita hanya ingin yang tersedia
        }
        
        cout << left << setw(10) << daftarKamera[i].id 
             << setw(15) << daftarKamera[i].merek 
             << setw(15) << daftarKamera[i].model 
             << setw(15) << (long)daftarKamera[i].hargaSewa 
             << setw(15) << daftarKamera[i].status << endl;
        adaData = true;
    }

    if (!adaData) cout << "Tidak ada data untuk ditampilkan.\n";
}

// ==========================================
// FUNGSI TAMBAHAN: PELANGGAN
// ==========================================
void tambahPelanggan() {
    bersihkanLayar();
    cout << "=== TAMBAH PELANGGAN ===\n";
    if (jumlahPelanggan >= MAX_PELANGGAN) {
        cout << "Database pelanggan penuh.\n";
        return;
    }
    
    Pelanggan p;
    cout << "ID Pelanggan: "; cin >> p.id;
    cout << "Nama: "; cin.ignore(); getline(cin, p.nama);
    cout << "No HP: "; cin >> p.noHP;
    
    daftarPelanggan[jumlahPelanggan] = p;
    jumlahPelanggan++;
    cout << "Pelanggan berhasil ditambahkan.\n";
}

// ==========================================
// 3. MODUL MANAJEMEN TRANSAKSI
// ==========================================

void prosesPenyewaan() {
    bersihkanLayar();
    cout << "=== PROSES PENYEWAAN ===\n";

    string idPel, idKam;
    
    // 1. Validasi Pelanggan
    cout << "Masukkan ID Pelanggan: ";
    cin >> idPel;
    bool pelFound = false;
    for(int i=0; i<jumlahPelanggan; i++) {
        if(daftarPelanggan[i].id == idPel) pelFound = true;
    }
    if(!pelFound) {
        cout << "Pelanggan tidak ditemukan! Tambahkan pelanggan dulu.\n";
        return;
    }

    // 2. Validasi Kamera
    cout << "Masukkan ID Kamera: ";
    cin >> idKam;
    int idxKam = -1;
    for(int i=0; i<jumlahKamera; i++) {
        if(daftarKamera[i].id == idKam) {
            idxKam = i;
            break;
        }
    }

    if(idxKam == -1) {
        cout << "Kamera tidak ditemukan!\n";
        return;
    }
    if(daftarKamera[idxKam].status == "Disewa") {
        cout << "Kamera sedang tidak tersedia!\n";
        return;
    }

    // 3. Input Data Sewa
    Transaksi t;
    cout << "ID Transaksi: "; cin >> t.idTransaksi;
    t.idPelanggan = idPel;
    t.idKamera = idKam;
    
    cout << "Tanggal Sewa (1-30): "; cin >> t.tglSewa;
    cout << "Rencana Tanggal Kembali (1-30): "; cin >> t.tglRencanaKembali;
    
    if(t.tglRencanaKembali <= t.tglSewa) {
        cout << "Tanggal kembali tidak valid!\n";
        return;
    }

    t.tglAktualKembali = 0;
    t.totalBiaya = 0;
    t.status = "Aktif";

    // Simpan Transaksi
    daftarTransaksi[jumlahTransaksi] = t;
    jumlahTransaksi++;

    // Update Status Kamera
    daftarKamera[idxKam].status = "Disewa";

    cout << "Transaksi berhasil dibuat! Kamera sekarang berstatus Disewa.\n";
}

void prosesPengembalian() {
    bersihkanLayar();
    cout << "=== PROSES PENGEMBALIAN & KASIR ===\n";
    
    string idTrans;
    cout << "Masukkan ID Transaksi: ";
    cin >> idTrans;

    int idxTrans = -1;
    for(int i=0; i<jumlahTransaksi; i++) {
        if(daftarTransaksi[i].idTransaksi == idTrans && daftarTransaksi[i].status == "Aktif") {
            idxTrans = i;
            break;
        }
    }

    if(idxTrans == -1) {
        cout << "Transaksi tidak ditemukan atau sudah selesai.\n";
        return;
    }

    // Ambil data transaksi
    Transaksi &t = daftarTransaksi[idxTrans]; // Menggunakan referensi agar update langsung tersimpan
    
    // Cari data kamera untuk harga
    int idxKam = -1;
    for(int i=0; i<jumlahKamera; i++) {
        if(daftarKamera[i].id == t.idKamera) {
            idxKam = i;
            break;
        }
    }
    double hargaPerHari = daftarKamera[idxKam].hargaSewa;

    // Input Pengembalian
    cout << "Tanggal Rencana Kembali: " << t.tglRencanaKembali << endl;
    cout << "Masukkan Tanggal Aktual Kembali (1-30): ";
    cin >> t.tglAktualKembali;

    // Hitung Biaya
    int durasiRencana = t.tglRencanaKembali - t.tglSewa;
    double biayaPokok = durasiRencana * hargaPerHari;
    
    int terlambat = t.tglAktualKembali - t.tglRencanaKembali;
    double denda = 0;

    if (terlambat > 0) {
        // Denda 10% dari harga sewa per hari dikali hari keterlambatan
        denda = terlambat * (hargaPerHari * 0.10);
    } else {
        terlambat = 0;
    }

    t.totalBiaya = biayaPokok + denda;
    t.status = "Selesai";
    
    // Update Status Kamera
    daftarKamera[idxKam].status = "Tersedia";

    // CETAK NOTA
    cout << "\n========================================\n";
    cout << "          NOTA PEMBAYARAN\n";
    cout << "========================================\n";
    cout << "ID Transaksi   : " << t.idTransaksi << endl;
    cout << "Kamera         : " << daftarKamera[idxKam].merek << " " << daftarKamera[idxKam].model << endl;
    cout << "Durasi Sewa    : " << durasiRencana << " Hari" << endl;
    cout << "Keterlambatan  : " << terlambat << " Hari" << endl;
    cout << "----------------------------------------\n";
    cout << "Biaya Pokok    : Rp " << (long)biayaPokok << endl;
    cout << "Denda          : Rp " << (long)denda << endl;
    cout << "----------------------------------------\n";
    cout << "TOTAL BAYAR    : Rp " << (long)t.totalBiaya << endl;
    cout << "========================================\n";
}

// ==========================================
// 4. MODUL PELAPORAN
// ==========================================

void laporanTransaksi(string filterStatus) {
    bersihkanLayar();
    cout << "=== LAPORAN TRANSAKSI (" << filterStatus << ") ===\n";
    
    cout << left << setw(10) << "ID Trx"
         << setw(10) << "ID Plg"
         << setw(10) << "ID Kam"
         << setw(10) << "Tgl Sewa"
         << setw(10) << "Tgl Rcn"
         << setw(10) << "Tgl Akt"
         << setw(15) << "Total" << endl;
    cout << "----------------------------------------------------------------------------\n";

    bool ada = false;
    for(int i=0; i<jumlahTransaksi; i++) {
        if(daftarTransaksi[i].status == filterStatus) {
            cout << left << setw(10) << daftarTransaksi[i].idTransaksi
                 << setw(10) << daftarTransaksi[i].idPelanggan
                 << setw(10) << daftarTransaksi[i].idKamera
                 << setw(10) << daftarTransaksi[i].tglSewa
                 << setw(10) << daftarTransaksi[i].tglRencanaKembali;
            
            if(filterStatus == "Selesai")
                 cout << setw(10) << daftarTransaksi[i].tglAktualKembali;
            else
                 cout << setw(10) << "-";

            cout << setw(15) << (long)daftarTransaksi[i].totalBiaya << endl;
            ada = true;
        }
    }
    if(!ada) cout << "Tidak ada data transaksi " << filterStatus << ".\n";
}

// ==========================================
// MAIN PROGRAM (MENU UTAMA)
// ==========================================

int main() {
    int pilihan;

    do {
        bersihkanLayar();
        cout << "========================================\n";
        cout << "   SISTEM MANAJEMEN RENTAL KAMERA\n";
        cout << "========================================\n";
        cout << "1. Manajemen Inventaris Kamera\n";
        cout << "2. Manajemen Pelanggan\n";
        cout << "3. Transaksi Penyewaan\n";
        cout << "4. Transaksi Pengembalian (Kasir)\n";
        cout << "5. Laporan Transaksi\n";
        cout << "0. Keluar\n";
        cout << "========================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                int subMenu;
                bersihkanLayar();
                cout << "-- Menu Inventaris --\n";
                cout << "1. Tambah Kamera\n";
                cout << "2. Hapus Kamera\n";
                cout << "3. Tampil Semua Kamera\n";
                cout << "4. Tampil Kamera Tersedia\n";
                cout << "5. Urutkan Kamera (Termurah)\n";
                cout << "Pilih: "; cin >> subMenu;
                if (subMenu == 1) tambahKamera();
                else if (subMenu == 2) hapusKamera();
                else if (subMenu == 3) tampilkanKamera(false);
                else if (subMenu == 4) tampilkanKamera(true);
                else if (subMenu == 5) urutkanKamera();
                pause();
                break;
            case 2:
                tambahPelanggan();
                pause();
                break;
            case 3:
                prosesPenyewaan();
                pause();
                break;
            case 4:
                prosesPengembalian();
                pause();
                break;
            case 5:
                int subLap;
                bersihkanLayar();
                cout << "-- Menu Laporan --\n";
                cout << "1. Transaksi Aktif (Sedang Disewa)\n";
                cout << "2. Riwayat Transaksi Selesai\n";
                cout << "Pilih: "; cin >> subLap;
                if (subLap == 1) laporanTransaksi("Aktif");
                else if (subLap == 2) laporanTransaksi("Selesai");
                pause();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan aplikasi ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    } while (pilihan != 0);

    return 0;
}