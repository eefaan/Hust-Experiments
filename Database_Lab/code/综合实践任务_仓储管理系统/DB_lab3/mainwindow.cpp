#include "mainwindow.h"
#include "ui_mainwindow.h"

static inline qint32 ArrayToInt(QByteArray source);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->login,SIGNAL(clicked()),this,SLOT(on_loginin_clicked()));


    // create a TCP socket
    tcpSocket = new QTcpSocket(this);//创建新的客户端套接字
    connect(tcpSocket,&QTcpSocket::connected,        //连接上之后无论服务器还是客户端都是收到connected信号
        [=](){
            qDebug()<<"connect successfully!";

            // repost to function "Switch"
            qDebug()<<"set tcp read.";
            connect(tcpSocket,&QTcpSocket::readyRead,this,&MainWindow::TCPread);        //一旦服务器发了包，便会收到一个readyraed的信号，和服务器相同的用法
            connect(this,SIGNAL(dataReceived(QByteArray)),this,SLOT(func_switch(QByteArray)));
        }
    );

    link();
    qDebug()<<"tcp_socket conn request sent!";


//    if(tcpSocket->waitForConnected())
//    {
//    //ui->readEdit->setText("成功建立连接");
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::link(){
    QString ip ="127.0.0.1";    //本地回环
    quint16 port = 8888;        //必须用同一个端口
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void MainWindow::TCPread(){
    QByteArray *buffer = new QByteArray();
    qint32 *s = new qint32(0);
    qint32 size = *s;
    while (tcpSocket->bytesAvailable() > 0)
    {
        buffer->append(tcpSocket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                emit dataReceived(data);
            }
        }
    }
}

void MainWindow::func_switch(QByteArray data){
    qDebug()<<"func switch!";
//    QByteArray array = tcpSocket->readAll();
    QByteArray array = data;
    QString strtemp = array;
    qDebug()<<strtemp;

    // save package to cache
    package_cache = array;
    choice_cache = package_cache.section(",",0,0);
    int Choice_int = choice_cache.toInt();        //收到的包为QByteArray格式，将它转换成STring并将第一部分的功能转为int
    switch(Choice_int)
    {
        case 1:proc_response_login(package_cache); break;    //登陆界面_登陆请求
        case 2:buyer_page->proc_response_flash(package_cache); break; //buyer_flash
        case 3:buyer_page->proc_response_submit(package_cache); break; //buyer_submit_response
        case 4:seller_page->proc_response_flash(package_cache); break; //seller_flash
        case 5:seller_page->proc_response_submit(package_cache); break; //seller_submit_response
        case 6:switch(stype){
            case 1:buyer_page->proc_response_gflash(package_cache); break;
            case 2:seller_page->proc_response_gflash(package_cache); break;
            case 3:auditor_page->proc_response_gflash(package_cache); break;
            default: break;
        } break;
        case 7:auditor_page->proc_response_poflash(package_cache); break;//purchase_order_flash
        case 8:auditor_page->proc_response_posubmit(package_cache); break;//purchase_order_submit
        case 9:auditor_page->proc_response_soflash(package_cache); break;//shipment_order_flash
        case 10:auditor_page->proc_response_sosubmit(package_cache); break;//shipment_order_submit
        default: break;
    }
}

