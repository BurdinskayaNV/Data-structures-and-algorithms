/// \file StringLegacy.h
/// \brief ������ � ������� �����
/// \author ���������� ������� ���-22
/// \date 10.05.2024

#pragma once
#include <string.h>   // ��� ������ � C-��������, ����� ��� strcpy, strcat � �.�.
#include <memory>     // ��� ������ � ������������ ���������� ������
#include <string>     // ��� ��������� ���������� C++
#include <vector>     // ��� ������ � ��������
#include <stdexcept>  // ��� ��������� �� �����������
#include <iostream>   // ��� ������ � �������� �����-������
#include <fstream>    // ��� �������� ������ � ������ ���������� � ���.
#include <cassert>    // ��� ���������� ������� assert()
#include <assert.h>   // ����������� ������ ������������� ����� � assert()

using namespace std;
class StringLegacy {
private: 
    char* str_;     // ������
    size_t length_; // ����� ������

    // ������� ���������� ������� ���������
    size_t* build_prefix_table(const StringLegacy& pattern) const
    {
       size_t* prefix_table = new size_t[pattern.length_];
       // ������������� ������� �������� �������
       prefix_table[0] = 0;
       // ������������� ��������
       size_t i = 1;
       size_t j = 0;
       // ���������� ������� ���������
       while (i < pattern.length_) {
          if (pattern.str_[i] == pattern.str_[j]) {
             prefix_table[i] = j + 1;
             i++; j++; }
          else {
             if (j > 0) { j = prefix_table[j - 1]; }
             else { prefix_table[i] = 0; i++; }
          }
       }
       return prefix_table; }

public:
    StringLegacy() : str_(_strdup("")), length_(0) {} 
    // ������� strdup() ����� ��������� � ������� malloc() �������� ������, ����������� ��� �������� ��������� ������,
    // �� ������� ��������� str, � ����� ���������� ����������� ���� ������ � ���������� ������� � ���������� ��������� �� ���. 
    
    // ����������� �� ���������
    StringLegacy(const char* str) : str_(_strdup(str)), length_(strlen(str)) {}
    // ����������� �� ���������
    StringLegacy(size_t length) : str_(_strdup("")), length_(length) {}
    //����������� �� string
    StringLegacy(const string& str) : str_(_strdup(str.c_str())), length_(str.length()) {}

    // ����������� �����������
    StringLegacy(const StringLegacy& other) : str_(_strdup(other.str_)), length_(other.length_) {}

    // ����������� �����������
    StringLegacy(StringLegacy&& other) noexcept : str_(other.str_), length_(other.length_) {
        other.str_ = nullptr;
        other.length_ = 0; }

    // ����������
    ~StringLegacy() { delete[] str_; }

    // �������� ������������ ������������
    StringLegacy& operator=(const StringLegacy& other) {
        if (this != &other) {
            delete[] str_;
            str_ = _strdup(other.str_);
            length_ = other.length_; }
        return *this; }

    StringLegacy& operator=(const string& str) {
        delete[] str_;
        str_ = _strdup(str.c_str());
        length_ = str.length();
        return *this; }

    // �������� ������������ ������������
    StringLegacy& operator=(StringLegacy&& other) noexcept {
        if (this != &other) {
            delete[] str_;
            str_ = other.str_;
            length_ = other.length_;
            other.str_ = nullptr;
            other.length_ = 0; }
        return *this; }

    // ������ � ��������� ������ �� �������
    char& operator[](size_t index) {
        if (index >= length_) {
            throw out_of_range("������ ��� ���������"); }
        return str_[index]; }

    // ������ � ����� ������
    size_t length() const { return length_; }

    // �������� �� ������� ������
    bool empty() const { return length_ == 0; }

    // ������� ������
    void clear() {
        free(str_);
        str_ = nullptr;
        length_ = 0; }

    // ��������� ����������� �� ��������� ������� �������,
    // �� ����, � ���������� �������, �� �� �����
    
