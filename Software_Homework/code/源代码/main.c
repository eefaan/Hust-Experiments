#include "class.h"

unsigned long ul;
int VegeCount;
int PlantCount;

int main()
{
    COORD size = {SCR_COL, SCR_ROW};              /*窗口缓冲区大小*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* 获取标准输出设备句柄*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* 获取标准输入设备句柄*/

    SetConsoleTitle(gp_sys_name);                 /*设置窗口标题*/
    SetConsoleScreenBufferSize(gh_std_out, size); /*设置窗口缓冲区大小80*25*/

    LoadData();                   /*数据加载*/
    InitInterface();              /*界面初始化*/
    RunSys();             /*系统功能模块的选择及运行*/
    CloseSys();            /*退出系统*/

    return 0;
}

/**
 * 函数名称: LoadData
 * 函数功能: 将四类基础数据和课堂数据从数据文件载入到内存缓冲区和十字链表中.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, 功能函数中除了函数ExitSys的返回值可以为FALSE外,
 *           其他函数的返回值必须为TRUE.
 *
 * 调用说明: 为了能够以统一的方式调用各功能函数, 将这些功能函数的原型设为
 *           一致, 即无参数且返回值为BOOL. 返回值为FALSE时, 结束程序运行.
 */
BOOL LoadData()
{
    int Re = 0;
    Re = CreatList();
    gc_sys_state |= Re;
    gc_sys_state &= ~(1 + 2 + 4 + 8 + 16 - Re);
    if (gc_sys_state < (1 | 2 | 4 | 8 | 16))
    {  /*数据加载提示信息*/
        printf("\n系统基础数据不完整!\n");
        printf("\n按任意键继续...\n");
    }
    printf("\n按任意键进入主界面...\n");
    getch();

    return TRUE;
}

/**
 * 函数名称: CreatList
 * 函数功能: 从数据文件读取基础数据, 并存放到所创建的十字链表中.
 * 输入参数: 无
 * 输出参数: phead 主链头指针的地址, 用来返回所创建的十字链.
 * 返 回 值: int型数值, 表示链表创建的情况.
 *           0  空链，无数据
 *           1  已加载课程信息数据，无其余信息数据
 *           2  已加载课程信息和教室信息数据，无其余信息数据
 *           4  已加载课程信息、教室信息和教师信息数据，无其余信息数据
 *           8  已加载课程信息、教室信息、教师信息和班级数据，无课堂信息数据
 *           16 已加载全部数据
 *
 * 调用说明:
 */
int CreatList()
{
    int i=0;//计数器
    int count=0;//计数器
    float credits;//学分
    int hours;//学时
    int weekday;//周几
    int class_num;//班级个数
    char subject_name[40],building[20],room_name[20],
         teacher_name[20],position[20],class_name[40];
         //课程名 教学楼 教室名
         //教师名 职位 班级名
    char lesson[100];//节数
    char week[100];//周数

    TEACHER_NODE *teacher_temp = teacher_head, *pTeacherNode,*pteacher_node;
    SUBJECT_NODE *subject_temp = subject_head, *pSubjectNode,*psubject_node;
    CLASS_NODE *class_temp = class_head, *pClassNode,*pclass_node;
    ROOM_NODE *room_temp = room_head, *pRoomNode,*proom_node;
    COURSE_NODE *course_temp = course_head, *pCourseNode;

    FILE *pFile;
    int find;
    int re = 0;

    //读取课程信息
    if ((pFile = fopen(gp_subject_info_filename, "rb")) == NULL)
    {
        printf("课程信息数据文件打开失败!\n");
        return re;
    }
    printf("课程信息数据文件打开成功!\n");
    /*从数据文件中读课程信息数据，存入以先进先出方式建立的课程信息链中*/
    while (fscanf(pFile,"%s %f %d",subject_name,&credits,&hours)!=EOF)
    {
        //新节点赋值
        pSubjectNode = (SUBJECT_NODE *)malloc(sizeof(SUBJECT_NODE));
        strcpy(pSubjectNode->subject_name,subject_name);
        pSubjectNode->subject_credits=credits;
        pSubjectNode->subject_hours=hours;
        pSubjectNode->scnext=NULL;
        pSubjectNode->next=NULL;

        //链接
        //若是头结点
        if(subject_head==NULL){
            subject_head = pSubjectNode;
            subject_temp = subject_head;
            count++;
        }
        //否则为后续结点
        else{
            subject_temp -> next = pSubjectNode;
            subject_temp = subject_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (subject_head == NULL)
    {
        printf("课程信息数据文件加载失败!\n");
        return re;
    }
    printf("课程信息数据文件加载成功!\n共导入%d条课程信息\n",count);
    count = 0;
    re += 1;


    //读取教室信息
    if ((pFile = fopen(gp_room_info_filename, "rb")) == NULL)
    {
        printf("教室信息数据文件打开失败!\n");
        return re;
    }
    printf("教室信息数据文件打开成功!\n");
    /*从数据文件中读教室信息数据，存入以先进先出方式建立的教室信息链中*/
    while (fscanf(pFile,"%s %s",building,room_name)!=EOF)
    {
        //新节点赋值
        pRoomNode = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
        strcpy(pRoomNode->building,building);
        strcpy(pRoomNode->room_name,room_name);
        pRoomNode->rcnext=NULL;
        pRoomNode->next=NULL;

        //链接
        //若是头结点
        if(room_head==NULL){
            room_head = pRoomNode;
            room_temp = room_head;
            count++;
        }
        //否则为后续结点
        else{
            room_temp -> next = pRoomNode;
            room_temp = room_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (room_head == NULL)
    {
        printf("教室信息数据文件加载失败!\n");
        return re;
    }
    printf("教室信息数据文件加载成功!\n共导入%d条教室信息\n",count);
    count = 0;
    re += 2;


    //读取教师信息
    if ((pFile = fopen(gp_teacher_info_filename, "rb")) == NULL)
    {
        printf("教师信息数据文件打开失败!\n");
        return re;
    }
    printf("教师信息数据文件打开成功!\n");
    /*从数据文件中读教师信息数据，存入以先进先出方式建立的教师信息链中*/
    while (fscanf(pFile,"%s %s",teacher_name,position)!=EOF)
    {
        //新节点赋值
        pTeacherNode = (TEACHER_NODE *)malloc(sizeof(TEACHER_NODE));
        strcpy(pTeacherNode -> teacher_name,teacher_name);
        strcpy(pTeacherNode ->position,position);
        pTeacherNode -> next = NULL;
        pTeacherNode ->tcnext=NULL;

        //链接
        //若是头结点
        if(teacher_head==NULL){
            teacher_head = pTeacherNode;
            teacher_temp = teacher_head;
            count++;
        }
        //否则为后续结点
        else{
            teacher_temp -> next = pTeacherNode;
            teacher_temp = teacher_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (teacher_head == NULL)
    {
        printf("教师信息数据文件加载失败!\n");
        return re;
    }
    printf("教师信息数据文件加载成功!\n共导入%d条教师信息\n",count);
    count = 0;
    re += 4;



    //读取班级信息
    if ((pFile = fopen(gp_class_info_filename, "rb")) == NULL)
    {
        printf("班级信息数据文件打开失败!\n");
        return re;
    }
    printf("班级信息数据文件打开成功!\n");
    /*从数据文件中读班级信息数据，存入以先进先出方式建立的班级信息链中*/
    while (fscanf(pFile,"%s",class_name)!=EOF)
    {
        //新节点赋值
        pClassNode = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
        strcpy(pClassNode->class_name,class_name);
        pClassNode->ccnext=NULL;
        pClassNode->next=NULL;

        //链接
        //若是头结点
        if(class_head==NULL){
            class_head = pClassNode;
            class_temp = class_head;
            count++;
        }
        //否则为后续结点
        else{
            class_temp -> next = pClassNode;
            class_temp = class_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (class_head == NULL)
    {
        printf("班级信息数据文件加载失败!\n");
        return re;
    }
    printf("班级信息数据文件加载成功!\n共导入%d条班级信息\n",count);
    count = 0;
    re += 8;


    //读取课堂信息
    if ((pFile = fopen(gp_course_info_filename, "rb")) == NULL)
    {
        printf("课堂信息数据文件打开失败!\n");
        return re;
    }
    printf("课堂信息数据文件打开成功!\n");
    /*从数据文件中读课堂信息数据，存入以先进先出方式建立的课堂信息链中*/
    while (fscanf(pFile,"%s %s %s %s %d %s %s %d",subject_name,building,
                  room_name,teacher_name,&weekday, lesson, week, &class_num)!=EOF)
    {
        //新节点赋值
        pCourseNode = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        for(i=0;i<10;i++){//初始化
            pCourseNode->class_name[i][0]='\0';
        }
        strcpy(pCourseNode->subject_name,subject_name);
        strcpy(pCourseNode->building,building);
        strcpy(pCourseNode->room_name,room_name);
        strcpy(pCourseNode->teacher_name,teacher_name);
        pCourseNode->weekday=weekday;
        pCourseNode->class_num=class_num;
        ScanfLesson(pCourseNode->lesson,lesson);
        ScanfWeek(pCourseNode->week,week);
        for(i=0;i<class_num;i++){
            fscanf(pFile,"%s",pCourseNode->class_name[i]);
        }
        pCourseNode->scnext=NULL;
        pCourseNode->rcnext=NULL;
        pCourseNode->tcnext=NULL;
        for(i=0;i<10;i++){
            pCourseNode->ccnext[i]=NULL;
        }
        pCourseNode->prior=NULL;
        pCourseNode->next=NULL;

        //单链表中链接
        //若是头结点
        if(course_head==NULL){
            course_head = pCourseNode;
            course_temp = course_head;
            count++;
        }
        //否则为后续结点
        else{
            course_temp -> next = pCourseNode;
            course_temp ->next->prior=course_temp;
            course_temp = course_temp -> next;
            count++;
        }

        //pcourse与四类基本信息链接
        //课程
        psubject_node = SeekSubjectNode(subject_head,pCourseNode->subject_name);
        pCourseNode->scnext = psubject_node->scnext;
        psubject_node->scnext = pCourseNode;
        //班级
        for(i=0;i<class_num;i++){
            pclass_node = SeekClassNode(class_head,pCourseNode->class_name[i]);
            pCourseNode->ccnext[i]=pclass_node->ccnext;
            pclass_node->ccnext=pCourseNode;
        }
        //教师
        pteacher_node = SeekTeacherNode(teacher_head,pCourseNode->teacher_name);
        pCourseNode->tcnext=pteacher_node->tcnext;
        pteacher_node->tcnext=pCourseNode;
        //教室
        proom_node = SeekRoomNode(room_head,pCourseNode->room_name,pCourseNode->building);
        pCourseNode->rcnext=proom_node->rcnext;
        proom_node->rcnext=pCourseNode;
    }
    fclose(pFile);
    if (course_head == NULL)
    {
        printf("课堂信息数据文件加载失败!\n");
        return re;
    }
    printf("课堂信息数据文件加载成功!\n共导入%d条课堂信息\n",count);
    count = 0;
    re += 16;

    return re;
}

/**
 * 函数名称: InitInterface
 * 函数功能: 初始化界面.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void InitInterface()
{

    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*黄色前景和蓝色背景*/

    SetConsoleTextAttribute(gh_std_out, att);  /*设置控制台屏幕缓冲区字符属性*/

    system("color F0\n");/*白底黑字*/
    ClearScreen();  /* 清屏*/

    /*创建弹出窗口信息堆栈，将初始化后的屏幕窗口当作第一层弹出窗口*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*屏幕字符属性*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;      /*弹出窗口的层号为0*/
    gp_top_layer->rcArea.Left = 0;  /*弹出窗口的区域为整个屏幕窗口*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();     /*显示菜单栏*/
    ShowState();    /*显示状态栏*/

    return;
}

/**
 * 函数名称: ClearScreen
 * 函数功能: 清除屏幕信息.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*取屏幕缓冲区信息*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*计算屏幕缓冲区字符单元数*/

    /*将屏幕缓冲区所有单元的字符属性设置为当前屏幕缓冲区字符属性*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*将屏幕缓冲区所有单元填充为空格字符*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);

    return;
}

/**
 * 函数名称: ShowMenu
 * 函数功能: 在屏幕上显示主菜单, 并设置热区, 在主菜单第一项上置选中标记.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur;
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++) /*在窗口第一行第一列处输出主菜单项*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*隐藏光标*/

    /*申请动态存储区作为存放菜单条屏幕区字符信息的缓冲区*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*将窗口第一行的内容读入到存放菜单条屏幕区字符信息的缓冲区中*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*将这一行中英文字母置为红色，其他字符单元置为白底黑字*/
    for (i=0; i<size.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*修改后的菜单条字符信息回写到窗口的第一行*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*将光标位置设置在第2行第1列*/

    /*将菜单项置为热区，热区编号为菜单项号，热区类型为0(按钮型)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*定位第i+1号菜单项的起止位置*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; /*设置菜单项所在字符单元的属性值*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*在选中主菜单项上做标记，gi_sel_menu初值为1*/

    return;
}

/**
 * 函数名称: ShowState
 * 函数功能: 显示状态条.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明: 状态条字符属性为白底黑字, 初始状态无状态信息.
 */
void ShowState()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int i;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SMALL_RECT rcMenu ={0, bInfo.dwSize.Y-1, size.X-1, bInfo.dwSize.Y-1};

    if (gp_buff_stateBar_info == NULL)
    {
        gp_buff_stateBar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
        ReadConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);
    }

    for (i=0; i<size.X; i++)
    {
        (gp_buff_stateBar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                                | BACKGROUND_RED;
/*
        ch = (char)((gp_buff_stateBar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_stateBar_info+i)->Attributes |= FOREGROUND_RED;
        }
*/
    }

    WriteConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);

    return;
}

/**
 * 函数名称: TagMainMenu
 * 函数功能: 在指定主菜单项上置选中标志.
 * 输入参数: num 选中的主菜单项号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*num为0时，将会去除主菜单项选中标记*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*否则，定位选中主菜单项的起止位置: PosA为起始位置, PosB为截止位置*/
    {
        for (i=1; i<num; i++)
        {
            PosA += strlen(ga_main_menu[i-1]) + 4;
        }
        PosB = PosA + strlen(ga_main_menu[num-1]);
    }

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;

    /*去除选中菜单项前面的菜单项选中标记*/
    for (i=0; i<PosA; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (gp_buff_menubar_info+i)->Char.AsciiChar;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*在选中菜单项上做标记，黑底白字*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*去除选中菜单项后面的菜单项选中标记*/
    for (i=PosB; i<bInfo.dwSize.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*将做好标记的菜单条信息写到窗口第一行*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}

/**
 * 函数名称: CloseSys
 * 函数功能: 关闭系统.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CloseSys(void)
{
    SUBJECT_NODE *pSubjectNode1 = subject_head, *pSubjectNode2;
    ROOM_NODE *pRoomNode1 = room_head, *pRoomNode2;
    TEACHER_NODE *pTeacherNode1 = teacher_head, *pTeacherNode2;
    CLASS_NODE *pClassNode1 = class_head,*pClassNode2;
    COURSE_NODE *pCourseNode1 = course_head,*pCourseNode2;

    while (pSubjectNode1 != NULL) /*释放课程链表的动态存储区*/
    {
        pSubjectNode2 = pSubjectNode1->next;
        free(pSubjectNode1);  /*释放动态存储区*/
        pSubjectNode1 = pSubjectNode2;
    }
    while (pRoomNode1 != NULL) /*释放教室链表的动态存储区*/
    {
        pRoomNode2 = pRoomNode1->next;
        free(pRoomNode1);  /*释放动态存储区*/
        pRoomNode1 = pRoomNode2;
    }
    while (pTeacherNode1 != NULL) /*释放教师链表的动态存储区*/
    {
        pTeacherNode2 = pTeacherNode1->next;
        free(pTeacherNode1);  /*释放动态存储区*/
        pTeacherNode1 = pTeacherNode2;
    }
    while (pClassNode1 != NULL) /*释放班级链表的动态存储区*/
    {
        pClassNode2 = pClassNode1->next;
        free(pClassNode1);  /*释放动态存储区*/
        pClassNode1 = pClassNode2;
    }
    while (pCourseNode1 != NULL) /*释放课堂链表的动态存储区*/
    {
        pCourseNode2 = pCourseNode1->next;
        free(pCourseNode1);  /*释放动态存储区*/
        pCourseNode1 = pCourseNode2;
    }

    ClearScreen();        /*清屏*/

    /*释放存放菜单条、状态条等信息动态存储区*/
    free(gp_buff_menubar_info);
    free(gp_buff_stateBar_info);

    /*关闭标准输入和输出设备句柄*/
    CloseHandle(gh_std_out);
    CloseHandle(gh_std_in);

    /*将窗口标题栏置为运行结束*/
    SetConsoleTitle("运行结束");

    return;
}

/**
 * 函数名称: RunSys
 * 函数功能: 运行系统, 在系统主界面下运行用户所选择的功能模块.
 * 输入参数: 无
 * 输出参数: phead 主链头指针的地址
 * 返 回 值: 无
 *
 * 调用说明:
 */
void RunSys()
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:字符单元层号, cAtt:字符单元属性*/
    char vkc, asc;      /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    while (bRet)
    {
        /*从控制台输入缓冲区中读一条记录*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT) /*如果记录由鼠标事件产生*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*获取鼠标坐标位置*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*取该位置的层号*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*取该字符单元属性*/
            if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
            {
                /* cAtt > 0 表明该位置处于热区(主菜单项字符单元)
                 * cAtt != gi_sel_menu 表明该位置的主菜单项未被选中
                 * gp_top_layer->LayerNo > 0 表明当前有子菜单弹出
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();            /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                    PopMenu(cAtt);       /*弹出鼠标所在主菜单项对应的子菜单*/
                }
            }
            else if (cAtt > 0) /*鼠标所在位置为弹出子菜单的菜单项字符单元*/
            {
                TagSubMenu(cAtt); /*在该子菜单项上做选中标记*/
            }

            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*如果按下鼠标左边第一键*/
            {
                if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
                {
                    if (cAtt > 0) /*如果该位置处于热区(主菜单项字符单元)*/
                    {
                        PopMenu(cAtt);   /*弹出鼠标所在主菜单项对应的子菜单*/
                    }
                    /*如果该位置不属于主菜单项字符单元，且有子菜单弹出*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*关闭弹出的子菜单*/
                        gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                    }
                }
                else /*层号不为0，表明该位置被弹出子菜单覆盖*/
                {
                    if (cAtt > 0) /*如果该位置处于热区(子菜单项字符单元)*/
                    {
                        PopOff(); /*关闭弹出的子菜单*/
                        gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/

                        /*执行对应功能函数:gi_sel_menu主菜单项号,cAtt子菜单项号*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*如果按下鼠标右键*/
            {
                if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
                {
                    PopOff();            /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*如果记录由按键产生*/
                 && inRec.Event.KeyEvent.bKeyDown) /*且键被按下*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*获取按键的虚拟键码*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*获取按键的ASC码*/

            /*系统快捷键的处理*/
            if (vkc == 112) /*如果按下F1键*/
            {
                if (gp_top_layer->LayerNo != 0) /*如果当前有子菜单弹出*/
                {
                    PopOff();            /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                }
                bRet = ExeFunction(5, 1);  /*运行帮助主题功能函数*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            { /*如果按下左或右Alt键*/
                switch (vkc)  /*判断组合键Alt+字母*/
                {
                    case 88:  /*Alt+X 退出*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,5);
                        break;
                    case 70:  /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77: /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81: /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83: /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72: /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }
            else if (asc == 0) /*其他控制键的处理*/
            {
                if (gp_top_layer->LayerNo == 0) /*如果未弹出子菜单*/
                {
                    switch (vkc) /*处理方向键(左、右、下)，不响应其他控制键*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40:
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else  /*已弹出子菜单时*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
                    switch (vkc) /*方向键(左、右、上、下)的处理*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu < 1)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 38:
                            num = gi_sel_sub_menu - 1;
                            if (num < 1)
                            {
                                num = ga_sub_menu_count[gi_sel_menu-1];
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num--;
                            }
                            TagSubMenu(num);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu > 5)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 40:
                            num = gi_sel_sub_menu + 1;
                            if (num > ga_sub_menu_count[gi_sel_menu-1])
                            {
                                num = 1;
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num++;
                            }
                            TagSubMenu(num);
                            break;
                    }
                }
            }
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*按下普通键*/
                if (gp_top_layer->LayerNo == 0)  /*如果未弹出子菜单*/
                {
                    switch (vkc)
                    {
                        case 70: /*f或F*/
                            PopMenu(1);
                            break;
                        case 77: /*m或M*/
                            PopMenu(2);
                            break;
                        case 81: /*q或Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s或S*/
                            PopMenu(4);
                            break;
                        case 72: /*h或H*/
                            PopMenu(5);
                            break;
                        case 13: /*回车*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*已弹出子菜单时的键盘输入处理*/
                {
                    if (vkc == 27) /*如果按下ESC键*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*如果按下回车键*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*其他普通键的处理*/
                    {
                        /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*依次与当前子菜单中每一项的代表字符进行比较*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*如果匹配成功*/
                                PopOff();
                                gi_sel_sub_menu = 0;
                                bRet = ExeFunction(gi_sel_menu, i-loc+1);
                            }
                        }
                    }
                }
            }
        }
    fflush(stdin);
    }
}

/**
 * 函数名称: PopMenu
 * 函数功能: 弹出指定主菜单项对应的子菜单.
 * 输入参数: num 指定的主菜单项号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PopMenu(int num)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh;
    int i, j, loc = 0;

    if (num != gi_sel_menu)       /*如果指定主菜单不是已选中菜单*/
    {
        if (gp_top_layer->LayerNo != 0) /*如果此前已有子菜单弹出*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*若已弹出该子菜单，则返回*/
    {
        return;
    }

    gi_sel_menu = num;    /*将选中主菜单项置为指定的主菜单项*/
    TagMainMenu(gi_sel_menu); /*在选中的主菜单项上做标记*/
    LocSubMenu(gi_sel_menu, &rcPop); /*计算弹出子菜单的区域位置, 存放在rcPop中*/

    /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*将该组子菜单项项名存入标签束结构变量*/
    labels.ppLabel = ga_sub_menu + loc;   /*标签束第一个标签字符串的地址*/
	labels.num = ga_sub_menu_count[gi_sel_menu - 1]; /*标签束中标签字符串的个数*/
	COORD aLoc[labels.num];/*定义一个坐标数组，存放每个标签字符串输出位置的坐标*/
    for (i=0; i<labels.num; i++) /*确定标签字符串的输出位置，存放在坐标数组中*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*使标签束结构变量labels的成员pLoc指向坐标数组的首元素*/
    /*设置热区信息*/
    areas.num = labels.num;       /*热区的个数，等于标签的个数，即子菜单的项数*/
    SMALL_RECT aArea[areas.num];                    /*定义数组存放所有热区位置*/
    char aSort[areas.num];                      /*定义数组存放所有热区对应类别*/
    char aTag[areas.num];                         /*定义数组存放每个热区的编号*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*热区定位*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*热区类别都为0(按钮型)*/
        aTag[i] = i + 1;           /*热区按顺序编号*/
    }
    areas.pArea = aArea;/*使热区结构变量areas的成员pArea指向热区位置数组首元素*/
    areas.pSort = aSort;/*使热区结构变量areas的成员pSort指向热区类别数组首元素*/
    areas.pTag = aTag;   /*使热区结构变量areas的成员pTag指向热区编号数组首元素*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*给弹出窗口画边框*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    { /*此循环用来在空串子菜项位置画线形成分隔，并取消此菜单项的热区属性*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0) /*串长为0，表明为空串*/
        {   /*首先画横线*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {   /*取消该区域字符单元的热区属性*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*按位与的结果保留了低两位*/
            }
        }

    }
    /*将子菜单项的功能键设为白底红字*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;  /*跳过空串*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * 函数名称: PopUp
 * 函数功能: 在指定区域输出弹出窗口信息, 同时设置热区, 将弹出窗口位置信息入栈.
 * 输入参数: pRc 弹出窗口位置数据存放的地址
 *           att 弹出窗口区域字符属性
 *           pLabel 弹出窗口中标签束信息存放的地址
             pHotArea 弹出窗口中热区信息存放的地址
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*弹出窗口所在位置字符单元信息入栈*/
    size.X = pRc->Right - pRc->Left + 1;    /*弹出窗口的宽度*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*弹出窗口的高度*/
    /*申请存放弹出窗口相关信息的动态存储区*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*将弹出窗口覆盖区域的字符信息保存，用于在关闭弹出窗口时恢复原样*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*此二重循环将所覆盖字符单元的原先属性值存入动态存储区，便于以后恢复*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*完成弹出窗口相关信息入栈操作*/
    /*设置弹出窗口区域字符的新属性*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*将标签束中的标签字符串在设定的位置输出*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*设置弹出窗口区域字符单元的新属性*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*此二重循环设置字符单元的层号*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*此二重循环设置所有热区中字符单元的热区类型和热区编号*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/**
 * 函数名称: PopOff
 * 函数功能: 关闭顶层弹出窗口, 恢复覆盖区域原外观和字符单元原属性.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*栈底存放的主界面屏幕信息，不用关闭*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*恢复弹出窗口区域原外观*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*恢复字符单元原属性*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*释放动态存储区*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * 函数名称: DrawBox
 * 函数功能: 在指定区域画边框.
 * 输入参数: pRc 存放区域位置信息的地址
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*画框用的字符*/
    COORD pos = {pRc->Left, pRc->Top};  /*定位在区域的左上角*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框左上角*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*此循环画上边框横线*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框右上角*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*此循环画边框左边线和右边线*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框左下角*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*画下边框横线*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框右下角*/
    return;
}

/**
 * 函数名称: TagSubMenu
 * 函数功能: 在指定子菜单项上做选中标记.
 * 输入参数: num 选中的子菜单项号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*计算弹出子菜单的区域位置, 存放在rcPop中*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*如果子菜单项号越界，或该项子菜单已被选中，则返回*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*首先取消原选中子菜单项上的标记*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*白底红字*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*在制定子菜单项上做选中标记*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*修改选中子菜单项号*/
    return;
}

/**
 * 函数名称: LocSubMenu
 * 函数功能: 计算弹出子菜单区域左上角和右下角的位置.
 * 输入参数: num 选中的主菜单项号
 * 输出参数: rc 存放区域位置信息的地址
 * 返 回 值: 无
 *
 * 调用说明:
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*区域的上边定在第2行，行号为1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*计算区域左边界位置, 同时计算第一个子菜单项在子菜单字符串数组中的位置*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*暂时存放第一个子菜单项字符串长度*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*查找最长子菜单字符串，将其长度存放在rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*计算区域的右边界*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*计算区域下边的行号*/
    if (rc->Right >= SCR_COL)  /*右边界越界的处理*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * 函数名称: DealInput
 * 函数功能: 在弹出窗口区域设置热区, 等待并相应用户输入.
 * 输入参数: pHotArea
 *           piHot 焦点热区编号的存放地址, 即指向焦点热区编号的指针
 * 输出参数: piHot 用鼠标单击、按回车或空格时返回当前热区编号
 * 返 回 值:
 *
 * 调用说明:
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*回车键或空格表示按下当前按钮*/
                iRet = 13;
                break;
            }
        }
    }
    return iRet;
}

void showcursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = TRUE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);   /*显现光标*/
}

void hidecursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*隐藏光标*/
}

/**弹出菜单*/
BOOL ShowModule(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 1;
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};
    char aTag[] = {1};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}

BOOL ChooseModule(char **pCh)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = FALSE; /*返回用户的选择，TRUE为确定，FALSE为取消*/
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6; /*空出弹出框的左右间隔*/
    pos.Y = 7;  /*画横线和上下留白*/
    rcPop.Left = (SCR_COL - pos.X) / 2; /*确认弹出框的位置*/
    rcPop.Right = rcPop.Left + pos.X - 1;   /*-1是因为开始坐标为0*/
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = 2; /*标签束中标签字符串的个数*/
    labels.ppLabel = pCh;   /*标签束第一个标签字符串的地址*/
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};   /*定义一个坐标数组，存放每个标签字符串输出位置的坐标*/
    labels.pLoc = aLoc; /*使标签束结构变量labels的成员ploc指向坐标数组的首元素*/

    areas.num = 2;  /*两个热区*/
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};/*热区定位*/
    char aSort[] = {0, 0};  /*热区类型*/
    char aTag[] = {1, 2};   /*热区编号*/
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);    /*画横线分隔*/

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
    }
    PopOff();

    return bRet;
}

void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    for (i=0; i<pHotArea->num; i++)
    {  /*将按钮类热区置为白底黑字*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*热区是按钮类*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*被激活热区是按钮类*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*被激活热区是文本框类*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/**
 * 函数名称: ExeFunction
 * 函数功能: 执行由主菜单号和子菜单号确定的功能函数.
 * 输入参数: m 主菜单项号
 *           s 子菜单项号
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明: 仅在执行函数ExitSys时, 才可能返回FALSE, 其他情况下总是返回TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*函数指针数组，用来存放所有功能函数的入口地址*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*将功能函数入口地址存入与功能函数所在主菜单号和子菜单号对应下标的数组元素*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = NULL;
    pFunction[4] = ExitSys;

    pFunction[5] = MaintainSubjectInfo;
    pFunction[6] = MaintainRoomInfo;
    pFunction[7] = MaintainTeacherInfo;
    pFunction[8] = MaintainClassInfo;
    pFunction[9] = NULL;
    pFunction[10] = MaintainCourseInfo;

    pFunction[11] = QuerySubjectInfo;
    pFunction[12] = QueryRoomInfo;
    pFunction[13] = QueryTeacherInfo;
    pFunction[14] = QueryClassInfo;
    pFunction[15] = NULL;
    pFunction[16] = QueryCourseInfo;
    pFunction[17] = NULL;
    pFunction[18] = QueryRestRoomInfo;

    pFunction[19] = StatRoomUtilization;
    pFunction[20] = StatRoomEfficiency;
    pFunction[21] = StatTeacherValidity;
    pFunction[22] = StatClassValidity;

    pFunction[23] = HelpTopic;
    pFunction[24] = NULL;
    pFunction[25] = AboutSys;

    for (i=1,loc=0; i<m; i++)  /*根据主菜单号和子菜单号计算对应下标*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*用函数指针调用所指向的功能函数*/
    }

    return bRet;
}

/*********************************************************************
**************************** 功 能 模 块 ****************************
*********************************************************************/

/**文件模块*/

/**
 * 函数名称: Savedata
 * 函数功能: 执行数据保存，将四类基础数据以及课堂链表分别存在五个文件中.
 * 输入参数:
 *
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"数据保存成功！",
                             "确认"
                            };
    char *plabel_choose[] = {"确认保存信息吗？",
                             "确定    取消"
                            };

    if (ChooseModule(plabel_choose) == 0){  /*取消保存*/
        PopOff();
        return bRet;
    }
    PopOff();
    SaveSysData();   /*保存信息*/
    ShowModule(plabel_result, 2);

    return bRet;
}

/**
 * 函数名称: BackupData
 * 函数功能: 执行数据备份，将四类基础数据以及课堂链表分别备份在五个文件中.
 * 输入参数:
 *
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"备份成功！已备份至：",
                             "C:\ClassBackup",
                             "确认"
                            };
    char *plabel_choose[] = {"确认备份信息吗？",
                             "确定    取消"
                            };
    char *filename = {"C:\\ClassBackup\\"};  /*备份路径*/

    if (ChooseModule(plabel_choose) == 0){  /*取消备份*/
        PopOff();
        return bRet;
    }
    PopOff();
    BackupSysData(filename);   /*备份信息*/
    ShowModule(plabel_result, 3);

    return bRet;
}

/**
 * 函数名称: RestoreData
 * 函数功能: 执行数据恢复，将四类基础数据以及课堂信息数据从五个文件中读入系统中.
 * 输入参数:
 *
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"恢复信息成功！",
                             "确认"
                            };
    char *plabel_choose[] = {"确认恢复信息吗？",
                             "确定    取消"
                            };
    char *filename = {"C:\\ClassBackup\\"};  /*备份文件所在路径*/

    if (ChooseModule(plabel_choose) == 0){  /*取消恢复*/
        PopOff();
        return bRet;
    }
    PopOff();
    RestoreSysData(filename);   /*恢复信息*/
    ShowModule(plabel_result, 2);

    ClearScreen();
    ShowMenu();

    return bRet;
}

BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"确认退出系统吗？", "确定    取消"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}


/**数据维护模块*/

