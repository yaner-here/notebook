/**
 * https://github.com/mrdcvlsc/APA
 * 本代码过长，难以在洛谷上提交
 * 运算符全部齐全
 */

#include<bits/stdc++.h>

namespace apa {
    #define LPOS_RNEG(SIGN_A, SIGN_B) (SIGN_A < SIGN_B)
    #define LNEG_RPOS(SIGN_A, SIGN_B) (SIGN_A > SIGN_B)
    #define SIGN_POSITIVE(SIGN) (!SIGN)
    #define SIGN_NEGATIVE(SIGN) (SIGN)
    #define CMP_RES_FLIP(CMP_RESULT) (-CMP_RESULT)
    static const size_t KARATSUBA_SIZE = 62;
    const unsigned char HEX_TO_CHAR[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    const unsigned char CHAR_TO_HEX[127] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xff, 0xff, 0xff,
        0xff, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    constexpr static size_t BIN = 2, OCT = 8, DEC = 10, HEX = 16, EMPTY = 1, INVALID = 20;
    typedef std::vector<uint8_t> byte_array;
    constexpr static int LESS = -1, EQUAL = 0, GREAT = 1, BITS_PER_BYTE = 8;
    constexpr static size_t BASE_BITS = (sizeof(uint32_t) * 8), BASE_BITS_MINUS1 = BASE_BITS - 1, BASE_BYTES = BASE_BITS / 8, LIMB_BITS = BASE_BITS, LIMB_BYTES = BASE_BYTES, CAST_BITS = BASE_BITS * 2, CAST_BYTES = BASE_BYTES * 2, INITIAL_LIMB_CAPACITY = 2, INITIAL_LIMB_LENGTH = 1, LIMB_GROWTH = 2;
    constexpr static uint32_t BASE_MAX = std::numeric_limits<uint32_t>::max();
    struct integer {
        size_t capacity;
        size_t length;
        uint32_t *limbs;
        integer() noexcept;
        integer(size_t num) noexcept;
        integer(const std::string &text, size_t base = 10);
        integer(std::initializer_list<uint32_t> limbs);
        integer(size_t capacity, size_t length, bool AllocateSpace = true);
        integer(uint32_t *arr, size_t capacity, size_t length) noexcept;
        integer(const integer &src);     
        integer(integer &&src) noexcept; 
        integer &operator=(const integer &src);     
        integer &operator=(integer &&src) noexcept; 
        ~integer();
        uint32_t &operator[](size_t i) noexcept;
        uint32_t &operator[](size_t i) const noexcept;
        int compare(const integer &with) const noexcept;
        bool operator<(const integer &op) const noexcept;
        bool operator>(const integer &op) const noexcept;
        bool operator==(const integer &op) const noexcept;
        bool operator!=(const integer &op) const noexcept;
        bool operator<=(const integer &op) const noexcept;
        bool operator>=(const integer &op) const noexcept;
        integer &operator&=(const integer &op) noexcept;
        integer &operator|=(const integer &op) noexcept;
        integer &operator^=(const integer &op) noexcept;
        integer operator&(const integer &op) const noexcept;
        integer operator|(const integer &op) const noexcept;
        integer operator^(const integer &op) const noexcept;
        integer operator~() const noexcept;
        void bit_realloc(const integer &op) noexcept;
        void remove_leading_zeros() noexcept ;
        void bit_flip(size_t padding = 0) noexcept;
        void bit_and(const integer &op) noexcept;
        void bit_or(const integer &op) noexcept;
        void bit_xor(const integer &op) noexcept;
        explicit operator bool() const noexcept;
        integer bit_division(const integer &op) const;
        integer &bit_division_assign(const integer &op);
        integer bit_modulo(const integer &op) const;
        integer &bit_modulo_assign(const integer &op);
        static void div_mod(integer& q, integer& r, integer& dividen, const integer& divisor);
        integer &operator+=(const integer &op) noexcept;
        integer &operator-=(const integer &op) noexcept;
        integer &operator*=(const integer &op) noexcept;
        integer &operator/=(const integer &op);
        integer &operator%=(const integer &op);
        integer operator+(const integer &op) const noexcept;
        integer operator-(const integer &op) const noexcept;
        integer operator*(const integer &op) const noexcept;
        integer operator/(const integer &op) const;
        integer operator%(const integer &op) const;
        integer &operator++() noexcept;
        integer &operator--() noexcept;
        integer operator++(int) noexcept;
        integer operator--(int) noexcept;
        integer &operator<<=(size_t bits) noexcept;
        integer &operator>>=(size_t bits) noexcept;
        integer operator<<(size_t bits) const noexcept;
        integer operator>>(size_t bits) const noexcept;
        void printHex() const;
        void printHex_spaced_out() const;
        void printBin_spaced_out() const;
        void printStatus(std::string printIdentifier = "default") const;
        std::string to_base10_string() const;
        std::string to_base16_string() const;
        size_t byte_size() const noexcept;
        size_t bit_size() const noexcept;
        uint32_t *detach();
    };
    void swap(integer &a, integer &b);
    std::ostream &operator<<(std::ostream &out, const integer &num);
    std::istream &operator>>(std::istream &in, integer &num);
    template <typename T1, typename T2>
    struct get_initial_capacity {
        private:
        static constexpr size_t partitions = sizeof(T1) / sizeof(T2);
        public:
        static constexpr size_t value = partitions ? partitions : 1;
    };
    integer::integer() noexcept: capacity(INITIAL_LIMB_CAPACITY), length(INITIAL_LIMB_LENGTH), limbs((uint32_t *) std::malloc(INITIAL_LIMB_CAPACITY * LIMB_BYTES)){}
    integer::integer(size_t num) noexcept: capacity(get_initial_capacity<size_t, uint32_t>::value), length(capacity), limbs((uint32_t *) std::calloc(capacity, sizeof(uint32_t))){
        std::memcpy(limbs, &num, sizeof(num));
        remove_leading_zeros();
    }
    integer::integer(size_t capacity, size_t length, bool AllocateSpace): capacity(capacity), length(length){
        if (AllocateSpace) {
            limbs = (uint32_t *) std::malloc(capacity * LIMB_BYTES);
        } else {
            limbs = NULL;
        }
    }
    integer::integer(const std::string &text, size_t base) {
        std::vector<uint8_t> output(text.size(), 0);
        std::string newText;
        if (base > 1 && base < HEX) {
            for (size_t i = 0; i < text.size(); ++i) {
                uint8_t carry = text[i] - '0';
                size_t j = text.size();
                while (j--) {
                    uint8_t tmp = output[j] * base + carry;
                    output[j] = tmp % 16;
                    carry = tmp / 16;
                }
            }
            size_t leading_zeros = 0;
            while (output.size() > 1 && !output[leading_zeros]) {
                leading_zeros++;
            }
            output.erase(output.begin(), output.begin() + leading_zeros);
            std::string stringForm(output.size(), '0');
            for (size_t i = 0; i < stringForm.size(); ++i) {
                stringForm[i] = HEX_TO_CHAR[output[i]];
            }
            newText = stringForm;
        } else if (base != HEX) {
            throw std::domain_error(
                "integer - string contructor : supported number "
                "base range is only from 2 to 16"
            );
        } else {
            newText = text;
        }
        size_t blocks = newText.size() / (CAST_BYTES);
        size_t remain = newText.size() % (CAST_BYTES);
        length = blocks;
        length += !!remain;
        capacity = length + LIMB_GROWTH;
        limbs = (uint32_t *) std::calloc(capacity, sizeof(uint32_t));
        for (size_t i = 0; i < newText.size(); ++i) {
            unsigned char CharByte = CHAR_TO_HEX[(unsigned char) newText[newText.size() - 1 - i]];
            if (CharByte == 0xff)
                break;
            size_t multiplier = std::pow(0x10, i % CAST_BYTES);
            limbs[i / CAST_BYTES] |= CharByte * multiplier;
        }
        remove_leading_zeros();
    }
    integer::integer(uint32_t *arr, size_t capacity, size_t length) noexcept: capacity(capacity), length(length), limbs(arr){}
    integer::integer(const integer &src): capacity(src.capacity), length(src.length), limbs((uint32_t *) std::malloc(capacity * LIMB_BYTES)){
        std::memcpy(limbs, src.limbs, length * LIMB_BYTES);
    }
    integer::integer(integer &&src) noexcept: capacity(src.capacity), length(src.length), limbs(src.limbs){
        src.limbs = NULL;
    }
    integer &integer::operator=(const integer &src) {
        if (this != &src) {
            if (capacity <= src.length) {
                limbs = (uint32_t *) std::realloc(limbs, src.capacity * LIMB_BYTES);
                capacity = src.capacity;
            }
            length = src.length;
            std::memcpy(limbs, src.limbs, src.length * LIMB_BYTES);
        }
        return *this;
    }
    integer &integer::operator=(integer &&src) noexcept {
        if (this != &src) {
            std::free(limbs); capacity = src.capacity; length = src.length; limbs = src.limbs; src.limbs = NULL;
        }
        return *this;
    }
    integer::integer(std::initializer_list<uint32_t> limbs): capacity(limbs.size() + LIMB_GROWTH), length(limbs.size()), limbs((uint32_t *) std::malloc(capacity * LIMB_BYTES)){
        size_t i = 0;
        for (auto limb: limbs) {
            this->limbs[length - 1 - i++] = limb;
        }
    }
    integer::~integer() { std::free(limbs); capacity = 0; length = 0; }
    uint32_t &integer::operator[](size_t i) noexcept { return limbs[i]; }
    uint32_t &integer::operator[](size_t i) const noexcept { return limbs[i]; }
    int integer::compare(const integer &op) const noexcept {
        if (length < op.length) {
            return LESS;
        } else if (length > op.length) {
            return GREAT;
        }
        for (size_t i = 0; i < length; ++i) {
            if (limbs[length - 1 - i] < op.limbs[length - 1 - i]) {
                return LESS;
            } else if (limbs[length - 1 - i] > op.limbs[length - 1 - i]) {
                return GREAT;
            }
        }
        return EQUAL;
    }
    bool integer::operator<(const integer &op) const noexcept { return compare(op) == LESS; }
    bool integer::operator>(const integer &op) const noexcept { return compare(op) == GREAT; }
    bool integer::operator==(const integer &op) const noexcept { return compare(op) == EQUAL; }
    bool integer::operator!=(const integer &op) const noexcept { return (*this == op) ^ 1u; }
    bool integer::operator<=(const integer &op) const noexcept { return compare(op) <= EQUAL; }
    bool integer::operator>=(const integer &op) const noexcept { return compare(op) >= EQUAL; }
    void integer::bit_realloc(const integer &op) noexcept {
        size_t zero_set = length * LIMB_BYTES;
        capacity = op.capacity;
        limbs = (uint32_t *) std::realloc(limbs, capacity * LIMB_BYTES);
        std::memset(limbs + length, 0x00, (op.length * LIMB_BYTES) - zero_set);
        length = op.length;
    }
    void integer::remove_leading_zeros() noexcept {
        for (size_t i = 0; i < length; ++i) {
            if (limbs[length - 1 - i]) {
                length -= i;
                return;
            }
        }
        length = 1;
    }
    void integer::bit_and(const integer &op) noexcept {
        for (size_t i = 0; i < op.length; ++i) {
            limbs[i] &= op.limbs[i];
        }
        for (size_t i = op.length; i < length; ++i) {
            limbs[i] &= 0;
        }
    }
    integer &integer::operator&=(const integer &op) noexcept {
        if (length < op.length) {
            bit_realloc(op);
        }
        bit_and(op);
        remove_leading_zeros();
        return *this;
    }
    integer integer::operator&(const integer &op) const noexcept {
        integer bitwise_and = *this;
        return bitwise_and &= op;
    }
    void integer::bit_or(const integer &op) noexcept {
        for (size_t i = 0; i < op.length; ++i) {
            limbs[i] |= op.limbs[i];
        }
        for (size_t i = op.length; i < length; ++i) {
            limbs[i] |= 0;
        }
    }
    integer &integer::operator|=(const integer &op) noexcept {
        if (length < op.length) {
            bit_realloc(op);
        }
        bit_or(op);
        remove_leading_zeros();
        return *this;
    }
    integer integer::operator|(const integer &op) const noexcept {
        integer bitwise_and = *this;
        return bitwise_and |= op;
    }
    void integer::bit_xor(const integer &op) noexcept {
        for (size_t i = 0; i < op.length; ++i) {
            limbs[i] ^= op.limbs[i];
        }
        for (size_t i = op.length; i < length; ++i) {
            limbs[i] ^= 0;
        }
    }
    integer &integer::operator^=(const integer &op) noexcept {
        if (length < op.length) {
            bit_realloc(op);
        }
        bit_xor(op);
        remove_leading_zeros();
        return *this;
    }
    integer integer::operator^(const integer &op) const noexcept {
        integer bitwise_and = *this;
        bitwise_and ^= op;
        return bitwise_and;
    }
    integer integer::operator~() const noexcept {
        integer bwn(length, length);
        for (size_t i = 0; i < length - 1; ++i) {
            bwn.limbs[i] = (~limbs[i]);
        }
        uint32_t mslimb = limbs[length - 1];
        uint32_t bitmask = mslimb | (mslimb >> 1);
        for (size_t i = 2; i < BASE_BITS; i *= 2) {
            bitmask |= bitmask >> i;
        }
        bwn.limbs[bwn.length - 1] = bitmask ^ mslimb;
        bwn.remove_leading_zeros();
        return bwn;
    }
    void integer::bit_flip(size_t padding) noexcept {
        size_t prev_length = length;
        length += padding;
        if (capacity < length + padding) {
            capacity = length + padding + LIMB_GROWTH;
            limbs = (uint32_t *) std::realloc(limbs, capacity * LIMB_BYTES);
        }
        for (size_t i = 0; i < prev_length; ++i) {
            limbs[i] = (~limbs[i]);
        }
        for (size_t i = prev_length; i < length; ++i) {
            limbs[i] = BASE_MAX;
        }
    }
    integer::operator bool() const noexcept {
        return (length == 1 && !limbs[0]) ^ 1u;
    }
    integer &integer::operator+=(const integer &op) noexcept {
        if (capacity <= op.length + 1) {
            capacity = op.length + LIMB_GROWTH;
            limbs = (uint32_t *) std::realloc(limbs, capacity * LIMB_BYTES);
        }
        if (length == capacity) {
            capacity = length + LIMB_GROWTH;
            limbs = (uint32_t *) std::realloc(limbs, capacity * LIMB_BYTES);
            limbs[length++] = 0;
        }
        if (length <= op.length) {
            std::memset(limbs + length, 0x00, ((op.length + 1) - length) * LIMB_BYTES);
            length = op.length + 1;
        }
        uint32_t carry = 0;
        for (size_t i = 0; i < op.length; ++i) {
            uint64_t sum = (uint64_t) limbs[i] + op.limbs[i] + carry;
            limbs[i] = sum;
            carry = sum >> BASE_BITS;
        }
        for (size_t i = op.length; i < length; ++i) {
            uint64_t sum = (uint64_t) limbs[i] + carry;
            limbs[i] = sum;
            carry = sum >> BASE_BITS;
        }
        remove_leading_zeros();
        return *this;
    }
    integer integer::operator+(const integer &op) const noexcept {
        uint32_t *max_limb, *min_limb;
        size_t max_len, min_len;
        if (length > op.length) { max_limb = limbs; max_len = length; min_limb = op.limbs; min_len = op.length;} 
        else { max_limb = op.limbs; max_len = op.length; min_limb = limbs; min_len = length; }
        uint32_t *sum_array = (uint32_t *) std::malloc(LIMB_BYTES * (max_len + 1));
        uint32_t carry = 0;
        for (size_t i = 0; i < min_len; ++i) {
            uint64_t sum = (uint64_t) max_limb[i] + min_limb[i] + carry;
            sum_array[i] = sum;
            carry = sum >> BASE_BITS;
        }
        for (size_t i = min_len; i < max_len; ++i) {
            uint64_t sum = (uint64_t) max_limb[i] + carry;
            sum_array[i] = sum;
            carry = sum >> BASE_BITS;
        }
        sum_array[max_len] = carry;
        return integer(sum_array, max_len + 1, max_len + carry);
    }
    integer &integer::operator-=(const integer &op) noexcept {
        uint32_t carry = 0;
        for (size_t i = 0; i < op.length; ++i) {
            uint64_t dif_index = (uint64_t) limbs[i] - op.limbs[i] - carry;
            limbs[i] = dif_index;
            carry = (dif_index >> BASE_BITS);
            carry &= 0x01;
        }
        for (size_t i = op.length; i < length; ++i) {
            uint64_t dif_index = (uint64_t) limbs[i] - carry;
            limbs[i] = dif_index;
            carry = (dif_index >> BASE_BITS);
            carry &= 0x01;
        }
        remove_leading_zeros();
        return *this;
    }
    integer integer::operator-(const integer &op) const noexcept {
        size_t dif_len = std::max(length, op.length);
        uint32_t *dif_array = (uint32_t *) std::malloc(dif_len * LIMB_BYTES);
        uint32_t carry = 0;
        for (size_t i = 0; i < op.length; ++i) {
            uint64_t dif_index = (uint64_t) limbs[i] - op.limbs[i] - carry;
            dif_array[i] = dif_index;
            carry = (dif_index >> BASE_BITS);
            carry &= 0x01;
        }
        for (size_t i = op.length; i < length; ++i) {
            uint64_t dif_index = (uint64_t) limbs[i] - carry;
            dif_array[i] = dif_index;
            carry = (dif_index >> BASE_BITS);
            carry &= 0x01;
        }
        integer dif_int(dif_array, dif_len, dif_len);
        dif_int.remove_leading_zeros();
        return dif_int;
    }
    integer &integer::operator*=(const integer &op) noexcept {
        integer product = *this * op;
        swap(product, *this);
        return *this;
    }
    integer integer::operator*(const integer &op) const noexcept {
        if ((*this && op) ^ 1u) {
            return 0;
        }
        uint32_t *arr = (uint32_t *) std::malloc(LIMB_BYTES * (length + op.length));
        integer product(arr, length + op.length, length + op.length);
        size_t i = 0, j = 0;
        uint32_t carry = 0;
        for (j = 0; j < length; ++j) {
            uint64_t product_index = (uint64_t) limbs[j] * op.limbs[0] + carry;
            product.limbs[j] = product_index;
            carry = (product_index >> BASE_BITS);
        }
        product.limbs[length] = carry;
        for (i = 1; i < op.length; ++i) {
            carry = 0;
            for (j = 0; j < length; ++j) {
                uint64_t product_index = (uint64_t) limbs[j] * op.limbs[i] + product.limbs[i + j] + carry;
                product.limbs[i + j] = product_index;
                carry = (product_index >> BASE_BITS);
            }
            product.limbs[i + length] = carry;
        }
        product.length -= !product.limbs[product.length - 1];
        return product;
    }
    integer &integer::operator/=(const integer &op) {
        if (!op) {
            throw std::domain_error("apa::integer - Division By Zero");
        }
        int special_case = compare(op);
        switch (special_case) {
            case EQUAL:
                length = 1;
                limbs[0] = 1;
                return *this;
            case LESS:
                length = 1;
                limbs[0] = 0;
                return *this;
        }
        if (op.length == 1 && op.limbs[0] == 1) {
            return *this;
        }
        return bit_division_assign(op);
    }
    integer integer::operator/(const integer &op) const {
        if (!op) {
            throw std::domain_error("apa::integer - Division By Zero");
        }
        int special_case = compare(op);
        switch (special_case) {
            case EQUAL:
                return 1;
            case LESS:
                return 0;
        }
        if (op.length == 1 && op.limbs[0] == 1) {
            return *this;
        }
        return bit_division(op);
    }
    integer &integer::operator%=(const integer &op) {
        if (!op) {
            throw std::domain_error("apa::integer - Division By Zero");
        }
        int special_case = compare(op);
        switch (special_case) {
            case EQUAL:
                length = 1;
                limbs[0] = 0;
                return *this;
            case LESS:
                return *this;
        }
        if (op.length == 1 && op.limbs[0] == 1) {
            length = 1;
            limbs[0] = 0;
            return *this;
        }
        return bit_modulo_assign(op);
    }
    integer integer::operator%(const integer &op) const {
        if (!op) {
            throw std::domain_error("apa::integer - Division By Zero");
        }
        int special_case = compare(op);
        switch (special_case) {
            case EQUAL:
                return 0;
            case LESS:
                return *this;
        }
        if (op.length == 1 && op.limbs[0] == 1) {
            return 0;
        }
        return bit_modulo(op);
    }
    void div_n_by_1(uint32_t *quotient, uint32_t *dividen, size_t length, uint32_t divisor) {
        uint64_t remainder = 0;
        remainder = dividen[length - 1] % divisor;
        remainder <<= BASE_BITS;
        quotient[length - 1] = dividen[length - 1] / divisor;
        for (size_t i = 1; i < length; ++i) {
            remainder |= dividen[length - 1 - i];
            quotient[length - 1 - i] = remainder / divisor;
            remainder = (remainder % divisor) << BASE_BITS;
        }
    }
    void div_n_by_m(uint32_t *quotient, const integer& dividen, const integer& divisor) {
        integer remainder(dividen.length, dividen.length);
        remainder.length = 1;
        remainder.limbs[0] = 0;
        uint32_t bit = 0, current_index = dividen.length, onebit = 1;
        size_t total_bits = dividen.length * BASE_BITS;
        for (size_t h = 0; h < total_bits; h += BASE_BITS) {
            remainder <<= BASE_BITS;
            remainder.limbs[0] = dividen.limbs[--current_index];
            quotient[current_index] = 0;
            if (remainder >= divisor) {
                uint32_t r = remainder.limbs[0];
                remainder >>= BASE_BITS;
                for (size_t i = 0; i < BASE_BITS; ++i) {
                    bit = (r << i);
                    bit >>= BASE_BITS_MINUS1;
                    remainder <<= 1;
                    remainder.limbs[0] |= bit;
                    if (remainder >= divisor) {
                        remainder -= divisor;
                        quotient[current_index] |= (onebit << (BASE_BITS_MINUS1 - i));
                    }
                }
            }
        }
    }
    integer integer::bit_division(const integer &op) const {
        uint32_t *arr = (uint32_t *) std::malloc(length * LIMB_BYTES);
        integer quotient(arr, length, length);
        if (op.length == 1) {
            div_n_by_1(quotient.limbs, limbs, length, op.limbs[0]);
        } else {
            div_n_by_m(quotient.limbs, *this, op);
        }
        quotient.remove_leading_zeros();
        return quotient;
    }
    integer &integer::bit_division_assign(const integer &op) {
        if (op.length == 1) {
            div_n_by_1(limbs, limbs, length, op.limbs[0]);
        } else {
            div_n_by_m(limbs, *this, op);
        }
        remove_leading_zeros();
        return *this;
    }
    uint32_t mod_n_by_1(uint32_t *dividen, size_t length, uint32_t divisor) {
        uint64_t remainder = 0;
        remainder = dividen[length - 1] % divisor;
        remainder <<= BASE_BITS;
        for (size_t i = 1; i < length; ++i) {
            remainder |= dividen[length - 1 - i];
            remainder = (remainder % divisor) << BASE_BITS;
        }
        return remainder >> BASE_BITS;
    }
    integer mod_n_by_m(const integer& dividen, const integer& divisor) {
        integer remainder(dividen.length, dividen.length);
        remainder.length = 1;
        remainder.limbs[0] = 0;
        uint32_t bit = 0, current_index = dividen.length;
        size_t total_bits = dividen.length * BASE_BITS;
        for (size_t h = 0; h < total_bits; h += BASE_BITS) {
            remainder <<= BASE_BITS;
            remainder.limbs[0] = dividen.limbs[--current_index];
            if (remainder >= divisor) {
                remainder >>= BASE_BITS;
                for (size_t i = 0; i < BASE_BITS; ++i) {
                    bit = dividen.limbs[current_index] << i;
                    bit >>= BASE_BITS_MINUS1;
                    remainder <<= 1;
                    remainder.limbs[0] |= bit;
                    if (remainder >= divisor) {
                        remainder -= divisor;
                    }
                }
            }
        }
        return remainder;
    }
    integer integer::bit_modulo(const integer &op) const {
        if (op.length == 1) {
            return mod_n_by_1(limbs, length, op.limbs[0]);
        }
        return mod_n_by_m(*this, op);
    }
    integer &integer::bit_modulo_assign(const integer &op) {
        if (op.length == 1) {
            limbs[0] = mod_n_by_1(limbs, length, op.limbs[0]);
            length = 1;
            return *this;
        }
        *this = mod_n_by_m(*this, op);
        return *this;
    }
    void integer::div_mod(integer& q, integer& r, integer& dividen, const integer& divisor) {
        if (divisor.length == 1) {
            uint64_t remainder = 0;
            uint32_t onelimb_divisor = divisor[0];
            remainder = dividen.limbs[dividen.length - 1] % onelimb_divisor;
            remainder <<= BASE_BITS;
            q.limbs[dividen.length - 1] = dividen.limbs[dividen.length - 1] / onelimb_divisor;
            for (size_t i = 1; i < dividen.length; ++i) {
                remainder |= dividen.limbs[dividen.length - 1 - i];
                q.limbs[dividen.length - 1 - i] = remainder / onelimb_divisor;
                remainder = (remainder % onelimb_divisor) << BASE_BITS;
            }
            r = remainder >> BASE_BITS;
        } else {
            integer remainder(dividen.length, dividen.length);
            remainder.length = 1;
            remainder.limbs[0] = 0;
            uint32_t bit = 0, current_index = dividen.length, onebit = 1;
            size_t total_bits = dividen.length * BASE_BITS;
            for (size_t h = 0; h < total_bits; h += BASE_BITS) {
                remainder <<= BASE_BITS;
                remainder.limbs[0] = dividen.limbs[--current_index];
                q.limbs[current_index] = 0;
                if (remainder >= divisor) {
                    uint32_t r = remainder.limbs[0];
                    remainder >>= BASE_BITS;
                    for (size_t i = 0; i < BASE_BITS; ++i) {
                        bit = (r << i);
                        bit >>= BASE_BITS_MINUS1;
                        remainder <<= 1;
                        remainder.limbs[0] |= bit;
                        if (remainder >= divisor) {
                            remainder -= divisor;
                            q.limbs[current_index] |= (onebit << (BASE_BITS_MINUS1 - i));
                        }
                    }
                }
            }
            r = remainder;
        }
        q.remove_leading_zeros();
    }
    integer &integer::operator++() noexcept {
        return *this += 1;
    }
    integer &integer::operator--() noexcept {
        return *this -= 1;
    }
    integer integer::operator++(int) noexcept {
        integer prev = *this;
        ++*this;
        return prev;
    }
    integer integer::operator--(int) noexcept {
        integer prev = *this;
        --*this;
        return prev;
    }
    integer &integer::operator<<=(size_t bits) noexcept {
        if (*this && bits) {
            size_t limb_shifts = bits / BASE_BITS;
            size_t bit_shifts = bits % BASE_BITS;
            size_t new_length = length + limb_shifts + 1;
            size_t zero_limbs = new_length - length - 1;
            if (new_length > capacity) {
                capacity = new_length + LIMB_GROWTH;
                limbs = (uint32_t *) std::realloc(limbs, capacity * LIMB_BYTES);
            }
            limbs[new_length - 1] = 0;
            for (size_t i = 0; i < length; ++i) {
                uint64_t temp_shift = limbs[length - 1 - i];
                temp_shift <<= bit_shifts;
                limbs[new_length - 1 - i] |= temp_shift >> BASE_BITS;
                limbs[new_length - 2 - i] = temp_shift;
            }
            if (zero_limbs) {
                std::memset(limbs, 0x00, zero_limbs * LIMB_BYTES);
            }
            length = new_length;
            length -= !limbs[length - 1];
        }
        return *this;
    }
    integer &integer::operator>>=(size_t bits) noexcept {
        if (*this && bits) {
            size_t limb_shifts = bits / BASE_BITS;
            if (limb_shifts >= length) {
                length = 1;
                limbs[0] = 0;
            } else {
                size_t bit_shifts = bits % BASE_BITS;
                size_t new_length = length - limb_shifts;
                limbs[0] = limbs[limb_shifts] >> bit_shifts;
                for (size_t i = 1; i < new_length; ++i) {
                    uint64_t temp_shift = limbs[i + limb_shifts];
                    temp_shift = (temp_shift << BASE_BITS) >> bit_shifts;
                    limbs[i - 1] |= temp_shift;
                    limbs[i] = temp_shift >> BASE_BITS;
                }
                length = new_length;
                length -= !limbs[length - 1] && length != 1;
            }
        }
        return *this;
    }
    integer integer::operator<<(size_t bits) const noexcept {
        integer shifted = *this;
        return shifted <<= bits;
    }
    integer integer::operator>>(size_t bits) const noexcept {
        integer shifted = *this;
        return shifted >>= bits;
    }
    void integer::printHex() const {
        std::cout << "0x";
        printf("%x", (uint32_t) limbs[length - 1]);
        for (size_t i = 1; i < length; ++i) {
            printf("%08x", (uint32_t) limbs[length - 1 - i]);
        }
        std::cout << "\n";
    }
    void integer::printHex_spaced_out() const {
        printf("%08x", (uint32_t) limbs[length - 1]);
        for (size_t i = 1; i < length; ++i) {
            printf(" %08x", (uint32_t) limbs[length - 1 - i]);
        }
        std::cout << "\n";
    }
    void integer::printBin_spaced_out() const {
        for (size_t i = 0; i < length; ++i) {
            std::cout << std::bitset<BASE_BITS>(limbs[length - 1 - i]) << " ";
        }
        std::cout << "\n";
    }
    void integer::printStatus(std::string printIdentifier) const {
        std::cout << "\n-----\n";
        std::cout << printIdentifier << "\n";
        std::cout << "capacity : " << capacity << "\n";
        std::cout << "length   : " << length << "\n";
        printHex_spaced_out();
    }
    std::string integer::to_base10_string() const {
        std::string Base10;
        integer quotient = *this, remainder = 0;
        Base10.reserve(quotient.length);
        if (quotient) {
            while (quotient) {
                div_mod(quotient, remainder, quotient, 10);
                Base10.push_back('0' + remainder.limbs[0]);
            }
            std::reverse(Base10.begin(), Base10.end());
        } else {
            Base10 = "0";
        }
        return Base10;
    }
    std::string integer::to_base16_string() const {
        char buffer[17];
        std::string hexform = "";
        sprintf(buffer, "%x", (uint32_t) limbs[length - 1]);
        hexform.append(buffer);
        for (size_t i = 1; i < length; ++i) {
            sprintf(buffer, "%08x", (uint32_t) limbs[length - 1 - i]);
            hexform.append(buffer);
        }
        return hexform;
    }
    size_t integer::byte_size() const noexcept {
        uint32_t ms_limb = limbs[length - 1];
        size_t cnt = 0;
        while (ms_limb) {
            ms_limb >>= 8;
            cnt++;
        }
        return (length - 1) * BASE_BYTES + cnt;
    }
    size_t integer::bit_size() const noexcept {
        uint32_t ms_limb = limbs[length - 1];
        size_t cnt = 0;
        while (ms_limb) {
            ms_limb >>= 1;
            cnt++;
        }
        return (length - 1) * BASE_BITS + cnt;
    }
    uint32_t *integer::detach() { uint32_t *detached = limbs; limbs = NULL; capacity = 0; length = 0; return detached; }
    void swap(integer &a, integer &b) { integer temp = std::move(a); a = std::move(b); b = std::move(temp);
    }
    std::ostream &operator<<(std::ostream &out, const integer &num) { out << num.to_base16_string(); return out; }
    std::istream &operator>>(std::istream &in, integer &num) { std::string input; in >> input; num = integer(input, 16); return in; }
    class bint_error : public std::exception {
        private:
        unsigned int error_code;
        std::string error_message;
        public:
        bint_error(unsigned int error_code);
        unsigned int get_error_code() const;
        const char *what() const throw();
    };
    class bint {
        private:
        integer number;
        uint32_t sign;
        int compare(const bint &with) const;
        static void bitwise_prepare(bint &left, bint &right);
        static bint add_partial(
            const uint32_t *l, size_t l_len, size_t l_index, const uint32_t *r, size_t r_len, size_t r_index
        );
        static void sub_partial(
            uint32_t *output, size_t out_len, size_t out_index, const uint32_t *m, size_t m_len, size_t m_index
        );
        static void mul_karatsuba(
            uint32_t *output, size_t out_len, size_t out_index, const uint32_t *l, size_t l_len, size_t l_index,
            const uint32_t *r, size_t r_len, size_t r_index
        );
        public:
        bint();
        bint(char num);
        bint(unsigned char num);
        bint(short num);
        bint(unsigned short num);
        bint(int num);
        bint(unsigned int num);
        bint(long num);
        bint(unsigned long num);
        bint(long long num);
        bint(unsigned long long num);
        bint(const std::string &input);
        bint(const char *input);
        bint(std::initializer_list<uint32_t> limbs, uint32_t sign = 0);
        bint(uint32_t *arr, size_t capacity, size_t length, uint32_t sign);
        bint(size_t capacity, size_t length, bool AllocateSpace = true);
        bint(const bint &src);     
        bint(bint &&src) noexcept; 
        bint &operator=(const bint &src);     
        bint &operator=(bint &&src) noexcept; 
        bint(uint32_t sign, const integer &number);     
        bint(uint32_t sign, integer &&number) noexcept; 
        ~bint();
        bool operator<(const bint &op) const;
        bool operator>(const bint &op) const;
        bool operator==(const bint &op) const;
        bool operator!=(const bint &op) const;
        bool operator<=(const bint &op) const;
        bool operator>=(const bint &op) const;
        bint &operator&=(const bint &op);
        bint &operator|=(const bint &op);
        bint &operator^=(const bint &op);
        bint operator&(const bint &op) const;
        bint operator|(const bint &op) const;
        bint operator^(const bint &op) const;
        bint operator~() const;
        explicit operator bool() const noexcept;
        bint &operator+=(const bint &op);
        bint &operator-=(const bint &op);
        bint &operator*=(const bint &op);
        bint &operator/=(const bint &op);
        bint &operator%=(const bint &op);
        bint operator+(const bint &op) const;
        bint operator-(const bint &op) const;
        bint operator*(const bint &op) const;
        bint operator/(const bint &op) const;
        bint operator%(const bint &op) const;
        bint operator-() const;
        bint mul_naive(const bint &op) const;
        bint &operator++();
        bint &operator--();
        bint operator++(int);
        bint operator--(int);
        bint &operator<<=(size_t bits);
        bint &operator>>=(size_t bits);
        bint operator<<(size_t bits) const;
        bint operator>>(size_t bits) const;
        void printHex() const;
        void printHex_spaced_out() const;
        void printStatus(std::string printIdentifier = "default") const;
        std::string to_base10_string() const;
        std::string to_base16_string() const;
        size_t capacity_size() const;
        size_t limb_size() const;
        size_t byte_size() const;
        size_t bit_size() const;
        const uint32_t *limb_view() const;
        const uint32_t *byte_view() const;
        uint32_t *detach();
    };
    void swap(bint &a, bint &b);
    std::ostream &operator<<(std::ostream &out, const bint &num);
    std::istream &operator>>(std::istream &in, bint &num);
    static const bint __BINT_ZERO = 0;
    static const bint __BINT_ONE = 1;
    static const bint __BINT_TWO = 2;
    static const bint __BINT_TEN = 10;
    bint_error::bint_error(unsigned int error_code) : error_code(error_code) {
        switch (error_code) {
            case 1:
                error_message = "assignment of an empty string literal to a bint is not allowed";
                break;
            case BIN:
                error_message = "invalid digit found in assigned \"binary\" number";
                break;
            case OCT:
                error_message = "invalid digit found in assigned \"octal\" number";
                break;
            case DEC:
                error_message = "invalid digit found in assigned \"decimal\" number";
                break;
            case HEX:
                error_message = "invalid digit found in assigned \"hex\" number";
                break;
        }
    }
    unsigned int bint_error::get_error_code() const {
        return this->error_code;
    }
    const char *bint_error::what() const throw() {
        return error_message.c_str();
    }
    bint::bint(char num)
    :   sign(num < 0)
    {
        if (num == std::numeric_limits<char>::min()) {
            char new_num = num + 1;
            number = integer((size_t) std::abs(new_num));
            number++;
        } else {
            number = integer((size_t) std::abs(num));
        }
    }
    bint::bint(unsigned char num): number(integer((size_t) num)), sign(0){}
    bint::bint(short num): sign(num < 0){
        if (num == std::numeric_limits<short>::min()) {
            short new_num = num + 1;
            number = integer((size_t) std::abs(new_num));
            number++;
        } else {
            number = integer((size_t) std::abs(num));
        }
    }
    bint::bint(unsigned short num): number(integer((size_t) num)), sign(0){}
    bint::bint(int num): sign(num < 0){
        if (num == std::numeric_limits<int>::min()) {
            int new_num = num + 1;
            number = integer((size_t) std::abs(new_num));
            number++;
        } else {
            number = integer((size_t) std::abs(num));
        }
    }
    bint::bint(unsigned int num): number(integer((size_t) num)), sign(0){}
    bint::bint(long num): sign(num < 0){
        if (num == std::numeric_limits<long>::min()) {
            long new_num = num + 1;
            number = integer((size_t) std::abs(new_num));
            number++;
        } else {
            number = integer((size_t) std::abs(num));
        }
    }
    bint::bint(unsigned long num): number(integer((size_t) num)), sign(0){}
    bint::bint(long long num): sign(num < 0){
        if (num == std::numeric_limits<long long>::min()) {
            long long new_num = num + 1;
            number = integer((size_t) std::abs(new_num));
            number++;
        } else {
            number = integer((size_t) std::abs(num));
        }
    }
    bint::bint(unsigned long long num) :number(integer((size_t) num)), sign(0){}
    bint::bint() :number(integer()), sign(0){}
    bint::bint(size_t capacity, size_t length, bool AllocateSpace): number(integer(capacity, length, AllocateSpace)), sign(0){}
    bint::bint(const std::string &input) {
        if (input.empty())
            throw bint_error(EMPTY); 
        size_t start_index = input[0] == '-';
        size_t base = 0;
        if (input.size() == 1 && (input[0] >= '0' && input[0] <= '9')) {
            base = DEC;
        } else if (input[start_index] == '0') {
            start_index++;
            if (input[start_index] == 'b') { 
                start_index++;
                for (size_t i = start_index; i < input.size(); ++i) {
                    if ((input[i] < '0') ^ (input[i] > '1')) {
                        throw bint_error(BIN);
                    }
                }
                base = BIN;
            } else if (input[start_index] == 'o') { 
                start_index++;
                for (size_t i = start_index; i < input.size(); ++i) {
                    if ((input[i] < '0') ^ (input[i] > '7')) {
                        throw bint_error(OCT);
                    }
                }
                base = OCT;
            } else if (input[start_index] == 'x') { 
                start_index++;
                for (size_t i = start_index; i < input.size(); ++i) {
                    if (CHAR_TO_HEX[(size_t) input[i]] == 0xff) {
                        throw bint_error(HEX);
                    }
                }
                base = HEX;
            } else {
                throw bint_error(INVALID);
            }
        } else { 
            for (size_t i = start_index; i < input.size(); ++i) {
                if ((input[i] < '0') ^ (input[i] > '9')) {
                    throw bint_error(DEC);
                }
            }
            base = DEC;
        }
        sign = input[0] == '-';
        number = integer(std::string(input.begin() + start_index, input.end()), base);
        number.remove_leading_zeros();
    }
    bint::bint(const char *input): bint(std::string(input)){}
    bint::bint(uint32_t *arr, size_t capacity, size_t length, uint32_t sign): number(integer(arr, capacity, length)), sign(sign){}
    bint::bint(const bint &src): number(src.number), sign(src.sign){}
    bint::bint(bint &&src) noexcept: number(std::move(src.number)), sign(src.sign){}
    bint &bint::operator=(const bint &src) {
        if (this != &src) {
            number = src.number;
            sign = src.sign;
        }
        return *this;
    }
    bint &bint::operator=(bint &&src) noexcept {
        if (this != &src) {
            number = std::move(src.number);
            sign = src.sign;
        }
        return *this;
    }
    bint::bint(uint32_t sign, const integer &number) { this->number = number; this->sign = sign; }
    bint::bint(uint32_t sign, integer &&number) noexcept { this->number = std::move(number); this->sign = sign; }
    bint::bint(std::initializer_list<uint32_t> limbs, uint32_t sign) { number = integer(limbs); this->sign = sign; }
    bint::~bint() { this->sign = 0; }
    int bint::compare(const bint &op) const {
        if (LPOS_RNEG(sign, op.sign)) {
            return GREAT;
        } else if (LNEG_RPOS(sign, op.sign)) {
            return LESS;
        } else if (SIGN_NEGATIVE(sign)) {
            return CMP_RES_FLIP(number.compare(op.number));
        }
        return number.compare(op.number);
    }
    bool bint::operator<(const bint &op) const { return compare(op) == LESS; }
    bool bint::operator>(const bint &op) const { return compare(op) == GREAT; }
    bool bint::operator==(const bint &op) const { return compare(op) == EQUAL; }
    bool bint::operator!=(const bint &op) const { return (*this == op) ^ 1u; }
    bool bint::operator<=(const bint &op) const { return compare(op) <= EQUAL; }
    bool bint::operator>=(const bint &op) const { return compare(op) >= EQUAL; }
    void bint::bitwise_prepare(bint &left, bint &right) {
        size_t lpadding = 0, rpadding = 0;
        if (left.limb_size() < right.limb_size()) {
            lpadding = right.limb_size() - left.limb_size();
        } else {
            rpadding = left.limb_size() - right.limb_size();
        }
        if (SIGN_NEGATIVE(left.sign)) {
            left.number.bit_flip(lpadding);
            ++left.number;
        }
        if (SIGN_NEGATIVE(right.sign)) {
            right.number.bit_flip(rpadding);
            ++right.number;
        }
        if (lpadding) {
            left.number.bit_realloc(right.number);
        } else if (rpadding) {
            right.number.bit_realloc(left.number);
        }
    }
    bint &bint::operator&=(const bint &op) {
        if (sign | op.sign) {
            bint left = *this, right = op;
            bitwise_prepare(left, right);
            left.number.bit_and(right.number);
            left.sign &= right.sign;
            if (SIGN_NEGATIVE(left.sign)) {
                left.number.bit_flip(0);
                ++left.number;
            }
            left.number.remove_leading_zeros();
            swap(*this, left);
        } else {
            number &= op.number;
        }
        return *this;
    }
    bint bint::operator&(const bint &op) const {
        bint bw = *this;
        return bw &= op;
    }
    bint &bint::operator|=(const bint &op) {
        if (sign | op.sign) {
            bint left = *this, right = op;
            bitwise_prepare(left, right);
            left.number.bit_or(right.number);
            left.sign |= right.sign;
            if (SIGN_NEGATIVE(left.sign)) {
                left.number.bit_flip(0);
                ++left.number;
            }
            left.number.remove_leading_zeros();
            swap(*this, left);
        } else {
            number |= op.number;
        }
        return *this;
    }
    bint bint::operator|(const bint &op) const {
        bint bw = *this;
        return bw |= op;
    }
    bint &bint::operator^=(const bint &op) {
        if (sign | op.sign) {
            bint left = *this, right = op;
            bitwise_prepare(left, right);
            left.number.bit_xor(right.number);
            left.sign ^= right.sign;
            if (SIGN_NEGATIVE(left.sign)) {
                left.number.bit_flip(0);
                ++left.number;
            }
            left.number.remove_leading_zeros();
            swap(*this, left);
        } else {
            number ^= op.number;
        }
        return *this;
    }
    bint bint::operator^(const bint &op) const {
        bint bw = *this;
        return bw ^= op;
    }
    bint bint::operator~() const {
        bint bwn = *this;
        if (SIGN_NEGATIVE(sign)) {
            --bwn.number;
        } else {
            ++bwn.number;
        }
        bwn.sign = bwn.sign ^ 1u;
        return bwn;
    }
    bint::operator bool() const noexcept {
        return (bool) number;
    }
    bint &bint::operator+=(const bint &op) {
        if (sign ^ op.sign) {
            int cmp = number.compare(op.number);
            if (cmp == GREAT) {
                number -= op.number;
            } else if (cmp == LESS) {
                number = op.number - number;
                sign = op.sign;
            } else {
                number.length = 1;
                number[0] = 0;
                sign = 0;
            }
        } else {
            number += op.number;
        }
        return *this;
    }
    bint bint::operator+(const bint &op) const {
        if (sign ^ op.sign) {
            int cmp = number.compare(op.number);
            if (cmp == GREAT) {
                return bint(sign, number - op.number);
            } else if (cmp == LESS) {
                return bint(op.sign, op.number - number);
            } else {
                return __BINT_ZERO;
            }
        }
        return bint(sign, number + op.number);
    }
    bint &bint::operator-=(const bint &op) {
        if (sign ^ op.sign) {
            number += op.number; 
        } else {
            int cmp = compare(op);
            if (cmp == EQUAL) {
                number.length = 1;
                number[0] = 0;
            } else if (SIGN_NEGATIVE(sign)) {
                if (cmp == GREAT) {
                    number = op.number - number;
                    sign = 0;
                } else {
                    number -= op.number;
                    sign = 0;
                }
            } else {
                if (cmp == GREAT) {
                    number -= op.number;
                    sign = 0;
                } else {
                    number = op.number - number;
                    sign = 0;
                }
            }
        }
        return *this;
    }
    bint bint::operator-(const bint &op) const {
        if (sign == op.sign) {
            int cmp = compare(op);
            if (cmp == EQUAL) {
                return __BINT_ZERO;
            } else if (SIGN_NEGATIVE(sign)) {
                if (cmp == GREAT) {
                    return bint(0, op.number - number);
                } else {
                    return bint(0, number - op.number);
                }
            } else {
                if (cmp == GREAT) {
                    return bint(0, number - op.number);
                } else {
                    return bint(0, op.number - number);
                }
            }
        }
        return bint(sign, number + op.number);
    }
    bint &bint::operator*=(const bint &op) {
        bint product = *this * op;
        swap(product, *this);
        return *this;
    }
    bint bint::mul_naive(const bint &op) const {
        bint product((sign == op.sign) ^ 1u, number * op.number);
        if (!product.number) {
            product.sign = 0;
        }
        return product;
    }
    bint bint::add_partial(
        const uint32_t *num1, size_t num1_len, size_t num1_index, const uint32_t *num2, size_t num2_len, size_t num2_index
    ) {
        size_t len = std::max(num1_len, num2_len) + 1;
        bint sum(len + 1, len);
        std::memset(sum.number.limbs, 0x00, LIMB_BYTES * sum.number.capacity);
        for (size_t i = 0; i < num1_len; ++i) {
            sum.number.limbs[i] = num1[num1_index + i];
        }
        uint32_t carry = 0;
        for (size_t i = 0; i < num2_len; ++i) {
            uint64_t sum_index = (uint64_t) sum.number.limbs[i] + num2[num2_index + i] + carry;
            sum.number.limbs[i] = sum_index;
            carry = sum_index >> BASE_BITS;
        }
        for (size_t i = num2_len; i < sum.number.length; ++i) {
            uint64_t sum_index = (uint64_t) sum.number.limbs[i] + carry;
            sum.number.limbs[i] = sum_index;
            carry = sum_index >> BASE_BITS;
        }
        sum.number.limbs[sum.number.length] += carry;
        sum.number.remove_leading_zeros();
        return sum;
    }
    void bint::mul_karatsuba(
        uint32_t *out, size_t out_len, size_t out_index, const uint32_t *num1, size_t num1_len, size_t num1_index,
        const uint32_t *num2, size_t num2_len, size_t num2_index
    ) {
        if (num2_len < KARATSUBA_SIZE || num1_len < KARATSUBA_SIZE) {
            size_t i = 0, j = 0;
            uint32_t carry = 0;
            for (j = 0; j < num1_len; ++j) {
                uint64_t product_index = (uint64_t) num1[j + num1_index] * num2[num2_index] + carry;
                out[j + out_index] = product_index;
                carry = (product_index >> BASE_BITS);
            }
            out[num1_len + out_index] = carry;
            for (i = 1; i < num2_len; ++i) {
                carry = 0;
                for (j = 0; j < num1_len; ++j) {
                    uint64_t product_index =
                        (uint64_t) num1[j + num1_index] * num2[i + num2_index] + out[i + j + out_index] + carry;
                    out[i + j + out_index] = product_index;
                    carry = (product_index >> BASE_BITS);
                }
                out[i + num1_len + out_index] = carry;
            }
            return;
        }
        size_t max_len = std::max(num1_len, num2_len);
        size_t split_len = max_len - (max_len / 2);
        size_t a_len, b_len, c_len, d_len;
        if (num1_len > split_len) {
            a_len = num1_len - split_len;
            b_len = split_len;
        } else {
            a_len = 0;
            b_len = num1_len;
        }
        if (num2_len > split_len) {
            c_len = num2_len - split_len;
            d_len = split_len;
        } else {
            c_len = 0;
            d_len = num2_len;
        }
        size_t z0_padding = split_len * 2;
        if (a_len && c_len) {
            mul_karatsuba(
                out, out_len, out_index + z0_padding, num1, a_len, split_len + num1_index, num2, c_len,
                split_len + num2_index
            );
        }
        bint z0;
        if (a_len && c_len) {
            z0 = bint(out + out_index + z0_padding, a_len + c_len + 1, a_len + c_len, 0);
        } else {
            z0 = bint(__BINT_ZERO.number.limbs, 1, 1, 0);
        }
        z0.number.remove_leading_zeros();
        mul_karatsuba(out, out_len, out_index, num1, b_len, num1_index, num2, d_len, num2_index);
        bint z1 = bint(out + out_index, b_len + d_len + 1, b_len + d_len, 0);
        z1.number.remove_leading_zeros();
        bint lsplit_add, rsplit_add;
        if (a_len) {
            lsplit_add = add_partial(num1, a_len, split_len + num1_index, num1, b_len, num1_index);
        } else {
            lsplit_add = add_partial(__BINT_ZERO.number.limbs, 1, 0, num1, b_len, num1_index);
        }
        if (c_len) {
            rsplit_add = add_partial(num2, c_len, split_len + num2_index, num2, d_len, num2_index);
        } else {
            rsplit_add = add_partial(__BINT_ZERO.number.limbs, 1, 0, num2, d_len, num2_index);
        }
        bint z2(
            lsplit_add.number.length + rsplit_add.number.length + 1, lsplit_add.number.length + rsplit_add.number.length
        );
        std::memset(z2.number.limbs, 0x00, z2.number.capacity * LIMB_BYTES);
        mul_karatsuba(
            z2.number.limbs, z2.number.length, 0, lsplit_add.number.limbs, lsplit_add.number.length, 0,
            rsplit_add.number.limbs, rsplit_add.number.length, 0
        );
        z2.number.remove_leading_zeros();
        bint z3 = std::move(z2);
        z3 -= z1;
        z3 -= z0;
        z0.detach();
        z1.detach();
        uint32_t carry = 0;
        for (size_t i = 0; i < z3.number.length; ++i) {
            uint64_t sum_index = (uint64_t) out[i + split_len + out_index] + z3.number.limbs[i] + carry;
            out[i + split_len + out_index] = sum_index;
            carry = sum_index >> BASE_BITS;
        }
        for (size_t i = out_index + split_len + z3.number.length; carry; ++i) {
            uint64_t sum_index = (uint64_t) out[i] + carry;
            out[i] = sum_index;
            carry = sum_index >> BASE_BITS;
        }
    }
    bint bint::operator*(const bint &op) const {
        if (number.length < KARATSUBA_SIZE || op.number.length < KARATSUBA_SIZE) {
            return mul_naive(op);
        }
        size_t len = number.length + op.number.length;
        bint product(len + 1, len);
        std::memset(product.number.limbs, 0x00, product.number.capacity * LIMB_BYTES);
        mul_karatsuba(
            product.number.limbs, product.number.length, 0, number.limbs, number.length, 0, op.number.limbs,
            op.number.length, 0
        );
        product.number.remove_leading_zeros();
        product.sign = (sign == op.sign) ^ 1u;
        return product;
    }
    bint &bint::operator/=(const bint &op) { sign = (sign == op.sign) ^ 1u; number /= op.number; if (!number) { sign = 0; } return *this; }
    bint bint::operator/(const bint &op) const { bint quotient((sign == op.sign) ^ 1u, number / op.number); if (!quotient.number) { quotient.sign = 0; } return quotient; }
    bint &bint::operator%=(const bint &op) { number %= op.number; if (!number) { sign = 0; } return *this; }
    bint bint::operator%(const bint &op) const { bint mod(sign, number % op.number); if (!mod.number) { mod.sign = 0; } return mod; }
    bint bint::operator-() const { bint negate = *this; negate.sign = negate.sign ^ 1u; return negate; }
    bint &bint::operator++() { return *this += __BINT_ONE; }
    bint &bint::operator--() { return *this -= __BINT_ONE; }
    bint bint::operator++(int) { bint prev = *this; ++*this; return prev; }
    bint bint::operator--(int) { bint prev = *this; --*this; return prev; }
    bint &bint::operator<<=(size_t bits) { number <<= bits; return *this; }
    bint &bint::operator>>=(size_t bits) { number >>= bits; number += sign; return *this; }
    bint bint::operator<<(size_t bits) const { bint shifted = *this; return shifted <<= bits; }
    bint bint::operator>>(size_t bits) const { bint shifted = *this; return shifted >>= bits; }
    void bint::printHex() const {
        if (SIGN_NEGATIVE(sign)) {
            std::cout << "-";
        }
        number.printHex();
    }
    void bint::printHex_spaced_out() const {
        number.printHex_spaced_out();
        std::cout << ((SIGN_NEGATIVE(sign)) ? "\nNegative:" : "\nPositive\n");
    }
    void bint::printStatus(std::string printIdentifier) const {
        number.printStatus(printIdentifier);
        std::cout << ((SIGN_NEGATIVE(sign)) ? "\nNegative:" : "\nPositive\n");
    }
    std::string bint::to_base10_string() const {
        std::string Base10 = "";
        if (SIGN_NEGATIVE(sign)) {
            Base10.push_back('-');
        }
        Base10.append(number.to_base10_string());
        return Base10;
    }
    std::string bint::to_base16_string() const {
        std::string Base16 = "";
        if (SIGN_NEGATIVE(sign)) {
            Base16.push_back('-');
        }
        Base16.append(number.to_base16_string());
        return Base16;
    }
    size_t bint::capacity_size() const { return number.capacity; }
    size_t bint::limb_size() const { return number.length; }
    size_t bint::byte_size() const { return number.byte_size(); }
    size_t bint::bit_size() const { return number.bit_size(); }
    const uint32_t *bint::limb_view() const { return (const uint32_t *) number.limbs; }
    const uint32_t *bint::byte_view() const { return (const uint32_t *) number.limbs; }
    uint32_t *bint::detach() { sign = 0; return number.detach(); }
    void swap(bint &a, bint &b) { bint temp = std::move(a); a = std::move(b); b = std::move(temp); }
    std::ostream &operator<<(std::ostream &out, const bint &num) { out << num.to_base16_string(); return out; }
    std::istream &operator>>(std::istream &in, bint &num) { std::string input; in >> input; num = bint(input); return in; }
}

int main(){
    apa::bint a = "123";
    apa::bint b = "456";
    std::cout << (a + b); // 等价于(a + b).to_base16_string()，十六机制
    std::cout << (a + b).to_base10_string();
    return 0;
}