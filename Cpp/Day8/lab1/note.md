* **Virtual address space (Không gian địa chỉ ảo) & Size:** Hệ điều hành 64-bit quản lý RAM bằng các địa chỉ dài 64 bit (8 bytes). Vì con trỏ chỉ là "một biến chứa địa chỉ", nên mọi con trỏ (dù là `int*`, `double*`, hay `MyStruct*`) **luôn luôn chiếm đúng 8 bytes**.
* **Sự giải mã (Decoding) khác nhau:** Nếu size bằng nhau, tại sao phải chia ra `int*` và `double*`? Kiểu dữ liệu của con trỏ là lệnh chỉ đạo cho CPU: *"Từ địa chỉ 8 byte này, hãy đọc tiếp X bytes, và giải mã các bit 0/1 đó theo chuẩn số nguyên hay chuẩn số thực IEEE 754"*. Nếu ép kiểu sai (như `reinterpret_cast`), bạn sẽ đọc ra một đống rác vì CPU giải mã sai quy tắc.
* **Quy tắc đọc Const Pointers (Đọc từ phải sang trái):**
* `const int*` (hoặc `int const*`): Data là const. Con trỏ trỏ đi chỗ khác được, nhưng không được phép sửa giá trị của nơi nó đang trỏ.
* `int* const`: Pointer là const. Được sửa data, nhưng con trỏ bị khóa cứng vào 1 địa chỉ duy nhất.


* **Constant Folding (Gấp hằng số):** Khi bạn dùng từ khóa `const` cho các biến cục bộ, bạn cung cấp một lời hứa với trình biên dịch rằng *"giá trị này không bao giờ thay đổi"*. Trình biên dịch (nhờ cờ `-O2`) sẽ bỏ luôn việc lưu biến đó vào RAM. Nó **nhúng thẳng (hardcode)** con số đó vào mã máy (Assembly). Chương trình chạy nhanh hơn do bớt được 1 lệnh đọc bộ nhớ (Memory Read).