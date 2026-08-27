cmake -S . -B build
cmake --build build
./build/day3_lab

Hướng dẫn thực hành để hiểu sâu:
Chạy thử lần 1: Chạy đoạn code nguyên bản trên, bạn sẽ thấy ở Nhiệm vụ 3, địa chỉ của biến in ra trong main và trong hàm bad_swap là hoàn toàn khác nhau. Dữ liệu gốc 100 và 200 không hề bị hoán đổi.

Chạy thử lần 2 (Sinh lỗi có chủ đích): Xóa dấu // ở dòng std::cout << &10; (Nhiệm vụ 1) hoặc my_swap(m, 20); (Nhiệm vụ 2) và bấm Build/Run. Đọc dòng báo lỗi màu đỏ của trình biên dịch (Compiler). Việc tự đọc và hiểu thông báo lỗi “lvalue required...” hay “cannot bind non-const lvalue reference...” chính là cốt lõi để làm chủ tư duy bộ nhớ trong C++.

**Bản chất của L-value và R-value:**

* **L-value (Locator Value):** Là dữ liệu có "hộ khẩu" – tức là chiếm một vùng nhớ cố định trong RAM và sống qua nhiều dòng code. Bạn có thể dùng toán tử `&` để lấy địa chỉ của nó và gán giá trị mới cho nó (ví dụ: biến `a`, `m`, `n`).
* **R-value (Read Value):** Là dữ liệu "tạm trú" – thường sinh ra trên thanh ghi CPU để tính toán nhanh, hoặc là một object tạm thời sẽ bị hủy ngay khi dấu chấm phẩy `;` kết thúc dòng lệnh (ví dụ: con số `10`, kết quả của `a + 5`). Vì nó thoắt ẩn thoắt hiện, C++ cấm bạn lấy địa chỉ `&` của nó.

**Bản chất của cơ chế Swap và Truyền dữ liệu:**

* **Truyền tham trị (`bad_swap`):** Trình biên dịch ngầm tạo ra một bản photocopy của dữ liệu gốc. Hàm chỉ hoán đổi trên bản photo rồi ném vào thùng rác khi chạy xong. Nếu bạn truyền một mảng 1GB, C++ cũng sẽ nai lưng ra copy 1GB đó, gây thảm họa hiệu năng.
* **Truyền tham chiếu (`good_swap` với `&`):** Hàm nhận được đường dẫn trực tiếp đến vùng nhớ thật. Không có bản copy nào được sinh ra. Bạn sửa gì trong hàm, dữ liệu gốc ngoài `main` thay đổi y hệt. Chi phí truyền dữ liệu lúc này gần như bằng 0.
* **Lý do `good_swap(m, 20)` bị cấm:** Tham chiếu `&` (non-const) là một lời cam kết: "Tôi sẽ trực tiếp thay đổi vùng nhớ mà anh truyền vào". Nhưng số `20` là R-value, không hề có vùng nhớ cố định. Bạn không thể thay đổi một bóng ma, nên trình biên dịch sẽ chặn đứng bạn ngay lập tức.

Tư duy cốt lõi đằng sau bài lab này là **tối ưu hóa (Optimization mindset)**: Ngôn ngữ C++ ép bạn phải phân biệt rõ đâu là đồ dùng lâu dài (L-value) và đâu là rác dùng một lần (R-value). Nhờ sự rạch ròi này, ở những bài sau (về Move Semantics), C++ sẽ cho phép bạn "ăn cắp" luôn vùng nhớ của R-value thay vì phải tốn công copy, giúp các chương trình C++ đạt tốc độ tối đa.