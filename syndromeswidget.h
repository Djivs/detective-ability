#ifndef SYNDROMESWIDGET_H
#define SYNDROMESWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMap>
#include <QVector>
#include <QPair>

namespace Ui {
class SyndromesWidget;
}

class SyndromesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SyndromesWidget(const QMap <int, QVector <QPair <int, int> > > &new_display_data, QWidget *parent = nullptr);
    ~SyndromesWidget();

private slots:
    void loadDisplayData();

private:
    Ui::SyndromesWidget *ui;

    QStandardItemModel *model;

    QMap <int, QVector <QPair <int, int> > > display_data;
};

#endif // SYNDROMESWIDGET_H
