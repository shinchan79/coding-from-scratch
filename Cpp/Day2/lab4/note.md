cmake -B build
cmake --build build
./build/app_init

Sau đó mở comment: 
```
int safeInt{pi}; 
    char safeChar{largeNumber};
```

```bash
cmake --build build

```

Trong Modern C++, nguyên tắc vàng là: **Luôn sử dụng `{}` để khởi tạo biến**. Nó giúp bạn bắt mọi lỗi tràn số và sai lệch kiểu dữ liệu ngay từ lúc gõ code (Compile-time). Nếu bạn thực sự muốn cắt cụt số `3.14` thành `3`, C++ ép bạn phải sử dụng công cụ tường minh (`static_cast<int>(pi)`) để báo cho người đọc code sau này biết rằng sự mất mát dữ liệu này là do bạn chủ đích làm, chứ không phải do code ẩu.