#include "syndromeswidget.h"
#include "ui_syndromeswidget.h"

#include "binary.h"

SyndromesWidget::SyndromesWidget(const QMap <int, QVector <QPair <int, int> > > &new_display_data, QWidget *parent)
    : QWidget(parent), display_data(new_display_data)
    , ui(new Ui::SyndromesWidget)
{
    ui->setupUi(this);
    setWindowTitle("Синдромы");

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Синдром", "Вектор ошибки"});

    ui->table_view->setModel(model);

    ui->multiplicity_input->setMaximum(new_display_data.keys().size());
    ui->multiplicity_input->setMinimum(1);
    ui->multiplicity_input->setValue(1);

    connect(ui->multiplicity_input, &QSpinBox::valueChanged, this, &SyndromesWidget::loadDisplayData);
    loadDisplayData();
}

SyndromesWidget::~SyndromesWidget()
{
    delete ui;
}

void SyndromesWidget::loadDisplayData() {
    const int multiplicity = ui->multiplicity_input->value();

    model->setRowCount(0);

    const auto syndrome_by_error = display_data[multiplicity];

    for (int i = 0; i < syndrome_by_error.size(); ++i) {
        model->insertRow(i);
        model->setData(model->index(i, 0), bin::bin_string(syndrome_by_error[i].first));
        model->setData(model->index(i, 1), bin::bin_string(syndrome_by_error[i].second));

        if (bin::bin_string(syndrome_by_error[i].first) == "") {
            qDebug() << syndrome_by_error[i];
        } 
    }

    ui->table_view->resizeColumnsToContents();
}
