#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_syndromes_clicked();

    void on_errors_clicked();

    void on_results_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;

    QMap <int, QVector <int>> errors;
    QMap <int, QVector <QPair <int, int>>> syndromes;
    QMap <int, QVector <int>> results;


};
#endif // MAINWINDOW_H
