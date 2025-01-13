#pragma once

#include <iostream>
#include <vector>
#include <string>

// Cac constant de lam viec voi file
const std::string NGAN_PHAN_TU_CSV = ",";
const std::string PLACEHOLDER_QUAN_LY = "<placeholder>\n"; // Placeholder de xay dung cau truc file quan ly
const int SO_DOI_TUONG_LAM_VIEC = 4; // kho, khach, hoa don, menu
const std::string MANAGING_FILE = "./pathFile.txt"; // Duong dan den file luu tru duong dan
const int MAX_DONG_DU_LIEU = 1000; // So dong du lieu toi da co the doc tu file
const int MAX_FILE_PATH_LENGTH = 200; // Do dai toi da cua duong dan file

// Cac constant quy dinh lua chon doi tuong
enum LuaChonDoiTuong {
    KHACH_HANG = 1,
    HOA_DON = 2,
    KHO = 3,
    MENU = 4
};

// Cac constant cho doi tuong hoa don
const int SO_LUONG_TOI_DA_MOI_MON = 10000; // So luong mon toi da co the tao dua vao nguyen lieu trong kho
const int MAX_HOA_DON = 100; // So luong toi da cua mang hoa don
const std::string HOA_DON_HEADER = "tenKhachHang,soDienThoai,diemTichLuyKhach,"
                                    "ngayNhap,thangNhap,namNhap,";
const int MAX_ARRAY_LENGTH_HOA_DON = 3000; // Do dai toi da cua chuoi thong tin hoa don

// Cac constant cho doi tuong khach hang
const int MAX_KHACH_HANG = 100; // So luong toi da cua mang khach hang
const int MAX_ARRAY_LENGTH_KHACH_HANG = 75; // Do dai toi da cua chuoi thong tin khach hang
const std::string KHACH_HANG_HEADER = "tenKhachHang,soDienThoai,diemTichLuy\n";
const int DO_DAI_TEN_KHACH = 50; // Do dai toi da cua ten khach hang
const int DO_DAI_SO_DIEN_THOAI = 15; // Do dai toi da cua so dien thoai

// Cac constant cho doi tuong kho
const std::string KHO_HEADER = "tenNguyenLieu,donVi,soLuong,gia\n";
const int MAX_DO_DAI_TEN_NGUYEN_LIEU = 50;
const int MAX_DO_DAI_CHUOI_DON_VI = 15;
const int MAX_ARRAY_LENGTH_KHO = 70;
const int MAX_NGUYEN_LIEU = 20; // So luong nguyen lieu toi da

// Cac constant cho doi tuong menu
const std::string MENU_HEADER = "tenMon,gia,";
const int MAX_MON = 30; // So luong mon toi da trong menu
const int DO_DAI_TEN_MON = 50; // Do dai toi da cua ten mon
const int MAX_ARRAY_LENGTH_MENU = 3000; // Do dai toi da cua chuoi thong tin menu

// Lop dinh nghia doi tuong ngay
class Ngay {
public:
    int ngay;
    int thang;
    int nam;

    Ngay(int d = 1, int m = 1, int y = 1970) : ngay(d), thang(m), nam(y) {}

    // Kiem tra xem hai ngay co trung nhau khong
    bool coNhuNhau(const Ngay& other) const {
        return ngay == other.ngay && thang == other.thang && nam == other.nam;
    }

    // Sao chep du lieu tu mot doi tuong ngay khac
    void saoChep(const Ngay& other) {
        ngay = other.ngay;
        thang = other.thang;
        nam = other.nam;
    }
};

// Ham doc file quan ly duong dan
void docFileQuanLi(int luaChon, std::string& duongDan) {
    // TODO: Implement ham doc duong dan tu file quan ly
}

// Ham cap nhat file quan ly
void capNhatFileQuanLi(int luaChon, const std::string& duongDanMoi) {
    // TODO: Implement ham cap nhat duong dan trong file quan ly
}

// Ham bo tro nhap an toan
void saferScanf(const std::string& formatString, void* addr) {
    // TODO: Implement ham nhap du lieu an toan
}

// Ham xem danh sach (Template de co the dung cho nhieu loai doi tuong)
template <typename DocFileFunc, typename KiemTraSoLuongFunc, typename HienThiFunc>
void xemDanhSach(DocFileFunc docFile, KiemTraSoLuongFunc kiemTraSoLuong, HienThiFunc hienThi, 
                 const std::string& fileQuanLi, int soLuongHienTai, int doLonVat, void* danhSachHienTai) {
    // TODO: Implement ham xem danh sach
}

// TODO: Them cac ham them, xoa, cap nhat, tim kiem du lieu voi thiet ke template de tai su dung code.
