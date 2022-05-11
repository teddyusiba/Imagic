#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QMimeData>
#include <QPixmap>
#include <QDesktopServices>
#include <QMenuBar>
#include <QMenu>
#include <QSettings>
#include <QApplication>
#include <QLabel>
#include <QThread>
#include <QActionEvent>
#include "algorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void grey(int i, QImage image, QLabel *label);

protected:
    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

private slots:
    void on_add_file_triggered();

    void on_radioButton_clicked();

    void on_save_file_triggered();

    void on_quit_triggered();

    void on_help_triggered();

    void on_question_triggered();

    void on_about_us_triggered();

    void on_about_QT_triggered();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:

    Ui::MainWindow *ui;
    QImage ori_img;    // 原始图像文件
    QImage res_img_1;  // 结果图像文件1
    QImage res_img_2;  // 结果图像文件2

    Algorithm *algorithm;

    int grey_index = -1;

    QList<QAction*> recentFileActionList; // 最近文件列表
    const int maxFileNr = 5; // 最近文件个数

    void loadFile(const QString& fileName);
    void adjustForCurrentFile(const QString& fileName);
    void updateRecentActionList();
};

#endif // MAINWINDOW_H
