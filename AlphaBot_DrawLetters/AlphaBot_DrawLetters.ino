/*******************************************************************************
 * Waveshare AlphaBot - Letter Drawing (Vẽ chữ cái in hoa: L, C, K)
 * 
 * Thư viện: AlphaBot.h
 * Phần cứng: Waveshare AlphaBot Car + Arduino UNO
 * 
 * Mục đích: Điều khiển xe AlphaBot di chuyển theo quỹ đạo để vẽ các chữ cái in hoa:
 * - drawL(): Vẽ chữ L
 * - drawC(): Vẽ chữ C
 * - drawK(): Vẽ chữ K
 * 
 * Biến tỉ lệ:
 *   n (ms): Thời gian chuẩn để xe đi hết một nét đơn vị (chiều cao chuẩn).
 *   Mọi khoảng cách và góc quay được tính toán tỉ lệ theo n:
 *   - Nét dọc chuẩn: n (ms)
 *   - Nét ngang: 0.6 * n (ms) (hoặc n nếu muốn chữ vuông)
 *   - Nét xiên chữ K: ~0.7 * n (ms) (căn cứ theo định lý Pytago: sqrt(0.5^2 + 0.5^2) ≈ 0.707)
 *   - Góc quay 90 độ: 0.22 * n (ms)
 *   - Góc quay 45 độ: 0.11 * n (ms)
 *   - Góc quay 180 độ: 0.34 * n (ms)
 *******************************************************************************/

#include "AlphaBot.h"

// Khởi tạo đối tượng AlphaBot
AlphaBot Car1 = AlphaBot();

// Biến n xác định tỉ lệ kích thước vẽ (thời gian tính bằng ms)
// Người dùng có thể thay đổi giá trị này để phóng to / thu nhỏ kích thước chữ
int n = 3000;

// Tốc độ động cơ của xe (0 - 255)
// Tốc độ 100 giúp xe chạy êm, lực kéo ổn định và hạn chế trượt bánh
const int CAR_SPEED = 100;

// Thời gian nghỉ (ms) giữa các bước di chuyển để chống giật và hạn chế sai số quán tính
const int STEP_DELAY = 500;

/*******************************************************************************
 * 1. HÀM VẼ CHỮ L IN HOA
 * -----------------------------------------------------------------------------
 * Vị trí bắt đầu: Đặt xe tại đỉnh góc trên bên trái của chữ L.
 * Hướng xe ban đầu: Hướng thẳng xuống dưới (Nam).
 * Quỹ đạo:
 *   - Đi thẳng n (vẽ nét dọc thân chữ L hướng xuống)
 *   - Rẽ trái 90 độ (hướng sang phải - Đông)
 *   - Đi thẳng 0.6 * n (vẽ nét ngang chân chữ L)
 *******************************************************************************/
void drawL(int scale = n) {
    // 1. Vẽ nét dọc thân chữ L
    Car1.Forward((unsigned int)scale);
    delay(STEP_DELAY);

    // 2. Rẽ trái 90 độ (hướng về phía nét ngang)
    Car1.Left((unsigned int)(0.22 * scale));
    delay(STEP_DELAY);

    // 3. Vẽ nét ngang chân chữ L (chiều rộng = 0.6 * scale)
    Car1.Forward((unsigned int)(0.6 * scale));
    delay(STEP_DELAY);

    // Dừng xe sau khi hoàn thành
    Car1.Brake();
}

/*******************************************************************************
 * 2. HÀM VẼ CHỮ C IN HOA
 * -----------------------------------------------------------------------------
 * Vị trí bắt đầu: Đặt xe tại góc trên bên phải của chữ C.
 * Hướng xe ban đầu: Hướng sang trái (Tây).
 * Quỹ đạo:
 *   - Đi thẳng 0.6 * n (vẽ nét ngang đỉnh chữ C từ phải sang trái)
 *   - Rẽ trái 90 độ (hướng xuống dưới - Nam)
 *   - Đi thẳng n (vẽ nét dọc lưng chữ C)
 *   - Rẽ trái 90 độ (hướng sang phải - Đông)
 *   - Đi thẳng 0.6 * n (vẽ nét ngang đáy chữ C từ trái sang phải)
 * (Lưu ý: Nếu muốn chữ C hình vuông đều, có thể đổi 0.6 * scale thành scale)
 *******************************************************************************/
void drawC(int scale = n) {
    // 1. Vẽ nét ngang trên của chữ C
    Car1.Forward((unsigned int)(0.6 * scale));
    delay(STEP_DELAY);

    // 2. Rẽ trái 90 độ để chúc xuống
    Car1.Left((unsigned int)(0.22 * scale));
    delay(STEP_DELAY);

    // 3. Vẽ nét dọc lưng chữ C (chiều cao = scale)
    Car1.Forward((unsigned int)scale);
    delay(STEP_DELAY);

    // 4. Rẽ trái 90 độ để hướng sang phải
    Car1.Left((unsigned int)(0.22 * scale));
    delay(STEP_DELAY);

    // 5. Vẽ nét ngang đáy của chữ C
    Car1.Forward((unsigned int)(0.6 * scale));
    delay(STEP_DELAY);

    // Dừng xe sau khi hoàn thành
    Car1.Brake();
}

