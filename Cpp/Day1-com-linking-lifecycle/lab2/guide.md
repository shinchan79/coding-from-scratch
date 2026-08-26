```
clang++ -c math_lib.cpp -o math_lib.o
```

Giải thích: Cờ -c yêu cầu trình biên dịch chỉ chạy đến bước Assembling (dịch ra mã máy nhị phân) và dừng lại, tạo ra file math_lib.o. Không thực hiện Linking.
```
ar rcs libmath.a math_lib.o
```
Sử dụng công cụ ar (Archive) của hệ điều hành để gom các file .o lại thành một thư viện.
Giải thích quy ước đặt tên (bắt buộc): Tên thư viện tĩnh trên macOS/Linux luôn phải có tiền tố là lib và hậu tố là .a. Ở đây, thư viện của chúng ta có tên gốc là math, nên file xuất ra phải là libmath.a.
```
clang++ main.cpp -L. -lmath -o my_app
```
Giải thích các cờ liên kết:

-L. : Nói cho Linker biết hãy tìm kiếm các file thư viện ở thư mục hiện tại (.). Nếu không có cờ này, Linker chỉ tìm trong các thư mục hệ thống (như /usr/lib).

-lmath : Nói cho Linker biết cần liên kết với thư viện tên là math. Trình liên kết sẽ tự động thêm tiền tố lib và hậu tố .a để đi tìm file libmath.a trong các đường dẫn đã cung cấp.

```
./my_app
```

Bản chất của Static Library: Khi chạy lệnh liên kết ở bước 3, Linker đã trích xuất mã máy của hàm add từ bên trong libmath.a và "copy-paste" vĩnh viễn trực tiếp vào file thực thi my_app. Sau khi file my_app được tạo ra, bạn có thể xóa file libmath.a đi mà chương trình vẫn chạy bình thường.