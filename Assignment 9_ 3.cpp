#include <iostream>
using namespace std;

// Cấu trúc Node cho danh sách liên kết
struct Nut {
    float heSo; // Hệ số của đơn thức
    int soMu;   // Số mũ của đơn thức
    Nut* lienKet; // Con trỏ trỏ đến nút tiếp theo
};

// Cấu trúc DanhSachDT đại diện cho danh sách đa thức
struct DanhSachDT {
    Nut* dau;  // Phần tử đầu tiên
    Nut* cuoi; // Phần tử cuối cùng
};

// Hàm khởi tạo danh sách đa thức
void khoiTaoDanhSach(DanhSachDT* ds) {
    ds->dau = ds->cuoi = NULL;
}

// Hàm tạo một nút mới
Nut* taoNut(float heSo, int soMu) {
    Nut* p = new Nut;
    if (p == NULL) return NULL;
    p->heSo = heSo;
    p->soMu = soMu;
    p->lienKet = NULL;
    return p;
}

// Hàm thêm nút vào danh sách
void themNut(DanhSachDT* ds, float heSo, int soMu) {
    Nut* p = taoNut(heSo, soMu);
    if (ds->dau == NULL) {
        ds->dau = ds->cuoi = p;
    }
    else {
        ds->cuoi->lienKet = p;
        ds->cuoi = p;
    }
}

// Hàm nhập đa thức từ bàn phím
void nhapDaThuc(DanhSachDT* ds) {
    float heSo;
    int soMu;
    cout << "- Bat đau nhap đa thuc (nhap he so 0 đe ket thuc): " << endl;
    do {
        cout << "Nhap he so: ";
        cin >> heSo;
        if (heSo == 0) break;
        cout << "Nhap so mu: ";
        cin >> soMu;
        themNut(ds, heSo, soMu);
    } while (heSo != 0);
}

// Hàm in đa thức ra màn hình
void inDaThuc(DanhSachDT ds) {
    Nut* p = ds.dau;
    cout << "\nf(x) = ";
    while (p != NULL) {
        cout << p->heSo << "x^" << p->soMu;
        if (p->lienKet != NULL) cout << " + ";
        p = p->lienKet;
    }
    cout << endl;
}

// Hàm cộng hai đa thức
DanhSachDT congDaThuc(DanhSachDT ds1, DanhSachDT ds2) {
    DanhSachDT ketQua;
    khoiTaoDanhSach(&ketQua);
    Nut* p1 = ds1.dau;
    Nut* p2 = ds2.dau;

    while (p1 != NULL && p2 != NULL) {
        if (p1->soMu > p2->soMu) {
            themNut(&ketQua, p1->heSo, p1->soMu);
            p1 = p1->lienKet;
        }
        else if (p1->soMu < p2->soMu) {
            themNut(&ketQua, p2->heSo, p2->soMu);
            p2 = p2->lienKet;
        }
        else {
            float tongHeSo = p1->heSo + p2->heSo;
            if (tongHeSo != 0) {
                themNut(&ketQua, tongHeSo, p1->soMu);
            }
            p1 = p1->lienKet;
            p2 = p2->lienKet;
        }
    }

    while (p1 != NULL) {
        themNut(&ketQua, p1->heSo, p1->soMu);
        p1 = p1->lienKet;
    }

    while (p2 != NULL) {
        themNut(&ketQua, p2->heSo, p2->soMu);
        p2 = p2->lienKet;
    }

    return ketQua;
}

// Hàm chính
int main() {
    DanhSachDT f, g, h;
    khoiTaoDanhSach(&f);
    khoiTaoDanhSach(&g);

    cout << "Nhap đa thuc f(x):" << endl;
    nhapDaThuc(&f);

    cout << "Nhap đa thuc g(x):" << endl;
    nhapDaThuc(&g);

    cout << "Đa thuc f(x):";
    inDaThuc(f);

    cout << "Đa thuc g(x):";
    inDaThuc(g);

    // Tính h(x) = f(x) + g(x)
    h = congDaThuc(f, g);

    cout << "Đa thuc h(x) = f(x) + g(x):";
    inDaThuc(h);

    return 0;
}