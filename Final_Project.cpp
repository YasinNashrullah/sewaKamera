#include <iostream>         // pustaka input output
#include <string>           // pustaka untuk string
#include <cstdlib>          // pustaka sistem

using namespace std;        // menggunakan namespace standar

// struktur data
struct DataKamera {         // definisi struktur data
    string nama;            // variabel nama kamera
    int harga;              // variabel harga sewa
};

struct Transaksi {          // struktur data transaksi
    int id;                 // id transaksi
    string namaPenyewa;     // nama penyewa
    string namaKamera;      // nama kamera disewa
    int hargaSewa;          // harga sewa per hari
    int lamaSewa;           // durasi sewa
    int status;             // status sewa 1 aktif 0 kembali
};

struct RentalSystem {       // struktur utama sistem
    DataKamera daftarKamera[100]; // array data kamera
    Transaksi daftarTransaksi[100]; // array data transaksi
    int jumlahKamera;       // jumlah kamera tersedia
    int jumlahTransaksi;    // jumlah transaksi tercatat
    int totalPendapatan;    // total pendapatan rental
    int nomorTransaksi;     // counter nomor transaksi

    // konstruktor
    RentalSystem() {        // konstruktor sistem
        jumlahKamera = 0;   // inisialisasi jumlah kamera
        jumlahTransaksi = 0; // inisialisasi jumlah transaksi
        totalPendapatan = 0; // inisialisasi pendapatan
        nomorTransaksi = 1; // inisialisasi nomor awal

        daftarKamera[jumlahKamera].nama = "Canon EOS 90D"; // nama kamera 1
        daftarKamera[jumlahKamera].harga = 150000;         // harga kamera 1
        jumlahKamera++;     // tambah jumlah kamera

        daftarKamera[jumlahKamera].nama = "Sony A6400";    // nama kamera 2
        daftarKamera[jumlahKamera].harga = 180000;         // harga kamera 2
        jumlahKamera++;     // tambah jumlah kamera

        daftarKamera[jumlahKamera].nama = "Nikon D7500";   // nama kamera 3
        daftarKamera[jumlahKamera].harga = 160000;         // harga kamera 3
        jumlahKamera++;     // tambah jumlah kamera
    }

    // fitur bantuan
    void tekanEnter() {     // fungsi jeda program
        cout << "tekan enter untuk lanjut..."; // pesan jeda
        cin.get();          // tunggu input enter
    }

    // fitur navigasi
    void login() {          // fungsi login admin
        string user, pass;  // variabel user dan password
        while (true) {      // loop login selamanya
            system("cls");  // bersihkan layar
            cout << "login admin" << endl; // judul login
            cout << "username: "; cin >> user; // input username
            cout << "password: "; cin >> pass; // input password
            cin.ignore();   // bersihkan buffer input

            if (user == "admin" && pass == "12") { // cek kredensial
                break;      // keluar loop jika benar
            } else {        // jika salah
                cout << "login gagal" << endl; // pesan gagal
                tekanEnter(); // minta tekan enter
            }
        }
    }

    void tampilkanMenu() {  // fungsi menu utama
        int menu;           // variabel pilihan menu
        do {                // loop menu utama
            system("cls");  // bersihkan layar
            cout << "rental kamera digital" << endl; // judul program
            cout << "1. sewa kamera" << endl; // menu 1
            cout << "2. pengembalian kamera" << endl; // menu 2
            cout << "3. urutkan harga kamera" << endl; // menu 3
            cout << "4. laporan pendapatan" << endl; // menu 4
            cout << "5. logout" << endl; // menu 5
            cout << "pilih menu: "; cin >> menu; // input pilihan
            cin.ignore();   // bersihkan buffer

            switch (menu) { // seleksi menu
                case 1: prosesSewa(); break; // jalankan sewa
                case 2: prosesPengembalian(); break; // jalankan kembali
                case 3: sortKamera(); break; // jalankan urut
                case 4: laporanPendapatan(); break; // jalankan laporan
                case 5: logout(); break; // menu keluar
                default:    // pilihan salah
                    cout << "menu tidak ada" << endl; // pesan salah
                    tekanEnter(); // jeda sebentar
            }
        } while (true);     // ulangi terus
    }

