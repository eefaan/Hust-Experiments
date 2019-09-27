#include "vegetable.h"

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
    RunSys(&gp_head);             /*系统功能模块的选择及运行*/
    CloseSys(gp_head);            /*退出系统*/

    return 0;
}

/**
 * 函数名称: LoadData
 * 函数功能: 将代码表和三类基础数据从数据文件载入到内存缓冲区和十字链表中.
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
    Re = CreatList(&gp_head);
    gc_sys_state |= Re;
    gc_sys_state &= ~(4 + 8 + 16 - Re);
    if (gc_sys_state < ( 4 | 8 | 16))
    {  /*数据加载提示信息*/
        printf("\n系统基础数据不完整!\n");
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
 *           0  空链, 无数据
 *           4  已加载蔬菜分类信息数据，无蔬菜基本信息和菜农种植信息数据
 *           12 已加载蔬菜分类信息和蔬菜基本信息数据，无菜农种植信息数据
 *           28 三类基础数据都已加载
 *
 * 调用说明:
 */
int CreatList(SPECIES_NODE **phead)
{
    int speciesNum = 0, vegeNum = 0, plantNum = 0;
    SPECIES_NODE *hd = NULL, *pSpeciesNode, tmp1;
    VEGE_NODE *pVegeNode, tmp2;
    PLANT_NODE *pPlantNode, tmp3;
    FILE *pFile;
    int find;
    int re = 0;

    if ((pFile = fopen(gp_species_info_filename, "rb")) == NULL)
    {
        printf("蔬菜种类信息数据文件打开失败!\n");
        return re;
    }
    printf("蔬菜种类信息数据文件打开成功!\n");

    /*从数据文件中读蔬菜种类信息数据，存入以后进先出方式建立的主链中*/
    while (fread(&tmp1, sizeof(SPECIES_NODE), 1, pFile) == 1)
    {
        pSpeciesNode = (SPECIES_NODE *)malloc(sizeof(SPECIES_NODE));
        *pSpeciesNode = tmp1;
        pSpeciesNode->vnext = NULL;
        pSpeciesNode->next = hd;
        hd = pSpeciesNode;
        speciesNum++;
    }
    fclose(pFile);

    if (hd == NULL)
    {
        printf("蔬菜种类信息数据文件加载失败!\n");
        return re;
    }
    printf("蔬菜种类信息数据文件加载成功!\n共导入%d条蔬菜种类信息\n",speciesNum);
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_vege_info_filename, "rb")) == NULL)
    {
        printf("蔬菜基本信息数据文件打开失败!\n");
        return re;
    }
    printf("蔬菜基本信息数据文件打开成功!\n");
    re += 8;

    /*从数据文件中读取蔬菜基本信息数据，存入主链对应结点的蔬菜基本信息支链中*/
    while (fread(&tmp2, sizeof(VEGE_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出的蔬菜基本信息*/
        pVegeNode = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
        *pVegeNode = tmp2;
        pVegeNode->vege_id = ++VegeCount; /*自增蔬菜编号*/
        pVegeNode->pnext = NULL;

        /*在主链上查找该蔬菜所属种类对应的主链结点*/
        pSpeciesNode = hd;
        while (pSpeciesNode != NULL
               && strcmp(pSpeciesNode->species_id, pVegeNode->species_id) != 0)
        {
            pSpeciesNode = pSpeciesNode->next;
        }
        if (pSpeciesNode != NULL) /*如果找到，则将结点以后进先出方式插入蔬菜信息支链*/
        {
            pVegeNode->next = pSpeciesNode->vnext;
            pSpeciesNode->vnext = pVegeNode;
            vegeNum++;
        }
        else  /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pVegeNode);
        }
    }
    fclose(pFile);
    printf("共导入%d条蔬菜基本信息\n",vegeNum);

    if ((pFile = fopen(gp_plant_info_filename, "rb")) == NULL)
    {
        printf("菜农种植信息数据文件打开失败!\n");
        return re;
    }
    printf("菜农种植信息数据文件打开成功!\n");
    re += 16;

    /*从数据文件中读取菜农种植信息数据，存入蔬菜基本信息支链对应结点的种植支链中*/
    while (fread(&tmp3, sizeof(PLANT_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出的菜农种植信息*/
        pPlantNode = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        *pPlantNode = tmp3;
        pPlantNode -> plant_id = ++PlantCount; /*自增菜农编号*/

        /*查找蔬菜信息支链上对应种植信息结点*/
        pSpeciesNode = hd;
        find = 0;
        while (pSpeciesNode != NULL && find == 0)
        {
            pVegeNode = pSpeciesNode->vnext;
            while (pVegeNode != NULL && find == 0)
            {
                if (strcmp(pVegeNode->vege_name, pPlantNode->vege_name) == 0)
                {
                    find = 1;
                    break;
                }
                pVegeNode = pVegeNode->next;
            }
            pSpeciesNode = pSpeciesNode->next;
        }
        if (find)  /*如果找到，则将结点以后进先出方式插入菜农种植信息支链中*/
        {
            pPlantNode->next = pVegeNode->pnext;
            pVegeNode->pnext = pPlantNode;
            plantNum++;
        }
        else /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);
    printf("共导入%d条菜农种植信息\n",plantNum);
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
    //system("color F0\n");/*白底黑字*/
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*黄色前景和蓝色背景*/

    SetConsoleTextAttribute(gh_std_out, att);  /*设置控制台屏幕缓冲区字符属性*/

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
void CloseSys(SPECIES_NODE *hd)
{
    SPECIES_NODE *pSpeciesNode1 = hd, *pSpeciesNode2;
    VEGE_NODE *pVegeNode1, *pVegeNode2;
    PLANT_NODE *pPlantNode1, *pPlantNode2;

    while (pSpeciesNode1 != NULL) /*释放十字交叉链表的动态存储区*/
    {
        pSpeciesNode2 = pSpeciesNode1->next;
        pVegeNode1 = pSpeciesNode1->vnext;
        while (pVegeNode1 != NULL) /*释放蔬菜基本信息支链的动态存储区*/
        {
            pVegeNode2 = pVegeNode1->next;
            pPlantNode1 = pVegeNode1->pnext;
            while (pPlantNode1 != NULL) /*释放种植信息支链的动态存储区*/
            {
                pPlantNode2 = pPlantNode1->next;
                free(pPlantNode1);
                pPlantNode1 = pPlantNode2;
            }
            free(pVegeNode1);
            pVegeNode1 = pVegeNode2;
        }
        free(pSpeciesNode1);  /*释放主链结点的动态存储区*/
        pSpeciesNode1 = pSpeciesNode2;
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
void RunSys(SPECIES_NODE **phead)
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
 *           pHotArea 弹出窗口中热区信息存放的地址
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

/**
 * 函数名称: showcursor
 * 函数功能: 显示光标.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void showcursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = TRUE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);   /*显现光标*/
}

/**
 * 函数名称: hidecursor
 * 函数功能: 隐藏光标.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void hidecursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*隐藏光标*/

}

/**
 * 函数名称: ShowModule
 * 函数功能: 弹出菜单.
 * 输入参数: pString 菜单文字字符串
 *           n 菜单行数
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
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

/**
 * 函数名称: ChooseModule
 * 函数功能: 弹出选择菜单.
 * 输入参数: pString 菜单文字字符串
 * 输出参数: 无
 * 返 回 值:
 *
 * 调用说明:
 */
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

    pFunction[5] = MaintainSpeciesInfo;
    pFunction[6] = NULL;
    pFunction[7] = MaintainVegeInfo;
    pFunction[8] = NULL;
    pFunction[9] = MaintainPlantInfo;

    pFunction[10] = QuerySpeciesInfo;
    pFunction[11] = NULL;
    pFunction[12] = QueryVegeInfo;
    pFunction[13] = NULL;
    pFunction[14] = QueryPlantInfo;

    pFunction[15] = StatAreaAndHarvest;
    pFunction[16] = StatAreaAndHarvestM;
    pFunction[17] = StatNum;
    pFunction[18] = StatNutrition;
    pFunction[19] = StatPlant;

    pFunction[20] = HelpTopic;
    pFunction[21] = NULL;
    pFunction[22] = AboutVegeSys;

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
 * 函数名称: SaveData
 * 函数功能: 执行数据保存, 将蔬菜分类信息.蔬菜基本信息.种植信息三级链表分别存在三个数据文件中.
 * 输入参数:
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
    SaveSysData(gp_head);   /*保存信息*/
    ShowModule(plabel_result, 2);

    return bRet;
}

/**
 * 函数名称: BackupData
 * 函数功能: 执行数据备份, 将蔬菜分类信息、蔬菜基本信息、种植信息三类基础数据备份到一个数据文件中.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"备份成功！已备份至：",
                             "D:\VegeSysBackup.dat",
                             "确认"
                            };
    char *plabel_choose[] = {"确认备份信息吗？",
                             "确定    取消"
                            };
    char *filename = {"D:\VegeSysBackup.dat"};  /*备份路径*/

    if (ChooseModule(plabel_choose) == 0){  /*取消备份*/
        PopOff();
        return bRet;
    }
    PopOff();
    BackupSysData(gp_head, filename);   /*备份信息*/
    ShowModule(plabel_result, 3);

    return bRet;
}

