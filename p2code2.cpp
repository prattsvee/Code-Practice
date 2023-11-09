#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

typedef std::vector<int> large_integer;

void add(large_integer &a, large_integer b) {
    int carry = 0;
    for (int i = 0; i < std::max(a.size(), b.size()) || carry; i++) {
        if (i == a.size()) a.push_back(0);
        a[i] += carry + (i < b.size() ? b[i] : 0);
        carry = a[i] >= 10;
        if (carry) a[i] -= 10;
    }
}

large_integer toLargeInteger(const std::string &str) {
    large_integer num;
    for (int i = str.size() - 1; i >= 0; i--) {
        num.push_back(str[i] - '0');
    }
    return num;
}

std::string toString(const large_integer &num) {
    std::string str;
    for (int i = num.size() - 1; i >= 0; i--) {
        str += std::to_string(num[i]);
    }
    return str;
}

large_integer generateRandomLargeInteger(int threshold) {
    large_integer num;
    for (int i = 0; i < threshold; i++) {
        num.push_back(rand() % 10);
    }
    return num;
}

large_integer prod(large_integer u, large_integer v, int threshold) {
    int n = std::max(u.size(), v.size());
    int m = n / 3;
    
    if (n <= threshold) {
        large_integer result(u.size() + v.size(), 0);
        for (int i = 0; i < u.size(); i++) {
            for (int j = 0, carry = 0; j < v.size() || carry; j++) {
                long long cur = result[i + j] + carry + (j < v.size() ? u[i] * v[j] : 0);
                result[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        while (result.size() > 1 && result.back() == 0) result.pop_back();
        return result;
    } else {
        large_integer divisor(m, 0);
        for (int i = 0; i < m; i++) {
            divisor[i] = 1;
        }
        large_integer u1(u.begin(), u.begin() + m);
        large_integer u2(u.begin() + m, u.begin() + 2 * m);
        large_integer u3(u.begin() + 2 * m, u.end());
        large_integer v1(v.begin(), v.begin() + m);
        large_integer v2(v.begin() + m, v.begin() + 2 * m);
        large_integer v3(v.begin() + 2 * m, v.end());
        
        large_integer z1 = prod(u1, v1, threshold);
        large_integer z2 = prod(u2, v2, threshold);
        large_integer z3 = prod(u3, v3, threshold);
        
        large_integer term1 = z1;
        for (int i = 0; i < 2 * m; i++) {
            term1.push_back(0);
        }
        
        large_integer term2 = z1;
        add(term2, z2);
        add(term2, z3);
        for (int i = 0; i < m; i++) {
            term2.push_back(0);
        }
        
        large_integer term3 = z3;
        
        add(term1, term2);
        add(term1, term3);
        
        return term1;
    }
}

large_integer prod_original(large_integer u, large_integer v, int threshold) {
    int n = std::max(u.size(), v.size());
    int m = n / 2;
    
    if (n <= threshold) {
        large_integer result(u.size() + v.size(), 0);
        for (int i = 0; i < u.size(); i++) {
            for (int j = 0, carry = 0; j < v.size() || carry; j++) {
                long long cur = result[i + j] + carry + (j < v.size() ? u[i] * v[j] : 0);
                result[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        while (result.size() > 1 && result.back() == 0) result.pop_back();
        return result;
    } else {
        large_integer divisor(m, 0);
        for (int i = 0; i < m; i++) {
            divisor[i] = 1;
        }
        large_integer x(u.begin(), u.begin() + m);
        large_integer y(u.begin() + m, u.end());
        large_integer w(v.begin(), v.begin() + m);
        large_integer z(v.begin() + m, v.end());
        
        large_integer xz = prod_original(x, z, threshold);
        large_integer yw = prod_original(y, w, threshold);
        large_integer xy = prod_original(x, y, threshold);
        
        large_integer term1 = xz;
        for (int i = 0; i < 2 * m; i++) {
            term1.push_back(0);
        }
        
        large_integer term2 = xy;
        add(term2, xz);
        add(term2, yw);
        for (int i = 0; i < m; i++) {
            term2.push_back(0);
        }
        
        large_integer term3 = yw;
        
        add(term1, term2);
        add(term1, term3);
        
        return term1;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " n" << std::endl;
        return 1; // Exit with an error code
    }

    int threshold = std::stoi(argv[1]);

    if (threshold % 6 != 0) {
        std::cerr << "Error: Input argument must be a multiple of 6." << std::endl;
        return 1; // Exit with an error code
    }

    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    std::string u_str;
    for (int i = 0; i < threshold; i++) {
        u_str += std::to_string(rand() % 10);
    }
    std::string v_str;
    for (int i = 0; i < threshold; i++) {
        v_str += std::to_string(rand() % 10);
    }

    large_integer u = toLargeInteger(u_str);
    large_integer v = toLargeInteger(v_str);

    std::cout << " A: " << u_str << std::endl;
    std::cout << " B: " << v_str << std::endl;

    large_integer result = prod(u, v, threshold);
    large_integer result_original = prod_original(u, v, threshold);

    std::cout << "The large integer multiplication from the division of three smaller integers is " << toString(result) << std::endl;
    std::cout << "The large integer multiplication from the division of two smaller integers is " << toString(result_original) << std::endl;

    return 0;
}

