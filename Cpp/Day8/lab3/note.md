* **Tại sao chậm hơn? (Pointer Chasing Overhead):** Để tính `***p3`, CPU không thể lấy số `42` ngay lập tức. Nó phải thực hiện 4 bước tuần tự:
1. Đọc địa chỉ lưu trong `p3` để tìm `p2`.
2. Đọc địa chỉ lưu trong `p2` để tìm `p1`.
3. Đọc địa chỉ lưu trong `p1` để tìm `data`.
4. Cuối cùng mới lấy được giá trị `42` để cộng vào `sumPointer`.
   Mỗi bước "dịch ngược" (dereference) sinh ra một lệnh load bộ nhớ (memory load instruction). Việc này ngăn cản CPU chạy song song các lệnh (Instruction-Level Parallelism) vì lệnh sau phải đợi kết quả địa chỉ của lệnh trước.


* **Tác dụng của `volatile`:** Nếu không có `volatile`, trình biên dịch `-O2` thừa thông minh để nhận ra `***p3` thực chất luôn trỏ về `data` và giá trị `data` không hề đổi. Nó sẽ tối ưu bằng cách ném số `42` thẳng vào một thanh ghi (register) tốc độ siêu cao, biến bài test thành con số 0 ms cho cả hai vòng lặp. Cờ `volatile` trói tay trình biên dịch, ép CPU phải ngoan ngoãn đi đường vòng qua RAM/L1 Cache ở mỗi chu kỳ lặp để bạn đo được sự thật vật lý.