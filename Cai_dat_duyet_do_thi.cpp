#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Số lượng đỉnh của đồ thị
const int V = 11;

// Mảng chuyển đổi từ ID sang tên Thành phố để in kết quả
const string cities[V] = {
    "Hà nội", "Sơn tây", "Hòa bình", "Thái nguyên", "Phủ lý", 
    "Hải dương", "Bắc ninh", "Hưng yên", "Hải phòng", "Bắc giang", "Uông bí"
};

// Cấu trúc một nút cho Danh sách liên kết
struct Node {
    int vertex;
    Node* next;
    Node(int v) : vertex(v), next(nullptr) {}
};

// --- CẤU TRÚC 1: DANH SÁCH KỀ DÙNG MẢNG (VECTOR) ---
class GraphArray {
    vector<int> adj[V];
public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Đồ thị vô hướng
    }

    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "Thứ tự duyệt BFS (Dùng Mảng kề): \n  ";
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << cities[curr] << " -> ";

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "Hết.\n";
    }
};

// --- CẤU TRÚC 2: DANH SÁCH KỀ DÙNG DANH SÁCH LIÊN KẾT ---
class GraphLinkedList {
    Node* adj[V];
public:
    GraphLinkedList() {
        for (int i = 0; i < V; ++i) adj[i] = nullptr;
    }

    // Thêm vào đầu danh sách liên kết
    void addEdge(int u, int v) {
        Node* newNode = new Node(v);
        newNode->next = adj[u];
        adj[u] = newNode;

        newNode = new Node(u);
        newNode->next = adj[v];
        adj[v] = newNode;
    }

    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "Thứ tự duyệt BFS (Dùng Danh sách liên kết): \n  ";
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << cities[curr] << " -> ";

            Node* temp = adj[curr];
            while (temp != nullptr) {
                int neighbor = temp->vertex;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
                temp = temp->next;
            }
        }
        cout << "Hết.\n";
    }

    // Giải phóng bộ nhớ giải thuật kết thúc
    ~GraphLinkedList() {
        for (int i = 0; i < V; ++i) {
            Node* temp = adj[i];
            while (temp != nullptr) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
        }
    }
};

int main() {
    // Khởi tạo 2 kiểu cấu trúc đồ thị
    GraphArray g1;
    GraphLinkedList g2;

    // Danh sách các cạnh từ hình vẽ (u, v)
    pair<int, int> edges[] = {
        {0, 1},  // Hà Nội - Sơn Tây (D6)
        {0, 2},  // Hà Nội - Hòa Bình (D5)
        {0, 3},  // Hà Nội - Thái Nguyên (D7)
        {0, 4},  // Hà Nội - Phủ Lý (D4)
        {0, 5},  // Hà Nội - Hải Dương (D1)
        {0, 6},  // Hà Nội - Bắc Ninh (D8)
        {4, 7},  // Phủ Lý - Hưng Yên (D3)
        {5, 7},  // Hải Dương - Hưng Yên (D2)
        {5, 8},  // Hải Dương - Hải Phòng (D13)
        {6, 9},  // Bắc Ninh - Bắc Giang (D9)
        {6, 10}, // Bắc Ninh - Uông Bí (D11)
        {9, 10}, // Bắc Giang - Uông Bí (D10)
        {8, 10}  // Hải Phòng - Uông Bí (D12)
    };

    // Nạp dữ liệu vào đồ thị
    for (auto edge : edges) {
        g1.addEdge(edge.first, edge.second);
        g2.addEdge(edge.first, edge.second);
    }

    // Đỉnh xuất phát: Hà Nội tương ứng với ID = 0
    int startNode = 0;

    // Chạy thử nghiệm và xuất kết quả
    g1.BFS(startNode);
    cout << "\n---------------------------------------------\n\n";
    g2.BFS(startNode);

    return 0;
}
