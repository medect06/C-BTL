#include "general.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

// So sánh hai đối tượng Ngay
bool Ngay::coNhuNhauNgay(const Ngay& other) const {
    return ngay == other.ngay && thang == other.thang && nam == other.nam;
}

// Sao chép giá trị ngày từ một đối tượng khác
void Ngay::saoChepNgay(const Ngay& source) {
    ngay = source.ngay;
    thang = source.thang;
    nam = source.nam;
}

// Đọc file quản lý với lựa chọn
void XuLyFileQuanLy::docFileQuanLi(int luaChon, string& duongDan) {
    if (luaChon < 1 || luaChon > 4) {
        cout << "Lua chon mo file quan li khong hop le!\n";
        return;
    }
    FILE* fptr = fopen(MANAGING_FILE.c_str(), "r");

    if (!fptr) {
        perror("Khong the mo file quan li file");
        return;
    }
    for (int i = 1; i <= luaChon; i++) {
        if (!fgets(&duongDan[0], MAX_FILE_PATH_LENGTH, fptr)) {
            perror("Xay ra loi khi doc file quan li");
            fclose(fptr);
            return;
        }
    }
    duongDan.erase(duongDan.find_last_not_of("\n") + 1); // Remove newline characters
    fclose(fptr);
}

// Cập nhật file quản lý với đường dẫn mới
void XuLyFileQuanLy::capNhatFileQuanLi(int luaChon, const string& duongDanMoi) {
    if (luaChon < 1 || luaChon > SO_DOI_TUONG_LAM_VIEC) {
        cout << "Lua chon khong hop le!\n";
        return;
    }
    char noiDungFile[SO_DOI_TUONG_LAM_VIEC][MAX_FILE_PATH_LENGTH] = { "" };
    FILE* fptr1 = fopen(MANAGING_FILE.c_str(), "r");
    if (!fptr1) {
        perror("Khong the mo file quan li!");
        return;
    }

    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        if (!fgets(noiDungFile[i], MAX_FILE_PATH_LENGTH, fptr1)) {
            perror("Co loi khi doc file quan li");
            fclose(fptr1);
            return;
        } else {
            noiDungFile[i][strcspn(noiDungFile[i], "\n")] = '\0';
        }
    }
    fclose(fptr1);

    strncpy(noiDungFile[luaChon - 1], duongDanMoi.c_str(), MAX_FILE_PATH_LENGTH - 1);
    noiDungFile[luaChon - 1][MAX_FILE_PATH_LENGTH - 1] = '\0';

    FILE* fptr2 = fopen(MANAGING_FILE.c_str(), "w");
    if (!fptr2) {
        perror("Khong the mo file quan li de ghi");
        return;
    }

    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        fprintf(fptr2, "%s\n", noiDungFile[i]);
    }
    fclose(fptr2);
}

// Reset nội dung mảng hoặc file
void XuLyFileQuanLy::reset(int* soPhanTuHienTai, int luaChonDoiTuong) {
    int canhCao;
    cout << "CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ";
    saferScanf("%d", &canhCao);
    if (canhCao != 1) {
        return;
    }

    int luaChonXoa;
    cout << "Xoa du lieu mang hien tai (1) hay xoa du lieu file (2) ";
    saferScanf("%d", &luaChonXoa);

    if (luaChonXoa != 1 && luaChonXoa != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChonXoa == 1) {
        *soPhanTuHienTai = 0;
        cout << "Mang da duoc reset\n";
    } else {
        resetFile(luaChonDoiTuong);
        cout << "File da duoc reset\n";
    }
}

// Xóa phần tử trong mảng hoặc file
void XuLyFileQuanLy::xoaPhanTu(void (*xoaMang)(void* mang, int* soLuong, void* vat), void (*xoaFile)(const string& duongDan, void* vat),
               void (*nhapThongTin)(void* vatThe, void* mang, int soLuong), int* soPhanTuMang, void* mangHienTai, int* soPhanTuMangDieuKien,
               void* mangDieuKien, int* soPhanTuFile, void* vatXoa, const string& duongDan) {
    int luaChonXoaBo;
    cout << "Xoa trong mang hien tai (1) hay xoa trong file (2): ";
    saferScanf("%d", &luaChonXoaBo);
    if (luaChonXoaBo != 1 && luaChonXoaBo != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChonXoaBo == 1) {
        if (*soPhanTuMang == 0) {
            cout << "Mang khong co phan tu\n";
            return;
        }
        nhapThongTin(vatXoa, mangDieuKien, *soPhanTuMangDieuKien);
        xoaMang(mangHienTai, soPhanTuMang, vatXoa);
    } else {
        if (*soPhanTuFile == 0) {
            cout << "File khong co phan tu\n";
            return;
        }
        nhapThongTin(vatXoa, mangDieuKien, *soPhanTuMangDieuKien);
        xoaFile(duongDan, vatXoa);
    }
}