/**
 * 函数名称: RestoreData
 * 函数功能: 执行数据恢复, 将蔬菜分类信息、蔬菜基本信息、种植信息三类基础数据回复到种植信息系统中.
 * 输入参数: 无
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
    char *filename = {"D:\VegeSysBackup.dat"};  /*备份文件所在路径*/

    if (ChooseModule(plabel_choose) == 0){  /*取消恢复*/
        PopOff();
        return bRet;
    }
    PopOff();
    RestoreSysData(&gp_head, filename);   /*恢复信息*/
    ShowModule(plabel_result, 2);

    return bRet;
}

/**
 * 函数名称: ExitSys
 * 函数功能: 退出系统.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
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
 * 函数名称: MaintainSpeciesInfo
 * 函数功能: 执行蔬菜种类信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainSpeciesInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"蔬菜种类信息添加成功！","确认"},
                               {"操作失败，编号或种类名称已存在！","确认"},
                               {"蔬菜种类信息修改成功！","确认"},
                               {"修改失败，未查询到对应种类信息！","确认"},
                               {"蔬菜种类信息删除成功！","确认"},
                               {"操作失败，未查询到对应种类信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();
    scanf("%d",&chooseNum);
    fflush(stdin);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入蔬菜种类信息*/
        flag = InsertSpeciesNode(&gp_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改蔬菜种类信息*/
        flag = ModifSpeciesNode(gp_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除蔬菜种类信息*/
        flag = DelSpeciesNode(&gp_head);
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
 * 函数名称: MaintainVegeInfo
 * 函数功能: 执行蔬菜基本信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainVegeInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"蔬菜基本信息添加成功！","确认"},
                               {"操作失败！","确认"},
                               {"蔬菜基本信息修改成功！","确认"},
                               {"修改失败，未查询到对应蔬菜信息！","确认"},
                               {"蔬菜基本信息删除成功！","确认"},
                               {"操作失败，未查询到对应蔬菜信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();/*显示光标*/
    scanf("%d",&chooseNum);
    fflush(stdin);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入蔬菜基本信息*/
        flag = InsertVegeNode(gp_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改蔬菜基本信息*/
        flag = ModifVegeNode(gp_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除蔬菜基本信息*/
        flag = DelVegeNode(gp_head);
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
 * 函数名称: MaintainPlantInfo
 * 函数功能: 执行菜农种植信息维护的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL MaintainPlantInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"菜农种植信息添加成功！","确认"},
                               {"操作失败！","确认"},
                               {"菜农种植信息修改成功！","确认"},
                               {"修改失败，未查询到对应种植信息！","确认"},
                               {"菜农种植信息删除成功！","确认"},
                               {"操作失败，未查询到对应种植信息！","确认"},
                               {"无效指令，回到主菜单！","确认"}
                              };
    printf("\n  请通过键入数字选择您想要进行的操作\n     1 : 添加信息\n     2 : 修改信息\n     3 : 删除信息\n\n  键入数字：");

    showcursor();  /*显现光标*/
    scanf("%d",&chooseNum);
    fflush(stdin);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*插入菜农种植信息*/
        flag = InsertPlantNode(gp_head);
        if(flag){   /*插入成功*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*插入失败*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*修改菜农种植信息*/
        flag = ModifPlantNode(gp_head);
        if(flag == 1){   /*修改成功*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*取消修改*/;}
        else{   /*修改失败*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*删除菜农种植信息*/
        flag = DelPlantNode(gp_head);
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
 * 函数名称: QuerySpeciesInfo
 * 函数功能: 执行蔬菜分类信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QuerySpeciesInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char species_id[6];
    SPECIES_NODE *pspecies_node;
    pspecies_node = NULL;

    showcursor();/*显示光标*/
    printf("\n  本模块将通过分类编号查询分类信息\n");
    printf("\n  请输入分类编号：");
    scanf("%[^\n]", species_id);
    getchar();
    hidecursor();/*隐藏光标*/

    pspecies_node = SeekSpeciesNode(gp_head, species_id);

    if(pspecies_node != NULL){/*如果找到*/
        printf ("\n  查询到的分类信息：\n");
        printf ("    分类编号：%s\n", pspecies_node -> species_id);
        printf ("    分类名称：%s\n", pspecies_node -> species_name);
        ShowModule(*plabel_result, 2);
    }
    else{/*如果未找到*/
        printf ("\n  未查询到对应分类信息！\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryVegeInfo
 * 函数功能: 执行蔬菜基本信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryVegeInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char species_id[6];
    char vege_nutrim[100];
    char vege_namem[20];
    SPECIES_NODE *pspecies_node;/*用于依据分类编号查找分类名称*/
    VEGE_NODE *pvege_node;/*结果链表*/
    pvege_node = NULL;
    int ChooseNum = 0;

    showcursor();/*显示光标*/

    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1 : 通过蔬菜部分名称查找\n");
    printf("    2 : 通过分类码和部分营养成分查找\n");
    printf("\n  请键入数字：");
    scanf("%d", &ChooseNum);
    fflush(stdin);

    if (ChooseNum == 1){
        printf ("\n  请输入蔬菜部分名称：");
        scanf ("%[^\n]", vege_namem);
        getchar();
        pvege_node = SeekVegeNodeM1(gp_head, vege_namem);/*查找并建立结果链表*/
    }
    else if (ChooseNum == 2){
        printf ("\n  请输入分类编码：");
        scanf ("%[^\n]", species_id);
        getchar();
        printf ("\n  请输入蔬菜所含部分营养成分：");
        scanf ("%[^\n]", vege_nutrim);
        getchar();
        pvege_node = SeekVegeNodeM2(gp_head, species_id, vege_nutrim);/*查找并建立结果链表*/
    }
    else{
        printf ("\n  键入数字有误！\n");
        printf("\n  按任意键返回主菜单...\n");
        hidecursor();/*隐藏光标*/
        getch();
        ClearScreen();
        ShowMenu();

        return bRet;
    }

    hidecursor();/*隐藏光标*/

    if(pvege_node != NULL){/*如果找到*/
        ShowModule(*plabel_result, 2);
        printf ("\n\n  查询到的蔬菜信息：\n");
        printf ("    蔬菜编号    蔬菜名称    分类编号    所属分类    营养成分\n");
        for (;pvege_node != NULL; pvege_node = pvege_node -> next){
            pspecies_node = SeekSpeciesNode(gp_head, pvege_node -> species_id);
            printf("    %-10d", pvege_node -> vege_id);
            printf("  %-10s", pvege_node -> vege_name);
            printf("  %-10s", pvege_node -> species_id);
            printf("  %-10s", pspecies_node -> species_name);
            printf("  %-10s\n", pvege_node -> nutrition);
        }
    }
    else{/*如果未找到*/
        printf ("\n  未查询到对应蔬菜信息！\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * 函数名称: QueryPlantInfo
 * 函数功能: 执行蔬菜种植信息查询的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL QueryPlantInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"查询完成","确认"},
                                  {"查询失败","确认"}
                                 };
    char vege_namem[20];
    char year[5];
    char vege_name[20];
    SPECIES_NODE *pspecies_node;/*用于依据分类编号查找分类名称*/
    VEGE_NODE *pvege_node;/*用于依据蔬菜名称查找蔬菜信息*/
    PLANT_NODE *pplant_node;/*结果链表*/
    pplant_node = NULL;
    int ChooseNum = 0;

    showcursor();/*显示光标*/

    printf("\n  通过键入数字选择查询方式：\n");
    printf("    1 : 通过蔬菜部分名称和种植年份查找\n");
    printf("    2 : 通过蔬菜名称查找，按年份降序显示\n\n");
    printf("  请键入数字：");
    scanf("%d", &ChooseNum);
    fflush(stdin);

    if (ChooseNum == 1){
        printf ("\n  请输入蔬菜部分名称：");
        scanf ("%[^\n]", vege_namem);
        getchar();
        printf ("\n  请输入种植年份：");
        scanf ("%[^\n]", year);
        getchar();
        pplant_node = SeekPlantNodeM1(gp_head, vege_namem, year);/*查找并建立结果链表*/
    }
    else if (ChooseNum == 2){
        printf ("\n  请输入蔬菜名称：");
        scanf ("%[^\n]", vege_name);
        getchar();
        pplant_node = SeekPlantNodeM2(gp_head, vege_name);/*查找并建立结果链表*/
    }
    else{
        printf ("\n  键入数字有误！\n");
        printf("\n  按任意键返回主菜单...\n");
        hidecursor();/*隐藏光标*/
        getch();
        ClearScreen();
        ShowMenu();

        return bRet;
    }

    hidecursor();/*隐藏光标*/

    if(pplant_node != NULL){/*如果找到*/
        ShowModule(*plabel_result, 2);
        printf ("\n  查询到的蔬菜信息：\n");
        printf ("    种植编号    菜农姓名    分类名称    蔬菜名称    种植年份    种植面积    收获重量\n");
        for (;pplant_node != NULL; pplant_node = pplant_node -> next){
            pvege_node = SeekVegeNode(gp_head, pplant_node -> vege_name);
            pspecies_node = SeekSpeciesNode(gp_head, pvege_node -> species_id);
            printf("    %-10d", pplant_node -> plant_id);
            printf("  %-10s", pplant_node -> plant_name);
            printf("  %-10s", pspecies_node -> species_name);
            printf("  %-10s", pplant_node -> vege_name);
            printf("  %-10s", pplant_node -> year);
            printf("  %-10d", pplant_node -> area);
            printf("  %-10f\n", pplant_node -> harvest);
        }
    }
    else{/*如果未找到*/
        printf ("\n  未查询到对应蔬菜信息\n");
        printf ("  或该蔬菜无种植信息!\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  按任意键返回主菜单...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}



/**数据统计模块*/

/**
 * 函数名称: StatAreaAndHarvest
 * 函数功能: 统计某年份各种蔬菜的种植总面积与总产量的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatAreaAndHarvest(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"统计完成","确认"},
                                  {"统计失败，在该年份未查询到种植信息","确认"}
                                 };
    char year[5];
    TOTAL_NODE *ptotal_node;
    ptotal_node = NULL;

    showcursor();/*显示光标*/
    printf ("\n  本模块将通过种植年份统计相关种植数据\n");
    printf ("\n  请输入年份：");
    scanf ("%[^\n]", year);
    getchar();
    hidecursor();/*隐藏光标*/

    ptotal_node = Stat1(gp_head, year);/*创建结果链表*/

    if(ptotal_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  统计到的种植信息 (按重量降序排列)：\n");
        printf ("    分类名称    种植面积    收获重量\n");
        for (;ptotal_node != NULL; ptotal_node = ptotal_node ->next){
            printf("    %-10s", ptotal_node -> species_name);
            printf("  %-10d", ptotal_node -> total_area);
            printf("  %-10f\n", ptotal_node -> total_harvest);
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
 * 函数名称: StatAreaAndHarvestM
 * 函数功能: 统计几年间某种蔬菜的种植总面积与总产量的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatAreaAndHarvestM(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"统计完成","确认"},
                                  {"统计失败，在对应年份未查询到其种植信息","确认"}
                                 };
    char vege_name[20];
    char year_head[5];
    char year_tail[5];
    TOTAL_NODE *ptotal_node;
    ptotal_node = NULL;

    showcursor();/*显示光标*/
    printf ("\n  本模块将通过蔬菜名称、起止年份统计相关种植数据\n");
    printf ("\n  请输入蔬菜名称：");
    scanf ("%[^\n]", vege_name);
    getchar();
    printf ("\n  请输入起始种植年份：");
    scanf ("%[^\n]", year_head);
    getchar();
    printf ("\n  请输入终止种植年份：");
    scanf ("%[^\n]", year_tail);
    getchar();
    hidecursor();/*隐藏光标*/

    ptotal_node = Stat2(gp_head, vege_name, year_head, year_tail);/*创建结果链表*/

    if(ptotal_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  统计到的种植信息：\n");
        printf ("    蔬菜名称    分类名称    种植面积    收获重量\n");
        for (;ptotal_node != NULL; ptotal_node = ptotal_node ->next){
            printf("    %-10s", ptotal_node -> vege_name);
            printf("  %-10s", ptotal_node -> species_name);
            printf("  %-10d", ptotal_node -> total_area);
            printf("  %-10f\n", ptotal_node -> total_harvest);
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
 * 函数名称: StatNum
 * 函数功能: 统计各种蔬菜分类所含蔬菜数量的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatNum(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"统计完成","确认"},
                                  {"统计失败，未查询到蔬菜信息","确认"}
                                 };

    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    VEGE_COUNT *pvege_count;
    VEGE_COUNT *pvege_count_head;

    pspecies_node = NULL;
    pvege_node = NULL;
    pvege_count = pvege_count_head;
    pvege_count_head = (VEGE_COUNT *)malloc(sizeof(VEGE_COUNT));
    pvege_count_head = NULL;

    for (pspecies_node = gp_head; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*二重循环依次搜索主链每个结点的蔬菜基本信息支链*/
        pvege_node = pspecies_node -> vnext;
        pvege_count = (VEGE_COUNT *)malloc(sizeof(VEGE_COUNT));
        pvege_count -> numcount = 0;
        strcpy(pvege_count -> species_id, pspecies_node -> species_id);
        strcpy(pvege_count -> species_name, pspecies_node -> species_name);

        while (pvege_node != NULL){/*计数*/
            pvege_count -> numcount++;
            pvege_node = pvege_node -> next;
        }

        pvege_count -> next = pvege_count_head;/*后进先出*/
        pvege_count_head = pvege_count;
    }

    if(pvege_count_head != NULL){
        printf ("\n  统计到的蔬菜数量信息：\n");
        printf ("    分类编号    分类名称    蔬菜数量\n");
        for (;pvege_count_head != NULL; pvege_count_head = pvege_count_head -> next){
            printf("    %-10s", pvege_count_head -> species_id);
            printf("  %-10s", pvege_count_head -> species_name);
            printf("  %-10d\n", pvege_count_head -> numcount);
        }
        ShowModule(*plabel_result, 2);
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
 * 函数名称: StatNutrition
 * 函数功能: 统计含有某种营养成分的蔬菜的信息的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatNutrition(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"统计完成","确认"},
                                  {"统计失败，未查询到含有此营养成分的蔬菜信息","确认"}
                                 };
    char nutrim[100];
    SPECIES_NODE *pspecies_node;/*用于查找分类名称*/
    VEGE_NODE *pvege_node;
    pvege_node = NULL;

    showcursor();/*显示光标*/
    printf ("\n  本模块将通过蔬菜部分营养成分统计相关蔬菜信息\n");
    printf ("\n  请输入蔬菜所含部分营养成分：");
    scanf ("%[^\n]", nutrim);
    getchar();
    hidecursor();/*隐藏光标*/

    pvege_node = SeekVegeNodeM3(gp_head, nutrim);/*创建结果链表*/

    if(pvege_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  统计到的蔬菜信息：\n");
        printf ("    蔬菜名称    分类名称    营养成分\n");
        for (;pvege_node != NULL; pvege_node = pvege_node ->next){
            pspecies_node = SeekSpeciesNode(gp_head, pvege_node -> species_id);
            printf("    %-10s", pvege_node -> vege_name);
            printf("  %-10s", pspecies_node -> species_name);
            printf("  %-10s\n", pvege_node -> nutrition);
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
 * 函数名称: StatPlant
 * 函数功能: 统计某菜农的所有种植信息的功能函数.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL StatPlant(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"统计完成","确认"},
                                  {"统计失败，未查询到该菜农的种植信息","确认"}
                                 };
    char plant_name[20];
    SPECIES_NODE *pspecies_node;/*用于查找分类名称*/
    VEGE_NODE *pvege_node;/*用于查找蔬菜信息*/
    PLANT_NODE *pplant_node;
    pplant_node = NULL;

    showcursor();/*显示光标*/
    printf ("\n  本模块将通过菜农姓名统计相关种植信息\n");
    printf ("\n  请输入菜农姓名：");
    scanf ("%[^\n]", plant_name);
    getchar();
    hidecursor();/*隐藏光标*/

    pplant_node = SeekPlantNodeM3(gp_head, plant_name);/*创建结果链表*/

    if(pplant_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  统计到的种植信息：\n");
        printf ("    菜农姓名    蔬菜名称    分类名称    种植年份    种植面积    收获重量\n");
        for (;pplant_node != NULL; pplant_node = pplant_node -> next){
            pvege_node = SeekVegeNode(gp_head, pplant_node -> vege_name);
            pspecies_node = SeekSpeciesNode(gp_head, pvege_node -> species_id);
            printf("    %-10s", pplant_node -> plant_name);
            printf("  %-10s", pplant_node -> vege_name);
            printf("  %-10s", pspecies_node -> species_name);
            printf("  %-10s", pplant_node -> year);
            printf("  %-10d", pplant_node -> area);
            printf("  %-10f\n", pplant_node -> harvest);
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

/**
 * 函数名称: HelpTopic
 * 函数功能: 显示帮助信息.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值:
 *
 * 调用说明:
 */
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"·数据单位：面积(分)      ",
                           "            收成(公斤)    ",
                           "·系统支持中文输入        ",
                           "·系统支持含空格字符串输入",
                           "·ALT+字母可快捷选择菜单  ",
                           "确认"
                          };
    ShowModule(plabel_name, 6);
    return bRet;
}

/**
 * 函数名称: AboutVegeSys
 * 函数功能: 显示作者信息.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值:
 *
 * 调用说明:
 */
BOOL AboutVegeSys(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"·作者信息: ",
                           "·本菜农种植信息管理系统由",
                           "  华中科技大学  计算机学院",
                           "  校际交流班  刘逸帆  制作",
                           "·邮箱: lyf460315457@qq.com",
                           "确认"
                          };
    ShowModule(plabel_name, 6);
    return bRet;
}

/*******************************************************************
**************************** 子 函 数 *****************************
*******************************************************************/
//文件
/**
 * 函数名称: SaveSysData
 * 函数功能: 保存三类基础数据.
 * 输入参数: hd 主链头结点指针
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL SaveSysData(SPECIES_NODE *hd)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    FILE *pfout;

    pfout = fopen(gp_species_info_filename, "wb");
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node->next){/*保存蔬菜种类信息*/
        fwrite(pspecies_node, sizeof(SPECIES_NODE), 1, pfout);
    }
    fclose(pfout);

    pfout = fopen(gp_vege_info_filename, "wb");
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node->next){/*保存蔬菜基本信息*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            fwrite(pvege_node, sizeof(VEGE_NODE), 1, pfout);
            pvege_node = pvege_node->next;
        }
    }
    fclose(pfout);

    pfout = fopen(gp_plant_info_filename, "wb");
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node->next){/*保存菜农种植信息*/
        pvege_node = pspecies_node->vnext;
        while (pvege_node != NULL){
            pplant_node = pvege_node->pnext;
            while (pplant_node != NULL){
                fwrite(pplant_node, sizeof(PLANT_NODE), 1, pfout);
                pplant_node = pplant_node->next;
            }
            pvege_node = pvege_node->next;
        }
    }
    fclose(pfout);

    return TRUE;
}

/**
 * 函数名称: BackupSysData
 * 函数功能: 将系统代码表和三类基础数据备份到一个数据文件.
 * 输入参数: hd 主链头结点指针
 *           filename 数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL BackupSysData(SPECIES_NODE *hd, char *filename)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    unsigned species_node_num = 0;
    unsigned vege_node_num = 0;
    unsigned plant_node_num = 0;
    FILE *fp;

    /*遍历十字链，分别统计三种基础信息的记录总数*/
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){
        species_node_num++;
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            vege_node_num++;
            pplant_node = pvege_node -> pnext;
            while (pplant_node != NULL){
                plant_node_num++;
                pplant_node = pplant_node ->next;
            }
            pvege_node = pvege_node -> next;
        }
    }

    fp = fopen(filename, "wb+");

    /*保存三类基础数据的记录总数*/
    fwrite((void*)&species_node_num, sizeof(species_node_num), 1, fp);
    fwrite((void*)&vege_node_num, sizeof(vege_node_num), 1, fp);
    fwrite((void*)&plant_node_num, sizeof(plant_node_num), 1, fp);

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){  /*备份蔬菜分类信息*/
        fwrite((void*)pspecies_node, sizeof(SPECIES_NODE), 1, fp);
    }
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){  /*备份蔬菜基本信息*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            fwrite((void*)pvege_node, sizeof(VEGE_NODE), 1, fp);
            pvege_node = pvege_node -> next;
        }
    }
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){  /*备份菜农种植信息*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            pplant_node = pvege_node -> pnext;
            while (pplant_node != NULL){
                fwrite((void*)pplant_node, sizeof(PLANT_NODE), 1, fp);
                pplant_node = pplant_node -> next;
            }
            pvege_node = pvege_node -> next;
        }
    }
    fclose(fp);

    return TRUE;
}

/**
 * 函数名称: RestoreSysData
 * 函数功能: 从指定数据文件中恢复三类基础数据.
 * 输入参数: phead 主链头结点指针的地址
 *           filename 存放备份数据的数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL RestoreSysData(SPECIES_NODE **phead, char *filename)
{
    SPECIES_NODE *hd = NULL;
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    unsigned long species_node_num = 0;
    unsigned long vege_node_num = 0;
    unsigned long plant_node_num = 0;
    unsigned long ulloop;
    int handle;
    int find;

    if ((handle = open(filename, O_RDONLY | O_BINARY)) == -1){
        handle = open(filename, O_CREAT | O_BINARY, S_IREAD);
    }

    /*读取三种基础信息的记录数*/
    read(handle, (char*)&species_node_num, sizeof(species_node_num));
    read(handle, (char*)&vege_node_num, sizeof(vege_node_num));
    read(handle, (char*)&plant_node_num, sizeof(plant_node_num));

    /*读取蔬菜种类信息，建立十字链主链*/
    for (ulloop = 1; ulloop <= species_node_num; ulloop++){
        pspecies_node = (SPECIES_NODE *)malloc(sizeof(SPECIES_NODE));
        read(handle, (char*)pspecies_node, sizeof(SPECIES_NODE));
        pspecies_node -> vnext = NULL;
        pspecies_node -> next = hd;
        hd = pspecies_node;
    }
    *phead = hd;

    /*读取蔬菜基本信息，建立蔬菜信息支链*/
    for (ulloop = 1; ulloop <= vege_node_num; ulloop++) {
        pvege_node = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
        read(handle, (char*)pvege_node, sizeof(VEGE_NODE));
        pvege_node -> pnext = NULL;
        pspecies_node = hd;
        while (pspecies_node != NULL
               && strcmp(pspecies_node -> species_id, pvege_node -> species_id) !=0){
            pspecies_node = pspecies_node -> next;
        }

        if (pspecies_node != NULL){
            pvege_node -> next = pspecies_node -> vnext;
            pspecies_node -> vnext = pvege_node;
        }
        else{
            free(pvege_node);
        }
    }

    /*读取菜农种植信息，建立种植信息支链*/
    for (ulloop = 1; ulloop <= plant_node_num; ulloop++){
        pplant_node = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        read (handle, (char*)pplant_node, sizeof(PLANT_NODE));
        pspecies_node = hd;
        find = 0;

        while (pspecies_node != NULL && find ==0) {
            pvege_node = pspecies_node -> vnext;
            while (pvege_node != NULL && find == 0){
                if (strcmp(pvege_node -> vege_name, pplant_node -> vege_name) == 0){
                    find = 1;
                    break;
                }
                pvege_node = pvege_node -> next;
            }
            pspecies_node = pspecies_node ->next;
        }

        if(find){
            pplant_node -> next = pvege_node -> pnext;
            pvege_node -> pnext = pplant_node;
        }
        else{
            free(pplant_node);
        }
    }

    close(handle);
    SaveSysData(hd);    /*将内存中的数据保存到数据文件*/
    return TRUE;
}

//数据维护
/**
 * 函数名称: InsertSpeciesNode
 * 函数功能: 在十字链表中插入一个蔬菜分类信息结点.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertSpeciesNode(SPECIES_NODE **hd)
{
    SPECIES_NODE *pspecies_node, *temp;
    pspecies_node = (SPECIES_NODE *)malloc(sizeof(SPECIES_NODE));
    pspecies_node -> vnext = NULL;
    pspecies_node -> next = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入蔬菜分类编码：");
    scanf("%[^\n]", pspecies_node -> species_id);
    getchar();
    printf("\n  请输入蔬菜种类名称：");
    scanf("%[^\n]", pspecies_node -> species_name);
    getchar();

    hidecursor();/*隐藏光标*/

    temp = *hd;
    if (*hd == NULL){/*如果没有主结点*/
        *hd = pspecies_node;
        (*hd) -> next = NULL;
        (*hd) -> vnext = NULL;
    }
    else{
        while (temp != NULL){/*检验重复结点*/
            if (strcmp(temp -> species_id, pspecies_node -> species_id) == 0 ||
                strcmp(temp -> species_name, pspecies_node -> species_name) == 0){
                return FALSE;
            }
            temp = temp -> next;
        }
        pspecies_node -> next = (*hd) -> next; /*插入新结点*/
        (*hd) -> next = pspecies_node;
        pspecies_node -> vnext = NULL;
    }
    return TRUE;
}

/**
 * 函数名称: ModifSpeciesNode
 * 函数功能: 对指定的蔬菜分类信息结点内容进行修改.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 2表示取消修改
 *
 * 调用说明:
 */
int ModifSpeciesNode(SPECIES_NODE *hd)
{
    char species_id[6];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    SPECIES_NODE *pspecies_node;

    showcursor();/*显示光标*/

    printf("\n  请输入想要修改的蔬菜种类的分类编码：");
    scanf("%[^\n]", species_id);
    getchar();

    hidecursor();/*隐藏光标*/

    pspecies_node = SeekSpeciesNode(hd, species_id);   /*查找指定分类信息结点*/
    if (pspecies_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    分类编号：%s\n", pspecies_node -> species_id);
        printf("    分类名称：%s\n", pspecies_node -> species_name);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }
        showcursor();/*显示光标*/
        printf("\n  请输入修改后的分类名称：");
        scanf("%[^\n]", pspecies_node -> species_name);
        getchar();
        hidecursor();/*隐藏光标*/
        return 1;
    }
    else{
        return 0;
    }
}

/**
 * 函数名称: DelSpeciesNode
 * 函数功能: 从十字链表中删除指定的蔬菜分类信息结点.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除.
 *
 * 调用说明:
 */
int DelSpeciesNode(SPECIES_NODE **hd)
{
    char species_id[6];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    SPECIES_NODE *pspecies_node_prior = NULL,
                 *pspecies_node_current = *hd;

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的蔬菜分类编号：");
    scanf("%[^\n]", species_id);
    getchar();

    hidecursor();/*隐藏光标*/

    while (pspecies_node_current != NULL
           && strcmp(pspecies_node_current -> species_id, species_id) != 0){
        pspecies_node_prior = pspecies_node_current;
        pspecies_node_current = pspecies_node_current -> next;
    }
    if (pspecies_node_current != NULL){  /*如果找到*/
        printf("\n  将要删除的信息：\n");
        printf("    分类编号：%s\n", pspecies_node_current -> species_id);
        printf("    分类名称：%s\n", pspecies_node_current -> species_name);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*删除信息*/
            if (pspecies_node_prior == NULL){   /*如果位于蔬菜种类主链上第一个位置*/
                *hd = pspecies_node_current -> next;
            }
            else{
                pspecies_node_prior -> next = pspecies_node_current -> next;
            }
            free(pspecies_node_current);
        }
        return 1;
    }
    return 0;
}

