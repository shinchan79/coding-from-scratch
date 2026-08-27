* **Bộ 5 hoàn thiện (Rule of Five):** Nếu một lớp quản lý tài nguyên Heap bằng con trỏ thô và buộc phải tự viết **Destructor**, thì theo chuẩn C++ hiện đại, bạn gần như chắc chắn phải viết nốt 4 thành viên còn lại để tránh lỗi hỏng dữ liệu:
1. *Destructor*
2. *Copy Constructor*
3. *Copy Assignment Operator*
4. *Move Constructor*
5. *Move Assignment Operator*


* **Nguyên tắc Không viết gì (Rule of Zero):** Trọng tâm cao nhất của Modern C++ là **đừng tự quản lý con trỏ thô** nếu không thực sự viết custom allocator. Bằng cách sử dụng các công cụ có sẵn như `std::unique_ptr`, `std::shared_ptr`, `std::string`, và các STL containers (`std::vector`), trình biên dịch sẽ tự động sinh ra mọi hàm hủy, copy, và move một cách cực kỳ an toàn và tối ưu. Bạn không cần phải viết một dòng code thủ công nào để quản lý bộ nhớ nữa.