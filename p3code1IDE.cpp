#include <iostream>
#include <string>
using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcsLength(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    return L[m][n];
}

string findLCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    int index = L[m][n];
    string lcs(index, ' ');

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: program1.exe <first-string> <second-string>" << endl;
        return 1;
    }

    string X = argv[1];
    string Y = argv[2];

    int length = lcsLength(X, Y);
    string lcs = findLCS(X, Y);

    cout << "Length of LCS: " << length << endl;
    cout << "LCS: " << lcs << endl;

    return 0;
}

