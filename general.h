#ifndef GENERAL_H
#define GENERAL_H

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
                          void (*themVaoMang)(void* mang, int* soLuongMang, void* vatThem), void* mangHienTai, int* soLuongMangHienTai, void* mangDieuKien,
                          int* soLuongMangDieuKien, int* soLuongFile, int gioiHan, void* vatThem, const string& duongDan);
    static void capNhatDuLieu(void (*capNhatMangTuFile)(void* mang, int* soLuongMang, const string& duongDan, int* soLuongFile),
                             void (*capNhatFileTuMang)(void* mang, int* soLuongMang, const string& duongDan, int* soLuongFile),
                             void* mangHienTai, int* soLuongMang, int* soLuongFile, const string& duongDan);
    static void timKiemDuLieu(void (*timKiem)(void* mang, int soLuongMang), void (*docFile)(const string& duongDan, int soLuongDoc, void* mangFile),
                             void* mangHienTai, int soLuongMang, int soLuongFile, const string& duongDan, int doLonVat);
};

#endif // GENERAL_H
