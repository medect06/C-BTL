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
