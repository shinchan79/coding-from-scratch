* **`++i` (Pre-increment) vs `i++` (Post-increment):**
* Với kiểu dữ liệu cơ bản (như `int`), compiler đủ thông minh để tối ưu hóa cả 2 thành một lệnh Assembly giống hệt nhau (nếu bạn không lấy giá trị trả về).
* Với kiểu dữ liệu phức tạp (như class, struct, iterator trong STL), `i++` bắt buộc phải tạo ra một biến tạm (temp copy) để lưu trạng thái cũ trước khi tăng, sau đó trả về biến tạm đó. `++i` tăng trực tiếp và trả về tham chiếu (reference). Luôn có thói quen dùng `++i` trong vòng lặp `for` để triệt tiêu chi phí copy dư thừa.


* **`constexpr` (Compile-time computation):**
* Ép compiler thực hiện tính toán ngay trong lúc build (Translation Unit).
* Kết quả cuối cùng được nhúng thẳng vào mã máy dưới dạng một hằng số (hardcoded value). Khi file thực thi (binary) chạy, CPU không tốn bất kỳ một clock cycle nào để tính toán lại kết quả đó, mang lại hiệu năng tối đa (zero-overhead at runtime).