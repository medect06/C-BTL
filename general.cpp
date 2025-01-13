#include "general.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Ngày
class Ngay {
public:
    int ngay, thang, nam;

    bool coNhuNhauNgay(const Ngay& other) const;
    void saoChepNgay(const Ngay& source);
};

bool Ngay::coNhuNhauNgay(const Ngay& other) const {
    return ngay == other.ngay && thang == other.thang && nam == other.nam;
}

void Ngay::saoChepNgay(const Ngay& source) {
    ngay = source.ngay;
    thang = source.thang;
    nam = source.nam;
}

// Xu ly file quan ly
class XuLyFileQuanLy {
public:
    static void docFileQuanLi(int luaChon, string& duongDan);
    static void capNhatFileQuanLi(int luaChon, const string& duongDanMoi);
    static void reset(int* soPhanTuHienTai, int luaChonDoiTuong);
    static void xoaPhanTu(void (*xoaMang)(void* mang, int* soLuong, void* vat), void (*xoaFile)(const string& duongDan, void* vat),
                          void (*nhapThongTin)(void* vatThe, void* mang, int soLuong), int* soPhanTuMang, void* mangHienTai, int* soPhanTuMangDieuKien,
                          void* mangDieuKien, int* soPhanTuFile, void* vatXoa, const string& duongDan);
    static void themPhanTu(void (*nhapThongTin)(void* vat, void* mang, int soLuongMang), void (*themVaoFile)(const string& duongDan, void* vatThem),
                          void (*themVaoMang)(void* mang, int* soLuongMang), void* mangHienTai, int* soLuongMangHienTai, void* mangDieuKien,
                          int* soLuongMangDieuKien, int* soLuongFile, int gioiHan, const string& duongDan);
    static void capNhatDuLieu(void (*capNhatMangTuFile)(void* mang, int* soLuongMang, const string& duongDan, int* soLuongFile),
                             void (*capNhatFileTuMang)(void* mang, int* soLuongMang, const string& duongDan, int* soLuongFile),
                             void* mangHienTai, int* soLuongMang, int* soLuongFile, const string& duongDan);
    static void timKiemDuLieu(void (*timKiem)(void* mang, int soLuongMang), void (*docFile)(const string& duongDan, int soLuongDoc, void* mangFile),
                             void* mangHienTai, int soLuongMang, int soLuongFile, const string& duongDan, int doLonVat);
};

void docFileQuanLi(int luaChon, string& duongDan) {
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
void capNhatFileQuanLi(int luaChon, const string& duongDanMoi) {
    if (luaChon < 1 || luaChon > 4) {
        cout << "Lua chon khong hop le!\n";
        return;
    }
    char noiDungFile[4][MAX_FILE_PATH_LENGTH] = { "" };
    FILE* fptr1 = fopen(MANAGING_FILE.c_str(), "r");
    if (!fptr1) {
        perror("Khong the mo file quan li!");
        return;
    }
    for (int i = 0; i < 4; i++) {
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

    for (int i = 0; i < 4; i++) {
        fprintf(fptr2, "%s\n", noiDungFile[i]);
    }
    fclose(fptr2);
}
