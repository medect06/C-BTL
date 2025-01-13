#include "general.h"
#include "kho.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class NguyenLieu {
public:
    char ten[DO_DAI_TEN];
    char donVi[DO_DAI_DONVI];
    float soLuong, gia;

    void chuanHoa() {
        strncpy(ten, "0", 2);
        strncpy(donVi, "0", 2);
        soLuong = gia = 0;
    }

    void saoChep(const NguyenLieu &nguyenLieuNguon) {
        strncpy(ten, nguyenLieuNguon.ten, DO_DAI_TEN - 1);
        strncpy(donVi, nguyenLieuNguon.donVi, DO_DAI_DONVI - 1);
        soLuong = nguyenLieuNguon.soLuong;
        gia = nguyenLieuNguon.gia;
    }

    static void themNhieu(vector<NguyenLieu>& danhSach, const string &duongDan) {
        ofstream fptr(duongDan, ios::app);
        if (!fptr) {
            cerr << "Khong the them nguyen lieu vao file\n";
            return;
        }
        for (const auto& nl : danhSach) {
            fptr << nl.ten << "," << nl.donVi << "," << nl.soLuong << "," << nl.gia << "\n";
        }
        fptr.close();
    }

    static int kiemTraSo(const string &duongDan) {
        ifstream fptr(duongDan);
        if (!fptr) {
            cerr << "Khong the mo duong dan de kiem tra so luong nguyen lieu\n";
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

    static void docFile(const string &duongDan, vector<NguyenLieu>& kho) {
        ifstream fptr(duongDan);
        if (!fptr) {
            cerr << "Khong the mo duong dan de kiem tra so luong nguyen lieu\n";
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

    static void xoaNguyenLieu(vector<NguyenLieu>& kho, const NguyenLieu& nlXoa) {
        auto it = find_if(kho.begin(), kho.end(), [&nlXoa](const NguyenLieu& nl) {
            return strcmp(nl.ten, nlXoa.ten) == 0;
        });
        if (it != kho.end()) {
            kho.erase(it);
        }
        ofstream fptr("output.txt", ios::out);
        if (!fptr) {
            cerr << "Khong the mo file kho de xoa nguyen lieu\n";
            return;
        }
        for (const auto& nl : kho) {
            fptr << nl.ten << "," << nl.donVi << "," << nl.soLuong << "," << nl.gia << "\n";
        }
        fptr.close();
    }
};
void themNguyenLieu(vector<NguyenLieu>& danhSach, const NguyenLieu& nguyenLieuMoi) {
    if (danhSach.size() >= MAX_NGUYEN_LIEU) {
        cout << "Kho da day, khong the them nguyen lieu moi!\n";
        return;
    }

    auto it = find_if(danhSach.begin(), danhSach.end(), [&nguyenLieuMoi](const NguyenLieu& nl) {
        return strcmp(nl.ten, nguyenLieuMoi.ten) == 0;
    });

    if (it != danhSach.end()) {
        cout << "Nguyen lieu nay da co trong kho\n";
        return;
    }

    danhSach.push_back(nguyenLieuMoi);
    cout << "Da them nguyen lieu vao mang\n";
}

void hienThiKho(const vector<NguyenLieu>& danhSach) {
    if (danhSach.empty()) {
        cout << "Chua co nguyen lieu\n";
        return;
    }

    cout << "DANH SACH NGUYEN LIEU TRONG KHO:\n"
         << setw(3) << "STT" << " " << setw(25) << "Ten Nguyen Lieu" << " "
         << setw(10) << "Don Vi" << " " << setw(10) << "So Luong\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        cout << setw(3) << i + 1 << " " << setw(25) << danhSach[i].ten << " "
             << setw(10) << danhSach[i].donVi << " " << setw(10) << fixed << setprecision(2)
             << danhSach[i].soLuong << "\n";
    }
}

void layNguyenLieu(vector<NguyenLieu>& danhSach, const NguyenLieu& nlSuDung, int soMon) {
    for (auto& nl : danhSach) {
        if (strcmp(nlSuDung.ten, nl.ten) == 0) {
            if (nlSuDung.soLuong * soMon <= nl.soLuong) {
                nl.soLuong -= nlSuDung.soLuong * soMon;
                return;
            }
            cout << "Khong the tru di nhieu nguyen lieu nhu vay\n";
            return;
        }
    }
}

void timKiemNguyenLieu(const vector<NguyenLieu>& danhSach) {
    if (danhSach.empty()) {
        cout << "Chua co nguyen lieu\n";
        return;
    }

    char ten[DO_DAI_TEN];
    cout << "Nhap ten nguyen lieu: ";
    cin.getline(ten, DO_DAI_TEN);
    cout << "\nDanh sach nguyen lieu tim duoc theo ten '" << ten << "':\n"
         << setw(3) << "STT" << " " << setw(25) << "Ten Nguyen Lieu" << " "
         << setw(10) << "Don Vi" << " " << setw(10) << "So Luong\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        if (strstr(danhSach[i].ten, ten)) {
            cout << setw(3) << i + 1 << " " << setw(25) << danhSach[i].ten << " "
                 << setw(10) << danhSach[i].donVi << " " << setw(10) << fixed << setprecision(2)
                 << danhSach[i].soLuong << "\n";
        }
    }
}
