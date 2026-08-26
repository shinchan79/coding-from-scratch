```bash
cmake -B build
cmake --build build
./build/app_alignment

```
Khi quan sát kết quả in ra từ biến `Offset of 'number'`, bạn sẽ thấy nó nằm ở vị trí byte thứ **4** thay vì byte thứ **1**. Đây là lời giải thích từ góc độ kiến trúc máy tính:

* **Chu kỳ đọc của CPU:** CPU không đọc RAM theo từng byte lẻ tẻ. Nó luôn đọc theo các khối bộ nhớ cố định (Data Bus), thường là 4 bytes (32-bit) hoặc 8 bytes (64-bit) mỗi lần.
* **Quy tắc Alignment:** CPU bắt buộc một biến kiểu `int` (4 bytes) phải bắt đầu tại một địa chỉ bộ nhớ chia hết cho 4. Nếu biến `int` bắt đầu ở byte số 1 (ngay sau `char`), nó sẽ nằm vắt ngang giữa hai khối đọc của CPU. Điều này ép CPU phải thực hiện 2 chu kỳ đọc RAM rồi mới ghép dữ liệu lại được, làm giảm hiệu năng hệ thống đi một nửa.
* **Giải pháp của C++:** Trình biên dịch sẽ tự động chèn thêm 3 bytes "rỗng" (padding) ngay sau biến `char` để đẩy biến `int` về đúng địa chỉ chia hết cho 4. Do đó, kích thước tổng của `1 char + 1 int` bị phình lên thành 8 bytes.
* **Chiến lược tối ưu Struct:** Như bạn thấy ở phần `GoodLayout`, nguyên tắc vàng để tiết kiệm RAM là luôn khai báo các biến thành viên theo thứ tự **kích thước từ lớn nhất đến nhỏ nhất** (ví dụ: `double` $\rightarrow$ `int` $\rightarrow$ `short` $\rightarrow$ `char`). Các biến nhỏ sẽ tự động lấp đầy những khoảng đệm thừa của nhau, giúp `GoodLayout` chỉ tốn 8 bytes thay vì 12 bytes như `BadLayout`.