Chúng ta sẽ sử dụng cờ `-fsanitize=undefined` (UBSan) để bắt lỗi tràn số này.

```bash
cmake -B build
cmake --build build
./build/app_ub

```
Khi chạy chương trình, bạn sẽ quan sát thấy hai hiện tượng vật lý sau:

1. **Biến chưa khởi tạo (Garbage Value):** Giá trị in ra của `garbageValue` sẽ là một con số vô nghĩa (ví dụ: `32767`, `1928374`, hoặc `0`). Nó đơn giản là đang đọc các byte rác do một phần mềm khác vô tình để lại trên thanh RAM của bạn trước đó. Nếu bạn dùng biến này làm điều kiện vòng lặp, chương trình có thể chạy vô hạn. Trong thực tế, compiler sẽ cảnh báo lỗi này rất sớm (đó là lý do ta phải dùng `-Wno-uninitialized` để cố tình bỏ qua).
2. **Tràn số nguyên có dấu (Signed Integer Overflow):** Khác với số không dấu (`unsigned int`) vốn được C++ cho phép quay vòng (wrap-around) về 0 khi bị tràn, số có dấu (`int`) bị cấm tràn.
* Ngay khi phép tính `maxInt + 1` được thực thi, **UBSan** sẽ đánh sập chương trình ngay lập tức và in ra thông báo lỗi màu đỏ: `runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'`.
* **Bản chất:** Trình biên dịch C++ luôn mặc định rằng *UB không bao giờ xảy ra*. Nếu bạn không dùng UBSan và biên dịch với cờ `-O3`, trình biên dịch có thể lờ đi phép cộng đó, hoặc tự động xóa bỏ các câu lệnh `if` kiểm tra lỗi bên dưới đoạn UB này (Dead Code Elimination), dẫn đến toàn bộ logic bảo mật của ứng dụng bị vô hiệu hóa hoàn toàn.