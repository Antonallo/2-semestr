#include <iostream>

class BitVector {
private:
    size_t size;
    unsigned char* bits;
public:
    BitVector(size_t n) {
        size = n;
        bits = new unsigned char[n / 8 + 1];
        for (size_t i = 0; i < n / 8 + 1; i++) {
            bits[i] = 0;
        }
    }

    BitVector() {
        size = 0;
        bits = NULL;
    }

    ~BitVector() {
        delete[] bits;
    }

    void set(size_t i, bool value) {
        size_t byte_pos = i / 8;
        size_t bit_pos = i % 8;
        if (value) {
            bits[byte_pos] |= (1 << bit_pos);
        }
        else {
            bits[byte_pos] &= ~(1 << bit_pos);
        }
    }

    bool get(size_t i) const {
        size_t byte_pos = i / 8;
        size_t bit_pos = i % 8;
        return (bits[byte_pos] >> bit_pos) & 1U;
    }

    size_t getSize() const {
        return size;
    }

    void insert(size_t pos, bool bit) {
        if (pos > size) {
            size = pos + 1;
            unsigned char* new_bits = new unsigned char[(size / 8) + 1];
            for (size_t i = 0; i < size / 8 + 1; i++) {
                new_bits[i] = 0;
            }
            for (size_t i = 0; i < pos / 8; i++) {
                new_bits[i] = bits[i];
            }
            set(pos, bit);
            for (size_t i = pos / 8; i < size / 8; i++) {
                new_bits[i + 1] = bits[i];
            }
            delete[] bits;
            bits = new_bits;
        }
        else {
            size++;
            for (size_t i = size - 1; i > pos; i--) {
                set(i, get(i - 1));
            }
            set(pos, bit);
        }
    }

    void erase(size_t pos) {
        if (pos >= size) {
            return;
        }
        size--;
        for (size_t i = pos; i < size; i++) {
            set(i, get(i + 1));
        }
    }

    void push_back(bool bit) {
        if (size % 8 == 0) {
            size++;
            unsigned char* new_bits = new unsigned char[(size / 8) + 1];
            for (size_t i = 0; i < size / 8 + 1; i++) {
                new_bits[i] = 0;
            }
            for (size_t i = 0; i < size / 8; i++) {
                new_bits[i] = bits[i];
            }
            delete[] bits;
            bits = new_bits;
        }
        else {
            size++;
        }
        set(size - 1, bit);
    }

    bool operator[](size_t i) const {
        return get(i);
    }
};

int main() {
    // Создание вектора длиной 10 битов
    BitVector bits(10);

    // Установка первых 5 битов в true, а последних 5 в false
    for (size_t i = 0; i < 5; i++) {
        bits.set(i, true);
    }
    for (size_t i = 5; i < 10; i++) {
        bits.set(i, false);
    }

    // Вывод значений битов вектора на экран
    for (size_t i = 0; i < bits.getSize(); i++) {
        std::cout << bits[i] << " ";
    }
    std::cout << std::endl;

    // Добавление нового бита в вектор
    bits.push_back(false);

    // Удаление последних 3 битов вектора
    for (size_t i = 0; i < 3; i++) {
        bits.erase(bits.getSize() - 1);
    }

    // Вывод значений битов вектора на экран
    for (size_t i = 0; i < bits.getSize(); i++) {
        std::cout << bits.get(i) << " ";
    }
    std::cout << std::endl;

    // Считывание значения бита с номером 2 из вектора
    std::cout << bits.get(2) << std::endl;

    // Считывание значения бита с индексом 5 из вектора
    std::cout << bits[5] << std::endl;

    return 0;
}