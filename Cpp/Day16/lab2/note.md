* **Interface Class (Che giấu bằng Đa hình):**
* Hàm `processBusinessLogic` chỉ giao tiếp với `ILogger`. Nó không biết và không quan tâm `ConsoleLogger` hoạt động ra sao.
* Việc này giúp tách rời (Decouple) các module. Nếu ngày mai bạn tạo thêm `FileLogger`, hàm `processBusinessLogic` không cần phải sửa đổi hay biên dịch lại dù chỉ 1 dòng (Đây chính là tư tưởng của Open/Closed Principle trong SOLID).


* **Pimpl Idiom (Pointer to Implementation - Che giấu bằng Con trỏ):**
* *Vấn đề:* Trong C++, mỗi khi bạn `#include <thu_vien_x>` vào file `.h`, bất kỳ file `.cpp` nào dùng header đó đều phải tải toàn bộ rác rưởi của `<thu_vien_x>`. Nếu lớp `Timer` lưu trực tiếp biến `<chrono>` vào Private, file `main.cpp` sẽ bị buộc phải nhồi nhét `<chrono>` vào bộ nhớ lúc biên dịch.
* *Giải pháp Pimpl:* Trong `Timer.h`, ta giấu mọi biến Private vào một con trỏ `pimpl`. `main.cpp` nhìn vào chỉ thấy một con trỏ 8 bytes, không hề biết nó trỏ đi đâu. Mọi chi tiết phức tạp, thư viện nặng nề đều bị nhốt vào `Timer.cpp`.
* *Lợi ích khổng lồ:* Giảm kịch liệt sự phụ thuộc mã nguồn (Compilation Dependency). Nếu sau này bạn sửa đổi code bên trong `Timer.cpp` (ví dụ đổi thuật toán đo giờ), hệ thống build (CMake) sẽ **chỉ biên dịch lại duy nhất file `Timer.cpp**`, còn `main.cpp` bỏ qua hoàn toàn. Trong các dự án Game Engine hay HFT lớn (hàng triệu dòng code), kỹ thuật này giúp giảm thời gian build từ 30 phút xuống còn vài giây.
* *Cái giá phải trả (Overhead):* Mỗi lần gọi `t.start()`, chương trình tốn chi phí đi vòng qua một con trỏ (Pointer Indirection) và tốn thêm 1 lần cấp phát Heap khi sinh ra `pimpl`. Đừng dùng Pimpl cho các Object cực nhỏ (như Vector, Ma trận đồ họa) nằm trong vòng lặp tỷ lần.