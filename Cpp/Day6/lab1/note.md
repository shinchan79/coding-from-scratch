* **Function signature (Chữ ký hàm) & Name Mangling:**
* Chữ ký hàm chỉ bao gồm **Tên hàm** và **Danh sách kiểu tham số**. Kiểu trả về (return type) *không* nằm trong chữ ký.
* Ở mức trình biên dịch, nó sẽ dùng kỹ thuật *Name Mangling* để đổi tên hàm nhằm hỗ trợ Overloading. Ví dụ `printData(int)` sẽ bị đổi ngầm thành `_Z9printDatai`, còn `printData(double)` thành `_Z9printDatad`. Nhờ vậy, file nhị phân hoàn toàn phân biệt được chúng là 2 hàm khác nhau.


* **Overload resolution (Phân giải nạp chồng):** Khi bạn gọi một hàm bị nạp chồng, compiler sẽ dò theo thứ tự ưu tiên:
1. Khớp chính xác (Exact Match).
2. Thăng hạng kiểu (Promotion) - ví dụ `float` lên `double`, `char` lên `int`.
3. Chuyển đổi tiêu chuẩn (Standard Conversion) - ví dụ `const char*` sang `std::string`. Nếu compiler tìm thấy 2 ứng viên "ngang kèo" nhau, nó sẽ báo lỗi `ambiguous call` và từ chối build.


* **Default arguments ở mức mã máy:** Hàm có tham số mặc định thực chất **không tồn tại** dưới dạng rút gọn trong bộ nhớ. Ở mức Assembly, chỉ có duy nhất một hàm nhận đủ tất cả tham số. Nhiệm vụ của trình biên dịch là lén lút "chèn" các giá trị mặc định vào lệnh gọi hàm (call site) trước khi đẩy vào thanh ghi/stack cho CPU xử lý.