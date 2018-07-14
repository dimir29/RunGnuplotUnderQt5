#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QGraphicsScene>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_m_selectFile_clicked();
    void onGnuplotFinished(int, QProcess::ExitStatus);

private:
    Ui::MainWindow *ui;
    QProcess* m_gnuplotProc;
    QGraphicsScene* m_scene;

};

#endif // MAINWINDOW_H
