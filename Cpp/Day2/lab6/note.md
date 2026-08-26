```bash
cmake -B build
cmake --build build

```

**Bước 4.1: Khởi động LLDB và đặt Breakpoint**

```bash
# Bật LLDB
lldb ./build/app_debug

```

*Lúc này dấu nhắc lệnh của Terminal sẽ chuyển thành `(lldb)`.*

```bash
# Đặt điểm dừng (breakpoint) tại dòng 16 của file main.cpp (dòng cout cuối cùng)
(lldb) b main.cpp:16

# Chạy chương trình
(lldb) run

```

*Chương trình sẽ chạy và khựng lại đúng tại dòng số 16. Bây giờ toàn bộ 3 biến đã được cấp phát trên RAM.*

**Bước 4.2: In giá trị bình thường vs Hexadecimal**
Cú pháp in của LLDB là `p` (print). Thêm `/x` để in dạng Hex.

* **Soi biến `negativeNumber`:**
```bash
(lldb) p negativeNumber
# Kết quả: (int) $0 = -1

(lldb) p/x negativeNumber
# Kết quả: (int) $1 = 0xffffffff

```

*Giải mã:* Máy tính không biết dấu trừ (`-`) là gì. Nó dùng chuẩn Bù 2 (Two's Complement). Số `-1` thực chất là toàn bộ 32 bits đều bật sáng thành số `1` (F trong hệ Hex = 1111).
* **Soi biến `colorMask`:**
```bash
(lldb) p colorMask
# Kết quả: (unsigned int) $2 = 4278190080

(lldb) p/x colorMask
# Kết quả: (unsigned int) $3 = 0xff000000

```

*Giải mã:* Con số `4278190080` trông rất vô nghĩa, nhưng khi nhìn dưới dạng Hex `0xff000000`, lập trình viên đồ họa sẽ hiểu ngay đây là kênh màu đỏ (Red) bật tối đa (FF = 255), các kênh khác (Green, Blue) đang tắt (00).
* **Soi biến `piFloat`:**
```bash
(lldb) p piFloat
# Kết quả: (float) $4 = 3.14158988

(lldb) p/x piFloat
# Kết quả: (float) $5 = 0x40490fd0

```

*Giải mã:* Số thực được mã hóa bằng chuẩn IEEE 754 cực kỳ phức tạp (chia thành bit dấu, phần mũ, và phần phân số). Đuôi `fd0` giải thích tại sao số `3.14159` gốc của bạn bị sai số nhẹ thành `3.14158988`.

**Bước 4.3: Đọc trực tiếp byte RAM thô (Bonus cực mạnh)**
Bạn có thể ra lệnh cho LLDB in từng byte vật lý trên RAM bằng lệnh `x` (examine memory).

```bash
(lldb) x/4xb &colorMask

```
*Giải mã:* Lệnh này báo LLDB đọc 4 bytes (4b) dưới định dạng Hex (x) tại địa chỉ con trỏ của biến colorMask. Kết quả trả về sẽ giúp bạn nhìn thấu cơ chế Little-Endian của chip Apple Silicon.

**Bước 4.4: Thoát Debugger**

```bash
(lldb) quit

```