//Клиент 
#include <iostream> 
#include <winsock2.h> 
#include <string> 
#include <windows.h> 
#pragma warning(disable: 4996)  // подавление предупреждения 4996 
#pragma comment (lib, "Ws2_32.lib") 
using namespace std;
#define SRV_HOST "localhost" 
#define SRV_PORT 1234 
#define CLNT_PORT 1235 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

struct Student
{
    char name[20];
    double a[4];
}A;


int main()
{
    setlocale(LC_ALL, "rus");
    Student buff;
    char vvod = '1', con = '1';
    if (WSAStartup(0x0202, (WSADATA*)&buff)) {
        cout << "Error WSAStartup \n" << WSAGetLastError();  // Ошибка! 
        return -1;
    }
    SOCKET s;
    int answ;    
    hostent* hp;
    sockaddr_in clnt_sin, srv_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    clnt_sin.sin_family = AF_INET;
    clnt_sin.sin_addr.s_addr = 0;
    clnt_sin.sin_port = htons(CLNT_PORT);
    bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin));
    hp = gethostbyname(SRV_HOST);
    srv_sin.sin_port = htons(SRV_PORT);
    srv_sin.sin_family = AF_INET;
    ((unsigned long*)&srv_sin.sin_addr)[0] =
        ((unsigned long**)hp->h_addr_list)[0][0];
    cout << "Попытка подключиться к серверу..." << endl;
    while (true) {
        if (connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin)) >= 0) {
            cout << "Подключен к серверу!" << endl;
            break;
        }
        cout << "Ошибка подключения";
    };
    recv(s, &con, sizeof(con), 0);
    cout << "Введите имя и баллы студента "<< endl;
    cin >> A.name>> A.a[0] >> A.a[1] >> A.a[2] >> A.a[3];
    send(s, (char*)&A, sizeof(A), 0);
    recv(s, (char*)&answ, sizeof(answ), 0);
    cout << answ << endl;
    switch (answ)
    {
    case 1: {cout << "Имется задолженость"<< "\n"; break; }
    case 2: {cout << "Получение стипендии невозможна \n"; break; }
    case 3: {cout << "Имеется стипендия \n"; break; }
    case 4: {cout << "Имеется повышенная стипендия \n"; }
    }
    system("pause");
    WSACleanup();
    return 0;
}
