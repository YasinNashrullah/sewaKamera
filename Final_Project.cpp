#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main() {

    // ================= DATA KAMERA =================
    string kamera[3] = {
        "Canon EOS 90D",
        "Sony A6400",
        "Nikon D7500"
    };
    int harga[3] = {150000, 180000, 160000};

    // ================= DATA SEWA AKTIF =================
    string sewaNama[10];
    string sewaKamera[10];
    int sewaHarga[10];
    int sewaHari[10];
    int sewaStatus[10]; // 1 = disewa, 0 = dikembalikan
    int jumlahSewa = 0;

    // ================= VARIABEL UMUM =================
    string user, pass;
    int menu;
    int totalPendapatan = 0;
    int noTransaksi = 1;

    // ================= LOGIN =================
LOGIN:
    system("cls");
    cout << "==============================\n";
    cout << "        LOGIN ADMIN           \n";
    cout << "==============================\n";
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;

    if (user != "admin" || pass != "12345") {
        cout << "\nLogin gagal!\n";
        system("pause");
        goto LOGIN;
    }

    // ================= MENU =================
MENU:
    system("cls");
    cout << "=================================\n";
    cout << "       RENTAL KAMERA DIGITAL     \n";
    cout << "=================================\n";
    cout << "1. Sewa Kamera\n";
    cout << "2. Pengembalian Kamera\n";
    cout << "3. Sort Kamera (Harga)\n";
    cout << "4. Laporan Pendapatan\n";
    cout << "5. Logout\n";
    cout << "6. Keluar Program\n";
    cout << "Pilih Menu : ";
    cin >> menu;

    // ================= SEWA KAMERA =================
    if (menu == 1) {
        system("cls");

        if (jumlahSewa >= 10) {
            cout << "Kapasitas sewa penuh!\n";
            system("pause");
            goto MENU;
        }

        string nama;
        int pilihan, lamaSewa;
        int totalAwal, totalBayar;
        double diskon = 0, potongan;
        int bayar, kembalian;

        time_t now = time(0);
        string tanggal = ctime(&now);

        cout << "Nama Pelanggan : ";
        cin.ignore();
        getline(cin, nama);

        cout << "\n----- DAFTAR KAMERA -----\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << kamera[i]
                 << " - Rp " << harga[i] << " / hari\n";
        }

        cout << "\nPilih Kamera (1-3): ";
        cin >> pilihan;
        if (pilihan < 1 || pilihan > 3) {
            cout << "Pilihan tidak valid!\n";
            system("pause");
            goto MENU;
        }

        cout << "Lama Sewa (hari): ";
        cin >> lamaSewa;

        totalAwal = harga[pilihan - 1] * lamaSewa;

        if (lamaSewa >= 7) diskon = 0.20;
        else if (lamaSewa >= 3) diskon = 0.10;

        potongan = totalAwal * diskon;
        totalBayar = totalAwal - potongan;

        system("cls");
        cout << "=========== STRUK SEWA ===========\n";
        cout << "No Transaksi : " << noTransaksi << endl;
        cout << "Tanggal      : " << tanggal;
        cout << "Nama         : " << nama << endl;
        cout << "Kamera       : " << kamera[pilihan - 1] << endl;
        cout << "Total Bayar  : Rp " << totalBayar << endl;
        cout << "=================================\n";

BAYAR:
        cout << "Uang Bayar   : Rp ";
        cin >> bayar;
        if (bayar < totalBayar) {
            cout << "Uang tidak cukup!\n";
            goto BAYAR;
        }

        kembalian = bayar - totalBayar;
        cout << "Kembalian    : Rp " << kembalian << endl;
        cout << "=================================\n";

        // Simpan transaksi sewa aktif
        sewaNama[jumlahSewa]    = nama;
        sewaKamera[jumlahSewa] = kamera[pilihan - 1];
        sewaHarga[jumlahSewa]  = harga[pilihan - 1];
        sewaHari[jumlahSewa]   = lamaSewa;
        sewaStatus[jumlahSewa] = 1;
        jumlahSewa++;

        totalPendapatan += totalBayar;
        noTransaksi++;

        system("pause");
        goto MENU;
    }

    // ================= PENGEMBALIAN =================
    else if (menu == 2) {
        system("cls");

        int ada = 0;
        for (int i = 0; i < jumlahSewa; i++) {
            if (sewaStatus[i] == 1) ada = 1;
        }

        if (ada == 0) {
            cout << "Tidak ada kamera yang sedang disewa.\n";
            system("pause");
            goto MENU;
        }

        cout << "===== DAFTAR SEWA AKTIF =====\n";
        for (int i = 0; i < jumlahSewa; i++) {
            if (sewaStatus[i] == 1) {
                cout << i + 1 << ". "
                     << sewaNama[i] << " | "
                     << sewaKamera[i] << " | "
                     << sewaHari[i] << " hari\n";
            }
        }

        int pilih;
        cout << "\nPilih nomor transaksi yang dikembalikan: ";
        cin >> pilih;

        if (pilih < 1 || pilih > jumlahSewa || sewaStatus[pilih - 1] == 0) {
            cout << "Pilihan tidak valid!\n";
            system("pause");
            goto MENU;
        }

        int telat;
        cout << "Jumlah hari keterlambatan: ";
        cin >> telat;

        int denda = 0;
        if (telat > 0) {
            denda = telat * 50000;
            cout << "Denda Keterlambatan : Rp " << denda << endl;
            totalPendapatan += denda;
        } else {
            cout << "Pengembalian tepat waktu.\n";
        }

        sewaStatus[pilih - 1] = 0;

        cout << "Kamera '" << sewaKamera[pilih - 1]
             << "' berhasil dikembalikan.\n";

        system("pause");
        goto MENU;
    }

    // ================= SORT =================
    else if (menu == 3) {
        system("cls");
        int pilihSort;

        cout << "=== SORT HARGA KAMERA ===\n";
        cout << "1. Termurah ke Termahal\n";
        cout << "2. Termahal ke Termurah\n";
        cout << "Pilih : ";
        cin >> pilihSort;

        for (int i = 0; i < 3 - 1; i++) {
            for (int j = 0; j < 3 - i - 1; j++) {
                if ((pilihSort == 1 && harga[j] > harga[j + 1]) ||
                    (pilihSort == 2 && harga[j] < harga[j + 1])) {

                    int tempHarga = harga[j];
                    harga[j] = harga[j + 1];
                    harga[j + 1] = tempHarga;

                    string tempKamera = kamera[j];
                    kamera[j] = kamera[j + 1];
                    kamera[j + 1] = tempKamera;
                }
            }
        }

        cout << "\nHASIL SORT:\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << kamera[i]
                 << " - Rp " << harga[i] << endl;
        }

        system("pause");
        goto MENU;
    }

    // ================= LAPORAN =================
    else if (menu == 4) {
        system("cls");
        cout << "====== LAPORAN PENDAPATAN ======\n";
        cout << "Total Transaksi  : " << noTransaksi - 1 << endl;
        cout << "Total Pendapatan : Rp " << totalPendapatan << endl;
        cout << "================================\n";
        system("pause");
        goto MENU;
    }

    // ================= LOGOUT =================
    else if (menu == 5) {
        goto LOGIN;
    }

    // ================= KELUAR =================
    else if (menu == 6) {
        system("cls");
        cout << "Terima kasih telah menggunakan\n";
        cout << "Program Rental Kamera\n";
        return 0;
    }

    else {
        cout << "Menu tidak valid!\n";
        system("pause");
        goto MENU;
    }
}