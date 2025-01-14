#pragma once
#include <vector>
#include <string>
#include "customer.h"
#include "general.h"
#include "menu.h"

using namespace std;

class HoaDon {
public:
    KhachHang khachHang;
    Ngay ngayNhapDon; // Sử dụng struct Ngay từ file general.h
    vector<int> soLuongMon;
    vector<string> tenMonGoi;
    vector<float> giaMonGoi;
    int soMonGoi;
    float tongTien;
    float tienThua;
    float tienNguyenLieu;

    void chuanHoa(); // Khởi tạo giá trị mặc định
    void saoChep(const HoaDon& hoaDonNguon); // Deep-copy hóa đơn nguồn

    static int kiemTraSoHoaDon(const string& duongDan); // Đọc số hóa đơn trong file
    static bool coNhuNhauHoaDon(const HoaDon& h1, const HoaDon& h2); // Kiểm tra xem hai hóa đơn có hoàn toàn cùng thuộc tính không
    static void docFileHoaDon(const string& duongDan, vector<HoaDon>& danhSachHoaDon); // Lấy dữ liệu trong file hóa đơn vào mảng
    static void xoaHoaDonKhoiFile(const string& duongDan, const HoaDon& hoaDonXoa); // Xóa một hóa đơn khỏi file
    static void themHoaDonVaoFile(const HoaDon& hoaDon, const string& duongDan); // Thêm một hóa đơn vào file
    static void xemHoaDon(const vector<HoaDon>& danhSachHoaHon); // Hiển thị danh sách hóa đơn
    static void timKiemHoaDon(const vector<HoaDon>& danhSachHoaDon); // Tìm kiếm hóa đơn trong mảng
    static void thanhToan(const vector<MonAn>& menu, vector<HoaDon>& danhSachHoaDon, int* soHoaDon, 
                          const vector<KhachHang>& danhSachKhachHang, int* soKhachHang,
                          const vector<NguyenLieu>& kho, const string& duongDanFileKhach); // Thực hiện thanh toán
};

void xoaHoaDon(vector<HoaDon>& danhSach, const HoaDon& hoaDonXoa); // Xóa hóa đơn khỏi mảng
void nhapThongTinHoaDon(HoaDon& hoaDon, const vector<MonAn>& menu);
void capNhatHoaDonTuFile(vector<HoaDon>& danhSachHoaDon, const string& duongDan, int* soHoaDonFile); 
void capNhatHoaDonTuMang(vector<HoaDon>& danhSachHoaDon, const string& duongDan, int* soHoaDonFile);
