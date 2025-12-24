#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct DataKamera {
    string nama;
    int harga;
};

struct Transaksi {
    int id;
    string namaPenyewa;
    string namaKamera;
    int hargaSewa;
    int lamaSewa;
    int status; // 1 = disewa, 0 = dikembalikan
};

class RentalSystem {
private:
    vector<DataKamera> daftarKamera;
    vector<Transaksi> daftarTransaksi;
    int totalPendapatan;
    int nomorTransaksi;

public:
    // konstruktor untuk inisialisasi data awal
    RentalSystem() {
        daftarKamera = {
            {"Canon EOS 90D", 150000},
            {"Sony A6400", 180000},
            {"Nikon D7500", 160000}
        };
        totalPendapatan = 0;
        nomorTransaksi = 1;
    }

    // fungsi untuk login admin
    void login() {
        string user, pass;
        while (true) {
            system("cls");
            cout << "Login Admin\n";
            cout << "Username : "; cin >> user;
            cout << "Password : "; cin >> pass;

            if (user == "admin" && pass == "12") {
                break;
            } else {
                cout << "Login gagal!\n";
                system("pause");
            }
        }
    }

    // fungsi menampilkan menu utama
    void tampilkanMenu() {
        int menu;
        do {
            system("cls");
            cout << "Rental Kamera Digital\n";
            cout << "1. Sewa Kamera\n";
            cout << "2. Pengembalian Kamera\n";
            cout << "3. Sort Kamera (Harga)\n";
            cout << "4. Laporan Pendapatan\n";
            cout << "5. Logout\n";
            cout << "6. Keluar Program\n";
            cout << "Pilih Menu : "; cin >> menu;

            switch (menu) {
                case 1: prosesSewa(); break;
                case 2: prosesPengembalian(); break;
                case 3: sortKamera(); break;
                case 4: laporanPendapatan(); break;
                case 5: login(); break;
                case 6: 
                    cout << "Terima kasih.\n";
                    exit(0);
                default: 
                    cout << "Menu tidak valid!\n"; 
                    system("pause");
            }
        } while (menu != 6);
    }

    // fungsi memproses penyewaan kamera
    void prosesSewa() {
        system("cls");
        if (daftarTransaksi.size() >= 100) {
            cout << "Kapasitas penuh.\n";
            system("pause");
            return;
        }

        string nama;
        int pilihan, lama, bayar;
        
        cout << "Nama Pelanggan : ";
        cin.ignore();
        getline(cin, nama);

        cout << "\nDaftar Kamera:\n";
        for (size_t i = 0; i < daftarKamera.size(); i++) {
            cout << i + 1 << ". " << daftarKamera[i].nama 
                 << " - Rp " << daftarKamera[i].harga << "/hari\n";
        }

        cout << "\nPilih Kamera : "; cin >> pilihan;
        if (pilihan < 1 || pilihan > (int)daftarKamera.size()) {
            cout << "Pilihan tidak valid.\n";
            return;
        }

        cout << "Lama Sewa (hari) : "; cin >> lama;

        int total = daftarKamera[pilihan - 1].harga * lama;
        double diskon = 0;

        if (lama >= 7) diskon = 0.20;
        else if (lama >= 3) diskon = 0.10;

        int potongan = total * diskon;
        int totalBayar = total - potongan;

        cout << "\nStruk Sewa\n";
        cout << "Total Bayar : Rp " << totalBayar << endl;

        while (true) {
            cout << "Uang Bayar : Rp "; cin >> bayar;
            if (bayar >= totalBayar) break;
            cout << "Uang kurang.\n";
        }

        cout << "Kembalian : Rp " << bayar - totalBayar << endl;
        
        Transaksi baru;
        baru.id = nomorTransaksi++;
        baru.namaPenyewa = nama;
        baru.namaKamera = daftarKamera[pilihan - 1].nama;
        baru.hargaSewa = daftarKamera[pilihan - 1].harga;
        baru.lamaSewa = lama;
        baru.status = 1;
        
        daftarTransaksi.push_back(baru);
        totalPendapatan += totalBayar;
        
        system("pause");
    }

    // fungsi memproses pengembalian kamera
    void prosesPengembalian() {
        system("cls");
        bool adaSewa = false; 
        
        cout << "Daftar Sewa Aktif:\n";
        for (size_t i = 0; i < daftarTransaksi.size(); i++) {
            if (daftarTransaksi[i].status == 1) {
                cout << i + 1 << ". " << daftarTransaksi[i].namaPenyewa 
                     << " | " << daftarTransaksi[i].namaKamera << endl;
                adaSewa = true;
            }
        }

        if (!adaSewa) {
            cout << "Tidak ada sewa aktif.\n";
            system("pause");
            return;
        }

        int pilih, telat;
        cout << "\nPilih nomor transaksi : "; cin >> pilih;
        
        if (pilih < 1 || pilih > (int)daftarTransaksi.size() || 
            daftarTransaksi[pilih - 1].status == 0) {
            cout << "Tidak valid.\n";
            system("pause");
            return;
        }

        cout << "Keterlambatan (hari) : "; cin >> telat;
        
        if (telat > 0) {
            int denda = telat * 50000;
            cout << "Denda : Rp " << denda << endl;
            totalPendapatan += denda;
        }

        daftarTransaksi[pilih - 1].status = 0;
        cout << "Pengembalian berhasil.\n";
        system("pause");
    }

    // fungsi mengurutkan harga kamera
    void sortKamera() {
        system("cls");
        int tipe;
        cout << "1. Termurah ke Termahal\n";
        cout << "2. Termahal ke Termurah\n";
        cout << "Pilih : "; cin >> tipe;

        // bubble sort sederhana
        for (size_t i = 0; i < daftarKamera.size() - 1; i++) {
            for (size_t j = 0; j < daftarKamera.size() - i - 1; j++) {
                bool tukar = false;
                if (tipe == 1 && daftarKamera[j].harga > daftarKamera[j+1].harga) tukar = true;
                if (tipe == 2 && daftarKamera[j].harga < daftarKamera[j+1].harga) tukar = true;
                
                if (tukar) {
                    DataKamera temp = daftarKamera[j];
                    daftarKamera[j] = daftarKamera[j+1];
                    daftarKamera[j+1] = temp;
                }
            }
        }

        cout << "\nHasil Sort:\n";
        for (const auto& k : daftarKamera) {
            cout << k.nama << " - Rp " << k.harga << endl;
        }
        system("pause");
    }

    // fungsi menampilkan laporan pendapatan
    void laporanPendapatan() {
        system("cls");
        cout << "Laporan Pendapatan\n";
        cout << "Total Transaksi : " << nomorTransaksi - 1 << endl;
        cout << "Total Pendapatan : Rp " << totalPendapatan << endl;
        system("pause");
    }

    // fungsi utama menjalankan sistem
    void jalankan() {
        login();
        tampilkanMenu();
    }
};

int main() {
    RentalSystem app;
    app.jalankan();
    return 0;
}