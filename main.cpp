#include "menu.h"
#include "customer.h"
#include "kho.h"
#include "bill.h"
#include "general.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Danh sách các món ăn mặc định và nguyên liệu tương ứng
MonAn menuMacDinh[] = {
    {"Ca phe den", 25.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Duong", "kg", 0.01, 13.00}}, 2},
    {"Ca phe sua", 30.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Sua dac", "hop", 0.01, 15.00}}, 2},
    {"Tra sua", 35.0, {{"Tra den", "kg", 0.01, 10.00}, {"Sua tuoi", "lit", 0.01, 20.00}}, 2},
    {"Ca phe da xay", 40.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Da vien", "kg", 0.1, 5.00}}, 2},
    {"Nuoc cam", 20.0, {{"Cam tuoi", "kg", 0.25, 25.00}}, 1},
    {"Sinh to dua hau", 35.0, {{"Dua hau", "kg", 0.3, 10.00}, {"Sua dac", "hop", 0.02, 15.00}}, 2},
    {"Banh mi op la", 50.0, {{"Bot banh mi", "kg", 0.15, 20.00}, {"Trung ga", "qua", 1, 5.00}}, 2},
    {"Banh mi que", 20.0, {{"Bot banh mi", "kg", 0.1, 20.00}, {"Pate gan", "hop", 0.02, 30.00}}, 2},
    {"Banh bao nhan thit", 25.0, {{"Bot banh bao", "kg", 0.2, 18.00}, {"Thit heo xay", "kg", 0.1, 50.00}}, 2},
    {"Nuoc ep tao", 30.0, {{"Tao tuoi", "kg", 0.3, 15.00}, {"Duong", "kg", 0.01, 13.00}}, 2}
};

// Danh sách nguyên liệu mặc định và giá tương ứng
NguyenLieu khoNguyenLieuMacDinh[] = {
    {"Ca phe bot", "kg", 10.0, 200.0}, {"Sua dac", "hop", 20.0, 15.0}, {"Sua tuoi", "lit", 15.0, 12.0},
    {"Duong", "kg", 8.0, 10.0}, {"Tra den", "kg", 5.0, 150.0}, {"Tran chau", "kg", 7.0, 50.0},
    {"Da vien", "kg", 50.0, 5.0}, {"Cam tuoi", "kg", 12.0, 25.0}, {"Dua hau", "kg", 20.0, 10.0},
    {"Bot banh mi", "kg", 25.0, 18.0}, {"Thit heo xay", "kg", 10.0, 120.0}, {"Bot banh bao", "kg", 15.0, 22.0},
    {"Trung ga", "qua", 30.0, 3.0}, {"Bo", "kg", 5.0, 80.0}, {"Pate gan", "hop", 10.0, 20.0},
    {"Tao tuoi", "kg", 18.0, 30.0}, {"Tuong ot", "chai", 12.0, 10.0}, {"Dau an", "lit", 10.0, 25.0},
    {"Hanh tay", "kg", 8.0, 12.0}, {"Mayonnaise", "chai", 10.0, 15.0}
};

int main() {
    int soMonMacDinh = 10;
    vector<KhachHang> danhSachKhachHang(MAX_KHACH_HANG);
    vector<HoaDon> danhSachHoaDon(MAX_HOA_DON);
    int soKhachHang = 0, soHoaDon = 0;

    FILE* pathFile;
    char fileQuanLiChung[MAX_FILE_PATH_LENGTH];

    pathFile = fopen(MANAGING_FILE, "r");
    if(pathFile) {
        fclose(pathFile);
    } else {
        cout << "Chu y, ban can cai dat duong dan den file quan li khach hang va hoa don!" << endl;
        pathFile = fopen(MANAGING_FILE, "w");
        if (!pathFile) {
            perror("Khong the tao file luu tru duong dan");
        } else {
            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                fprintf(pathFile, PLACEHOLDER_QUAN_LY);
            }
            fclose(pathFile);
        }
    }

    vector<NguyenLieu> khoNguyenLieuSuDung;
    int soLuongNguyenLieuSuDung = 0;

    docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
    int soLuongNguyenLieu = kiemTraSo(fileQuanLiChung);
    if(soLuongNguyenLieu > 0) {
        khoNguyenLieuSuDung.resize(soLuongNguyenLieu);
        docFile(fileQuanLiChung, khoNguyenLieuSuDung);
        soLuongNguyenLieuSuDung = soLuongNguyenLieu;
    } else {
        cout << "Su dung du lieu kho mac dinh" << endl;
        khoNguyenLieuSuDung.assign(begin(khoNguyenLieuMacDinh), end(khoNguyenLieuMacDinh));
        soLuongNguyenLieuSuDung = size(khoNguyenLieuMacDinh);
    }    

    vector<MonAn> menuSuDung;
    int soMonSuDung = 0;

    docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
    int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
    if(soMonFile > 0) {
        menuSuDung.resize(soMonFile);
        docFileMenu(fileQuanLiChung, menuSuDung);
        soMonSuDung = soMonFile;
    } else {
        cout << "Su dung du lieu menu mac dinh" << endl;
        menuSuDung.assign(begin(menuMacDinh), end(menuMacDinh));
        soMonSuDung = soMonMacDinh;
    }

    int luaChon = -1, luaChonCon = -1, luaChonCon2 = -1;
    
    do {
        cout << "\n--- MENU QUAN CAFE ---\n";
        cout << "1. Menu\n";
        cout << "2. Thanh toan\n";
        cout << "3. Hoa don\n";
        cout << "4. Khach hang\n";
        cout << "5. Kho\n";
        cout << "6. Thong ke\n";
        cout << "7. Xu li file\n";
        cout << "8. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;
        
        switch (luaChon) {
            case 1:
                do {
                    cout << "\n--- MENU ---\n";
                    cout << "1. Xem danh sach mon\n";
                    cout << "2. Them mon\n";
                    cout << "3. Xoa mon\n";
                    cout << "4. Sua mon\n";
                    cout << "5. Cap nhat menu\n";
                    cout << "6. Xoa du lieu menu\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> luaChonCon;
                    switch (luaChonCon) {
                    case 1: {
                        docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                        xemDanhSach(static_cast<void (*)(char*, int, void*)>(docFileMenu), static_cast<int (*)(char*)>(kiemTraSoMonAn),
                                    static_cast<void (*)(void *, int)>(hienThiMenu), fileQuanLiChung, soMonSuDung, sizeof(MonAn), menuSuDung);   
                        break;
                    }
                    case 2: {
                        docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                        int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                        MonAn monMoi;
                        themPhanTu(static_cast<void (*)(void*, void*, int)>(nhapThongTinMonAn), static_cast<void (*)(char[], void*)>(themMonAnVaoFile), 
                                   static_cast<void (*)(void*, int*, void*)>(themMonAnVaoMang),
                                   menuSuDung, &soMonSuDung, khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung,
                                   &soMonFile, MAX_MON, &monMoi, fileQuanLiChung);
                        break;
                    }
                    case 3: {
                        docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                        int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                        MonAn monXoa;
                        xoaPhanTu(static_cast<void (*)(void*, int*, void*)>(xoaMonAnTrongMang), static_cast<void (*)(char*, void*)>(xoaMonAnKhoiFile),
                                  static_cast<void (*)(void*, void*, int)>(nhapTenMonAn), &soMonSuDung, menuSuDung, &placeHolderVal,
                                  placeHolderArr, &soMonFile, &monXoa, fileQuanLiChung);
                        break;
                    }
                    case 4: {
                        int luaChonSua;
                        cout << "Sua mon trong menu hien tai (1) hay sua mon trong file menu tu file (2): ";
                        cin >> luaChonSua;

                        if(luaChonSua != 1 && luaChonSua != 2) {
                            cout << "Lua chon khong hop le\n";
                            break;
                        }

                        string monThayDoi;
                        bool timThayMon = false;
                        int viTriMonCanSua = 0;

                        if(luaChonSua == 1) {
                            if(soMonSuDung == 0) {
                                cout << "Menu hien tai khong co mon an\n";
                                break;
                            }

                            hienThiMenu(menuSuDung, soMonSuDung);
                            cout << "Nhap ten mon an can thay doi: ";
                            cin.ignore();
                            getline(cin, monThayDoi);

                            for(int i = 0; i < soMonSuDung; i++) {
                                if(monThayDoi == menuSuDung[i].tenMon) {
                                    timThayMon = true;
                                    viTriMonCanSua = i;
                                    break;
                                }
                            }

                            if(!timThayMon) {
                                cout << "Menu khong co mon: " << monThayDoi << endl;
                                cout << "Co le ban da danh thua dau cach?\n";
                                break;
                            }

                            cout << "Nhap thong tin moi cho mon can sua\n";
                            nhapThongTinMonAn(&menuSuDung[viTriMonCanSua], khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                        } else {
                            docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                            int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                            if(soMonFile == 0) {
                                cout << "File khong co mon an\n";
                                break;
                            }
                            vector<MonAn> menuFile(soMonFile);
                            docFileMenu(fileQuanLiChung, menuFile);

                            hienThiMenu(menuFile, soMonFile);
                            cout << "Nhap ten mon an can thay doi: ";
                            cin.ignore();
                            getline(cin, monThayDoi);

                            for(int i = 0; i < soMonFile; i++) {
                                if(monThayDoi == menuFile[i].tenMon) {
                                    timThayMon = true;
                                    viTriMonCanSua = i;
                                    break;
                                }
                            }

                            if(!timThayMon) {
                                cout << "Menu khong co mon: " << monThayDoi << endl;
                                cout << "Co le ban da danh thua dau cach?\n";
                                break;
                            }

                            cout << "Nhap thong tin moi cho mon can sua\n";
                            nhapThongTinMonAn(&menuFile[viTriMonCanSua], khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);

                            capNhatMonAnTuMang(menuFile, LUA_CHON_MENU);
                        }

                        cout << "Mon an da duoc sua\n";
                        break;
                    }
                    case 5: {
                        docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                        int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                        capNhatDuLieu(static_cast<void (*)(void*, int*, char[], int*)>(capNhatMonAnTuFile), 
                                      static_cast<void (*)(void*, int*, char[], int*)>(capNhatMonAnTuMang),
                                      menuSuDung, &soMonSuDung, &soMonFile, fileQuanLiChung);
                        break;
                    }
                    case 6: {
                        reset(&soMonSuDung, LUA_CHON_MENU);
                        break;
                    }
                    case 7:
                        break;
                    default:
                        cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    }
                } while (luaChonCon != 7);
                break;

            case 2: {
                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                thanhToan(menuSuDung, soMonSuDung, danhSachHoaDon, &soHoaDon, danhSachKhachHang, &soKhachHang, khoNguyenLieuSuDung, soLuongNguyenLieuSuDung, fileQuanLiChung);
                break;
            }

            case 3:
                do {
                    cout << "\n--- HOA DON ---\n";
                    cout << "1. Xem danh sach hoa don\n";
                    cout << "2. Tim kiem hoa don\n";
                    cout << "3. Them hoa don vao file\n";
                    cout << "4. Xoa hoa don\n";
                    cout << "5. Cap nhat file hoa don\n";
                    cout << "6. Xoa du lieu hoa don\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> luaChonCon;
            
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            xemDanhSach(static_cast<void (*)(char*, int, void*)>(docFileHoaDon), static_cast<int (*)(char*)>(kiemTraSoHoaDon), 
                                       static_cast<void (*)(void*, int)>(xemHoaDon), fileQuanLiChung, soHoaDon, sizeof(HoaDon), danhSachHoaDon);
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soFile = kiemTraSoHoaDon(fileQuanLiChung);
                            timKiemDuLieu(static_cast<void (*)(void*, int)>(timKiemHoaDon), static_cast<void (*)(char[], int, void*)>(docFileHoaDon), 
                                          danhSachHoaDon, soHoaDon, soFile, fileQuanLiChung, sizeof(HoaDon));
                            break;
                        }
                        case 3: {
                            HoaDon hoaDonMoi;
                            nhapThongTinHoaDon(&hoaDonMoi, menuSuDung, soMonSuDung);
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            themHoaDonVaoFile(hoaDonMoi, fileQuanLiChung);
                            cout << "Hoa don duoc them thanh cong\n";
                            break;
                        }
                        case 4: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon hoaDon;
                            xoaPhanTu(static_cast<void (*)(void*, int*, void*)>(xoaHoaDon), static_cast<void (*)(char*, void*)>(xoaHoaDonKhoiFile),
                                      static_cast<void (*)(void*, void*, int)>(nhapThongTinHoaDon), &soHoaDon, danhSachHoaDon, &soMonSuDung,
                                      menuSuDung, &soHoaDonFile, &hoaDon, fileQuanLiChung);
                            break;
                        }
                        case 5: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            capNhatDuLieu(static_cast<void (*)(void*, int*, char[], int*)>(capNhatHoaDonTuFile), 
                                          static_cast<void (*)(void*, int*, char[], int*)>(capNhatHoaDonTuMang),
                                          danhSachHoaDon, &soHoaDon, &soHoaDonFile, fileQuanLiChung);
                            break;
                        }
                        case 6: {
                            reset(&soHoaDon, LUA_CHON_HOA_DON);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    }
                } while (luaChonCon != 7);
                break;

            case 4:
                do {
                    cout << "\n--- KHACH HANG ---\n";
                    cout << "1. Xem danh sach khach hang\n";
                    cout << "2. Tim kiem khach hang\n";
                    cout << "3. Them khach hang\n"; 
                    cout << "4. Xoa khach hang\n";  
                    cout << "5. Cap nhat du lieu khach hang\n";
                    cout << "6. Xoa du lieu khach hang\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> luaChonCon;
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            xemDanhSach(static_cast<void (*)(char*, int, void*)>(docFileKhachHang), static_cast<int (*)(char*)>(kiemTraSoKhachHang), 
                                        static_cast<void (*)(void*, int)>(xemDanhSachKhachHang), fileQuanLiChung, soKhachHang, sizeof(KhachHang), danhSachKhachHang);
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soFile = kiemTraSoKhachHang(fileQuanLiChung);
                            timKiemDuLieu(static_cast<void (*)(void*, int)>(timKiemKhachHang), static_cast<void (*)(char[], int, void*)>(docFileKhachHang),
                                           danhSachKhachHang, soKhachHang, soFile, fileQuanLiChung, sizeof(KhachHang));
                            break;
                        }
                        case 3: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soKhachFile = kiemTraSoKhachHang(fileQuanLiChung);
                            KhachHang khachMoi;
                            themPhanTu(static_cast<void (*)(void*, void*, int)>(nhapThongTinKhach), static_cast<void (*)(char[], void*)>(themKhachHangVaoFile),
                                       static_cast<void (*)(void*, int*, void*)>(themKhachHang),
                                       danhSachKhachHang, &soKhachHang, placeHolderArr, &placeHolderVal,
                                       &soKhachFile, MAX_KHACH_HANG, &khachMoi, fileQuanLiChung);
                            break;
                        }
                        case 4: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soKhachHangFile = kiemTraSoKhachHang(fileQuanLiChung);
                            KhachHang khachHang;
                            xoaPhanTu(static_cast<void (*)(void*, int*, void*)>(xoaKhachHang), static_cast<void (*)(char*, void*)>(xoaKhachKhoiFile),
                                      static_cast<void (*)(void*, void*, int)>(nhapTenSDTKhach),
                                      &soKhachHang, danhSachKhachHang, &placeHolderVal,
                                      &placeHolderArr, &soKhachHangFile, &khachHang, fileQuanLiChung);
                            break;
                        }
                        case 5: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung); 
                            int soKhachFile = kiemTraSoKhachHang(fileQuanLiChung);
                            capNhatDuLieu(static_cast<void (*)(void*, int*, char[], int*)>(capNhatKhachTuFile),
                                          static_cast<void (*)(void*, int*, char[], int*)>(capNhatKhachTuMang),
                                          danhSachKhachHang, &soKhachHang, &soKhachFile, fileQuanLiChung);
                            break;
                        }
                        case 6: {
                            reset(&soKhachHang, LUA_CHON_KHACH_HANG);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    }
                } while (luaChonCon != 7);
                break;

            case 5:
                do {
                    cout << "\n--- MENU QUAN LY KHO NGUYEN LIEU ---\n";
                    cout << "1. Xem kho nguyen lieu\n";
                    cout << "2. Tim kiem nguyen lieu\n";
                    cout << "3. Them nguyen lieu\n";
                    cout << "4. Xoa nguyen lieu\n";
                    cout << "5. Cap nhat file nguyen lieu\n";
                    cout << "6. Xoa du lieu kho\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";

                    cin >> luaChonCon; 
            
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            xemDanhSach(static_cast<void (*)(char*, int, void*)>(docFileKho), static_cast<int (*)(char*)>(kiemTraSoNguyenLieu),
                                        static_cast<void (*)(void*, int)>(hienThiKho), fileQuanLiChung, soLuongNguyenLieuSuDung, sizeof(NguyenLieu), 
                                        khoNguyenLieuSuDung);
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            timKiemDuLieu(static_cast<void (*)(void*, int)>(timKiemNguyenLieu), static_cast<void (*)(char[], int, void*)>(docFileKho),
                                          khoNguyenLieuSuDung, soLuongNguyenLieuSuDung, soFile, fileQuanLiChung, sizeof(NguyenLieu));
                            break;
                        }
                        case 3: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            NguyenLieu nguyenLieuMoi;
                            themPhanTu(static_cast<void (*)(void*, void*, int)>(nhapThongTinNguyenLieu), static_cast<void (*)(char[], void*)>(themNguyenLieuVaoFile),
                                       static_cast<void (*)(void*, int*, void*)>(themNguyenLieu), khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung, 
                                       placeHolderArr, &placeHolderVal, &soNguyenLieuFile, MAX_NGUYEN_LIEU, &nguyenLieuMoi, fileQuanLiChung);
                            break;
                        }    
                        case 4: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            NguyenLieu nguyenLieuXoa;
                            xoaPhanTu(static_cast<void (*)(void*, int*, void*)>(xoaNguyenLieu), static_cast<void (*)(char*, void*)>(xoaNguyenLieuKhoiFile),
                                      static_cast<void (*)(void*, void*, int)>(nhapTenNguyenLieu), &soLuongNguyenLieuSuDung, khoNguyenLieuSuDung, &placeHolderVal, 
                                      placeHolderArr, &soNguyenLieuFile, &nguyenLieuXoa, fileQuanLiChung);
                            break;
                        }
                    }
                    case 5: {
                        docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                        int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                        capNhatDuLieu(static_cast<void (*)(void*, int*, char[], int*)>(capNhatKhoTuFile),
                                      static_cast<void (*)(void*, int*, char[], int*)>(capNhatKhoTuMang),
                                      khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung, &soNguyenLieuFile, fileQuanLiChung);
                        break;
                    }   
                    case 6: {
                        reset(&soLuongNguyenLieuSuDung, LUA_CHON_KHO);
                        break;
                    }
                    case 7:
                        break;
                    default:
                        cout << "Lua chon khong hop le, vui long chon lai\n";
                    }
                } while (luaChonCon != 7);
                break; 

            case 6: 
                do {
                    cout << "\n--- Thong ke ---\n";
                    cout << "1. Thong ke trong nam\n";
                    cout << "2. Thong ke trong thang\n";
                    cout << "3. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> luaChonCon;

                    switch (luaChonCon){
                        case 1: {
                            int namThongKe;
                            cout << "Nhap nam thong ke: ";
                            cin >> namThongKe;

                            if(namThongKe < 0) {
                                cout << "Nam khong the am\n";
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            vector<HoaDon> danhSachHoaDonFile(soHoaDonFile);

                            if(!danhSachHoaDonFile.data()) {
                                cout << "Khong the khoi tao mang dong de thong ke hoa don theo nam\n";
                                break;
                            }

                            docFileHoaDon(fileQuanLiChung, danhSachHoaDonFile);

                            float tongTienQ1 = 0, chiPhiQ1 = 0;
                            float tongTienQ2 = 0, chiPhiQ2 = 0;
                            float tongTienQ3 = 0, chiPhiQ3 = 0;
                            float tongTienQ4 = 0, chiPhiQ4 = 0;
                            int soDonQ1 = 0, soDonQ2 = 0, soDonQ3 = 0, soDonQ4 = 0;
                            bool tonTaiNam = false;

                            for(const auto& hoaDon : danhSachHoaDonFile) {
                                if(hoaDon.ngayNhapDon.nam == namThongKe) {
                                    tonTaiNam = true;
                                    if(hoaDon.ngayNhapDon.thang >= 1 && hoaDon.ngayNhapDon.thang <= 3) {
                                        tongTienQ1 += hoaDon.tongTien - hoaDon.tienThua;
                                        chiPhiQ1 += hoaDon.tienNguyenLieu;
                                        soDonQ1++;
                                    } else if(hoaDon.ngayNhapDon.thang >= 4 && hoaDon.ngayNhapDon.thang <= 6) {
                                        tongTienQ2 += hoaDon.tongTien - hoaDon.tienThua;
                                        chiPhiQ2 += hoaDon.tienNguyenLieu;
                                        soDonQ2++;
                                    } else if(hoaDon.ngayNhapDon.thang >= 7 && hoaDon.thang <= 9) {
                                        tongTienQ3 += hoaDon.tongTien - hoaDon.tienThua;
                                        chiPhiQ3 += hoaDon.tienNguyenLieu;
                                        soDonQ3++;
                                    } else if(hoaDon.ngayNhapDon.thang >= 10 && hoaDon.thang <= 12) {
                                        tongTienQ4 += hoaDon.tongTien - hoaDon.tienThua;
                                        chiPhiQ4 += hoaDon.tienNguyenLieu;
                                        soDonQ4++;
                                    }
                                }
                            }

                            if(!tonTaiNam) {
                                cout << "Khong ton tai nam " << namThongKe << " trong he thong\n";
                                break;
                            }
                            cout << "\n--- Nam " << namThongKe << " ---\n";
                            cout << "Quy 1 co " << soDonQ1 << " don hang, tong loi nhuan: " << fixed << setprecision(2) << tongTienQ1 - chiPhiQ1 << "\n";
                            cout << "Quy 2 co " << soDonQ2 << " don hang, tong loi nhuan: " << fixed << setprecision(2) << tongTienQ2 - chiPhiQ2 << "\n";
                            cout << "Quy 3 co " << soDonQ3 << " don hang, tong loi nhuan: " << fixed << setprecision(2) << tongTienQ3 - chiPhiQ3 << "\n";
                            cout << "Quy 4 co " << soDonQ4 << " don hang, tong loi nhuan: " << fixed << setprecision(2) << tongTienQ4 - chiPhiQ4 << "\n";
                            cout << "Nam " << namThongKe << " co " << soDonQ1 + soDonQ2 + soDonQ3 + soDonQ4 
                                 << " don hang, tong thu nhap: " << fixed << setprecision(2) 
                                 << tongTienQ1 - chiPhiQ1 + tongTienQ2 - chiPhiQ2 + tongTienQ3 - chiPhiQ3 + tongTienQ4 - chiPhiQ4 << "\n";

                            break;
                        }
                        case 2: {
                            int namThongKe, thangThongKe;
                            cout << "Nhap nam thong ke: ";
                            cin >> namThongKe;
                            cout << "Nhap thang thong ke: ";
                            cin >> thangThongKe;

                            if(namThongKe < 0 || thangThongKe < 0) {
                                cout << "Nam va thang khong the am\n";
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            vector<HoaDon> danhSachHoaDonFile(soHoaDonFile);
                            
                            if(!danhSachHoaDonFile.data()) {
                                cout << "Khong the khoi tao mang dong de thong ke hoa don theo thang\n";
                                break;
                            }

                            docFileHoaDon(fileQuanLiChung, danhSachHoaDonFile);

                            float tongTienThongKe = 0, tienNguyenLieuThongKe = 0;
                            int soHoaDonThongKe = 0;
                            bool tonTaiThoiDiem = false;

                            for(const auto& hoaDon : danhSachHoaDonFile) {
                                if(hoaDon.ngayNhapDon.nam == namThongKe && hoaDon.ngayNhapDon.thang == thangThongKe) {
                                    tonTaiThoiDiem = true;
                                    tongTienThongKe += hoaDon.tongTien - hoaDon.tienThua;
                                    tienNguyenLieuThongKe += hoaDon.tienNguyenLieu;
                                    soHoaDonThongKe++;
                                }
                            }

                            if(!tonTaiThoiDiem) {
                                cout << "Khong ton tai hoa don thang " << thangThongKe << " nam " << namThongKe << " trong file\n";
                                break;
                            }
                            cout << "\n--- Thong ke thang " << thangThongKe << " nam " << namThongKe << " ---\n";
                            cout << "Tong thu nhap: " << fixed << setprecision(2) << tongTienThongKe - tienNguyenLieuThongKe << "\n";
                            cout << "So hoa don: " << soHoaDonThongKe << "\n";

                            break;
                        }
                        case 3:
                            break;
                        default:
                            cout << "Lua chon khong hop le, vui long chon lai\n";
                    }
                } while(luaChonCon != 3);
                break;

            case 7:
                do {
                    cout << "\n--- FILE ---\n";
                    cout << "1. File khach hang\n";
                    cout << "2. File hoa don\n";
                    cout << "3. File kho\n";
                    cout << "4. File menu\n";
                    cout << "5. Reset file quan li\n";
                    cout << "6. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> luaChonCon;
                    if(luaChonCon == 5) {
                        FILE* quanLiFptr = fopen(MANAGING_FILE, "w");
                        if(quanLiFptr) {
                            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                                fprintf(quanLiFptr, PLACEHOLDER_QUAN_LY);
                            }
                            fclose(quanLiFptr);
                            cout << "Reset file thanh cong\n";
                        } else {
                            perror("Khong the reset file quan ly");
                        }
                    } else if(luaChonCon == 1 || luaChonCon == 2 || luaChonCon == 3 || luaChonCon == 4) {
                        do {
                            cout << "\n--- Hanh dong ---\n";
                            cout << "1. Xoa file\n";
                            cout << "2. Tao file\n";
                            cout << "3. Di chuyen file\n";
                            cout << "4. Xem duong dan hien tai\n";
                            cout << "5. Chon file\n";
                            cout << "6. Quay lai\n";
                            cout << "Nhap lua chon: ";
                            cin >> luaChonCon2;
                    
                            switch (luaChonCon2) {
                                case 1: {
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    int ketQuaXoa = remove(fileQuanLiChung);
                                    if(ketQuaXoa != 0) {
                                        perror("Xoa file that bai");
                                        break;
                                    }
                                    cout << "File da duoc xoa!\n";
                                    capNhatFileQuanLi(luaChonCon, "");
                                    break;
                                }
                                case 2: {
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    cout << "Nhap duong dan moi: ";
                                    cin.ignore();
                                    cin.getline(duongDanMoi, MAX_FILE_PATH_LENGTH);

                                    FILE* fptr = fopen(duongDanMoi, "w");
                                    if(!fptr) {
                                        cout << "Loi khi tao file!\n";
                                        break;
                                    }

                                    switch (luaChonCon) {
                                        case LUA_CHON_KHACH_HANG:
                                            fprintf(fptr, KHACH_HANG_HEADER);
                                            break;
                                        case LUA_CHON_HOA_DON:
                                            fprintf(fptr, HOA_DON_HEADER);
                                            break;
                                        case LUA_CHON_KHO:
                                            fprintf(fptr, KHO_HEADER);
                                            break;
                                        case LUA_CHON_MENU:
                                            fprintf(fptr, MENU_HEADER);
                                        default:
                                            break;
                                    }

                                    cout << "File duoc tao thanh cong!\n";
                                    fclose(fptr);
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 3: {
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    cout << "Nhap dia chi moi: ";
                                    cin.ignore();
                                    cin.getline(duongDanMoi, MAX_FILE_PATH_LENGTH);

                                    docFileQuanLi(luaChonCon, fileQuanLiChung);

                                    if(strncmp(duongDanMoi, fileQuanLiChung, MAX_FILE_PATH_LENGTH) == 0) {
                                        cout << "Duong dan moi khong the giong duong dan cu!\n";
                                        break;
                                    }
                                    
                                    FILE* fptrDich = fopen(duongDanMoi, "w");
                                    if(!fptrDich) {
                                        perror("Loi khi tao file o dia chi moi");
                                        break;
                                    }

                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    FILE* fptrNguon = fopen(fileQuanLiChung, "r");
                                    if(!fptrNguon) {
                                        perror("Khong the mo file cu de chuyen du lieu");
                                        break;
                                    }
                                    char dongDuLieu[MAX_DONG_DU_LIEU];
                                    while(fgets(dongDuLieu, MAX_DONG_DU_LIEU - 1, fptrNguon)) {
                                        dongDuLieu[MAX_DONG_DU_LIEU - 1] = '\0';
                                        fprintf(fptrDich, "%s", dongDuLieu);
                                    }
                                    fclose(fptrNguon);
                                    fclose(fptrDich);

                                    if(remove(fileQuanLiChung) != 0) {
                                        perror("File du lieu nguon chua duoc xoa");
                                    }

                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    cout << "File da duoc cap nhat thanh cong\n";
                                    break;
                                }
                                case 4: {
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    cout << "Duong dan hien tai: " << fileQuanLiChung << "\n";
                                    break;
                                }
                                case 5: {
                                    cout << "CANH BAO: HAY DAM BAO FILE DUOC HUONG TOI LA FILE DU LIEU DUNG LOAI VA DUNG CU PHAP!!!!\n";
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    cout << "Nhap dia chi moi: ";
                                    cin.ignore();
                                    cin.getline(duongDanMoi, MAX_FILE_PATH_LENGTH);

                                    FILE* fptr = fopen(duongDanMoi, "r");
                                    if(!fptr) {
                                        perror("Khong the su dung file");
                                        break;
                                    }

                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 6:
                                    break;
                                default:
                                    cout << "Lua chon khong hop le. Vui long chon lai.\n";
                            }             
                        } while (luaChonCon2 != 6);
                    } else if(luaChonCon != 6) {
                        cout << "Lua chon khong hop le. Vui long chon lai!\n";
                    }
                } while(luaChonCon != 6);
                break; 
                case 8:
                    cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai.\n";
            }
        } while (luaChon != 8);

        if(canFreeKhoNguyenLieu == 1) {
            free(khoNguyenLieuSuDung);
        }

        if(canFreeMenu == 1) {
            free(menuSuDung);
        }

        return 0;
    }
}


 
