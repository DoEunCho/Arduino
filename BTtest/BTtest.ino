#include <SoftwareSerial.h>

SoftwareSerial BTSerial(11, 12);  // SoftwareSerial(RX, TX)

byte buffer[1024];    // 데이터 수신 버퍼
int bufferPosition;   // 버퍼에 기록할 위치

void setup()  
{
  BTSerial.begin(9600);   // 블루투스 모듈 초기화
  Serial.begin(9600);   // 시리얼 모니터 초기화
  bufferPosition = 0; //버퍼 위치 초기화
}

// loop문 안에서 데이터를 받아올 때는 한번에 한글자씩 받아오게 됨.
// 글자를 하나씩 받아와서 출력하고, 현재 bufferPositon에 맞게 데이터를 버퍼에 저장하고 bufferPositon을 1개 늘려줌.
// 이렇게 계속 반복하여 문자열의 끝('\n') 이 나오게 되면 버퍼의 마지막에 ('\0')을 넣고 버퍼에 저장된 문자열을 
// 다시 스마튼폰으로 전송하고 버퍼를 초기화 해준다. 

void loop()
{
  if (BTSerial.available()){      // 블루투스로 데이터 수신
    byte data = BTSerial.read(); //수신 받은 데이터 저장
    Serial.write(data);       // 수신된 데이터 시리얼 모니터로 출력
    buffer[bufferPosition++] = data;
    
    if(data == '\n'){     // 문자열 종료 표시
      buffer[bufferPosition] = '\0';

    // 스마트폰으로 전송할 문자열을 시리얼 모니터에 출력
    //  Serial.print("Echo Back : "); 
    //  Serial.write(buffer, bufferPosition);
      delay(2000);
      // 스마트폰으로 문자열 전송
      BTSerial.write(buffer, bufferPosition);
      bufferPosition = 0;
    }
  }
}
