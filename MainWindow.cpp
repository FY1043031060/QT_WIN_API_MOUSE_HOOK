#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPoint>
static HHOOK hHook;

LRESULT __stdcall MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MOUSEHOOKSTRUCT MyMouseHookStruct =*(MOUSEHOOKSTRUCT*)lParam;
    if(nCode < 0)
    {
        return CallNextHookEx(hHook,nCode,wParam,lParam);
    }else{
        QString strCaption = QString("x = ") + MyMouseHookStruct.pt.x + QString("  y = ") + MyMouseHookStruct.pt.y;
        qDebug()<<"Mouse Point" << QPointF((float)MyMouseHookStruct.pt.x,(float)MyMouseHookStruct.pt.y);
        qDebug() << strCaption;
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_button = new QPushButton(this);
    QLabel* label = new QLabel(this);
    QHBoxLayout* pLayout = new QHBoxLayout(this);
    pLayout->addWidget(label);
    pLayout->addWidget(m_button);
    centralWidget()->setLayout(pLayout);
    connect(m_button,&QPushButton::clicked,this,[&](){
        if(hHook == 0)
        {

            //这里挂节钩子
            HINSTANCE instr=  (HINSTANCE)GetCurrentProcess();
            qDebug()<< "CurrentProcess" << instr;
            hHook = SetWindowsHookEx(WH_MOUSE_LL,MouseHookProc,NULL, 0);
            if(hHook == 0)
            {
                qDebug()<<QString("SetWindowsHookEx Failed");
                return;
            }
            m_button->setText("OFF");
        }
        else
        {
            bool ret = UnhookWindowsHookEx(hHook);
            if(ret == false)
            {
                qDebug()<<QString("UnhookWindowsHookEx Failed");
                return;
            }
            hHook = 0;
            m_button->setText("ON");
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

