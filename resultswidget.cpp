#include "resultswidget.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(const QMap <int, QVector<int>> &display_data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResultsWidget)
{
    ui->setupUi(this);
    setWindowTitle("Результаты");

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Кратность ошибки", "Обнаруженные ошибки",\
                                      "Всего ошибок", "Обнаруживающая способность, %"});
    
    ui->table_view->setModel(model);

    int row = 0;
    for (auto &multiplicity: display_data.keys()) {
        model->insertRow(row);
        model->setData(model->index(row, 0), multiplicity);

        for (int col = 1; col <= display_data.size(); ++col) {
            model->setData(model->index(row, col), display_data[multiplicity][col - 1]);
        }

        row++;
    }

    ui->table_view->resizeColumnsToContents();
}

ResultsWidget::~ResultsWidget()
{
    delete ui;
}
