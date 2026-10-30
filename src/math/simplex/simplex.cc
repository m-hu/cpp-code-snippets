#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;
const double INF = 1e18;

// Two-Phase / Standard Simplex for Linear Programming
// Maximize c^T x subject to A x <= b, x >= 0
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m = 0, n = 0; // m constraints, n variables
    if (!(cin >> m >> n)) return 0;

    // Tableau size: (m + 1) rows, (n + m + 1) columns
    // Row 0..m-1: constraints with slack variables
    // Row m: objective row
    vector<vector<double>> tab(static_cast<size_t>(m + 1), vector<double>(static_cast<size_t>(n + m + 1), 0.0));

    // Objective function coefficients
    for (int j = 0; j < n; ++j) {
        double c = 0;
        cin >> c;
        tab[static_cast<size_t>(m)][static_cast<size_t>(j)] = -c; // Maximize sum(c_j * x_j)
    }

    // Constraints: A_i x <= b_i
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> tab[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
        tab[static_cast<size_t>(i)][static_cast<size_t>(n + i)] = 1.0; // Slack variable
        cin >> tab[static_cast<size_t>(i)][static_cast<size_t>(n + m)]; // RHS b_i
    }

    // Simplex pivot iterations
    while (true) {
        // Find entering variable (most negative in objective row)
        int enter_col = -1;
        double min_val = -EPS;
        for (int j = 0; j < n + m; ++j) {
            if (tab[static_cast<size_t>(m)][static_cast<size_t>(j)] < min_val) {
                min_val = tab[static_cast<size_t>(m)][static_cast<size_t>(j)];
                enter_col = j;
            }
        }

        if (enter_col == -1) {
            // Optimal solution reached
            cout << "OPTIMAL\n";
            cout << fixed << setprecision(2) << tab[static_cast<size_t>(m)][static_cast<size_t>(n + m)] << "\n";
            return 0;
        }

        // Find leaving variable (minimum ratio test)
        int leave_row = -1;
        double min_ratio = INF;
        for (int i = 0; i < m; ++i) {
            double coeff = tab[static_cast<size_t>(i)][static_cast<size_t>(enter_col)];
            if (coeff > EPS) {
                double ratio = tab[static_cast<size_t>(i)][static_cast<size_t>(n + m)] / coeff;
                if (ratio < min_ratio - EPS) {
                    min_ratio = ratio;
                    leave_row = i;
                }
            }
        }

        if (leave_row == -1) {
            cout << "UNBOUNDED\n";
            return 0;
        }

        // Pivot on (leave_row, enter_col)
        double pivot_val = tab[static_cast<size_t>(leave_row)][static_cast<size_t>(enter_col)];
        for (int j = 0; j <= n + m; ++j) {
            tab[static_cast<size_t>(leave_row)][static_cast<size_t>(j)] /= pivot_val;
        }

        for (int i = 0; i <= m; ++i) {
            if (i != leave_row) {
                double factor = tab[static_cast<size_t>(i)][static_cast<size_t>(enter_col)];
                if (abs(factor) > EPS) {
                    for (int j = 0; j <= n + m; ++j) {
                        tab[static_cast<size_t>(i)][static_cast<size_t>(j)] -= factor * tab[static_cast<size_t>(leave_row)][static_cast<size_t>(j)];
                    }
                }
            }
        }
    }

    return 0;
}
