/***********************************************


    digital_scale 

Chức năng: đo lượng nước đã uống 

author: Nguyễn Thanh Tùng
date: 12/2/25

hệ số chuẩn: -1057.894




**********************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <Arduino.h>
#include "HX711.h"
#include "Last2.h"
#include "Touch_sensor.h"

// interface 
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int TOUCH_SENSOR_PIN = 4; 


// ngoại vi 
HX711 scale;
Touch_sensor tSensor(TOUCH_SENSOR_PIN); 
// LiquidCrystal_I2C lcd(0x27, 16, 2); 

// biến toàn cục 
Last2 data; 
int currWeight = 0;
int lastWeight = 0;
int steadyWeight = 0;   
int drinkedWater = 0; 
int currT = 0; 
int lastT = 0; 

void setup() {
  Serial.begin(57600); 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); 
  scale.set_scale(-385.421); 
  scale.tare(0); 
}

void loop() {
  // tổng quan như thế nào hè?
  // 1. nếu như đang chạm thì không làm các điều dưới  
  // 2. xác định lượng nước bình ổn  
  // 3. tính lượng nước đã uống
      // a. xem lượng nước trong ly bình ổn trong ly 
      // b. so sánh với lượng nước bình ổn trước đó 
      // c. nếu lượng nước bình ổn trong ly thay đổi và lượng nước trước đó lớn hơn -> 
          //cộng chênh lệch vào lượng nước đã uống 

  if (!(tSensor.isTouched())) {
  // mốc thời gian 
  currT = millis(); 

  // lấy giá trị cân nặng hiện tại  
  currWeight = round_number_for_scale(scale.get_units(1)); 
  currWeight = currWeight - (currWeight % 10); 

  // 1. xác định lượng nước bình ổn sau 2s 
    // check xem thử lượng nước này có giống với lượng nước trước đó không?
    // nếu có thì lượng nước bình ổn là lượng nước hiện tại  
  if (currWeight == lastWeight && currT - lastT > 2000) {
    steadyWeight = currWeight; 
    lastT = currT; 
  }


  Serial.print("Lượng nước bình ổn: "); 
  Serial.println(steadyWeight); 


  // 2. xác định lượng nước đã uống 
    // cập nhập giá trị bình ổn: điều kiện cập nhập: giá trị đã có trong dữ liệu khác với giá trị hiện tại 
    // cập nhập giá trị nước đã uống. Điều kiện cập nhập: giống với cái trên 
    if (data.new_value != steadyWeight) {
      data.add(steadyWeight); 
      if (data.new_value < data.old_value) {
        drinkedWater += data.old_value - data.new_value; 
      }
    }

  Serial.print("Lượng nước đã uống: "); Serial.println(drinkedWater); 





  // cập nhập giá trị cho loop tiếp theo 
  lastWeight = currWeight; 

  delay(100);


  } // end of touch_sensor if
    


  

}

/***************

  Làm tròn số 
    từ cân 

**************/
unsigned int round_number_for_scale(float number) {
  unsigned int result;

  number *= -1; 

  
  if (number < 1) { 
    number = 0; 
  } else {
    number = (unsigned int)round(number); 
  }

  result = number; 

  return result; 
}


/***********

 TIMEPASS

check thời 
  gian đã 
  trôi qua 

***********/
void timepass(int) {}