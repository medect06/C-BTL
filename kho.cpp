#include "kho.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Định nghĩa các phương thức của lớp NguyenLieu
void NguyenLieu::chuanHoa() {
    ten.clear();
    donVi.clear();
    soLuong = gia = 0;
}

void NguyenLieu::saoChep(const NguyenLieu &nguyenLieuNguon) {
    ten = nguyenLieuNguon.ten;
    donVi = nguyenLieuNguon.donVi;
    soLuong = nguyenLieuNguon.soLuong;
    gia = nguyenLieuNguon.gia;
}

void NguyenLieu::themNhieu(vector<NguyenLieu>& danhSach, const string &duongDan) {
    ofstream fptr(duongDan, ios::app);
    if (!fptr) {
        cerr << "Không thể thêm nguyên liệu vào file\n";
        return;
    }
    for (const auto& nl : danhSach) {
        fptr << nl.ten << "," << nl.donVi << "," << nl.soLuong << "," << nl.gia << "\n";
    }
    fptr.close();
}

int NguyenLieu::kiemTraSo(const string &duongDan) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở đường dẫn để kiểm tra số lượng nguyên liệu\n";
        return -1;
    }
    int soNguyenLieu = 0;
    fptr.ignore(10000, '\n');
    string line;
    while (getline(fptr, line)) {
        soNguyenLieu++;
    }
    fptr.close();
    return soNguyenLieu;
}

void NguyenLieu::docFile(const string &duongDan, vector<NguyenLieu>& kho) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở đường dẫn để kiểm tra số lượng nguyên liệu\n";
        return;
    }
    string line;
    fptr.ignore(10000, '\n');
    kho.clear();
    while (getline(fptr, line)) {
        NguyenLieu nl;
        istringstream iss(line);
        string soLuongStr, giaStr;
        getline(iss, nl.ten, ',');
        getline(iss, nl.donVi, ',');
        getline(iss, soLuongStr, ',');
        getline(iss, giaStr);
        nl.soLuong = stof(soLuongStr);
        nl.gia = stof(giaStr);
        kho.push_back(nl);
    }
    fptr.close();
}

void NguyenLieu::xoaNguyenLieu(vector<NguyenLieu>& kho, const NguyenLieu& nlXoa) {
    auto it = find_if(kho.begin(), kho.end(), [&nlXoa](const NguyenLieu& nl) {
        return nl.ten == nlXoa.ten;
    });
    if (it != kho.end()) {
        kho.erase(it);
    }

    ofstream fptr("output.txt", ios::out);
    if (!fptr) {
        cerr << "Không thể mở file để xóa nguyên liệu\n";
        return;
    }
    for (const auto& nl : kho) {
        fptr << nl.ten << "," << nl.donVi << "," << nl.soLuong << "," << nl.gia << "\n";
    }
    fptr.close();
}

// Các hàm liên quan tới việc quản lý nguyên liệu trong kho
void themNguyenLieu(vector<NguyenLieu>& danhSach, const NguyenLieu& nguyenLieuMoi) {
    if (danhSach.size() >= MAX_NGUYEN_LIEU) {
        cout << "Kho đã đầy, không thể thêm nguyên liệu mới!\n";
        return;
    }
    auto it = find_if(danhSach.begin(), danhSach.end(), [&nguyenLieuMoi](const NguyenLieu& nl) {
        return nl.ten == nguyenLieuMoi.ten;
    });
    if (it != danhSach.end()) {
        cout << "Nguyên liệu này đã có trong kho\n";
        return;
    }
    danhSach.push_back(nguyenLieuMoi);
    cout << "Đã thêm nguyên liệu vào danh sách\n";
}

void hienThiKho(const vector<NguyenLieu>& danhSach) {
    if (danhSach.empty()) {
        cout << "Chưa có nguyên liệu\n";
        return;
    }
    cout << "DANH SÁCH NGUYÊN LIỆU TRONG KHO:\n"
         << setw(3) << "STT" << " " << setw(25) << "Tên Nguyên Liệu" << " "
         << setw(10) << "Đơn Vị" << " " << setw(10) << "Số Lượng\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        cout << setw(3) << i + 1 << " " << setw(25) << danhSach[i].ten << " "
             << setw(10) << danhSach[i].donVi << " " << setw(10) << fixed << setprecision(2)
             << danhSach[i].soLuong << "\n";
    }
}

void layNguyenLieu(vector<NguyenLieu>& danhSach, const NguyenLieu& nlSuDung, int soMon) {
    for (auto& nl : danhSach) {
        if (nl.ten == nlSuDung.ten) {
            if (nlSuDung.soLuong * soMon <= nl.soLuong) {
                nl.soLuong -= nlSuDung.soLuong * soMon;
                return;
            }
            cout << "Không thể trừ bớt nhiều nguyên liệu như vậy\n";
            return;
        }
    }
}

void timKiemNguyenLieu(const vector<NguyenLieu>& danhSach) {
    if (danhSach.empty()) {
        cout << "Chưa có nguyên liệu\n";
        return;
    }
    string ten;
    cout << "Nhập tên nguyên liệu: ";
    getline(cin, ten);
    cout << "\nDanh sách nguyên liệu tìm được theo tên '" << ten << "':\n"
         << setw(3) << "STT" << " " << setw(25) << ten << " "
         << setw(10) << "Đơn Vị" << " " << setw(10) << "Số Lượng\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].ten.find(ten) != string::npos) {
            cout << setw(3) << i + 1 << " " << setw(25) << danhSach[i].ten << " "
                 << setw(10) << danhSach[i].donVi << " " << setw(10) << fixed << setprecision(2)
                 << danhSach[i].soLuong << "\n";
        }
    }
}