    // fitur utama
    void prosesSewa() {     // fungsi proses sewa
        system("cls");      // bersihkan layar
        if (jumlahTransaksi >= 100) { // cek kapasitas array
            cout << "penyimpanan penuh" << endl; // pesan penuh
            tekanEnter();   // jeda
            return;         // batal sewa
        }

        string nama;        // variabel nama penyewa
        int pilihan, lama, bayar; // variabel input sewa
        
        cout << "nama pelanggan: "; // prompt nama
        getline(cin, nama); // input nama lengkap

        cout << endl << "daftar kamera" << endl; // header daftar
        for (int i = 0; i < jumlahKamera; i++) { // loop daftar kamera
            cout << i + 1 << ". " << daftarKamera[i].nama << " - harga: " << daftarKamera[i].harga << " per hari" << endl; // tampil kamera
        }

        cout << endl << "pilih kamera: "; cin >> pilihan; // input pilihan
        if (pilihan < 1 || pilihan > jumlahKamera) { // validasi pilihan
            cout << "pilihan salah" << endl; // pesan salah
            cin.ignore();   // bersihkan buffer
            tekanEnter();   // jeda
            return;         // batal
        }

        cout << "lama sewa (hari): "; cin >> lama; // input lama sewa

        int total = daftarKamera[pilihan - 1].harga * lama; // hitung total
        double diskon = 0;  // inisialisasi diskon

        if (lama >= 7) diskon = 0.20; // diskon 1 minggu
        else if (lama >= 3) diskon = 0.10; // diskon 3 hari

        int potongan = (int)(total * diskon); // hitung nominal diskon
        int totalBayar = total - potongan; // hitung bayar akhir

        cout << endl << "struk sewa" << endl; // judul struk
        cout << "harga normal: rp " << total << endl; // tampil harga asli
        cout << "diskon: " << (int)(diskon * 100) << "%" << endl; // tampil persentase
        cout << "potongan: rp " << potongan << endl; // tampil potongan
        cout << "total bayar: rp " << totalBayar << endl; // tampil total

        while (true) {      // loop pembayaran
            cout << "uang bayar: rp "; cin >> bayar; // input uang
            if (bayar >= totalBayar) break; // cek kecukupan
            cout << "uang kurang" << endl; // pesan kurang
        }

        cout << "kembalian: rp " << bayar - totalBayar << endl; // tampil kembalian
        
        daftarTransaksi[jumlahTransaksi].id = nomorTransaksi; // simpan id
        daftarTransaksi[jumlahTransaksi].namaPenyewa = nama; // simpan nama
        daftarTransaksi[jumlahTransaksi].namaKamera = daftarKamera[pilihan - 1].nama; // simpan kamera
        daftarTransaksi[jumlahTransaksi].hargaSewa = daftarKamera[pilihan - 1].harga; // simpan harga
        daftarTransaksi[jumlahTransaksi].lamaSewa = lama; // simpan lama
        daftarTransaksi[jumlahTransaksi].status = 1; // set status sewa

        nomorTransaksi++;   // update nomor
        jumlahTransaksi++;  // update jumlah
        totalPendapatan = totalPendapatan + totalBayar; // update pendapatan
        
        cin.ignore();       // bersihkan buffer
        tekanEnter();       // jeda
    }

