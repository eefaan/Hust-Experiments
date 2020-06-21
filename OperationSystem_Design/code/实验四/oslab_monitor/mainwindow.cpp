#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hostname_file("/proc/sys/kernel/hostname"),
    uptime_file("/proc/uptime"),
    ostype_file("/proc/sys/kernel/ostype"),
    osrelease_file("/proc/sys/kernel/osrelease"),
    cpuinfo_file("/proc/cpuinfo"),
    stat_file("/proc/stat"),
    meminfo_file("/proc/meminfo")
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // set timer
    QTimer *mytimer = new QTimer(this);
    mytimer->start(1000);

    // set status
    connect(mytimer, SIGNAL(timeout()), this, SLOT(set_status_time()));
    connect(mytimer, SIGNAL(timeout()), this, SLOT(set_status_cpu_usage()));
    connect(mytimer, SIGNAL(timeout()), this, SLOT(set_status_memory_usage()));
    connect(ui->button_shut, SIGNAL(clicked()), this, SLOT(shut()));
    connect(ui->button_reboot, SIGNAL(clicked()), this, SLOT(reboot()));

    // set PAGE: topview
    connect(mytimer, SIGNAL(timeout()), this, SLOT(send_signals()));
    connect(this, SIGNAL(sys_info(int,QString)), this, SLOT(set_sys_info(int,QString)));

    // set PAGE: process
    connect(mytimer, SIGNAL(timeout()), this, SLOT(set_process_list()));
    connect(ui->proc_shut, SIGNAL(clicked()), this, SLOT(process_shut()));
    connect(ui->proc_creat, SIGNAL(clicked()), this, SLOT(process_creat()));
    connect(ui->Edit_pid, SIGNAL(textEdited(QString)), this, SLOT(search_pid(QString)));

    // initial graph
    for (int i=0; i<100; i++){
        cpu_num[i]=0;
        mem_num[i]=0;
        swap_num[i]=0;
    }


    // show graph
    connect(mytimer, SIGNAL(timeout()), this, SLOT(graph_cpu()));
    connect(mytimer, SIGNAL(timeout()), this, SLOT(graph_memory()));
    connect(mytimer, SIGNAL(timeout()), this, SLOT(graph_swap()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shut()
{
    QProcess process;
    process.startDetached("shutdown -h now");
}

void MainWindow::reboot()
{
    QProcess process;
    process.startDetached("reboot");
}

void MainWindow::send_signals()
{
    QString msg="123";
    QString tmp;
    std::string patterm{""};
    std::regex re(patterm);
    std::smatch sm;
    std::string log;

    // set_pc_name
    QFile file(hostname_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"open file error: hostname_file";
        return;
    }
    msg = file.readAll();
    patterm = ".*";
    re = std::regex(patterm);
    log = msg.toUtf8().constData();
    regex_search(log, sm, re);
    msg = QString::fromStdString(sm.str());
//    qDebug()<<msg;
    emit sys_info(0,msg);
    file.close();




    // set_sys_time
    file.setFileName(uptime_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"open file error: uptime_file";
        return;
    }
    msg = file.readAll();
    patterm = "\\d*";
    re = std::regex(patterm);
    log = msg.toUtf8().constData();
    regex_search(log, sm, re);
    log = sm.str();
    time_t run = atoi(log.c_str());
    tm *ltm = localtime(&run);
    msg.setNum(-8+ltm->tm_hour);
    msg+=':';
    msg+=tmp.setNum(ltm->tm_min);
    msg+=':';
    msg+=tmp.setNum(ltm->tm_sec);
//    qDebug()<<msg;
    emit sys_info(2,msg);
    // set_boot_time
    time_t now = time(0);
    time_t boot = now - run;
    ltm = localtime(&boot);
    msg.setNum(1900+ltm->tm_year);
    msg+='.';
    msg+=tmp.setNum(1+ltm->tm_mon);
    msg+='.';
    msg+=tmp.setNum(ltm->tm_mday);
    msg+=' ';
    msg+=tmp.setNum(ltm->tm_hour);
    msg+=':';
    msg+=tmp.setNum(ltm->tm_min);
//    msg+=':';
//    msg+=tmp.setNum(ltm->tm_sec);
//    qDebug()<<msg;
    emit sys_info(1,msg);
    file.close();



    // set_os_version
    file.setFileName(ostype_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"open file error: ostype_file";
        return;
    }
    msg = file.readAll();
    patterm = ".*";
    re = std::regex(patterm);
    log = msg.toUtf8().constData();
    regex_search(log, sm, re);
    msg = QString::fromStdString(sm.str());
    file.close();
    file.setFileName(osrelease_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"open file error: osrelease_file";
        return;
    }
    msg += ' ';
    msg += file.readAll();
    patterm = ".*";
    re = std::regex(patterm);
    log = msg.toUtf8().constData();
    regex_search(log, sm, re);
    msg = QString::fromStdString(sm.str());
//    qDebug()<<msg;
    emit sys_info(3,msg);
    file.close();


    // set_cpu_info
    file.setFileName(cpuinfo_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"open file error: cpuinfo_file";
        return;
    }
    msg = file.readAll();
    log = msg.toUtf8().constData();
    patterm = "model[\\s]name[\\s]*:\\s";
    re = std::regex(patterm);
    if(regex_search(log, sm, re)){
        patterm = ".*";
        re = std::regex(patterm);
        std::string temp(sm.suffix());
        regex_search(temp,sm,re);
        emit sys_info(4,QString::fromStdString(sm.str()));
    }

    patterm = "cpu[\\s]MHz[\\s]*:\\s";
    re = std::regex(patterm);
    if(regex_search(log, sm, re)){
        patterm = ".*";
        re = std::regex(patterm);
        std::string temp(sm.suffix());
        regex_search(temp,sm,re);
        emit sys_info(5,QString::fromStdString(sm.str()));
    }
    file.close();

    return;
}


void MainWindow::set_sys_info(int row_num, QString Msg)
{
    QTableWidgetItem *item = new QTableWidgetItem(Msg);
    item->setFlags(item->flags() & (~Qt::ItemIsSelectable));
    ui->tableWidget->setItem(row_num,0,item);
    // 设置单元格不可编辑
//    this->item->setFlags(this->item->flags() & (~Qt::ItemIsEditable));
    // 设置单元格不可选择
//    this->item->setFlags(this->item->flags() & (~Qt::ItemIsSelectable));
}

void MainWindow::set_status_time()
{
    QString str="";
    QString tmp="";
    time_t now = time(0);
    tm *ltm  = localtime(&now);
    str.setNum(1900+ltm->tm_year);
    str+='.';
    str+=tmp.setNum(1+ltm->tm_mon);
    str+='.';
    str+=tmp.setNum(ltm->tm_mday);
    str+=' ';
    str+=tmp.setNum(ltm->tm_hour);
    str+=':';
    str+=tmp.setNum(ltm->tm_min);
    str+=':';
    str+=tmp.setNum(ltm->tm_sec);
    ui->label_now->setText("Time: "+str);
}

void MainWindow::set_status_cpu_usage()
{
    QString str="";
    calcu_usage_cpu cpu("/proc/stat");
//    str = QString::fromStdString(cpu.show_usage(this->cpu_n));
    str = QString::fromStdString(cpu.show_usage(cpu_n));
    ui->label_cpu->setText(str);
}

void MainWindow::set_status_memory_usage()
{
    QString str="";
    calcu_usage_memory mem("/proc/meminfo");
    str = QString::fromStdString(mem.show_usage(mem_n,swap_n));
    ui->label_memory->setText(str);
}

void MainWindow::set_process_list()
{
    this->cell_row = ui->table_proc->currentRow();
    this->cell_column = ui->table_proc->currentColumn();
//    ui->table_proc->clear();
    ui->table_proc->setRowCount(0); //rst
    ui->table_proc->setSortingEnabled(false);
    ui->table_proc->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_proc->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->table_proc->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

    QString tempStr; //读取文件信息字符串
    QFile tempFile; //用于打开系统文件
    QDir qd("/proc");
    QStringList qsList = qd.entryList();
    QString qs = qsList.join("\n");
    QString id_of_pro;
    bool ok;
    int find_start = 3;
    int a, b;
    int nProPid; //进程PID
    int number_of_sleep = 0, number_of_run = 0, number_of_zombie = 0;
    int totalProNum = 0; //进程总数
    QString proName; //进程名
    QString proState; //进程状态
    QString proPri; //进程优先级
    QString proMem; //进程占用内存

    //循环读取进程
    while (1)
    {
        //获取进程PID
        a = qs.indexOf("\n", find_start);
        b = qs.indexOf("\n", a+1);
        find_start = b;
        id_of_pro = qs.mid(a+1, b-a-1);
        totalProNum++;
        nProPid = id_of_pro.toInt(&ok, 10);
        if(!ok)
        {
            break;
        }

        //打开PID所对应的进程状态文件
        tempFile.setFileName("/proc/" + id_of_pro + "/stat");
        if ( !tempFile.open(QIODevice::ReadOnly) )
        {
//            QMessageBox::warning(this, tr("warning"), tr("The pid stat file can not open!"), QMessageBox::Yes);
            return;
        }
        tempStr = tempFile.readLine();
        if (tempStr.length() == 0)
        {
            break;
        }
        a = tempStr.indexOf("(");
        b = tempStr.indexOf(")");
        proName = tempStr.mid(a+1, b-a-1);
        proName.trimmed(); //删除两端的空格
        proState = tempStr.section(" ", 2, 2);
        proPri = tempStr.section(" ", 17, 17);
        proMem = tempStr.section(" ", 22, 22);
        switch ( proState.at(0).toLatin1() )
        {
        case 'S':   number_of_sleep++; break; //Sleep
        case 'R':   number_of_run++; break; //Running
        case 'Z':   number_of_zombie++; break; //Zombie
        default :   break;
        }

        // set a record
        int rowIndex = ui->table_proc->rowCount();
        ui->table_proc->setRowCount(rowIndex + 1);//总行数增加1
        ui->table_proc->setRowHeight(rowIndex, 24);//设置行的高度

        QTableWidgetItem *item = new QTableWidgetItem(id_of_pro);
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table_proc->setItem(rowIndex,0,item);
        item = new QTableWidgetItem(proName);
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table_proc->setItem(rowIndex,1,item);
        item = new QTableWidgetItem(proState);
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table_proc->setItem(rowIndex,2,item);
        item = new QTableWidgetItem(proPri);
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table_proc->setItem(rowIndex,3,item);
        item = new QTableWidgetItem(proMem);
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table_proc->setItem(rowIndex,4,item);
        tempFile.close();//关闭该PID进程的状态文件
    }
    QString temp;
    temp = "Proc_Num: "+QString::number(totalProNum, 10);
    ui->label_pNum->setText(temp);
    temp = "Running: "+QString::number(number_of_run, 10);
    ui->label_pRun->setText(temp);
    temp = "Sleeping: "+QString::number(number_of_sleep, 10);
    ui->label_pSleep->setText(temp);
    temp = "Zombie: "+QString::number(number_of_zombie, 10);
    ui->label_pZombie->setText(temp);
    ui->table_proc->setSortingEnabled(true);
    if(cell_row!=-1)
        ui->table_proc->setCurrentCell(this->cell_row,this->cell_column);
}

void MainWindow::process_shut()
{
    QProcess process;
    int row = ui->table_proc->currentRow();
    QTableWidgetItem *item = ui->table_proc->item(row,0);
    qDebug()<<item->text();
    process.startDetached("kill -9 "+item->text());
    process.kill();
}

void* a_new_thread(void* args)
{
//    execv();
    qDebug()<<"new thread";
    QProcess process;
    process.startDetached("/home/parallels/build-oslab_3wins-Desktop_Qt_5_0_2_GCC_64bit-Debug/oslab_3wins");
    pthread_exit(NULL);
    qDebug()<<"thread dead";
    return 0;
}


void MainWindow::process_creat()
{
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids;
    //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    int ret = pthread_create(&tids, NULL, a_new_thread, NULL);
    if (ret != 0)
    {
       qDebug() << "pthread_create error: error_code=" << ret << endl;
    }
}

void MainWindow::search_pid(QString text)
{
    qDebug()<<text;
    if(text.isEmpty()){
        this->cell_row=-1;
        this->cell_column=-1;
        return;
    }
    QList<QTableWidgetItem *> list_item;
//    list_item = ui->table_proc->findItems(text,Qt::MatchExactly);
//    if (list_item.isEmpty()) return;// no match
//    QTableWidgetItem *item = list_item.first();
    int rows = ui->table_proc->rowCount();
    bool founded = false;
    for(int i = 0; i < rows; ++i)
    {
        if(ui->table_proc->item(i, 0)->text() == text)
        {
            founded = true;
            this->cell_row=i;
            this->cell_column=0;
            ui->table_proc->setCurrentCell(this->cell_row,this->cell_column);
            break;
        }
    }
    if(!founded)
    {
        //we didn't find our value, so we return
        this->cell_row=-1;
        this->cell_column=-1;
        return;
    }
}

void MainWindow::graph_cpu()
{
    //设置画布颜色
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    ui->widget_cpu->setBackground(plotGradient);

    //设置坐标颜色/坐标名称颜色
    ui->widget_cpu->xAxis->setLabelColor(Qt::white);//文字颜色
    ui->widget_cpu->yAxis->setLabelColor(Qt::white);
    ui->widget_cpu->xAxis->setTickLabelColor(Qt::white);//坐标轴数字颜色
    ui->widget_cpu->yAxis->setTickLabelColor(Qt::white);
    ui->widget_cpu->xAxis->setBasePen(QPen(Qt::white, 1));//坐标轴颜色及宽度
    ui->widget_cpu->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget_cpu->xAxis->setTickPen(QPen(Qt::white, 1));//主刻度
    ui->widget_cpu->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_cpu->xAxis->setSubTickPen(QPen(Qt::white, 1));//副刻度
    ui->widget_cpu->yAxis->setSubTickPen(QPen(Qt::white, 1));

    //设置属性可缩放，移动等
//    CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
//                                     QCP::iSelectLegend | QCP::iSelectPlottables);

//    QTime t;
//    t=QTime::currentTime();
//    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
//    n=qrand()%50;

    QVector<double> temp(100);
    QVector<double> temp1(100);


    for(int i=0; i<99; i++)
    {
        cpu_num[i]=cpu_num[i+1];
    }
    cpu_num[99]=cpu_n;
//    for(int i=0;i<120;i++){
//        temp[i]=i;
//    }
    for(int i=0;i<100;i++)
    {
        temp[i] = i;
        temp1[i] = cpu_num[i];
    }
    ui->widget_cpu->addGraph();
    ui->widget_cpu->graph(0)->setPen(QPen(Qt::green));
    ui->widget_cpu->graph(0)->setData(temp,temp1);

    ui->widget_cpu->xAxis->setLabel("time");
    ui->widget_cpu->yAxis->setLabel("rate");

    ui->widget_cpu->xAxis->setRange(0,100);
    ui->widget_cpu->yAxis->setRange(0,100);
    ui->widget_cpu->replot();
}

void MainWindow::graph_memory()
{
    //设置画布颜色
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    ui->widget_mem->setBackground(plotGradient);

    //设置坐标颜色/坐标名称颜色
    ui->widget_mem->xAxis->setLabelColor(Qt::white);//文字颜色
    ui->widget_mem->yAxis->setLabelColor(Qt::white);
    ui->widget_mem->xAxis->setTickLabelColor(Qt::white);//坐标轴数字颜色
    ui->widget_mem->yAxis->setTickLabelColor(Qt::white);
    ui->widget_mem->xAxis->setBasePen(QPen(Qt::white, 1));//坐标轴颜色及宽度
    ui->widget_mem->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget_mem->xAxis->setTickPen(QPen(Qt::white, 1));//主刻度
    ui->widget_mem->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_mem->xAxis->setSubTickPen(QPen(Qt::white, 1));//副刻度
    ui->widget_mem->yAxis->setSubTickPen(QPen(Qt::white, 1));

    //设置属性可缩放，移动等
//    CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
//                                     QCP::iSelectLegend | QCP::iSelectPlottables);

//    QTime t;
//    t=QTime::currentTime();
//    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
//    n=qrand()%50;

    QVector<double> temp(100);
    QVector<double> temp1(100);


    for(int i=0; i<99; i++)
    {
        mem_num[i]=mem_num[i+1];
    }
    mem_num[99]=mem_n;
//    for(int i=0;i<120;i++){
//        temp[i]=i;
//    }
    for(int i=0;i<100;i++)
    {
        temp[i] = i;
        temp1[i] = mem_num[i];
    }
    ui->widget_mem->addGraph();
    ui->widget_mem->graph(0)->setPen(QPen(Qt::green));
    ui->widget_mem->graph(0)->setData(temp,temp1);

    ui->widget_mem->xAxis->setLabel("time");
    ui->widget_mem->yAxis->setLabel("rate");

    ui->widget_mem->xAxis->setRange(0,100);
    ui->widget_mem->yAxis->setRange(0,100);
    ui->widget_mem->replot();
}

void MainWindow::graph_swap()
{
    //设置画布颜色
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    ui->widget_swap->setBackground(plotGradient);

    //设置坐标颜色/坐标名称颜色
    ui->widget_swap->xAxis->setLabelColor(Qt::white);//文字颜色
    ui->widget_swap->yAxis->setLabelColor(Qt::white);
    ui->widget_swap->xAxis->setTickLabelColor(Qt::white);//坐标轴数字颜色
    ui->widget_swap->yAxis->setTickLabelColor(Qt::white);
    ui->widget_swap->xAxis->setBasePen(QPen(Qt::white, 1));//坐标轴颜色及宽度
    ui->widget_swap->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget_swap->xAxis->setTickPen(QPen(Qt::white, 1));//主刻度
    ui->widget_swap->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_swap->xAxis->setSubTickPen(QPen(Qt::white, 1));//副刻度
    ui->widget_swap->yAxis->setSubTickPen(QPen(Qt::white, 1));

    //设置属性可缩放，移动等
//    CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
//                                     QCP::iSelectLegend | QCP::iSelectPlottables);

//    QTime t;
//    t=QTime::currentTime();
//    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
//    n=qrand()%50;

    QVector<double> temp(100);
    QVector<double> temp1(100);


    for(int i=0; i<99; i++)
    {
        swap_num[i]=swap_num[i+1];
    }
    swap_num[99]=swap_n;
//    for(int i=0;i<120;i++){
//        temp[i]=i;
//    }
    for(int i=0;i<100;i++)
    {
        temp[i] = i;
        temp1[i] = swap_num[i];
    }
    ui->widget_swap->addGraph();
    ui->widget_swap->graph(0)->setPen(QPen(Qt::green));
    ui->widget_swap->graph(0)->setData(temp,temp1);

    ui->widget_swap->xAxis->setLabel("time");
    ui->widget_swap->yAxis->setLabel("rate");

    ui->widget_swap->xAxis->setRange(0,100);
    ui->widget_swap->yAxis->setRange(0,100);
    ui->widget_swap->replot();
}
