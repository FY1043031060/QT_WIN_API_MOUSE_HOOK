#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Windows.h>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
private:
    //HHOOK hHook;
    QPushButton* m_button;
};

#endif // MAINWINDOW_H
