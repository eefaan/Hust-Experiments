#include "mainwindow.h"
#include "ui_mainwindow.h"

static inline QByteArray IntToArray(qint32 source);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cur(0),
    db_ip("localhost"),
    db_port(3306),
    db_name("db_lab"),
    db_account("dblab"),
    db_password("dblab")
{
    ui->setupUi(this);

    // initial button
    ui->button_stop->setEnabled(false);
    ui->button_exp->setEnabled(false);

    // db setting
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(db_ip);
    db.setPort(db_port);
    db.setDatabaseName(db_name);
    db.setUserName(db_account);
    db.setPassword(db_password);
    query = new QSqlQuery(db);
    query_temp = new QSqlQuery(db);

    // connect slots
    connect(ui->button_exp,SIGNAL(clicked()),this,SLOT(export_db()));
    connect(ui->button_start,SIGNAL(clicked()),this,SLOT(start_conn()));
    connect(ui->button_stop,SIGNAL(clicked()),this,SLOT(stop_conn()));

    myMapper = new QSignalMapper();

    // create a TCP socket
    static int index =1;
    setWindowTitle("server:8888");
    //新建套接字
    tcpServer = new QTcpServer(this);
    //listen,监听所有ip地址，用8888端口
    tcpServer->listen(QHostAddress::Any,8888);
    //捕获newconnect信号,如果有一个新的连接，就会收到newConnection的信号
    connect(tcpServer,&QTcpServer::newConnection,
        [=](){
            //得到最近的一个客户端连接
            tcpSocket[cur] = tcpServer->nextPendingConnection();
            //得到客户端的地址和端口.转换为string
            QString ip = tcpSocket[cur]->peerAddress().toString();
            quint16 port = tcpSocket[cur]->peerPort();
            QString temp = QString::fromUtf8("用户%1 地址%2 端口%3 连接成功").arg(index++).arg(ip).arg(port);
            ui->message->append(temp);
            qDebug()<<"connect!";
            connect(tcpSocket[cur],SIGNAL(readyRead()),myMapper,SLOT(map()));
            myMapper->setMapping(tcpSocket[cur],cur);
            cur++;
            // connect(tcpSocket[cur],&QTcpSocket::readyRead,this,&MainWindow::func_switch);
        }
    );
    connect(myMapper, SIGNAL(mapped(int)), this, SLOT(func_switch(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_conn(){
    if(db.open()){
        qDebug()<<"Database: connect successfully!";
        ui->message->append("Database: connect successfully!");
        //connect test
        query->exec("SELECT * FROM T_KSYS");
        while(query->next()){
            QString str_temp = query->value(0).toString();
            qDebug()<<str_temp;
        }
        ui->button_start->setEnabled(false);
        ui->button_stop->setEnabled(true);
        ui->button_exp->setEnabled(true);

    }
    else qDebug() << "Database: connect error!";

    return;
}

void MainWindow::stop_conn(){
    db.close();
    ui->message->append("Database: disconnect successfully!");
    ui->button_start->setEnabled(true);
    ui->button_stop->setEnabled(false);
    ui->button_exp->setEnabled(false);
    return;
}

void MainWindow::export_db(){

}

void MainWindow::func_switch(int i){
    qDebug()<<"func select!";
    QByteArray array = (tcpSocket[i])->readAll();
    tcpSocket[i]->flush();
    QString strtemp = array;
    qDebug()<<strtemp;
    ui->message->append(strtemp);
    Bag[i] = array;
    choice[i] = Bag[i].section(",",0,0);
    int Choice_int = choice[i].toInt();        //收到的包为QByteArray格式，将它转换成STring并将第一部分的功能转为int
    switch(Choice_int){
        case 1: l_login(i); break;    //登陆界面_登陆请求
        case 2: b_flash(i); break;    //采购界面 刷新请求
        case 3: b_submit(i); break;    //采购界面_采购请求
        case 4: s_flash(i); break;    //销售界面_刷新请求
        case 5: s_submit(i); break;    //销售界面_出库请求
        case 6: g_flash(i); break;  //仓库货品刷新
        case 7: a_poflash(i); break;    //审计界面_
        case 8: a_posubmit(i); break;    //审计界面_
        case 9: a_soflash(i); break;    //审计界面_
        case 10: a_sosubmit(i); break;    //审计界面_
        default: break;
    }
}

void MainWindow::l_login(int i){
    // analyse request
    section1[i] = Bag[i].section(",",1,1);
    section2[i] = Bag[i].section(",",2,2);
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("账号%1,密码%2").arg(section1[i]).arg(section2[i]));

    // DB query
    bool flag = false;
    int user_type = 0;
    int user_id = 0;
    query->exec(QString("select * from staff where account = '%1' and password = '%2'").arg(section1[i]).arg(section2[i]));
    while(query->next()){
        qDebug()<<"finded!";
        flag = true;
        user_type = query->value(2).toInt();
        user_id = query->value(0).toInt();
    }
    if(!flag){// login failed
        ui->message->append("login failed.");
        server_write(QString("1,登陆失败,0"), i);
        return;
    }// or login success, make message
    ui->message->append("login success, user's type: "+QString::number(user_type));

    // create response
    server_write(QString("1,登录成功,1,%1,%2").arg(user_type).arg(user_id), i);

    return;
}

void MainWindow::b_flash(int i){
    // analyse request
    section1[i] = Bag[i].section(",",1,1);// users' sno
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("flash request from user(sno): %1").arg(section1[i]));

    // DB query
    // trans to be audi first
    server_write(QString("2,flash_begin,1"), i);
    query->exec(QString("select * from p_order,good where bno = %1 and p_order.ano is null and p_order.gno = good.gno").arg(section1[i]));
    while(query->next()){
        int pono = query->value("pono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
//        int ano = query->value("ano").toInt();// 审批人号
        QDateTime date = query->value("date").toDateTime();//date
        // create response
        server_write(QString("2,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9").
            arg(pono).arg(gno).arg(gnum).arg("未审批").arg("无").arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu), i
        );
    }
    // then trans has been audi
    query->exec(QString("select * from p_order,staff,good where bno = %1 and p_order.ano = staff.sno and p_order.gno = good.gno").arg(section1[i]));
    while(query->next()){
        int pono = query->value("pono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
        QString aname = query->value("sname").toString();// 审批人号 TODO:trans to 姓名
        QDateTime date = query->value("date").toDateTime();//date
        // create response
        server_write(QString("2,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9").
            arg(pono).arg(gno).arg(gnum).arg("已审批").arg(aname).arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu), i
        );
    }
    ui->message->append("flash done.");
    return;
}

void MainWindow::b_submit(int i){
    /* request's construct:
     *     request_type, good_name, good_place, manufacturer, purchase_num, sno
     */

    // analyse request
    section1[i] = Bag[i].section(",",1,1);
    section2[i] = Bag[i].section(",",2,2);
    section3[i] = Bag[i].section(",",3,3);
    section4[i] = Bag[i].section(",",4,4);
    section5[i] = Bag[i].section(",",5,5);
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append("buyer's submit");

    // judge if input is null
    if(section1[i]=="" || section2[i]=="" || section3[i]=="" || section4[i]==""){
        server_write(QString("3,输入不得为空,0"), i);
        return;
    }
    // TODO: judge if input is illegal, such as input a int to gnum
    if(false){
        server_write(QString("3,输入信息有误,0"), i);
        return;
    }

    // DB update
    // query if the good exists
    query->exec(QString("select * from good where gname = '%1' and gplace = '%2' and gmanu = '%3'").
                        arg(section1[i]).
                        arg(section2[i]).
                        arg(section3[i])
    );
    bool flag = false;
    int gno = 0;
    while(query->next()){
        gno = query->value(0).toInt();
        flag = true;
    }
    if(flag){// good has been exist
        query->exec(QString("insert into p_order(bno,gno,gnum,date) values(%1,%2,%3,'%4')").
            arg(section5[i]).arg(gno).arg(section4[i]).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
        );
        // create response
        server_write(QString("3,采购单提交成功,1"), i);
    }
    else{// need to create a new good in TABLE_GOOD
        query->exec(QString("insert into good(gname,gplace,gnum,gmanu) values('%1','%2',%3,'%4')").
            arg(section1[i]).arg(section2[i]).arg(0).arg(section3[i])
        );
        query->exec(QString("select * from good order by id DESC limit 1"));
        while(query->next()){// get the gno
            gno = query->value(0).toInt();
        }
        query->exec(QString("insert into p_order(bno,gno,gnum,date) values(%1,%2,%3,'%4')").
            arg(section5[i]).arg(gno).arg(section4[i]).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
        );
        // create response
        server_write(QString("3,新建货品并提交采购单成功,1"), i);
    }

    return;
}

void MainWindow::s_flash(int i){
    // analyse request
    section1[i] = Bag[i].section(",",1,1);// users' sno
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("flash request from user(sno): %1").arg(section1[i]));

    // DB query
    // trans to be audi first
    server_write(QString("4,flash_begin,1"), i);
    query->exec(QString("select * from s_order,good where sno = %1 and s_order.ano is null and s_order.gno = good.gno").arg(section1[i]));
    while(query->next()){
        int pono = query->value("sono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
//        int ano = query->value("ano").toInt();// 审批人号
        QDateTime date = query->value("date").toDateTime();//date
        // create response
        server_write(QString("4,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9").
            arg(pono).arg(gno).arg(gnum).arg("未审批").arg("无").arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu), i
        );
    }
    // then trans has been audi
    query->exec(QString("select * from s_order,staff,good where s_order.sno = %1 and s_order.ano = staff.sno and s_order.gno = good.gno").arg(section1[i]));
    while(query->next()){
        int pono = query->value("sono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
        QString aname = query->value("sname").toString();// 审批人号 TODO:trans to 姓名
        QDateTime date = query->value("date").toDateTime();//date

        bool en_flag = query->value("has_audi").isNull();// 审批状态
        QString temp_audi;
        if(en_flag){
            temp_audi = "未审批";
        }
        else{
            if(query->value("has_audi").toBool()){
                temp_audi = "已审批";
            }
            else{
                temp_audi = "缺货";
            }
        }

        // create response
        server_write(QString("4,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9").
            arg(pono).arg(gno).arg(gnum).arg(temp_audi).arg(aname).arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu), i
        );
    }
    ui->message->append("flash order done.");
    return;
}

void MainWindow::s_submit(int i){
    /* request's construct:
     *     request_type, good_name, good_place, manufacturer, purchase_num, sno
     */

    // analyse request
    section1[i] = Bag[i].section(",",1,1);
    section2[i] = Bag[i].section(",",2,2);
    section3[i] = Bag[i].section(",",3,3);
    section4[i] = Bag[i].section(",",4,4);
    section5[i] = Bag[i].section(",",5,5);
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append("buyer's submit");

    // judge if input is null
    if(section1[i]=="" || section2[i]=="" || section3[i]=="" || section4[i]==""){
        server_write(QString("5,输入不得为空,0"), i);
        return;
    }
    // TODO: judge if input is illegal, such as input a int to gnum
    if(false){
        server_write(QString("5,输入信息有误,0"), i);
        return;
    }

    // DB update
    // query if the good exists
    query->exec(QString("select * from good where gname = '%1' and gplace = '%2' and gmanu = '%3'").
                        arg(section1[i]).
                        arg(section2[i]).
                        arg(section3[i])
    );
    bool flag = false;
    int gno = 0;
    while(query->next()){
        gno = query->value(0).toInt();
        flag = true;
    }
    if(flag){// good has been exist
        query->exec(QString("insert into s_order(sno,gno,gnum,date) values(%1,%2,%3,'%4')").
            arg(section5[i]).arg(gno).arg(section4[i]).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
        );
        // create response
        server_write(QString("5,采购单提交成功,1"), i);
    }
    else{// need to create a new good in TABLE_GOOD
        // create response
        server_write(QString("5,货物信息不存在,0"), i);
    }

    return;
}

void MainWindow::g_flash(int i){
    // analyse request
    section1[i] = Bag[i].section(",",1,1);// users' sno
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("flash request from user(sno): %1").arg(section1[i]));

    // DB query
    // trans to be audi first
    server_write(QString("6,flash_begin,1"), i);
    query->exec(QString("select * from goods_store"));
    while(query->next()){
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
        bool gen = query->value("gen").toBool();// 缺货标识
        // create response
        server_write(QString("6,flash_item,0,%1,%2,%3,%4,%5,%6").
            arg(gno).arg(gname).arg(gplace).arg(gmanu).arg(gnum).arg(gen?"缺货":"货存充足"), i
        );
    }
    ui->message->append("flash goods done.");
}

