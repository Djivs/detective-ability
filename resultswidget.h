#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H

#include <QWidget>
#include <QArrayData>
#include <QMap>
#include <QStandardItemModel>

namespace Ui {
class ResultsWidget;
}

class ResultsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsWidget(const QMap <int, QVector<int>> &display_data, QWidget *parent = nullptr);
    ~ResultsWidget();

private:
    Ui::ResultsWidget *ui;

    QStandardItemModel *model;
};

#endif // RESULTSWIDGET_H
