Dòng lệnh `#define MAGIC_NUMBER 42` là một **chỉ thị tiền xử lý (preprocessor directive)** dùng để định nghĩa một Macro.

Về bản chất, nó hoạt động y hệt tính năng **Tìm và Thay thế (Find and Replace - Ctrl+H)** trong các trình soạn thảo văn bản thông thường.

* **Cách hoạt động (Liên hệ với bước cờ `-E` bạn vừa làm):** Ở bước Tiền xử lý, phần mềm sẽ quét toàn bộ file `.cpp`. Cứ chỗ nào xuất hiện cụm từ `MAGIC_NUMBER`, nó sẽ tự động xóa đi và dán cứng số `42` vào thế chỗ, rồi mới đưa kết quả đó đi biên dịch. Hàm `main` của bạn lúc này sẽ hiểu là in ra số 42.
* **Mục đích:** Giúp mã nguồn dễ đọc và dễ bảo trì. Giả sử bạn có 100 chỗ trong code sử dụng con số 42. Thay vì gõ "chết" số 42 ở 100 nơi (những con số vô hồn này trong lập trình gọi là *Magic Numbers*), bạn gán cho nó một cái tên. Nếu sau này hệ thống thay đổi và cần dùng số 100, bạn chỉ việc sửa đúng 1 dòng `#define` trên cùng, cả 100 chỗ kia sẽ tự động được cập nhật theo.

**Lưu ý với Modern C++:**
Tuy `#define` là "đặc sản" của C, nhưng trong C++ hiện đại, người ta khuyến cáo **không nên** dùng nó để định nghĩa hằng số nữa. Lý do là `#define` chỉ là trò "thay thế văn bản" mù quáng, nó không tuân theo quy tắc kiểm tra kiểu dữ liệu (type safety) hay phạm vi hoạt động (scope) của C++, rất dễ gây lỗi diện rộng trong các dự án lớn.

Thay vào đó, bạn nên dùng `constexpr` (ưu tiên) hoặc `const` như sau:

```cpp
constexpr int MAGIC_NUMBER = 42;

```

Cách này vừa đạt được mục đích quản lý số tập trung, vừa được trình biên dịch bảo vệ chặt chẽ về mặt kiểu dữ liệu.