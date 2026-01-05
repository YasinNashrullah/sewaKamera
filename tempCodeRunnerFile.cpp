// =================== PERSON 1: DATA STRUCTURES & SETUP ===================
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// data kamera menggunakan array terpisah (bukan struct)
// string nama[100];
// int harga[100]; 

// struktur data untuk transaksi
struct Transaksi {
    int id;
    string namaPenyewa;
    string namaKamera;
    int hargaSewa;
    int lamaSewa;
    int status; // 1 disewa 0 dikembalikan
};

// struct utama sistem rental
struct RentalSystem {
    // data global dalam struct
    // ganti struct DataKamera dengan array biasa
    string daftarNamaKamera[100]; // pengganti .nama
    int daftarHargaKamera[100];   // pengganti .harga
    
    Transaksi daftarTransaksi[100];
    int jumlahKamera;
    int jumlahTransaksi;
    int totalPendapatan;
    int nomorTransaksi;

    // konstruktor untuk menyiapkan data awal
    // fungsi untuk menyiapkan data awal (pengganti konstruktor)
    void settingAwal() {
        jumlahKamera = 0;
        jumlahTransaksi = 0;
        totalPendapatan = 0;
        nomorTransaksi = 1;

        // data awal kamera 1
        daftarNamaKamera[jumlahKamera] = "Canon EOS 90D";
        daftarHargaKamera[jumlahKamera] = 150000;
        jumlahKamera++;

        // data awal kamera 2
        daftarNamaKamera[jumlahKamera] = "Sony A6400";
        daftarHargaKamera[jumlahKamera] = 180000;
        jumlahKamera++;

        // data awal kamera 3
        daftarNamaKamera[jumlahKamera] = "Nikon D7500";
        daftarHargaKamera[jumlahKamera] = 160000;
        jumlahKamera++;
    }

    // =================== PERSON 2: AUTHENTICATION & UTILS ===================
    // fungsi bantuan untuk pause
    void tekanEnter() {
        cout << "tekan enter untuk lanjut...";
        cin.get(); 
    }

    // fungsi untuk masuk sebagai admin
    void login() {
        string user, pass;
        while (true) {
            system("cls");
            cout << "login admin" << endl;
            cout << "username: "; cin >> user;
            cout << "password: "; cin >> pass;
            cin.ignore();

            if (user == "admin" && pass == "12") {
                break;
            } else {
                cout << "login gagal" << endl;
                tekanEnter();
            }
        }
    }

    // =================== PERSON 3: MENU & MAIN LOOP ===================
    // fungsi untuk menampilkan menu utama
    void tampilkanMenu() {
        int menu;
        do {
            system("cls");
            cout << "rental kamera digital" << endl;
            cout << "1. sewa kamera" << endl;
            cout << "2. pengembalian kamera" << endl;
            cout << "3. urutkan harga kamera" << endl;
            cout << "4. laporan pendapatan" << endl;
            cout << "5. logout" << endl;
            cout << "pilih menu: "; cin >> menu;
            cin.ignore(); // bersihkan enter

            switch (menu) {
                case 1: prosesSewa(); break;
                case 2: prosesPengembalian(); break;
                case 3: sortKamera(); break;
                case 4: laporanPendapatan(); break;
                case 5: logout(); break;
                default: 
                    cout << "menu tidak ada" << endl; 
                    tekanEnter();
            }
        } while (true);
    }

    // =================== PERSON 4: RENTAL TRANSACTION ===================
    void prosesSewa() {
        system("cls");
        if (jumlahTransaksi >= 100) {
            cout << "penyimpanan penuh" << endl;
            tekanEnter();
            return;
        }

        string nama;
        int pilihan, lama, bayar;
        
        cout << "nama pelanggan: ";
        getline(cin, nama);

        cout << endl << "daftar kamera" << endl;
        for (int i = 0; i < jumlahKamera; i++) {
            cout << i + 1 << ". " << daftarNamaKamera[i] << " - harga: " << daftarHargaKamera[i] << " per hari" << endl;
        }

        cout << endl << "pilih kamera: "; cin >> pilihan;
        if (pilihan < 1 || pilihan > jumlahKamera) {
            cout << "pilihan salah" << endl;
            cin.ignore();
            tekanEnter();
            return;
        }

        cout << "lama sewa (hari): "; cin >> lama;

        int total = daftarHargaKamera[pilihan - 1] * lama;
        double diskon = 0;

        if (lama >= 7) diskon = 0.20;
        else if (lama >= 3) diskon = 0.10;

        int potongan = (int)(total * diskon);
        int totalBayar = total - potongan;

        cout << endl << "struk sewa" << endl;
        cout << "harga normal: rp " << total << endl;
        cout << "diskon: " << (int)(diskon * 100) << "%" << endl;
        cout << "potongan: rp " << potongan << endl;
        cout << "total bayar: rp " << totalBayar << endl;

        while (true) {
            cout << "uang bayar: rp "; cin >> bayar;
            if (bayar >= totalBayar) break;
            cout << "uang kurang" << endl;
        }

        cout << "kembalian: rp " << bayar - totalBayar << endl;
        
        daftarTransaksi[jumlahTransaksi].id = nomorTransaksi;
        daftarTransaksi[jumlahTransaksi].namaPenyewa = nama;
        daftarTransaksi[jumlahTransaksi].namaKamera = daftarNamaKamera[pilihan - 1];
        daftarTransaksi[jumlahTransaksi].hargaSewa = daftarHargaKamera[pilihan - 1];
        daftarTransaksi[jumlahTransaksi].lamaSewa = lama;
        daftarTransaksi[jumlahTransaksi].status = 1;

        nomorTransaksi++;
        jumlahTransaksi++;
        totalPendapatan = totalPendapatan + totalBayar;
        
        cin.ignore();
        tekanEnter();
    }

