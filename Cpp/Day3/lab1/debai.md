### Lab Ngày 3: Phép thử L-value, R-value và Cơ chế Swap

**Nhiệm vụ 1: Chứng minh L-value có địa chỉ, R-value thì không**

1. Khai báo một biến `int a = 10;`. Biến `a` lúc này là một **Object** (vùng nhớ có tên `a`, kiểu `int`, tuổi thọ trong block code đó).
2. Thử in ra địa chỉ của biến `a` bằng toán tử `&` (`std::cout << &a;`). Quan sát kết quả.
3. Thử in ra địa chỉ của con số `10` (`std::cout << &10;`) hoặc một biểu thức tạm (`std::cout << &(a + 5);`).
4. **Kết luận:** Bước 3 sẽ bị trình biên dịch (compiler) báo lỗi ngay lập tức. Điều này chứng minh `10` hoặc `a + 5` là **R-value** (giá trị tạm thời, được CPU tính toán trên thanh ghi, không có địa chỉ bộ nhớ cố định để lấy ra).

**Nhiệm vụ 2: Viết hàm Swap và bắt lỗi R-value**

1. Viết một hàm hoán đổi yêu cầu truyền tham chiếu (L-value reference):
```cpp
void my_swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

```


2. Khai báo `int m = 5, n = 10;`, sau đó gọi `my_swap(m, n);`. Việc hoán đổi sẽ thành công vì `m` và `n` là các **L-value**.
3. **Thử nghiệm sinh lỗi:** Cố tình gọi `my_swap(m, 20);` hoặc `my_swap(15, 10);`.
4. **Kết luận:** Trình biên dịch sẽ từ chối biên dịch. Hàm của bạn yêu cầu một "tham chiếu đến L-value" (`int&`), tức là nó cần một vùng nhớ cố định để thao tác. Việc bạn truyền số `20` (một R-value) vào là vô lý vì R-value không có vùng nhớ cố định để lưu giá trị mới.

**Nhiệm vụ 3: Quan sát di chuyển dữ liệu (Pass-by-value vs Pass-by-reference)**

1. Viết thêm một hàm `bad_swap(int x, int y)` (truyền tham trị - pass-by-value) với nội dung hoán đổi tương tự.
2. Trong hàm `main()`, in ra địa chỉ của 2 biến truyền vào.
3. Bên trong hàm `bad_swap`, in ra địa chỉ của `x` và `y`.
4. **Kết luận:** Bạn sẽ thấy địa chỉ bên trong `bad_swap` khác hoàn toàn địa chỉ ngoài `main()`. Khi truyền tham trị, C++ đã âm thầm copy tạo ra các **Object tạm thời** (R-value). Việc hoán đổi chỉ xảy ra trên các bản sao này rồi bị hủy bỏ ngay khi thoát hàm, khiến dữ liệu gốc ở `main()` không suy xuyển. Đây là lý do tiêu chuẩn vàng của C++ là dùng tham chiếu (`T&`) để tránh copy vô ích.