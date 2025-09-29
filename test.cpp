#include <iostream>
using namespace std;

void so_nguyen_to(int a, int b)
{
    if (b >= a)
    {
        for (int i = a; i <= b; i++)
        {
            int dem = 0;
            for (int j = 1; j < 10; j++)
            {
                if (i % j == 0)
                {
                    dem += 1;
                }
            }
            cout << "so cac uoc cua " << i << " :" << dem << endl;
            if (dem < 2)
            {
                cout << "Cac so nguyen to" << i << " ";
            }
        }
    }
    else
    {
        cout << "Error" << endl;
    }
}
int main(void)
{
    int a, b;
    cout << "Nhap gia tri a: " << endl;
    cin >> a;
    cout << "Nhap gia tri b: " << endl;
    cin >> b;
    so_nguyen_to(a, b);
}