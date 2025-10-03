import pandas as pd

# Dữ liệu từ kết quả chạy
data = [
    (2, 0, 0),
    (4, 0, 0),
    (8, 0, 0),
    (16, 0, 0),
    (32, 0, 0),
    (64, 0, 0),
    (128, 0, 0),
    (256, 0, 0),
    (512, 0, 0),
    (1024, 0, 0),
    (2048, 0, 0),
    (4096, 0, 0),
    (8192, 0, 0),
    (16384, 0, 0),
    (32768, 0, 1.001),
    (65536, 0, 0.999),
    (131072, 0, 1.825),
    (262144, 0, 3.999),
    (524288, 0, 9.771)
]

# Tạo DataFrame
df = pd.DataFrame(data, columns=["n", "BinarySearch(ms)", "LinearSearch(ms)"])

df.to_csv("search_times.csv", index=False)

print(df)