/**
 * 函数名称: InsertVegeNode
 * 函数功能: 在十字链表中插入一个蔬菜基本信息结点.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertVegeNode(SPECIES_NODE *hd)
{
    SPECIES_NODE *pspecies_node;
    pspecies_node = NULL;
    VEGE_NODE *pvege_node;
    VEGE_NODE *pvege_temp;
    pvege_node = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_temp = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入蔬菜所属分类编码：");
    scanf("%[^\n]", pvege_node -> species_id);
    getchar();
    printf("\n  请输入蔬菜名称：");
    scanf("%[^\n]", pvege_node -> vege_name);
    getchar();
    printf("\n  请输入蔬菜所含营养成分：");
    scanf("%[^\n]", pvege_node -> nutrition);
    getchar();

    hidecursor();/*隐藏光标*/

    for (pspecies_node = hd; pspecies_node != NULL ; pspecies_node = pspecies_node -> next){/*检验重复结点*/
        pvege_temp = pspecies_node -> vnext;
        while (pvege_temp != NULL){
            if (strcmp(pvege_temp -> vege_name, pvege_node -> vege_name ) == 0){
                printf("\n  该蔬菜基本信息已经存在！");
                return FALSE;
            }
            pvege_temp = pvege_temp -> next;
        }
    }

    pspecies_node = SeekSpeciesNode(hd, pvege_node -> species_id);/*查找主链上对应种类结点*/
    if (pspecies_node == NULL){
        printf("\n  找不到对应蔬菜分类！");
        return FALSE;
    }

    if (pspecies_node -> vnext == NULL){/*如果支链没有结点*/
        pvege_node -> next = NULL;
        pvege_node -> pnext = NULL;
        pvege_node -> vege_id = ++VegeCount;
        pspecies_node -> vnext = pvege_node;
    }
    else{/*支链已有结点*/
        pvege_node -> next = pspecies_node -> vnext;
        pspecies_node -> vnext = pvege_node;
        pvege_node -> pnext = NULL;
        pvege_node -> vege_id = ++VegeCount;
    }

    return TRUE;
}

