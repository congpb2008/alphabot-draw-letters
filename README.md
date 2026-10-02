# Waveshare AlphaBot - Letter Drawing (L, C, K)

Chương trình điều khiển robot **Waveshare AlphaBot** vẽ các chữ cái in hoa **L**, **C** và **K** trên nền tảng Arduino UNO, dựa trên tham số tỉ lệ thời gian `n` (milliseconds).

---

## 📌 Tổng quan dự án

Dự án này hiện thực hóa các hàm di chuyển và điều khiển góc quay của robot vi sai 2 bánh Waveshare AlphaBot để vẽ quỹ đạo hình học của 3 chữ cái in hoa:
- `drawL()`: Vẽ chữ L in hoa (nét liền không nhấc bút).
- `drawC()`: Vẽ chữ C in hoa (nét liền không nhấc bút).
- `drawK()`: Vẽ chữ K in hoa theo quy trình quay 180° và lùi về tâm.
- `drawK_Optimized()`: Phương pháp vẽ chữ K cải tiến (sử dụng `Backward` lùi thẳng về tâm mà không quay 180°, triệt tiêu hoàn toàn sai số trượt bánh do quán tính).

---

## ⚙️ Nguyên lý tỉ lệ thời gian `n`

Tất cả các khoảng cách di chuyển và thời gian quay đều được tính toán theo tỉ lệ chuẩn hóa với biến `n` (`int n = 3000;` tương đương 3000ms):

| Yếu tố hình học | Công thức thời gian | Thời gian tương ứng khi $n = 3000$ | Ý nghĩa hình học |
| :--- | :--- | :--- | :--- |
| **Nét dọc chuẩn** | `n` | 3000 ms | Chiều cao chuẩn của thân chữ |
| **Nét ngang** | `0.6 * n` | 1800 ms | Bề rộng chân chữ L và đỉnh/đáy chữ C |
| **Nét xiên (K)** | `0.7 * n` | 2100 ms | Cạnh huyền tam giác vuông $\sqrt{0.5^2 + 0.5^2} \approx 0.707$ |
| **Góc quay 90°** | `0.22 * n` | 660 ms | Quay góc vuông |
| **Góc quay 45°** | `0.11 * n` | 330 ms | Quay góc xiên nét chữ K |
| **Góc quay 180°** | `0.34 * n` | 1020 ms | Quay ngược đầu (có tính bù quán tính bánh xe) |

> **Lưu ý chống giật bánh:**
> Mã nguồn đã tích hợp khoảng đệm dừng `delay(STEP_DELAY)` (500ms) sau mỗi bước di chuyển nhằm triệt tiêu quán tính cơ học và mô-men xoắn phản hồi, giúp robot giữ góc quay chính xác tuyệt đối trên bề mặt phẳng.

---

## 🧭 Hướng dẫn đặt xe ban đầu

1. **Chữ L (`drawL`)**:
   - Vị trí: Góc trên cùng bên trái.
   - Hướng xe: Chúc thẳng xuống dưới (Nam).
2. **Chữ C (`drawC`)**:
   - Vị trí: Góc trên cùng bên phải.
   - Hướng xe: Hướng sang trái (Tây).
3. **Chữ K (`drawK` / `drawK_Optimized`)**:
   - Vị trí: Chân nét dọc chính (góc dưới cùng bên trái).
   - Hướng xe: Hướng thẳng lên trên (Bắc).

---

## 🛠️ Cấu hình phần cứng

- **Bo mạch điều khiển:** Arduino UNO R3
- **Khung xe robot:** Waveshare AlphaBot
- **Mạch điều khiển động cơ:** L298P Dual H-Bridge Motor Driver
  - Motor trái: ENA (Pin 5), IN1 (A1), IN2 (A0)
  - Motor phải: ENB (Pin 6), IN4 (A2), IN3 (A3)
- **Tốc độ mặc định:** `CAR_SPEED = 100` (trên thang 255)

---

## 🚀 Cách nạp chương trình

1. Mở file `AlphaBot_DrawLetters/AlphaBot_DrawLetters.ino` bằng **Arduino IDE**.
2. Đảm bảo file `AlphaBot.h` và `AlphaBot.cpp` nằm cùng thư mục với file `.ino`.
3. Trong hàm `setup()`, bỏ dấu chú thích `//` trước hàm bạn muốn vẽ (`drawL()`, `drawC()`, hoặc `drawK()`).
4. Chọn Board: **Arduino Uno** và đúng cổng COM tương ứng.
5. Bấm **Upload** (Nạp code). Xe sẽ chờ 2 giây trước khi bắt đầu vẽ để bạn kịp đặt xe xuống sàn và thả tay an toàn.

---

## 📄 Bản quyền

Mã nguồn mở phục vụ học tập và nghiên cứu phòng thí nghiệm IoT / Robotics.
