#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// struktur data
// Struct untuk menyimpan data kamera yang tersedia untuk disewa
struct DataKamera {
    string nama;
    int harga;
};

// Struct untuk mencatat data transaksi penyewaan
struct Transaksi {
    int id;
    string namaPenyewa;
    string namaKamera;
    int hargaSewa;
    int lamaSewa;
    int status;
};

struct RentalSystem {
    DataKamera daftarKamera[100];
    Transaksi daftarTransaksi[100];
    int jumlahKamera;
    int jumlahTransaksi;
    int totalPendapatan;
    int nomorTransaksi;

    // Constructor: Inisialisasi data awal sistem saat program dijalankan
    RentalSystem() {
        jumlahKamera = 0;
        jumlahTransaksi = 0;
        totalPendapatan = 0;
        nomorTransaksi = 1;

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

    // Fungsi pembantu untuk menjeda program agar user bisa membaca output
    void tekanEnter() {
        cout << "tekan enter untuk lanjut...";
        cin.get();
    }

    // Fungsi untuk autentikasi admin sebelum masuk ke sistem utama
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

    // Menampilkan menu utama dan menangani navigasi pilihan user
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
            cin.ignore();

            switch (menu) {
                case 1: prosesSewa(); break;
                case 2: prosesPengembalian(); break;
                case 3: sortKamera(); break;
                case 4: laporanPendapatan(); break;
                case 5: logout(); return;
                default:
                    cout << "menu tidak ada" << endl;
                    tekanEnter();
            }
        } while (true);
    }

    // Menangani proses penyewaan kamera: input data, hitung biaya, dan simpan transaksi
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
            cout << i + 1 << ". " << daftarKamera[i].nama << " - harga: " << daftarKamera[i].harga << " per hari" << endl;
        }

        cout << endl << "pilih kamera: "; cin >> pilihan;
        if (pilihan < 1 || pilihan > jumlahKamera) {
            cout << "pilihan salah" << endl;
            cin.ignore();
            tekanEnter();
            return;
        }

        cout << "lama sewa (hari): "; cin >> lama;

        int total = daftarKamera[pilihan - 1].harga * lama;
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
        daftarTransaksi[jumlahTransaksi].namaKamera = daftarKamera[pilihan - 1].nama;
        daftarTransaksi[jumlahTransaksi].hargaSewa = daftarKamera[pilihan - 1].harga;
        daftarTransaksi[jumlahTransaksi].lamaSewa = lama;
        daftarTransaksi[jumlahTransaksi].status = 1;

        nomorTransaksi++;   
        jumlahTransaksi++;  
        totalPendapatan = totalPendapatan + totalBayar; 
        
        cin.ignore();       
        tekanEnter();       
    }

    // Menangani pengembalian kamera: cek denda keterlambatan dan update status transaksi
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

    // Mengurutkan daftar kamera berdasarkan harga menggunakan Bubble Sort
    void sortKamera() {     
        system("cls");      
        int tipe;           
        cout << "1. termurah ke termahal" << endl;
        cout << "2. termahal ke termurah" << endl; 
        cout << "pilih: "; cin >> tipe; 
        cin.ignore();       

        for (int i = 0; i < jumlahKamera - 1; i++) {
            for (int j = 0; j < jumlahKamera - i - 1; j++) {
                bool tukar = false; 
                if (tipe == 1 && daftarKamera[j].harga > daftarKamera[j+1].harga) tukar = true;
                if (tipe == 2 && daftarKamera[j].harga < daftarKamera[j+1].harga) tukar = true;
                
                if (tukar == true) {
                    DataKamera temp = daftarKamera[j];
                    daftarKamera[j] = daftarKamera[j+1];
                    daftarKamera[j+1] = temp;
                }
            }
        }

        cout << endl << "hasil urut" << endl; 
        for (int k = 0; k < jumlahKamera; k++) { 
            cout << daftarKamera[k].nama << " - harga: " << daftarKamera[k].harga << endl; 
        }
        tekanEnter();       
    }

    // Menampilkan laporan ringkas jumlah transaksi dan total pendapatan
    void laporanPendapatan() { 
        system("cls");      
        cout << "laporan pendapatan" << endl;
        cout << "total transaksi: " << nomorTransaksi - 1 << endl; 
        cout << "total pendapatan: rp " << totalPendapatan << endl; 
        tekanEnter();       
    }

    // Keluar dari sesi admin dan kembali ke halaman login
    void logout() {         
        system("cls");      
        cout << "log out berhasil" << endl; 
        tekanEnter(); 
        return; 
    }

    // Loop utama aplikasi yang menghubungkan login dan menu
    void jalankan() {       
        while (true) {      
            login();        
            tampilkanMenu(); 
        }
    }
};

int main() {                
    RentalSystem app;       
    app.jalankan();         
    return 0;               
}