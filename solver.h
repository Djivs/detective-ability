#ifndef SOLVER_H
#define SOLVER_H

#include <QMap>
#include <QVector>

class Solver
{
public:
    Solver();

    QMap <int, QVector <int>> errors_by_multiplicity();
    int impose_error(int num, int error);
    int syndrome(int a, int b = gen_polynomial);
private:
    static const int gen_polynomial = 0b1011;
};

#endif // SOLVER_H
