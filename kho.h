#pragma once
#include "general.h"
#include <vector>
#include <string>
using namespace std;

// Class quản lý nguyên liệu
class NguyenLieu {
public:
    string ten;
    string donVi;  // kg, hộp, trái, gói
    float soLuong;
    float gia;  // Tính trên một đơn vị

    NguyenLieu(const string& ten, const string& donVi, float soLuong, float gia);
    NguyenLieu(const NguyenLieu& source);
    bool coNhuNhau(const NguyenLieu& other) const;
    void saoChepTu(const NguyenLieu& source);
    void nhapThongTin();
};

// Class quản lý kho
class QuanLyKho {
public:
    vector<NguyenLieu> kho;

    void chuanHoaKho();
    void saoChepNguyenLieu(int indexNhan, int indexNguon);
    void themNhieuNguyenLieuVaoFile(const string& duongDan);
    int kiemTraSoNguyenLieu(const string& duongDan);
    void docFileKho(const string& duongDan); 
    void xoaNguyenLieuKhoiFile(int index, const string& duongDan);
    void themNguyenLieuVaoFile(int index, const string& duongDan);
    void hienThiKho();
    void themNguyenLieu(const NguyenLieu& nguyenLieuMoi);
    void xoaNguyenLieu(int index);
    void layNguyenLieu(int index, int soMon);
    void nhapTenNguyenLieu(int index);
    void timKiemNguyenLieu();
    void capNhatKhoTuFile(const string& duongDan);
    void capNhatKhoTuMang(const string& duongDan);
};

#endif 
