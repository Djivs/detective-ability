#include "solver.h"

#include "binary.h"

using namespace bin;

Solver::Solver() {}

QMap <int, QVector <int>> Solver::errors_by_multiplicity() {
    QMap <int, QVector <int>> result;

    const int maxError = 0b0111'1111;

    for (int error = 1; error <= maxError; ++error) {
        int multiplicity = 0;

        for (int powerOf2 = 1; powerOf2 < maxError + 1; powerOf2 *= 2) {
            multiplicity += static_cast<bool>(error & powerOf2);
        }

        result[multiplicity].push_back(error);
    }

    return result;
}

int Solver::impose_error(int num, int error) {
    auto num_bytes = bin_string(num);
    auto error_bytes = bin_string(error);

    while (num_bytes.size() < error_bytes.size()) {
        num_bytes += '0';
    }

    while (error_bytes.size() < num_bytes.size()) {
        error_bytes  += '0';
    }

    for (int i = 0; i < error_bytes.size(); ++i) {
        if (error_bytes[i].toLatin1() - '0') {
            num_bytes[i] = QChar(!(num_bytes[i].toLatin1() - '0') + '0');
        }
    }

    return from_bin_string(num_bytes);

}

int Solver::syndrome(int err, int gen) {
    if (err < gen) {
        return err;
    }

    const auto err_bin_str = bin_string(err);
    int integer = 0;
    int cur = 0;
    int gen_bits_amount = bitsAmount(gen);

    int err_bit_pos = 0;
    for (; err_bit_pos < gen_bits_amount; err_bit_pos++) {
        cur <<= 1;
        cur += int(err_bin_str[err_bit_pos].toLatin1() - '0');
    }

    for (; err_bit_pos <= int(bitsAmount(err)); err_bit_pos++) {
        int firstBitInCur = cur / powBinary(gen_bits_amount-1);
        integer <<= 1;
        integer += firstBitInCur;

        if (firstBitInCur == 1) {
            cur ^= gen;
        }
        if (err_bit_pos == bitsAmount(err)) {
            break;
        }

        cur <<= 1;
        cur += static_cast<bool>(err_bin_str[err_bit_pos].toLatin1() - '0');
    }

    return cur;
}
