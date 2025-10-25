#include <bits/stdc++.h>
using namespace std;

struct intervals {
    int time_start, time_end;
};

bool cmp(intervals a, intervals b) {
    return a.time_start < b.time_start;
}

intervals *merge_intervals(intervals *inter, int n, int &new_n) {
    sort(inter, inter + n, cmp);

    intervals *merged = new intervals[n];
    merged[0].time_start = inter[0].time_start;
    merged[0].time_end = inter[0].time_end;
    
    int k = 0;

    for (int i = 1; i < n; i++) {
        if (inter[i].time_start <= merged[k].time_end) {
            merged[k].time_end = max(merged[k].time_end, inter[i].time_end);
        } else {
            k++;
            merged[k].time_start = inter[i].time_start;
            merged[k].time_end = inter[i].time_end;
        }
    }

    new_n = k + 1;
    return merged;
}

int main() {
    intervals inter[] = {
        {1, 3},
        {2, 6},
        {8, 10},
        {15, 18}
    };

    int new_n;
    intervals *result = merge_intervals(inter, 4, new_n);

    for (int i = 0; i < new_n; i++) {
        cout << result[i].time_start << " " << result[i].time_end << endl;
    }
}