void MainWindow::a_poflash(int i){
    // analyse request
    section1[i] = Bag[i].section(",",1,1);// users' sno
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("flash request from user(sno): %1").arg(section1[i]));

    // DB query
    // trans to be audi first
    server_write(QString("7,flash_begin,1"), i);
    query->exec(QString("select * from p_order,good,staff f1 where p_order.bno = f1.sno and p_order.ano is null and p_order.gno = good.gno"));
    while(query->next()){
        int pono = query->value("pono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
//        int ano = query->value("ano").toInt();// 审批人号
        QDateTime date = query->value("date").toDateTime();//date
        QString bname = query->value("sname").toString();

        // create response
        server_write(QString("7,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10").
            arg(pono).arg(gno).arg(gnum).arg("未审批").arg("无").arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu).arg(bname), i
        );
    }
    // then trans has been audi
    query->exec(QString("select f1.sname,f2.sname,p_order.*,good.* from p_order,staff f1,staff f2,good where p_order.bno = f1.sno and p_order.ano = f2.sno and p_order.gno = good.gno"));
    while(query->next()){
        int pono = query->value("pono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
        QString bname = query->value(0).toString();// 申请人
        QString aname = query->value(1).toString();// 审批人
        QDateTime date = query->value("date").toDateTime();//date
        // create response
        server_write(QString("7,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10").
            arg(pono).arg(gno).arg(gnum).arg("已审批").arg(aname).arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu).arg(bname), i
        );
    }
    ui->message->append("flash done.");
    return;
}
void MainWindow::a_soflash(int i){
    // analyse request
    section1[i] = Bag[i].section(",",1,1);// users' sno
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("flash request from user(sno): %1").arg(section1[i]));

    // DB query
    // trans to be audi first
    server_write(QString("9,flash_begin,1"), i);
    query->exec(QString("select * from s_order,good,staff f1 where s_order.sno = f1.sno and s_order.ano is null and s_order.gno = good.gno"));
    while(query->next()){
        int pono = query->value("sono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 出货数
//        bool flag = query->value("has_audi").toBool();// 审批状态
//        int ano = query->value("ano").toInt();// 审批人号
        QDateTime date = query->value("date").toDateTime();//date
        QString sname = query->value("sname").toString();

        // create response
        server_write(QString("9,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10").
            arg(pono).arg(gno).arg(gnum).arg("未审批").arg("无").arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu).arg(sname), i
        );
    }
    // then trans has been audi
    query->exec(QString("select f1.sname,f2.sname,s_order.*,good.* from s_order,staff f1,staff f2,good where s_order.sno = f1.sno and s_order.ano = f2.sno and s_order.gno = good.gno"));
    while(query->next()){
        int pono = query->value("sono").toInt();// 采购单号
        int gno = query->value("gno").toInt();// 货号
        QString gname = query->value("gname").toString();//货品名称
        QString gplace = query->value("gplace").toString();//存放地
        QString gmanu = query->value("gmanu").toString();//生产商
        int gnum = query->value("gnum").toInt();// 进货数
        QString sname = query->value(0).toString();// 申请人
        QString aname = query->value(1).toString();// 审批人
        QDateTime date = query->value("date").toDateTime();//date

        bool en_flag = query->value("has_audi").isNull();// 审批状态
        QString temp_audi;
        if(en_flag){
            temp_audi = "未审批";
        }
        else{
            if(query->value("has_audi").toBool()){
                temp_audi = "已审批";
            }
            else{
                temp_audi = "缺货";
            }
        }

        // create response
        server_write(QString("9,flash_item,0,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10").
            arg(pono).arg(gno).arg(gnum).arg(temp_audi).arg(aname).arg(date.toString("yyyy-MM-dd hh:mm:ss")).arg(gname).arg(gplace).arg(gmanu).arg(sname), i
        );
    }
    ui->message->append("flash done.");
    return;
}
void MainWindow::a_posubmit(int i){// func id: 8
    // func_id, 申请ID, 审批人ID

    // analyse request
    section1[i] = Bag[i].section(",",2,2);// users' sno
    section2[i] = Bag[i].section(",",1,1);// pono
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("po_submit from user(sno): %1").arg(section1[i]));

    // DB query
    query->exec(QString("select * from p_order where p_order.pono = %1").arg(section2[i]));
    int gno=0;
    int gnum=0;
    while(query->next()){
        gno = query->value("gno").toInt();
        gnum = query->value("gnum").toInt();
    }
    // update TABLE p_order
    query->exec(QString("update p_order set ano = %1, has_audi = %2 where pono = %3").arg(section1[i]).arg("true").arg(section2[i]));
    // update TABLE good
    query->exec(QString("update good set gnum = gnum + %1 where gno = %2").arg(gnum).arg(gno));

    int flag=0;
    // proc: lack of good
    query->exec(QString("select * from good where gno = %1").arg(gno));
    int total=0;
    while(query->next()){
        total = query->value("gnum").toInt();
    }
    query->exec(QString("select * from s_order where gno = %1 and has_audi = 0 order by date").arg(gno));
    while(query->next()){
        int out_num = query->value("gnum").toInt();
        int sono = query->value("sono").toInt();
        if(total>=out_num){
            flag=1;
            total -= out_num;
            query_temp->exec(QString("update good set gnum = %1 where gno = %2").arg(total).arg(gno));
            query_temp->exec(QString("update s_order set has_audi = 1 where sono = %1").arg(sono));
        }
        else{
            break;
        }
    }
    // create response
    if(flag) server_write(QString("8,批准成功且缺货状态的出库申请被满足"),i);
    else server_write(QString("8,批准成功"),i);
}

