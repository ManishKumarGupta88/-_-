#include <iostream>
#include <string>
using namespace std;
string encrypt(const string &text, int shift);
string decrypt(const string &text, int shift);
string readFile(const string &filename);
void writeFile(const string &filename, const string &content);
int main() {
    string inputFilename, outputFilename;
    int shift;
    char choice;

    cout << "Enter the input file name: ";
    cin >> inputFilename;
    cout << "Enter the output file name: ";
    cin >> outputFilename;
    cout << "Enter the shift value: ";
    cin >> shift;
    cout << "Encrypt (E) or Decrypt (D)? ";
    cin >> choice;

    string content = readFile(inputFilename);
    string result;

    if (choice == 'E' || choice == 'e') {
        result = encrypt(content, shift);
    } else if (choice == 'D' || choice == 'd') {
        result = decrypt(content, shift);
    } else {
        cerr << "Invalid choice!" <<endl;
        return 1;
    }

    writeFile(outputFilename, result);
    cout << "Operation completed. Check the output file." << endl;

    return 0;
}
// Function to encrypt a text using Caesar cipher
string encrypt(const string &text, int shift) {
    string result = "";
    int i = 0;
    while (text[i] != '\0') {
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            char base = (c >= 'a' && c <= 'z') ? 'a' : 'A';
            char encrypted_char = ((c - base + shift) % 26) + base;
            result.push_back(encrypted_char);
        } else {
            result.push_back(c); 
        }
        i++;
    }
    return result;
}
// Function to decrypt a text using Caesar cipher
string decrypt(const string &text, int shift) {
    return encrypt(text, 26 - shift); 
}
// Function to read content from a file
string readFile(const string &filename) {
    FILE *file = fopen(filename.c_str(), "r");
    if (file == nullptr) {
        cerr << "Error opening file " << filename << endl;
        return "";
    }
    string content;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
        content += buffer;
    }
    fclose(file);
    return content;
}
// Function to write content from a file
void writeFile(const string &filename, const string &content) {
    FILE *file = fopen(filename.c_str(), "w");
    if (file == nullptr) {
        cerr << "Error creating file " << filename << endl;
        return;
    }
    fputs(content.c_str(), file);
    fclose(file);
}