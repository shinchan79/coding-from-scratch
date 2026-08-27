* **Bộ ba Fibonacci & godbolt.org:**
* *Normal Recursion* cực kỳ chậm (độ phức tạp $O(2^n)$).
* *Iterative* và *Tail Recursive* đều chạy chớp nhoáng ($O(n)$). Nếu bạn copy 2 hàm này thả vào [godbolt.org](https://godbolt.org/) (bật cờ `-O2`), bạn sẽ thấy mã Assembly sinh ra của chúng **gần như y hệt nhau**. Trình biên dịch đã lén biến lời gọi đệ quy đuôi thành một vòng lặp `jmp` (Jump) để không tốn thêm Stack Frame nào.


* **Chiến lược đo đạc `<chrono>`:** Từ nay về sau, hiệu năng không nói bằng cảm tính. Mọi lý thuyết tối ưu hóa phải được chứng minh bằng con số mili-giây qua bộ đếm thời gian thực `high_resolution_clock`. Cờ `-O2` trong CMake là bắt buộc để `<chrono>` phản ánh đúng tốc độ của CPU, không bị nhiễu bởi các lệnh debug.
* **Cache Locality (Row-major vs Column-major):**
* RAM máy tính là một mảng 1 chiều khổng lồ.
* Khi CPU cần đọc `matrix[0]`, nó không bốc 1 số nguyên (4 bytes), mà bốc luôn một **Cache Line** (thường là 64 bytes, tương đương 16 số nguyên liên tiếp) nhét vào L1 Cache.
* **Row-major** (duyệt theo hàng): Đọc `matrix[0]`, 15 số tiếp theo đã nằm sẵn trong Cache (Cache Hit). CPU chạy với tốc độ bàn thờ.
* **Column-major** (duyệt theo cột): Đọc `matrix[0]`, bước tiếp theo nhảy tới `matrix[10000]`. Dữ liệu này chưa có trong Cache (Cache Miss). CPU phải chờ RAM đi lấy dữ liệu mới, gây thắt cổ chai toàn hệ thống dù thuật toán y hệt nhau. Tốc độ thực tế có thể chênh nhau từ 5 đến 20 lần.