    void prosesPengembalian() { // fungsi pengembalian
        system("cls");      // bersihkan layar
        bool adaSewa = false; // flag sewa aktif
        
        cout << "daftar sewa aktif" << endl; // judul daftar
        for (int i = 0; i < jumlahTransaksi; i++) { // loop transaksi
            if (daftarTransaksi[i].status == 1) { // cek status aktif
                cout << i + 1 << ". " << daftarTransaksi[i].namaPenyewa 
                     << " - kamera: " << daftarTransaksi[i].namaKamera << endl; // tampil data
                adaSewa = true; // tandai ditemukan
            }
        }

        if (adaSewa == false) { // jika kosong
            cout << "tidak ada sewa aktif" << endl; // pesan kosong
            tekanEnter();   // jeda
            return;         // kembali
        }

        int pilih, telat;   // variabel input
        cout << endl << "pilih nomor: "; cin >> pilih; // pilih transaksi
        
        if (pilih < 1 || pilih > jumlahTransaksi || 
            daftarTransaksi[pilih - 1].status == 0) { // validasi pilihan
            cout << "tidak valid" << endl; // pesan salah
            cin.ignore();   // bersihkan buffer
            tekanEnter();   // jeda
            return;         // batal
        }

        cout << "telat (hari): "; cin >> telat; // input keterlambatan
        
        if (telat > 0) {    // jika terlambat
            int denda = telat * 50000; // hitung denda
            cout << "denda: rp " << denda << endl; // tampil denda
            totalPendapatan = totalPendapatan + denda; // update pendapatan
        }

        daftarTransaksi[pilih - 1].status = 0; // ubah status kembali
        cout << "kamera kembali" << endl; // pesan sukses
        cin.ignore();       // bersihkan buffer
        tekanEnter();       // jeda
    }

    void sortKamera() {     // fungsi urutkan
        system("cls");      // bersihkan layar
        int tipe;           // variabel tipe urut
        cout << "1. termurah ke termahal" << endl; // opsi 1
        cout << "2. termahal ke termurah" << endl; // opsi 2
        cout << "pilih: "; cin >> tipe; // input pilihan
        cin.ignore();       // bersihkan buffer

        for (int i = 0; i < jumlahKamera - 1; i++) { // loop bubble sort
            for (int j = 0; j < jumlahKamera - i - 1; j++) { // loop dalam
                bool tukar = false; // flag tukar
                if (tipe == 1 && daftarKamera[j].harga > daftarKamera[j+1].harga) tukar = true; // cek naik
                if (tipe == 2 && daftarKamera[j].harga < daftarKamera[j+1].harga) tukar = true; // cek turun
                
                if (tukar == true) { // jika perlu tukar
                    DataKamera temp = daftarKamera[j]; // simpan sementara
                    daftarKamera[j] = daftarKamera[j+1]; // tukar posisi
                    daftarKamera[j+1] = temp; // kembalikan nilai
                }
            }
        }

        cout << endl << "hasil urut" << endl; // judul hasil
        for (int k = 0; k < jumlahKamera; k++) { // loop hasil
            cout << daftarKamera[k].nama << " - harga: " << daftarKamera[k].harga << endl; // tampil data
        }
        tekanEnter();       // jeda
    }

    void laporanPendapatan() { // fungsi laporan
        system("cls");      // bersihkan layar
        cout << "laporan pendapatan" << endl; // judul laporan
        cout << "total transaksi: " << nomorTransaksi - 1 << endl; // tampil jumlah
        cout << "total pendapatan: rp " << totalPendapatan << endl; // tampil uang
        tekanEnter();       // jeda
    }

    void logout() {         // fungsi logout
        system("cls");      // bersihkan layar
        cout << "log out berhasil" << endl; // pesan keluar
        tekanEnter(); // jeda sebentar
        return; // keluar fungsi
    }

    // sistem utama
    void jalankan() {       // fungsi utama jalan
        while (true) {      // loop utama
            login();        // panggil login
            tampilkanMenu(); // panggil menu
        }
    }
};

int main() {                // fungsi main program
    RentalSystem app;       // buat objek sistem (untuk running)
    app.jalankan();         // jalankan sistem
    return 0;               // program selesai
}