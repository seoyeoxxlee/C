#include <stdio.h>
#include <wiringPi.h>

#define BUZZER_PIN 1  // GPIO 18

void shortBeep() {
    digitalWrite(BUZZER_PIN, HIGH); // 짧은 신호 켜기
    delay(250);                     // 250ms 유지
    digitalWrite(BUZZER_PIN, LOW);  // 끄기
    delay(250);                     // 신호 간 간격
}

void longBeep() {
    digitalWrite(BUZZER_PIN, HIGH); // 긴 신호 켜기
    delay(750);                     // 750ms 유지
    digitalWrite(BUZZER_PIN, LOW);  // 끄기
    delay(250);                     // 신호 간 간격
}

void sendSOS() {
    // 'S': 짧은 신호 3번
    for (int i = 0; i < 3; i++) shortBeep();

    delay(750); // 문자 간 간격

    // 'O': 긴 신호 3번
    for (int i = 0; i < 3; i++) longBeep();

    delay(750); // 문자 간 간격

    // 'S': 짧은 신호 3번
    for (int i = 0; i < 3; i++) shortBeep();

    delay(1500); // 단어 간 간격
}

int main(void) {
    if (wiringPiSetup() == -1) return 1; // 초기화 실패 시 종료

    pinMode(BUZZER_PIN, OUTPUT); // 버저 출력 설정

    while (1) {
        sendSOS(); // SOS 반복 출력
    }

    return 0;
}
