#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QString>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gnuplotProc{nullptr},
    m_scene{nullptr}
{
    ui->setupUi(this);
    m_gnuplotProc = new QProcess(this);
    m_gnuplotProc->connect(m_gnuplotProc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onGnuplotFinished(int, QProcess::ExitStatus)));
    m_scene = new QGraphicsScene(ui->centralWidget);
    ui->m_imageView->setScene(m_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_selectFile_clicked()
{
    QString caption{"Select file for gnuplot"};
    QString file = QFileDialog::getOpenFileName(this->ui->centralWidget, caption, QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first(),{"Plot (*.plt);;All Files (*.*)"});

    QStringList args = {file};
    m_gnuplotProc->start({"gnuplot"}, args);

}

void MainWindow::onGnuplotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "gnuplot finished with exit code:" << exitCode << "and exit status:" << exitStatus;
    QPixmap pixmap;
    if (pixmap.load("Output.png")){
        m_scene->addPixmap(pixmap);
    }else{
        qDebug() << "can not load Output.png";
    }
}
