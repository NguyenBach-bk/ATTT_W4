#include <iostream>
using namespace std;

// Hàm khởi tạo mảng S với khóa
void ksa(int S[], const string &key) {
    int key_length = key.length();
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(S[i], S[j]);
    }
}

// Hàm tạo keystream và mã hóa
string rc4(const string &text, const string &key) {
    int S[256];
    ksa(S, key);

    int i = 0, j = 0;
    string cipher_text = "";

    for (size_t n = 0; n < text.length(); n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);

        int K = S[(S[i] + S[j]) % 256]; // Key-stream byte
        cipher_text += text[n] ^ K; // XOR với byte
    }

    return cipher_text;
}

// Hàm in chuỗi dưới dạng hex
void print_hex(const string &str) {
    for (unsigned char c : str) {
        cout << hex << ((c >> 4) & 0xF) << (c & 0xF) << " ";
    }
    cout << endl;
}

int main() {
    // Khóa và chuỗi text
    string key = "ETE9";
    string text = "Hanoi University of Science and Technology";

    // Mã hóa RC4
    string cipher_text = rc4(text, key);

    // In kết quả
    cout << "Key: " << key << endl;
    cout << "Thong tin: " << text << endl;
    cout << "Ma hoa (hex): ";
    print_hex(cipher_text);

    return 0;
}