/**
 * 函数名称: ModifVegeNode
 * 函数功能: 对指定的蔬菜基本信息结点内容进行修改.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 2表示取消修改
 *
 * 调用说明:
 */
int ModifVegeNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    VEGE_NODE *pvege_node;

    showcursor();/*显示光标*/
    printf("\n  请输入蔬菜名称以进行修改：");
    scanf("%[^\n]", vege_name);
    getchar();
    hidecursor();/*隐藏光标*/

    pvege_node = SeekVegeNode(hd, vege_name);   /*查找指定蔬菜信息结点*/
    if (pvege_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    蔬菜名称：%s\n", pvege_node -> vege_name);
        printf("    营养成分：%s\n", pvege_node -> nutrition);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }

        showcursor();/*显示光标*/

        printf("\n  请输入修改后的营养成分：");
        scanf("%[^\n]", pvege_node -> nutrition);
        getchar();

        hidecursor();/*隐藏光标*/
        return 1;
    }
    else{
        return 0;
    }
    return FALSE;
}

/**
 * 函数名称: DelVegeNode
 * 函数功能: 从十字链表中删除指定的蔬菜基本信息结点.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除
 *
 * 调用说明:
 */
int DelVegeNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node_prior,
              *pvege_node_current;
    pvege_node_current = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的蔬菜名称：");
    scanf("%[^\n]", vege_name);
    getchar();

    hidecursor();/*隐藏光标*/

    pvege_node_current = SeekVegeNode(hd, vege_name);

    if (pvege_node_current != NULL){/*如果找到*/
        pspecies_node = SeekSpeciesNode(hd, pvege_node_current -> species_id);/*在十字链中查找该蔬菜所属分类结点*/
        pvege_node_prior = NULL;
        pvege_node_current = pspecies_node -> vnext;
        while (pvege_node_current != NULL
               && strcmp(pvege_node_current -> vege_name, vege_name) != 0){/*支链上查找该蔬菜结点*/
            pvege_node_prior = pvege_node_current;
            pvege_node_current = pvege_node_current -> next;
        }

        printf("\n  将要删除的信息：\n");
        printf("    分类编号：%s\n", pvege_node_current -> species_id);
        printf("    蔬菜名称：%s\n", pvege_node_current -> vege_name);
        printf("    营养成分：%s\n", pvege_node_current -> nutrition);

        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*删除信息*/
        if (pvege_node_prior == NULL){   /*如果位于蔬菜基本信息支链上第一个位置*/
            pspecies_node -> vnext = pvege_node_current -> next;
        }
        else{
            pvege_node_prior -> next = pvege_node_current -> next;
        }
        free(pvege_node_current);
        }
        return 1;
    }

    return 0;
}

