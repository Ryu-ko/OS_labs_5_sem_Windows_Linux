#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

using namespace std;

#define FILE_PATH L"F:/.Уник/3 курс/ОС/9laba/lab09/lab09/OS09_01.txt"

BOOL printFileInfo(LPWSTR FileName);
string getFileName(wchar_t* filePath);
LPCWSTR getFileType(HANDLE file);
BOOL printFileTxt(LPWSTR FileName);

int main()
{
    setlocale(LC_ALL, "Rus");
    
    LPWSTR path = (LPWSTR)FILE_PATH;
    printFileInfo(path);
    printFileTxt(path);
}

BOOL printFileInfo(LPWSTR path) 
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    SYSTEMTIME sysTime;
    BY_HANDLE_FILE_INFORMATION fi;
    BOOL fResult = GetFileInformationByHandle(file, &fi);
    
    if (fResult) 
    {
        FileTimeToSystemTime(&fi.ftCreationTime, &sysTime);
        cout << "Creation time: " << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear << " " << sysTime.wHour + 3 << '.' << sysTime.wMinute << '.' << sysTime.wSecond;
        FileTimeToSystemTime(&fi.ftLastWriteTime, &sysTime);
        cout << "\nLast update time: " << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear << " " << sysTime.wHour + 3 << '.' << sysTime.wMinute << '.' << sysTime.wSecond;
        cout << "\nFile name: " << getFileName((wchar_t*)FILE_PATH);
        wcout << "\nFile type: " << getFileType(file);
        cout << "\nFile size: " << fi.nFileSizeHigh << '.' << fi.nFileSizeLow;
    }
    
    CloseHandle(file);
    return true;
}

BOOL printFileTxt(LPWSTR path) 
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    // Буфер для чтения файла
    char buf[1024];
    DWORD countBytes = 0;
    
    ZeroMemory(buf, sizeof(buf));

    // Чтение файла с использованием функции ReadFile
    BOOL b = ReadFile(file, &buf, sizeof(buf) - 1, &countBytes, NULL);
    if (!b) throw "read file failed";

    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
    
    wchar_t* wideStr = new wchar_t[wideStrLen];
    int result = MultiByteToWideChar(CP_UTF8, 0, buf, -1, wideStr, wideStrLen);

    int ansiLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);

    char* ansiStr = new char[ansiLen];
    result = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, ansiStr, ansiLen, NULL, NULL);

    cout << "\n-- Read file " << countBytes << " byte succesfull:\n" << ansiStr << '\n';
}

LPCWSTR getFileType(HANDLE file) 
{
    
    switch (GetFileType(file)) 
    {
        case FILE_TYPE_UNKNOWN:
            return L"FILE_TYPE_UNKNOWN";
        case FILE_TYPE_DISK:
            return L"FILE_TYPE_DISK";
        case FILE_TYPE_CHAR:
            return L"FILE_TYPE_CHAR";
        case FILE_TYPE_PIPE:
            return L"FILE_TYPE_PIPE";
        case FILE_TYPE_REMOTE:
            return L"FILE_TYPE_REMOTE";
        default:
            return L"ERROR: WRITE FILE TYPE";
    }
}
string getFileName(wchar_t* filePath) 
{
    wstring ws(filePath);
    
    string filename(ws.begin(), ws.end());
    
    const size_t last_slash_idx = filename.find_last_of("\\/");
    
    if (string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }
    
    return filename;
}

















//
//FileTimeToSystemTime - это функция в Windows API, используемая для преобразования времени в формате FILETIME в формат SYSTEMTIME.
//
//cpp
//Copy code
//BOOL FileTimeToSystemTime(
//    const FILETIME* lpFileTime,  // указатель на структуру FILETIME
//    LPSYSTEMTIME   lpSystemTime  // указатель на структуру SYSTEMTIME
//);



//HANDLE file = CreateFile(
//    path,                  // LPCTSTR lpFileName: Путь к файлу
//    GENERIC_READ,          // DWORD dwDesiredAccess: Запрашиваемый доступ к файлу
//    NULL,                  // DWORD dwShareMode: Режим совместного доступа
//    NULL,                  // LPSECURITY_ATTRIBUTES lpSecurityAttributes: Атрибуты безопасности (в данном случае, отсутствуют)
//    OPEN_ALWAYS,           // DWORD dwCreationDisposition: Действие при создании файла (открывать существующий, если существует) если файл существует, он должен быть открыт, а если не существует, то создан.Другие возможные значения включают CREATE_NEW, CREATE_ALWAYS, и т.д.
//    FILE_ATTRIBUTE_NORMAL, // DWORD dwFlagsAndAttributes: Атрибуты файла (обычный файл)
//    NULL);                 // HANDLE hTemplateFile: Шаблон файла (не используется, установите в NULL)

