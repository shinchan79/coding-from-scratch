Lab sử dụng thư viện `<variant>` và `<chrono>` để giả lập lại cách hoạt động của một ngôn ngữ thông dịch (như Python/JavaScript) ngay bên trong C++, sau đó benchmark tốc độ (đo lường hiệu năng) để thấy rõ sự áp đảo của hệ thống kiểu dữ liệu tĩnh (Static Typing).

```bash
cmake -B build
cmake --build build
./build/app_benchmark

```

Khi chạy bài Lab này, bạn sẽ thấy phiên bản Dynamic mô phỏng chậm hơn phiên bản Static từ **10 đến 50 lần**. Dưới đây là những gì diễn ra ở tầng phần cứng:

* **Static Typing (Không chi phí Runtime):** Ở dòng `staticSum += i;`, trình biên dịch C++ xác nhận kiểu dữ liệu ngay từ lúc bạn gõ code. Nó sẽ dịch dòng này thành đúng **1 lệnh máy duy nhất** (ví dụ: `add eax, ecx` trong Assembly). CPU thực thi lệnh này chớp nhoáng vì nó không cần suy nghĩ gì thêm.
* **Dynamic Typing (Gánh nặng của Thông dịch viên):** Ở vòng lặp thứ hai, mỗi khi gọi phép `+`, hệ thống phải làm 3 việc tốn kém:
1. **Kiểm tra kiểu (Type Tag Checking):** Phải mở "nhãn" của biến ra xem nó đang chứa chữ, số nguyên hay số thực (`std::holds_alternative`).
2. **Rẽ nhánh (Branching):** Dùng lệnh `if/else` hoặc `switch` để quyết định xem sẽ dùng thuật toán cộng số nguyên hay ghép chuỗi văn bản. Nếu CPU đoán sai nhánh (Branch Misprediction), toàn bộ chu trình xử lý sẽ bị khựng lại.
3. **Đóng gói (Boxing/Unboxing):** Tính xong lại phải bọc kết quả vào một đối tượng kiểu động mới.


* **Kẻ thù của Tối ưu hóa (Optimization Blocker):** Trong C++, vì mọi thứ là cố định, compiler có thể gộp nhiều lệnh vào làm một (Loop Unrolling) hoặc dùng lệnh SIMD (cộng nhiều số một lúc). Đối với ngôn ngữ động, compiler bị "mù" vì kiểu dữ liệu có thể thay đổi bất cứ lúc nào, nên nó không dám thực hiện bất kỳ tối ưu hóa mạnh tay nào.