#pragma once
#include <vector>
#include <string>
using namespace std;

class NguyenLieu {
public:
    char ten[DO_DAI_TEN];
    char donVi[DO_DAI_DONVI];
    float soLuong, gia;
    void chuanHoa();                          //Cài đặt mặc định cho nguyên liệu, tránh giá trị rác
    void saoChep(const NguyenLieu &nguyenLieuNguon);        //Sao chép thông tin từ nguyên liệu nguồn
    static void themNhieu(vector<NguyenLieu>& danhSach, const string &duongDan); //Thêm nhiều nguyên liệu vào file
    static int kiemTraSo(const string &duongDan);                       //Kiểm tra số lượng nguyên liệu trong file 
    static void docFile(const string &duongDan, vector<NguyenLieu>& kho);  //Đọc dữ liệu từ file
    static void xoaNguyenLieu(vector<NguyenLieu>& kho, const NguyenLieu& nlXoa); //Xóa nguyên liệu khỏi file
};

// Chức năng liên quan tới vector<NguyenLieu>
void themNguyenLieu(vector<NguyenLieu>& danhSach, 
                   const NguyenLieu& nguyenLieuMoi);   //Thêm nguyên liệu vào danh sách

void hienThiKho(const vector<NguyenLieu>& danhSach);             //Hiển thị danh sách nguyên liệu trong kho
void layNguyenLieu(vector<NguyenLieu>& danhSach, 
                   const NguyenLieu& nlSuDung, int soMon); //Lấy nguyên liệu từ kho để sử dụng
void timKiemNguyenLieu(const vector<NguyenLieu>& danhSach);       //Tìm kiếm nguyên liệu trong kho
