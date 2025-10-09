#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x;
    double y;
};

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool compareX(Point a, Point b) {
        return a.x < b.x;
}

bool compareY(Point a, Point b) {
        return a.y < b.y;
}

double bruteForce(vector<Point>& P) {
    double d = 1e18;
    for (int i = 0; i < (int)P.size(); ++i)
        for (int j = i + 1; j < (int)P.size(); ++j)
            d = min(d, distance(P[i], P[j]));
    
    return d;
}

double closestPair(vector<Point>& Px, vector<Point>& Py) {
    int n = Px.size();
    if (n <= 3) return bruteForce(Px); 

    int mid = n / 2;
    double midX = Px[mid].x;

    vector<Point> Pxl(Px.begin(), Px.begin() + mid);
    vector<Point> Pxr(Px.begin() + mid, Px.end());

    vector<Point> Pyl, Pyr;
    for (auto &p : Py) {
        if (p.x <= midX)
            Pyl.push_back(p);
        else
            Pyr.push_back(p);
    }

    double d1 = closestPair(Pxl, Pyl);
    double d2 = closestPair(Pxr, Pyr);
    double d = min(d1, d2);

    vector<Point> Sy;
    for (auto &p : Py)
        if (fabs(p.x - midX) < d)
            Sy.push_back(p);

    for (int i = 0; i < (int)Sy.size(); ++i) {
        for (int j = i + 1; j < (int)Sy.size() && (Sy[j].y - Sy[i].y) < d && j - i <= 6; ++j) {
            d = min(d, distance(Sy[i], Sy[j]));
        }
    }

    return d;
}

int main() {

    vector<Point> P = {{1, 1}, {2, 2}, {3, 3}, {10, 10}, {11, 11}, {12, 12}, {6, 5}};
    int n = 7;

    vector<Point> Px = P, Py = P;
    sort(Px.begin(), Px.end(), compareX);
    sort(Py.begin(), Py.end(), compareY);

    double ans = closestPair(Px, Py);
    cout << fixed << setprecision(6);
    cout << "Min distance: " << ans << endl;
}