void MainWindow::a_sosubmit(int i){
    // func_id, 申请ID, 审批人ID
    // analyse request
    section1[i] = Bag[i].section(",",2,2);// users' sno
    section2[i] = Bag[i].section(",",1,1);// pono
    ui->message->append("request from socket: "+QString::number(i));
    ui->message->append(QString("po_submit from user(sno): %1").arg(section1[i]));
    // DB query
    query->exec(QString("select * from s_order where s_order.sono = %1").arg(section2[i]));
    int gno = 0;
    int gnum = 0;
    while(query->next()){
        gno = query->value("gno").toInt();
        gnum = query->value("gnum").toInt();
    }
    //check the num from TABLE good
    query->exec(QString("select * from good where gno = %1").arg(gno));
    int store_num = 0;
    while(query->next()){
        store_num = query->value("gnum").toInt();
        if(store_num>=gnum){//库存满足要求
            query->exec(QString("update good set gnum = gnum - %1 where gno = %2").arg(gnum).arg(gno));
            query->exec(QString("update s_order set ano = %1, has_audi = 1 where sono = %2").arg(section1[i]).arg(section2[i]));
            server_write(QString("10,批准成功"),i);
        }
        else{//否则记录缺货
            query->exec(QString("update s_order set ano = %1, has_audi = 0 where sono = %2").arg(section1[i]).arg(section2[i]));
            server_write(QString("10,库存不足-记录缺货"),i);
        }
    }
}

void MainWindow::server_write(QString str, int i){
//    tcpSocket[i]->write(str.toUtf8().data());
    tcpSocket[i]->write(IntToArray(str.toUtf8().size())); //write size of data
    tcpSocket[i]->write(str.toUtf8()); //write the data itself
//    while(!tcpSocket[i]->waitForBytesWritten()){}
    return;
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    // Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