 // 1. ��������� � StringLegacy " > "
    bool operator>(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] > s.str_[i]) { return true; }
            else if (str_[i] < s.str_[i]) { return false; }
            i++; }
        return length_ > s.length_; }

    //��������� � char*
    bool operator>(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ > strlen(s); }

    //��������� � char*
    bool operator>(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ > strlen(s); }

    //Friend-������� ��� ��������� � char* � StringLegacy
    friend bool operator>(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++;  }
        return strlen(str) > s.length_; }

    //Friend-������� ��� ��������� � string � StringLegacy
    friend bool operator>(const string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++; }
        return str.length() > s.length_; }

    //��������� � string
    bool operator>(const string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ > s.length(); }
    
 // 2. ��������� � StringLegacy " < "
    bool operator<(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] < s.str_[i]) { return true; }
            else if (str_[i] > s.str_[i]) { return false; }
            i++; }
        return length_ < s.length_; }

    //��������� � char*
    bool operator<(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ < strlen(s); }

    bool operator<(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ < strlen(s); }

    //Friend-������� ��� ��������� � char* � StringLegacy
    friend bool operator<(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return strlen(str) < s.length_; }

    //Friend-������� ��� ��������� � string � StringLegacy
    friend bool operator<(const std::string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return str.length() < s.length_; }

    //��������� � string
    bool operator<(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ < s.length(); }
   
 // 3. ��������� � StringLegacy " == "
    bool operator==(const StringLegacy& s) const {
        if (length_ != s.length_) { return false; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s.str_[i]) { return false; }
        }
        return true; }

    //��������� � char*
    bool operator==(char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return false; }
            i++; }
        return str_[i] == '\0' && s[i] == '\0'; }

    //��������� � char*
    bool operator==(const char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return false; }
            i++; }
        return str_[i] == '\0' && s[i] == '\0'; }

    //Friend-������� ��� ��������� � char* � StringLegacy
    friend bool operator==(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && s.str_[i] != '\0') {
            if (str[i] != s.str_[i]) { return false; }
            i++; }
        return str[i] == '\0' && s.str_[i] == '\0'; }

    //Friend-������� ��� ��������� � string � StringLegacy
    friend bool operator==(const std::string& str, const StringLegacy& s) {
        if (str.length() != s.length_) { return false; }
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != s.str_[i]) { return false; }
        }
        return true; }

    //��������� � string
    bool operator==(const std::string& s) const {
        if (length_ != s.length()) { return false; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s[i]) { return false; }
        }
        return true; }

// 4. ��������� � StringLegacy " != "
    bool operator!=(const StringLegacy& s) const {
        if (length_ != s.length_) { return true; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s.str_[i]) { return true; }
        }
        return false; }

    //��������� � char*
    bool operator!=(char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return true; }
            i++; }
        return !(str_[i] == '\0' && s[i] == '\0'); }

    //��������� � char*
    bool operator!=(const char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return true; }
            i++; }
        return !(str_[i] == '\0' && s[i] == '\0'); }

    //Friend-������� ��� ��������� � char* � StringLegacy
    friend bool operator!=(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && s.str_[i] != '\0') {
            if (str[i] != s.str_[i]) { return true; }
            i++; }
        return !(str[i] == '\0' && s.str_[i] == '\0'); }

    //Friend-������� ��� ��������� � string � StringLegacy
    friend bool operator!=(const std::string& str, const StringLegacy& s) {
        if (str.length() != s.length_) { return true; }
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != s.str_[i]) { return true; }
        }
        return false; }

    //��������� � string
    bool operator!=(const std::string& s) const {
        if (length_ != s.length()) { return true; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s[i]) { return true; }
        }
        return false; }