    // =================== PERSON 5: RETURN TRANSACTION ===================
    // fungsi untuk mengembalikan kamera
    void prosesPengembalian() {
        system("cls");
        bool adaSewa = false; 
        
        cout << "daftar sewa aktif" << endl;
        for (int i = 0; i < jumlahTransaksi; i++) {
            if (daftarTransaksi[i].status == 1) {
                cout << i + 1 << ". " << daftarTransaksi[i].namaPenyewa 
                     << " - kamera: " << daftarTransaksi[i].namaKamera << endl;
                adaSewa = true;
            }
        }

        if (adaSewa == false) {
            cout << "tidak ada sewa aktif" << endl;
            tekanEnter();
            return;
        }

        int pilih, telat;
        cout << endl << "pilih nomor: "; cin >> pilih;
        
        if (pilih < 1 || pilih > jumlahTransaksi || 
            daftarTransaksi[pilih - 1].status == 0) {
            cout << "tidak valid" << endl;
            cin.ignore();
            tekanEnter();
            return;
        }

        cout << "telat (hari): "; cin >> telat;
        
        if (telat > 0) {
            int denda = telat * 50000;
            cout << "denda: rp " << denda << endl;
            totalPendapatan = totalPendapatan + denda;
        }

        daftarTransaksi[pilih - 1].status = 0;
        cout << "kamera kembali" << endl;
        cin.ignore();
        tekanEnter();
    }

    // =================== PERSON 6: SORTING & REPORTS ===================
    // fungsi untuk mengurutkan harga kamera
    void sortKamera() {
        system("cls");
        int tipe;
        cout << "1. termurah ke termahal" << endl;
        cout << "2. termahal ke termurah" << endl;
        cout << "pilih: "; cin >> tipe;
        cin.ignore(); // clean

        for (int i = 0; i < jumlahKamera - 1; i++) {
            for (int j = 0; j < jumlahKamera - i - 1; j++) {
                bool tukar = false;
                if (tipe == 1 && daftarHargaKamera[j] > daftarHargaKamera[j+1]) tukar = true;
                if (tipe == 2 && daftarHargaKamera[j] < daftarHargaKamera[j+1]) tukar = true;
                
                if (tukar == true) {
                    // tukar harga
                    int tempHarga = daftarHargaKamera[j];
                    daftarHargaKamera[j] = daftarHargaKamera[j+1];
                    daftarHargaKamera[j+1] = tempHarga;

                    // tukar nama (harus ikut ditukar agar sesuai)
                    string tempNama = daftarNamaKamera[j];
                    daftarNamaKamera[j] = daftarNamaKamera[j+1];
                    daftarNamaKamera[j+1] = tempNama;
                }
            }
        }

        cout << endl << "hasil urut" << endl; 
        for (int k = 0; k < jumlahKamera; k++) {
            cout << daftarNamaKamera[k] << " - harga: " << daftarHargaKamera[k] << endl;
        }
        tekanEnter();
    }

    // fungsi untuk melihat pendapatan
    void laporanPendapatan() {
        system("cls");
        cout << "laporan pendapatan" << endl;
        cout << "total transaksi: " << nomorTransaksi - 1 << endl;
        cout << "total pendapatan: rp " << totalPendapatan << endl;
        tekanEnter();
    }

    void logout() {         
        system("cls");      
        cout << "log out berhasil" << endl; 
        tekanEnter(); 
        return; 
    }

    void jalankan() {
        while (true) {
            login();
            tampilkanMenu();
        }
    }
};

int main() {
    RentalSystem app;
    app.settingAwal(); // panggil setting awal manual
    app.jalankan();
    return 0;
}