/**
 * 函数名称: InsertPlantNode
 * 函数功能: 在十字链表中插入一个种植信息结点.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE表示插入成功, FALSE表示插入失败
 *
 * 调用说明:
 */
BOOL InsertPlantNode(SPECIES_NODE *hd)
{
    VEGE_NODE *pvege_node;
    pvege_node = NULL;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_temp;
    pplant_node = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
    pplant_temp = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入蔬菜名称：");
    scanf("%[^\n]", pplant_node -> vege_name);
    getchar();
    printf("\n  请输入菜农姓名：");
    scanf("%[^\n]", pplant_node -> plant_name);
    getchar();
    printf("\n  请输入种植年份：");
    scanf("%[^\n]", pplant_node -> year);
    getchar();
    printf("\n  请输入种植面积：");
    scanf("%d", &pplant_node -> area);
    fflush(stdin);
    printf("\n  请输入收获总量：");
    scanf("%f", &pplant_node -> harvest);
    getchar();

    hidecursor();/*隐藏光标*/

    pvege_node = SeekVegeNode(hd, pplant_node -> vege_name);/*查找对应蔬菜信息结点*/
    if (pvege_node == NULL){
        printf("\n  找不到相应蔬菜信息！");
        return FALSE;
    }

    pplant_temp = pvege_node -> pnext;
    while (pplant_temp != NULL){/*查找重复结点*/
        if (strcmp(pplant_temp -> plant_name, pplant_node -> plant_name) == 0
            && strcmp(pplant_temp -> year, pplant_node -> year) == 0){
            printf("\n  该种植信息已经存在！");
            return FALSE;
        }
        pplant_temp = pplant_temp -> next;
    }

    if (pvege_node -> pnext == NULL){/*如果支链没有结点*/
        pplant_node -> next = NULL;
        pplant_node -> plant_id = ++PlantCount;
        pvege_node -> pnext = pplant_node;
    }
    else{/*支链已有结点*/
        pplant_node -> next = pvege_node -> pnext;
        pvege_node -> pnext = pplant_node;
        pplant_node -> plant_id = ++PlantCount;
    }

    return TRUE;
}

