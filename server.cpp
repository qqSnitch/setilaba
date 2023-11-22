//Сервер 
#include <iostream> 
#include <winsock2.h> 
#include <windows.h> 
#include <string> 
#pragma comment (lib, "Ws2_32.lib") 
#pragma warning(disable: 4996)  // подавление предупреждения 4996 
#define SRV_PORT 1234 
#define BUF_SIZE 64 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
using namespace std;
struct Student
{
    char name[20];
    double a[4];
}B;

int main() {
    setlocale(LC_ALL, "rus");
    Student buff;
    int avarege_score;
    int n;
    if (WSAStartup(0x0202, (WSADATA*)&buff))
    {
        cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка! 
        return -1;
    }
    SOCKET s, s_new;
    int from_len;
    char buf[BUF_SIZE] = { 0 };
    sockaddr_in sin, from_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(SRV_PORT);
    bind(s, (sockaddr*)&sin, sizeof(sin));
    char ready;
    listen(s, 3);
    while (1) {
        cout << "Вошёл в цикл! " << endl;
        from_len = sizeof(from_sin);
        s_new = accept(s, (sockaddr*)&from_sin, &from_len);
        cout << "Подключён новый клиент! " << endl;
        ready = '1';
        send(s_new, &ready, sizeof(ready), 0);
        recv(s_new, (char*)&B, sizeof(B), 0);
        if (B.a[0] < 3 || B.a[1] < 3 || B.a[2] < 3 || B.a[3] < 3)avarege_score = 1;
        else if (B.a[0] == 3 || B.a[1] == 3 || B.a[2] == 3 || B.a[3] == 3)avarege_score = 2;
        else if (B.a[0] == 4 || B.a[1] == 4 || B.a[2] == 4 || B.a[3] == 4)avarege_score = 3;
        else if (B.a[0] == 5 || B.a[1] == 5 || B.a[2] == 5 || B.a[3] == 5)avarege_score = 4;
        send(s_new, (char*)&avarege_score, sizeof(avarege_score), 0); avarege_score = 0;
        cout << "Клиент отключён" << endl;
        closesocket(s_new);
    }
    WSACleanup();
    return 0;
}
