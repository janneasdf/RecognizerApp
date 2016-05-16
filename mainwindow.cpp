#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitorview.h"
#include "monitor.h"
#include <memory>

using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Monitor* monitor = new Monitor(this);
    MonitorView* monitorView = new MonitorView(this);
    monitorView->initialize(monitor,
                            ui->messageBrowser,
                            ui->clearMessagesButton,
                            ui->toggleConnectionButton);

}

MainWindow::~MainWindow()
{
    delete ui;
}
