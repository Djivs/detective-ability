#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "errorswidget.h"
#include "syndromeswidget.h"
#include "resultswidget.h"
#include "solver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Обнаруживающая способность кода");

    const int coded_information_vector = 0b1000101;

    std::unique_ptr<Solver> solver;
    errors = solver->errors_by_multiplicity();

    for (auto &multiplicity: errors.keys()) {
        for (auto &error : errors[multiplicity]) {
            syndromes[multiplicity].append({solver->syndrome(error), error});
        }
    }

    QMap <int, int> syndrome_table;
    for (int i = 0; i < errors[1].size(); ++i) {
        syndrome_table[solver->syndrome(errors[1][i])] = errors[1][i];
    }

    for (auto &multiplicity : errors.keys()) {
        qDebug() << multiplicity;
        int detected_count = 0;
        int overall_count = errors[multiplicity].count();
        for (auto &error: errors[multiplicity]) {
            auto transferred_val = solver->impose_error(coded_information_vector, error);
            auto syndrome_val = solver->syndrome(transferred_val);

            auto corrected_val = solver->impose_error(coded_information_vector, syndrome_table[syndrome_val]);

            if (solver->syndrome(corrected_val)) {
                ++detected_count;
            }
        }

        QVector <int> result = {detected_count, overall_count,\
                               static_cast<int>(static_cast<float>(detected_count) / static_cast<float>(overall_count) * 100.0)};

        results[multiplicity] = result;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_syndromes_clicked()
{


    SyndromesWidget *w = new SyndromesWidget(syndromes);
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
}


void MainWindow::on_errors_clicked()
{
    ErrorsWidget *w = new ErrorsWidget(errors);
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
}


void MainWindow::on_results_clicked()
{
    ResultsWidget *w = new ResultsWidget(results);
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
}


void MainWindow::on_exit_clicked()
{
    this->close();
}

