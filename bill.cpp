#include "general.h"
#include "menu.h"
#include "bill.h"

void HoaDon::chuanHoa() {
    khachHang.chuanHoa();
    ngayNhapDon = {0, 0, 0};
    soLuongMon.assign(MAX_MON, 0);
    tenMonGoi.assign(MAX_MON, "");
    giaMonGoi.assign(MAX_MON, 0);
    soMonGoi = 0;
    tongTien = 0;
    tienThua = 0;
    tienNguyenLieu = 0;
}

void HoaDon::saoChep(const HoaDon& hoaDonNguon) {
    khachHang = hoaDonNguon.khachHang;
    ngayNhapDon = hoaDonNguon.ngayNhapDon;
    soLuongMon = hoaDonNguon.soLuongMon;
    tenMonGoi = hoaDonNguon.tenMonGoi;
    giaMonGoi = hoaDonNguon.giaMonGoi;
    soMonGoi = hoaDonNguon.soMonGoi;
    tongTien = hoaDonNguon.tongTien;
    tienThua = hoaDonNguon.tienThua;
    tienNguyenLieu = hoaDonNguon.tienNguyenLieu;
}
int HoaDon::kiemTraSoHoaDon(const string& duongDan) {
    ifstream fptr(duongDan);
    int soHoaDon = 0;
    string line;
    while(getline(fptr, line)) {
        soHoaDon++;
    }
    return soHoaDon;
}

bool HoaDon::coNhuNhauHoaDon(const HoaDon& h1, const HoaDon& h2) {
    return h1.khachHang == h2.khachHang && h1.ngayNhapDon == h2.ngayNhapDon;
}

void HoaDon::docFileHoaDon(const string& duongDan, vector<HoaDon>& danhSachHoaDon) {
    ifstream fptr(duongDan);
    string line;
    while(getline(fptr, line)) {
        HoaDon hoaDon;
        istringstream iss(line);
        iss >> hoaDon.khachHang.tenKhachHang >> hoaDon.khachHang.soDienThoai >> hoaDon.khachHang.diemTichLuy;
        danhSachHoaDon.push_back(hoaDon);
    }
}

void HoaDon::xoaHoaDonKhoiFile(const string& duongDan, const HoaDon& hoaDonXoa) {
    ifstream fptrIn(duongDan);
    ofstream fptrOut("temp.txt");
    string line;
    while(getline(fptrIn, line)) {
        HoaDon hoaDon;
        istringstream iss(line);
        iss >> hoaDon.khachHang.tenKhachHang >> hoaDon.khachHang.soDienThoai >> hoaDon.khachHang.diemTichLuy;
        if (!coNhuNhauHoaDon(hoaDon, hoaDonXoa)) {
            fptrOut << line << endl;
        }
    }
    fptrIn.close();
    fptrOut.close();
    remove(duongDan.c_str());
    rename("temp.txt", duongDan.c_str());
}
void HoaDon::themHoaDonVaoFile(const HoaDon& hoaDon, const string& duongDan) {
    ofstream fptr(duongDan, ios::app);
    fptr << hoaDon.khachHang.tenKhachHang << " " 
         << hoaDon.khachHang.soDienThoai << " " 
         << hoaDon.khachHang.diemTichLuy << endl;
}

void HoaDon::xemHoaDon(const vector<HoaDon>& danhSachHoaDon) {
    for (const auto& hoaDon : danhSachHoaDon) {
        cout << "Ten: " << hoaDon.khachHang.tenKhachHang << ", "
             << "SDT: " << hoaDon.khachHang.soDienThoai << ", "
             << "Diem: " << hoaDon.khachHang.diemTichLuy << endl;
    }
}

void HoaDon::timKiemHoaDon(const vector<HoaDon>& danhSachHoaDon) {
    string tenKhach;
    cout << "Nhập tên khách hàng cần tìm: ";
    cin >> tenKhach;
    for (const auto& hoaDon : danhSachHoaDon) {
        if (hoaDon.khachHang.tenKhachHang == tenKhach) {
            cout << "Tìm thấy: " << hoaDon.khachHang.tenKhachHang << ", "
                 << hoaDon.khachHang.soDienThoai << ", "
                 << hoaDon.khachHang.diemTichLuy << endl;
            return;
        }
    }
    cout << "Không tìm thấy hóa đơn nào của khách hàng tên " << tenKhach << endl;
}

void HoaDon::thanhToan(const vector<MonAn>& menu, vector<HoaDon>& danhSachHoaDon, int *soHoaDon, 
                          const vector<KhachHang>& danhSachKhachHang, int *soKhachHang,
                          const vector<NguyenLieu>& kho, const string& duongDanFileKhach) {
    // 1. Load thông tin hóa đơn
    // 2. Tính tổng tiền
    // 3. Thêm hóa đơn vào danh sách
    // 4. Cập nhật file khách hàng
    // (Code logic chi tiết ở đây)
}
void xoaHoaDon(vector<HoaDon>& danhSach, const HoaDon& hoaDonXoa) {
    auto it = remove_if(danhSach.begin(), danhSach.end(), [&hoaDonXoa](const HoaDon& hoaDon) {
        return HoaDon::coNhuNhauHoaDon(hoaDon, hoaDonXoa);
    });
    danhSach.erase(it, danhSach.end());
}