/**
 * 函数名称: ModifPlantNode
 * 函数功能: 对指定的种植信息结点内容进行修改.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示修改失败, 1表示修改成功, 2表示取消修改
 *
 * 调用说明:
 */
int ModifPlantNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char plant_name[20];
    char year[5];
    char *plabel_choose[] = {"确认修改信息吗？",
                             "确认    取消"
                            };
    PLANT_NODE *pplant_node;

    showcursor();/*显示光标*/

    printf("\n  请输入蔬菜名称以进行修改：");
    scanf("%[^\n]", vege_name);
    getchar();
    printf("\n  请输入菜农姓名以进行修改：");
    scanf("%[^\n]", plant_name);
    getchar();
    printf("\n  请输入种植年份以进行修改：");
    scanf("%[^\n]", year);
    getchar();

    hidecursor();/*隐藏光标*/

    pplant_node = SeekPlantNode(hd, vege_name, plant_name, year);   /*查找指定种植信息结点*/
    if (pplant_node != NULL){    /*如果找到*/
        printf("\n  将要修改的信息：\n");
        printf("    蔬菜名称：%s\n", pplant_node -> vege_name);
        printf("    菜农姓名：%s\n", pplant_node -> plant_name);
        printf("    种植年份：%s\n", pplant_node -> year);
        printf("    种植面积：%d\n", pplant_node -> area);
        printf("    收获总量：%f\n", pplant_node -> harvest);
        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否修改*/
            return 2;  /*取消修改*/
        }
        showcursor();/*显示光标*/
        printf("\n  请输入修改后的种植面积：");
        scanf("%d", &pplant_node -> area);
        fflush(stdin);
        printf("\n  请输入修改后的收获总量：");
        scanf("%f", &pplant_node -> harvest);
        getchar();
        hidecursor();/*隐藏光标*/
        return 1;
    }
    else{
        return 0;
    }
    return FALSE;
}

/**
 * 函数名称: DelPlantNode
 * 函数功能: 从十字链表中删除指定的菜农种植信息结点.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: int类型, 0表示删除失败, 1表示删除成功, 2表示取消删除
 *
 * 调用说明: 根据蔬菜名称、菜农姓名和种植年份可以确定唯一的菜农种植信息
 */
int DelPlantNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char plant_name[20];
    char year[5];
    char *plabel_choose[] = {"确认删除信息吗？",
                             "确认    取消"
                            };
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node_prior,
               *pplant_node_current;
    pplant_node_current = NULL;

    showcursor();/*显示光标*/

    printf("\n  请输入要删除的蔬菜名称：");
    scanf("%[^\n]", vege_name);
    getchar();
    printf("\n  请输入菜农的姓名以确认种植信息：");
    scanf("%[^\n]", plant_name);
    getchar();
    printf("\n  请输入种植年份以确认种植信息：");
    scanf("%[^\n]", year);
    getchar();

    hidecursor();/*隐藏光标*/

    pplant_node_current = SeekPlantNode(hd, vege_name, plant_name, year);

    if (pplant_node_current != NULL){/*如果找到*/
        pvege_node = SeekVegeNode(hd, pplant_node_current -> vege_name);/*在十字链中查找该种植信息所属蔬菜结点*/
        pplant_node_prior = NULL;
        pplant_node_current = pvege_node -> pnext;
        while (pplant_node_current != NULL
               && strcmp(pplant_node_current -> plant_name, plant_name) != 0){/*支链上查找该种植结点*/
            pplant_node_prior = pplant_node_current;
            pplant_node_current = pplant_node_current -> next;
        }

        printf("\n  将要删除的信息：\n");
        printf("    蔬菜名称：%s\n", pplant_node_current -> vege_name);
        printf("    菜农姓名：%s\n", pplant_node_current -> plant_name);
        printf("    种植年份：%s\n", pplant_node_current -> year);
        printf("    种植面积：%d\n", pplant_node_current -> area);
        printf("    收获重量：%f\n", pplant_node_current -> harvest);

        if(!ChooseModule(plabel_choose)){   /*确认信息并决定是否删除*/
            return 2;  /*取消删除*/
        }
        else{   /*删除信息*/
        if (pplant_node_prior == NULL){   /*如果位于种植信息支链上第一个位置*/
            pvege_node -> pnext = pplant_node_current -> next;
        }
        else{
            pplant_node_prior -> next = pplant_node_current -> next;
        }
        free(pplant_node_current);
        }
        return 1;
    }

    return 0;
}

//数据查询
/**
 * 函数名称: SeekSpeciesNode
 * 函数功能: 按分类编码查找蔬菜种类信息结点.
 * 输入参数: hd 主链头指针
 *           species_id 分类编码
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明:
 */
SPECIES_NODE *SeekSpeciesNode(SPECIES_NODE *hd, char *species_id)
{
    SPECIES_NODE *pspecies_node = hd;
    int find = 0;

    while (pspecies_node != NULL){
        if(strcmp(pspecies_node -> species_id, species_id) == 0){
            find = 1;
            break;
        }
        pspecies_node = pspecies_node -> next;
    }

    if (find){  /*如果找到*/
        return pspecies_node;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekVegeNode
 * 函数功能: 按蔬菜名称查找蔬菜基本信息结点.
 * 输入参数: hd 主链头指针
 *           vege_name 蔬菜名称
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址，否则返回NULL
 *
 * 调用说明:
 */
VEGE_NODE *SeekVegeNode (SPECIES_NODE *hd, char *vege_name)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    int find = 0;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*二重循环依次搜索主链每个结点的蔬菜基本信息支链*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            if (strcmp(pvege_node -> vege_name, vege_name) == 0){
                find = 1;
                break;
            }
            pvege_node = pvege_node -> next;
        }
        if (find){
            break;
        }
    }

    if(find){
        return pvege_node;
    }
    return NULL;
}

/**
 * 函数名称: SeekVegeNodeM1
 * 函数功能: 按蔬菜名称中文子串查询满足条件的所有蔬菜基本信息结点.
 * 输入参数: hd 主链头指针
 *           vege_namem 蔬菜名中文字串
 * 输出参数: 无
 * 返 回 值: 将所有满足条件的结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明:
 */
VEGE_NODE *SeekVegeNodeM1 (SPECIES_NODE *hd, char *vege_namem)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node_head;/*结果链表头指针*/
    VEGE_NODE *pvege_node_temp;
    VEGE_NODE *pvege_node;

    pvege_node_head = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_node_head = NULL;
    pvege_node_temp = NULL;
    pvege_node = NULL;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*二重循环遍历蔬菜结点*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            if ( (strstr (pvege_node -> vege_name, vege_namem) ) != NULL){/*建立结果链表*/
                pvege_node_temp = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
                *pvege_node_temp = *pvege_node;
                pvege_node_temp -> next = pvege_node_head;
                pvege_node_head = pvege_node_temp;

            }
            pvege_node = pvege_node -> next;
        }
    }

    return pvege_node_head;
}

/**
 * 函数名称: SeekVegeNodeM2
 * 函数功能: 按分类码和营养成分组合查询满足条件的所有蔬菜基本信息结点.
 * 输入参数: hd 主链头指针
 *           species_id 蔬菜分类编号
 *           vege_nutrim 蔬菜营养成分子串
 * 输出参数: 无
 * 返 回 值: 将所有满足条件的结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明:
 */
