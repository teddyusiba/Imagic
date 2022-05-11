#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    // 设置窗口名称和图标
    setWindowIcon(QIcon(":/pic/logo.png"));
    setWindowTitle("Imagic");

    // 设置窗口大小
    setFixedSize(1154, 744);


    // 侧边栏初始化，图标大小为50*50
    ui->taskBtn_1->setIconSize(QSize(50, 50));
    ui->taskBtn_1->setIcon(QIcon(":/pic/task_1.png"));
    ui->taskBtn_1->setText(QStringLiteral("欢迎"));
    ui->taskBtn_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->taskBtn_2->setIconSize(QSize(50, 50));
    ui->taskBtn_2->setIcon(QIcon(":/pic/task_2.png"));
    ui->taskBtn_2->setText(QStringLiteral("图像恢复"));
    ui->taskBtn_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->taskBtn_3->setIconSize(QSize(50, 50));
    ui->taskBtn_3->setIcon(QIcon(":/pic/task_3.png"));
    ui->taskBtn_3->setText(QStringLiteral("灰度图像"));
    ui->taskBtn_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // 默认显示的子窗口
    ui->stackedWidget->setCurrentWidget(ui->page_0);

    // 切换显示子窗口
    connect(ui->taskBtn_1, &QToolButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_0);
    });
    connect(ui->taskBtn_2, &QToolButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_1);
    });
    connect(ui->taskBtn_3, &QToolButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    });

    // 建立打开最近文件菜单项
    QAction* recentFileAction = nullptr;
    for(auto i = 0; i < maxFileNr; ++i){
        recentFileAction = new QAction(this);
        recentFileAction->setVisible(false);
        connect(recentFileAction, &QAction::triggered, this, [=]()
        {
            loadFile(recentFileAction->data().toString());
        });
        recentFileActionList.append(recentFileAction);
    }

    for(auto i = 0; i < maxFileNr; ++i)
        ui->recent_menu->addAction(recentFileActionList.at(i));

    updateRecentActionList();

    // 1.创建子线程对象
    MyThread *greyThread = new MyThread; // 灰度处理线程
    MyThread *tnnrThread = new MyThread; // 图像恢复线程

    connect(this, &MainWindow::grey, greyThread, &MyThread::greyPara);

    // 2. 启动子线程
    connect(ui->runBtn_2, &QPushButton::clicked, this, [=]()
    {
        emit grey(grey_index, ori_img, ui->label_result_2);
        greyThread->start(); // 相当于让run开始运行
    });

    // 3. 接受子线程的数据
    connect(greyThread, &MyThread::outPut, this, [=](QImage res2)
    {
        res_img_2 = res2;
    });


    // 4. 线程对象的析构
    connect(this, &MainWindow::destroyed, this, [=]()
    {
        greyThread->quit();
        greyThread->wait();
        greyThread->deleteLater();

        tnnrThread->quit();
        tnnrThread->wait();
        tnnrThread->deleteLater();
    });

    // 主界面退出按钮
    connect(ui->closeBtn, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 打开拖入图像
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->urls()[0].fileName().right(3).compare("jpg") ||
            event->mimeData()->urls()[0].fileName().right(3).compare("png"))
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();      // 获取MIME数据

    if(mimeData->hasUrls()){                            // 如果数据中包含URL
        QList<QUrl> urlList = mimeData->urls();         // 获取URL列表
        // 将其中第一个URL表示为本地文件路径
        QString fileName = urlList.at(0).toLocalFile();

        loadFile(fileName);
    }
}

void MainWindow::on_add_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open File"), "e:\\QTDemo\\Imagic\\pic",
                tr("Images (*.png *.jpg);"));
//    qDebug() << fileName;

    loadFile(fileName);
}

void MainWindow::on_save_file_triggered()
{
    if (ui->stackedWidget->currentWidget() == ui->page_1)
    {
        if (res_img_1.isNull())
        {
            QMessageBox::warning(this,"警告","当前暂未有任何输出图片!");
        }
        else
        {
            QString fileName = QFileDialog::getSaveFileName(
                        this, tr("Open File"), "e:\\QTDemo\\Imagic\\pic",
                        tr("Images (*.png *.jpg);"));
            res_img_1.save(fileName);
        }
    }
    else if (ui->stackedWidget->currentWidget() == ui->page_2)
    {
        if (res_img_2.isNull())
        {
            QMessageBox::warning(this,"警告","当前界面暂未有任何输出图片!");
        }
        else
        {
            QString fileName = QFileDialog::getSaveFileName(
                        this, tr("Open File"), "e:\\QTDemo\\Imagic\\pic",
                        tr("Images (*.png *.jpg);"));
            res_img_2.save(fileName);
        }
    }
    else return;
}

void MainWindow::on_quit_triggered()
{
    this->close();
}

void MainWindow::on_help_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/teddyusiba/Imagic/blob/master/README.md")));
}

void MainWindow::on_question_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/teddyusiba/Imagic/issues")));
}

void MainWindow::on_about_us_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/teddyusiba/Imagic")));
}

void MainWindow::on_about_QT_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://www.qt.io/zh-cn/")));
}

void MainWindow::loadFile(const QString &fileName)
{
    if (!(ori_img.load(fileName)))
    {
        QMessageBox::warning(this,"警告","图片打开失败!");
        return;
    }
    QImage output = ori_img.scaled(ui->label_input_1->width(), ui->label_input_1->height(), Qt::KeepAspectRatio);
    ui->label_input_1->setPixmap(QPixmap::fromImage(output));
    ui->label_input_2->setPixmap(QPixmap::fromImage(output));

    adjustForCurrentFile(fileName); // 调整当前 最近文件列表
}

void MainWindow::adjustForCurrentFile(const QString &fileName)
{
    QSettings settings;
    QStringList recentFileNames = settings.value("recentFiles").toStringList();
    recentFileNames.removeAll(fileName);
    recentFileNames.prepend(fileName);
    while (recentFileNames.size() > maxFileNr)
        recentFileNames.removeLast();
    settings.setValue("recentFiles", recentFileNames);

    updateRecentActionList();
}

void MainWindow::updateRecentActionList()
{
    QSettings settings;
    QStringList recentFileNames = settings.value("recentFiles").toStringList();

    auto itEnd = 0;
    if(recentFileNames.size() <= maxFileNr)
        itEnd = recentFileNames.size();
    else
        itEnd = maxFileNr;

    for (auto i = 0; i < itEnd; ++i) {
        QString strippedName = QFileInfo(recentFileNames.at(i)).fileName();
        recentFileActionList.at(i)->setText(strippedName);
        recentFileActionList.at(i)->setData(recentFileNames.at(i));
        recentFileActionList.at(i)->setVisible(true);
    }

    for (auto i = itEnd; i < maxFileNr; ++i)
        recentFileActionList.at(i)->setVisible(false);
}

void MainWindow::on_radioButton_clicked()
{
    grey_index = 1;
}

void MainWindow::on_radioButton_2_clicked()
{
    grey_index = 2;
}

void MainWindow::on_radioButton_3_clicked()
{
    grey_index = 3;
}

void MainWindow::on_radioButton_4_clicked()
{
    grey_index = 4;
}
