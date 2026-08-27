* **Vấn đề (Tại sao cần SSO?):** Như bạn đã học ở bài Heap vs Stack, việc gọi HĐH cấp phát bộ nhớ động (`new`/`malloc`) tiêu tốn hàng trăm chu kỳ CPU. Trong thực tế, hầu hết các chuỗi được sử dụng trong lập trình đều rất ngắn (ví dụ: "Error", "Admin", "John"). Nếu mỗi chuỗi ngắn này đều phải xin RAM trên Heap, hiệu năng tổng thể của chương trình sẽ sụt giảm nghiêm trọng.
* **Cơ chế Small String Optimization:**
* Bản thân một biến `std::string` chứa các con trỏ và biến đếm trạng thái, chiếm khoảng 24 đến 32 bytes (tùy trình biên dịch).
* Các kỹ sư thiết kế C++ đã dùng một thủ thuật: Nếu chuỗi bạn nhập vào đủ ngắn, trình biên dịch sẽ **tái sử dụng chính 32 bytes rỗng này** để nhét trực tiếp các ký tự vào bên trong nó.
* Kết quả: Chuỗi ngắn của bạn hoàn toàn nằm trên **Stack**, thời gian khởi tạo là 0 ms (Zero OS overhead).


* **Vượt ngưỡng (SSO Threshold):**
* Khi bạn chạy Lab trên, bạn sẽ thấy địa chỉ của `str.data()` (nơi chứa chữ) lúc đầu trùng khớp hoặc nằm ngay sát địa chỉ gốc của `&str` (Stack).
* Đối với trình biên dịch GCC/Clang (Linux/macOS), ngưỡng này thường là **15 ký tự**. Đối với MSVC (Windows), nó thường là 15 hoặc 22 ký tự.
* Ngay khi bạn chèn ký tự thứ 16, mảng Stack bên trong không còn đủ chỗ. Lúc này `std::string` mới thực hiện một cuộc gọi `new` thực sự, cấp phát bộ nhớ trên **Heap** (bạn sẽ thấy địa chỉ RAM bị nhảy sang một vùng số hoàn toàn khác), copy 15 ký tự cũ sang, và tắt chế độ SSO.