/**
 * 函数名称: MaintainSubjectInfo
 * 函数功能: 执行课程信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainSubjectInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"课程信息添加成功！","确认"},
                               {"操作失败！","确认"},
                               {"课程信息修改成功！","确认"},
                               {"修改失败！","确认"},
                               {"课程信息删除成功！","确认"},
                               {"操作失败，未查询到对应课程信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();/*显示光标*/
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入课程信息*/
        flag = InsertSubjectNode(&subject_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改课程信息*/
        flag = ModifSubjectNode(subject_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除课程信息*/
        flag = DelSubjectNode(&subject_head);
        if(flag == 1){   /*删除成功*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*取消删除*/;}
        else{   /*删除失败*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*输入错误选项*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();/*隐藏光标*/
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: MaintainRoomInfo
 * 函数功能: 执行教室信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainRoomInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"教室信息添加成功！","确认"},
                               {"操作失败，教室信息已存在！","确认"},
                               {"教室信息修改成功！","确认"},
                               {"修改失败！","确认"},
                               {"教室信息删除成功！","确认"},
                               {"操作失败，未查询到对应教室信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入教室信息*/
        flag = InsertRoomNode(&room_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改教室信息*/
        flag = ModifRoomNode(room_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除教室信息*/
        flag = DelRoomNode(&room_head);
        if(flag == 1){   /*删除成功*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*取消删除*/;}
        else{   /*删除失败*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*输入错误选项*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: MaintainTeacherInfo
 * 函数功能: 执行教师信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainTeacherInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"教师信息添加成功！","确认"},
                               {"操作失败，教师信息已存在！","确认"},
                               {"教师信息修改成功！","确认"},
                               {"修改失败！","确认"},
                               {"教师信息删除成功！","确认"},
                               {"操作失败，未查询到对应教师信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入教师信息*/
        flag = InsertTeacherNode(&teacher_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改教师信息*/
        flag = ModifTeacherNode(teacher_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除教师信息*/
        flag = DelTeacherNode(&teacher_head);
        if(flag == 1){   /*删除成功*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*取消删除*/;}
        else{   /*删除失败*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*输入错误选项*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: MaintainClassInfo
 * 函数功能: 执行班级信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainClassInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"班级信息添加成功！","确认"},
                               {"操作失败，班级信息已存在！","确认"},
                               {"班级信息修改成功！","确认"},
                               {"修改失败！","确认"},
                               {"班级信息删除成功！","确认"},
                               {"操作失败，未查询到对应班级信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入班级信息*/
        flag = InsertClassNode(&class_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改班级信息*/
        flag = ModifClassNode(class_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除班级信息*/
        flag = DelClassNode(&class_head);
        if(flag == 1){   /*删除成功*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*取消删除*/;}
        else{   /*删除失败*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*输入错误选项*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: MaintainCourseInfo
 * 函数功能: 执行课堂信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainCourseInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"课堂信息添加成功！","确认"},
                               {"操作失败！","确认"},
                               {"课堂信息修改成功！","确认"},
                               {"修改失败！","确认"},
                               {"课堂信息删除成功！","确认"},
                               {"操作失败，未查询到对应课堂信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();  /*显现光标*/

    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入课堂信息*/
        flag = InsertCourseNode(&course_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改课堂信息*/
        flag = ModifCourseNode(course_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除课堂信息*/
        flag = DelCourseNode(&course_head);
        if(flag == 1){   /*删除成功*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*取消删除*/;}
        else{   /*删除失败*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*输入错误选项*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();  /*隐藏光标*/

    ClearScreen();
    ShowMenu();

    return bRet;
}

/**数据查询模块*/
/**
 * 函数名称: QuerySubjectInfo
 * 函数功能: 执行课程信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QuerySubjectInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char subject_name[20];
    char class_name[40];
    SUBJECT_NODE *psubject_node = NULL;
    CLASS_NODE *pclass_node = NULL;
    COURSE_NODE *pcourse_node =NULL;
    int ChooseNum = 0;

    showcursor();/*显示光标*/
    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1：通过课程名称查找课程基本信息\n");
    printf("    2：通过班级名称查找其学习的所有课程信息\n");
    printf("\n  请键入数字：");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  请输入课程名称：");
        scanf ("%s", subject_name);
        psubject_node = SeekSubjectNode(subject_head, subject_name);/*查找结点*/

        if(psubject_node != NULL){/*如果找到*/
            printf ("\n  课程基本信息：\n");
            printf ("    课程名称：%s\n",psubject_node->subject_name);
            printf ("    课程学分：%.1f\n", psubject_node ->subject_credits);
            printf ("    课程学时：%d\n", psubject_node ->subject_hours);
            ShowModule(*plabel_result, 2);
        }
        else{/*如果未找到*/
            printf ("\n  未查询到对应课程信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else if (ChooseNum == 2){
        printf ("\n  请输入班级名称：");
        scanf ("%s", class_name);
        pclass_node=SeekClassNode(class_head,class_name);
        if(pclass_node==NULL){/*班级信息错误*/
            printf ("\n  未查询到对应班级信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//否则查询到对应班级
            if(pclass_node->ccnext !=NULL){//若对应班级有课堂结点
                pcourse_node = SeekSubjectNode2(pclass_node->ccnext,pclass_node->class_name);/*查找并排序建立结果链表*/

                ShowModule(*plabel_result, 2);
                printf ("\n\n    查询到该班级所修所有课程信息：(按课程名称排序)\n\n");
                printf ("  课程名称                                  学分       学时\n");
                for (;pcourse_node != NULL; pcourse_node = pcourse_node ->next){
                    printf("  %-40s", pcourse_node ->subject_name);
                    printf("  %-10.1f", SeekSubjectNode(subject_head,pcourse_node->subject_name)->subject_credits);
                    printf("  %-10d\n", SeekSubjectNode(subject_head,pcourse_node->subject_name)->subject_hours);
                }
            }

            else{/*否则该班级无所修课程*/
                printf ("\n  未查询到与该班级相关的课堂信息！\n");
                ShowModule(*(plabel_result+1),2);
            }
        }
    }

    else{
        printf ("\n  键入数字有误！\n");
    }

    hidecursor();/*隐藏光标*/

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryRoomInfo
 * 函数功能: 执行教室信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryRoomInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char building[20];
    char subject_name[20];
    char class_name[40];
    ROOM_NODE *proom_node=NULL;/*用于存储结果链表*/
    CLASS_NODE *pclass_node=NULL;//用于遍历查询班级结点
    COURSE_NODE *pcourse_node;//用于遍历查询课堂结点
    int ChooseNum = 0;
    int i,j;//计数器

    showcursor();/*显示光标*/

    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1 : 通过教学楼名称查询其所有教室信息\n");
    printf("    2 : 通过班级和课程名称查询课堂所处教室\n");
    printf("\n  请键入数字：");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  请输入教学楼名称：");
        scanf ("%s", building);
        proom_node = SeekRoomNode2(room_head, building);/*查找并排序建立结果链表*/

        if(proom_node != NULL){/*如果找到*/
            ShowModule(*plabel_result, 2);
            printf ("\n\n  查询到该教学楼所含所有教室信息：(按教室名称排序)\n");
            for (;proom_node != NULL; proom_node = proom_node ->next){
                printf("    %s %s\n", proom_node->building, proom_node->room_name);
            }
        }
        else{/*如果未找到*/
            printf ("\n  未查询到对应教学楼信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else if (ChooseNum == 2){
        printf ("\n  请输入班级名称：");
        scanf ("%s", class_name);
        printf ("\n  请输入课程名称：");
        scanf ("%s", subject_name);

        pclass_node=SeekClassNode(class_head,class_name);
        if(pclass_node==NULL){/*班级信息错误*/
            printf ("\n  未查询到对应班级信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//否则 查询到对应班级 继续查询教室
            if(pclass_node->ccnext !=NULL){//若对应班级有课堂结点
                pcourse_node = SeekRoomNode3(pclass_node->ccnext,subject_name,pclass_node->class_name);/*查找并排序建立结果链表*/

                if(pcourse_node!=NULL){//若找到对应课堂结点
                    ShowModule(*plabel_result, 2);
                    printf ("\n\n    查询到的教室信息：\n\n");
                    printf ("  教室                  时间        节数                周数\n");
                    for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
                        printf("  %-10s %-10s 周%-10d",pcourse_node->building,pcourse_node->room_name,pcourse_node->weekday);
                        for(i=1,j=0;i<=12;i++){
                            if(pcourse_node->lesson[i]){
                                printf("%d ",i);
                                j+=2;
                                if(i>=10) j++;
                            }
                        }
                        for(;j<20;j++){//补全长度
                            printf(" ");
                        }
                        for(i=1;i<=29;i++){
                            if(pcourse_node->week[i]){
                                printf("%d ",i);

                            }
                        }
                        printf("\n");
                    }
                }
                else{/*否则该班级无该课堂信息*/
                    printf ("\n  未查询到对应课堂信息！\n");
                    ShowModule(*(plabel_result+1),2);
                }

            }

            else{/*否则该班级无相关课堂结点*/
                printf ("\n  未查询到与该班级相关的课堂信息！\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else{
        printf ("\n  键入数字有误！\n");
    }

    hidecursor();/*隐藏光标*/

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryTeacherInfo
 * 函数功能: 执行教师信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryTeacherInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char teacher_name[20];
    char subject_name[20];
    char class_name[40];
    TEACHER_NODE *pteacher_node=NULL;/*用于存储结果链表*/
    SUBJECT_NODE *psubject_node=NULL;
    CLASS_NODE *pclass_node=NULL;
    COURSE_NODE *pcourse_node=NULL;//用于遍历查询课堂结点
    int ChooseNum = 0;

    showcursor();/*显示光标*/

    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1 : 通过教师姓名查询教师基本信息\n");
    printf("    2 : 通过班级、课程名称查询其任课教师信息\n");
    printf("    3 : 通过课程名称查询其所有任课教师信息\n");
    printf("\n  请键入数字：");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  请输入教师姓名：");
        scanf ("%s", teacher_name);
        hidecursor();/*隐藏光标*/
        pteacher_node = SeekTeacherNode(teacher_head, teacher_name);/*查找并建立结果链表*/

        if(pteacher_node != NULL){/*如果找到*/
            printf ("\n\n  教师基本信息：\n");
            printf ("    教师姓名：%s\n",pteacher_node->teacher_name);
            printf ("    教师职位：%s\n", pteacher_node ->position);
            ShowModule(*plabel_result, 2);
        }
        else{/*如果未找到*/
            printf ("\n  未查询到对应教师信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else if (ChooseNum == 2){
        printf ("\n  请输入班级名称：");
        scanf ("%s", class_name);
        printf ("\n  请输入课程名称：");
        scanf ("%s", subject_name);
        hidecursor();/*隐藏光标*/

        pclass_node = SeekClassNode(class_head,class_name);
        if(pclass_node==NULL){/*班级信息错误*/
            printf ("\n  未查询到对应班级信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//否则 查询到对应班级 继续查询教师
            if(pclass_node->ccnext !=NULL){//若对应班级有课堂结点
                pcourse_node = SeekTeacherNode2(pclass_node->ccnext,subject_name,pclass_node->class_name);/*查找并排序建立结果链表*/

                if(pcourse_node!=NULL){//若找到对应课堂定点
                    ShowModule(*plabel_result, 2);
                    printf ("\n\n  该班级对应科目的任课教师为：(按教师姓名排序)\n");
                    for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
                        printf("    %-6s %s\n",pcourse_node->teacher_name,SeekTeacherNode(teacher_head,pcourse_node->teacher_name)->position);
                    }
                }
                else{/*否则该班级无该课堂信息*/
                    printf ("\n  未查询到对应课堂信息！\n");
                    ShowModule(*(plabel_result+1),2);
                }

            }

            else{/*否则该班级无相关课堂结点*/
                printf ("\n  未查询到与该班级相关的课程信息！\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else if (ChooseNum == 3){
        printf ("\n  请输入课程名称：");
        scanf ("%s", subject_name);
        hidecursor();/*隐藏光标*/

        psubject_node = SeekSubjectNode(subject_head,subject_name);
        if(psubject_node==NULL){/*课程信息错误*/
            printf ("\n  未查询到对应课程信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//否则 查询到对应课程 继续查询教师
            if(psubject_node->scnext !=NULL){//若对应课程有课堂结点
                pcourse_node = SeekTeacherNode3(psubject_node->scnext);/*查找并排序建立结果链表*/

                ShowModule(*plabel_result, 2);
                printf ("\n\n  该课程的任课教师为：(按教师姓名排序)\n");
                for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
                    printf("    %-6s %s\n",pcourse_node->teacher_name,SeekTeacherNode(teacher_head,pcourse_node->teacher_name)->position);
                }

            }

            else{/*否则该课程无相关课堂结点*/
                printf ("\n  未查询到与该课程相关的教师信息！\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else{
        printf ("\n  键入数字有误！\n");
        hidecursor();/*隐藏光标*/
    }



    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryClassInfo
 * 函数功能: 执行班级信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryClassInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char subject_name[20];
    char class_namem[40];
    SUBJECT_NODE *psubject_node=NULL;//用于遍历查询课程结点
    CLASS_NODE *pclass_node=NULL;/*用于存储结果链表*/
    COURSE_NODE *pcourse_node;//用于遍历查询课堂结点
    int ChooseNum = 0;

    showcursor();/*显示光标*/

    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1 : 通过课程名称查询需修此课程的所有班级信息\n");
    printf("    2 : 通过部分班级名称模糊查询班级信息\n");
    printf("\n  请键入数字：");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  请输入课程名称：");
        scanf ("%s", subject_name);
        psubject_node = SeekSubjectNode(subject_head,subject_name);/*查找并建立结果链表*/
        if(psubject_node==NULL){/*课程信息错误*/
            printf ("\n  未查询到对应课程信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//否则 查询到对应课程 继续查询教师
            if(psubject_node->scnext !=NULL){//若对应课程有课堂结点
                pclass_node = SeekClassNode2(psubject_node->scnext);/*查找并排序建立结果链表*/
                if(strlen(subject_name)<30){
                    ShowModule(*plabel_result, 2);
                }
                printf ("\n\n  需学习该课程的班级有：\n");
                for(;pclass_node!=NULL;pclass_node=pclass_node->next){
                    printf("    %s\n",pclass_node->class_name);
                }

            }

            else{/*否则该课程无相关课堂结点*/
                printf ("\n  未查询到与该课程相关的班级信息！\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else if (ChooseNum == 2){
        printf ("\n  请输入部分班级名称：");
        scanf ("%s", class_namem);

        pclass_node = SeekClassNodeM(class_head, class_namem);/*查找并建立结果链表*/
        if(pclass_node != NULL){/*如果找到*/
            printf ("\n  查找到的班级有：(按班级名称排序)\n");
            for(;pclass_node!=NULL;pclass_node=pclass_node->next){
                printf("    %s\n",pclass_node->class_name);
            }
            ShowModule(*plabel_result, 2);
        }
        else{/*如果未找到*/
            printf ("\n  未查询相关班级信息！\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else{
        printf ("\n  键入数字有误！\n");
    }

    hidecursor();/*隐藏光标*/

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryCourseInfo
 * 函数功能: 执行课堂信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryCourseInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char subject_name[40];
    char building[20];
    char room_name[20];
    char teacher_name[20];
    char class_name[40];
    int weekday;
    int week_start;
    int i;

    SUBJECT_NODE *psubject_node;/*用于依据分类编号查找分类名称*/
    ROOM_NODE *proom_node;/*结果链表*/
    TEACHER_NODE *pteacher_node = NULL;
    CLASS_NODE *pclass_node=NULL;
    COURSE_NODE *pcourse_node=NULL;

    int ChooseNum = 0;

    showcursor();/*显示光标*/

    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1 : 通过课程、教室、教师、时间等条件唯一查找课堂信息\n");
    printf("    2 : 通过课程名称查找所有相关课堂信息(按教师姓名排序)\n");
    printf("    3 : 通过教室地址查找所有相关课堂信息(按课程名称排序)\n");    printf("    4 : 通过教师姓名查找所有相关课堂信息(按课程名称排序)\n");    printf("    5 : 通过班级名称查找所有相关课堂信息(按课程名称排序)\n");
    printf("\n\n  请键入数字：");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf("\n  请输入课程名称：");
        scanf("%s", subject_name);
        printf("\n  请输入教室所属教学楼：");
        scanf("%s", building);
        printf("\n  请输入教室名称：");
        scanf("%s", room_name);
        printf("\n  请输入教师姓名：");
        scanf("%s", teacher_name);
        printf("\n  请输入课堂位于周几：");
        scanf("%d", &weekday);
        printf("\n  请输入课堂起始周次：");
        scanf("%d", &week_start);

        //判断输入时间格式
        if(weekday<1 || weekday>7 ||
           week_start>29 || week_start<1 ){
            printf("\n  输入课堂时间格式有误！\n");
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }

        pcourse_node = SeekCourseNode(course_head,subject_name,building,room_name,
                                      teacher_name,weekday,week_start);/*查找并建立结果链表*/
        if(pcourse_node!=NULL){//若查询到
            printf("\n  课堂信息：\n");
            printf("    课程名称：%s\n", pcourse_node ->subject_name);
            printf("    教室地址：%s %s\n",pcourse_node->building, pcourse_node ->room_name);
            printf("    教师姓名：%s\n", pcourse_node ->teacher_name);
            printf("    参与班级：%s\n", pcourse_node ->class_name[0]);
            for(i=1;i<pcourse_node->class_num;i++){
                if(pcourse_node->class_name[i][0]!='\0'){
                    printf("              %s\n",pcourse_node->class_name[i]);
                }
            }
            printf("    课堂时间：周%d 节数：",pcourse_node->weekday);
            for(i=1;i<=12;i++){
                if(pcourse_node->lesson[i]){
                    printf("%d ",i);
                }
            }
            printf("\n");
            printf("    课堂周次：");            for(i=1;i<=29;i++){
                if(pcourse_node->week[i]){
                    printf("%d ",i);
                }
            }
            printf("\n");

            ShowModule(*plabel_result, 2);
        }
        else{
            printf("\n  未查询到对应课堂信息！\n");
            ShowModule(*(plabel_result+1), 2);
        }

        printf("\n\n  按任意键返回主菜单...\n");
        getch();
        ClearScreen();
        ShowMenu();
        return bRet;
    }
    else if (ChooseNum == 2){
        printf ("\n\n  请输入课程名称：");
        scanf ("%s", subject_name);
        psubject_node =SeekSubjectNode(subject_head,subject_name);
        if(psubject_node!=NULL){
            if(psubject_node->scnext){
                pcourse_node = SeekCourseNode_S(psubject_node->scnext);/*排序并建立结果链表*/
            }
        }
        else{
            printf("  未查询到对应课程信息！\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }
    }

    else if (ChooseNum == 3){
        printf ("\n  请输入教室地址：\n");
        printf("  教学楼：");
        scanf ("%s", building);
        printf("  教室：");
        scanf ("%s",room_name);
        proom_node =SeekRoomNode(room_head,room_name,building);
        if(proom_node!=NULL){
            if(proom_node->rcnext){
                pcourse_node = SeekCourseNode_R(proom_node->rcnext);/*排序并建立结果链表*/
            }
        }
        else{
            printf("  未查询到对应教室信息！\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }
    }

    else if (ChooseNum == 4){
        printf ("\n  请输入教师姓名：");
        scanf ("%s", teacher_name);
        pteacher_node =SeekTeacherNode(teacher_head,teacher_name);
        if(pteacher_node!=NULL){
            if(pteacher_node->tcnext){
                pcourse_node = SeekCourseNode_T(pteacher_node->tcnext);/*排序并建立结果链表*/
            }
        }
        else{
            printf("  未查询到对应教师信息！\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }
    }

    else if (ChooseNum == 5){
        printf ("\n  请输入班级名称：");
        scanf ("%s", class_name);
        pclass_node =SeekClassNode(class_head,class_name);
        if(pclass_node!=NULL){
            if(pclass_node->ccnext){
                pcourse_node = SeekCourseNode_C(pclass_node->ccnext,pclass_node->class_name);/*排序并建立结果链表*/
            }
        }
        else{
            printf("  未查询到对应班级信息！\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();

            return bRet;
        }
    }

    else{
        printf ("\n  键入数字有误！\n");
        printf("\n  按任意键返回主菜单...\n");
        getch();
        ClearScreen();
        ShowMenu();

        return bRet;
    }

    hidecursor();/*隐藏光标*/

    if(pcourse_node != NULL){/*如果找到*/
        ShowModule(*plabel_result, 2);
        printf ("\n\n  查询到的课堂信息：\n\n");

        for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
            printf("    课程名称：%s\n", pcourse_node ->subject_name);
            printf("    教室地址：%s %s\n", pcourse_node->building,pcourse_node ->room_name);
            printf("    教师姓名：%s\n", pcourse_node ->teacher_name);
            printf("    参与班级：%s\n", pcourse_node ->class_name[0]);
            for(i=1;i<pcourse_node->class_num;i++){
                if(pcourse_node->class_name[i][0]!='\0'){
                    printf("              %s\n",pcourse_node->class_name[i]);
                }
            }
            printf("    课堂时间：周%d 节数：",pcourse_node->weekday);
            for(i=1;i<=12;i++){
                if(pcourse_node->lesson[i]){
                    printf("%d ",i);
                }
            }
            printf("\n");
            printf("    课堂周次：");            for(i=1;i<=29;i++){
                if(pcourse_node->week[i]){
                    printf("%d ",i);
                }
            }
            printf("\n\n");
        }
    }
    else{/*如果未找到*/
        printf ("\n  未查询到相关课堂信息！\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryRestRoomInfo
 * 函数功能: 执行空闲教室信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryRestRoomInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    int weekday;//周几
    int week;//第几周
    int lesson;//第几节课
    ROOM_NODE *proom_node=NULL;/*用于存储结果链表*/

    int i,j;//计数器

    showcursor();/*显示光标*/
    printf("\n  本模块将通过具体时间查询某节课的所有空闲教室信息\n");
    printf("\n  请输入周数(1~29)：");
    scanf("%d", &week);
    printf("\n  请输入周几(1~7)：");
    scanf("%d", &weekday);
    printf("\n  请输入节数(1~12)：");
    scanf("%d", &lesson);
    hidecursor();/*隐藏光标*/

    //判断输入时间格式
    if(weekday<1 || weekday>7 ||
       lesson<1 || lesson>12 ||
       weekday<1 || weekday>29 ){
        printf("\n  输入时间格式有误！\n");
        printf("\n\n  按任意键返回主菜单...\n");
        getch();
        ClearScreen();
        ShowMenu();
        return bRet;
    }

    proom_node = SeekRestRoomNode(room_head, week,weekday,lesson);

    if(proom_node != NULL){/*如果找到*/
        ShowModule(*plabel_result, 2);
        printf ("\n  查询到 第%d周 周%d 第%d节课 的空闲教室信息：\n",week,weekday,lesson);
        for(;proom_node!=NULL;proom_node=proom_node->next){
            printf("    %-10s %-20s\n",proom_node->building,proom_node->room_name);
        }
    }
    else{/*如果未找到*/
        printf ("\n  在该时段未查询到空闲教室信息！\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}


/**数据分析模块*/
/**
 * 函数名称: StatRoomUtilization
 * 函数功能: 执行教室利用率分析的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatRoomUtilization(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"分析完成","确认"},
                                  {"分析失败，未查询到相应教学楼信息","确认"}
                                 };
    char building[20];
    int week;
    int i;//计数器
    ROOM_NODE *proom_node=NULL;
    COURSE_NODE *pcourse_node;
    UTILI_NODE *putili_node;
    UTILI_NODE *putili_head=NULL;
    int room_num=0;//教室间数
    int lesson_num=0;//有课节数
    int choose_num=0;


    showcursor();/*显示光标*/
    printf("\n  通过键入数字选择查询方式：\n");
    printf ("  1.通过输入教学楼名称与周数以教学楼为单位分析一周内指定楼栋教室利用率\n");
    printf ("  2.通过输入教学楼名称与周数以教室为单位分析一周内该楼栋教室利用率\n");
    printf ("\n  请输入数字以选择功能：");
    scanf("%d",&choose_num);
    hidecursor();/*隐藏光标*/

    if (choose_num==1){
        showcursor();/*显示光标*/
        printf ("\n  请输入教学楼名称：");
        scanf ("%s", building);        printf ("\n  请输入周次：");
        scanf ("%d", &week);
        hidecursor();/*隐藏光标*/

        //检查时间输入格式
        if(week<1 || week>29){
            printf("\n  输入周数格式有误！\n");
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }

        proom_node = SeekRoomNode2(room_head, building);/*创建结果链表*/

        if(proom_node != NULL){//若查询到对应教学楼信息
            for(;proom_node!=NULL;proom_node=proom_node->next){//遍历教室链
                for(pcourse_node=proom_node->rcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){//遍历统计该教室利用率
                    if(pcourse_node->week[week]){
                        for(i=1;i<=12;i++){
                            if(pcourse_node->lesson[i]){
                                lesson_num++;
                            }
                        }
                    }
                }
                room_num++;
            }

            //输出结果
            ShowModule(*plabel_result, 2);
            printf ("\n  分析所得第%d周%s的教室利用率：\n",week,building);
            printf("    可用教室节数：%d\n", room_num*56);
            printf("    已用教室节数：%d\n", lesson_num);
            if(room_num){
                printf("    教室利用率：%.3f\n", (float)lesson_num/(room_num*56));
            }
            else{
                printf("    本周无可用教室！\n");
            }
        }
        else{
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if(choose_num==2){
        showcursor();/*显示光标*/
        printf ("\n  请输入教学楼名称：");
        scanf ("%s", building);        printf ("\n  请输入周次：");
        scanf ("%d", &week);
        hidecursor();/*隐藏光标*/

        //检查时间输入格式
        if(week<1 || week>29){
            printf("\n  输入周数格式有误！\n");
            printf("\n\n  按任意键返回主菜单...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }

        proom_node = SeekRoomNode2(room_head, building);/*创建结果链表*/

        if(proom_node != NULL){//若查询到对应教学楼信息
            for(;proom_node!=NULL;proom_node=proom_node->next){//遍历教室链
                putili_node = (UTILI_NODE*)malloc(sizeof(UTILI_NODE));//新建利用率结点
                strcpy(putili_node->room_name,proom_node->room_name);
                putili_node->lesson=0;
                for(pcourse_node=proom_node->rcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){//遍历统计该教室利用率
                    if(pcourse_node->week[week]){
                        for(i=1;i<=12;i++){
                            if(pcourse_node->lesson[i]){
                                putili_node->lesson++;
                            }
                        }
                    }
                }
                putili_node->next=putili_head;
                putili_head=putili_node;
            }

            //若成功构建结果链表 对其排序并输出
            if(putili_head){
                UTILI_NODE *putili_node_prior;
                UTILI_NODE *putili_node_after;
                UTILI_NODE *putili_node_temp;
                UTILI_NODE *putili_node_cur;

                putili_node_prior = putili_head;
                putili_node_temp = (UTILI_NODE *)malloc(sizeof(UTILI_NODE));/*用于交换结点的临时结点*/

                while (putili_node_prior -> next != NULL){/*选择排序*/
                    putili_node_cur = putili_node_prior;
                    putili_node_after = putili_node_prior -> next;
                    while (putili_node_after != NULL){/*cur是(最大)教师名称地址*/
                        if (putili_node_cur -> lesson< putili_node_after -> lesson){
                            putili_node_cur = putili_node_after;
                        }
                        putili_node_after = putili_node_after -> next;
                    }

                    if (putili_node_cur != putili_node_prior){/*交换两个结点中的信息，指针域不交换*/
                        *putili_node_temp = *putili_node_prior;
                        *putili_node_prior = *putili_node_cur;
                        putili_node_prior -> next = putili_node_temp -> next;/*恢复prior->next指向的结点*/
                        putili_node_temp -> next = putili_node_cur -> next;
                        *putili_node_cur = *putili_node_temp;/*cur数据交换，->next指向不变*/
                    }
                    putili_node_prior = putili_node_prior -> next;
                }


                //输出结果
                ShowModule(*plabel_result, 2);
                printf ("\n    分析所得第%d周%s的各教室能效 (按能效降序排列)：\n\n",week,building);
                printf ("  教室    已用教室节数    可用教室节数    教室利用率\n");
                for (;putili_head != NULL; putili_head = putili_head ->next){
                    printf("  %-10s", putili_head ->room_name);
                    printf("   %-13d", putili_head ->lesson);
                    printf("   %-10d", 12*7);
                    printf("   %-10.3f\n", (float)(putili_head->lesson)/(12*7));
                }
            }

            else{
                printf("  第%d周%s无可用教室！\n",week,building);
            }
        }
        else{
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else{
        printf("\n  输入数字有误！\n");
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: StatRoomEfficiency
 * 函数功能: 执行教室能效分析的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatRoomEfficiency(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"分析完成","确认"},
                                  {"分析失败，未查询到相应教学楼信息","确认"}
                                 };
    char building[20];
    int week;
    int i;//计数器
    ROOM_NODE *proom_node=NULL;
    COURSE_NODE *pcourse_node;
    UTILI_NODE *putili_head=NULL;//结果链头结点
    UTILI_NODE *putili_node;

    showcursor();/*显示光标*/
    printf ("\n  本模块将通过输入教学楼名称与周数分析该周指定楼栋各教室能效\n");
    printf ("\n  请输入教学楼名称：");
    scanf ("%s", building);    printf ("\n  请输入周次：");
    scanf ("%d", &week);
    hidecursor();/*隐藏光标*/

    //检查时间输入格式
    if(week<1 || week>29){
        printf("\n  输入周数格式有误！\n");
        printf("\n\n  按任意键返回主菜单...\n");
        getch();
        ClearScreen();
        ShowMenu();
        return bRet;
    }

    proom_node = SeekRoomNode2(room_head, building);/*创建结果链表*/

    if(proom_node != NULL){//若查询到对应教学楼信息
        for(;proom_node!=NULL;proom_node=proom_node->next){//遍历教室链
            putili_node = (UTILI_NODE*)malloc(sizeof(UTILI_NODE));//新建利用率结点
            strcpy(putili_node->room_name,proom_node->room_name);
            putili_node->lesson=0;
            putili_node->lesson_day=0;
            putili_node->lesson_night=0;
            for(pcourse_node=proom_node->rcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){//遍历统计该教室利用率
                if(pcourse_node->week[week]){
                    for(i=1;i<=8;i++){
                        if(pcourse_node->lesson[i]){
                            putili_node->lesson++;
                            putili_node->lesson_day++;
                        }
                    }
                    for(;i<=12;i++){
                        if(pcourse_node->lesson[i]){
                            putili_node->lesson++;
                            putili_node->lesson_night++;
                        }
                    }
                }
            }
            if(putili_node->lesson_day>0 && putili_node->lesson_night==0){//若有白天无夜晚
                putili_node->effi_rent=100.0;
            }
            else if(putili_node->lesson_day==0 &&putili_node->lesson_night==0){//若无白天无夜晚
                putili_node->effi_rent=-1.0;
            }
            else{
                putili_node->effi_rent=(float)(putili_node->lesson_day)/(putili_node->lesson_night);
            }
            putili_node->next=putili_head;
            putili_head=putili_node;
        }

        //若成功构建结果链表 对其排序并输出
        if(putili_head){
            UTILI_NODE *putili_node_prior;
            UTILI_NODE *putili_node_after;
            UTILI_NODE *putili_node_temp;
            UTILI_NODE *putili_node_cur;

            putili_node_prior = putili_head;
            putili_node_temp = (UTILI_NODE *)malloc(sizeof(UTILI_NODE));/*用于交换结点的临时结点*/

            while (putili_node_prior -> next != NULL){/*选择排序*/
                putili_node_cur = putili_node_prior;
                putili_node_after = putili_node_prior -> next;
                while (putili_node_after != NULL){/*cur是(最大)地址*/
                    if (putili_node_cur ->effi_rent > putili_node_after ->effi_rent){
                        putili_node_cur = putili_node_after;
                    }
                    putili_node_after = putili_node_after -> next;
                }

                if (putili_node_cur != putili_node_prior){/*交换两个结点中的信息，指针域不交换*/
                    *putili_node_temp = *putili_node_prior;
                    *putili_node_prior = *putili_node_cur;
                    putili_node_prior -> next = putili_node_temp -> next;/*恢复prior->next指向的结点*/
                    putili_node_temp -> next = putili_node_cur -> next;
                    *putili_node_cur = *putili_node_temp;/*cur数据交换，->next指向不变*/
                }
                putili_node_prior = putili_node_prior -> next;
            }

            //输出结果
            ShowModule(*plabel_result, 2);
            printf ("\n    分析所得第%d周%s的各教室能效 (按能效升序排列)：\n\n",week,building);
            printf ("  教室    白天使用节数    夜晚使用节数       比值\n");
            for (putili_node=putili_head;putili_head != NULL; putili_head = putili_head ->next){
                if(putili_head->effi_rent>-0.5){
                    printf("  %-10s", putili_head ->room_name);
                    printf("   %-13d", putili_head ->lesson_day);
                    printf("   %-10d", putili_head->lesson_night);
                    printf("   %-4.3f\n", putili_head->effi_rent);
                }
            }

            printf("\n  Tips:1.白天夜晚排课节数比值为100.0代表该教室仅有白天被排课，为节能教室\n");
            printf("       2.未在表单中出现的教室在该周无排课，即教室未被启用\n");

            while(putili_node && putili_node->effi_rent<-0.5){//跳过无白天无夜晚结点
                putili_node = putili_node->next;
            }
            if(putili_node && putili_node->effi_rent<2){//若当前仍有结点且白天/夜晚《2（不合理）
                printf("\n\n  经过分析，以下教室在第%d周内的白日排课低于夜晚排课的两倍，认为其能效分配不合理\n  ",week);
                while(putili_node && putili_node->effi_rent<2){//遍历不合理结点
                    printf("  %s",putili_node->room_name);
                    putili_node = putili_node->next;
                }
            }
            else{
                printf("\n\n  经过分析，本周各教室排课的白天夜晚分布相对合理，能效分配合理！\n");
            }

        }

        else{
            printf("\n  第%d周%s无可分析教室！\n",week,building);
        }
    }
    else{
        ShowModule(*(plabel_result+1), 2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: StatTeacherValidity
 * 函数功能: 执行教师排课合理性分析的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatTeacherValidity(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"统计完成","确认"},
                                  {"统计失败，未查询到教师授课信息","确认"}
                                 };
    int i,j;//计数器
    int flag_1=0;//记录是否有单周参与课堂过多的不合理情况
    int flag_2=0;//记录是否有参与课堂跨过午餐或晚餐时段的不合理情况
    int lesson_max[30];//储存每周上课节数

    int teacher_num=0;//教师数量
    int teacher_sum=0;//所有教师总课时
    float teacher_ave=0;//教师课时平均值
    float teacher_dx=0;//教师总课时方差


    TEACHER_NODE *pteacher_node=teacher_head;
    COURSE_NODE *pcourse_node=NULL;
    STATTEACHER_NODE *pstat_node=NULL;
    STATTEACHER_NODE *pstat_head=NULL;//分析信息链头指针

    for(;pteacher_node!=NULL;pteacher_node=pteacher_node->next){
        for(i=0;i<30;i++){
            lesson_max[i]=0;
        }
        pstat_node = (STATTEACHER_NODE*)malloc(sizeof(STATTEACHER_NODE));//新建结点
        strcpy(pstat_node->teacher_name,pteacher_node->teacher_name);
        strcpy(pstat_node->position,pteacher_node->position);
        pstat_node->lesson_sum=0;
        pstat_node->lesson_max=0;
        pstat_node->week_lesson_max=0;
        pstat_node->subject_num=0;
        //遍历课堂结点
        for(pcourse_node=pteacher_node->tcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->tcnext){//遍历统计该教室利用率
            for(i=1;i<30;i++){
                if(pcourse_node->week[i]){
                    for(j=1;j<=12;j++){
                        if(pcourse_node->lesson[j]){//若查询到一节课
                            pstat_node->lesson_sum++;
                            lesson_max[i]++;
                        }
                        if(pcourse_node->lesson[4]&&pcourse_node->lesson[5]){//若课堂跨越中午
                            pstat_node->subject_num=1;
                            strcpy(pstat_node->subject_name,pcourse_node->subject_name);
                            flag_2=1;
                        }
                        if(pcourse_node->lesson[8]&&pcourse_node->lesson[9]){//若课堂跨越傍晚
                            pstat_node->subject_num=2;
                            strcpy(pstat_node->subject_name,pcourse_node->subject_name);
                            flag_2=1;
                        }
                    }
                }
            }
        }
        for(i=0;i<30;i++){
            if(lesson_max[i]>pstat_node->lesson_max){
                pstat_node->lesson_max=lesson_max[i];
                pstat_node->week_lesson_max=i;
            }
        }
        if(pstat_node->lesson_max>20) flag_1=1;//存在授课超过20节的情况
        //链接结点
        pstat_node->next=pstat_head;
        pstat_head=pstat_node;
    }

    if(pstat_head != NULL){//若成功构建结果链表 对其排序并进行输出 （按总课时数降序排列
        STATTEACHER_NODE *pstat_node_prior;
        STATTEACHER_NODE *pstat_node_after;
        STATTEACHER_NODE *pstat_node_temp;
        STATTEACHER_NODE *pstat_node_cur;
        pstat_node_prior = pstat_head;
        pstat_node_temp = (STATTEACHER_NODE *)malloc(sizeof(STATTEACHER_NODE));/*用于交换结点的临时结点*/
        while (pstat_node_prior -> next != NULL){/*选择排序*/
            pstat_node_cur = pstat_node_prior;
            pstat_node_after = pstat_node_prior -> next;
            while (pstat_node_after != NULL){/*cur是(最大)地址*/
                if (pstat_node_cur ->lesson_sum < pstat_node_after ->lesson_sum){
                    pstat_node_cur = pstat_node_after;
                }
                pstat_node_after = pstat_node_after -> next;
            }
            if (pstat_node_cur != pstat_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pstat_node_temp = *pstat_node_prior;
                *pstat_node_prior = *pstat_node_cur;
                pstat_node_prior -> next = pstat_node_temp -> next;/*恢复prior->next指向的结点*/
                pstat_node_temp -> next = pstat_node_cur -> next;
                *pstat_node_cur = *pstat_node_temp;/*cur数据交换，->next指向不变*/
            }
            pstat_node_prior = pstat_node_prior -> next;
        }


        pstat_node = pstat_head;
        ShowModule(*plabel_result, 2);
        printf ("\n    分析所得教师任课信息：(按总课时数排序)\n\n");
        printf ("  教师姓名    教师职位    教授总课时    一周教授课时最大值    \n");
        for (;pstat_node != NULL; pstat_node = pstat_node ->next){
            printf("  %-10s", pstat_node->teacher_name);
            printf("  %-10s", pstat_node->position);
            printf("      %-12d", pstat_node->lesson_sum);
            printf("  第%d周 %-10d\n", pstat_node ->week_lesson_max,pstat_node->lesson_max);
            teacher_sum+=pstat_node->lesson_sum;
            teacher_num++;
        }

        //计算方差
        teacher_ave=(float)teacher_sum/teacher_num;
        for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
            teacher_dx+=((pstat_node->lesson_sum-teacher_ave)*(pstat_node->lesson_sum-teacher_ave));
        }
        teacher_dx=teacher_dx/teacher_num;
        printf("\n\n  教师平均总任课课时数为:%.3f，方差为:%.3f，",teacher_ave,teacher_dx);
        if(teacher_dx>1){
            printf("分析得各教师教学任务不够平均！\n");
        }
        else{
            printf("分析得各教师教学任务相对平均！\n");
        }

        //不合理性
        if(flag_1 || flag_2){//若存在不合理性
            printf("\n\n  此外经分析已有排课方案对以下教师不够合理，亟待调整：\n");
            if(flag_1){//若存在一周授课过多
                printf("\n  以下教师在一周内担任教学任务将超过指定课时，教学任务较繁重：\n");
                for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
                    if(pstat_node->lesson_max>20){
                        printf("    %s老师在第%d周担任了%d个课时的教学任务.\n",pstat_node->teacher_name,
                                                                          pstat_node->week_lesson_max,
                                                                          pstat_node->lesson_max);
                    }
                }
            }
            if(flag_2){//若存在授课跨越休息时间
                printf("\n  以下教师担任的课程可能跨过休息时间，不够合理：\n");
                for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
                    if(pstat_node->subject_num==1){
                        printf("    %s老师教授的 %s 排课跨越了午休时间.\n",pstat_node->teacher_name,pstat_node->subject_name);
                    }
                    if(pstat_node->subject_num==2){
                        printf("    %s老师教授的 %s 排课跨越了晚餐时间.\n",pstat_node->teacher_name,pstat_node->subject_name);
                    }
                }
            }
        }
    }
    else{
        ShowModule(*(plabel_result+1), 2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: StatClassValidity
 * 函数功能: 执行班级排课合理性分析的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatClassValidity(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"分析完成","确认"},
                                  {"分析失败，未查询到班级上课信息","确认"}
                                 };
    int class_i;
    int i,j;//计数器
    int lesson_max[30];//储存每周上课节数
    int flag=0;//判断是否有不合理排课情况出现
    int day_lesson[30][6];
    int max;
    int min;

    int class_num=0;//班级数量
    int class_sum=0;//所有班级总课时
    float class_ave=0;//班级课时平均值
    float class_dx=0;//班级总课时方差

    CLASS_NODE *pclass_node=class_head;
    COURSE_NODE *pcourse_node=NULL;
    STATCLASS_NODE *pstat_node=NULL;
    STATCLASS_NODE *pstat_head=NULL;//分析信息链头指针

    for(;pclass_node!=NULL;pclass_node=pclass_node->next){
        for(i=0;i<30;i++){
            lesson_max[i]=0;
            for(j=0;j<6;j++){
                day_lesson[i][j]=0;
            }
        }
        pstat_node = (STATCLASS_NODE*)malloc(sizeof(STATCLASS_NODE));//新建结点
        strcpy(pstat_node->class_name,pclass_node->class_name);
        pstat_node->lesson_sum=0;
        pstat_node->lesson_max=0;
        pstat_node->week_lesson_max=0;
        pstat_node->max_de_min=0;
        //遍历课堂结点
        for(pcourse_node=pclass_node->ccnext;pcourse_node!=NULL;pcourse_node=pcourse_node->ccnext[class_i]){//遍历统计该教室利用率
            for(i=1;i<30;i++){
                if(pcourse_node->week[i]){
                    for(j=1;j<=12;j++){
                        if(pcourse_node->lesson[j]){//若查询到一节课
                            pstat_node->lesson_sum++;
                            lesson_max[i]++;
                            day_lesson[i][pcourse_node->weekday]++;
                        }
                    }
                }
            }
            class_i=return_i(pcourse_node,pclass_node->class_name);
        }
        for(i=0;i<30;i++){
            if(lesson_max[i]>pstat_node->lesson_max){
                pstat_node->lesson_max=lesson_max[i];
                pstat_node->week_lesson_max=i;
            }
        }

        //赋值节数差
        for(i=1;i<30;i++){//遍历周数 计算每周差值
            max=0;
            min=13;
            for(j=1;j<6;j++){
                max=max>day_lesson[i][j]?max:day_lesson[i][j];
                min=min<day_lesson[i][j]?min:day_lesson[i][j];
            }
            day_lesson[i][0]=max-min;//记录每周节数差值
        }
        for(i=1;i<30;i++){//向结点中赋值
            if(day_lesson[i][0]>pstat_node->max_de_min){//若当前周差值最大
                pstat_node->max_de_min=day_lesson[i][0];
                pstat_node->week=i;
                pstat_node->les_max=0;
                pstat_node->les_min=13;
                for(j=1;j<6;j++){
                    if(day_lesson[i][j]>pstat_node->les_max){
                        pstat_node->les_max=day_lesson[i][j];
                        pstat_node->lesson_max_day=j;
                    }
                    if(day_lesson[i][j]<pstat_node->les_min){
                        pstat_node->les_min=day_lesson[i][j];
                        pstat_node->lesson_min_day=j;
                    }
                }
            }
        }

        //链接结点
        pstat_node->next=pstat_head;
        pstat_head=pstat_node;
    }

    if(pstat_head != NULL){//若成功构建结果链表 按班级名称排序并输出
        STATCLASS_NODE *pstat_node_prior;
        STATCLASS_NODE *pstat_node_after;
        STATCLASS_NODE *pstat_node_temp;
        STATCLASS_NODE *pstat_node_cur;
        pstat_node_prior = pstat_head;
        pstat_node_temp = (STATTEACHER_NODE *)malloc(sizeof(STATTEACHER_NODE));/*用于交换结点的临时结点*/
        while (pstat_node_prior -> next != NULL){/*选择排序*/
            pstat_node_cur = pstat_node_prior;
            pstat_node_after = pstat_node_prior -> next;
            while (pstat_node_after != NULL){/*cur是(最大)地址*/
                if (strcmp(pstat_node_cur ->class_name , pstat_node_after ->class_name)>0){
                    pstat_node_cur = pstat_node_after;
                }
                pstat_node_after = pstat_node_after -> next;
            }
            if (pstat_node_cur != pstat_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pstat_node_temp = *pstat_node_prior;
                *pstat_node_prior = *pstat_node_cur;
                pstat_node_prior -> next = pstat_node_temp -> next;/*恢复prior->next指向的结点*/
                pstat_node_temp -> next = pstat_node_cur -> next;
                *pstat_node_cur = *pstat_node_temp;/*cur数据交换，->next指向不变*/
            }
            pstat_node_prior = pstat_node_prior -> next;
        }


        ShowModule(*plabel_result, 2);
        printf ("\n    分析所得班级学习信息：(按班级名称排序)\n\n");
        printf ("    班级名称                总学时    一周课时最大值    \n");
        for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
            printf("  %-25s", pstat_node->class_name);
            printf("  %-10d", pstat_node->lesson_sum);
            printf("  第%d周 %-10d\n", pstat_node ->week_lesson_max,pstat_node->lesson_max);
            class_sum+=pstat_node->lesson_sum;
            class_num++;
            if(pstat_node->max_de_min>=6) flag=1;//记录存在不合理情况
        }


        //计算方差
        class_ave=(float)class_sum/class_num;
        for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
            class_dx+=((pstat_node->lesson_sum-class_ave)*(pstat_node->lesson_sum-class_ave));
        }
        class_dx=class_dx/class_num;
        printf("\n\n  班级平均总学习课时数为:%.3f，方差为:%.3f，",class_ave,class_dx);
        if(class_dx>1){
            printf("分析得各班级学习任务不够平均！\n");
        }
        else{
            printf("分析得各班级学习任务相对平均！\n");
        }

        //不合理性
        if(flag){//若存在不合理性
            printf("\n\n  此外经分析已有排课方案对以下班级不够合理，亟待调整：(仅分析周一至周五是否平均)\n");
            for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
                if(pstat_node->max_de_min>=6){
                printf("    %s在 第%d周 周%d与周%d 的排课课时数相差%d节，不够平均.\n",pstat_node->class_name,
                                                                                       pstat_node->week,
                                                                                       pstat_node->lesson_max_day,
                                                                                       pstat_node->lesson_min_day,
                                                                                       pstat_node->max_de_min);
                }
            }
        }

    }
    else{
        ShowModule(*(plabel_result+1), 2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**帮助模块*/
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"可通过快捷键调用菜单功能",
                           "可通过 关于 开启作者主页",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL AboutSys(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"作者信息：华中科技大学",
                           "计科校交1601班 刘逸帆",
                           "确认"
                          };
    char *plabel_choose[] = {"确认开启作者主页？",
                             "确认    取消"
                            };


    ShowModule(plabel_name, 3);

    if(ChooseModule(plabel_choose)){  //开启浏览器
        system("explorer https://github.com/yifaanleo/shujujiegou");
    }

    return bRet;
}




/*******************************************************************
**************************** 子 函 数 *****************************
*******************************************************************/

//文件
/**
 * 函数名称: SaveSysData
 * 函数功能: 保存五类基础数据.
 * 输入参数: hd 主链头结点指针
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL SaveSysData()
{
    int i=0;//计数器
    TEACHER_NODE *pteacher_node;
    CLASS_NODE *pclass_node;
    ROOM_NODE *proom_node;
    SUBJECT_NODE *psubject_node;
    COURSE_NODE *pcourse_node;

    FILE *pfout;

    //课程
    pfout = fopen(gp_subject_info_filename, "wb+");
    for (psubject_node = subject_head; psubject_node != NULL; psubject_node = psubject_node->next){/*保存课程信息*/
        fprintf(pfout,"%s %.1f %d\n",psubject_node->subject_name,psubject_node->subject_credits,psubject_node->subject_hours);
    }
    fclose(pfout);
    //教室
    pfout = fopen(gp_room_info_filename, "wb+");
    for (proom_node = room_head; proom_node != NULL; proom_node = proom_node->next){/*保存教室信息*/
        fprintf(pfout,"%s %s\n",proom_node->building,proom_node->room_name);
    }
    fclose(pfout);
    //教师
    pfout = fopen(gp_teacher_info_filename, "wb+");
    for (pteacher_node = teacher_head; pteacher_node != NULL; pteacher_node = pteacher_node->next){/*保存教师信息*/
        fprintf(pfout,"%s %s\n",pteacher_node->teacher_name,pteacher_node->position);
    }
    fclose(pfout);
    //班级
    pfout = fopen(gp_class_info_filename, "wb+");
    for (pclass_node = class_head; pclass_node != NULL; pclass_node = pclass_node->next){/*保存班级信息*/
        fprintf(pfout,"%s\n",pclass_node->class_name);
    }
    fclose(pfout);
    //课堂
    pfout = fopen(gp_course_info_filename, "wb+");
    for (pcourse_node = course_head; pcourse_node != NULL; pcourse_node = pcourse_node->next){/*保存课堂信息*/
        fprintf(pfout,"%s ",pcourse_node->subject_name);
        fprintf(pfout,"%s ",pcourse_node->building);
        fprintf(pfout,"%s ",pcourse_node->room_name);
        fprintf(pfout,"%s ",pcourse_node->teacher_name);
        fprintf(pfout,"%d ",pcourse_node->weekday);

        for(i=1;i<=12;i++){//节数
            if(pcourse_node->lesson[i]==1){
                fprintf(pfout,"%d.",i);
            }
        }
        fprintf(pfout," ");

        for(i=1;i<=29;i++){//周数
            if(pcourse_node->week[i]==1){
                fprintf(pfout,"%d.",i);
            }
        }

        fprintf(pfout," %d",pcourse_node->class_num);
        for(i=0;i<pcourse_node->class_num;i++){
            fprintf(pfout," %s",pcourse_node->class_name[i]);
        }
        fprintf(pfout,"\n");

    }
    fclose(pfout);

    return TRUE;
}

/**
 * 函数名称: BackupSysData
 * 函数功能: 将五类基础数据备份到数据文件.
 * 输入参数: filename 数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL BackupSysData(char *filename)
{
    int i=0;//计数器
    TEACHER_NODE *pteacher_node;
    CLASS_NODE *pclass_node;
    ROOM_NODE *proom_node;
    SUBJECT_NODE *psubject_node;
    COURSE_NODE *pcourse_node;

    char subject_info_filename[50];
    strcpy(subject_info_filename,filename);
    strcat(subject_info_filename,"subject.dat");
    char room_info_filename[50];
    strcpy(room_info_filename,filename);
    strcat(room_info_filename,"room.dat");
    char teacher_info_filename[50];
    strcpy(teacher_info_filename,filename);
    strcat(teacher_info_filename,"teacher.dat");
    char class_info_filename[50];
    strcpy(class_info_filename,filename);
    strcat(class_info_filename,"class.dat");
    char course_info_filename[50];
    strcpy(course_info_filename,filename);
    strcat(course_info_filename,"course.dat");

    FILE *pfout;

    //课程
    pfout = fopen(subject_info_filename, "wb+");
    for (psubject_node = subject_head; psubject_node != NULL; psubject_node = psubject_node->next){/*保存课程信息*/
        fprintf(pfout,"%s %.1f %d\n",psubject_node->subject_name,psubject_node->subject_credits,psubject_node->subject_hours);
    }
    fclose(pfout);
    //教室
    pfout = fopen(room_info_filename, "wb+");
    for (proom_node = room_head; proom_node != NULL; proom_node = proom_node->next){/*保存教室信息*/
        fprintf(pfout,"%s %s\n",proom_node->building,proom_node->room_name);
    }
    fclose(pfout);
    //教师
    pfout = fopen(teacher_info_filename, "wb+");
    for (pteacher_node = teacher_head; pteacher_node != NULL; pteacher_node = pteacher_node->next){/*保存教师信息*/
        fprintf(pfout,"%s %s\n",pteacher_node->teacher_name,pteacher_node->position);
    }
    fclose(pfout);
    //班级
    pfout = fopen(class_info_filename, "wb+");
    for (pclass_node = class_head; pclass_node != NULL; pclass_node = pclass_node->next){/*保存班级信息*/
        fprintf(pfout,"%s\n",pclass_node->class_name);
    }
    fclose(pfout);
    //课堂
    pfout = fopen(course_info_filename, "wb+");
    for (pcourse_node = course_head; pcourse_node != NULL; pcourse_node = pcourse_node->next){/*保存课堂信息*/
        fprintf(pfout,"%s ",pcourse_node->subject_name);
        fprintf(pfout,"%s ",pcourse_node->building);
        fprintf(pfout,"%s ",pcourse_node->room_name);
        fprintf(pfout,"%s ",pcourse_node->teacher_name);
        fprintf(pfout,"%d ",pcourse_node->weekday);

        for(i=1;i<=12;i++){//节数
            if(pcourse_node->lesson[i]==1){
                fprintf(pfout,"%d.",i);
            }
        }
        fprintf(pfout," ");

        for(i=1;i<=29;i++){//周数
            if(pcourse_node->week[i]==1){
                fprintf(pfout,"%d.",i);
            }
        }

        fprintf(pfout," %d",pcourse_node->class_num);
        for(i=0;i<pcourse_node->class_num;i++){
            fprintf(pfout," %s",pcourse_node->class_name[i]);
        }
        fprintf(pfout,"\n");

    }
    fclose(pfout);

    return TRUE;
}

/**
 * 函数名称: RestoreSysData
 * 函数功能: 从指定数据文件中恢复五类基础数据.
 * 输入参数: filename 存放备份数据的数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL RestoreSysData(char *filename)
{
    int i=0;//计数器
    int count=0;//计数器
    float credits;//学分
    int hours;//学时
    int weekday;//周几
    int class_num;//班级个数
    char subject_name[40],building[20],room_name[20],
         teacher_name[20],position[20],class_name[40];
         //课程名 教学楼 教室名
         //教师名 职位 班级名
    char lesson[100];//节数
    char week[100];//周数

    TEACHER_NODE *teacher_temp = teacher_head, *pTeacherNode,*pteacher_node;
    SUBJECT_NODE *subject_temp = subject_head, *pSubjectNode,*psubject_node;
    CLASS_NODE *class_temp = class_head, *pClassNode,*pclass_node;
    ROOM_NODE *room_temp = room_head, *pRoomNode,*proom_node;
    COURSE_NODE *course_temp = course_head, *pCourseNode;

    char subject_info_filename[50];
    strcpy(subject_info_filename,filename);
    strcat(subject_info_filename,"subject.dat");
    char room_info_filename[50];
    strcpy(room_info_filename,filename);
    strcat(room_info_filename,"room.dat");
    char teacher_info_filename[50];
    strcpy(teacher_info_filename,filename);
    strcat(teacher_info_filename,"teacher.dat");
    char class_info_filename[50];
    strcpy(class_info_filename,filename);
    strcat(class_info_filename,"class.dat");
    char course_info_filename[50];
    strcpy(course_info_filename,filename);
    strcat(course_info_filename,"course.dat");

    subject_head=NULL;
    room_head=NULL;
    teacher_head=NULL;
    class_head=NULL;
    course_head=NULL;

    FILE *pFile;
    int find;

    //读取课程信息
    if ((pFile = fopen(subject_info_filename, "rb")) == NULL)
    {
        printf("课程信息数据文件打开失败!\n");
        return FALSE;
    }
    printf("课程信息数据文件打开成功!\n");
    /*从数据文件中读课程信息数据，存入以先进先出方式建立的课程信息链中*/
    while (fscanf(pFile,"%s %f %d",subject_name,&credits,&hours)!=EOF)
    {
        //新节点赋值
        pSubjectNode = (SUBJECT_NODE *)malloc(sizeof(SUBJECT_NODE));
        strcpy(pSubjectNode->subject_name,subject_name);
        pSubjectNode->subject_credits=credits;
        pSubjectNode->subject_hours=hours;
        pSubjectNode->scnext=NULL;
        pSubjectNode->next=NULL;

        //链接
        //若是头结点
        if(subject_head==NULL){
            subject_head = pSubjectNode;
            subject_temp = subject_head;
            count++;
        }
        //否则为后续结点
        else{
            subject_temp -> next = pSubjectNode;
            subject_temp = subject_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (subject_head == NULL)
    {
        printf("课程信息数据文件加载失败!\n");
        return FALSE;
    }
    printf("课程信息数据文件加载成功!\n共导入%d条课程信息\n",count);
    count = 0;


    //读取教室信息
    if ((pFile = fopen(room_info_filename, "rb")) == NULL)
    {
        printf("教室信息数据文件打开失败!\n");
        return FALSE;
    }
    printf("教室信息数据文件打开成功!\n");
    /*从数据文件中读教室信息数据，存入以先进先出方式建立的教室信息链中*/
    while (fscanf(pFile,"%s %s",building,room_name)!=EOF)
    {
        //新节点赋值
        pRoomNode = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
        strcpy(pRoomNode->building,building);
        strcpy(pRoomNode->room_name,room_name);
        pRoomNode->rcnext=NULL;
        pRoomNode->next=NULL;

        //链接
        //若是头结点
        if(room_head==NULL){
            room_head = pRoomNode;
            room_temp = room_head;
            count++;
        }
        //否则为后续结点
        else{
            room_temp -> next = pRoomNode;
            room_temp = room_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (room_head == NULL)
    {
        printf("教室信息数据文件加载失败!\n");
        return FALSE;
    }
    printf("教室信息数据文件加载成功!\n共导入%d条教室信息\n",count);
    count = 0;


    //读取教师信息
    if ((pFile = fopen(teacher_info_filename, "rb")) == NULL)
    {
        printf("教师信息数据文件打开失败!\n");
        return FALSE;
    }
    printf("教师信息数据文件打开成功!\n");
    /*从数据文件中读教师信息数据，存入以先进先出方式建立的教师信息链中*/
    while (fscanf(pFile,"%s %s",teacher_name,position)!=EOF)
    {
        //新节点赋值
        pTeacherNode = (TEACHER_NODE *)malloc(sizeof(TEACHER_NODE));
        strcpy(pTeacherNode -> teacher_name,teacher_name);
        strcpy(pTeacherNode ->position,position);
        pTeacherNode -> next = NULL;
        pTeacherNode ->tcnext=NULL;

        //链接
        //若是头结点
        if(teacher_head==NULL){
            teacher_head = pTeacherNode;
            teacher_temp = teacher_head;
            count++;
        }
        //否则为后续结点
        else{
            teacher_temp -> next = pTeacherNode;
            teacher_temp = teacher_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (teacher_head == NULL)
    {
        printf("教师信息数据文件加载失败!\n");
        return FALSE;
    }
    printf("教师信息数据文件加载成功!\n共导入%d条教师信息\n",count);
    count = 0;


    //读取班级信息
    if ((pFile = fopen(class_info_filename, "rb")) == NULL)
    {
        printf("班级信息数据文件打开失败!\n");
        return FALSE;
    }
    printf("班级信息数据文件打开成功!\n");
    /*从数据文件中读班级信息数据，存入以先进先出方式建立的班级信息链中*/
    while (fscanf(pFile,"%s",class_name)!=EOF)
    {
        //新节点赋值
        pClassNode = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
        strcpy(pClassNode->class_name,class_name);
        pClassNode->ccnext=NULL;
        pClassNode->next=NULL;

        //链接
        //若是头结点
        if(class_head==NULL){
            class_head = pClassNode;
            class_temp = class_head;
            count++;
        }
        //否则为后续结点
        else{
            class_temp -> next = pClassNode;
            class_temp = class_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (class_head == NULL)
    {
        printf("班级信息数据文件加载失败!\n");
        return FALSE;
    }
    printf("班级信息数据文件加载成功!\n共导入%d条班级信息\n",count);
    count = 0;


    //读取课堂信息
    if ((pFile = fopen(course_info_filename, "rb")) == NULL)
    {
        printf("课堂信息数据文件打开失败!\n");
        return FALSE;
    }
    printf("课堂信息数据文件打开成功!\n");
    /*从数据文件中读课堂信息数据，存入以先进先出方式建立的课堂信息链中*/
    while (fscanf(pFile,"%s %s %s %s %d %s %s %d",subject_name,building,
                  room_name,teacher_name,&weekday, lesson, week, &class_num)!=EOF)
    {
        //新节点赋值
        pCourseNode = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        for(i=0;i<10;i++){//初始化
            pCourseNode->class_name[i][0]='\0';
        }
        strcpy(pCourseNode->subject_name,subject_name);
        strcpy(pCourseNode->building,building);
        strcpy(pCourseNode->room_name,room_name);
        strcpy(pCourseNode->teacher_name,teacher_name);
        pCourseNode->weekday=weekday;
        pCourseNode->class_num=class_num;
        ScanfLesson(pCourseNode->lesson,lesson);
        ScanfWeek(pCourseNode->week,week);
        for(i=0;i<class_num;i++){
            fscanf(pFile,"%s",pCourseNode->class_name[i]);
        }
        pCourseNode->scnext=NULL;
        pCourseNode->rcnext=NULL;
        pCourseNode->tcnext=NULL;
        for(i=0;i<10;i++){
            pCourseNode->ccnext[i]=NULL;
        }
        pCourseNode->prior=NULL;
        pCourseNode->next=NULL;

        //单链表中链接
        //若是头结点
        if(course_head==NULL){
            course_head = pCourseNode;
            course_temp = course_head;
            count++;
        }
        //否则为后续结点
        else{
            course_temp -> next = pCourseNode;
            course_temp ->next->prior=course_temp;
            course_temp = course_temp -> next;
            count++;
        }

        //pcourse与四类基本信息链接
        //课程
        psubject_node = SeekSubjectNode(subject_head,pCourseNode->subject_name);
        pCourseNode->scnext = psubject_node->scnext;
        psubject_node->scnext = pCourseNode;
        //班级
        for(i=0;i<class_num;i++){
            pclass_node = SeekClassNode(class_head,pCourseNode->class_name[i]);
            pCourseNode->ccnext[i]=pclass_node->ccnext;
            pclass_node->ccnext=pCourseNode;
        }
        //教师
        pteacher_node = SeekTeacherNode(teacher_head,pCourseNode->teacher_name);
        pCourseNode->tcnext=pteacher_node->tcnext;
        pteacher_node->tcnext=pCourseNode;
        //教室
        proom_node = SeekRoomNode(room_head,pCourseNode->room_name,pCourseNode->building);
        pCourseNode->rcnext=proom_node->rcnext;
        proom_node->rcnext=pCourseNode;
    }
    fclose(pFile);
    if (course_head == NULL)
    {
        printf("课堂信息数据文件加载失败!\n");
        return FALSE;
    }
    printf("课堂信息数据文件加载成功!\n共导入%d条课堂信息\n",count);
    count = 0;

    return TRUE;
}


//数据维护
/**
 * 函数名称: InsertSubjectNode
 * 函数功能: 在课程链表中插入一个课程信息结点.
 * 输入参数: hd 课程链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertSubjectNode(SUBJECT_NODE **hd)
{
    SUBJECT_NODE *psubject_node, *temp;
    psubject_node = (SUBJECT_NODE *)malloc(sizeof(SUBJECT_NODE));
    psubject_node -> scnext = NULL;
    psubject_node -> next = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入课程名称：");
    scanf("%s", psubject_node->subject_name);
    printf("\n  请输入课程学分：");
    scanf("%f", &psubject_node->subject_credits);
    printf("\n  请输入课程学时：");
    scanf("%d", &psubject_node->subject_hours);

    hidecursor();/*隐藏光标*/

    temp = *hd;
    if (*hd == NULL){/*如果没有头结点*/
        *hd = psubject_node;
        (*hd) -> next = NULL;
        (*hd) -> scnext = NULL;
    }
    else{
        while (temp != NULL){/*检验重复结点*/
            if (strcmp(temp ->subject_name, psubject_node ->subject_name) == 0){
                printf("  该课程信息已存在！\n");
                return FALSE;
            }
            temp = temp -> next;
        }
        psubject_node -> next = (*hd) -> next; /*插入新结点*/
        (*hd) -> next = psubject_node;
        psubject_node -> scnext = NULL;
    }
    return TRUE;
}

/**
 * 函数名称: ModifSubjectNode
 * 函数功能: 对指定的课程信息结点内容进行修改.
 * 输入参数: hd 课程链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 0表示修改失败
 *
 * 调用说明:
 */
int ModifSubjectNode(SUBJECT_NODE *hd)
{
    char subject_name[40];
    float subject_credits;
    int subject_hours;
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    SUBJECT_NODE *psubject_node,*psubject_temp;

    showcursor();/*显示光标*/

    printf("\n  请输入想要修改的课程名称：");
    scanf("%s", subject_name);

    hidecursor();/*隐藏光标*/

    psubject_node = SeekSubjectNode(hd, subject_name);   /*查找指定分类信息结点*/
    if (psubject_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    课程名称：%s\n", psubject_node ->subject_name);
        printf("    课程学分：%.1f\n", psubject_node ->subject_credits);
        printf("    课程学时：%d\n", psubject_node ->subject_hours);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }
        showcursor();/*显示光标*/
        printf("\n  请输入修改后的课程名称：");
        scanf("%s", subject_name);
        printf("\n  请输入修改后的课程学分：");
        scanf("%f", &subject_credits);
        printf("\n  请输入修改后的课程学时：");
        scanf("%d", &subject_hours);
        hidecursor();/*隐藏光标*/

        //检验重复结点
        psubject_temp=hd;
        while (psubject_temp != NULL){
            if (strcmp(psubject_temp ->subject_name, subject_name) == 0 &&
                strcmp(psubject_node->subject_name,subject_name)!=0){
                printf("  该课程信息已存在！\n");
                return 0;
            }
            psubject_temp = psubject_temp -> next;
        }

        //修改课程节点
        strcpy(psubject_node->subject_name,subject_name);
        psubject_node->subject_credits=subject_credits;
        psubject_node->subject_hours=subject_hours;

        //修改课堂节点
        COURSE_NODE *temp=psubject_node->scnext;//赋值头结点
        for(;temp!=NULL;temp=temp->scnext){
            strcpy(temp->subject_name,subject_name);
        }
        return 1;
    }
    else{
        printf("  未查询到该课程信息！\n");
        return 0;
    }
}

/**
 * 函数名称: DelSubjectNode
 * 函数功能: 从课程链表中删除指定的课程信息结点.
 * 输入参数: hd 课程链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除.
 *
 * 调用说明:
 */
int DelSubjectNode(SUBJECT_NODE **hd)
{
    char subject_name[40];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    SUBJECT_NODE *psubject_node_prior = NULL,
                 *psubject_node_current = *hd;

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的课程名称：");
    scanf("%s", subject_name);

    hidecursor();/*隐藏光标*/

    while (psubject_node_current != NULL
           && strcmp(psubject_node_current ->subject_name, subject_name) != 0){
        psubject_node_prior = psubject_node_current;
        psubject_node_current = psubject_node_current -> next;
    }
    if (psubject_node_current != NULL){  /*如果找到*/
        printf("\n  将要删除的信息：\n");
        printf("    课程名称：%s\n", psubject_node_current ->subject_name );
        printf("    课程学分：%.1f\n", psubject_node_current ->subject_credits );
        printf("    课程学时：%d\n", psubject_node_current ->subject_hours );
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }

        else{   /*删除信息*/
        if (psubject_node_prior == NULL){   /*如果位于课程单链上第一个位置*/
            while(psubject_node_current->scnext){//删除相关课堂结点
                DelCourseNodeS(psubject_node_current->scnext);
            }
            *hd = psubject_node_current -> next;
        }
        else{//否则位于其他位置
            while(psubject_node_current->scnext){//删除相关课堂结点
                DelCourseNodeS(psubject_node_current->scnext);
            }
            psubject_node_prior -> next = psubject_node_current -> next;
        }
        free(psubject_node_current);
        }

        return 1;
    }
    return 0;
}


/**
 * 函数名称: InsertRoomNode
 * 函数功能: 在教室链表中插入一个教室信息结点.
 * 输入参数: hd 教室链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertRoomNode(ROOM_NODE **hd)
{
    ROOM_NODE *proom_node, *temp;
    proom_node = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
    proom_node -> rcnext = NULL;
    proom_node -> next = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入教室所属教学楼名称：");
    scanf("%s", proom_node->building);
    printf("\n  请输入教室名称：");
    scanf("%s", proom_node->room_name);

    hidecursor();/*隐藏光标*/

    temp = *hd;
    if (*hd == NULL){/*如果没有头结点*/
        *hd = proom_node;
        (*hd) -> next = NULL;
        (*hd) -> rcnext = NULL;
    }
    else{
        while (temp != NULL){/*检验重复结点*/
            if (strcmp(temp ->room_name, proom_node->room_name) ==0 &&
                strcmp(temp->building,proom_node->building) == 0){
                printf("  该教室信息已存在！\n");
                return FALSE;
            }
            temp = temp -> next;
        }
        proom_node -> next = (*hd) -> next; /*插入新结点*/
        (*hd) -> next = proom_node;
        proom_node -> rcnext = NULL;
    }
    return TRUE;
}


/**
 * 函数名称: ModifRoomNode
 * 函数功能: 对指定的教室信息结点内容进行修改.
 * 输入参数: hd 教室链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 0表示修改失败
 *
 * 调用说明:
 */
int ModifRoomNode(ROOM_NODE *hd)
{
    char room_name[20];
    char building[20];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    ROOM_NODE *proom_node,*proom_temp;

    showcursor();/*显示光标*/

    printf("\n  请输入想要修改的教室所属教学楼：");
    scanf("%s", building);
    printf("\n  请输入想要修改的教室名称：");
    scanf("%s", room_name);

    hidecursor();/*隐藏光标*/

    proom_node = SeekRoomNode(hd, room_name, building);   /*查找指定分类信息结点*/
    if (proom_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    教室所属教学楼：%s\n", proom_node ->building);
        printf("    教室名称：%s\n", proom_node ->room_name);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }
        showcursor();/*显示光标*/
        printf("\n  请输入修改后的教学楼名称：");
        scanf("%s", building);
        printf("\n  请输入修改后的教室名称：");
        scanf("%s", room_name);
        hidecursor();/*隐藏光标*/

        //检验重复结点
        proom_temp=hd;
        while (proom_temp != NULL){
            if (strcmp(proom_temp ->room_name, room_name) ==0 &&
                strcmp(proom_temp->building,building) == 0 &&(
                strcmp(proom_node->room_name,room_name)!=0 ||
                strcmp(proom_node->building,building)!=0)){
                printf("  该教室信息已存在！\n");
                return 0;
            }
            proom_temp = proom_temp -> next;
        }

        //修改教室节点
        strcpy(proom_node ->building,building);
        strcpy(proom_node->room_name,room_name);

        //修改课堂节点
        COURSE_NODE *temp=proom_node->rcnext;//赋值头结点
        for(;temp!=NULL;temp=temp->rcnext){
            strcpy(temp->building,building);
            strcpy(temp->room_name,room_name);
        }
        return 1;
    }
    else{
        printf("  未查询到该教室信息！\n");
        return 0;
    }
}

/**
 * 函数名称: DelRoomNode
 * 函数功能: 从教室链表中删除指定的教室信息结点.
 * 输入参数: hd 教室链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除.
 *
 * 调用说明:
 */
int DelRoomNode(ROOM_NODE **hd)
{
    char building[20];
    char room_name[20];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    ROOM_NODE *proom_node_prior = NULL,
                 *proom_node_current = *hd;

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的教室所属教学楼：");
    scanf("%s", building);
    printf("\n  请输入要删除的教室名称：");
    scanf("%s", room_name);

    hidecursor();/*隐藏光标*/

    while (proom_node_current != NULL
           && (strcmp(proom_node_current ->room_name, room_name) != 0
           || strcmp(proom_node_current->building,building)!=0)){
        proom_node_prior = proom_node_current;
        proom_node_current = proom_node_current -> next;
    }
    if (proom_node_current != NULL){  /*如果找到*/
        printf("\n  将要删除的信息：\n");
        printf("    所属教学楼：%s\n", proom_node_current ->building );
        printf("    教室名称：%s\n", proom_node_current ->room_name );
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*删除信息*/
        if (proom_node_prior == NULL){   /*如果位于教室单链上第一个位置*/
            while(proom_node_current->rcnext){//删除相关课堂结点
                DelCourseNodeS(proom_node_current->rcnext);
            }
            *hd = proom_node_current -> next;
        }
        else{//否则位于其他位置
            while(proom_node_current->rcnext){//删除相关课堂结点
                DelCourseNodeS(proom_node_current->rcnext);
            }
            proom_node_prior -> next = proom_node_current -> next;
        }
        free(proom_node_current);
        }

        return 1;
    }
    return 0;
}

/**
 * 函数名称: InsertTeacherNode
 * 函数功能: 在教师链表中插入一个教师信息结点.
 * 输入参数: hd 教师链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertTeacherNode(TEACHER_NODE **hd)
{
    TEACHER_NODE *pteacher_node, *temp;
    pteacher_node = (TEACHER_NODE *)malloc(sizeof(TEACHER_NODE));
    pteacher_node -> tcnext = NULL;
    pteacher_node -> next = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入教师姓名：");
    scanf("%s", pteacher_node->teacher_name);
    printf("\n  请输入教师职位：");
    scanf("%s", pteacher_node->position);

    hidecursor();/*隐藏光标*/

    temp = *hd;
    if (*hd == NULL){/*如果没有头结点*/
        *hd = pteacher_node;
        (*hd) -> next = NULL;
        (*hd) -> tcnext = NULL;
    }
    else{
        while (temp != NULL){/*检验重复结点*/
            if (strcmp(temp -> teacher_name, pteacher_node -> teacher_name) == 0){
                printf("  该教师信息已存在！\n");
                return FALSE;
            }
            temp = temp -> next;
        }

        pteacher_node -> next = (*hd) -> next; /*插入新结点*/
        (*hd) -> next = pteacher_node;
        pteacher_node -> tcnext = NULL;
    }
    return TRUE;
}

/**
 * 函数名称: ModifTeacherNode
 * 函数功能: 对指定的教师信息结点内容进行修改.
 * 输入参数: hd 教师链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 0表示修改失败
 *
 * 调用说明:
 */
int ModifTeacherNode(TEACHER_NODE *hd)
{
    char teacher_name[20];
    char position[20];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    TEACHER_NODE *pteacher_node,*pteacher_temp;

    showcursor();/*显示光标*/

    printf("\n  请输入想要修改的教师姓名：");
    scanf("%s", teacher_name);

    hidecursor();/*隐藏光标*/

    pteacher_node = SeekTeacherNode(hd, teacher_name);   /*查找指定分类信息结点*/
    if (pteacher_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    教师姓名：%s\n", pteacher_node ->teacher_name);
        printf("    教师职位：%s\n", pteacher_node ->position);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }
        showcursor();/*显示光标*/
        printf("\n  请输入修改后的教师姓名：");
        scanf("%s", teacher_name);
        printf("\n  请输入修改后的教师职位：");
        scanf("%s", position);
        hidecursor();/*隐藏光标*/

        //检验重复结点
        pteacher_temp=hd;
        while (pteacher_temp != NULL){
            if (strcmp(pteacher_temp -> teacher_name,teacher_name) == 0 &&
                strcmp(pteacher_node->teacher_name,teacher_name)!=0){
                printf("  该教师信息已存在！\n");
                return 0;
            }
            pteacher_temp = pteacher_temp -> next;
        }

        //修改教师节点
        strcpy(pteacher_node->teacher_name,teacher_name);
        strcpy(pteacher_node->position,position);

        //修改课堂节点
        COURSE_NODE *temp=pteacher_node->tcnext;//赋值头结点
        for(;temp!=NULL;temp=temp->tcnext){
            strcpy(temp->teacher_name,teacher_name);
        }
        return 1;
    }
    else{
        printf("  未查询到该教师信息！\n");
        return 0;
    }
}

/**
 * 函数名称: DelTeacherNode
 * 函数功能: 从教师链表中删除指定的教师信息结点.
 * 输入参数: hd 教师链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除.
 *
 * 调用说明:
 */
int DelTeacherNode(TEACHER_NODE **hd)
{
    char teacher_name[20];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    TEACHER_NODE *pteacher_node_prior = NULL,
                 *pteacher_node_current = *hd;

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的教师姓名：");
    scanf("%s", teacher_name);

    hidecursor();/*隐藏光标*/

    while (pteacher_node_current != NULL
           && strcmp(pteacher_node_current ->teacher_name, teacher_name) != 0){
        pteacher_node_prior = pteacher_node_current;
        pteacher_node_current = pteacher_node_current -> next;
    }
    if (pteacher_node_current != NULL){  /*如果找到*/
        printf("\n  将要删除的信息：\n");
        printf("    教师姓名：%s\n", pteacher_node_current ->teacher_name );
        printf("    教师职位：%s\n", pteacher_node_current ->position );
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*删除信息*/
        if (pteacher_node_prior == NULL){   /*如果位于教师单链上第一个位置*/
            while(pteacher_node_current->tcnext){//删除相关课堂结点
                DelCourseNodeS(pteacher_node_current->tcnext);
            }
            *hd = pteacher_node_current -> next;
        }
        else{//否则位于其他位置
            while(pteacher_node_current->tcnext){//删除相关课堂结点
                DelCourseNodeS(pteacher_node_current->tcnext);
            }
            pteacher_node_prior -> next = pteacher_node_current -> next;
        }
        free(pteacher_node_current);
        }

        return 1;
    }
    return 0;
}

/**
 * 函数名称: InsertClassNode
 * 函数功能: 在班级链表中插入一个班级信息结点.
 * 输入参数: hd 班级链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertClassNode(CLASS_NODE **hd)
{
    CLASS_NODE *pclass_node, *temp;
    pclass_node = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
    pclass_node -> ccnext = NULL;
    pclass_node -> next = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入班级名称：");
    scanf("%s", pclass_node->class_name);

    hidecursor();/*隐藏光标*/

    temp = *hd;
    if (*hd == NULL){/*如果没有头结点*/
        *hd = pclass_node;
        (*hd) -> next = NULL;
        (*hd) -> ccnext = NULL;
    }
    else{
        while (temp != NULL){/*检验重复结点*/
            if (strcmp(temp ->class_name, pclass_node ->class_name) == 0){
                printf("  该班级信息已存在！\n");
                return FALSE;
            }
            temp = temp -> next;
        }
        pclass_node -> next = (*hd) -> next; /*插入新结点*/
        (*hd) -> next = pclass_node;
        pclass_node -> ccnext = NULL;
    }
    return TRUE;
}

/**
 * 函数名称: ModifClassNode
 * 函数功能: 对指定的班级信息结点内容进行修改.
 * 输入参数: hd 班级链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 0表示修改失败
 *
 * 调用说明:
 */
int ModifClassNode(CLASS_NODE *hd)
{
    int i;
    char class_name[40];
    char class_name_past[40];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    CLASS_NODE *pclass_node,*pclass_temp;

    showcursor();/*显示光标*/

    printf("\n  请输入想要修改的班级名称：");
    scanf("%s", class_name);

    hidecursor();/*隐藏光标*/

    strcpy(class_name_past,class_name);
    pclass_node = SeekClassNode(hd, class_name);   /*查找指定分类信息结点*/
    if (pclass_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    班级名称：%s\n", pclass_node ->class_name);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }
        showcursor();/*显示光标*/
        printf("\n  请输入修改后的班级名称：");
        scanf("%s", class_name);
        hidecursor();/*隐藏光标*/

        //检验重复结点
        pclass_temp=hd;
        while (pclass_temp != NULL){
            if (strcmp(pclass_temp ->class_name, class_name) == 0 &&
                strcmp(pclass_node->class_name,class_name)!= 0){
                printf("  该班级信息已存在！\n");
                return 0;
            }
            pclass_temp = pclass_temp -> next;
        }

        //修改班级节点
        strcpy(pclass_node->class_name,class_name);

        //修改课堂节点
        COURSE_NODE *temp=pclass_node->ccnext;//赋值头结点
        while(temp!=NULL){
            i=return_i(temp,class_name_past);
            strcpy(temp->class_name[i],class_name);
            temp=temp->ccnext[i];
        }
        return 1;
    }
    else{
        printf("  未查询到该班级信息！\n");
        return 0;
    }
}

/**
 * 函数名称: DelClassNode
 * 函数功能: 从班级链表中删除指定的班级信息结点.
 * 输入参数: hd 班级链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除.
 *
 * 调用说明:
 */
int DelClassNode(CLASS_NODE **hd)
{
    int class_i,j;
    char class_name[40];
    char class_name_past[40];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    CLASS_NODE *pclass_node_prior = NULL,
                 *pclass_node_current = *hd;
    COURSE_NODE *pcourse_node;
    COURSE_NODE *pcourse_temp;//用于存储将被删除的ccnext指针以继续删除后续class

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的班级名称：");
    scanf("%s", class_name);
    strcpy(class_name_past,class_name);

    hidecursor();/*隐藏光标*/

    while (pclass_node_current != NULL
           && strcmp(pclass_node_current ->class_name, class_name) != 0){
        pclass_node_prior = pclass_node_current;
        pclass_node_current = pclass_node_current -> next;
    }
    if (pclass_node_current != NULL){  /*如果找到*/
        printf("\n  将要删除的信息：\n");
        printf("    班级名称：%s\n", pclass_node_current ->class_name );
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*删除信息*/
            if (pclass_node_prior == NULL){   /*如果位于班级单链上第一个位置*/
                pcourse_temp=pclass_node_current->ccnext;
                while(pcourse_temp){
                    pcourse_node=pcourse_temp;//node为当前处理结点
                    //若下一结点仅有待删除的class
                    if(pcourse_node->class_num==1){
                        pcourse_temp=pcourse_node->ccnext[0];//存储将被删除的ccnext指针
                        DelCourseNodeS(pcourse_node);
                    }
                    //若下一结点中含有多个class
                    else{
                        class_i=return_i(pcourse_node,class_name_past);
                        pcourse_temp=pcourse_node->ccnext[class_i];//存储将被删除的ccnext指针
                        for(j=class_i;j<9;j++){//删除结点中对应class信息
                            strcpy(pcourse_node->class_name[j],pcourse_node->class_name[j+1]);
                            pcourse_node->ccnext[j]=pcourse_node->ccnext[j+1];
                        }
                        pcourse_node->class_name[j][0]='\0';
                        pcourse_node->ccnext[j]=NULL;
                        pcourse_node->class_num--;
                    }
                }
                *hd = pclass_node_current -> next;
            }
            else{//否则位于其他位置
                pcourse_temp=pclass_node_current->ccnext;
                while(pcourse_temp){
                    pcourse_node=pcourse_temp;//node为当前处理结点
                    //若下一结点仅有待删除的class
                    if(pcourse_node->class_num==1){
                        pcourse_temp=pcourse_node->ccnext[0];//存储将被删除的ccnext指针
                        DelCourseNodeS(pcourse_node);
                    }
                    //若下一结点中含有多个class
                    else{
                        class_i=return_i(pcourse_node,class_name_past);
                        pcourse_temp=pcourse_node->ccnext[class_i];//存储将被删除的ccnext指针
                        for(j=class_i;j<9;j++){//删除结点中对应class信息
                            strcpy(pcourse_node->class_name[j],pcourse_node->class_name[j+1]);
                            pcourse_node->ccnext[j]=pcourse_node->ccnext[j+1];
                        }
                        pcourse_node->class_name[j][0]='\0';
                        pcourse_node->ccnext[j]=NULL;
                        pcourse_node->class_num--;
                    }
                }
                pclass_node_prior -> next = pclass_node_current -> next;
            }
            free(pclass_node_current);
        }

        return 1;
    }
    return 0;
}


/**
 * 函数名称: InsertCourseNode
 * 函数功能: 在课堂链表中插入一个课堂信息结点，并令教师、班级、教室、课程链中对应结点指向新课堂结点.
 * 输入参数: hd 课堂链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertCourseNode(COURSE_NODE **hd)
{
    int class_i;
    int i=0,j=0,k;//计数器
    int weekday=0;
    int les_start=0,les_end=0;
    int week_start=0,week_end=0;
    int week[50];

    SUBJECT_NODE *psubject_node;
    CLASS_NODE *pclass_node;
    TEACHER_NODE *pteacher_node;
    ROOM_NODE *proom_node;
    COURSE_NODE *pcourse_node, *temp;

    pcourse_node = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
    pcourse_node->scnext=NULL;
    for(i=0;i<10;i++){
        pcourse_node->ccnext[i]=NULL;
    }
    pcourse_node->tcnext=NULL;
    pcourse_node->rcnext=NULL;
    pcourse_node->next = NULL;
    pcourse_node->prior= NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入课程名称：");
    scanf("%s", pcourse_node->subject_name);
    printf("\n  请输入教室所属教学楼：");
    scanf("%s", pcourse_node->building);
    printf("\n  请输入教室名称：");
    scanf("%s", pcourse_node->room_name);
    printf("\n  请输入教师姓名：");
    scanf("%s", pcourse_node->teacher_name);

    pcourse_node->class_num=0;
    for(i=0;i<10;i++){//初始化
        pcourse_node->class_name[i][0]='\0';
    }
    printf("\n  请输入班级名称(空格或换行间隔 文件尾结束输入)：");
    i=0;
    while(scanf("%s", pcourse_node->class_name[i])!=EOF){
        i++;
    }
    pcourse_node->class_num=i;

    printf("\n  请输入课程开设在周几(1~7)：");
    scanf("%d", &weekday);
    printf("\n  请输入课程开始节数(1~12)：");
    scanf("%d", &les_start);
    printf("\n  请输入课程结束节数(1~12)：");
    scanf("%d", &les_end);
    printf("\n  请输入课程周数(1~29 空格或换行间隔 文件尾结束输入)：");
    i=0;
    while(scanf("%d",&week[i])!=EOF){
        if(week[i]<1 ||week[i]>29){
            printf("  输入周数格式有误！\n");
            return FALSE;
        }
        i++;
    }

    hidecursor();/*隐藏光标*/

    //判断输入时间格式
    if(weekday<1 || weekday>7 ||
       les_start<1 || les_start>12 || les_end<1 || les_end>12 ||
       les_start>les_end ){
        printf("  输入课堂时间格式(周几或节数)有误！\n");
        return FALSE;
    }

    //设置课堂时间
    pcourse_node->weekday = weekday;
    for(j=0;j<=12;j++){//初始化
        pcourse_node->lesson[j]=0;
    }
    for(j=0;j<=29;j++){//初始化
        pcourse_node->week[j]=0;
    }
    for(j=les_start;j<=les_end;j++){
        pcourse_node->lesson[j]=1;
    }
    for(j=0;j<i;j++){
        pcourse_node->week[week[j]]=1;
    }
    //week[0]记录起始周数
    for(i=1;i<=29;i++){
        if(pcourse_node->week[i]){
            pcourse_node->week[0]=i;
            break;
        }
    }



    //判断时间不冲突
    //课程
    psubject_node = SeekSubjectNode(subject_head,pcourse_node->subject_name);
    if(psubject_node == NULL){//未查询到课程
        printf("  未在系统中查找到对应课程信息！\n");
        return FALSE;
    }


    //教室
    proom_node = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
    if(proom_node == NULL){//未查询到教室
        printf("  未在系统中查找到对应教室信息！\n");
        return FALSE;
    }
    temp=proom_node->rcnext;
    if(temp!=NULL){//该教室有相关课堂 判断时间是否冲突
        for(;temp!=NULL;temp=temp->rcnext){//遍历课程相关课堂
            if(temp->weekday==weekday){//若周几相同
                 for(i=1;i<=29;i++){//遍历周数
                    if(temp->week[i] && pcourse_node->week[i]){//若周数重合
                        for(j=les_start;j<=les_end;j++){//判断节数是否冲突
                            if(temp->lesson[j]){//若冲突
                                printf("  教室时间冲突！\n");
                                return FALSE;
                            }
                        }
                    }
                }
            }
        }
    }


    //教师
    pteacher_node = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
    if(pteacher_node == NULL){//未查询到教师
        printf("  未在系统中查找到对应教师信息！\n");
        return FALSE;
    }
    temp=pteacher_node->tcnext;
    if(temp!=NULL){//该教师有相关课堂 判断时间是否冲突
        for(;temp!=NULL;temp=temp->tcnext){//遍历课程相关课堂
            if(temp->weekday==weekday){//若周几相同
                 for(i=1;i<=29;i++){//遍历周数
                    if(temp->week[i] && pcourse_node->week[i]){//若周数重合
                        for(j=les_start;j<=les_end;j++){//判断节数是否冲突
                            if(temp->lesson[j]){//若冲突
                                printf("  教师时间冲突！\n");
                                return FALSE;
                            }
                        }
                    }
                }
            }
        }
    }

    //班级
    for(k=0;k<pcourse_node->class_num;k++){
        pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
        if(pclass_node == NULL){//未查询到班级
            printf("  未在系统中查找到对应班级信息！\n");
            return FALSE;
        }
        temp=pclass_node->ccnext;
        if(temp!=NULL){//该班级有相关课堂 判断时间是否冲突
            class_i=return_i(temp,pcourse_node->class_name[k]);
            for(;temp!=NULL;class_i=return_i(temp,pcourse_node->class_name[k]),temp=temp->ccnext[class_i]){//遍历课程相关课堂
                if(temp->weekday==weekday){//若周几相同
                    for(i=1;i<=29;i++){//遍历周数
                        if(temp->week[i] && pcourse_node->week[i]){//若周数重合
                            for(j=les_start;j<=les_end;j++){//判断节数是否冲突
                                if(temp->lesson[j]){//若冲突
                                    printf("  班级(%s)时间冲突！\n",pcourse_node->class_name[k]);
                                    return FALSE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //判断课堂节点是否重复(一天不能出现两节相同信息但节数不同的课堂
        temp=course_head;
        while (temp != NULL){/*检验重复结点*/
            if (strcmp(temp->subject_name,pcourse_node->subject_name)==0 &&
                strcmp(temp ->building, pcourse_node ->building) == 0 &&
                strcmp(temp->room_name,pcourse_node->room_name)==0 &&
                strcmp(temp->teacher_name,pcourse_node->teacher_name)==0&&
                temp->weekday ==pcourse_node->weekday){
                for(i=1;i<30;i++){
                    if(temp->week[i]&&pcourse_node->week[i]) {
                        printf("  该课堂信息已存在，可尝试修改已有课堂的时间信息！\n");
                        return 0;
                    }
                }
                }
            temp = temp -> next;
        }


    //将pcourse_node与四类基本信息链接
    //对应课程链接课堂
    pcourse_node->scnext = psubject_node->scnext;
    psubject_node->scnext = pcourse_node;
    //对应教室链接课堂
    pcourse_node->rcnext=proom_node->rcnext;
    proom_node->rcnext=pcourse_node;
    //对应教师链接课堂
    pcourse_node->tcnext=pteacher_node->tcnext;
    pteacher_node->tcnext=pcourse_node;
    //对应班级链接课堂
    for(k=0;k<pcourse_node->class_num;k++){
        pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
        pcourse_node->ccnext[k]=pclass_node->ccnext;
        pclass_node->ccnext=pcourse_node;
    }


    //课堂单链中添加课堂结点
    if(course_head==NULL){//若是第一个
        pcourse_node->prior=NULL;
        pcourse_node->next=NULL;
        course_head=pcourse_node;
    }
    else{//否则
        pcourse_node->prior=NULL;
        pcourse_node->next=course_head;
        pcourse_node->next->prior=pcourse_node;
        course_head=pcourse_node;
    }
    return TRUE;
}

/**
 * 函数名称: ModifCourseNode
 * 函数功能: 对指定的课堂信息结点内容进行修改.
 * 输入参数: hd 课堂链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 2表示取消修改
 *
 * 调用说明:
 */
int ModifCourseNode(COURSE_NODE *hd)
{
    int class_i;
    int i,j,k;//计数器
    int choose_num;
    char subject_name[40];
    char building[20];
    char room_name[20];
    char teacher_name[20];
    int week_start;
    int class_num;
    int weekday;//周几
    int les_start;//课堂开始节数（修改课堂时间
    int les_end;//课堂结束节数（修改课堂时间
    int week[50];//课堂周数（修改课堂时间
    char class_name[10][40];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    SUBJECT_NODE *psubject_node,*psubject_node_del;
    CLASS_NODE *pclass_node,*pclass_node_del;
    TEACHER_NODE *pteacher_node,*pteacher_node_del;
    ROOM_NODE *proom_node,*proom_node_del;
    COURSE_NODE *pcourse_node, *temp;
    pcourse_node = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));

    showcursor();/*显示光标*/

    printf("\n    此功能将通过课程名称、教室所在地、教师姓名、课堂起始时间\n  来唯一确定课堂信息并进行修改\n");
    printf("\n  请输入课程名称：");
    scanf("%s", subject_name);
    printf("\n  请输入教室所属教学楼：");
    scanf("%s", building);
    printf("\n  请输入教室名称：");
    scanf("%s", room_name);
    printf("\n  请输入教师姓名：");
    scanf("%s", teacher_name);
    printf("\n  请输入课堂位于周几：");
    scanf("%d", &weekday);
    printf("\n  请输入课堂起始周次：");
    scanf("%d", &week_start);

    hidecursor();/*隐藏光标*/

    //判断输入时间格式
    if(weekday<1 || weekday>7 ||
       week_start>29 || week_start<1 ){
        printf("  输入课堂时间格式有误！\n");
        return 0;
    }

    pcourse_node = SeekCourseNode(hd, subject_name, building, room_name,
                                  teacher_name, weekday, week_start);   /*查找指定课堂信息结点*/
    if (pcourse_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    课程名称：%s\n", pcourse_node ->subject_name);
        printf("    教室地址：%s %s\n",pcourse_node->building, pcourse_node ->room_name);
        printf("    教师姓名：%s\n", pcourse_node ->teacher_name);

        printf("    参与班级：%s\n", pcourse_node ->class_name[0]);
        for(i=1;i<pcourse_node->class_num;i++){
            if(pcourse_node->class_name[i][0]!='\0'){
                printf("              %s\n",pcourse_node->class_name[i]);
            }
        }

        printf("    课堂时间：周%d 节数：",pcourse_node->weekday);
        for(i=1;i<=12;i++){
            if(pcourse_node->lesson[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        printf("    课堂周次：");        for(i=1;i<=29;i++){
            if(pcourse_node->week[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }


        //修改
        showcursor();/*显示光标*/

        printf("\n  1.课程名称 2.教室地址 3.教师姓名 4.参与班级 5.课堂时间\n  请输入序号以选择欲修改的内容：");
        scanf("%d",&choose_num);

        if(choose_num==1){//修改课程名称
            printf("\n  请输入修改后的课程名称：");
            scanf("%s", subject_name);
            hidecursor();/*隐藏光标*/

            //判断课程已存在即可修改课程
            psubject_node = SeekSubjectNode(subject_head,subject_name);
            if(psubject_node == NULL){//未查询到课程
                printf("  未在系统中查找到目标课程信息！\n");
                return 0;
            }

            //若查询到 删除原来其与课程链的链接 并添加新的链接
            psubject_node_del = SeekSubjectNode(subject_head,pcourse_node->subject_name);
            //若课堂结点在课程链(子链)中无前驱
            if(pcourse_node == psubject_node_del->scnext){//从课程链中删除
                psubject_node_del->scnext=psubject_node_del->scnext->scnext;
            }
            //否则有前驱 遍历教室链子链寻找
            else{
                for(temp=psubject_node_del->scnext;temp->scnext;temp=temp->scnext){
                    if(temp->scnext == pcourse_node){//temp->next是待删除结点
                        temp->scnext=temp->scnext->scnext;
                        break;
                    }
                }
            }

            //修改为新课堂并链接课程
            strcpy(pcourse_node->subject_name,subject_name);
            pcourse_node->scnext = psubject_node->scnext;
            psubject_node->scnext = pcourse_node;

            return 1;
        }

        else if(choose_num==2){//修改教室地址
            printf("\n  请输入教室所属教学楼：");
            scanf("%s", building);
            printf("\n  请输入教室名称：");
            scanf("%s", room_name);
            hidecursor();/*隐藏光标*/

            //判断时间不冲突即可修改教室
            proom_node = SeekRoomNode(room_head,room_name,building);
            if(proom_node == NULL){//未查询到教室
                printf("  未在系统中查找到目标教室信息！\n");
                return 0;
            }
            temp=proom_node->rcnext;
            if(temp!=NULL){//该教室有相关课堂 判断时间是否冲突
                for(;temp!=NULL;temp=temp->rcnext){//遍历课程相关课堂
                    if(temp->weekday==weekday){//若周几相同
                         for(i=1;i<=29;i++){//遍历周数
                            if(temp->week[i] && pcourse_node->week[i]){//若周数重合
                                for(j=1;j<=12;j++){//判断节数是否冲突
                                    if(temp->lesson[j] && pcourse_node->lesson[j]){//若冲突
                                        printf("  教室时间冲突！\n");
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //若查询到 删除原来其与教室链的链接 并添加新的链接
            proom_node_del = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
            //若课堂结点在教室链(子链)中无前驱
            if(pcourse_node == proom_node_del->rcnext){//从教室链中删除
                proom_node_del->rcnext=proom_node_del->rcnext->rcnext;
            }
            //否则有前驱 遍历教室链子链寻找
            else{
                for(temp=proom_node_del->rcnext;temp->rcnext;temp=temp->rcnext){
                    if(temp->rcnext == pcourse_node){//temp->next是待删除结点
                        temp->rcnext=temp->rcnext->rcnext;
                        break;
                    }
                }
            }

            //对应教室链接课堂
            strcpy(pcourse_node->building,building);
            strcpy(pcourse_node->room_name,room_name);
            pcourse_node->rcnext=proom_node->rcnext;
            proom_node->rcnext=pcourse_node;

            return 1;
        }

        else if(choose_num==3){//修改教师姓名
            printf("\n  请输入教师姓名：");
            scanf("%s", teacher_name);
            hidecursor();/*隐藏光标*/
            //判断时间不冲突即可修改教师
            pteacher_node = SeekTeacherNode(teacher_head,teacher_name);
            if(pteacher_node == NULL){//未查询到教师
                printf("  未在系统中查找到目标教师信息！\n");
                return 0;
            }
            temp=pteacher_node->tcnext;
            if(temp!=NULL){//该教师有相关课堂 判断时间是否冲突
                for(;temp!=NULL;temp=temp->tcnext){//遍历课程相关课堂
                    if(temp->weekday==weekday){//若周几相同
                         for(i=1;i<=29;i++){//遍历周数
                            if(temp->week[i] && pcourse_node->week[i]){//若周数重合
                                for(j=1;j<=12;j++){//判断节数是否冲突
                                    if(temp->lesson[j] && pcourse_node->lesson[j]){//若冲突
                                        printf("  教师时间冲突！\n");
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //若查询到 删除原来其与教师链的链接 并添加新的链接
            pteacher_node_del = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
            //若课堂结点在教师链(子链)中无前驱
            if(pcourse_node == pteacher_node_del->tcnext){//从教师链中删除
                pteacher_node_del->tcnext=pteacher_node_del->tcnext->tcnext;
            }
            //否则有前驱 遍历教师链子链寻找
            else{
                for(temp=pteacher_node_del->tcnext;temp->tcnext;temp=temp->tcnext){
                    if(temp->tcnext == pcourse_node){//temp->next是待删除结点
                        temp->tcnext=temp->tcnext->tcnext;
                        break;
                    }
                }
            }

            //对应教师链接课堂
            strcpy(pcourse_node->teacher_name,teacher_name);
            pcourse_node->tcnext=pteacher_node->tcnext;
            pteacher_node->tcnext=pcourse_node;

            return 1;
        }

        else if(choose_num==4){//修改参与班级
            class_num=0;
            for(i=0;i<10;i++){//初始化
                class_name[i][0]='\0';
            }
            printf("\n  请输入班级名称(空格或换行间隔 文件尾结束输入)：");
            i=0;
            while(scanf("%s", class_name[i])!=EOF){
                i++;
            }
            class_num=i;
            hidecursor();/*隐藏光标*/
            //判断时间不冲突即可修改班级
            for(k=0;k<class_num;k++){
                pclass_node = SeekClassNode(class_head,class_name[k]);
                if(pclass_node == NULL){//未查询到班级
                    printf("  未在系统中查找到目标班级(%s)信息！\n",class_name[k]);
                    return 0;
                }
                temp=pclass_node->ccnext;
                if(temp!=NULL){//该班级有相关课堂 判断时间是否冲突
                    for(;temp!=NULL;class_i=return_i(temp,class_name[k]),temp=temp->ccnext[class_i]){//遍历课程相关课堂
                        if(temp->weekday==weekday &&
                           (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                            strcmp(temp->building,pcourse_node->building)!=0 ||
                            strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                            strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                            temp->week[0] != pcourse_node->week[0]
                            )
                           ){//若周几相同 且不可能为同一条课堂记录
                            for(i=1;i<=29;i++){//遍历周数
                                if(temp->week[i] && pcourse_node->week[i]){//若周数重合
                                    for(j=1;j<=12;j++){//判断节数是否冲突
                                        if(temp->lesson[j] && pcourse_node->lesson[j]){//若冲突
                                            printf("  %s时间冲突！\n",class_name[k]);
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //若查询到 删除原来其与班级链的链接 并添加新的链接
            for(i=0;i<pcourse_node->class_num;i++){//遍历课堂顶点中所有班级信息
                pclass_node_del = SeekClassNode(class_head,pcourse_node->class_name[i]);
                //若课堂结点在班级链(子链)中无前驱
                if(pcourse_node == pclass_node_del->ccnext){//从教室链中删除
                    class_i=return_i(pclass_node_del->ccnext,pcourse_node->class_name[i]);
                    pclass_node_del->ccnext=pclass_node_del->ccnext->ccnext[class_i];
                }
                //否则有前驱 遍历教室链子链寻找
                else{
                    class_i=return_i(pclass_node_del->ccnext,pcourse_node->class_name[i]);
                    temp=pclass_node_del->ccnext;
                    for(;temp->ccnext[class_i];
                        class_i=return_i(temp,pcourse_node->class_name[i]),temp=temp->ccnext){
                        if(temp->ccnext[class_i] == pcourse_node){//temp->next是待删除结点
                            temp->ccnext[class_i]=temp->ccnext[class_i]->ccnext[return_i(temp->ccnext[class_i],pcourse_node->class_name[i])];
                            break;
                        }
                    }
                }
            }
            //对应班级链接课堂
            //初始化course的班级域
            for(k=0;k<10;k++){
                pcourse_node->class_name[k][0]='\0';
                pcourse_node->ccnext[k]=NULL;
            }
            //赋值班级数与班级
            pcourse_node->class_num =class_num;
            for(k=0;k<class_num;k++){
                strcpy(pcourse_node->class_name[k],class_name[k]);
                pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
                pcourse_node->ccnext[k]=pclass_node->ccnext;
                pclass_node->ccnext=pcourse_node;
            }
            hidecursor();/*隐藏光标*/
            return 1;
        }

        else if(choose_num==5){//修改课堂时间
            //初始化课堂周数
            for(i=0;i<50;i++){
                week[i]=0;
            }

            printf("\n  请输入课程开设在周几(1~7)：");
            scanf("%d", &weekday);
            printf("\n  请输入课程开始节数(1~12)：");
            scanf("%d", &les_start);
            printf("\n  请输入课程结束节数(1~12)：");
            scanf("%d", &les_end);
            printf("\n  请输入课程周数(1~29 空格或换行间隔 文件尾结束输入)：");
            i=0;
            while(scanf("%d",&week[i])!=EOF){
                if(week[i]<1 ||week[i]>29){
                    printf("输入课堂周数格式有误！\n");
                    return 0;
                }
                i++;
            }

            //判断输入时间格式
            if(weekday<1 || weekday>7 ||
               les_start<1 || les_start>12 || les_end<1 || les_end>12 ||
               les_start>les_end ){
                printf("输入课堂时间格式有误！\n");
                hidecursor();/*隐藏光标*/
                return 0;
            }

            //设置课堂时间并暂时存储在time_temp内
            COURSE_NODE *time_temp;
            time_temp=(COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            //赋值
            time_temp->weekday = weekday;
            for(j=0;j<=12;j++){//初始化节数
                time_temp->lesson[j]=0;
            }
            for(j=0;j<=29;j++){//初始化周数
                time_temp->week[j]=0;
            }
            for(j=les_start;j<=les_end;j++){
                time_temp->lesson[j]=1;
            }
            for(j=0;j<i;j++){
                time_temp->week[week[j]]=1;
            }
            //week[0]记录起始周数
            for(i=1;i<=29;i++){
                if(time_temp->week[i]){
                    time_temp->week[0]=i;
                    break;
                }
            }

            //判断时间是否冲突
            //教室
            proom_node = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
            temp=proom_node->rcnext;
            if(temp!=NULL){//该教室有相关课堂 判断时间是否冲突
                for(;temp!=NULL;temp=temp->rcnext){//遍历课程相关课堂
                    if(temp->weekday==weekday){//若周几相同
                         for(i=1;i<=29;i++){//遍历周数
                            if(temp->week[i] && time_temp->week[i]){//若周数重合
                                for(j=les_start;j<=les_end;j++){//判断节数是否冲突
                                    if(temp->lesson[j] &&
                                       (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                                        strcmp(temp->building,pcourse_node->building)!=0 ||
                                        strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                                        strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                                        strcmp(temp->class_name[0],pcourse_node->class_name[0])!=0 ||
                                        temp->week[0] != pcourse_node->week[0]
                                        )){//若冲突(跳过待修改课堂信息的检测)
                                        printf("  教室时间冲突！\n");
                                        hidecursor();/*隐藏光标*/
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //教师
            pteacher_node = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
            temp=pteacher_node->tcnext;
            if(temp!=NULL){//该教师有相关课堂 判断时间是否冲突
                for(;temp!=NULL;temp=temp->tcnext){//遍历课程相关课堂
                    if(temp->weekday==weekday){//若周几相同
                         for(i=1;i<=29;i++){//遍历周数
                            if(temp->week[i] && time_temp->week[i]){//若周数重合
                                for(j=les_start;j<=les_end;j++){//判断节数是否冲突
                                    if(temp->lesson[j]&&
                                       (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                                        strcmp(temp->building,pcourse_node->building)!=0 ||
                                        strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                                        strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                                        strcmp(temp->class_name[0],pcourse_node->class_name[0])!=0 ||
                                        temp->week[0] != pcourse_node->week[0]
                                        )){//若冲突(跳过待修改课堂信息的检测)
                                        printf("  教师时间冲突！\n");
                                        hidecursor();/*隐藏光标*/
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //班级
            for(k=0;k<pcourse_node->class_num;k++){
                pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
                temp=pclass_node->ccnext;
                if(temp!=NULL){//该班级有相关课堂 判断时间是否冲突
                    class_i=return_i(temp,pcourse_node->class_name[k]);
                    for(;temp!=NULL;class_i=return_i(temp,pcourse_node->class_name[k]),temp=temp->ccnext[class_i]){//遍历课程相关课堂
                        if(temp->weekday==weekday){//若周几相同
                            for(i=1;i<=29;i++){//遍历周数
                                if(temp->week[i] && time_temp->week[i]){//若周数重合
                                    for(j=les_start;j<=les_end;j++){//判断节数是否冲突
                                        if(temp->lesson[j]&&
                                           (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                                            strcmp(temp->building,pcourse_node->building)!=0 ||
                                            strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                                            strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                                            strcmp(temp->class_name[0],pcourse_node->class_name[0])!=0 ||
                                            temp->week[0] != pcourse_node->week[0]
                                            )){//若冲突(跳过待修改课堂信息的检测)
                                            printf("  班级(%s)时间冲突！\n",pcourse_node->class_name[k]);
                                            hidecursor();/*隐藏光标*/
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            hidecursor();/*隐藏光标*/
            //判断课堂节点是否重复(一天不能出现两节相同信息但节数不同的课堂
            temp=course_head;
            while (temp != NULL){/*检验重复结点*/
                if (strcmp(temp->subject_name,pcourse_node->subject_name)==0 &&
                    strcmp(temp ->building, pcourse_node ->building) == 0 &&
                    strcmp(temp->room_name,pcourse_node->room_name)==0 &&
                    strcmp(temp->teacher_name,pcourse_node->teacher_name)==0&&
                    temp->weekday ==time_temp->weekday &&
                    (temp->weekday != pcourse_node->weekday ||
                     temp->week[0] != pcourse_node->week[0])){
                    for(i=1;i<30;i++){
                        if(temp->week[i]&&time_temp->week[i]) {
                            printf("  该课堂信息已存在，可尝试修改已有课堂的时间信息！\n");
                            return 0;
                        }
                    }
                }
                temp = temp -> next;
            }

            //修改pcourse_node的时间
            pcourse_node->weekday=time_temp->weekday;
            for(i=0;i<13;i++){
                pcourse_node->lesson[i]=time_temp->lesson[i];
            }
            for(i=0;i<30;i++){
                pcourse_node->week[i]=time_temp->week[i];
            }

            hidecursor();/*隐藏光标*/
            return 1;

        }

        else{//输入错误数字
            printf("      输入数字有误！");
            hidecursor();/*隐藏光标*/
            return 0;
        }
    }

    else{
        printf("  未查询到对应课堂信息！\n");
        hidecursor();/*隐藏光标*/
        return 0;
    }

}

/**
 * 函数名称: DelCourseNode
 * 函数功能: 从课堂链中删除指定的课堂信息结点.
 * 输入参数: hd 课堂链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除
 *
 * 调用说明: 根据课程名、地址、教师姓名、起始周次可以确定唯一的课堂信息
 */
int DelCourseNode(COURSE_NODE **hd)
{
    int i;//计数器
    char subject_name[40];
    char building[20];
    char room_name[20];
    char teacher_name[20];
    int week_start;
    int weekday;
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    COURSE_NODE *pcourse_node;

    showcursor();/*显示光标*/

    printf("\n    此功能将通过课程名称、教室所在地、教师姓名、课堂起始时间\n  来唯一确定课堂信息并进行删除\n");
    printf("\n  请输入课程名称：");
    scanf("%s", subject_name);
    printf("\n  请输入教室所属教学楼：");
    scanf("%s", building);
    printf("\n  请输入教室名称：");
    scanf("%s", room_name);
    printf("\n  请输入教师姓名：");
    scanf("%s", teacher_name);
    printf("\n  请输入课堂位于周几：");
    scanf("%d", &weekday);
    printf("\n  请输入课堂起始周次：");
    scanf("%d", &week_start);

    hidecursor();/*隐藏光标*/

    pcourse_node = SeekCourseNode(course_head,subject_name,building,room_name,teacher_name,weekday,week_start);

    if (pcourse_node != NULL){/*如果找到*/
        printf("\n  将要删除的信息：\n");
        printf("    课程名称：%s\n", pcourse_node ->subject_name);
        printf("    教室地址：%s\n", pcourse_node ->room_name);
        printf("    教师姓名：%s\n", pcourse_node ->teacher_name);

        printf("    参与班级：%s\n", pcourse_node ->class_name[0]);
        for(i=1;i<pcourse_node->class_num;i++){
            if(pcourse_node->class_name[i][0]!='\0'){
                printf("              %s\n",pcourse_node->class_name[i]);
            }
        }

        printf("    课堂时间：周%d 节数：",pcourse_node->weekday);
        for(i=1;i<=12;i++){
            if(pcourse_node->lesson[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        printf("    课堂周次：");        for(i=1;i<=29;i++){
            if(pcourse_node->week[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*调用函数删除信息*/
            DelCourseNodeS(pcourse_node);
        }
        return 1;
    }

    return 0;
}

/**
 * 函数名称: DelCourseNodeS
 * 函数功能: DelCourseNode的子函数.
 */
void DelCourseNodeS(COURSE_NODE *pcourse_node)
{
    int class_i;
    int find;
    int i=0,j=0,k;//计数器
    int weekday=0;
    int les_start=0,les_end=0;
    int week_start=0,week_end=0;
    int week[50];

    SUBJECT_NODE *psubject_node;
    CLASS_NODE *pclass_node;
    TEACHER_NODE *pteacher_node;
    ROOM_NODE *proom_node;
    COURSE_NODE *temp;


    //课程链中删除
    psubject_node = SeekSubjectNode(subject_head,(pcourse_node)->subject_name);
    //若课堂结点在课程链(子链)中无前驱
    if(pcourse_node == psubject_node->scnext){//从课程链中删除
        psubject_node->scnext=psubject_node->scnext->scnext;
    }
    //否则有前驱 遍历教室链子链寻找
    else{
        for(temp=psubject_node->scnext;temp->scnext;temp=temp->scnext){
            if(temp->scnext == pcourse_node){//temp->next是待删除结点
                temp->scnext=temp->scnext->scnext;
                break;
            }
        }
    }

    //教室链中删除
    proom_node = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
    //若课堂结点在教室链(子链)中无前驱
    if(pcourse_node == proom_node->rcnext){//从教室链中删除
        proom_node->rcnext=proom_node->rcnext->rcnext;
    }
    //否则有前驱 遍历教室链子链寻找
    else{
        for(temp=proom_node->rcnext;temp->rcnext;temp=temp->rcnext){
            if(temp->rcnext == pcourse_node){//temp->next是待删除结点
                temp->rcnext=temp->rcnext->rcnext;
                break;
            }
        }
    }

    //教师链中删除
    pteacher_node = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
    //若课堂结点在教师链(子链)中无前驱
    if(pcourse_node == pteacher_node->tcnext){//从教师链中删除
        pteacher_node->tcnext=pteacher_node->tcnext->tcnext;
    }
    //否则有前驱 遍历教师链子链寻找
    else{
        for(temp=pteacher_node->tcnext;temp->tcnext;temp=temp->tcnext){
            if(temp->tcnext == pcourse_node){//temp->next是待删除结点
                temp->tcnext=temp->tcnext->tcnext;
                break;
            }
        }
    }

    //班级链中删除
    for(i=0;i<pcourse_node->class_num;i++){//遍历课堂顶点中所有班级信息
        pclass_node = SeekClassNode(class_head,pcourse_node->class_name[i]);
        //若课堂结点在班级链(子链)中无前驱
        if(pcourse_node == pclass_node->ccnext){//从教室链中删除
            class_i=return_i(pclass_node->ccnext,pcourse_node->class_name[i]);
            pclass_node->ccnext=pclass_node->ccnext->ccnext[class_i];
        }
        //否则有前驱 遍历教室链子链寻找
        else{
            class_i=return_i(pclass_node->ccnext,pcourse_node->class_name[i]);
            temp=pclass_node->ccnext;
            for(;temp->ccnext[class_i];
                class_i=return_i(temp,pcourse_node->class_name[i]),temp=temp->ccnext[class_i]){
                if(temp->ccnext[class_i] == pcourse_node){//temp->next是待删除结点
                    temp->ccnext[class_i]=temp->ccnext[class_i]->ccnext[return_i(temp->ccnext[class_i],pcourse_node->class_name[i])];
                    break;
                }
            }
        }
    }

    //删除课堂单链中结点
    //若仅有首结点
    if(course_head->next==NULL && course_head->prior==NULL){
        course_head=NULL;
        return 0;
    }
    //若是首结点
    if(pcourse_node->prior==NULL){//替换为后继节点
        course_head=course_head->next;
        course_head->prior=NULL;
        return 0;
    }
    //若待删除的是尾结点
    if(pcourse_node->next==NULL){
        pcourse_node->prior->next=NULL;
        return 0;
    }
    //否则删除的是普通结点
    pcourse_node->prior->next=pcourse_node->next;
    pcourse_node->next->prior=pcourse_node->prior;
    return 0;
}


//数据查询
/**
 * 函数名称: SeekSubjectNode
 * 函数功能: 按课程名称查找课程信息结点.
 * 输入参数: hd 课程链头指针
 *           subject_name 课程名称
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
SUBJECT_NODE *SeekSubjectNode(SUBJECT_NODE *hd, char *subject_name)
{
    SUBJECT_NODE *psubject_node = hd;
    int find = 0;

    while (psubject_node != NULL){
        if(strcmp(psubject_node ->subject_name, subject_name) == 0){
            find = 1;
            break;
        }
        psubject_node = psubject_node -> next;
    }

    if (find){  /*如果找到*/
        return psubject_node;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekSubjectNode2
 * 函数功能: 在班级相关课堂链中查找不重复的课程名称并排序.
 * 输入参数: hd 班级相关课程链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekSubjectNode2(COURSE_NODE *hd,char *class_name)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior= NULL;
    COURSE_NODE *pcourse_node_after=NULL;
    COURSE_NODE *pcourse_node_cur=NULL;
    COURSE_NODE *pcourse_node_temp=NULL;

    char subject_name[50][40];
    int class_i;
    int flag=0;
    int find = 0;
    int i,j=0;//计数器

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){
        for(i=0;i<j;i++){
            if(strcmp(pcourse_node->subject_name,subject_name[i])==0){//若课程已被记录
                flag=1;
            }
        }
        if(!flag){//若课程未被记录
            strcpy(subject_name[j++],pcourse_node->subject_name);
            pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            *pcourse_temp = *pcourse_node;//复制结点值
            pcourse_temp->next=pcourse_head;
            pcourse_head=pcourse_temp;
        }
        flag=0;
        class_i=return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)课程名称地址*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekRoomNode
 * 函数功能: 按教室名称与所属教学楼查找教室信息结点.
 * 输入参数: hd 教室链头指针
 *           room_name 教室名称
 *           building 教室所属教学楼
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
ROOM_NODE *SeekRoomNode(ROOM_NODE *hd, char *room_name ,char *building)
{
    ROOM_NODE *proom_node = hd;
    int find = 0;

    while (proom_node != NULL){
        if(strcmp(proom_node ->room_name, room_name) == 0&&
           strcmp(proom_node->building,building)==0){
            find = 1;
            break;
        }
        proom_node = proom_node -> next;
    }

    if (find){  /*如果找到*/
        return proom_node;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekRoomNode2
 * 函数功能: 查询教学楼中所有教室名称并排序.
 * 输入参数: hd 教室链头指针
 *           building 教室所属教学楼
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
ROOM_NODE *SeekRoomNode2(ROOM_NODE *hd, char *building)
{
    ROOM_NODE *proom_head=NULL;//头指针
    ROOM_NODE *proom_temp=NULL;//用于构建链表
    ROOM_NODE *proom_node=hd;//用于遍历原始链表

    //用于排序
    ROOM_NODE *proom_node_prior;
    ROOM_NODE *proom_node_after;
    ROOM_NODE *proom_node_cur;
    ROOM_NODE *proom_node_temp;

    while(proom_node !=NULL){
        if(strcmp(proom_node->building,building)==0){//若查询到对应教学楼
            proom_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
            *proom_temp = *proom_node;//复制结点值
            proom_temp->next=proom_head;
            proom_head=proom_temp;
        }
        proom_node=proom_node->next;
    }

    //若成功构建结果链表 对其排序
    if(proom_head){
        proom_node_prior = proom_head;
        proom_node_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));/*用于交换结点的临时结点*/

        while (proom_node_prior -> next != NULL){/*选择排序*/
            proom_node_cur = proom_node_prior;
            proom_node_after = proom_node_prior -> next;
            while (proom_node_after != NULL){/*cur是(最小)教室名称地址*/
                if (strcmp (proom_node_cur -> room_name, proom_node_after -> room_name) > 0){
                    proom_node_cur = proom_node_after;
                }
                proom_node_after = proom_node_after -> next;
            }

            if (proom_node_cur != proom_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *proom_node_temp = *proom_node_prior;
                *proom_node_prior = *proom_node_cur;
                proom_node_prior -> next = proom_node_temp -> next;/*恢复prior->next指向的结点*/
                proom_node_temp -> next = proom_node_cur -> next;
                *proom_node_cur = *proom_node_temp;/*cur数据交换，->next指向不变*/
            }
            proom_node_prior = proom_node_prior -> next;
        }
    }

    return proom_head;
}

/**
 * 函数名称: SeekRoomNode3
 * 函数功能: 在班级附属课堂链中，按课程名称查找教室信息结点.
 * 输入参数: hd 班级相关课程链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekRoomNode3(COURSE_NODE *hd,char *subject_name,char *class_name)
{
    int class_i;
    COURSE_NODE *pcourse_node=hd;//用于遍历课堂链
    COURSE_NODE *pcourse_head=NULL;//头指针
    COURSE_NODE *pcourse_temp=NULL;//用于构建链表

    while(pcourse_node !=NULL){
        if(strcmp(pcourse_node->subject_name,subject_name)==0){//若查询到
            pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            *pcourse_temp = *pcourse_node;//复制结点值
            pcourse_temp->next=pcourse_head;
            pcourse_head=pcourse_temp;
        }
        class_i = return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekTeacherNode
 * 函数功能: 按教师姓名查找教师信息结点.
 * 输入参数: hd 教师链头指针
 *           teacher_name 教师姓名
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
TEACHER_NODE *SeekTeacherNode(TEACHER_NODE *hd, char *teacher_name)
{
    TEACHER_NODE *pteacher_node = hd;
    int find = 0;

    while (pteacher_node != NULL){
        if(strcmp(pteacher_node ->teacher_name, teacher_name) == 0){
            find = 1;
            break;
        }
        pteacher_node = pteacher_node -> next;
    }

    if (find){  /*如果找到*/
        return pteacher_node;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekTeacherNode2
 * 函数功能: 在班级相关课堂链中查找根据课程名称查找教师.
 * 输入参数: hd 班级相关课程链头指针
 *           subject_name 课程名称
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekTeacherNode2(COURSE_NODE *hd,char *subject_name,char *class_name)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    char teacher_name[10][20];
    int class_i;
    int flag=0;
    int i,j=0;//计数器

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){
        if(strcmp(pcourse_node->subject_name,subject_name)==0){//若查询到对应课程
            for(i=0;i<50;i++){
                if(strcmp(pcourse_node->teacher_name,teacher_name[i])==0){//若教师已被记录
                    flag=1;
                }
            }
            if(!flag){//若教师未被记录
                strcpy(teacher_name[j++],pcourse_node->teacher_name);
                pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
                *pcourse_temp = *pcourse_node;//复制结点值
                pcourse_temp->next=pcourse_head;
                pcourse_head=pcourse_temp;
            }
            flag=0;
        }
        class_i=return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)课程名称地址*/
                if (strcmp (pcourse_node_cur -> teacher_name, pcourse_node_after -> teacher_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekTeacherNode3
 * 函数功能: 在课程相关课堂链中查找并排序所有教师.
 * 输入参数: hd 课程相关课程链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekTeacherNode3(COURSE_NODE *hd)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    char teacher_name[10][20];
    int flag=0;
    int i,j=0;//计数器

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){
        for(i=0;i<50;i++){
            if(strcmp(pcourse_node->teacher_name,teacher_name[i])==0){//若教师已被记录
                flag=1;
            }
        }
        if(!flag){//若教师未被记录
            strcpy(teacher_name[j++],pcourse_node->teacher_name);
            pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            *pcourse_temp = *pcourse_node;//复制结点值
            pcourse_temp->next=pcourse_head;
            pcourse_head=pcourse_temp;
        }
        flag=0;
        pcourse_node=pcourse_node->scnext;
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        //对姓名进行排序
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)课程名称地址*/
                if (strcmp (pcourse_node_cur -> teacher_name, pcourse_node_after -> teacher_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }

        //对职位进行排序
//        pcourse_node_prior = pcourse_head;
//        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

//        while (pcourse_node_prior -> next != NULL){/*选择排序*/
//            pcourse_node_cur = pcourse_node_prior;
//            pcourse_node_after = pcourse_node_prior -> next;
//            while (pcourse_node_after != NULL){/*cur是(最大)课程名称地址*/
//                if (strcmp (pcourse_node_cur -> position, pcourse_node_after -> position) < 0){
//                    pcourse_node_cur = pcourse_node_after;
 //               }
 //               pcourse_node_after = pcourse_node_after -> next;
 //           }

//            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
//                *pcourse_node_temp = *pcourse_node_prior;
//                *pcourse_node_prior = *pcourse_node_cur;
//                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
//                pcourse_node_temp -> next = pcourse_node_cur -> next;
//                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
//            }
//            pcourse_node_prior = pcourse_node_prior -> next;
//        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekClassNode
 * 函数功能: 按班级名称查找班级信息结点.
 * 输入参数: hd 班级链头指针
 *           class_name 教师姓名
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
CLASS_NODE *SeekClassNode(CLASS_NODE *hd, char *class_name)
{
    CLASS_NODE *pclass_node = hd;
    int find = 0;

    while (pclass_node != NULL){
        if(strcmp(pclass_node ->class_name, class_name) == 0){
            find = 1;
            break;
        }
        pclass_node = pclass_node -> next;
    }

    if (find){  /*如果找到*/
        return pclass_node;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekClassNode2
 * 函数功能: 在课程相关课堂链中查找并排序所有班级.
 * 输入参数: hd 课程相关课堂链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
CLASS_NODE *SeekClassNode2(COURSE_NODE *hd)
{
    COURSE_NODE *pcourse_node=NULL;//用于遍历课堂链表
    CLASS_NODE *pclass_node=NULL;
    CLASS_NODE *pclass_head=NULL;
    CLASS_NODE *pclass_temp=NULL;

    //用于排序
    CLASS_NODE *pclass_node_prior;
    CLASS_NODE *pclass_node_after;
    CLASS_NODE *pclass_node_cur;
    CLASS_NODE *pclass_node_temp;

    char class_name[50][40];
    int flag=0;
    int i,j,k=0;//计数器

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){
        for(j=0;j<pcourse_node->class_num;j++){
            for(i=0;i<k;i++){
                if(strcmp(pcourse_node->class_name[j],class_name[i])==0){//若班级已被记录
                    flag=1;
                }
            }
            if(!flag){//若班级未被记录
                strcpy(class_name[k++],pcourse_node->class_name[j]);
                pclass_node=SeekClassNode(class_head,pcourse_node->class_name[j]);
                pclass_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
                *pclass_temp = *pclass_node;//复制结点值
                pclass_temp->next=pclass_head;
                pclass_head=pclass_temp;
            }
            flag=0;
        }
        pcourse_node=pcourse_node->scnext;
    }

    //若成功构建结果链表 按班级名称对其排序
    if(pclass_head){
        pclass_node_prior = pclass_head;
        pclass_node_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));/*用于交换结点的临时结点*/

        while (pclass_node_prior -> next != NULL){/*选择排序*/
            pclass_node_cur = pclass_node_prior;
            pclass_node_after = pclass_node_prior -> next;
            while (pclass_node_after != NULL){/*cur是(最小)课程名称地址*/
                if (strcmp (pclass_node_cur -> class_name, pclass_node_after -> class_name) > 0){
                    pclass_node_cur = pclass_node_after;
                }
                pclass_node_after = pclass_node_after -> next;
            }

            if (pclass_node_cur != pclass_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pclass_node_temp = *pclass_node_prior;
                *pclass_node_prior = *pclass_node_cur;
                pclass_node_prior -> next = pclass_node_temp -> next;/*恢复prior->next指向的结点*/
                pclass_node_temp -> next = pclass_node_cur -> next;
                *pclass_node_cur = *pclass_node_temp;/*cur数据交换，->next指向不变*/
            }
            pclass_node_prior = pclass_node_prior -> next;
        }
    }

    return pclass_head;
}

/**
 * 函数名称: SeekClassNodeM
 * 函数功能: 按部分班级名称查找班级信息结点，并按班级名称排序.
 * 输入参数: hd 班级链头指针
 *           class_namem 部分班级姓名
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明: 根据班级姓名可以确定种植信息
 */
CLASS_NODE *SeekClassNodeM(CLASS_NODE *hd, char *class_namem)
{
    CLASS_NODE *pclass_head;/*结果链表头指针*/
    CLASS_NODE *pclass_temp;
    CLASS_NODE *pclass_node;

    pclass_head = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
    pclass_head = NULL;
    pclass_temp = NULL;
    pclass_node = hd;

    //用于排序
    CLASS_NODE *pclass_node_prior;
    CLASS_NODE *pclass_node_after;
    CLASS_NODE *pclass_node_cur;
    CLASS_NODE *pclass_node_temp;

    while (pclass_node != NULL){
        if ( (strstr (pclass_node -> class_name, class_namem) ) != NULL){/*建立结果链表*/
            pclass_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
            *pclass_temp = *pclass_node;
            pclass_temp -> next = pclass_head;
            pclass_head = pclass_temp;
        }
        pclass_node = pclass_node -> next;
    }

    //若成功构建结果链表 按班级名称对其排序
    if(pclass_head){
        pclass_node_prior = pclass_head;
        pclass_node_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));/*用于交换结点的临时结点*/

        while (pclass_node_prior -> next != NULL){/*选择排序*/
            pclass_node_cur = pclass_node_prior;
            pclass_node_after = pclass_node_prior -> next;
            while (pclass_node_after != NULL){/*cur是(最小)课程名称地址*/
                if (strcmp (pclass_node_cur -> class_name, pclass_node_after -> class_name) > 0){
                    pclass_node_cur = pclass_node_after;
                }
                pclass_node_after = pclass_node_after -> next;
            }

            if (pclass_node_cur != pclass_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pclass_node_temp = *pclass_node_prior;
                *pclass_node_prior = *pclass_node_cur;
                pclass_node_prior -> next = pclass_node_temp -> next;/*恢复prior->next指向的结点*/
                pclass_node_temp -> next = pclass_node_cur -> next;
                *pclass_node_cur = *pclass_node_temp;/*cur数据交换，->next指向不变*/
            }
            pclass_node_prior = pclass_node_prior -> next;
        }
    }

    return pclass_head;
}

/**
 * 函数名称: SeekCourseNode
 * 函数功能: 按课程名、地址、教师姓名、起始周次查找课堂信息结点.
 * 输入参数: hd 课堂链头指针
 *           subject_name 课程名称
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekCourseNode(COURSE_NODE *hd,char *subject_name,char *building,
                            char *room_name,char *teacher_name,int weekday,int week_start)
{
    COURSE_NODE *pcourse_node = hd;
    int find = 0;

    while (pcourse_node != NULL){
        if(strcmp(pcourse_node ->subject_name, subject_name) == 0 &&
           strcmp(pcourse_node->building,building)==0 &&
           strcmp(pcourse_node->room_name,room_name)==0 &&
           strcmp(pcourse_node->teacher_name,teacher_name)==0 &&
           pcourse_node->weekday == weekday &&
           pcourse_node->week[0] == week_start){
            find = 1;
            break;
        }
        pcourse_node = pcourse_node -> next;
    }

    if (find){  /*如果找到*/
        return pcourse_node;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekCourseNode_S
 * 函数功能: 排序课程链下的课堂链表.
 * 输入参数: hd 课程下附属的课堂链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekCourseNode_S(COURSE_NODE *hd)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){//复制结果链表

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//复制结点值
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        pcourse_node=pcourse_node->scnext;
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)教师名称地址*/
                if (strcmp (pcourse_node_cur -> teacher_name, pcourse_node_after -> teacher_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekCourseNode_R
 * 函数功能: 排序教室链下的课堂链表.
 * 输入参数: hd 教室结点下附属的课堂链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekCourseNode_R(COURSE_NODE *hd)//排序教室链下的课堂链表
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){//复制结果链表

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//复制结点值
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        pcourse_node=pcourse_node->rcnext;
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)教师名称地址*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekCourseNode_T
 * 函数功能: 排序教师链下的课堂链表.
 * 输入参数: hd 教师结点下附属的课堂链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekCourseNode_T(COURSE_NODE *hd)//排序教师链下的课堂链表
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){//复制结果链表

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//复制结点值
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        pcourse_node=pcourse_node->tcnext;
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)教师名称地址*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekCourseNode_C
 * 函数功能: 排序班级链下的课堂链表.
 * 输入参数: hd 班级结点下附属的课堂链头指针
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
COURSE_NODE *SeekCourseNode_C(COURSE_NODE *hd,char* class_name)//排序班级链下的课堂链表
{
    int class_i;
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //用于排序
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node用于遍历课堂链

    while(pcourse_node !=NULL){//复制结果链表

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//复制结点值
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        class_i=return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    //若成功构建结果链表 对其排序
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*用于交换结点的临时结点*/

        while (pcourse_node_prior -> next != NULL){/*选择排序*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur是(最小)教师名称地址*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*恢复prior->next指向的结点*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur数据交换，->next指向不变*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * 函数名称: SeekRestRoomNode
 * 函数功能: 查找指定时间的空闲教室并生成结果链表.
 * 输入参数: hd 教室链头指针
 *           week 周数
 *           lesson 节数
 * 输出参数: 无
 * 返 回 值: 查中时返回结果链表的地址, 否则返回NULL
 *
 * 调用说明:
 */
ROOM_NODE *SeekRestRoomNode(ROOM_NODE *hd, int week,int weekday,int lesson)//依据时间查找空闲教室
{
    ROOM_NODE *proom_head=NULL;//头指针
    ROOM_NODE *proom_temp=NULL;//用于构建链表
    ROOM_NODE *proom_node=hd;//用于遍历原始链表
    COURSE_NODE *pcourse_node;//用于遍历教室链附属的课堂链
    int flag=0;

    //用于排序
    ROOM_NODE *proom_node_prior;
    ROOM_NODE *proom_node_after;
    ROOM_NODE *proom_node_cur;
    ROOM_NODE *proom_node_temp;

    while(proom_node !=NULL){
        if(proom_node->rcnext){
            for(pcourse_node=proom_node->rcnext,flag=0;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){
                if(pcourse_node->week[week] &&pcourse_node->weekday==weekday &&pcourse_node->lesson[lesson]){
                    flag=1;
                }
            }
        }
        if(!flag){//若查询到对应空教室
            proom_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
            *proom_temp = *proom_node;//复制结点值
            proom_temp->next=proom_head;
            proom_head=proom_temp;
        }
        proom_node=proom_node->next;
    }

    //若成功构建结果链表 按教室名排序
    if(proom_head){
        proom_node_prior = proom_head;
        proom_node_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));/*用于交换结点的临时结点*/

        while (proom_node_prior -> next != NULL){/*选择排序*/
            proom_node_cur = proom_node_prior;
            proom_node_after = proom_node_prior -> next;
            while (proom_node_after != NULL){/*cur是(最小)教室名称地址*/
                if (strcmp (proom_node_cur -> room_name, proom_node_after -> room_name) > 0){
                    proom_node_cur = proom_node_after;
                }
                proom_node_after = proom_node_after -> next;
            }

            if (proom_node_cur != proom_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *proom_node_temp = *proom_node_prior;
                *proom_node_prior = *proom_node_cur;
                proom_node_prior -> next = proom_node_temp -> next;/*恢复prior->next指向的结点*/
                proom_node_temp -> next = proom_node_cur -> next;
                *proom_node_cur = *proom_node_temp;/*cur数据交换，->next指向不变*/
            }
            proom_node_prior = proom_node_prior -> next;
        }
    }

    //按教学楼排序
    if(proom_head){
        proom_node_prior = proom_head;
        proom_node_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));/*用于交换结点的临时结点*/

        while (proom_node_prior -> next != NULL){/*选择排序*/
            proom_node_cur = proom_node_prior;
            proom_node_after = proom_node_prior -> next;
            while (proom_node_after != NULL){/*cur是(最小)教学楼名称地址*/
                if (strcmp (proom_node_cur ->building, proom_node_after -> building) > 0){
                    proom_node_cur = proom_node_after;
                }
                proom_node_after = proom_node_after -> next;
            }

            if (proom_node_cur != proom_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *proom_node_temp = *proom_node_prior;
                *proom_node_prior = *proom_node_cur;
                proom_node_prior -> next = proom_node_temp -> next;/*恢复prior->next指向的结点*/
                proom_node_temp -> next = proom_node_cur -> next;
                *proom_node_cur = *proom_node_temp;/*cur数据交换，->next指向不变*/
            }
            proom_node_prior = proom_node_prior -> next;
        }
    }

    return proom_head;
}








//从文件中读取节数信息
void ScanfLesson(int *c_lesson,char *lesson)
{
    int i=0;
    for(i=0;i<13;i++){
        *(c_lesson+i)=0;
    }
    i=0;
    while(*lesson!='\0'){
        if(*lesson!='.'){//读取到数字
            i*=10;
            i+=(*lesson-'0');
        }
        if(*lesson=='.'){//读取到数字间的间隔
            *(c_lesson+i)=1;
            i=0;
        }
        lesson++;
    }
}

//从文件中读取周数信息
void ScanfWeek(int *c_week,char *week)
{
    int i=0;
    *c_week=30;
    for(i=1;i<30;i++){
        *(c_week+i)=0;
    }
    i=0;
    while(*week!='\0'){
        if(*week!='.'){//读取到数字
            i*=10;
            i+=(*week-'0');
        }
        if(*week=='.'){//读取到数字间的间隔
            *(c_week+i)=1;
            if(i<(*c_week)){
                *c_week=i;//课堂起始周次
            }
            i=0;
        }
        week++;
    }
}

//在课堂结点中通过教室名称定位指针数组中的指针
int return_i(COURSE_NODE *course_node,char*class_name)
{
    int find=0;
    int i=0;
    for(i=0;i<course_node->class_num;i++){
        if(strcmp(course_node->class_name[i],class_name)==0){
            find=i;
            break;
        }
    }

    return find;
}

