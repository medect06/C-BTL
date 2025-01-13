#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class KhachHang {
public:
    string tenKhachHang;
    string soDienThoai;
    float diemTichLuy = 0.0;

    KhachHang() {}
    KhachHang(string ten, string sdt, float diem) : tenKhachHang(ten), soDienThoai(sdt), diemTichLuy(diem) {}
};

void themKhachHang(vector<KhachHang>& danhSachKhachHang, const KhachHang& khachHangMoi);
void xemDanhSachKhachHang(const vector<KhachHang>& danhSachKhachHang);
void timKiemKhachHang(const vector<KhachHang>& danhSachKhachHang);
void xoaKhachHang(vector<KhachHang>& danhSachKhach, const KhachHang& khachXoa);
void nhapThongTinKhach(KhachHang& khachHang);
void nhapTenSDTKhach(KhachHang& khachHang);
void capNhatKhachTuMang(vector<KhachHang>& danhSach, const string& duongDan);
void capNhatKhachTuFile(vector<KhachHang>& danhSach, const string& duongDan);
void layDiemTichLuy(const vector<KhachHang>& danhSachKhachHang, KhachHang& khach);
void chuanHoaKhachHang(vector<KhachHang>& danhSachKhachHang);
void saoChepKhachHang(KhachHang& khachNhan, const KhachHang& khachNguon);
int kiemTraSoKhachHang(const string& duongDan);
bool coNhuNhauKhachHang(const KhachHang& k1, const KhachHang& k2);
void docFileKhachHang(const string& duongDan, vector<KhachHang>& danhSachKhachHang);
void xoaKhachKhoiFile(const string& duongDan, const KhachHang& khachXoa);
void themKhachHangVaoFile(const string& duongDan, const KhachHang& khach);
void themNhieuKhachVaoFile(const vector<KhachHang>& danhSachKhach, const string& duongDan);