// Thêm phần tử vào mảng hoặc file
void XuLyFileQuanLy::themPhanTu(void (*nhapThongTin)(void* vat, void* mang, int soLuongMang), void (*themVaoFile)(const string& duongDan, void* vatThem),
               void (*themVaoMang)(void* mang, int* soLuongMang, void* vatThem), void* mangHienTai, int* soLuongMangHienTai, void* mangDieuKien, int* soLuongMangDieuKien,
               int* soLuongFile, int gioiHan, void* vatThem, const string& duongDan) {
    int luaChonThem;
    cout << "Them vao mang hien tai (1) hay them vao file (2): ";
    saferScanf("%d", &luaChonThem);
    if (luaChonThem != 1 && luaChonThem != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChonThem == 1) {
        if (*soLuongMangHienTai >= gioiHan) {
            cout << "Mang da day\n";
            return;
        }
        nhapThongTin(vatThem, mangDieuKien, *soLuongMangDieuKien);
        themVaoMang(mangHienTai, soLuongMangHienTai, vatThem);
    } else {
        if (*soLuongFile >= gioiHan) {
            cout << "File da day\n";
            return;
        }
        nhapThongTin(vatThem, mangDieuKien, *soLuongMangDieuKien);
        themVaoFile(duongDan, vatThem);
    }
}

// Cập nhật dữ liệu từ file hoặc mảng
void XuLyFileQuanLy::capNhatDuLieu(void (*capNhatMangTuFile)(void* mang, int* soLuongMang, const string& duongDan, int* soLuongFile),
               void (*capNhatFileTuMang)(void* mang, int* soLuongMang, const string& duongDan, int* soLuongFile),
               void* mangHienTai, int* soLuongMang, int* soLuongFile, const string& duongDan) {
    int luaChonCapNhat;
    cout << "Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2): ";
    saferScanf("%d", &luaChonCapNhat);
    if (luaChonCapNhat != 1 && luaChonCapNhat != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChonCapNhat == 1 && *soLuongFile == 0) {
        cout << "File khong co mon an\n";
        return;
    } else if (luaChonCapNhat == 2 && *soLuongMang == 0) {
        cout << "Mang khong co mon an\n";
        return;
    }

    if (luaChonCapNhat == 1) {
        capNhatMangTuFile(mangHienTai, soLuongMang, duongDan, soLuongFile);
    } else {
        capNhatFileTuMang(mangHienTai, soLuongMang, duongDan, soLuongFile);
    }
}

// Tìm kiếm dữ liệu trong mảng
void XuLyFileQuanLy::timKiemDuLieu(void (*timKiem)(void* mang, int soLuongMang), void (*docFile)(const string& duongDan, int soLuongDoc, void* mangFile),
               void* mangHienTai, int soLuongMang, int soLuongFile, const string& duongDan, int doLonVat) {
    int luaChonTimKiem;
    cout << "Tim kiem trong mang (1) hay trong file (2): ";
    saferScanf("%d", &luaChonTimKiem);
    if (luaChonTimKiem != 1 && luaChonTimKiem != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChonTimKiem == 1) {
        if (soLuongMang == 0) {
            cout << "Chua co du lieu trong mang\n";
            return;
        }
        timKiem(mangHienTai, soLuongMang);
    } else {
        if (soLuongFile == 0) {
            cout << "Chua co du lieu trong file\n";
            return;
        }
        void* mangFile = malloc(doLonVat * soLuongFile);
        if (!mangFile) {
            cout << "Khong the khoi tao mang dong de tim kiem\n";
            return;
        }
        docFile(duongDan, soLuongFile, mangFile);

        timKiem(mangFile, soLuongFile);

        free(mangFile);
    }
}
