#include "long_number.hpp"

using rva::LongNumber;
    
//конструктор по умолчанию
LongNumber::LongNumber() {
  length = 1;
  sign = 1;
  numbers = new int[length];
  numbers[0] = 0;
}

//конструктор с параметрами
LongNumber::LongNumber(int length, int sign) {
  this->length = length;
  this->sign = sign;
  numbers = new int[length];
  numbers[0] = 0;
}

//конструктор от строки
LongNumber::LongNumber(const char* const str) {
    int total_len = get_length(str);
    
    int start = 0;
    sign = 1;
    
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }
    
    while (start < total_len && str[start] == '0') {
        start++;
    }
    
    if (start == total_len) {
        length = 1;
        numbers = new int[1];
        numbers[0] = 0;
        sign = 1;
        return;
    }
    
    length = total_len - start;
    
    numbers = new int[length];
    
    for (int i = 0; i < length; i++) {
        char digit_char = str[total_len - 1 - i];
        numbers[i] = digit_char - '0';
    }
}

//конструктор копирования
LongNumber::LongNumber(const LongNumber& x) {
  length = x.length;
  sign = x.sign;
  numbers = new int[length];
  for (int i = 0; i<length; i++) {
    numbers[i] = x.numbers[i];
  }
}

//конструктор перемещения
LongNumber::LongNumber(LongNumber&& x) {
  length = x.length;
  sign = x.sign;
  numbers = x.numbers;
  x.numbers = nullptr;
  x.length = 0;
  x.sign = 1;
}

//деструктор
LongNumber::~LongNumber() {
  delete[] numbers;
}

//оператор присваивания от строки
LongNumber& LongNumber::operator = (const char* const str) {
    int str_length = get_length(str);
    
    int start = 0;
    int new_sign = 1;
    
    if (str[0] == '-') {
        new_sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }
    
    while (start < str_length && str[start] == '0') {
        start++;
    }
    
  delete[] numbers;

    if (start == str_length) {
        length = 1;
        numbers = new int[1];
        numbers[0] = 0;
        sign = 1;
        return *this;
    }
    
    int new_length = str_length - start;
    
    numbers = new int[new_length];
    length = new_length;
    sign = new_sign;
    
    for (int i = 0; i < length; i++) {
        numbers[i] = str[str_length - 1 - i] - '0';
    }
    
    return *this;
}

//оператор копирования
LongNumber& LongNumber::operator = (const LongNumber& x) {
    if (this == &x) {
        return *this;
    }
    
    delete[] numbers;
    
    length = x.length;
    sign = x.sign;
    numbers = new int[length];
    
    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }
    
    return *this;
}

