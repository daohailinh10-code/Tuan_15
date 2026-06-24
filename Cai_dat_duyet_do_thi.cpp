#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Số lượng địa điểm
const int SO_LUONG_DINH = 11;

// Danh sách tên các thành phố
const string ten_thanh_pho[SO_LUONG_DINH] = {
    "Hà Nội", "Sơn Tây", "Hòa Bình", "Thái Nguyên", "Phủ Lý", 
    "Hải Dương", "Bắc Ninh", "Hưng Yên", "Hải Phòng", "Bắc Giang", "Uông Bí"
};

// --- CẤU TRÚC 1: DANH SÁCH KỀ DÙNG MẢNG (VECTOR) ---
class DoThiBangVector {
    vector<int> danh_sach_ke[SO_LUONG_DINH];
public:
    void them_canh(int u, int v) {
        danh_sach_ke[u].push_back(v);
        danh_sach_ke[v].push_back(u);
    }

    void duyet_BFS(int dinh_bat_dau) {
        vector<bool> da_tham(SO_LUONG_DINH, false);
        queue<int> hang_doi;

        da_tham[dinh_bat_dau] = true;
        hang_doi.push(dinh_bat_dau);

        cout << "Thứ tự duyệt BFS (Dùng Mảng/Vector):" << endl;
        while (!hang_doi.empty()) {
            int hien_tai = hang_doi.front();
            hang_doi.pop();
            cout << ten_thanh_pho[hien_tai] << (hang_doi.empty() ? "" : " -> ");

            for (int lang_gieng : danh_sach_ke[hien_tai]) {
                if (!da_tham[lang_gieng]) {
                    da_tham[lang_gieng] = true;
                    hang_doi.push(lang_gieng);
                }
            }
        }
        cout << " -> Hết." << endl;
    }
};

// --- CẤU TRÚC 2: DANH SÁCH KỀ DÙNG DANH SÁCH LIÊN KẾT ---
struct Nut {
    int id_dinh;
    Nut* tiep_theo;
    Nut(int id) : id_dinh(id), tiep_theo(nullptr) {}
};

class DoThiBangDSLK {
    Nut* danh_sach_ke[SO_LUONG_DINH];
public:
    DoThiBangDSLK() { 
        for(int i = 0; i < SO_LUONG_DINH; ++i) danh_sach_ke[i] = nullptr; 
    }

    void them_canh(int u, int v) {
        Nut* nut_moi = new Nut(v);
        nut_moi->tiep_theo = danh_sach_ke[u];
        danh_sach_ke[u] = nut_moi;

        nut_moi = new Nut(u);
        nut_moi->tiep_theo = danh_sach_ke[v];
        danh_sach_ke[v] = nut_moi;
    }

    void duyet_BFS(int dinh_bat_dau) {
        vector<bool> da_tham(SO_LUONG_DINH, false);
        queue<int> hang_doi;

        da_tham[dinh_bat_dau] = true;
        hang_doi.push(dinh_bat_dau);

        cout << "Thứ tự duyệt BFS (Dùng Danh sách liên kết):" << endl;
        while (!hang_doi.empty()) {
            int hien_tai = hang_doi.front();
            hang_doi.pop();
            cout << ten_thanh_pho[hien_tai] << (hang_doi.empty() ? "" : " -> ");

            Nut* tam = danh_sach_ke[hien_tai];
            while (tam != nullptr) {
                if (!da_tham[tam->id_dinh]) {
                    da_tham[tam->id_dinh] = true;
                    hang_doi.push(tam->id_dinh);
                }
                tam = tam->tiep_theo;
            }
        }
        cout << " -> Hết." << endl;
    }

    ~DoThiBangDSLK() {
        for (int i = 0; i < SO_LUONG_DINH; ++i) {
            Nut* tam = danh_sach_ke[i];
            while (tam) {
                Nut* xoa = tam;
                tam = tam->tiep_theo;
                delete xoa;
            }
        }
    }
};

int main() {
    DoThiBangVector do_thi_1;
    DoThiBangDSLK do_thi_2;

    // Danh sách các kết nối đường bộ
    pair<int, int> duong_di[] = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, 
        {4, 7}, {5, 7}, {5, 8}, {6, 9}, {6, 10}, {9, 10}, {8, 10}
    };

    for (auto& canh : duong_di) {
        do_thi_1.them_canh(canh.first, canh.second);
        do_thi_2.them_canh(canh.first, canh.second);
    }

    // Duyệt bắt đầu từ Hà Nội (ID = 0)
    do_thi_1.duyet_BFS(0);
    cout << "\n---------------------------------------------\n" << endl;
    do_thi_2.duyet_BFS(0);

    return 0;
}