void nhapThongTinHoaDon(HoaDon& hoaDon, const vector<MonAn>& menu) {
    cout << "Nhập tên khách hàng: ";
    cin >> hoaDon.khachHang.tenKhachHang;
    cout << "Nhập số điện thoại: ";
    cin >> hoaDon.khachHang.soDienThoai;
    hoaDon.soMonGoi = 0;
    // (Nhập các thông tin khác của hóa đơn)
}


void HoaDon::capNhatHoaDonTuFile(vector<HoaDon>& danhSachHoaDon, const string& duongDan, int* soHoaDonFile) {
    ifstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở file để cập nhật từ file!" << endl;
        return;
    }
    danhSachHoaDon.clear();
    HoaDon hoaDon;
    while (fptr >> hoaDon.khachHang.tenKhachHang >> hoaDon.khachHang.soDienThoai >> hoaDon.khachHang.diemTichLuy) {
        danhSachHoaDon.push_back(hoaDon);
    }
    *soHoaDonFile = danhSachHoaDon.size();
}

void HoaDon::capNhatHoaDonTuMang(vector<HoaDon>& danhSachHoaDon, const string& duongDan, int* soHoaDonFile) {
    ofstream fptr(duongDan);
    if (!fptr) {
        cerr << "Không thể mở file để cập nhật từ mảng!" << endl;
        return;
    }
    for (const auto& hoaDon : danhSachHoaDon) {
        fptr << hoaDon.khachHang.tenKhachHang << " "
             << hoaDon.khachHang.soDienThoai << " "
             << hoaDon.khachHang.diemTichLuy << endl;
    }
    *soHoaDonFile = danhSachHoaDon.size();
}
void HoaDon::xoaHoaDon(vector<HoaDon>& danhSachHoaDon, const HoaDon& hoaDonXoa) {
    auto it = remove_if(danhSachHoaDon.begin(), danhSachHoaDon.end(), [&hoaDonXoa](const HoaDon& hoaDon) {
        return HoaDon::coNhuNhauHoaDon(hoaDon, hoaDonXoa);
    });
    danhSachHoaDon.erase(it, danhSachHoaDon.end());
}

void HoaDon::nhapThongTinHoaDon(HoaDon& hoaDon, const vector<MonAn>& menu) {
    cout << "Nhập tên khách hàng: ";
    cin >> hoaDon.khachHang.tenKhachHang;
    cout << "Nhập số điện thoại: ";
    cin >> hoaDon.khachHang.soDienThoai;
    hoaDon.soMonGoi = 0;
    // (Nhập các thông tin khác của hóa đơn)
}

void HoaDon::xemHoaDon(const vector<HoaDon>& danhSachHoaDon) {
    for (const auto& hoaDon : danhSachHoaDon) {
        cout << "Tên KH: " << hoaDon.khachHang.tenKhachHang << ", "
             << "SDT: " << hoaDon.khachHang.soDienThoai << ", "
             << "Điểm: " << hoaDon.khachHang.diemTichLuy << endl;
    }
}

void HoaDon::timKiemHoaDon(const vector<HoaDon>& danhSachHoaDon) {
    string tenKhach;
    cout << "Nhập tên khách hàng cần tìm: ";
    cin >> tenKhach;
    for (const auto& hoaDon : danhSachHoaDon) {
        if (hoaDon.khachHang.tenKhachHang == tenKhach) {
            cout << "Tìm thấy: " << hoaDon.khachHang.tenKhachHang << ", "
                 << hoaDon.khachHang.soDienThoai << ", "
                 << hoaDon.khachHang.diemTichLuy << endl;
            return;
        }
    }
    cout << "Không tìm thấy hóa đơn nào của khách hàng tên " << tenKhach << endl;
}
void HoaDon::thanhToan(const vector<MonAn>& menu, vector<HoaDon>& danhSachHoaDon, int *soHoaDon, 
                          const vector<KhachHang>& danhSachKhachHang, int *soKhachHang,
                          const vector<NguyenLieu>& kho, const string& duongDanFileKhach) {
    // 1. Load thông tin hóa đơn
    // 2. Tính tổng tiền
    // 3. Thêm hóa đơn vào danh sách
    // 4. Cập nhật file khách hàng
    // (Code logic chi tiết ở đây)
}

void xoaHoaDon(vector<HoaDon>& danhSachHoaDon, const HoaDon& hoaDonXoa) {
    auto it = remove_if(danhSachHoaDon.begin(), danhSachHoaDon.end(), [&hoaDonXoa](const HoaDon& hoaDon) {
        return HoaDon::coNhuNhauHoaDon(hoaDon, hoaDonXoa);
    });
    danhSachHoaDon.erase(it, danhSachHoaDon.end());
}
