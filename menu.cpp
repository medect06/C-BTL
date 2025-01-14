#include "general.h"
#include "menu.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Định nghĩa các phương thức của lớp MonAn
void MonAn::chuanHoa() {
    tenMon.clear();
    gia = 0;
    nguyenLieu.clear();
}

void MonAn::saoChep(const MonAn &monNguon) {
    tenMon = monNguon.tenMon;
    gia = monNguon.gia;
    nguyenLieu = monNguon.nguyenLieu;
}

void MonAn::themNhieuMonAnVaoFile(const vector<MonAn>& danhSachMonAn, const string& duongDan) {
    ofstream fptr(duongDan, ios::app);
    if (!fptr) {
        cerr << "Không thể thêm món ăn vào file\n";
        return;
    }
    for (const auto& mon : danhSachMonAn) {
        fptr << mon.tenMon << "," << mon.gia << ",";
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.tenNguyenLieu << ",";
        }
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.donVi << ",";
        }
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.soLuong << ",";
        }
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.gia << ",";
        }
        fptr << mon.nguyenLieu.size() << "\n";
    }
    fptr.close();
}

int MonAn::kiemTraSoMonAn(const string &duongDan) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở đường dẫn để kiểm tra số lượng món ăn trong menu\n";
        return -1;
    }
    int soMonAn = 0;
    string line;
    while (getline(fptr, line)) {
        soMonAn++;
    }
    fptr.close();
    return soMonAn;
}

void MonAn::docFileMenu(const string &duongDan, vector<MonAn>& danhSachMonAn) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở đường dẫn để kiểm tra số lượng món ăn trong menu\n";
        return;
    }
    string line;
    danhSachMonAn.clear();
    while (getline(fptr, line)) {
        MonAn mon;
        istringstream iss(line);
        string giaStr;
        getline(iss, mon.tenMon, ',');
        getline(iss, giaStr, ',');
        mon.gia = stof(giaStr);
        while (getline(iss, giaStr, ',')) {
            NguyenLieu nl;
            nl.tenNguyenLieu = giaStr;
            getline(iss, nl.donVi, ',');
            getline(iss, giaStr, ',');
            nl.soLuong = stof(giaStr);
            getline(iss, giaStr, ',');
            nl.gia = stof(giaStr);
            mon.nguyenLieu.push_back(nl);
        }
        getline(iss, giaStr);
        mon.nguyenLieu.resize(stoi(giaStr));
        danhSachMonAn.push_back(mon);
    }
    fptr.close();
}

// Định nghĩa các hàm chức năng liên quan tới MonAn
void themMonAn(vector<MonAn>& danhSach, const MonAn& monMoi) {
    danhSach.push_back(monMoi);
}

void hienThiMenu(const vector<MonAn>& danhSach) {
    cout << "Danh sách món ăn:\n";
    cout << "Tên món\t\tGiá\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        cout << danhSach[i].tenMon << "\t" << danhSach[i].gia << "\n";
    }
}
void timKiemMon(const vector<MonAn>& danhSach) {
    string tenMon;
    cout << "Nhập tên món ăn cần tìm: ";
    getline(cin, tenMon);
    for (const auto& mon : danhSach) {
        if (mon.tenMon == tenMon) {
            cout << "Tên món: " << mon.tenMon << ", Giá: " << mon.gia << "\n";
            return;
        }
    }
    cout << "Không tìm thấy món ăn này.\n";
}

void nhapThongTinMonAn(MonAn& monAn, const vector<NguyenLieu>& kho) {
    cout << "Nhập tên món: ";
    getline(cin, monAn.tenMon);
    cout << "Nhập giá món: ";
    cin >> monAn.gia;
    cin.ignore();
    int soNguyenLieu;
    cout << "Nhập số nguyên liệu: ";
    cin >> soNguyenLieu;
    cin.ignore();

    for (int i = 0; i < soNguyenLieu; ++i) {
        NguyenLieu nl;
        cout << "Nhập tên nguyên liệu: ";
        getline(cin, nl.tenNguyenLieu);
        auto it = find_if(kho.begin(), kho.end(), [&nl](const NguyenLieu& x) {
            return x.tenNguyenLieu == nl.tenNguyenLieu;
        });
        if (it == kho.end()) {
            cout << "Nguyên liệu không tồn tại trong kho.\n";
            continue;
        }
        nl.donVi = it->donVi;
        nl.gia = it->gia;
        cout << "Nhập số lượng: ";
        cin >> nl.soLuong;
        cin.ignore();
        monAn.nguyenLieu.push_back(nl);
    }
}

void xoaMonAnTrongMang(vector<MonAn>& menu, const MonAn& monXoa) {
    menu.erase(remove_if(menu.begin(), menu.end(), [&monXoa](const MonAn& mon) {
        return mon.tenMon == monXoa.tenMon;
    }), menu.end());
}

void themMonAnVaoMang(vector<MonAn>& menu, const MonAn& monThem) {
    menu.push_back(monThem);
}

void capNhatMonAnTuFile(vector<MonAn>& menu, const string& duongDan) {
    docFileMenu(duongDan, menu);
}

void capNhatMonAnTuMang(vector<MonAn>& menu, const string& duongDan) {
    ofstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở file để cập nhật món ăn\n";
        return;
    }
    for (const auto& mon : menu) {
        fptr << mon.tenMon << "," << mon.gia << ",";
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.tenNguyenLieu << ",";
        }
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.donVi << ",";
        }
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.soLuong << ",";
        }
        for (const auto& nl : mon.nguyenLieu) {
            fptr << nl.gia << ",";
        }
        fptr << mon.nguyenLieu.size() << "\n";
    }
    fptr.close();
}