/*******************************************************************************
 * 3. HÀM VẼ CHỮ K IN HOA (Theo quy trình Prototype chuẩn của bạn)
 * -----------------------------------------------------------------------------
 * Vị trí bắt đầu: Đặt xe tại chân nét dọc (góc dưới bên trái).
 * Hướng xe ban đầu: Hướng lên trên (Bắc).
 * Quỹ đạo:
 *   - Đi thẳng n (vẽ nét dọc chính từ dưới lên trên)
 *   - Quay 180 độ quay đầu xe (hướng xuống dưới - Nam)
 *   - Đi thẳng 0.5 * n (đi về đúng tâm điểm giữa thân chữ)
 *   - Rẽ trái 45 độ (xe chúc theo hướng Đông-Nam, góc 135 độ so với trục dọc)
 *   - Đi thẳng 0.7 * n (vẽ nét xiên dưới bên phải)
 *   - Lùi thẳng 0.7 * n (lùi về lại tâm giữa bằng Backward để giữ nguyên góc)
 *   - Rẽ trái 90 độ (từ Đông-Nam rẽ trái 90 độ sẽ hướng lên Đông-Bắc)
 *   - Đi thẳng 0.7 * n (vẽ nét xiên trên bên phải)
 *******************************************************************************/
void drawK(int scale = n) {
    // 1. Vẽ nét dọc chính (hướng từ dưới lên trên)
    Car1.Forward((unsigned int)scale);
    delay(STEP_DELAY);

    // 2. Quay 180 độ quay đầu về
    Car1.Left((unsigned int)(0.34 * scale));
    delay(STEP_DELAY);

    // 3. Đi về chính giữa nét dọc (0.5 * scale)
    Car1.Forward((unsigned int)(0.5 * scale));
    delay(STEP_DELAY);

    // 4. Rẽ trái 45 độ (hướng xuống nét xiên dưới bên phải - Đông Nam)
    Car1.Left((unsigned int)(0.11 * scale));
    delay(STEP_DELAY);

    // 5. Đi nét xiên dưới (~0.7 * scale)
    Car1.Forward((unsigned int)(0.7 * scale));
    delay(STEP_DELAY);

    // 6. Lùi lại về điểm giữa (dùng Backward để không bị lệch góc xe)
    Car1.Backward((unsigned int)(0.7 * scale));
    delay(STEP_DELAY);

    // 7. Rẽ trái 90 độ để hướng lên nét xiên trên (Đông Bắc)
    Car1.Left((unsigned int)(0.22 * scale));
    delay(STEP_DELAY);

    // 8. Đi nét xiên trên (~0.7 * scale)
    Car1.Forward((unsigned int)(0.7 * scale));
    delay(STEP_DELAY);

    // Dừng xe sau khi hoàn thành
    Car1.Brake();
}

/*******************************************************************************
 * PHƯƠNG PHÁP TỐI ƯU CHO CHỮ K: drawK_Optimized()
 * -----------------------------------------------------------------------------
 * Ưu điểm thực nghiệm trong Robot học:
 * Không cần quay 180 độ (giảm thiểu sai số trượt bánh và quán tính xe).
 * Sau khi vẽ nét dọc, xe dùng Car1.Backward(0.5 * scale) lùi thẳng về tâm giữa,
 * sau đó rẽ phải 45 độ để vẽ nét xiên trên, rồi rẽ phải 90 độ để vẽ nét xiên dưới.
 *******************************************************************************/
void drawK_Optimized(int scale = n) {
    // 1. Vẽ nét dọc chính từ dưới lên
    Car1.Forward((unsigned int)scale);
    delay(STEP_DELAY);

    // 2. Lùi thẳng về điểm giữa thân chữ (vẫn giữ nguyên hướng Bắc)
    Car1.Backward((unsigned int)(0.5 * scale));
    delay(STEP_DELAY);

    // 3. Rẽ phải 45 độ (hướng xiên lên trên bên phải - Đông Bắc)
    Car1.Right((unsigned int)(0.11 * scale));
    delay(STEP_DELAY);

    // 4. Vẽ nét xiên trên
    Car1.Forward((unsigned int)(0.7 * scale));
    delay(STEP_DELAY);

    // 5. Lùi về tâm giữa (vẫn hướng Đông Bắc)
    Car1.Backward((unsigned int)(0.7 * scale));
    delay(STEP_DELAY);

    // 6. Rẽ phải 90 độ (từ Đông Bắc chuyển sang hướng Đông Nam)
    Car1.Right((unsigned int)(0.22 * scale));
    delay(STEP_DELAY);

    // 7. Vẽ nét xiên dưới
    Car1.Forward((unsigned int)(0.7 * scale));
    delay(STEP_DELAY);

    // Dừng xe sau khi hoàn thành
    Car1.Brake();
}

void setup() {
    // Cài đặt tốc độ động cơ
    Car1.SetSpeed(CAR_SPEED);
    
    // Chờ 2 giây để người dùng đặt xe xuống sàn và thả tay an toàn
    delay(2000);

    // Chọn hàm vẽ bạn muốn thực hiện (bỏ comment hàm cần chạy):
    // drawL();
    // drawC();
    drawK();
    // drawK_Optimized();
}

void loop() {
    // Để trống vòng lặp để xe chỉ thực hiện vẽ 1 lần duy nhất trong setup()
}