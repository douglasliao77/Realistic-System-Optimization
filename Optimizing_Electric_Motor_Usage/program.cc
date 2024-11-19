#include <iostream>
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int> ;
using vvi = vector<vi>;

const int INF = 1e9;
int B, scal = 1,nlinks = 0;
string nr;

vi LTYPES;
vector<double> LDIST;
vvi A(1000, vi(4));
vvi C(1000, vi(4));

vvi LIBATT = {
    {12, 8, 5, 0},
    {11, 7, 4, 0},
    {10, 6, 3, 0},
    {10, 6, 3, 0},
    {12, 8, 5, 0}
};

vvi LICOST = {
    {2, 4, 7, 10},
    {1, 4, 7, 10},
    {1, 5, 8, 14},
    {1, 6, 10, 17},
    {1, 7, 15, 20}
};

void setup(string nr) {
    ifstream f("data/path" + nr + ".txt");
    double dist;
    double type;
    f >> B >> nlinks;
   
    for (int i=0;i<nlinks;++i) {
        f >> type >> dist;
        LDIST.push_back(dist);
        LTYPES.push_back(type);
    }

    // Setup data: a and c
    for (int j=0;j<nlinks;++j) {
        for (int k=0;k<4;++k) {
            C[j][k] = static_cast<int>(std::round(LDIST[j] * LICOST[LTYPES[j]-1][k] / scal));
            A[j][k] = static_cast<int>(std::round(LDIST[j] * LIBATT[LTYPES[j]-1][k] / scal));
        }
    }
}

void solve() {
    vvi table(nlinks + 1, vi(B+1,INF));
    vvi path(nlinks, vi(B+1,-1));

    // Starts at i=0 with full battery which cost zero
    table[0][B] = 0;

    // Fill out the table
    for (int i=0; i<nlinks; ++i) {
        for (int L0 = 0; L0 <= B; ++L0) {
            if (table[i][L0] != INF) {
                for (int k=0; k<4; ++k) {
                    int newL0 = L0 - A[i][k];
                    if (newL0 >= 0) {
                        int newCost = table[i][L0] + C[i][k];
                        if (newCost < table[i + 1][newL0]) {
                            table[i + 1][newL0] = newCost;
                            path[i][newL0] = k; 
                        }
                    }
                }
            }
        }
    }

    // All the possible solutons are in step nlinks (last)
    int minCost = INF, bestL0 = -1;
    for (int L0=0; L0<=B; ++L0) {
        if (table[nlinks][L0] < minCost) {
            minCost = table[nlinks][L0];
            bestL0 = L0;
        }
    }

    cout << "#-------------------------------------# \n";
    cout << "Path with " << nlinks << " links read from file " << nr << "\n";
    cout << "Initial battery level " << B << "\n";
    cout << "#-------------------------------------# \n";
    cout << "Optimal cost: " << minCost << "\n";
    cout << "#-------------------------------------# \n";
    cout << "Final battery level: " << bestL0 << "\n";
    cout << "#-------------------------------------# \n";

    // Backtrack to find the path
    vector<int> optPath;
    int L0 = bestL0;
    for (int i=nlinks-1;i >= 0; --i) {
        int k = path[i][L0];
        optPath.push_back(k);
        L0 += A[i][k]; 
    }
    reverse(optPath.begin(), optPath.end());

    cout << "Path: ";
    for (int k : optPath) {
        cout << k + 1 << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    if (argc != 2) {
        cout << "You forgot to specify nr as argument \n";
        return 0;
    }
    nr = argv[1];
    setup(nr);
    solve();
}