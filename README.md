# The Sword in the Stone

## Mô tả

"The Sword in the Stone" là một trò chơi mô phỏng cuộc phiêu lưu của các hiệp sĩ trong việc giải cứu thế giới khỏi phép thuật hủy diệt của phù thủy Ultimecia. Trò chơi bao gồm nhiều sự kiện và nhân vật khác nhau, mỗi nhân vật có khả năng và đặc điểm riêng.

## Hướng dẫn

1. Đọc kỹ mô tả của "The Sword in the Stone" để hiểu rõ về luật chơi và các nhân vật trong game.

2. (Tùy chọn) Bạn có thể sửa đổi nội dung trong các file `tc1_armyknights` và `tc1_events` để tạo ra các kịch bản game khác nhau. Nếu không, bạn có thể giữ nguyên các file mẫu.

3. Mở terminal và di chuyển đến thư mục chứa các file source code.

4. Biên dịch chương trình bằng lệnh sau:

   ```
   g++ -o main main.cpp knight2.cpp -I . -std=c++11
   ```

5. Chạy chương trình với lệnh:

   ```
   ./main tc1_armyknights tc1_events
   ```

6. Chương trình sẽ chạy và hiển thị kết quả cuối cùng là "WIN" hoặc "LOSE" tùy thuộc vào kết quả của cuộc phiêu lưu.

## Lưu ý

- Đảm bảo rằng bạn đã cài đặt trình biên dịch C++ (g++) trên máy tính của mình.
- Các file `tc1_armyknights` và `tc1_events` phải nằm trong cùng thư mục với các file source code.
- Kết quả của trò chơi phụ thuộc vào các sự kiện và đặc điểm của các hiệp sĩ được định nghĩa trong các file input.