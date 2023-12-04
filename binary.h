#pragma once

#include <QString>
#include <cmath>

namespace bin {
    static int powBinary(int n) {
        int res = 1;
        for (int i = 1; i <= n; i++) {
            res <<= 1;
        }
        return res;
    }

    static int bits(int num ){
        int retVal = 0 ;

        while ( num ){
            retVal += ( num & 1 );
            num >>= 1 ;
        }

        return retVal;
    }

    static int bitsAmount (int num) {
        int result = 0;
        int bitsAmount = 0;
        for (int powerOf2 = 1; powerOf2 <= num; powerOf2 *= 2) {
            ++bitsAmount;
        }

        return bitsAmount;
    }

    static QString bin_string(int num) {
        QString bin;
        const int len = bitsAmount(num);
        for (int i = len - 1; i >= 0; --i) {
            bin += QChar(static_cast<bool>(num & static_cast<int>(pow(2, i))) + '0');
        }

        return bin;
    }

    static int from_bin_string(const QString &bin) {
        int result = 0;
        int power_of_2 = 1;
        for (int i = bin.size() - 1; i >= 0; --i) {
            if (bin[i].toLatin1() - '0') {
                result += power_of_2;
            }
            power_of_2 *= 2;
        }

        return result;
    }


}