// 5. ��������� � StringLegacy " <= "
    bool operator<=(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] < s.str_[i]) { return true; }
            else if (str_[i] > s.str_[i]) { return false; }
            i++; }
        return length_ <= s.length_; }

    //��������� � char*
    bool operator<=(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ <= strlen(s); }

    //��������� � char*
    bool operator<=(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ <= strlen(s); }

    //Friend-������� ��� ��������� � char* � StringLegacy
    friend bool operator<=(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return strlen(str) <= s.length_; }

    //Friend-������� ��� ��������� � string � StringLegacy
    friend bool operator<=(const std::string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return str.length() <= s.length_; }

    //��������� � string
    bool operator<=(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ <= s.length(); }

 // 6. ��������� � StringLegacy " >= "
    bool operator>=(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] > s.str_[i]) { return true; }
            else if (str_[i] < s.str_[i]) { return false; }
            i++; }
        return length_ >= s.length_; }

    //��������� � char*
    bool operator>=(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ >= strlen(s); }

    //��������� � char*
    bool operator>=(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ >= strlen(s); }

    //Friend-������� ��� ��������� � char* � StringLegacy
    friend bool operator>=(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++; }
        return strlen(str) >= s.length_; }

    //Friend-������� ��� ��������� � string � StringLegacy
    friend bool operator>=(const std::string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++; }
        return str.length() >= s.length_; }

    //��������� � string
    bool operator>=(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ >= s.length(); }

 // 7. ������������ � StringLegacy " + "
    StringLegacy operator+(const StringLegacy& s) const {
        StringLegacy result;
        result.length_ = length_ + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s.str_, s.length_, result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }

    //������������ � char*
    StringLegacy operator+(char* s) const {
        StringLegacy result;
        result.length_ = length_ + strlen(s);
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s, strlen(s), result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }

    //Friend-������� ������������ char* �  StringLegacy
    friend StringLegacy operator+(char* str, const StringLegacy& s) {
        StringLegacy result;
        result.length_ = strlen(str) + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str, strlen(str), result.str_);
        copy_n(s.str_, s.length_, result.str_ + strlen(str));
        result.str_[result.length_] = '\0';
        return result;
    }

    //Friend-������� ������������ string �  StringLegacy
    friend StringLegacy operator+(const std::string& str, const StringLegacy& s) {
        StringLegacy result;
        result.length_ = str.length() + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str.c_str(), str.length(), result.str_);
        copy_n(s.str_, s.length_, result.str_ + str.length());
        result.str_[result.length_] = '\0';
        return result;
    }

    //������������ � string
    StringLegacy operator+(const std::string& s) const {
        StringLegacy result;
        result.length_ = length_ + s.length();
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s.c_str(), s.length(), result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }
    
 // 8. ������� ������, �������, ��������, ��������������
    // ������� ������ ���������� ��������� �������.
    // ���������� ����� ������ +1, ���� �� ������ ������
    size_t seek_last(char ch) const {
        for (size_t i = length_ - 1; i >= 1; i--) {
            if (str_[i] == ch) { return i; }
        }
        return length_ + 1; }

    // ������� ������� ������ � �������
    void insert(size_t pos, const char* str) {
        size_t str_len = strlen(str);
        size_t new_length = length_ + str_len;

        char* new_str = new char[new_length + 1];
        copy_n(str_, pos, new_str);
        copy_n(str, str_len, new_str + pos);
        copy_n(str_ + pos, length_ - pos, new_str + pos + str_len);
        new_str[new_length] = '\0';

        delete[] str_;
        str_ = new_str;
        length_ = new_length; }

    // ������� ������� ������ � ������� (StringLegacy)
    void insert(size_t pos, const StringLegacy& str) {
        insert(pos, str.str_); }

    // ������� ������� ������ � ������� (std::string)
    void insert(size_t pos, const std::string& str) {
        insert(pos, str.c_str()); }

    // ������� �������� count �������� �� �������
    void erase(size_t index, size_t count) {
        if (index >= length_ || count == 0) { return; }

        size_t new_length = length_ - count;
        char* new_str = new char[new_length + 1];

        copy_n(str_, index, new_str);
        copy_n(str_ + index + count, new_length - index, new_str + index);
        new_str[new_length] = '\0';

        delete[] str_;
        str_ = new_str;
        length_ = new_length; }

    // �������� �������������� � char*
    operator char* () const { return str_; }
  
    // �������� �������������� � std::string
    operator std::string() const { return std::string(str_); }

    // �������� ������ ��������� ���. ���� �� ������, ���������� ����� + 1
    size_t kmp_search(const StringLegacy& pattern) const {
        // �������� ������� ���������
        size_t* prefix_table = build_prefix_table(pattern);
        // ������������� ��������
        size_t i = 0; // ������ ������
        size_t j = 0; // ������ �������
        // ����� ������� � ������
        while (i < length_ && j < pattern.length_) {
            if (str_[i] == pattern.str_[j]) { i++; j++; }
            else {
                // ���� ������� �� ���������, �������� ������ �������
                // �� ������ ������� ���������
                if (j > 0) { j = prefix_table[j - 1]; }
                else { i++; }
            }
        }
        // ������������ ������
        delete[] prefix_table;
        // ������� ������� ������ �������, ���� �� ������
        if (j == pattern.length_) { return i - j; }
        else { return length_ + 1; }
    }

    // ���������������� ����� ��������� � ��������� ������� � ���������� ��������. ���� �� ������, ���������� ����� + 1
    size_t search(const StringLegacy& pattern) const {
        size_t text_len = length_;
        size_t pattern_len = pattern.length_;
        // �������� �� ������
        for (size_t i = 0; i <= text_len - pattern_len; i++) {
            // �������� ������� ��������
            if (str_[i] != pattern.str_[0]) { continue; }
            // �������� ���������� ��������
            if (str_[i + pattern_len - 1] != pattern.str_[pattern_len - 1]) { continue; }
            // ������ �������� �������
            size_t j = 0;
            while (j < pattern_len && str_[i + j] == pattern.str_[j]) { j++; }
            // ��������, ������ �� �������
            if (j == pattern_len) { return i; }
        }
        // ������� �� ������
        return length_ + 1; }

    // ���������, ������� ���������� ������ ��������� �������� �������� ������������������
    static StringLegacy generate_random_string(size_t length, const std::string& charset) {
        StringLegacy random_string(length);
        for (size_t i = 0; i < length; i++) {
            random_string.str_[i] = charset[rand() % charset.length()];
        }
        return random_string; }

    // ���������, ������� ������ ������ �� ���������� �����
    static vector<StringLegacy> read_lines_from_file(const string& filename) {
        ifstream file(filename);
        vector<StringLegacy> lines;
        if (file.is_open()) { string line;
           while (getline(file, line)) {
             lines.push_back(StringLegacy(line));
           }
           file.close();
        }
        else { cerr << "Error opening file: " << filename << endl; }
        return lines; }
};
