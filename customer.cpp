#include "customer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Định nghĩa các phương thức của lớp KhachHang
void KhachHang::chuanHoa() {
    tenKhachHang.clear();
    soDienThoai.clear();
    diemTichLuy = 0;
}

void KhachHang::saoChep(const KhachHang &khachNguon) {
    tenKhachHang = khachNguon.tenKhachHang;
    soDienThoai = khachNguon.soDienThoai;
    diemTichLuy = khachNguon.diemTichLuy;
}

void KhachHang::themNhieu(vector<KhachHang>& danhSach, const string &duongDan) {
    ofstream fptr(duongDan, ios::app);
    if (!fptr) {
        cerr << "Không thể thêm khách hàng vào file\n";
        return;
    }
    for (const auto& kh : danhSach) {
        fptr << kh.tenKhachHang << "," << kh.soDienThoai << "," << kh.diemTichLuy << "\n";
    }
    fptr.close();
}

int KhachHang::kiemTraSo(const string &duongDan) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở đường dẫn để kiểm tra số lượng khách hàng\n";
        return -1;
    }
    int soKhachHang = 0;
    fptr.ignore(10000, '\n');
    string line;
    while (getline(fptr, line)) {
        soKhachHang++;
    }
    fptr.close();
    return soKhachHang;
}

void KhachHang::docFile(const string &duongDan, vector<KhachHang>& danhSach) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở đường dẫn để kiểm tra số lượng khách hàng\n";
        return;
    }
    string line;
    fptr.ignore(10000, '\n');
    danhSach.clear();
    while (getline(fptr, line)) {
        KhachHang kh;
        istringstream iss(line);
        string diemTichLuyStr;
        getline(iss, kh.tenKhachHang, ',');
        getline(iss, kh.soDienThoai, ',');
        getline(iss, diemTichLuyStr);
        kh.diemTichLuy = stof(diemTichLuyStr);
        danhSach.push_back(kh);
    }
    fptr.close();
}
void KhachHang::xoaKhachHang(vector<KhachHang>& danhSach, const KhachHang& khachXoa) {
    auto it = find_if(danhSach.begin(), danhSach.end(), [&khachXoa](const KhachHang& kh) {
        return kh.tenKhachHang == khachXoa.tenKhachHang && kh.soDienThoai == khachXoa.soDienThoai;
    });
    if (it != danhSach.end()) {
        danhSach.erase(it);
    }

    ofstream fptr("output.txt", ios::out);
    if (!fptr) {
        cerr << "Không thể mở file để xóa khách hàng\n";
        return;
    }
    for (const auto& kh : danhSach) {
        fptr << kh.tenKhachHang << "," << kh.soDienThoai << "," << kh.diemTichLuy << "\n";
    }
    fptr.close();
}

void KhachHang::themKhachHangVaoFile(const string &duongDan, const KhachHang& khach) {
    ofstream fptr(duongDan, ios::app);
    if (!fptr) {
        cerr << "Không thể thêm khách hàng vào file\n";
        return;
    }
    fptr << kh.tenKhachHang << "," << kh.soDienThoai << "," << kh.diemTichLuy << "\n";
    fptr.close();
}

void KhachHang::themNhieuKhachVaoFile(const vector<KhachHang>& danhSach, const string &duongDan) {
    ofstream fptr(duongDan, ios::app);
    if (!fptr) {
        cerr << "Không thể thêm khách hàng vào file\n";
        return;
    }
    for (const auto& kh : danhSach) {
        fptr << kh.tenKhachHang << "," << kh.soDienThoai << "," << kh.diemTichLuy << "\n";
    }
    fptr.close();
}

void themKhachHang(vector<KhachHang>& danhSach, const KhachHang& khachHangMoi) {
    danhSach.push_back(khachHangMoi);
}

void xemDanhSachKhachHang(const vector<KhachHang>& danhSach) {
    for (const auto& kh : danhSach)
        cout << "Tên: " << kh.tenKhachHang << ", Số Điện Thoại: " << kh.soDienThoai << ", Điểm Tích Lũy: " << kh.diemTichLuy << endl;
}

void timKiemKhachHang(const vector<KhachHang>& danhSach) {
    string ten;
    cout << "Nhập tên khách hàng cần tìm: ";
    getline(cin, ten);
    for (const auto& kh : danhSach) {
        if (kh.tenKhachHang == ten) {
            cout << "Tên: " << kh.tenKhachHang << ", Số Điện Thoại: " << kh.soDienThoai << ", Điểm Tích Lũy: " << kh.diemTichLuy << endl;
            return;
        }
    }
    cout << "Không tìm thấy khách hàng này." << endl;
}

void docFileKhachHang(const string& duongDan, vector<KhachHang>& danhSach) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở file để đọc danh sách khách hàng" << endl;
        return;
    }
    KhachHang kh;
    while (fptr >> kh.tenKhachHang >> kh.soDienThoai >> kh.diemTichLuy) {
        danhSach.push_back(kh);
    }
    fptr.close();
}
