#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Constants
const string NGAN_PHAN_TU_CSV = ",";
const string PLACEHOLDER_QUAN_LY = "<placeholder>\n";
const int SO_DOI_TUONG_LAM_VIEC = 4;
const string MANAGING_FILE = "./pathFile.txt";
const int MAX_DONG_DU_LIEU = 1000;
const int MAX_FILE_PATH_LENGTH = 200;

const int LUA_CHON_KHACH_HANG = 1;
const int LUA_CHON_HOA_DON = 2;
const int LUA_CHON_KHO = 3;
const int LUA_CHON_MENU = 4;

const int SO_LUONG_TOI_DA_MOI_MON = 10000;
const int MAX_HOA_DON = 100;
const string HOA_DON_HEADER = "tenKhachHang,soDienThoai,diemTichLuyKhach,...";
const int MAX_ARRAY_LENGTH_HOA_DON = 3000;

const int MAX_KHACH_HANG = 100;
const string KHACH_HANG_HEADER = "tenKhachHang,soDienThoai,diemTichLuy\n";
const int DO_DAI_TEN_KHACH = 50;
const int DO_DAI_SO_DIEN_THOAI = 15;

const string KHO_HEADER = "tenNguyenLieu,donVi,soLuong,gia\n";
const int MAX_DO_DAI_TEN_NGUYEN_LIEU = 50; 
const int MAX_DO_DAI_CHUOI_DON_VI = 15;
const int MAX_ARRAY_LENGTH_KHO = 70;
const int MAX_NGUYEN_LIEU = 20;

const string MENU_HEADER = "tenMon,gia,...";
const int MAX_MON = 30;
const int DO_DAI_TEN_MON = 50;
const int MAX_ARRAY_LENGTH_MENU = 3000;

// Class Ngay
class Ngay {
public:
    int ngay;
    int thang;
    int nam;

    Ngay() = default;
    Ngay(int n, int t, int y) : ngay(n), thang(t), nam(y) {}

    bool coNhuNhauNgay(const Ngay& other) const {
        return ngay == other.ngay && thang == other.thang && nam == other.nam;
    }

    void saoChepNgay(const Ngay& source) {
        ngay = source.ngay;
        thang = source.thang;
        nam = source.nam;
    }
};

// Class XuLyFileQuanLy
class XuLyFileQuanLy {
public:
    static void docFileQuanLi(int luaChon, string& duongDan);
    static void capNhatFileQuanLi(int luaChon, const string& duongDanMoi);
};

// Wallper for saferScanf
void saferScanf(const string& formatString, void* addr);

#endif /* GENERAL_HPP_ */
