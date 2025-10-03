#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

template<typename Func>
double measureTime(Func func) {
auto start = high_resolution_clock::now();
func();
auto end = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(end - start);
return duration.count() / 1000.0; // milliseconds
}

int binary_search(const vector<int>& arr, int target) {
  int left = 0, right = arr.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

int linear_search(const vector<int>& arr, int target) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == target) return i;
  }
  return -1;
}

// int main() {
//   for (int k = 1; k < 20; k++) {
//     int n = 1 << k; // 2^k
//     vector<int> arr(n);
//     for (int i = 0; i < n; i++) arr[i] = i;

//     double time_binary = measureTime([&]() { binary_search(arr, -1); });
//     double time_linear = measureTime([&]() { linear_search(arr, -1); });

//     cout << "n = " << n << ", binary: " << time_binary << " ms, " 
//                       << " linear: " << time_linear << " ms" << endl;
//   }
// }

bool is_prime_optimized(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }
  return true;
}

bool is_prime_naive(int n) {
  if (n <= 1) return false;
  for (int i = 2; i < n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

// int main() {
//   for (int k = 1; k < 20; k++) {
//     int n = 1 << k;
//     int p = n % 2 == 0 ? n - 1 : n;
//     while (p > 1 && !is_prime_optimized(p)) p -= 2;
//     if (p < 2) p = 2;

//     double time_optimized = measureTime([&]() { is_prime_optimized(p); });
//     double time_naive = measureTime([&]() { is_prime_naive(p); });

//     cout << "n=" << n << ", prime=" << p << ", optimized: " << time_optimized << " ms, naive: " << time_naive << " ms" << endl;
//   }
//   return 0;
// }

int gcd_mod(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

int gcd_sub(int a, int b) {
  while (a != b) {
    if (a > b) a -= b;
    else b -= a;
  }
  return a;
}

// int main() {
//   for (int k = 1; k < 20; k++) {
//     int n = 1 << k;
//     int a = n, b = n / 2;

//     double time_mod = measureTime([&]() { gcd_mod(a, b); });
//     double time_sub = measureTime([&]() { gcd_sub(a, b); });

//     cout << "n=" << n << ", mod: " << time_mod << " ms, sub: " << time_sub << " ms" << endl;
//   }
//   return 0;
// }

int count_bits_loop(int n) {
  int count = 0;
  for (int i = 0; i < 32; i++) {
    if (n & (1 << i)) count++;
  }
  return count;
}

int count_bits_kern(int n) {
  int count = 0;
  while (n) {
    n &= n - 1;
    count++;
  }
  return count;
}

// int main() {
//   for (int k = 1; k < 20; k++) {
//     int n = 1 << k;
//     int num = (1 << min(k, 31)) - 1; // All 1s

//     double time_loop = measureTime([&]() { count_bits_loop(num); });
//     double time_kern = measureTime([&]() { count_bits_kern(num); });

//     cout << "n=" << n << ", num=" << num << ", loop: " << time_loop << " ms, kern: " << time_kern << " ms" << endl;
//   }
//   return 0;
// }

// a. Fibonacci
long long fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n-1) + fib_recursive(n-2);
}

long long fib_memo_helper(int n, vector<long long>& memo) {
    if (memo[n] != -1) return memo[n];
    if (n <= 1) return n;
    memo[n] = fib_memo_helper(n-1, memo) + fib_memo_helper(n-2, memo);
    return memo[n];
}

long long fib_memo(int n) {
    vector<long long> memo(n+1, -1);
    return fib_memo_helper(n, memo);
}

long long fib_iterative(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// b. Sum array DC
long long sum_dc(const vector<int>& arr, int low, int high) {
    if (low == high) return arr[low];
    int mid = (low + high) / 2;
    return sum_dc(arr, low, mid) + sum_dc(arr, mid+1, high);
}

// c. Power
long long power_naive(long long a, int n) {
    long long res = 1;
    for (int i = 0; i < n; i++) {
        res *= a;
    }
    return res;
}

long long power_dc(long long a, int n) {
    if (n == 0) return 1;
    long long half = power_dc(a, n/2);
    if (n % 2 == 0) return half * half;
    return a * half * half;
}

// d. Hanoi (count moves)
long long hanoi(int n) {
    if (n == 1) return 1;
    return hanoi(n-1) + 1 + hanoi(n-1);
}

int main() {
    // cout << "Fibonacci:" << endl;
    // for (int n = 10; n <= 39; n += 5) {
    //     if (n <= 35) {
    //         double time_rec = measureTime([&]() { fib_recursive(n); });
    //         cout << "n=" << n << ", recursive: " << time_rec << " ms" << endl;
    //     }
    //     double time_memo = measureTime([&]() { fib_memo(n); });
    //     double time_iter = measureTime([&]() { fib_iterative(n); });
    //     cout << "n=" << n << ", memo: " << time_memo << " ms, iterative: " << time_iter << " ms" << endl;
    // }

    // cout << "\nSum DC:" << endl;
    // for (int n = 10; n <= 39; n += 10) {
    //     vector<int> arr(n);
    //     for (int i = 0; i < n; i++) arr[i] = i;
    //     double time_sum = measureTime([&]() { sum_dc(arr, 0, n-1); });
    //     cout << "n=" << n << ", sum_dc: " << time_sum << " ms" << endl;
    // }

    // cout << "\nPower (a=2):" << endl;
    // for (int n = 10; n <= 39; n += 10) {
    //     double time_naive = measureTime([&]() { power_naive(2, n); });
    //     double time_dc = measureTime([&]() { power_dc(2, n); });
    //     cout << "n=" << n << ", naive: " << time_naive << " ms, dc: " << time_dc << " ms" << endl;
    // }

    cout << "\nHanoi:" << endl;
    for (int n = 10; n <= 30; n += 5) {
        double time_hanoi = measureTime([&]() { hanoi(n); });
        cout << "n=" << n << ", hanoi: " << time_hanoi << " ms" << endl;
    }

    // // Để tìm n max, chạy loop riêng và dừng khi >10s (10000 ms)
    // // Ví dụ cho fib_recursive
    // int max_n_fib = 35;
    // double time = measureTime([&]() { fib_recursive(max_n_fib); });
    // while (true) {
    //     max_n_fib++;
    //     double new_time = measureTime([&]() { fib_recursive(max_n_fib); });
    //     if (new_time > 10000) break;
    //     time = new_time;
    // }
    // cout << "Max n for fib recursive: " << max_n_fib - 1 << " (time ~" << time << " ms)" << endl;


    // int max_n_hanoi = 30;
    // time = measureTime([&]() { hanoi(max_n_hanoi); });
    // while (true) {
    //     max_n_hanoi++;
    //     double new_time = measureTime([&]() { hanoi(max_n_hanoi); });
    //     if (new_time > 10000) break;
    //     time = new_time;
    // }
    // cout << "Max n for hanoi: " << max_n_hanoi - 1 << " (time ~" << time << " ms)" << endl;

    return 0;
}