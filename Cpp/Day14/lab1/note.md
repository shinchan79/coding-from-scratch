* **Size vs Capacity:**
* `size()` là số lượng phần tử *thực sự* đang chứa trong vector.
* `capacity()` là sức chứa của vùng nhớ mà vector đã xin Hệ điều hành. Vector luôn xin dư bộ nhớ để dự phòng (Capacity $\ge$ Size).


* **Reallocation & Amortized Complexity (Tại sao nhân đôi?):**
* Khi `size == capacity`, vector không còn chỗ. Nó phải thực hiện **Reallocation**: (1) Xin một mảng RAM mới to hơn, (2) Copy toàn bộ dữ liệu cũ sang, (3) Xóa mảng cũ. Bước (2) tốn thời gian $O(N)$.
* *Nếu mỗi lần đầy chỉ cộng thêm 1 ô:* Cứ thêm 1 phần tử lại phải copy toàn bộ mảng cũ. Tổng thời gian để chèn $N$ phần tử sẽ lên tới $O(N^2)$ (cực kỳ chậm).
* *Chiến thuật nhân đôi (Growth Factor = 2):* Bằng cách nhân đôi capacity (0 $\rightarrow$ 1 $\rightarrow$ 2 $\rightarrow$ 4 $\rightarrow$ 8 $\rightarrow$ 16 $\rightarrow$ 32), tần suất phải copy giảm theo cấp số nhân. Toán học chứng minh rằng tổng chi phí copy chia đều cho $N$ phần tử sẽ tiệm cận về một hằng số. Do đó, chi phí chèn trung bình (Amortized complexity) được tính là **$O(1)$**, ngang bằng mảng tĩnh. (Lưu ý: Trình biên dịch GCC/Clang nhân 2, MSVC trên Windows nhân 1.5 để tiết kiệm RAM hơn).


* **Data Locality (`vector` vô đối so với `list`):**
* Dù cả 2 đều có độ phức tạp duyệt qua mảng là $O(N)$, nhưng phần cứng máy tính không chạy theo lý thuyết Big O. CPU đọc RAM theo từng khối **Cache Line (64 bytes)**.
* Vì `vector` cấp phát liên tục 100%, đọc 1 số nguyên (4 bytes), CPU bốc luôn 15 số tiếp theo vào L1 Cache. 15 bước lặp tiếp theo CPU không cần chờ RAM (**Cache Hit**).
* Mỗi node của `list` được cấp phát lẻ tẻ rải rác trên Heap bằng lệnh `new`. CPU bốc 64 bytes về thì phần lớn là rác, vòng lặp sau lại phải đợi RAM (**Cache Miss**). Thực tế, `vector` luôn nghiền nát `list` về tốc độ với chênh lệch hàng chục lần.