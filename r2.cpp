#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main() {

    // data kamera
    string kamera[3] = {
        "Canon EOS 90D",
        "Sony A6400",
        "Nikon D7500"
    };

    int harga[3] = {150000, 180000, 160000};

    // ===== VARIABEL UMUM =====
    string user, pass;
    int menu;
    int totalPendapatan = 0;
    int noTransaksi = 1;

LOGIN:
    system("cls");
    cout << "==============================\n";
    cout << "        LOGIN ADMIN           \n";
    cout << "==============================\n";
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;

    if (user != "admin" || pass != "12") {
        cout << "\nLogin gagal!\n";
        system("pause");
        goto LOGIN;
    }

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

    // ================== SEWA ==================
    if (menu == 1) {
        system("cls");

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
        cout << "ID Transaksi : " << noTransaksi << endl;
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

        ofstream file("struk_rental.txt", ios::app);
        file << "=============================\n";
        file << "ID Transaksi : " << noTransaksi << endl;
        file << "Nama         : " << nama << endl;
        file << "Kamera       : " << kamera[pilihan - 1] << endl;
        file << "Total Bayar  : Rp " << totalBayar << endl;
        file << "=============================\n\n";
        file.close();

        totalPendapatan += totalBayar;
        noTransaksi++;

        system("pause");
        goto MENU;
    }

    // ================== PENGEMBALIAN ==================
    else if (menu == 2) {
        system("cls");

        int telatHari, idTransaksiKembali;  
        string namaKembali;
        int denda = 0;

        cout << "=== PENGEMBALIAN KAMERA ===\n";
        cout << "ID Transaksi   : ";
        cin >> idTransaksiKembali;
        cout << "Nama Penyewa   : ";
        cin.ignore();
        getline(cin, namaKembali);

        cout << "Keterlambatan (hari) : ";
        cin >> telatHari;

        cout << "\n--- STRUK PENGEMBALIAN ---\n";
        cout << "ID Transaksi : " << idTransaksiKembali << endl;
        cout << "Nama         : " << namaKembali << endl;

        if (telatHari > 0) {
            denda = telatHari * 50000;
            cout << "Denda Telat  : Rp " << denda << " (" << telatHari << " hari)\n";
            totalPendapatan += denda;
        } else {
            cout << "Status       : Tepat Waktu\n";
            cout << "Denda        : Rp 0\n";
        }

        cout << "Total Bayar  : Rp " << denda << endl;
        cout << "--------------------------\n";

        cout << "\nKamera berhasil dikembalikan.\n";
        system("pause");
        goto MENU;
    }

    // ================== SORT ==================
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

    // ================== LAPORAN ==================
    else if (menu == 4) {
        system("cls");
        cout << "====== LAPORAN PENDAPATAN ======\n";
        cout << "Total Transaksi  : " << noTransaksi - 1 << endl;
        cout << "Total Pendapatan : Rp " << totalPendapatan << endl;
        cout << "================================\n";
        system("pause");
        goto MENU;
    }

    // ================== LOGOUT ==================
    else if (menu == 5) {
        goto LOGIN;
    }

    // ================== KELUAR ==================
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