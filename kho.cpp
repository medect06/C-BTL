#include "general.h"
#include "kho.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

void chuanHoaKho(NguyenLieu* kho, int soNguyenLieu) {
    for (int i = 0; i < soNguyenLieu; i++) {
        strncpy(kho[i].tenNguyenLieu, "0", 2);
        strncpy(kho[i].donVi, "0", 2);
        kho[i].soLuong = kho[i].gia = 0;
    }
}

void saoChepNguyenLieu(NguyenLieu* nguyenLieuNhan, const NguyenLieu* nguyenLieuNguon) {
    strncpy(nguyenLieuNhan->tenNguyenLieu, nguyenLieuNguon->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);
    strncpy(nguyenLieuNhan->donVi, nguyenLieuNguon->donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
    nguyenLieuNhan->soLuong = nguyenLieuNguon->soLuong;
    nguyenLieuNhan->gia = nguyenLieuNguon->gia;
}

void themNhieuNguyenLieuVaoFile(const vector<NguyenLieu>& danhSachNguyenLieu, const char* duongDan) {
    FILE* fptr = fopen(duongDan, "a");
    if (!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }

    for (const auto& nl : danhSachNguyenLieu) {
        fprintf(fptr, "%s,%s,%.2f,%.2f\n", nl.tenNguyenLieu, nl.donVi, nl.soLuong, nl.gia);
    }

    fclose(fptr);
}

int kiemTraSoNguyenLieu(const char* duongDan) {
    FILE* fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong nguyen lieu");
        return -1;
    }

    int soNguyenLieu = 0;
    fseek(fptr, sizeof(KHO_HEADER), SEEK_SET);
    char msg[MAX_ARRAY_LENGTH_KHO];
    while (fgets(msg, MAX_ARRAY_LENGTH_KHO, fptr)) {
        soNguyenLieu++;
    }

    fclose(fptr);
    return soNguyenLieu;
}

void docFileKho(const char* duongDan, int soNguyenLieu, NguyenLieu kho[]) {
    if (soNguyenLieu == 0) return;

    FILE* fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong nguyen lieu");
        return;
    }

    chuanHoaKho(kho, soNguyenLieu);
    char msg[MAX_ARRAY_LENGTH_KHO];
    fseek(fptr, sizeof(KHO_HEADER), SEEK_SET);

    for (int i = 0; i < soNguyenLieu; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_KHO - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file nguyen lieu");
            break;
        }

        msg[MAX_ARRAY_LENGTH_KHO - 1] = '\0';
        msg[strcspn(msg, "\n")] = '\0';

        strncpy(kho[i].tenNguyenLieu, strtok(msg, NGAN_PHAN_TU_CSV), MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);
        strncpy(kho[i].donVi, strtok(NULL, NGAN_PHAN_TU_CSV), MAX_DO_DAI_CHUOI_DON_VI - 1);
        kho[i].soLuong = atof(strtok(NULL, NGAN_PHAN_TU_CSV));
        kho[i].gia = atof(strtok(NULL, NGAN_PHAN_TU_CSV));
    }

    fclose(fptr);
}
void xoaNguyenLieuKhoiFile(const char* duongDan, const NguyenLieu* nguyenLieuXoa) {
    int soNguyenLieuFile = kiemTraSoNguyenLieu(duongDan);
    if (soNguyenLieuFile == 0) {
        printf("Kho trong\n");
        return;
    }

    vector<NguyenLieu> khoFile(soNguyenLieuFile);
    docFileKho(duongDan, soNguyenLieuFile, &khoFile[0]);

    auto it = find_if(khoFile.begin(), khoFile.end(), [nguyenLieuXoa](const NguyenLieu& nl) {
        return strcmp(nl.tenNguyenLieu, nguyenLieuXoa->tenNguyenLieu) == 0;
    });

    if (it != khoFile.end()) {
        khoFile.erase(it);
        printf("Xoa nguyen lieu khoi file kho thanh cong\n");
    }

    FILE* fptr = fopen(duongDan, "w");
    if (!fptr) {
        perror("Khong the mo file kho de xoa nguyen lieu");
        return;
    }

    fprintf(fptr, KHO_HEADER);
    for (const auto& nl : khoFile) {
        fprintf(fptr, "%s,%s,%.2f,%.2f\n", nl.tenNguyenLieu, nl.donVi, nl.soLuong, nl.gia);
    }

    fclose(fptr);
}

void themNguyenLieuVaoFile(const char* duongDan, const NguyenLieu* nguyenLieu) {
    int soNguyenLieuFile = kiemTraSoNguyenLieu(duongDan);
    if (soNguyenLieuFile >= MAX_NGUYEN_LIEU) {
        printf("File nguyen lieu day\n");
        return;
    }

    vector<NguyenLieu> khoFile(soNguyenLieuFile);
    docFileKho(duongDan, soNguyenLieuFile, &khoFile[0]);

    for (const auto& nl : khoFile) {
        if (strcmp(nl.tenNguyenLieu, nguyenLieu->tenNguyenLieu) == 0) {
            printf("Nguyen lieu da co trong file\n");
            return;
        }
    }

    FILE* fptr = fopen(duongDan, "a");
    if (!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }

    fprintf(fptr, "%s,%s,%.2f,%.2f\n", nguyenLieu->tenNguyenLieu, nguyenLieu->donVi, nguyenLieu->soLuong, nguyenLieu->gia);
    fclose(fptr);
    printf("Nguyen lieu da duoc them vao file\n");
}

