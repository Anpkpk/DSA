#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Rectangle {
    Point top_left;
    Point bot_right;
};

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double area(Rectangle r) {
    double width = abs(r.bot_right.x - r.top_left.x);
    double height = abs(r.bot_right.y - r.top_left.y);

    return width*height;
}

double perimeter(Rectangle r) {
    double width = abs(r.bot_right.x - r.top_left.x);
    double height = abs(r.bot_right.y - r.top_left.y);

    return 2*(width + height);
}

bool contains(Rectangle r, Point p) {
    return (p.x >= r.top_left.x && p.x <= r.bot_right.x &&
            p.y >= r.top_left.y && p.y <= r.bot_right.y);
}

int main() {
    Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    cout << distance(p1, p2) << endl;

    Rectangle r = {p1, p2};

    cout << area(r) << " " << perimeter(r) << endl;

    Point p3 = {3, 4};
    cout << contains(r, p3);
}