
#include <iostream>
#include <Windows.h>
#include <process.h>

int main()
{
    LPCWSTR an = L"..\\Debug\\OS03_02_1.exe";
    LPCWSTR an1 = L"..\\Debug\\OS03_02_2.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi, pi1; 
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) ) std::cout << "---Proc 1 created\n";
    else std::cout << "---Proc 1 not created\n";
    if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1)) std::cout << "---Proc 2 created\n";
    else std::cout << "---Proc 2 not created\n";

    for (int i = 0; i < 100; i++) {
        Sleep(1000);
        std::cout << "OS03_02: " << _getpid() << "\n";
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    WaitForSingleObject(pi1.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi1.hProcess);

    return 0;
}





// STARTUPINFO si; // структура, исп для настройки атрибутов нового процесса
// PROCESS_INFORMATION pi, pi1; // информация о созданном процессе и его первичном потоке


 //заполняет блок памяти нулями.
    //1-указатель на блок памяти, 2-размер блока памяти
// ZeroMemory(&si, sizeof(STARTUPINFO));


// путь, cmd, 2 указателя на структуру для настройки атрибутов безопасности процесса и потока, нет наследования,
// имеем собственное окно консоли, не исп текущий каталог для нового процесса, 
// пустой указатель на структуру STARTUPINFO, структура в кот сохр инфа о созд процессе 
// 1 параметр указывает на имя исполняемого модуля, который следует запустить.
// предпоследний: Эта структура используется для указания свойств окна, таких как размеры окна, положение, атрибуты окна, стандартные дескрипторы и другие параметры.
// последний параметр представляет собой структуру PROCESS_INFORMATION, которая будет заполнена информацией о созданном процессе и его основном потоке.
// if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) std::cout << "---Proc 1 created\n";


// WaitForSingleObject(pi.hProcess, INFINITE); //ждать пока дочерний процесс не выйдет из работы(время ожидания)