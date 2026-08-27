* **Bản chất của Reallocation (Tái cấp phát):** Khi bạn dùng `push_back` (hoặc `emplace_back`) trên một `std::vector` không dùng `reserve()`, cứ mỗi lần mảng đầy (`size == capacity`), nó sẽ tự động nhân đôi không gian để dự phòng. Tuy nhiên, đằng sau hậu trường, hành động "nhân đôi" này bao gồm 3 bước tốn kém:
1. Xin Hệ điều hành một mảng RAM mới to gấp đôi.
2. Copy toàn bộ dữ liệu từ mảng cũ sang mảng mới.
3. Xóa mảng cũ.


* **Tại sao không có `reserve()` lại chậm?** Với 20 triệu phần tử, vòng lặp thứ nhất phải thực hiện tái cấp phát khoảng 25-26 lần. Những lần cuối cùng, nó phải chật vật copy hàng chục triệu object (vài trăm MB dữ liệu) từ vùng nhớ này sang vùng nhớ khác một cách hoàn toàn vô ích, khiến CPU và RAM bị nghẽn.
* **Sức mạnh của `reserve(SIZE)`:** Nó cung cấp cho vector một "lời tiên tri". Bạn ra lệnh xin đúng 1 cục RAM đủ chứa 20 triệu phần tử ngay từ đầu vòng lặp. Xuyên suốt quá trình chèn dữ liệu sau đó, **Reallocation không bao giờ xảy ra (0 times)**. CPU chỉ làm đúng một việc là gán giá trị thẳng vào RAM, biến độ phức tạp của việc thêm phần tử từ *Amortized $O(1)$* (thỉnh thoảng bị chậm đột xuất do copy) thành *True $O(1)$* (nhanh và cực kỳ ổn định).