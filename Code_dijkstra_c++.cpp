#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include <algorithm>
#include <iomanip>

#define INF INT_MAX

using namespace std;

// Hàm này thực hiện thuật toán Dijkstra để tìm đường đi ngắn nhất từ nút bắt đầu đến tất cả các nút khác trong biểu đồ
vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size(); // Số lượng nodes trong biểu đồ
    vector<int> dist(n+1, INF); // Khởi tạo khoảng cách ngắn nhất tới tất cả các nút là vô cùng
    dist[start] = 0; // Khoảng cách từ nút bắt đầu đến chính nó là 0

    // Khởi tạo hàng đợi có mức độ ưu tiên tối thiểu với các cặp (khoảng cách, nút). Hàng đợi được sắp xếp theo khoảng cách tăng dần.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start}); // Bắt đầu với nút bắt đầu có khoảng cách 0

    // Trong khi vẫn còn các nút để xử lý
    while (!pq.empty()) {
        int u = pq.top().second; // node để xử lý
        int d = pq.top().first; // Khoảng cách ngắn nhất hiện tại tới nút này
        pq.pop(); // Xóa nút khỏi hàng đợi

        // Nếu khoảng cách ngắn nhất hiện tại lớn hơn khoảng cách được lưu trữ, hãy bỏ qua nút này
        if (d > dist[u]) {
            continue;
        }

        for (auto& edge : graph[u]) {
            int v = edge.first; // Nút ở đầu kia của cạnh
            int w = edge.second; // độ dài của cạnh

            // Nếu đi qua cạnh này dẫn đến đường đi tới v ngắn hơn, hãy cập nhật khoảng cách ngắn nhất và xếp hàng v
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
            // for(int i = 1; i < n; i++){
            //     cout << setw(15) << dist[i] << " "; // setw(10) sets a field width of 10
            // }
            // cout<< endl;
        }
    }

    // Trả lại khoảng cách ngắn nhất cho tất cả các nút
    return dist;
}

int main() {
    // cout<<"Nhap so luong nut va canh: \n";
    int n, m; // Số lượng nút và cạnh
    cin >> n >> m;


    vector<vector<pair<int, int>>> graph(m); // Danh sách kề của đồ thị
    // cout<<"Nhap cac canh cua do thi: \n";
    // Đọc các cạnh và thêm chúng vào danh sách kề
    for (int i = 0; i < m; i++) {
        int u, v, w; // Một cạnh từ u đến v có độ dài w
        // cout<<"Nhap canh thu "<<i+1<<": ";
        cin >> u >> v >> w;
        graph[u].push_back({v, w}); // Thêm cạnh vào danh sách kề
        graph[v].push_back({u, w}); // Vì đồ thị là vô hướng nên cũng thêm cạnh ngược
    }

    // cout<<"Nhap nut bat dau: ";
    int start; // Nút khởi đầu
    cin >> start;

    // Tìm khoảng cách ngắn nhất từ nút bắt đầu đến tất cả các nút khác
    vector<int> shortestDistances = dijkstra(graph, start);

    // In khoảng cách ngắn nhất
    for (int i = 0; i < n; i++) {
        cout << "Shortest distance from " << start << " to " << i+1 << " is " << shortestDistances[i+1] << endl;
    }

    return 0;
}

// 4 5
// 1 2 5
// 2 3 4
// 3 4 6
// 1 3 8
// 2 4 7

// 7 9
// 1 2 5
// 2 3 7
// 2 5 9
// 2 6 3
// 2 7 6
// 3 4 6
// 3 5 6
// 4 5 8
// 6 7 4