VEGE_NODE *SeekVegeNodeM2 (SPECIES_NODE *hd, char *species_id, char *vege_nutrim)
{
    SPECIES_NODE *pspecies_node = hd;
    VEGE_NODE *pvege_node_head;/*结果链表头指针*/
    VEGE_NODE *pvege_node_temp;
    VEGE_NODE *pvege_node;
    pvege_node_head = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_node_head = NULL;
    pvege_node_temp = NULL;
    pvege_node = NULL;
    int find = 0;

    while (pspecies_node != NULL){
        if(strcmp(pspecies_node -> species_id, species_id) == 0){
            find = 1;
            break;
        }
        pspecies_node = pspecies_node -> next;
    }

    if (find){  /*如果找到蔬菜种类*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){/*遍历蔬菜结点*/
            if ( (strstr (pvege_node -> nutrition , vege_nutrim) ) != NULL){/*建立结果链表*/
                pvege_node_temp = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
                *pvege_node_temp = *pvege_node;
                pvege_node_temp -> next = pvege_node_head;
                pvege_node_head = pvege_node_temp;
            }
            pvege_node = pvege_node -> next;
        }
        return pvege_node_head;
    }
    else{   /*如果未找到*/
        return NULL;
    }
}

/**
 * 函数名称: SeekVegeNodeM3
 * 函数功能: 按蔬菜所含部分营养成分查询满足条件的所有蔬菜基本信息结点.
 * 输入参数: hd 主链头指针
 *           nutrim 蔬菜部分营养成分
 * 输出参数: 无
 * 返 回 值: 将所有满足条件的结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明:
 */
VEGE_NODE *SeekVegeNodeM3 (SPECIES_NODE *hd, char *nutrim)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node_head;/*结果链表头指针*/
    VEGE_NODE *pvege_node_temp;
    VEGE_NODE *pvege_node;

    pvege_node_head = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_node_head = NULL;
    pvege_node_temp = NULL;
    pvege_node = NULL;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*二重循环遍历蔬菜结点*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            if ( (strstr (pvege_node -> nutrition, nutrim) ) != NULL){/*建立结果链表*/
                pvege_node_temp = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
                *pvege_node_temp = *pvege_node;
                pvege_node_temp -> next = pvege_node_head;
                pvege_node_head = pvege_node_temp;
            }
            pvege_node = pvege_node -> next;
        }
    }

    return pvege_node_head;
}

/**
 * 函数名称: SeekPlantNode
 * 函数功能: 按蔬菜名称、菜农姓名和种植年份查找种植信息结点.
 * 输入参数: hd 主链头指针
 *           vege_name 蔬菜名称
 *           plant_name 菜农姓名
 *           year 种植年份
 * 输出参数: 无
 * 返 回 值: 查中时返回结点的地址, 否则返回NULL
 *
 * 调用说明: 根据蔬菜名称、菜农姓名和种植年份可以确定唯一种植信息
 */
PLANT_NODE *SeekPlantNode(SPECIES_NODE *hd, char *vege_name, char *plant_name, char *year)
{
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_node_head;
    PLANT_NODE *pplant_node_temp;
    pvege_node = NULL;
    pplant_node = NULL;
    pplant_node_head = NULL;
    pplant_node_temp = NULL;

    pvege_node = SeekVegeNode(hd, vege_name);/*查找对应蔬菜基本信息结点*/

    /*如果找到，则在种植信息支链上继续查找指定种植信息结点*/
    if (pvege_node != NULL){
        pplant_node = pvege_node -> pnext;
        while(pplant_node != NULL){
            if(strcmp(pplant_node -> plant_name, plant_name) == 0
               && strcmp(pplant_node -> year, year) == 0){
                pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
                *pplant_node_temp = *pplant_node;
                pplant_node_temp -> next = pplant_node_head;
                pplant_node_head = pplant_node_temp;
            }
            pplant_node = pplant_node -> next;
        }
    }

    return pplant_node_head;
}

/**
 * 函数名称: SeekPlantNodeM1
 * 函数功能: 按蔬菜部分名称和种植年份查找所有种植信息结点.
 * 输入参数: hd 主链头指针
 *           vege_namem 蔬菜部分名称
 *           year 种植年份
 * 输出参数: 无
 * 返 回 值: 将所有满足条件的结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明:
 */
PLANT_NODE *SeekPlantNodeM1(SPECIES_NODE *hd, char *vege_namem, char *year)
{
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_node_head;    /*结果链首结点*/
    PLANT_NODE *pplant_node_temp;
    pvege_node = NULL;
    pplant_node = NULL;
    pplant_node_temp = NULL;
    int find = 0;

    pvege_node = SeekVegeNodeM1(hd, vege_namem);/*查找对应蔬菜基本信息结点*/

    /*如果找到，则在蔬菜名称结果链表上继续查找指定种植信息结点*/
    if (pvege_node != NULL){
        pplant_node_head = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        pplant_node_head = NULL;
        for (;pvege_node != NULL; pvege_node = pvege_node -> next){
            pplant_node = pvege_node -> pnext;
            while(pplant_node != NULL){
                if(strcmp(pplant_node -> year, year) == 0){
                    find = 1;
                    pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
                    *pplant_node_temp = *pplant_node;
                    pplant_node_temp -> next = pplant_node_head;
                    pplant_node_head = pplant_node_temp;
                }
                pplant_node = pplant_node -> next;
            }
        }
    }

    if(find){
        return pplant_node_head;
    }
    else{
        return NULL;
    }
}

/**
 * 函数名称: SeekPlantNodeM2
 * 函数功能: 按蔬菜名称查找种植信息结点, 并对种植信息结点按种植年份排序.
 * 输入参数: hd 主链头指针
 *           vege_name 蔬菜名称
 * 输出参数: 无
 * 返 回 值: 将所有满足条件的结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明:
 */
PLANT_NODE *SeekPlantNodeM2(SPECIES_NODE *hd, char *vege_name)
{
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_node_prior;
    PLANT_NODE *pplant_node_after;
    PLANT_NODE *pplant_node_cur;
    PLANT_NODE *pplant_node_temp;
    pvege_node = NULL;
    pplant_node = NULL;
    pplant_node_prior = NULL;
    pplant_node_after = NULL;
    pplant_node_cur = NULL;
    pplant_node_temp = NULL;

    pvege_node = SeekVegeNode(hd, vege_name);
    if (pvege_node == NULL || pvege_node -> pnext == NULL){/*如果未找到*/
        return NULL;
    }

    pplant_node = pvege_node -> pnext;/*种植信息链头指针*/
    pplant_node_prior = pplant_node;
    pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));/*用于交换结点的临时结点*/

    while (pplant_node_prior -> next != NULL){/*选择排序*/
        pplant_node_cur = pplant_node_prior;
        pplant_node_after = pplant_node_prior -> next;
        while (pplant_node_after != NULL){/*cur是最大年份地址*/
            if (strcmp (pplant_node_cur -> year, pplant_node_after -> year) < 0){
                pplant_node_cur = pplant_node_after;
            }
            pplant_node_after = pplant_node_after -> next;
        }

        if (pplant_node_cur != pplant_node_prior){/*交换两个结点中的信息，指针域不交换*/
            *pplant_node_temp = *pplant_node_prior;
            *pplant_node_prior = *pplant_node_cur;
            pplant_node_prior -> next = pplant_node_temp -> next;/*恢复prior->next指向的结点*/
            pplant_node_temp -> next = pplant_node_cur -> next;
            *pplant_node_cur = *pplant_node_temp;/*cur数据交换，->next指向不变*/
        }
        pplant_node_prior = pplant_node_prior -> next;
    }
    free(pplant_node_temp);
    return pplant_node;
}

/**
 * 函数名称: SeekPlantNodeM3
 * 函数功能: 按菜农姓名查找种植信息结点，并按种植年份排序.
 * 输入参数: hd 主链头指针
 *           plant_name 菜农姓名
 * 输出参数: 无
 * 返 回 值: 将所有满足条件的结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明: 根据菜农姓名可以确定种植信息
 */
