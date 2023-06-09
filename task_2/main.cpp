#include<iostream>

void my_memcpy(void* dst, const void* src, size_t size) {
    size_t bytes_amount = sizeof(src) * size;
    char* dst_bytes = (char*)dst;
    const char* src_bytes = (const char*)src;
    for (size_t i = 0; i < bytes_amount; ++i)
        dst_bytes[i] = src_bytes[i];
}

int main() {
    char str1[] = "Hello, world!";
    char str2[20];
    my_memcpy(str2, str1, strlen(str1) + 1);
    std::cout << str2;
    return 0;
}
        