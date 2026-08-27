* **Thứ tự khởi tạo (Initialization Order):**
1. Khi một đối tượng kế thừa được tạo, lớp cha (**Base**) luôn được khởi tạo trước lớp con (**Derived**).
2. Trong phạm vi của một lớp, các thành viên dữ liệu (Member variables) được khởi tạo **đúng theo thứ tự chúng xuất hiện trong khai báo class**, hoàn toàn không phụ thuộc vào thứ tự bạn viết chúng trong Member Initializer List.


* **Thứ tự hủy (Destruction Order - Đảo ngược hoàn toàn):**
1. Quá trình hủy diễn ra ngược lại với khởi tạo: **Lớp con bị hủy trước, lớp cha bị hủy sau**.
2. Các thành viên dữ liệu bên trong lớp cũng bị hủy theo thứ tự ngược lại với lúc chúng được khai báo (vào trước ra sau theo nguyên tắc ngăn xếp).


* **Virtual Destructor (Hủy ảo - Sống còn cho Đa hình):** Khi bạn dùng con trỏ lớp cha trỏ tới đối tượng lớp con trên Heap (`Base* ptr = new Derived()`) và gọi lệnh `delete ptr`, nếu destructor của `Base` **không** có từ khóa `virtual`, chương trình chỉ gọi destructor của `Base` và bỏ qua hoàn toàn destructor của `Derived`. Hậu quả là `DerivedResource` sẽ bị rò rỉ vĩnh viễn (Memory/Resource Leak). Luôn luôn khai báo `virtual ~Base() = default;` cho mọi Base Class có tính đa hình.
* **Resource Cleanup (Dọn dẹp tài nguyên qua RAII):** Destructor chính là nơi duy nhất bảo đảm tài nguyên (file handle, network socket, memory block) được trả lại an toàn. Bất kể hàm thoát ra bằng lệnh `return` bình thường hay do `throw` ngoại lệ (Stack Unwinding), destructor của các biến cục bộ vẫn luôn được gọi chính xác 100%.