//оператор присваивания перемещением
LongNumber& LongNumber::operator = (LongNumber&& x) {
    if (this == &x) {
        return *this;
    }
    
    delete[] numbers;
    
    length = x.length;
    sign = x.sign;
    numbers = x.numbers;
    
    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;
    
    return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
  if (length == 1 && numbers[0] == 0 &&
    x.length == 1 && x.numbers[0] == 0) {
      return true;
    }
  
  if (sign != x.sign) return false;
  if (length != x.length) return false;

  for (int i = 0; i < length; i++) {
    if (numbers[i] != x.numbers[i]) return false;
  }
  return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
  return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
  if (sign > x.sign) {
    return true;
  } else if (sign < x.sign) {
    return false;
  } else if (sign == 0) return false;

  if (length > x.length) {
    return (sign > 0);
  } else if (length < x.length) {
    return (sign < 0);
  } else {
    for (int i = length - 1; i >= 0; i--) {
          if (numbers[i] > x.numbers[i]) return (sign > 0);
          if (numbers[i] < x.numbers[i]) return (sign < 0);
        }
  }
  return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
  return x > *this;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
  LongNumber res;
  LongNumber min;
  LongNumber max;
  if (sign == x.sign) {
    if (*this > x) {
      res = LongNumber(length + 1, sign);
      min = x;
      max = *this;
    } else {
      res = LongNumber(x.length + 1, sign);
      min = *this;
      max = x;
    }
    
    for (int i = 0; i < min.length; i++)
      res.numbers[i] = min.numbers[i] + max.numbers[i];
    
    for (int i = min.length; i < max.length; i++)
      res.numbers[i] = max.numbers[i];
    
    for (int i = 0; i < res.length - 1; i++) {
      if (res.numbers[i] > 9) {
        res.numbers[i] -= 10;
        res.numbers[i+1]++;
      }
    }
    
    if (res.numbers[res.length - 1] == 0)
      res.length--;
  } else {
    LongNumber abs_x = x;
    LongNumber dividend = *this;
    
    abs_x.sign = 1;
    dividend.sign = 1;
    
    if (dividend > abs_x) {
      res = LongNumber(length + 1, sign);
      min = x;
      max = *this;
    } else {
      res = LongNumber(x.length + 1, x.sign);
      min = *this;
      max = x;
    }
    
    for (int i = 0; i < max.length; i++)
      res.numbers[i] = max.numbers[i];
    
    for (int i = 0; i < min.length; i++)
      res.numbers[i] = res.numbers[i] - min.numbers[i];
    
    for (int i = 0; i < res.length - 1; i++) {
      if (res.numbers[i] < 0) {
        res.numbers[i] += 10;
        res.numbers[i+1]--;
      }
    }
    
    while (res.length > 1 and res.numbers[res.length - 1] == 0)
      res.length--;
    
    if (res.length == 1 and res.numbers[0] == 0)
      res.sign = 1;
  }
  
  return res;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
  LongNumber res;
  res = x;
  res.sign = -res.sign;
  
  res = *this + res;
  
  return res;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
  LongNumber res;
  res = LongNumber(length + x.length, sign * x.sign);
  for (int i = 0; i < x.length; i++) {
    for (int j = 0; j < length; j++) {
      res.numbers[i+j] += x.numbers[i] * numbers[j];
      if (res.numbers[i+j] > 9) {
        int r = res.numbers[i+j]/10;
        res.numbers[i+j+1] += r;
        res.numbers[i+j] -= r*10;
      }
    }
  }
  while (res.length > 1 and res.numbers[res.length - 1] == 0)
    res.length--;
  return res;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
  LongNumber res;
  LongNumber abs_x = x;
  LongNumber dividend = *this;
  
  abs_x.sign = 1;
  dividend.sign = 1;
  
  if (dividend < abs_x)
    return res;
  else {
    res = LongNumber(length - x.length + 1, sign * x.sign);
    
    for (int i = 0; i < res.length; i++) {
      LongNumber divisor = LongNumber(length - i, 1);
      
      for (int j = 0; j < x.length; j++)
        divisor.numbers[length - x.length - i + j] = x.numbers[j];
      
      int counter = 0;
      while (dividend > divisor or dividend == divisor) {
        counter++;
        dividend = dividend - divisor;
      }
      res.numbers[res.length - i - 1] = counter;
    }
  }
  
  while (res.length > 1 and res.numbers[res.length - 1] == 0)
    res.length--;
  
  return res;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
  LongNumber res;
  LongNumber abs_x = x;
  LongNumber dividend = *this;
  
  abs_x.sign = 1;
  dividend.sign = 1;
  
  res = dividend - (dividend / abs_x) * abs_x;
  
  if (is_negative())
    res.sign = -1;
  
  return res;
}

bool LongNumber::is_negative() const noexcept {
  return (sign == -1);
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
  if (str == nullptr) return 0;
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace rva {
  std::ostream& operator << (std::ostream &os, const LongNumber& x) {
    if (x.sign == -1) os << '-';
    for (int i = x.length - 1; i >= 0; i--) {
      os << x.numbers[i];
    }
    return os;
  }
}
