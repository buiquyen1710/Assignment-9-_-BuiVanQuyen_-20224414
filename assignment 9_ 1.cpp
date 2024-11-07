#include<iostream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node* link;
};

struct List {
    Node* first;
    Node* last;
};

// Hàm so sánh chu?i 
int sosanhchuoi(const char* chuoi1, const char* chuoi2) {
    while (*chuoi1 && (*chuoi1 == *chuoi2)) {
        chuoi1++;
        chuoi2++;
    }
    return *(unsigned char*)chuoi1 - *(unsigned char*)chuoi2;
}

// Kh?i t?o danh sách r?ng
void danhsachrong(List& list) {
    list.first = NULL;
    list.last = NULL;
}

// Hàm nh?p thông tin sinh viên
SinhVien nhapthongtin() {
    SinhVien sv;
    cout << "Nhap MSSV: ";
    cin >> sv.maSV;
    cout << "Nhap ho ten sinh vien: ";
    cin >> sv.hoTen;
    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.gioiTinh;
    cout << "Nhap Ngay Thang Nam Sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Nhap dia chi sinh vien: ";
    cin >> sv.diaChi;
    cout << "Nhap lop sinh vien: ";
    cin >> sv.lop;
    cout << "Nhap khoa sinh vien: ";
    cin >> sv.khoa;
    return sv;
}

// Hàm in thông tin sinh viên
void inthongtin(SinhVien sv) {
    cout << "MSSV: " << sv.maSV << endl;
    cout << "Ho va ten: " << sv.hoTen << endl;
    cout << "Gioi tinh: " << (sv.gioiTinh == 1 ? "Nam" : "Nu") << endl;
    cout << "Ngay sinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << endl;
    cout << "Dia chi: " << sv.diaChi << endl;
    cout << "Lop: " << sv.lop << endl;
    cout << "Khoa: " << sv.khoa << endl;
}

// Hàm thêm sinh viên vào danh sách dã s?p x?p
void themsinhvien(List& list, SinhVien sv) {
    Node* newnode = new Node;
    newnode->data = sv;
    newnode->link = NULL;

    // N?u danh sách r?ng
    if (list.first == NULL) {
        list.first = list.last = newnode;
        return;
    }

    Node* current = list.first;
    Node* prev = NULL;

    // Tìm v? trí d? chèn sinh viên vào danh sách dã s?p x?p
    while (current != NULL && sosanhchuoi(current->data.maSV, sv.maSV) < 0) {
        prev = current;
        current = current->link;
    }

    // Chèn vào d?u danh sách
    if (prev == NULL) {
        newnode->link = list.first;
        list.first = newnode;
    }
    // Chèn vào gi?a ho?c cu?i
    else {
        prev->link = newnode;
        newnode->link = current;
    }

    // C?p nh?t "last" n?u chèn ? cu?i danh sách
    if (current == NULL) {
        list.last = newnode;
    }
}

// Hàm in danh sách sinh viên
void indanhsachsinhvien(List list) {
    Node* current = list.first;
    while (current != NULL) {
        inthongtin(current->data);
        cout << endl;
        current = current->link;
    }
}

// Hàm tìm sinh viên có cùng ngày sinh
void timkiemcungngaysinh(List list, Ngay date) {
    Node* current = list.first;
    bool timthay = false;

    while (current != NULL) {
        if (current->data.ngaySinh.ngay == date.ngay &&
            current->data.ngaySinh.thang == date.thang &&
            current->data.ngaySinh.nam == date.nam) {
            inthongtin(current->data);
            timthay = true;
        }
        current = current->link;
    }

    if (!timthay) {
        cout << "Khong tim thay sinh vien co cung ngay sinh" << endl;
    }
}

// Hàm xóa sinh viên có cùng ngày sinh
void xoasinhviencungngaysinh(List& list, Ngay date) {
    Node* current = list.first;
    Node* prev = NULL;
    bool timthay = false;

    while (current != NULL) {
        // N?u sinh viên có ngày sinh trùng kh?p
        if (current->data.ngaySinh.ngay == date.ngay &&
            current->data.ngaySinh.thang == date.thang &&
            current->data.ngaySinh.nam == date.nam) {

            timthay = true;

            // Xóa sinh viên d?u danh sách
            if (prev == NULL) {
                list.first = current->link;
                delete current;
                current = list.first;
            }
            // Xóa sinh viên gi?a ho?c cu?i
            else {
                prev->link = current->link;
                delete current;
                current = prev->link;
            }

            // C?p nh?t con tr? last n?u xóa ? cu?i danh sách
            if (current == NULL) {
                list.last = prev;
            }
        }
        else {
            prev = current;
            current = current->link;
        }
    }

    if (!timthay) {
        cout << "Khong tim thay sinh vien nao co cung ngay sinh de xoa!" << endl;
    }
}

int main() {
    List list;
    danhsachrong(list);

    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    // Nh?p danh sách sinh viên và thêm vào danh sách dã s?p x?p
    for (int i = 0; i < n; i++) {
        SinhVien sv = nhapthongtin();
        themsinhvien(list, sv);
    }
    cout << endl;

    // In danh sách sinh viên dã s?p x?p
    cout << "Danh sach sinh vien sau khi sap xep theo ma SV:" << endl;
    indanhsachsinhvien(list);
    cout << endl;

    // Thêm m?t sinh viên m?i và gi? danh sách s?p x?p
    cout << "Nhap thong tin sinh vien moi: " << endl;
    SinhVien sv = nhapthongtin();
    themsinhvien(list, sv);

    // In l?i danh sách sau khi thêm sinh viên m?i
    cout << "Danh sach sinh vien sau khi them sinh vien moi:" << endl;
    indanhsachsinhvien(list);
    cout << endl;

    // Tìm sinh viên có cùng ngày sinh
    Ngay ngay;
    cout << "Nhap ngay sinh (dd mm yyyy) de tim sinh vien: ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
    cout << "Sinh vien co cung ngay sinh: " << endl;
    timkiemcungngaysinh(list, ngay);
    cout << endl;

    // Xóa sinh viên có cùng ngày sinh
    cout << "Nhap ngay sinh (dd mm yyyy) de xoa sinh vien: ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
    xoasinhviencungngaysinh(list, ngay);
    cout << "Danh sach sinh vien sau khi xoa sinh vien co cung ngay sinh:" << endl;
    indanhsachsinhvien(list);

    return 0;
}
