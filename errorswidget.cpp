#include "errorswidget.h"
#include "ui_errorswidget.h"

#include "binary.h"

ErrorsWidget::ErrorsWidget(QMap <int, QVector <int>> display_data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ErrorsWidget)
{
    ui->setupUi(this);
    setWindowTitle("Векторы ошибок");

    setup_ui();

    for (auto &multiplicity: display_data.keys()) {
        QString errors;
        for (auto &error : display_data[multiplicity]) {
            errors += bin::bin_string(error) + ' ';
        }


        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount() - 1, 0), multiplicity);
        model->setData(model->index(model->rowCount() - 1, 1), display_data[multiplicity].size());
        model->setData(model->index(model->rowCount() - 1, 2), errors);
    }

    ui->table_view->resizeColumnsToContents();
}

ErrorsWidget::~ErrorsWidget()
{
    delete ui;
}


void ErrorsWidget::setup_ui() {
    model = new QStandardItemModel(this);
    QStringList header = {"Кратность", "Количество ошибок", "Векторы ошибок"};
    model->setHorizontalHeaderLabels(header);

    ui->table_view->setModel(model);

}
