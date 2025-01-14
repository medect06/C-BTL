#pragma once

#include <vector>
#include <string>
using namespace std;
#include "kho.h"
#include "general.h"

// Cấu trúc món ăn
class MonAn {
public:
    string tenMon;
    float gia;
    vector<NguyenLieu> nguyenLieu;
    
    void chuanHoa(); // Cài đặt mặc định cho món ăn, tránh giá trị rác
    void saoChep(const MonAn& monNguon); // Sao chép thông tin từ món ăn nguồn

    static void themNhieuMonAnVaoFile(const vector<MonAn>& danhSachMonAn, const string& duongDan); // Thêm nhiều đối tượng món ăn vào file
    static int kiemTraSoMonAn(const string& duongDan); // Kiểm tra số món ăn trong file
    static void docFileMenu(const string& duongDan, vector<MonAn>& danhSachMonAn); // Đọc dữ liệu trong file menu ra mảng
    static void xoaMonAnKhoiFile(const string& duongDan, const MonAn& monXoa); // Xóa một món ăn khỏi file
};

// Chức năng liên quan tới vector<MonAn>
void themMonAn(vector<MonAn>& danhSach, const MonAn& monMoi); // Thêm món ăn vào danh sách
void hienThiMenu(const vector<MonAn>& danhSach); // Hiển thị danh sách món ăn trong menu
void timKiemMon(const vector<MonAn>& danhSach); // Tìm kiếm món ăn trong menu
void nhapThongTinMonAn(MonAn& monAn, const vector<NguyenLieu>& kho); // Nhập thông tin cho một đối tượng món ăn
void nhapTenMonAn(MonAn& monAn, const vector<NguyenLieu>& kho); // Nhập tên món ăn để định vị nhanh chóng đối tượng
void themMonAnVaoMang(vector<MonAn>& menu, const MonAn& monThem); // Thêm một món ăn vào mảng
void xoaMonAnTrongMang(vector<MonAn>& menu, const MonAn& monXoa); // Xóa một món ăn khỏi mảng
void capNhatMonAnTuFile(vector<MonAn>& menu, const string& duongDan); // Cập nhật món ăn từ file
void capNhatMonAnTuMang(vector<MonAn>& menu, const string& duongDan); // Cập nhật món ăn từ mảng
