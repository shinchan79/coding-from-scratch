 * **Tại sao `vector` vượt trội `list`? (Sự thật về Cache Line):**
* Cả hai cấu trúc đều mang độ phức tạp $O(n)$ khi duyệt. Nhưng ở mức vật lý, RAM không trả về từng số nguyên một. Khi gọi `vec[0]`, CPU sẽ kéo luôn **64 bytes** (16 số nguyên liên tiếp) vào L1 Cache. Do `vector` là một khối nhớ liền mạch 100%, 15 số tiếp theo đã nằm sẵn trong CPU (Cache Hit), tốc độ xử lý nhanh như chớp.
* Ngược lại, mỗi node của `list` được cấp phát lẻ tẻ bằng `new`, rải rác khắp nơi trên Heap. CPU kéo 64 bytes về thì 60 bytes là rác. Lần lặp tiếp theo, nó lại phải chờ RAM (Cache Miss). Hệ quả: `vector` thường nhanh hơn `list` từ 10 đến 50 lần trong thực tế.


* **SlowCopy vs FastCopy (Pointer Arithmetic):**
* Bài toán copy mảng phản ánh sức mạnh của toán tử con trỏ. Cùng là một khối dữ liệu 40MB, nếu ép con trỏ làm việc ở cấp độ 1-byte (`char*`), CPU phải thực hiện 40 triệu lệnh gán.
* Khi ép kiểu sang `uint64_t*`, nhờ kiến trúc 64-bit, phép toán con trỏ `*pDst++` sẽ "cắn" một lúc 8 bytes. Số vòng lặp và số lệnh CPU giảm đi 8 lần, tốc độ tăng vọt.
* **Trùm cuối `std::memcpy`:** Đây là hàm được viết bằng mã Assembly tối ưu riêng cho từng loại chip. Nó sử dụng tập lệnh SIMD (AVX/SSE) để copy 16, 32, hoặc thậm chí 64 bytes trong đúng 1 chu kỳ máy. Lời khuyên: luôn dùng `std::memcpy` hoặc `std::copy` khi cần di chuyển bộ nhớ thay vì tự viết vòng lặp `for`.