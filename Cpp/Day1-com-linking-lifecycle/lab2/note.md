```#pragma once```:
`#pragma once` là một chỉ thị tiền xử lý (preprocessor directive) được đặt ở đầu các file Header (`.h`), có tác dụng **ngăn chặn file header đó bị copy/include nhiều lần** vào cùng một file mã nguồn (Translation Unit) trong quá trình biên dịch.

**1. Vấn đề nó giải quyết (Tại sao lại cần?)**
Ở bước Tiền xử lý (Preprocessing - cờ `-E`), lệnh `#include` hoạt động bằng cách copy-paste y nguyên nội dung file header vào file `.cpp`.

Giả sử dự án của bạn lớn lên:

* File `A.h` có `#include "math_lib.h"`
* File `main.cpp` lại có `#include "A.h"` và `#include "math_lib.h"`

Lúc này, nội dung của `math_lib.h` sẽ bị copy 2 lần vào `main.cpp`. Nếu trong `math_lib.h` có định nghĩa một struct hoặc class, trình biên dịch sẽ báo lỗi **Redefinition** (Định nghĩa lại nhiều lần) và dừng ngay lập tức. `#pragma once` sinh ra để trình biên dịch tự động bỏ qua file này ở lần copy thứ hai.

**2. So sánh với cách truyền thống (Include Guards)**
Trước khi có `#pragma once`, các lập trình viên C/C++ phải dùng kỹ thuật "Include Guards" rất cồng kềnh bằng các macro:

```cpp
// Cách cũ (Include Guards)
#ifndef MATH_LIB_H
#define MATH_LIB_H

int add(int a, int b);

#endif

```

Nhược điểm của cách cũ là bạn phải tự đặt tên macro (`MATH_LIB_H`). Nếu bạn copy code sang file khác mà quên đổi tên macro, hai file sẽ bị trùng tên và trình biên dịch sẽ lờ đi một file, gây ra những lỗi cực kỳ khó tìm.

**3. Tại sao `#pragma once` lại được ưa chuộng trong Modern C++?**

* **Ngắn gọn:** Chỉ cần đúng 1 dòng ở dòng đầu tiên của file.
* **An toàn:** Trình biên dịch tự quản lý file dựa trên đường dẫn hệ điều hành, không lo chuyện đặt trùng tên macro.
* **Tăng tốc độ build:** Trình biên dịch hiện đại biết file này đã được xử lý nên thậm chí không thèm mở file đó ra đọc lại ở lần include thứ hai.
* *(Thực tiễn)*: Mặc dù `#pragma once` không được ghi chính thức trong sách giáo khoa chuẩn ISO C++, nhưng **100% các trình biên dịch hiện đại** (GCC, Clang của Mac, MSVC của Windows) đều hỗ trợ nó hoàn hảo và nó đã trở thành tiêu chuẩn công nghiệp thực tế.