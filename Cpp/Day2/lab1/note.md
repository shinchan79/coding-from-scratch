```bash
cmake -B build
cmake --build build
./build/app_types

```
1. **Tại sao `char` cần dấu `+`?** Kích thước của `char` luôn là 1 byte (giá trị thực tế từ -128 đến 127). Tuy nhiên, `std::cout` được thiết kế để hiển thị `char` dưới dạng ký tự văn bản. Nếu bạn không thêm dấu `+` (Unary Plus), console sẽ in ra một khoảng trắng vô hình hoặc ký tự rác. Dấu `+` ép C++ thực hiện *Numeric Promotion*, nâng cấp `char` thành `int` để hiển thị con số bề chìm.
2. **Sự khác biệt giữa `min()` và `lowest()` đối với số thực (`float`/`double`):** Đây là lỗi logic cực kỳ phổ biến. Đối với số nguyên (như `int`), `min()` trả về số âm sâu nhất. Nhưng đối với kiểu số thực, `min()` lại trả về **số dương nhỏ nhất sát với 0** (ví dụ: `1.17549e-38`). Để lấy được cực hạn âm thực sự (ví dụ: `-3.40282e+38`), bạn bắt buộc phải dùng hàm `lowest()`.
3. **Tại sao `bool` chứa 1 bit dữ liệu nhưng lại tốn 1 byte RAM?** `bool` chỉ có 2 trạng thái `0` (false) hoặc `1` (true), lý thuyết chỉ cần 1 bit. Tuy nhiên, `sizeof(bool)` sẽ trả về 1 byte (8 bits). Nguyên nhân là do CPU và RAM hiện đại không thể truy xuất bộ nhớ ở cấp độ bit. Đơn vị nhỏ nhất có thể đánh địa chỉ (addressable) trên phần cứng là 1 byte. C++ lãng phí 7 bits để đổi lấy tốc độ truy cập CPU tối đa.