// 
//FILE_TYPE_UNKNOWN: Этот тип файла указывает, что тип файла неизвестен.Вероятно, это может произойти, если система не может определить тип файла.
//
//FILE_TYPE_DISK : Этот тип файла указывает на дисковый файл.Такие файлы обычно хранятся на физических носителях данных, таких как жесткие диски.
//
//FILE_TYPE_CHAR : Этот тип файла указывает на символьное устройство.Символьные устройства предоставляют поток символов, и их можно читать или записывать как последовательность символов.
//
//FILE_TYPE_PIPE : Этот тип файла указывает на канал(pipe).Каналы - это механизм межпроцессного взаимодействия, где данные могут передаваться между процессами.
//
//FILE_TYPE_REMOTE : Этот тип файла указывает на удаленный файл.Такие файлы находятся на удаленном устройстве или сервере.
//
//default: Если встречается тип файла, который не соответствует ни одному из указанных в case, возвращается сообщение об ошибке "ERROR: WRITE FILE TYPE".


//
//wstring ws(filePath); : Здесь создается объект wstring(строка широких символов) из переданного wchar_t* пути к файлу.Это нужно для работы с путями, содержащими символы широких символов(Unicode).


// если слеш найден то удаляем строку от начала до позиции слеша включая
//if (string::npos != last_slash_idx)
//{
//    filename.erase(0, last_slash_idx + 1);
//}



//BOOL b = ReadFile(file, &buf, sizeof(buf) - 1, &countBytes, NULL);

//HANDLE file : Дескриптор файла, из которого будут считываться данные.
//
//LPVOID lpBuffer : Указатель на буфер, в который будут записываться считанные данные.
//
//DWORD nNumberOfBytesToRead : Количество байтов, которое нужно прочитать из файла.
//
//LPDWORD lpNumberOfBytesRead : Указатель на переменную, в которую будет записано реальное количество считанных байт.
//
//LPOVERLAPPED lpOverlapped : Указатель на структуру OVERLAPPED, используемую для асинхронного ввода - вывода.В данном случае, так как последний параметр установлен в NULL, операция чтения будет синхронной.


//int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0); из UTF8 в широкую строку (Unicode).

//UINT CodePage : Кодовая страница, используемая для преобразования.В данном случае, CP_UTF8, что означает, что входные данные представляют собой UTF - 8 кодированный текст.
//
//DWORD dwFlags : Флаги для дополнительных опций конвертации.В данном случае, параметр установлен в 0, что указывает на отсутствие дополнительных опций.
//
//LPCCH lpMultiByteStr : Указатель на строку, содержащую последовательность байтов(в данном случае, ваш буфер buf).
//
//int cbMultiByte : Количество байт во входной строке.В данном случае, -1 означает, что входная строка является нуль - терминированной, и длина будет автоматически определена.
//
//LPWSTR lpWideCharStr : Указатель на буфер, в который будут записаны широкие символы.
//
//int cchWideChar : Максимальное количество широких символов, которые могут быть записаны в буфер.Если этот параметр установлен в 0, функция вычислит необходимый размер буфера.


//
//широкой строки в ANSI - кодировку.
//
//CP_ACP: Это константа, представляющая кодовую страницу системы(ANSI code page).
//
//0 : Флаги.В данном случае, они установлены в 0, что означает использование стандартных опций преобразования.
//
//wideStr : Указатель на входную широкую строку(Unicode).
//
//- 1 : Количество символов входной строки для преобразования.Значение - 1 указывает на то, что строка должна быть преобразована полностью до завершающего символа NULL.
//
//NULL : Указатель на буфер для хранения многобайтовой строки.Если этот параметр установлен в NULL, функция возвращает размер буфера, не записывая данные.
//
//0 : Размер выходного буфера в байтах.
//
//NULL : Указатель на переменную, которая будет содержать количество байтов, записанных в буфер.Если параметр равен NULL, эта информация не возвращается.
//
//NULL : Указатель на переменную, которая будет содержать значение замещающего символа(если он используется).В данном случае, параметр не используется, поэтому передается NULL.


