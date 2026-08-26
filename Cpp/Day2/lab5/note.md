**Bước 1: Chạy code nguyên bản**

```bash
cmake -B build
cmake --build build
./build/app_cast

```

**Bước 2:**
Mở file `main.cpp`, bỏ comment:

```cpp
    int* safePtr = static_cast<int*>(constPtr); 
```

```bash
cmake --build build

```
### Tại sao C-style cast lại nguy hiểm?

Cú pháp ép kiểu kiểu C `(type)value` là một công cụ  hoạt động mù quáng. Khi bạn dùng `(int*)ptr`, trình biên dịch sẽ thử làm theo thứ tự sau cho đến khi thành công:

1. `const_cast` (Bỏ qua hằng số).
2. `static_cast` (Ép kiểu thông thường).
3. `reinterpret_cast` (Ép kiểu con trỏ thô bạo ở mức độ byte).

Nó nguy hiểm vì 2 lý do:

* **Không rõ ràng mục đích:** Người đọc code không biết bạn đang muốn làm tròn số, hay đang muốn gỡ bỏ `const`, hay đang muốn ép kiểu một con trỏ rác. `static_cast` ép bạn phải nói rõ ý định và từ chối nếu bạn vi phạm quy tắc cơ bản (như gỡ `const`).
* **Không thể tìm kiếm (Grep-ability):** Trong một dự án 1 triệu dòng code, bạn không thể tìm kiếm bằng phím tắt `Ctrl+F` tất cả các chỗ dùng C-style cast (vì cú pháp `(type)` quá chung chung). Ngược lại, bạn có thể dễ dàng tìm ra toàn bộ các chỗ ép kiểu rủi ro bằng cách search từ khóa `static_cast` hoặc `reinterpret_cast`.