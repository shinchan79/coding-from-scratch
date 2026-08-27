* **Member Initializer List (Danh sách khởi tạo thành viên) & Tối ưu hiệu năng:**
* *Sai lầm phổ biến:* Khai báo biến trong thân constructor rồi mới gán giá trị (ví dụ: `res = Resource("abc")`). Làm như vậy, trình biên dịch sẽ gọi **Default Constructor** của object trước, rồi sau đó mới gọi **Copy Assignment Operator** để ghi đè. Tốn gấp đôi số bước thực thi!
* *Giải pháp tối ưu:* Dùng Member Initializer List (dấu `:` trước thân constructor). Các thành phần được khởi tạo trực tiếp bằng tham số truyền vào ngay từ nhịp đầu tiên, loại bỏ hoàn toàn các lời gọi khởi tạo mặc định thừa thãi.


* **Delegating Constructors (Constructor ủy quyền):** Cho phép một constructor gọi trực tiếp một constructor khác trong cùng một lớp. Giúp tái sử dụng code khởi tạo, tránh lặp lại logic.
* **Explicit Constructors:** Theo mặc định, nếu constructor chỉ nhận 1 tham số, C++ cho phép chuyển đổi ngầm định (implicit conversion) từ kiểu dữ liệu đó sang đối tượng của lớp (ví dụ truyền số nguyên vào hàm nhận `Player`). Điều này gây ra những bug logic cực kỳ khó dò. Từ khóa `explicit` ra lệnh cho trình biên dịch: *"Cấm tự ý chuyển đổi ngầm định, bắt buộc phải khởi tạo tường minh"*.