void MainWindow::proc_response_login(QString response){
    /* response's construct:
     *     response_type, alarm_message, success_flag, user_type, user_id
     */
    QString section1 = response.section(",",1,1);//get section 2, which is message
    int section2 = response.section(",",2,2).toInt();//get section 3, which is return value, 1means success
    int section3 = response.section(",",3,3).toInt();//get section 4, which is user's type
    int section4 = response.section(",",4,4).toInt();//get section 4, which is user's id

    if(section2==0){// login failed
        msgBox = new QMessageBox("提示",		///--这里是设置消息框标题
            section1,						///--这里是设置消息框显示的内容
            QMessageBox::Critical,							///--这里是在消息框显示的图标
            QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
            QMessageBox::Cancel | QMessageBox::Escape,	///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
            0);														///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮
        msgBox->show();
        return;
    }

    stype = section3;
    sno = section4;
    QString request;

    switch(section3){
        case 1:// purchase control
            // create a page
            buyer_page = new buyer_mw();
            // initial buyer's table
            request = "2,"+QString::number(sno);
            TCPwrite(request);
            // link response to sub_page
            connect(buyer_page,SIGNAL(logout_signal()),this,SLOT(buyer_logout()));//logout button
            connect(buyer_page,SIGNAL(flash_signal()),this,SLOT(buyer_flash()));
            connect(buyer_page,SIGNAL(gflash_signal()),this,SLOT(buyer_gflash()));
            connect(buyer_page,SIGNAL(submit_signal(QString)),this,SLOT(buyer_submit(QString)));
            // hide and show
            this->hide();
            buyer_page->show();
            break;
        case 2:// seller controller
            // create a page
            seller_page = new seller_mw();
            // initial buyer's table
            request = "4,"+QString::number(sno);
            TCPwrite(request);
            // link response to sub_page
            connect(seller_page,SIGNAL(logout_signal()),this,SLOT(seller_logout()));//logout button
            connect(seller_page,SIGNAL(flash_signal()),this,SLOT(seller_flash()));
            connect(seller_page,SIGNAL(gflash_signal()),this,SLOT(seller_gflash()));
            connect(seller_page,SIGNAL(submit_signal(QString)),this,SLOT(seller_submit(QString)));
            // hide and show
            this->hide();
            seller_page->show();
            break;
        case 3:
            // create a page
            auditor_page = new auditor_mw();
            // initial buyer's table
            request = "7,"+QString::number(sno);
            TCPwrite(request);
            // link response to sub_page
            connect(auditor_page,SIGNAL(logout_signal()),this,SLOT(auditor_logout()));//logout button
            connect(auditor_page,SIGNAL(poflash_signal()),this,SLOT(auditor_poflash()));
            connect(auditor_page,SIGNAL(soflash_signal()),this,SLOT(auditor_soflash()));
            connect(auditor_page,SIGNAL(gflash_signal()),this,SLOT(auditor_gflash()));
            connect(auditor_page,SIGNAL(posubmit_signal(QString)),this,SLOT(auditor_posubmit(QString)));
            connect(auditor_page,SIGNAL(sosubmit_signal(QString)),this,SLOT(auditor_sosubmit(QString)));
            // hide and show
            this->hide();
            auditor_page->show();
            break;
        default:
            break;
    }
}



void MainWindow::on_loginin_clicked(){
    QString account = ui->account->text();
    QString password = ui->password->text();
    qDebug()<<"account: "+account;
    qDebug()<<"password: "+password;
    QString str = "1,"+account+","+password;
    TCPwrite(str);

//    QByteArray array = tcpSocket->readAll();
//    QString strtemp = array;
//    qDebug()<<strtemp;
}

void MainWindow::TCPwrite(QString str){
    tcpSocket->write(str.toUtf8().data());
}

// buyer's controler: logout or repost the request
void MainWindow::buyer_logout(){
    buyer_page->hide();
    delete buyer_page;
    ui->account->clear();
    ui->password->clear();
    this->show();
    return;
}
void MainWindow::buyer_flash(){
    // request srv
    QString request = "2,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}
void MainWindow::buyer_gflash(){
    // request srv
    QString request = "6,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}
void MainWindow::buyer_submit(QString request){
    // request srv
    TCPwrite(request+","+QString::number(sno));
    return;
}




// seller's controler: logout or repost the request
void MainWindow::seller_logout(){
    seller_page->hide();
    delete seller_page;
    ui->account->clear();
    ui->password->clear();
    this->show();
    return;
}
void MainWindow::seller_flash(){
    // request srv
    QString request = "4,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}
void MainWindow::seller_gflash(){
    // request srv
    QString request = "6,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}
void MainWindow::seller_submit(QString request){
    // request srv
    TCPwrite(request+","+QString::number(sno));
    return;
}




// auditor's controler: logout or repost the request
void MainWindow::auditor_logout(){
    auditor_page->hide();
    delete auditor_page;
    ui->account->clear();
    ui->password->clear();
    this->show();
    return;
}
void MainWindow::auditor_poflash(){
    // request srv
    QString request = "7,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}
void MainWindow::auditor_posubmit(QString request){
    // request srv
    QString request_s = "8,"+request+","+QString::number(sno)+",";
    TCPwrite(request_s);
    return;
}
void MainWindow::auditor_soflash(){
    // request srv
    QString request = "9,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}
void MainWindow::auditor_sosubmit(QString request){
    // request srv
    QString request_s = "10,"+request+","+QString::number(sno)+",";
    TCPwrite(request_s);
    return;
}
void MainWindow::auditor_gflash(){
    // request srv
    QString request = "6,"+QString::number(sno)+",";
    TCPwrite(request);
    return;
}




qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
