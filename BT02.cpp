#include<bits/stdc++.h>
#include <fstream>
using namespace std;
const int MAX_XE = 101;
const string TEN_FILE = "BT02.txt";
struct XeMay
{
    string nhanHieu;
    string bienSo;
    int namSanXuat;
    void inThongTin() const
    {
        cout << " Nhan hieu: " << nhanHieu
             << " Bien so: " << bienSo
             << " Nam SX: " << namSanXuat << endl;
    }
};
void themXe(XeMay DSX[], int& SLHT)
{
    if (SLHT >= MAX_XE)
        {
        cout << "LOI:danh sach day (" << MAX_XE << " xe), khong them dc xe moi." << endl;
        return;
    }
    XeMay XM;
    cout << "\n THEM XE MOI " << endl;
    cout << "Nhap nhan hieu xe (vd: Honda): ";
    getline(cin >> ws, XM.nhanHieu);
    cout << "Nhap bien so xe (vd: 15-AM 030.01): ";
    getline(cin >> ws, XM.bienSo);
    for (int i = 0; i < SLHT; ++i)
    {
        if (DSX[i].bienSo == XM.bienSo)
        {
            cout << "LOI:bien so nay da ton tai" << endl;
            return;
        }
    }
    cout << "Nhap nam san xuat: ";
    while (!(cin >> XM.namSanXuat))
    {
        cout << "dau vao khong hop le. Nhap so nam: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    DSX[SLHT] = XM;
    SLHT++;
    cout << "\n=> da them xe " << XM.nhanHieu << " (" << XM.bienSo << ") thanh cong." << endl;
}
void xoaXeTheoBienSo(XeMay DSX[], int& SLHT)
{
    if (SLHT == 0)
        {
        cout << "\ndanh sach dang trong, khong co gi de xoa." << endl;
        return;
    }
    string BSCX;
    cout << "\n XOA XE THEO BIEN SO " << endl;
    cout << "Nhap Bien so xe can xoa: ";
    getline(cin >> ws, BSCX);
    int VT = -1;
    for (int i = 0; i < SLHT; ++i)
    {
        if (DSX[i].bienSo == BSCX)
        {
            VT = i;
            break;
        }
    }
    if (VT != -1)
    {
        for (int i = VT; i < SLHT - 1; ++i) DSX[i] = DSX[i + 1];
        SLHT--;
        cout << "\n=> da xoa xe co Bien so " << BSCX << " thanh cong." << endl;
    }
    else cout << "\n=> LOI:khong tim thay xe co Bien so " << BSCX << "." << endl;
}
void hienThiDanhSach(const XeMay DSX[], int SLHT)
{
    cout << "\n DANH SACH XE MAY HIEN TAI (" << SLHT << " xe) " << endl;
    if (SLHT == 0)
        {
        cout << "danh sach hien dang trong." << endl;
        return;
    }
    for (int i = 0; i < SLHT; ++i)
    {
        cout << i + 1 << ". ";
        DSX[i].inThongTin();
    }
}
void luuDanhSachVaoFile(const XeMay DSX[], int SLHT)
{
    ofstream OF(TEN_FILE);
    if (OF.is_open())
        {
        OF << SLHT << endl;
        for (int i = 0; i < SLHT; ++i)
        {
            OF << DSX[i].nhanHieu << "|"
                    << DSX[i].bienSo << "|"
                    << DSX[i].namSanXuat << endl;
        }
        OF.close();
        cout << "\n[TDZ] da luu danh sach " << SLHT << " xe vao file **" << TEN_FILE << "**" << endl;
    }
    else
        cout << "\n[TDZ] khong the mo file **" << TEN_FILE << "** de ghi du lieu" << endl;
}
void docDanhSachTuFile(XeMay DSX[], int& SLHT)
{
    ifstream IF(TEN_FILE);
    SLHT = 0;

    if (IF.is_open())
    {
        int SLX;
        if (!(IF >> SLX))
        {
            cout << "[CB] File **" << TEN_FILE << "** bi hong hoac trong. tao danh sach moi." << endl;
            IF.close();
            return;
        }
        IF.ignore(10000, '\n');

        if (SLX > MAX_XE)
        {
             cout << "[CB] So luong xe trong file vuot qua gioi han (" << MAX_XE << "). Chi doc toi da " << MAX_XE << " xe" << endl;
             SLX = MAX_XE;
        }

        string LN;
        for (int i = 0; i < SLX; ++i)
        {
            if (getline(IF, LN))
            {
                stringstream SS(LN);
                string SG_NH, SG_BS, SG_NSX;
                int count = 0;
                if (getline(SS, SG_NH, '|') && count++ < 3)
                {
                    if (getline(SS, SG_BS, '|') && count++ < 3)
                    {
                        if (getline(SS, SG_NSX))
                        {
                            count++;
                        }
                    }
                }
                if (count == 3)
                {
                    DSX[SLHT].nhanHieu = SG_NH;
                    DSX[SLHT].bienSo = SG_BS;
                    try {
                        DSX[SLHT].namSanXuat = stoi(SG_NSX);
                        SLHT++;
                    }
                    catch (const std::exception& e)
                    {
                        cout << "[CB] loi doc nam san xuat o dong " << i + 2 << " (du lieu bi bo qua)." << endl;
                        continue;
                    }
                }
                else
                {
                    cout << "[CB] loi dinh dang du lieu o dong " << i + 2 << " (du lieu bi bo qua)." << endl;
                }
            }
        }
        IF.close();
        cout << "\n[TDZ] da doc thanh cong **" << SLHT << "** xe tu file **" << TEN_FILE << "**" << endl;
    }
    else cout << "\n[TDZ] khong tim thay file **" << TEN_FILE << "** hoac khong the mo. Bat dau voi danh sach trong" << endl;
}
int main()
{
    XeMay DSX[MAX_XE];
    int SLHT = 0;
    docDanhSachTuFile(DSX, SLHT);
    int LC;
    do {
        cout << "      CHUONG TRINH QUAN LY XE MAY" << endl;
        cout << "=============================================" << endl;
        cout << "1. Them xe moi" << endl;
        cout << "2. Xoa xe theo Bien so" << endl;
        cout << "3. Hien thi danh sach xe" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "=============================================" << endl;
        cout << "Nhap lua chon cua ban: ";
        if (!(cin >> LC))
            {
            cout << "LOL: vui long nhap so tuong ung voi chuc nang." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            LC = -1;
            continue;
        }
        switch (LC)
        {
            case 1:
                themXe(DSX, SLHT);
                break;
            case 2:
                xoaXeTheoBienSo(DSX, SLHT);
                break;
            case 3:
                hienThiDanhSach(DSX, SLHT);
                break;
            case 0:
                luuDanhSachVaoFile(DSX, SLHT);
                cout << "\nda thoat chuong trinh quan ly xe may." << endl;
                break;
            default:
                cout << "lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
    while (LC != 0);
}
