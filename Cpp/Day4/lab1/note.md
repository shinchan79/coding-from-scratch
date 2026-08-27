**1. Bitwise Optimization (Tối ưu hóa bằng bit)**

* **Bản chất:** Máy tính hoạt động bằng nhị phân. Các phép toán bit tác động trực tiếp lên chuỗi nhị phân này thông qua mạch logic cơ bản của CPU nên tốn cực ít chu kỳ máy (clock cycles) so với các phép tính toán học thông thường.
* **Trong code:**
* `<< 1` (Dịch trái): Tương đương nhân 2. Nhanh hơn phép `* 2`.
* `>> 1` (Dịch phải): Tương đương chia 2 (lấy nguyên). Nhanh hơn phép `/ 2`.
* `& 1` (AND với 1): Kiểm tra số lẻ. Nhanh hơn rất nhiều so với phép chia lấy dư `% 2` (phép chia là một trong những lệnh tốn kém nhất của CPU).
* **XOR Swap:** Thuật toán đổi giá trị hai biến số nguyên cho nhau mà không cần cấp phát thêm vùng nhớ cho biến tạm (temp).



**2. Short-circuit Evaluation (Đánh giá đoản mạch)**

* **Bản chất:** Nếu kết quả của một biểu thức logic đã được định đoạt ở vế đầu, CPU sẽ ngắt ngay và **bỏ qua hoàn toàn** việc thực thi vế sau. Điều này giúp tiết kiệm thời gian xử lý và tránh các lỗi sập chương trình.
* **Trong code:**
* `false && sideEffect()`: Phép AND cần cả 2 vế là `true`. Vì vế đầu đã `false`, kết quả chắc chắn là `false`. Hàm `sideEffect()` bị bỏ qua hoàn toàn.
* `true || sideEffect()`: Phép OR chỉ cần 1 vế `true`. Vì vế đầu đã `true`, kết quả chắc chắn là `true`. Hàm `sideEffect()` bị bỏ qua.
* *Ứng dụng thực chiến:* Rất phổ biến khi kiểm tra con trỏ: `if (ptr != nullptr && ptr->value == 1)`. Nhờ đoản mạch, nếu `ptr` bị null, vế sau sẽ không chạy, giúp chương trình không bị crash.



**3. Type Promotion (Thăng hạng kiểu dữ liệu)**

* **Bản chất:** Kiến trúc CPU hiện đại (như x86/ARM) được thiết kế để tính toán số học tối ưu nhất trên các thanh ghi chuẩn (thường là 32-bit hoặc 64-bit). C++ tuân theo quy tắc phần cứng này: nó ngầm định nâng cấp các kiểu dữ liệu nhỏ lên kiểu lớn hơn trước khi đưa vào tính toán.
* **Trong code:** Mặc dù `c1` và `c2` là kiểu `char` (chỉ chiếm 1 byte), khi thực hiện phép cộng `+`, C++ tự động thăng hạng cả hai lên kiểu `int` (thường là 4 byte). Kết quả trả về mang kiểu `int`. Việc này vừa đảm bảo hiệu suất khớp với thanh ghi CPU, vừa ngăn chặn lỗi tràn số (overflow) nếu kết quả vượt quá sức chứa của 1 byte.