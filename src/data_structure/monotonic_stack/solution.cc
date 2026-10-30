#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n) || n < 0) {
        return 0;
    }

    vector<int64_t> h(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> h[static_cast<size_t>(i)];
    }

    int64_t max_area = 0;
    vector<int> st;
    st.reserve(static_cast<size_t>(n));

    for (int i = 0; i <= n; ++i) {
        int64_t cur_h = (i == n) ? -1 : h[static_cast<size_t>(i)];
        while (!st.empty() && h[static_cast<size_t>(st.back())] >= cur_h) {
            int64_t height = h[static_cast<size_t>(st.back())];
            st.pop_back();
            int64_t width = st.empty() ? static_cast<int64_t>(i)
                                       : static_cast<int64_t>(i - st.back() - 1);
            max_area = max(max_area, height * width);
        }
        st.push_back(i);
    }

    vector<int> span(static_cast<size_t>(n));
    st.clear();
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && h[static_cast<size_t>(st.back())] <= h[static_cast<size_t>(i)]) {
            st.pop_back();
        }
        span[static_cast<size_t>(i)] = st.empty() ? (i + 1) : (i - st.back());
        st.push_back(i);
    }

    cout << max_area << "\n";
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << span[static_cast<size_t>(i)];
    }
    cout << "\n";

    return 0;
}
