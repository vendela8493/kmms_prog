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
    
    if (sign == x.sign) {
        int max_len = (length > x.length) ? length : x.length;
        res = LongNumber(max_len + 1, sign);
        
        for (int i = 0; i < res.length; i++) {
            res.numbers[i] = 0;
        }
        
        for (int i = 0; i < max_len; i++) {
            if (i < length) res.numbers[i] += numbers[i];
            if (i < x.length) res.numbers[i] += x.numbers[i];
        }
        
        for (int i = 0; i < res.length - 1; i++) {
            if (res.numbers[i] >= 10) {
                res.numbers[i + 1] += res.numbers[i] / 10;
                res.numbers[i] %= 10;
            }
        }
        
        while (res.length > 1 && res.numbers[res.length - 1] == 0) {
            res.length--;
        }
    }
    else {
        LongNumber abs_this = *this;
        LongNumber abs_x = x;
        abs_this.sign = 1;
        abs_x.sign = 1;
        
        if (abs_this == abs_x) {
            return LongNumber("0");
        }
        else if (abs_this > abs_x) {
            res = abs_this - abs_x; 
            res.sign = sign;
        }
        else {
            res = abs_x - abs_this;
            res.sign = x.sign; 
        }
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
	LongNumber result(length + x.length, sign * x.sign);
	for (int i = 0; i < result.length; i++) {
        result.numbers[i] = 0;
    }
    
    for (int i = 0; i < length; i++) {
        int carry = 0;
        for (int j = 0; j < x.length; j++) {
            int product = numbers[i] * x.numbers[j] + result.numbers[i + j] + carry;
            result.numbers[i + j] = product % 10;
            carry = product / 10;
        }
        if (carry > 0) {
            result.numbers[i + x.length] += carry;
        }
    }
    
    for (int i = 0; i < result.length - 1; i++) {
        if (result.numbers[i] >= 10) {
            result.numbers[i + 1] += result.numbers[i] / 10;
            result.numbers[i] = result.numbers[i] % 10;
        }
    }
    
    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }
    
    if (result.length == 1 && result.numbers[0] == 0) {
        result.sign = 1;
    }
    
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
  if (x.length == 1 && x.numbers[0] == 0) {
        return LongNumber("0");
    }
    
    LongNumber res;
    LongNumber abs_x = x;
    LongNumber dividend = *this;
    
    abs_x.sign = 1;
    dividend.sign = 1;
    
    if (dividend < abs_x) {
        return LongNumber("0");  
    }
    
    res = LongNumber(length - x.length + 1, sign * x.sign);
    
    for (int i = 0; i < res.length; i++) {
        res.numbers[i] = 0;
    }
    
    for (int i = 0; i < res.length; i++) {
        LongNumber divisor(length - i, 1);
        
        for (int j = 0; j < divisor.length; j++) {
            divisor.numbers[j] = 0;
        }
        
        for (int j = 0; j < x.length; j++) {
            int pos = length - x.length - i + j;
            if (pos >= 0 && pos < divisor.length) {
                divisor.numbers[pos] = x.numbers[j];
            }
        }
        
        while (divisor.length > 1 && divisor.numbers[divisor.length - 1] == 0) {
            divisor.length--;
        }
        
        int counter = 0;
        while (dividend > divisor || dividend == divisor) {
            counter++;
            
            for (int j = 0; j < divisor.length; j++) {
                dividend.numbers[j] -= divisor.numbers[j];
            }
            
            for (int j = 0; j < dividend.length - 1; j++) {
                if (dividend.numbers[j] < 0) {
                    dividend.numbers[j] += 10;
                    dividend.numbers[j + 1]--;
                }
            }
            
            while (dividend.length > 1 && dividend.numbers[dividend.length - 1] == 0) {
                dividend.length--;
            }
        }
        
        res.numbers[res.length - i - 1] = counter;
    }
    
    while (res.length > 1 && res.numbers[res.length - 1] == 0) {
        res.length--;
    }
	if (res.sign == -1 and dividend > 0) {
		LongNumber one(1, 1);
		res = res - one;
	}
    
    return res;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
  if (x.length == 1 && x.numbers[0] == 0) {
        return LongNumber("0");
    }
    
    LongNumber abs_this = *this;
    LongNumber abs_x = x;
    
    abs_this.sign = 1;
    abs_x.sign = 1;
    
    LongNumber quotient = abs_this / abs_x; 
    
    LongNumber product = quotient * abs_x;
    
    LongNumber remainder = abs_this - product;
    
    if (this->sign == -1 && !(remainder.length == 1 && remainder.numbers[0] == 0)) {
        remainder.sign = -1;
    }
    
    return remainder;
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