#ifndef ERRORSWIDGET_H
#define ERRORSWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMap>
#include <QVector>

namespace Ui {
class ErrorsWidget;
}

class ErrorsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorsWidget(QMap <int, QVector <int>> display_data, QWidget *parent = nullptr);
    ~ErrorsWidget();
private:
    void setup_ui();

private:
    Ui::ErrorsWidget *ui;

    QStandardItemModel *model;
};

#endif // ERRORSWIDGET_H
