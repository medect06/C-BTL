#include "customer.h"

void themKhachHang(vector<KhachHang>& danhSachKhachHang, const KhachHang& khachHangMoi) {
    danhSachKhachHang.push_back(khachHangMoi);
}

void xemDanhSachKhachHang(const vector<KhachHang>& danhSachKhachHang) {
    for (const auto& kh : danhSachKhachHang) {
        cout << "Ten: " << kh.tenKhachHang << ", So Dien Thoai: " << kh.soDienThoai << ", Diem Tich Luy: " << kh.diemTichLuy << endl;
    }
}

void timKiemKhachHang(const vector<KhachHang>& danhSachKhachHang) {
    string ten;
    cout << "Nhap ten khach hang can tim: ";
    getline(cin, ten);

    for (const auto& kh : danhSachKhachHang) {
        if (kh.tenKhachHang == ten) {
            cout << "Ten: " << kh.tenKhachHang << ", So Dien Thoai: " << kh.soDienThoai << ", Diem Tich Luy: " << kh.diemTichLuy << endl;
            return;
        }
    }

    cout << "Khong tim thay khach hang nay." << endl;
}

void xoaKhachHang(vector<KhachHang>& danhSachKhach, const KhachHang& khachXoa) {
    for (auto it = danhSachKhach.begin(); it != danhSachKhach.end(); ++it) {
        if (coNhuNhauKhachHang(*it, khachXoa)) {
            danhSachKhach.erase(it);
            return;
        }
    }
}
#include "customer.h"

void nhapThongTinKhach(KhachHang& khachHang) {
    cout << "Nhap ten khach hang: ";
    getline(cin, khachHang.tenKhachHang);

    cout << "Nhap so dien thoai: ";
    getline(cin, khachHang.soDienThoai);

    cout << "Nhap diem tich luy: ";
    cin >> khachHang.diemTichLuy;
    cin.ignore();
}

void nhapTenSDTKhach(KhachHang& khachHang) {
    cout << "Nhap ten khach hang: ";
    getline(cin, khachHang.tenKhachHang);

    cout << "Nhap so dien thoai: ";
    getline(cin, khachHang.soDienThoai);
}

void capNhatKhachTuMang(vector<KhachHang>& danhSach, const string& duongDan) {
    docFileKhachHang(duongDan, danhSach);
}

void capNhatKhachTuFile(vector<KhachHang>& danhSach, const string& duongDan) {
    docFileKhachHang(duongDan, danhSach);
}
#include "customer.h"

void layDiemTichLuy(const vector<KhachHang>& danhSachKhachHang, KhachHang& khach) {
    for (const auto& khachHienTai : danhSachKhachHang) {
        if (khachHienTai.tenKhachHang == khach.tenKhachHang && khachHienTai.soDienThoai == khach.soDienThoai) {
            khach.diemTichLuy = khachHienTai.diemTichLuy;
            return;
        }
    }
}

void chuanHoaKhachHang(vector<KhachHang>& danhSachKhachHang) {
    for (auto& kh : danhSachKhachHang) {
        kh.diemTichLuy = max(0.0f, kh.diemTichLuy);
    }
}

void saoChepKhachHang(KhachHang& khachNhan, const KhachHang& khachNguon) {
    khachNhan.tenKhachHang = khachNguon.tenKhachHang;
    khachNhan.soDienThoai = khachNguon.soDienThoai;
    khachNhan.diemTichLuy = khachNguon.diemTichLuy;
}

int kiemTraSoKhachHang(const string& duongDan) {
    ifstream file(duongDan);
    if (!file.is_open()) return -1;

    int soKhachHang = 0;
    string line;
    while (getline(file, line)) soKhachHang++;

    file.close();
    return soKhachHang;
}

bool coNhuNhauKhachHang(const KhachHang& k1, const KhachHang& k2) {
    return k1.tenKhachHang == k2.tenKhachHang && k1.soDienThoai == k2.soDienThoai;
}
#include "customer.h"
#include <fstream>

void docFileKhachHang(const string& duongDan, vector<KhachHang>& danhSachKhachHang) {
    ifstream file(duongDan);
    if (!file.is_open()) return;

    KhachHang kh;
    while (file >> kh.tenKhachHang >> kh.soDienThoai >> kh.diemTichLuy) {
        danhSachKhachHang.push_back(kh);
    }

    file.close();
}

void xoaKhachKhoiFile(const string& duongDan, const KhachHang& khachXoa) {
    vector<KhachHang> danhSachKhachHang;
    docFileKhachHang(duongDan, danhSachKhachHang);

    xoaKhachHang(danhSachKhachHang, khachXoa);
    ofstream outFile(duongDan, ofstream::trunc);

    for (const auto& kh : danhSachKhachHang) {
        outFile << kh.tenKhachHang << " " << kh.soDienThoai << " " << kh.diemTichLuy << endl;
    }

    outFile.close();
}

void themKhachHangVaoFile(const string& duongDan, const KhachHang& khach) {
    ofstream file(duongDan, ios::app);
    if (!file.is_open()) return;

    file << kh.tenKhachHang << " " << kh.soDienThoai << " " << kh.diemTichLuy << endl;
    file.close();
}

void themNhieuKhachVaoFile(const vector<KhachHang>& danhSachKhach, const string& duongDan) {
    ofstream file(duongDan, ios::app);
    if (!file.is_open()) return;

    for (const auto& kh : danhSachKhach) {
        file << kh.tenKhachHang << " " << kh.soDienThoai << " " << kh.diemTichLuy << endl;
