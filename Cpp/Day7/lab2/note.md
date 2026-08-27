* **Từ khóa `inline` và Quyền lực của Compiler:**
* Bạn đặt `inline` chỉ là một lời "gợi ý". Trình biên dịch hiện đại mới là người nắm quyền quyết định cuối cùng.
* Nếu hàm quá dài hoặc chứa vòng lặp phức tạp, compiler sẽ phớt lờ `inline` vì nếu nhúng code đó vào 1000 chỗ, file nhị phân sẽ phình to (Code Bloat), gây tràn I-Cache (Instruction Cache) và làm chương trình chậm đi. Ngược lại, dù bạn không viết `inline`, ở mức tối ưu `-O2`, compiler vẫn tự động inline các hàm ngắn gọn.


* **Recursion (Đệ quy) vs Iteration (Vòng lặp):**
* Đệ quy viết code rất thanh lịch, dễ đọc (nhất là với Cây/Đồ thị), nhưng cái giá phải trả là mỗi lần gọi lại tốn thêm một Stack Frame (giống bài Lab trước). Rất dễ bị `Stack Overflow` và tốn chi phí gọi hàm (Call overhead).
* Vòng lặp chạy bằng biến cục bộ, không tốn thêm Stack, tốc độ luôn là nhanh nhất nhưng code thường dài và khó bảo trì hơn.


* **Tail Call Optimization (TCO - Tối ưu hóa đệ quy đuôi):**
* Là "tuyệt chiêu" kết hợp vẻ đẹp của đệ quy và tốc độ của vòng lặp.
* **Điều kiện bắt buộc:** Lời gọi đệ quy phải là **hành động cuối cùng** của hàm. Không được cộng, trừ, hay làm bất cứ phép tính nào sau khi hàm đệ quy trả về (giống như `fibRecursive` làm phép `+` ở cuối là vi phạm).
* Khi thấy cấu trúc này, compiler (`-O2`) biết rằng Stack Frame của hàm hiện tại không còn giá trị gì nữa (vì chả còn lệnh nào để làm). Thay vì tạo Frame mới, nó sẽ lén lút biến hàm đệ quy đó thành một **vòng lặp nhảy (goto/jump)** ngay trên Assembly, dùng chung luôn 1 Stack Frame. Bạn không bao giờ bị Stack Overflow nữa.