void hienThiKho(const vector<NguyenLieu>& kho) {
    if (kho.empty()) {
        printf("Chua co nguyen lieu\n");
        return;
    }

    printf("DANH SACH NGUYEN LIEU TRONG KHO:\n%-3s %-25s %-10s %-10s\n", "STT", "Ten Nguyen Lieu", "Don Vi", "So Luong");
    for (size_t i = 0; i < kho.size(); i++) {
        printf("%-3d %-25s %-10s %-10.2f\n", int(i) + 1, kho[i].tenNguyenLieu, kho[i].donVi, kho[i].soLuong);
    }
}

void themNguyenLieu(vector<NguyenLieu>& kho, const NguyenLieu& nguyenLieuMoi) {
    if (kho.size() >= MAX_NGUYEN_LIEU) {
        printf("Kho da day, khong the them nguyen lieu moi!\n");
        return;
    }

    auto it = find_if(kho.begin(), kho.end(), [&nguyenLieuMoi](const NguyenLieu& nl) {
        return strcmp(nl.tenNguyenLieu, nguyenLieuMoi.tenNguyenLieu) == 0;
    });

    if (it != kho.end()) {
        printf("Nguyen lieu nay da co trong kho\n");
        return;
    }

    kho.push_back(nguyenLieuMoi);
    printf("Da them nguyen lieu vao mang\n");
}

void xoaNguyenLieu(vector<NguyenLieu>& kho, const NguyenLieu& nguyenLieuXoa) {
    auto it = find_if(kho.begin(), kho.end(), [&nguyenLieuXoa](const NguyenLieu& nl) {
        return strcmp(nl.tenNguyenLieu, nguyenLieuXoa.tenNguyenLieu) == 0;
    });

    if (it != kho.end()) {
        kho.erase(it);
        printf("Nguyen lieu da duoc xoa\n");
    } else {
        printf("Khong tim thay nguyen lieu\n");
    }
}
void layNguyenLieu(vector<NguyenLieu>& kho, const NguyenLieu& nguyenLieuSuDung, int soMon) {
    for (auto& nl : kho) {
        if (strcmp(nguyenLieuSuDung.tenNguyenLieu, nl.tenNguyenLieu) == 0) {
            if (nguyenLieuSuDung.soLuong * soMon <= nl.soLuong) {
                nl.soLuong -= nguyenLieuSuDung.soLuong * soMon;
                return;
            }
            printf("Khong the tru di nhieu nguyen lieu nhu vay\n");
            return;
        }
    }
}

void nhapThongTinNguyenLieu(NguyenLieu* nguyenLieu) {
    chuanHoaKho(nguyenLieu, 1);
    printf("Nhap ten nguyen lieu: ");
    fgets(nguyenLieu->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    nguyenLieu->tenNguyenLieu[strcspn(nguyenLieu->tenNguyenLieu, "\n")] = '\0';

    printf("Nhap don vi do cua nguyen lieu: ");
    fgets(nguyenLieu->donVi, MAX_DO_DAI_CHUOI_DON_VI - 1, stdin);
    nguyenLieu->donVi[strcspn(nguyenLieu->donVi, "\n")] = '\0';

    printf("Nhap so luong nguyen lieu: ");
    scanf("%f", &(nguyenLieu->soLuong));
    
    printf("Nhap gia cua nguyen lieu: ");
    scanf("%f", &(nguyenLieu->gia));
}

void nhapTenNguyenLieu(NguyenLieu* nguyenLieu) {
    chuanHoaKho(nguyenLieu, 1);
    printf("Nhap ten nguyen lieu: ");
    fgets(nguyenLieu->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    nguyenLieu->tenNguyenLieu[strcspn(nguyenLieu->tenNguyenLieu, "\n")] = '\0';
}

void timKiemNguyenLieu(const vector<NguyenLieu>& kho) {
    if (kho.empty()) {
        printf("Chua co nguyen lieu\n");
        return;
    }

    char tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU];
    printf("Nhap ten nguyen lieu: ");
    fgets(tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    tenNguyenLieu[strcspn(tenNguyenLieu, "\n")] = '\0';

    printf("\nDanh sach nguyen lieu tim duoc theo ten '%s':\n%-3s %-25s %-10s %-10s\n", tenNguyenLieu, "STT", "Ten Nguyen Lieu", "Don Vi", "So Luong");
    for (size_t i = 0; i < kho.size(); i++) {
        if (strstr(kho[i].tenNguyenLieu, tenNguyenLieu)) {
            printf("%-3d %-25s %-10s %-10.2f\n", int(i) + 1, kho[i].tenNguyenLieu, kho[i].donVi, kho[i].soLuong);
        }
    }
}

void capNhatKhoTuFile(vector<NguyenLieu>& kho, const char* duongDan) {
    ifstream file(duongDan);
    string line;
    while (getline(file, line)) {
        NguyenLieu nguyenLieu;
        istringstream iss(line);
        iss >> nguyenLieu.tenNguyenLieu >> nguyenLieu.donVi >> nguyenLieu.soLuong >> nguyenLieu.gia;
        auto it = find_if(kho.begin(), kho.end(), [nguyenLieu](const NguyenLieu& nl) {
            return strcmp(nl.tenNguyenLieu, nguyenLieu.tenNguyenLieu) == 0;
        });

        if (it != kho.end()) {
            *it = nguyenLieu;
        } else {
            kho.push_back(nguyenLieu);
        }
    }
    printf("Cap nhat kho tu file thanh cong\n");
}

void capNhatKhoTuMang(const vector<NguyenLieu>& kho, const char* duongDan) {
    ofstream file(duongDan);
    for (const auto& nl : kho) {
        file << nl.tenNguyenLieu << " " << nl.donVi << " " << nl.soLuong << " " << nl.gia << endl;
    }
    printf("Cap nhat kho tu mang thanh cong\n");
}