PLANT_NODE *SeekPlantNodeM3(SPECIES_NODE *hd, char *plant_name)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_node_head;
    PLANT_NODE *pplant_node_prior;
    PLANT_NODE *pplant_node_after;
    PLANT_NODE *pplant_node_cur;
    PLANT_NODE *pplant_node_temp;
    pspecies_node = NULL;
    pvege_node = NULL;
    pplant_node = NULL;
    pplant_node_head = NULL;
    pplant_node_prior = NULL;
    pplant_node_after = NULL;
    pplant_node_cur = NULL;
    pplant_node_temp = NULL;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*三重循环遍历种植结点*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            pplant_node = pvege_node -> pnext;
            while(pplant_node != NULL){
                if ( (strcmp (pplant_node -> plant_name, plant_name) ) == 0){
                    pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
                    *pplant_node_temp = *pplant_node;
                    pplant_node_temp -> next = pplant_node_head;
                    pplant_node_head = pplant_node_temp;
                }
                pplant_node = pplant_node -> next;
            }
            pvege_node = pvege_node -> next;
        }
    }

    if (pplant_node_head!=NULL){
        pplant_node_prior = pplant_node_head;/*种植信息链头指针*/
        pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));/*用于交换结点的临时结点*/

        while (pplant_node_prior -> next != NULL){/*选择排序*/
            pplant_node_cur = pplant_node_prior;
            pplant_node_after = pplant_node_prior -> next;
            while (pplant_node_after != NULL){/*cur是最大年份地址*/
                if (strcmp (pplant_node_cur -> year, pplant_node_after -> year) < 0){
                    pplant_node_cur = pplant_node_after;
                }
                pplant_node_after = pplant_node_after -> next;
            }

            if (pplant_node_cur != pplant_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *pplant_node_temp = *pplant_node_prior;
                *pplant_node_prior = *pplant_node_cur;
                pplant_node_prior -> next = pplant_node_temp -> next;/*恢复prior->next指向的结点*/
                pplant_node_temp -> next = pplant_node_cur -> next;
                *pplant_node_cur = *pplant_node_temp;/*cur数据交换，->next指向不变*/
            }
            pplant_node_prior = pplant_node_prior -> next;
        }
        free(pplant_node_temp);
    }
    return pplant_node_head;
}

//数据统计
/**
 * 函数名称: Stat1
 * 函数功能: 按年份统计各种蔬菜分类的总种植面积与总产量.
 * 输入参数: hd 主链头指针
 *           year 种植年份
 * 输出参数: 无
 * 返 回 值: 将统计结点复制到结果链表, 返回结果链表的头结点地址
 *
 * 调用说明: 根据种植年份可以确定种植信息
 */
TOTAL_NODE *Stat1(SPECIES_NODE *hd, char *year)
{
    int total_area;
    int find;
    float total_harvest;

    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    TOTAL_NODE *ptotal_node_head;/*结果链表头指针*/
    TOTAL_NODE *ptotal_node_temp;
    TOTAL_NODE *ptotal_node_prior;
    TOTAL_NODE *ptotal_node_after;
    TOTAL_NODE *ptotal_node_cur;

    pspecies_node = NULL;
    pvege_node = NULL;
    pplant_node = NULL;
    ptotal_node_head = (TOTAL_NODE *)malloc(sizeof(TOTAL_NODE));
    ptotal_node_head = NULL;
    ptotal_node_temp = NULL;
    ptotal_node_prior = NULL;
    ptotal_node_after = NULL;
    ptotal_node_cur = NULL;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*三重循环遍历种植结点*/
        pvege_node = pspecies_node -> vnext;
        find = 0;
        total_area = 0;
        total_harvest = 0;
        while (pvege_node != NULL){
            pplant_node = pvege_node -> pnext;
            while(pplant_node != NULL){
                if ( (strcmp (pplant_node -> year, year) ) == 0){/*计算结点数据*/
                    find = 1;
                    total_area += pplant_node -> area;
                    total_harvest += pplant_node -> harvest;
                }
                pplant_node = pplant_node -> next;
            }
            pvege_node = pvege_node -> next;
        }
        if (find != 0){/*如果找到，建立结果链表*/
            ptotal_node_temp = (TOTAL_NODE *)malloc(sizeof(TOTAL_NODE));
            strcpy (ptotal_node_temp -> species_name, pspecies_node -> species_name);/*赋数据域*/
            ptotal_node_temp -> total_area = total_area;
            ptotal_node_temp -> total_harvest = total_harvest;
            ptotal_node_temp -> next = ptotal_node_head;/*后进先出*/
            ptotal_node_head = ptotal_node_temp;
        }
    }

    if (ptotal_node_head != NULL){/*排序*/
        ptotal_node_temp = NULL;
        ptotal_node_prior = ptotal_node_head;
        ptotal_node_temp = (TOTAL_NODE *)malloc(sizeof(TOTAL_NODE));/*用于交换结点的临时结点*/

        while (ptotal_node_prior -> next != NULL){/*选择排序*/
            ptotal_node_cur = ptotal_node_prior;
            ptotal_node_after = ptotal_node_prior -> next;
            while (ptotal_node_after != NULL){/*cur是最大重量地址*/
                if (ptotal_node_cur -> total_harvest < ptotal_node_after -> total_harvest){
                    ptotal_node_cur = ptotal_node_after;
                }
                ptotal_node_after = ptotal_node_after -> next;
            }

            if (ptotal_node_cur != ptotal_node_prior){/*交换两个结点中的信息，指针域不交换*/
                *ptotal_node_temp = *ptotal_node_prior;
                *ptotal_node_prior = *ptotal_node_cur;
                ptotal_node_prior -> next = ptotal_node_temp -> next;/*恢复prior->next指向的结点*/
                ptotal_node_temp -> next = ptotal_node_cur -> next;
                *ptotal_node_cur = *ptotal_node_temp;/*cur数据交换，->next指向不变*/
            }
            ptotal_node_prior = ptotal_node_prior -> next;
        }
        free(ptotal_node_temp);
    }

    return ptotal_node_head;
}

/**
 * 函数名称: Stat2
 * 函数功能: 按蔬菜名称统计蔬菜在年份区间内的种植面积、总产量.
 * 输入参数: hd 主链头指针
 *           vege_name 蔬菜名称
 *           year_head 起始年份
 *           year_tail 终止年份
 * 输出参数: 无
 * 返 回 值: 将统计结点复制到结果链表，返回结果链表的头结点地址
 *
 * 调用说明: 根据菜农姓名可以确定种植信息
 */
TOTAL_NODE *Stat2(SPECIES_NODE *hd, char *vege_name, char *year_head, char *year_tail)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    TOTAL_NODE *ptotal_node;

    pspecies_node = NULL;
    pvege_node = NULL;
    pplant_node = NULL;
    ptotal_node = (TOTAL_NODE *)malloc(sizeof(TOTAL_NODE));
    ptotal_node -> total_area = 0;
    ptotal_node -> total_harvest = 0;
    ptotal_node -> next = NULL;
    strcpy (ptotal_node -> vege_name, vege_name);

    pvege_node = SeekVegeNode(hd, vege_name);/*查找蔬菜结点*/

    if (pvege_node != NULL){/*如果找到*/
        pspecies_node = SeekSpeciesNode(hd, pvege_node -> species_id);/*查找种类名称*/
        strcpy (ptotal_node -> species_name, pspecies_node -> species_name);
        pplant_node = pvege_node -> pnext;

        while (pplant_node != NULL){/*统计结点数据*/
            if (JudgeYear(year_head, pplant_node -> year, year_tail)){/*如果年份信息符合条件*/
                ptotal_node -> total_area += pplant_node -> area;
                ptotal_node -> total_harvest += pplant_node -> harvest;
            }
            pplant_node = pplant_node -> next;
        }
        return ptotal_node;
    }
    return NULL;
}

/**
 * 函数名称: JudgeYearR
 * 函数功能: 判断年份字符串格式是否正确.
 * 输入参数: year 年份
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL JudgeYearR(char *year)
{
    int Len = strlen(year);
    BOOL find = TRUE;
    int i;

    for(i = 0; i < Len; i++){
        if(year[i] < '0' || year[i] > '9'){
            find = FALSE;
        }
    }

    return find;
}

/**
 * 函数名称: JudgeYearR
 * 函数功能: 判断年份字符串是否在年份区间内.
 * 输入参数: year_temp 待判定年份
 *           year_head 年份区间首
 *           year_tail 年份区间尾
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明:
 */
BOOL JudgeYear(char *year_head, char *year_temp, char* year_tail)
{
    int LenH = strlen(year_head);
    int LenP = strlen(year_temp);
    int LenT = strlen(year_tail);

    if(LenH == LenP && LenP == LenT){/*年份位数相同*/
        if(strcmp(year_head, year_temp) <= 0
           &&strcmp(year_temp, year_tail) <= 0){
            return TRUE;
           }
    }
    else if(LenH == LenP && LenP < LenT){/*前两个年份位数相同*/
        if(strcmp(year_head, year_temp) <= 0){
            return TRUE;
        }
    }
    else if(LenH < LenP && LenP == LenT){/*后两个年份位数相同*/
        if(strcmp(year_temp, year_tail) <= 0){
            return TRUE;
        }
    }

    return FALSE;
}
