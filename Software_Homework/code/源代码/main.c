#include "class.h"

unsigned long ul;
int VegeCount;
int PlantCount;

int main()
{
    COORD size = {SCR_COL, SCR_ROW};              /*���ڻ�������С*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* ��ȡ��׼����豸���*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* ��ȡ��׼�����豸���*/

    SetConsoleTitle(gp_sys_name);                 /*���ô��ڱ���*/
    SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С80*25*/

    LoadData();                   /*���ݼ���*/
    InitInterface();              /*�����ʼ��*/
    RunSys();             /*ϵͳ����ģ���ѡ������*/
    CloseSys();            /*�˳�ϵͳ*/

    return 0;
}

/**
 * ��������: LoadData
 * ��������: ������������ݺͿ������ݴ������ļ����뵽�ڴ滺������ʮ��������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, ���ܺ����г��˺���ExitSys�ķ���ֵ����ΪFALSE��,
 *           ���������ķ���ֵ����ΪTRUE.
 *
 * ����˵��: Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���, ����Щ���ܺ�����ԭ����Ϊ
 *           һ��, ���޲����ҷ���ֵΪBOOL. ����ֵΪFALSEʱ, ������������.
 */
BOOL LoadData()
{
    int Re = 0;
    Re = CreatList();
    gc_sys_state |= Re;
    gc_sys_state &= ~(1 + 2 + 4 + 8 + 16 - Re);
    if (gc_sys_state < (1 | 2 | 4 | 8 | 16))
    {  /*���ݼ�����ʾ��Ϣ*/
        printf("\nϵͳ�������ݲ�����!\n");
        printf("\n�����������...\n");
    }
    printf("\n�����������������...\n");
    getch();

    return TRUE;
}

/**
 * ��������: CreatList
 * ��������: �������ļ���ȡ��������, ����ŵ���������ʮ��������.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ, ����������������ʮ����.
 * �� �� ֵ: int����ֵ, ��ʾ�����������.
 *           0  ������������
 *           1  �Ѽ��ؿγ���Ϣ���ݣ���������Ϣ����
 *           2  �Ѽ��ؿγ���Ϣ�ͽ�����Ϣ���ݣ���������Ϣ����
 *           4  �Ѽ��ؿγ���Ϣ��������Ϣ�ͽ�ʦ��Ϣ���ݣ���������Ϣ����
 *           8  �Ѽ��ؿγ���Ϣ��������Ϣ����ʦ��Ϣ�Ͱ༶���ݣ��޿�����Ϣ����
 *           16 �Ѽ���ȫ������
 *
 * ����˵��:
 */
int CreatList()
{
    int i=0;//������
    int count=0;//������
    float credits;//ѧ��
    int hours;//ѧʱ
    int weekday;//�ܼ�
    int class_num;//�༶����
    char subject_name[40],building[20],room_name[20],
         teacher_name[20],position[20],class_name[40];
         //�γ��� ��ѧ¥ ������
         //��ʦ�� ְλ �༶��
    char lesson[100];//����
    char week[100];//����

    TEACHER_NODE *teacher_temp = teacher_head, *pTeacherNode,*pteacher_node;
    SUBJECT_NODE *subject_temp = subject_head, *pSubjectNode,*psubject_node;
    CLASS_NODE *class_temp = class_head, *pClassNode,*pclass_node;
    ROOM_NODE *room_temp = room_head, *pRoomNode,*proom_node;
    COURSE_NODE *course_temp = course_head, *pCourseNode;

    FILE *pFile;
    int find;
    int re = 0;

    //��ȡ�γ���Ϣ
    if ((pFile = fopen(gp_subject_info_filename, "rb")) == NULL)
    {
        printf("�γ���Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�γ���Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж��γ���Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ŀγ���Ϣ����*/
    while (fscanf(pFile,"%s %f %d",subject_name,&credits,&hours)!=EOF)
    {
        //�½ڵ㸳ֵ
        pSubjectNode = (SUBJECT_NODE *)malloc(sizeof(SUBJECT_NODE));
        strcpy(pSubjectNode->subject_name,subject_name);
        pSubjectNode->subject_credits=credits;
        pSubjectNode->subject_hours=hours;
        pSubjectNode->scnext=NULL;
        pSubjectNode->next=NULL;

        //����
        //����ͷ���
        if(subject_head==NULL){
            subject_head = pSubjectNode;
            subject_temp = subject_head;
            count++;
        }
        //����Ϊ�������
        else{
            subject_temp -> next = pSubjectNode;
            subject_temp = subject_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (subject_head == NULL)
    {
        printf("�γ���Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("�γ���Ϣ�����ļ����سɹ�!\n������%d���γ���Ϣ\n",count);
    count = 0;
    re += 1;


    //��ȡ������Ϣ
    if ((pFile = fopen(gp_room_info_filename, "rb")) == NULL)
    {
        printf("������Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("������Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж�������Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ľ�����Ϣ����*/
    while (fscanf(pFile,"%s %s",building,room_name)!=EOF)
    {
        //�½ڵ㸳ֵ
        pRoomNode = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
        strcpy(pRoomNode->building,building);
        strcpy(pRoomNode->room_name,room_name);
        pRoomNode->rcnext=NULL;
        pRoomNode->next=NULL;

        //����
        //����ͷ���
        if(room_head==NULL){
            room_head = pRoomNode;
            room_temp = room_head;
            count++;
        }
        //����Ϊ�������
        else{
            room_temp -> next = pRoomNode;
            room_temp = room_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (room_head == NULL)
    {
        printf("������Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("������Ϣ�����ļ����سɹ�!\n������%d��������Ϣ\n",count);
    count = 0;
    re += 2;


    //��ȡ��ʦ��Ϣ
    if ((pFile = fopen(gp_teacher_info_filename, "rb")) == NULL)
    {
        printf("��ʦ��Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("��ʦ��Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж���ʦ��Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ľ�ʦ��Ϣ����*/
    while (fscanf(pFile,"%s %s",teacher_name,position)!=EOF)
    {
        //�½ڵ㸳ֵ
        pTeacherNode = (TEACHER_NODE *)malloc(sizeof(TEACHER_NODE));
        strcpy(pTeacherNode -> teacher_name,teacher_name);
        strcpy(pTeacherNode ->position,position);
        pTeacherNode -> next = NULL;
        pTeacherNode ->tcnext=NULL;

        //����
        //����ͷ���
        if(teacher_head==NULL){
            teacher_head = pTeacherNode;
            teacher_temp = teacher_head;
            count++;
        }
        //����Ϊ�������
        else{
            teacher_temp -> next = pTeacherNode;
            teacher_temp = teacher_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (teacher_head == NULL)
    {
        printf("��ʦ��Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("��ʦ��Ϣ�����ļ����سɹ�!\n������%d����ʦ��Ϣ\n",count);
    count = 0;
    re += 4;



    //��ȡ�༶��Ϣ
    if ((pFile = fopen(gp_class_info_filename, "rb")) == NULL)
    {
        printf("�༶��Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�༶��Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж��༶��Ϣ���ݣ��������Ƚ��ȳ���ʽ�����İ༶��Ϣ����*/
    while (fscanf(pFile,"%s",class_name)!=EOF)
    {
        //�½ڵ㸳ֵ
        pClassNode = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
        strcpy(pClassNode->class_name,class_name);
        pClassNode->ccnext=NULL;
        pClassNode->next=NULL;

        //����
        //����ͷ���
        if(class_head==NULL){
            class_head = pClassNode;
            class_temp = class_head;
            count++;
        }
        //����Ϊ�������
        else{
            class_temp -> next = pClassNode;
            class_temp = class_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (class_head == NULL)
    {
        printf("�༶��Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("�༶��Ϣ�����ļ����سɹ�!\n������%d���༶��Ϣ\n",count);
    count = 0;
    re += 8;


    //��ȡ������Ϣ
    if ((pFile = fopen(gp_course_info_filename, "rb")) == NULL)
    {
        printf("������Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("������Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж�������Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ŀ�����Ϣ����*/
    while (fscanf(pFile,"%s %s %s %s %d %s %s %d",subject_name,building,
                  room_name,teacher_name,&weekday, lesson, week, &class_num)!=EOF)
    {
        //�½ڵ㸳ֵ
        pCourseNode = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        for(i=0;i<10;i++){//��ʼ��
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

        //������������
        //����ͷ���
        if(course_head==NULL){
            course_head = pCourseNode;
            course_temp = course_head;
            count++;
        }
        //����Ϊ�������
        else{
            course_temp -> next = pCourseNode;
            course_temp ->next->prior=course_temp;
            course_temp = course_temp -> next;
            count++;
        }

        //pcourse�����������Ϣ����
        //�γ�
        psubject_node = SeekSubjectNode(subject_head,pCourseNode->subject_name);
        pCourseNode->scnext = psubject_node->scnext;
        psubject_node->scnext = pCourseNode;
        //�༶
        for(i=0;i<class_num;i++){
            pclass_node = SeekClassNode(class_head,pCourseNode->class_name[i]);
            pCourseNode->ccnext[i]=pclass_node->ccnext;
            pclass_node->ccnext=pCourseNode;
        }
        //��ʦ
        pteacher_node = SeekTeacherNode(teacher_head,pCourseNode->teacher_name);
        pCourseNode->tcnext=pteacher_node->tcnext;
        pteacher_node->tcnext=pCourseNode;
        //����
        proom_node = SeekRoomNode(room_head,pCourseNode->room_name,pCourseNode->building);
        pCourseNode->rcnext=proom_node->rcnext;
        proom_node->rcnext=pCourseNode;
    }
    fclose(pFile);
    if (course_head == NULL)
    {
        printf("������Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("������Ϣ�����ļ����سɹ�!\n������%d��������Ϣ\n",count);
    count = 0;
    re += 16;

    return re;
}

/**
 * ��������: InitInterface
 * ��������: ��ʼ������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void InitInterface()
{

    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*��ɫǰ������ɫ����*/

    SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

    system("color F0\n");/*�׵׺���*/
    ClearScreen();  /* ����*/

    /*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*��Ļ�ַ�����*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;      /*�������ڵĲ��Ϊ0*/
    gp_top_layer->rcArea.Left = 0;  /*�������ڵ�����Ϊ������Ļ����*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();     /*��ʾ�˵���*/
    ShowState();    /*��ʾ״̬��*/

    return;
}

/**
 * ��������: ClearScreen
 * ��������: �����Ļ��Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*ȡ��Ļ��������Ϣ*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*������Ļ�������ַ���Ԫ��*/

    /*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);

    return;
}

/**
 * ��������: ShowMenu
 * ��������: ����Ļ����ʾ���˵�, ����������, �����˵���һ������ѡ�б��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
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
    for (i=0; i < 5; i++) /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

    /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
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

    /*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*�����λ�������ڵ�2�е�1��*/

    /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*��λ��i+1�Ų˵������ֹλ��*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; /*���ò˵��������ַ���Ԫ������ֵ*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/

    return;
}

/**
 * ��������: ShowState
 * ��������: ��ʾ״̬��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ״̬���ַ�����Ϊ�׵׺���, ��ʼ״̬��״̬��Ϣ.
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
 * ��������: TagMainMenu
 * ��������: ��ָ�����˵�������ѡ�б�־.
 * �������: num ѡ�е����˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
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

    /*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
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

    /*��ѡ�в˵���������ǣ��ڵװ���*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
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

    /*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: CloseSys
 * ��������: �ر�ϵͳ.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CloseSys(void)
{
    SUBJECT_NODE *pSubjectNode1 = subject_head, *pSubjectNode2;
    ROOM_NODE *pRoomNode1 = room_head, *pRoomNode2;
    TEACHER_NODE *pTeacherNode1 = teacher_head, *pTeacherNode2;
    CLASS_NODE *pClassNode1 = class_head,*pClassNode2;
    COURSE_NODE *pCourseNode1 = course_head,*pCourseNode2;

    while (pSubjectNode1 != NULL) /*�ͷſγ�����Ķ�̬�洢��*/
    {
        pSubjectNode2 = pSubjectNode1->next;
        free(pSubjectNode1);  /*�ͷŶ�̬�洢��*/
        pSubjectNode1 = pSubjectNode2;
    }
    while (pRoomNode1 != NULL) /*�ͷŽ�������Ķ�̬�洢��*/
    {
        pRoomNode2 = pRoomNode1->next;
        free(pRoomNode1);  /*�ͷŶ�̬�洢��*/
        pRoomNode1 = pRoomNode2;
    }
    while (pTeacherNode1 != NULL) /*�ͷŽ�ʦ����Ķ�̬�洢��*/
    {
        pTeacherNode2 = pTeacherNode1->next;
        free(pTeacherNode1);  /*�ͷŶ�̬�洢��*/
        pTeacherNode1 = pTeacherNode2;
    }
    while (pClassNode1 != NULL) /*�ͷŰ༶����Ķ�̬�洢��*/
    {
        pClassNode2 = pClassNode1->next;
        free(pClassNode1);  /*�ͷŶ�̬�洢��*/
        pClassNode1 = pClassNode2;
    }
    while (pCourseNode1 != NULL) /*�ͷſ�������Ķ�̬�洢��*/
    {
        pCourseNode2 = pCourseNode1->next;
        free(pCourseNode1);  /*�ͷŶ�̬�洢��*/
        pCourseNode1 = pCourseNode2;
    }

    ClearScreen();        /*����*/

    /*�ͷŴ�Ų˵�����״̬������Ϣ��̬�洢��*/
    free(gp_buff_menubar_info);
    free(gp_buff_stateBar_info);

    /*�رձ�׼���������豸���*/
    CloseHandle(gh_std_out);
    CloseHandle(gh_std_in);

    /*�����ڱ�������Ϊ���н���*/
    SetConsoleTitle("���н���");

    return;
}

/**
 * ��������: RunSys
 * ��������: ����ϵͳ, ��ϵͳ�������������û���ѡ��Ĺ���ģ��.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void RunSys()
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:�ַ���Ԫ���, cAtt:�ַ���Ԫ����*/
    char vkc, asc;      /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    while (bRet)
    {
        /*�ӿ���̨���뻺�����ж�һ����¼*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
            {
                /* cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
                 * cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
                 * gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    PopMenu(cAtt);       /*��������������˵����Ӧ���Ӳ˵�*/
                }
            }
            else if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                TagSubMenu(cAtt); /*�ڸ��Ӳ˵�������ѡ�б��*/
            }

            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*������������ߵ�һ��*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(���˵����ַ���Ԫ)*/
                    {
                        PopMenu(cAtt);   /*��������������˵����Ӧ���Ӳ˵�*/
                    }
                    /*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    }
                }
                else /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
                    {
                        PopOff(); /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/

                        /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*�����������Ҽ�*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*�����¼�ɰ�������*/
                 && inRec.Event.KeyEvent.bKeyDown) /*�Ҽ�������*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*��ȡ�������������*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*��ȡ������ASC��*/

            /*ϵͳ��ݼ��Ĵ���*/
            if (vkc == 112) /*�������F1��*/
            {
                if (gp_top_layer->LayerNo != 0) /*�����ǰ���Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
                bRet = ExeFunction(5, 1);  /*���а������⹦�ܺ���*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            { /*������������Alt��*/
                switch (vkc)  /*�ж���ϼ�Alt+��ĸ*/
                {
                    case 88:  /*Alt+X �˳�*/
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
            else if (asc == 0) /*�������Ƽ��Ĵ���*/
            {
                if (gp_top_layer->LayerNo == 0) /*���δ�����Ӳ˵�*/
                {
                    switch (vkc) /*�������(���ҡ���)������Ӧ�������Ƽ�*/
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
                else  /*�ѵ����Ӳ˵�ʱ*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                    switch (vkc) /*�����(���ҡ��ϡ���)�Ĵ���*/
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
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*������ͨ��*/
                if (gp_top_layer->LayerNo == 0)  /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)
                    {
                        case 70: /*f��F*/
                            PopMenu(1);
                            break;
                        case 77: /*m��M*/
                            PopMenu(2);
                            break;
                        case 81: /*q��Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s��S*/
                            PopMenu(4);
                            break;
                        case 72: /*h��H*/
                            PopMenu(5);
                            break;
                        case 13: /*�س�*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
                {
                    if (vkc == 27) /*�������ESC��*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*������»س���*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*������ͨ���Ĵ���*/
                    {
                        /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*���ƥ��ɹ�*/
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
 * ��������: PopMenu
 * ��������: ����ָ�����˵����Ӧ���Ӳ˵�.
 * �������: num ָ�������˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
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

    if (num != gi_sel_menu)       /*���ָ�����˵�������ѡ�в˵�*/
    {
        if (gp_top_layer->LayerNo != 0) /*�����ǰ�����Ӳ˵�����*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*���ѵ������Ӳ˵����򷵻�*/
    {
        return;
    }

    gi_sel_menu = num;    /*��ѡ�����˵�����Ϊָ�������˵���*/
    TagMainMenu(gi_sel_menu); /*��ѡ�е����˵����������*/
    LocSubMenu(gi_sel_menu, &rcPop); /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

    /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*�������Ӳ˵������������ǩ���ṹ����*/
    labels.ppLabel = ga_sub_menu + loc;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
	labels.num = ga_sub_menu_count[gi_sel_menu - 1]; /*��ǩ���б�ǩ�ַ����ĸ���*/
	COORD aLoc[labels.num];/*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
    for (i=0; i<labels.num; i++) /*ȷ����ǩ�ַ��������λ�ã����������������*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
    /*����������Ϣ*/
    areas.num = labels.num;       /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                      /*��������������������Ӧ���*/
    char aTag[areas.num];                         /*����������ÿ�������ı��*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*������λ*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;           /*������˳����*/
    }
    areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*���������ڻ��߿�*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    { /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0) /*����Ϊ0������Ϊ�մ�*/
        {   /*���Ȼ�����*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {   /*ȡ���������ַ���Ԫ����������*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*��λ��Ľ�������˵���λ*/
            }
        }

    }
    /*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;  /*�����մ�*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * ��������: PopUp
 * ��������: ��ָ�������������������Ϣ, ͬʱ��������, ����������λ����Ϣ��ջ.
 * �������: pRc ��������λ�����ݴ�ŵĵ�ַ
 *           att �������������ַ�����
 *           pLabel ���������б�ǩ����Ϣ��ŵĵ�ַ
             pHotArea ����������������Ϣ��ŵĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*������������λ���ַ���Ԫ��Ϣ��ջ*/
    size.X = pRc->Right - pRc->Left + 1;    /*�������ڵĿ��*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*�������ڵĸ߶�*/
    /*�����ŵ������������Ϣ�Ķ�̬�洢��*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*��ɵ������������Ϣ��ջ����*/
    /*���õ������������ַ���������*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*����ǩ���еı�ǩ�ַ������趨��λ�����*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*���õ������������ַ���Ԫ��������*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
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
 * ��������: PopOff
 * ��������: �رն��㵯������, �ָ���������ԭ��ۺ��ַ���Ԫԭ����.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*�ָ�������������ԭ���*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*�ָ��ַ���Ԫԭ����*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * ��������: DrawBox
 * ��������: ��ָ�����򻭱߿�.
 * �������: pRc �������λ����Ϣ�ĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*�����õ��ַ�*/
    COORD pos = {pRc->Left, pRc->Top};  /*��λ����������Ͻ�*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*��ѭ�����ϱ߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*��ѭ�����߿�����ߺ��ұ���*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*���±߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    return;
}

/**
 * ��������: TagSubMenu
 * ��������: ��ָ���Ӳ˵�������ѡ�б��.
 * �������: num ѡ�е��Ӳ˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*���ƶ��Ӳ˵�������ѡ�б��*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*�޸�ѡ���Ӳ˵����*/
    return;
}

/**
 * ��������: LocSubMenu
 * ��������: ���㵯���Ӳ˵��������ϽǺ����½ǵ�λ��.
 * �������: num ѡ�е����˵����
 * �������: rc �������λ����Ϣ�ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*����������ұ߽�*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*���������±ߵ��к�*/
    if (rc->Right >= SCR_COL)  /*�ұ߽�Խ��Ĵ���*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * ��������: DealInput
 * ��������: �ڵ�������������������, �ȴ�����Ӧ�û�����.
 * �������: pHotArea
 *           piHot ����������ŵĴ�ŵ�ַ, ��ָ�򽹵�������ŵ�ָ��
 * �������: piHot ����굥�������س���ո�ʱ���ص�ǰ�������
 * �� �� ֵ:
 *
 * ����˵��:
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*�س�����ո��ʾ���µ�ǰ��ť*/
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
    SetConsoleCursorInfo(gh_std_out, &lpCur);   /*���ֹ��*/
}

void hidecursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/
}

/**�����˵�*/
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

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
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
    BOOL bRet = FALSE; /*�����û���ѡ��TRUEΪȷ����FALSEΪȡ��*/
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6; /*�ճ�����������Ҽ��*/
    pos.Y = 7;  /*�����ߺ���������*/
    rcPop.Left = (SCR_COL - pos.X) / 2; /*ȷ�ϵ������λ��*/
    rcPop.Right = rcPop.Left + pos.X - 1;   /*-1����Ϊ��ʼ����Ϊ0*/
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = 2; /*��ǩ���б�ǩ�ַ����ĸ���*/
    labels.ppLabel = pCh;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};   /*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
    labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�Աplocָ�������������Ԫ��*/

    areas.num = 2;  /*��������*/
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};/*������λ*/
    char aSort[] = {0, 0};  /*��������*/
    char aTag[] = {1, 2};   /*�������*/
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);    /*�����߷ָ�*/

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

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    for (i=0; i<pHotArea->num; i++)
    {  /*����ť��������Ϊ�׵׺���*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*�����ǰ�ť��*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*�����������ǰ�ť��*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*�������������ı�����*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/**
 * ��������: ExeFunction
 * ��������: ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���.
 * �������: m ���˵����
 *           s �Ӳ˵����
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��: ����ִ�к���ExitSysʱ, �ſ��ܷ���FALSE, ������������Ƿ���TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
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

    for (i=1,loc=0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}

/*********************************************************************
**************************** �� �� ģ �� ****************************
*********************************************************************/

/**�ļ�ģ��*/

/**
 * ��������: Savedata
 * ��������: ִ�����ݱ��棬��������������Լ���������ֱ��������ļ���.
 * �������:
 *
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"���ݱ���ɹ���",
                             "ȷ��"
                            };
    char *plabel_choose[] = {"ȷ�ϱ�����Ϣ��",
                             "ȷ��    ȡ��"
                            };

    if (ChooseModule(plabel_choose) == 0){  /*ȡ������*/
        PopOff();
        return bRet;
    }
    PopOff();
    SaveSysData();   /*������Ϣ*/
    ShowModule(plabel_result, 2);

    return bRet;
}

/**
 * ��������: BackupData
 * ��������: ִ�����ݱ��ݣ���������������Լ���������ֱ𱸷�������ļ���.
 * �������:
 *
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"���ݳɹ����ѱ�������",
                             "C:\ClassBackup",
                             "ȷ��"
                            };
    char *plabel_choose[] = {"ȷ�ϱ�����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    char *filename = {"C:\\ClassBackup\\"};  /*����·��*/

    if (ChooseModule(plabel_choose) == 0){  /*ȡ������*/
        PopOff();
        return bRet;
    }
    PopOff();
    BackupSysData(filename);   /*������Ϣ*/
    ShowModule(plabel_result, 3);

    return bRet;
}

/**
 * ��������: RestoreData
 * ��������: ִ�����ݻָ�����������������Լ�������Ϣ���ݴ�����ļ��ж���ϵͳ��.
 * �������:
 *
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"�ָ���Ϣ�ɹ���",
                             "ȷ��"
                            };
    char *plabel_choose[] = {"ȷ�ϻָ���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    char *filename = {"C:\\ClassBackup\\"};  /*�����ļ�����·��*/

    if (ChooseModule(plabel_choose) == 0){  /*ȡ���ָ�*/
        PopOff();
        return bRet;
    }
    PopOff();
    RestoreSysData(filename);   /*�ָ���Ϣ*/
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
    char *pCh[] = {"ȷ���˳�ϵͳ��", "ȷ��    ȡ��"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
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


/**����ά��ģ��*/

/**
 * ��������: MaintainSubjectInfo
 * ��������: ִ�пγ���Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainSubjectInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"�γ���Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ�","ȷ��"},
                               {"�γ���Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�","ȷ��"},
                               {"�γ���Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ�γ���Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();/*��ʾ���*/
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*����γ���Ϣ*/
        flag = InsertSubjectNode(&subject_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸Ŀγ���Ϣ*/
        flag = ModifSubjectNode(subject_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ���γ���Ϣ*/
        flag = DelSubjectNode(&subject_head);
        if(flag == 1){   /*ɾ���ɹ�*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*ȡ��ɾ��*/;}
        else{   /*ɾ��ʧ��*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*�������ѡ��*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();/*���ع��*/
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: MaintainRoomInfo
 * ��������: ִ�н�����Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainRoomInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"������Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ�������Ϣ�Ѵ��ڣ�","ȷ��"},
                               {"������Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�","ȷ��"},
                               {"������Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ������Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*���������Ϣ*/
        flag = InsertRoomNode(&room_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸Ľ�����Ϣ*/
        flag = ModifRoomNode(room_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ��������Ϣ*/
        flag = DelRoomNode(&room_head);
        if(flag == 1){   /*ɾ���ɹ�*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*ȡ��ɾ��*/;}
        else{   /*ɾ��ʧ��*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*�������ѡ��*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: MaintainTeacherInfo
 * ��������: ִ�н�ʦ��Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainTeacherInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"��ʦ��Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ���ʦ��Ϣ�Ѵ��ڣ�","ȷ��"},
                               {"��ʦ��Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�","ȷ��"},
                               {"��ʦ��Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ��ʦ��Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*�����ʦ��Ϣ*/
        flag = InsertTeacherNode(&teacher_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸Ľ�ʦ��Ϣ*/
        flag = ModifTeacherNode(teacher_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ����ʦ��Ϣ*/
        flag = DelTeacherNode(&teacher_head);
        if(flag == 1){   /*ɾ���ɹ�*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*ȡ��ɾ��*/;}
        else{   /*ɾ��ʧ��*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*�������ѡ��*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: MaintainClassInfo
 * ��������: ִ�а༶��Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainClassInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"�༶��Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ��༶��Ϣ�Ѵ��ڣ�","ȷ��"},
                               {"�༶��Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�","ȷ��"},
                               {"�༶��Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ�༶��Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();
    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*����༶��Ϣ*/
        flag = InsertClassNode(&class_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸İ༶��Ϣ*/
        flag = ModifClassNode(class_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ���༶��Ϣ*/
        flag = DelClassNode(&class_head);
        if(flag == 1){   /*ɾ���ɹ�*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*ȡ��ɾ��*/;}
        else{   /*ɾ��ʧ��*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*�������ѡ��*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: MaintainCourseInfo
 * ��������: ִ�п�����Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainCourseInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"������Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ�","ȷ��"},
                               {"������Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�","ȷ��"},
                               {"������Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ������Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();  /*���ֹ��*/

    scanf("%d",&chooseNum);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*���������Ϣ*/
        flag = InsertCourseNode(&course_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸Ŀ�����Ϣ*/
        flag = ModifCourseNode(course_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ��������Ϣ*/
        flag = DelCourseNode(&course_head);
        if(flag == 1){   /*ɾ���ɹ�*/
            ShowModule(*(plabel_result+4),2);
        }
        else if(flag == 2){ /*ȡ��ɾ��*/;}
        else{   /*ɾ��ʧ��*/
            ShowModule(*(plabel_result+5),2);
        }
    }

    else{   /*�������ѡ��*/
        ShowModule(*(plabel_result+6), 2);
    }

    hidecursor();  /*���ع��*/

    ClearScreen();
    ShowMenu();

    return bRet;
}

/**���ݲ�ѯģ��*/
/**
 * ��������: QuerySubjectInfo
 * ��������: ִ�пγ���Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QuerySubjectInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char subject_name[20];
    char class_name[40];
    SUBJECT_NODE *psubject_node = NULL;
    CLASS_NODE *pclass_node = NULL;
    COURSE_NODE *pcourse_node =NULL;
    int ChooseNum = 0;

    showcursor();/*��ʾ���*/
    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1��ͨ���γ����Ʋ��ҿγ̻�����Ϣ\n");
    printf("    2��ͨ���༶���Ʋ�����ѧϰ�����пγ���Ϣ\n");
    printf("\n  ��������֣�");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  ������γ����ƣ�");
        scanf ("%s", subject_name);
        psubject_node = SeekSubjectNode(subject_head, subject_name);/*���ҽ��*/

        if(psubject_node != NULL){/*����ҵ�*/
            printf ("\n  �γ̻�����Ϣ��\n");
            printf ("    �γ����ƣ�%s\n",psubject_node->subject_name);
            printf ("    �γ�ѧ�֣�%.1f\n", psubject_node ->subject_credits);
            printf ("    �γ�ѧʱ��%d\n", psubject_node ->subject_hours);
            ShowModule(*plabel_result, 2);
        }
        else{/*���δ�ҵ�*/
            printf ("\n  δ��ѯ����Ӧ�γ���Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else if (ChooseNum == 2){
        printf ("\n  ������༶���ƣ�");
        scanf ("%s", class_name);
        pclass_node=SeekClassNode(class_head,class_name);
        if(pclass_node==NULL){/*�༶��Ϣ����*/
            printf ("\n  δ��ѯ����Ӧ�༶��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//�����ѯ����Ӧ�༶
            if(pclass_node->ccnext !=NULL){//����Ӧ�༶�п��ý��
                pcourse_node = SeekSubjectNode2(pclass_node->ccnext,pclass_node->class_name);/*���Ҳ��������������*/

                ShowModule(*plabel_result, 2);
                printf ("\n\n    ��ѯ���ð༶�������пγ���Ϣ��(���γ���������)\n\n");
                printf ("  �γ�����                                  ѧ��       ѧʱ\n");
                for (;pcourse_node != NULL; pcourse_node = pcourse_node ->next){
                    printf("  %-40s", pcourse_node ->subject_name);
                    printf("  %-10.1f", SeekSubjectNode(subject_head,pcourse_node->subject_name)->subject_credits);
                    printf("  %-10d\n", SeekSubjectNode(subject_head,pcourse_node->subject_name)->subject_hours);
                }
            }

            else{/*����ð༶�����޿γ�*/
                printf ("\n  δ��ѯ����ð༶��صĿ�����Ϣ��\n");
                ShowModule(*(plabel_result+1),2);
            }
        }
    }

    else{
        printf ("\n  ������������\n");
    }

    hidecursor();/*���ع��*/

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryRoomInfo
 * ��������: ִ�н�����Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryRoomInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char building[20];
    char subject_name[20];
    char class_name[40];
    ROOM_NODE *proom_node=NULL;/*���ڴ洢�������*/
    CLASS_NODE *pclass_node=NULL;//���ڱ�����ѯ�༶���
    COURSE_NODE *pcourse_node;//���ڱ�����ѯ���ý��
    int ChooseNum = 0;
    int i,j;//������

    showcursor();/*��ʾ���*/

    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1 : ͨ����ѧ¥���Ʋ�ѯ�����н�����Ϣ\n");
    printf("    2 : ͨ���༶�Ϳγ����Ʋ�ѯ������������\n");
    printf("\n  ��������֣�");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  �������ѧ¥���ƣ�");
        scanf ("%s", building);
        proom_node = SeekRoomNode2(room_head, building);/*���Ҳ��������������*/

        if(proom_node != NULL){/*����ҵ�*/
            ShowModule(*plabel_result, 2);
            printf ("\n\n  ��ѯ���ý�ѧ¥�������н�����Ϣ��(��������������)\n");
            for (;proom_node != NULL; proom_node = proom_node ->next){
                printf("    %s %s\n", proom_node->building, proom_node->room_name);
            }
        }
        else{/*���δ�ҵ�*/
            printf ("\n  δ��ѯ����Ӧ��ѧ¥��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else if (ChooseNum == 2){
        printf ("\n  ������༶���ƣ�");
        scanf ("%s", class_name);
        printf ("\n  ������γ����ƣ�");
        scanf ("%s", subject_name);

        pclass_node=SeekClassNode(class_head,class_name);
        if(pclass_node==NULL){/*�༶��Ϣ����*/
            printf ("\n  δ��ѯ����Ӧ�༶��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//���� ��ѯ����Ӧ�༶ ������ѯ����
            if(pclass_node->ccnext !=NULL){//����Ӧ�༶�п��ý��
                pcourse_node = SeekRoomNode3(pclass_node->ccnext,subject_name,pclass_node->class_name);/*���Ҳ��������������*/

                if(pcourse_node!=NULL){//���ҵ���Ӧ���ý��
                    ShowModule(*plabel_result, 2);
                    printf ("\n\n    ��ѯ���Ľ�����Ϣ��\n\n");
                    printf ("  ����                  ʱ��        ����                ����\n");
                    for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
                        printf("  %-10s %-10s ��%-10d",pcourse_node->building,pcourse_node->room_name,pcourse_node->weekday);
                        for(i=1,j=0;i<=12;i++){
                            if(pcourse_node->lesson[i]){
                                printf("%d ",i);
                                j+=2;
                                if(i>=10) j++;
                            }
                        }
                        for(;j<20;j++){//��ȫ����
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
                else{/*����ð༶�޸ÿ�����Ϣ*/
                    printf ("\n  δ��ѯ����Ӧ������Ϣ��\n");
                    ShowModule(*(plabel_result+1),2);
                }

            }

            else{/*����ð༶����ؿ��ý��*/
                printf ("\n  δ��ѯ����ð༶��صĿ�����Ϣ��\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else{
        printf ("\n  ������������\n");
    }

    hidecursor();/*���ع��*/

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryTeacherInfo
 * ��������: ִ�н�ʦ��Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryTeacherInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char teacher_name[20];
    char subject_name[20];
    char class_name[40];
    TEACHER_NODE *pteacher_node=NULL;/*���ڴ洢�������*/
    SUBJECT_NODE *psubject_node=NULL;
    CLASS_NODE *pclass_node=NULL;
    COURSE_NODE *pcourse_node=NULL;//���ڱ�����ѯ���ý��
    int ChooseNum = 0;

    showcursor();/*��ʾ���*/

    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1 : ͨ����ʦ������ѯ��ʦ������Ϣ\n");
    printf("    2 : ͨ���༶���γ����Ʋ�ѯ���ον�ʦ��Ϣ\n");
    printf("    3 : ͨ���γ����Ʋ�ѯ�������ον�ʦ��Ϣ\n");
    printf("\n  ��������֣�");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  �������ʦ������");
        scanf ("%s", teacher_name);
        hidecursor();/*���ع��*/
        pteacher_node = SeekTeacherNode(teacher_head, teacher_name);/*���Ҳ������������*/

        if(pteacher_node != NULL){/*����ҵ�*/
            printf ("\n\n  ��ʦ������Ϣ��\n");
            printf ("    ��ʦ������%s\n",pteacher_node->teacher_name);
            printf ("    ��ʦְλ��%s\n", pteacher_node ->position);
            ShowModule(*plabel_result, 2);
        }
        else{/*���δ�ҵ�*/
            printf ("\n  δ��ѯ����Ӧ��ʦ��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else if (ChooseNum == 2){
        printf ("\n  ������༶���ƣ�");
        scanf ("%s", class_name);
        printf ("\n  ������γ����ƣ�");
        scanf ("%s", subject_name);
        hidecursor();/*���ع��*/

        pclass_node = SeekClassNode(class_head,class_name);
        if(pclass_node==NULL){/*�༶��Ϣ����*/
            printf ("\n  δ��ѯ����Ӧ�༶��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//���� ��ѯ����Ӧ�༶ ������ѯ��ʦ
            if(pclass_node->ccnext !=NULL){//����Ӧ�༶�п��ý��
                pcourse_node = SeekTeacherNode2(pclass_node->ccnext,subject_name,pclass_node->class_name);/*���Ҳ��������������*/

                if(pcourse_node!=NULL){//���ҵ���Ӧ���ö���
                    ShowModule(*plabel_result, 2);
                    printf ("\n\n  �ð༶��Ӧ��Ŀ���ον�ʦΪ��(����ʦ��������)\n");
                    for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
                        printf("    %-6s %s\n",pcourse_node->teacher_name,SeekTeacherNode(teacher_head,pcourse_node->teacher_name)->position);
                    }
                }
                else{/*����ð༶�޸ÿ�����Ϣ*/
                    printf ("\n  δ��ѯ����Ӧ������Ϣ��\n");
                    ShowModule(*(plabel_result+1),2);
                }

            }

            else{/*����ð༶����ؿ��ý��*/
                printf ("\n  δ��ѯ����ð༶��صĿγ���Ϣ��\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else if (ChooseNum == 3){
        printf ("\n  ������γ����ƣ�");
        scanf ("%s", subject_name);
        hidecursor();/*���ع��*/

        psubject_node = SeekSubjectNode(subject_head,subject_name);
        if(psubject_node==NULL){/*�γ���Ϣ����*/
            printf ("\n  δ��ѯ����Ӧ�γ���Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//���� ��ѯ����Ӧ�γ� ������ѯ��ʦ
            if(psubject_node->scnext !=NULL){//����Ӧ�γ��п��ý��
                pcourse_node = SeekTeacherNode3(psubject_node->scnext);/*���Ҳ��������������*/

                ShowModule(*plabel_result, 2);
                printf ("\n\n  �ÿγ̵��ον�ʦΪ��(����ʦ��������)\n");
                for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
                    printf("    %-6s %s\n",pcourse_node->teacher_name,SeekTeacherNode(teacher_head,pcourse_node->teacher_name)->position);
                }

            }

            else{/*����ÿγ�����ؿ��ý��*/
                printf ("\n  δ��ѯ����ÿγ���صĽ�ʦ��Ϣ��\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else{
        printf ("\n  ������������\n");
        hidecursor();/*���ع��*/
    }



    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryClassInfo
 * ��������: ִ�а༶��Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryClassInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char subject_name[20];
    char class_namem[40];
    SUBJECT_NODE *psubject_node=NULL;//���ڱ�����ѯ�γ̽��
    CLASS_NODE *pclass_node=NULL;/*���ڴ洢�������*/
    COURSE_NODE *pcourse_node;//���ڱ�����ѯ���ý��
    int ChooseNum = 0;

    showcursor();/*��ʾ���*/

    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1 : ͨ���γ����Ʋ�ѯ���޴˿γ̵����а༶��Ϣ\n");
    printf("    2 : ͨ�����ְ༶����ģ����ѯ�༶��Ϣ\n");
    printf("\n  ��������֣�");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf ("\n  ������γ����ƣ�");
        scanf ("%s", subject_name);
        psubject_node = SeekSubjectNode(subject_head,subject_name);/*���Ҳ������������*/
        if(psubject_node==NULL){/*�γ���Ϣ����*/
            printf ("\n  δ��ѯ����Ӧ�γ���Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
        else{//���� ��ѯ����Ӧ�γ� ������ѯ��ʦ
            if(psubject_node->scnext !=NULL){//����Ӧ�γ��п��ý��
                pclass_node = SeekClassNode2(psubject_node->scnext);/*���Ҳ��������������*/
                if(strlen(subject_name)<30){
                    ShowModule(*plabel_result, 2);
                }
                printf ("\n\n  ��ѧϰ�ÿγ̵İ༶�У�\n");
                for(;pclass_node!=NULL;pclass_node=pclass_node->next){
                    printf("    %s\n",pclass_node->class_name);
                }

            }

            else{/*����ÿγ�����ؿ��ý��*/
                printf ("\n  δ��ѯ����ÿγ���صİ༶��Ϣ��\n");
                ShowModule(*(plabel_result+1),2);
            }
        }

    }

    else if (ChooseNum == 2){
        printf ("\n  �����벿�ְ༶���ƣ�");
        scanf ("%s", class_namem);

        pclass_node = SeekClassNodeM(class_head, class_namem);/*���Ҳ������������*/
        if(pclass_node != NULL){/*����ҵ�*/
            printf ("\n  ���ҵ��İ༶�У�(���༶��������)\n");
            for(;pclass_node!=NULL;pclass_node=pclass_node->next){
                printf("    %s\n",pclass_node->class_name);
            }
            ShowModule(*plabel_result, 2);
        }
        else{/*���δ�ҵ�*/
            printf ("\n  δ��ѯ��ذ༶��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
        }
    }

    else{
        printf ("\n  ������������\n");
    }

    hidecursor();/*���ع��*/

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryCourseInfo
 * ��������: ִ�п�����Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryCourseInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char subject_name[40];
    char building[20];
    char room_name[20];
    char teacher_name[20];
    char class_name[40];
    int weekday;
    int week_start;
    int i;

    SUBJECT_NODE *psubject_node;/*�������ݷ����Ų��ҷ�������*/
    ROOM_NODE *proom_node;/*�������*/
    TEACHER_NODE *pteacher_node = NULL;
    CLASS_NODE *pclass_node=NULL;
    COURSE_NODE *pcourse_node=NULL;

    int ChooseNum = 0;

    showcursor();/*��ʾ���*/

    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1 : ͨ���γ̡����ҡ���ʦ��ʱ�������Ψһ���ҿ�����Ϣ\n");
    printf("    2 : ͨ���γ����Ʋ���������ؿ�����Ϣ(����ʦ��������)\n");
    printf("    3 : ͨ�����ҵ�ַ����������ؿ�����Ϣ(���γ���������)\n");    printf("    4 : ͨ����ʦ��������������ؿ�����Ϣ(���γ���������)\n");    printf("    5 : ͨ���༶���Ʋ���������ؿ�����Ϣ(���γ���������)\n");
    printf("\n\n  ��������֣�");
    scanf("%d", &ChooseNum);

    if (ChooseNum == 1){
        printf("\n  ������γ����ƣ�");
        scanf("%s", subject_name);
        printf("\n  ���������������ѧ¥��");
        scanf("%s", building);
        printf("\n  ������������ƣ�");
        scanf("%s", room_name);
        printf("\n  �������ʦ������");
        scanf("%s", teacher_name);
        printf("\n  ���������λ���ܼ���");
        scanf("%d", &weekday);
        printf("\n  �����������ʼ�ܴΣ�");
        scanf("%d", &week_start);

        //�ж�����ʱ���ʽ
        if(weekday<1 || weekday>7 ||
           week_start>29 || week_start<1 ){
            printf("\n  �������ʱ���ʽ����\n");
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }

        pcourse_node = SeekCourseNode(course_head,subject_name,building,room_name,
                                      teacher_name,weekday,week_start);/*���Ҳ������������*/
        if(pcourse_node!=NULL){//����ѯ��
            printf("\n  ������Ϣ��\n");
            printf("    �γ����ƣ�%s\n", pcourse_node ->subject_name);
            printf("    ���ҵ�ַ��%s %s\n",pcourse_node->building, pcourse_node ->room_name);
            printf("    ��ʦ������%s\n", pcourse_node ->teacher_name);
            printf("    ����༶��%s\n", pcourse_node ->class_name[0]);
            for(i=1;i<pcourse_node->class_num;i++){
                if(pcourse_node->class_name[i][0]!='\0'){
                    printf("              %s\n",pcourse_node->class_name[i]);
                }
            }
            printf("    ����ʱ�䣺��%d ������",pcourse_node->weekday);
            for(i=1;i<=12;i++){
                if(pcourse_node->lesson[i]){
                    printf("%d ",i);
                }
            }
            printf("\n");
            printf("    �����ܴΣ�");            for(i=1;i<=29;i++){
                if(pcourse_node->week[i]){
                    printf("%d ",i);
                }
            }
            printf("\n");

            ShowModule(*plabel_result, 2);
        }
        else{
            printf("\n  δ��ѯ����Ӧ������Ϣ��\n");
            ShowModule(*(plabel_result+1), 2);
        }

        printf("\n\n  ��������������˵�...\n");
        getch();
        ClearScreen();
        ShowMenu();
        return bRet;
    }
    else if (ChooseNum == 2){
        printf ("\n\n  ������γ����ƣ�");
        scanf ("%s", subject_name);
        psubject_node =SeekSubjectNode(subject_head,subject_name);
        if(psubject_node!=NULL){
            if(psubject_node->scnext){
                pcourse_node = SeekCourseNode_S(psubject_node->scnext);/*���򲢽����������*/
            }
        }
        else{
            printf("  δ��ѯ����Ӧ�γ���Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }
    }

    else if (ChooseNum == 3){
        printf ("\n  ��������ҵ�ַ��\n");
        printf("  ��ѧ¥��");
        scanf ("%s", building);
        printf("  ���ң�");
        scanf ("%s",room_name);
        proom_node =SeekRoomNode(room_head,room_name,building);
        if(proom_node!=NULL){
            if(proom_node->rcnext){
                pcourse_node = SeekCourseNode_R(proom_node->rcnext);/*���򲢽����������*/
            }
        }
        else{
            printf("  δ��ѯ����Ӧ������Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }
    }

    else if (ChooseNum == 4){
        printf ("\n  �������ʦ������");
        scanf ("%s", teacher_name);
        pteacher_node =SeekTeacherNode(teacher_head,teacher_name);
        if(pteacher_node!=NULL){
            if(pteacher_node->tcnext){
                pcourse_node = SeekCourseNode_T(pteacher_node->tcnext);/*���򲢽����������*/
            }
        }
        else{
            printf("  δ��ѯ����Ӧ��ʦ��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }
    }

    else if (ChooseNum == 5){
        printf ("\n  ������༶���ƣ�");
        scanf ("%s", class_name);
        pclass_node =SeekClassNode(class_head,class_name);
        if(pclass_node!=NULL){
            if(pclass_node->ccnext){
                pcourse_node = SeekCourseNode_C(pclass_node->ccnext,pclass_node->class_name);/*���򲢽����������*/
            }
        }
        else{
            printf("  δ��ѯ����Ӧ�༶��Ϣ��\n");
            ShowModule(*(plabel_result+1),2);
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();

            return bRet;
        }
    }

    else{
        printf ("\n  ������������\n");
        printf("\n  ��������������˵�...\n");
        getch();
        ClearScreen();
        ShowMenu();

        return bRet;
    }

    hidecursor();/*���ع��*/

    if(pcourse_node != NULL){/*����ҵ�*/
        ShowModule(*plabel_result, 2);
        printf ("\n\n  ��ѯ���Ŀ�����Ϣ��\n\n");

        for(;pcourse_node!=NULL;pcourse_node=pcourse_node->next){
            printf("    �γ����ƣ�%s\n", pcourse_node ->subject_name);
            printf("    ���ҵ�ַ��%s %s\n", pcourse_node->building,pcourse_node ->room_name);
            printf("    ��ʦ������%s\n", pcourse_node ->teacher_name);
            printf("    ����༶��%s\n", pcourse_node ->class_name[0]);
            for(i=1;i<pcourse_node->class_num;i++){
                if(pcourse_node->class_name[i][0]!='\0'){
                    printf("              %s\n",pcourse_node->class_name[i]);
                }
            }
            printf("    ����ʱ�䣺��%d ������",pcourse_node->weekday);
            for(i=1;i<=12;i++){
                if(pcourse_node->lesson[i]){
                    printf("%d ",i);
                }
            }
            printf("\n");
            printf("    �����ܴΣ�");            for(i=1;i<=29;i++){
                if(pcourse_node->week[i]){
                    printf("%d ",i);
                }
            }
            printf("\n\n");
        }
    }
    else{/*���δ�ҵ�*/
        printf ("\n  δ��ѯ����ؿ�����Ϣ��\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryRestRoomInfo
 * ��������: ִ�п��н�����Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryRestRoomInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    int weekday;//�ܼ�
    int week;//�ڼ���
    int lesson;//�ڼ��ڿ�
    ROOM_NODE *proom_node=NULL;/*���ڴ洢�������*/

    int i,j;//������

    showcursor();/*��ʾ���*/
    printf("\n  ��ģ�齫ͨ������ʱ���ѯĳ�ڿε����п��н�����Ϣ\n");
    printf("\n  ����������(1~29)��");
    scanf("%d", &week);
    printf("\n  �������ܼ�(1~7)��");
    scanf("%d", &weekday);
    printf("\n  ���������(1~12)��");
    scanf("%d", &lesson);
    hidecursor();/*���ع��*/

    //�ж�����ʱ���ʽ
    if(weekday<1 || weekday>7 ||
       lesson<1 || lesson>12 ||
       weekday<1 || weekday>29 ){
        printf("\n  ����ʱ���ʽ����\n");
        printf("\n\n  ��������������˵�...\n");
        getch();
        ClearScreen();
        ShowMenu();
        return bRet;
    }

    proom_node = SeekRestRoomNode(room_head, week,weekday,lesson);

    if(proom_node != NULL){/*����ҵ�*/
        ShowModule(*plabel_result, 2);
        printf ("\n  ��ѯ�� ��%d�� ��%d ��%d�ڿ� �Ŀ��н�����Ϣ��\n",week,weekday,lesson);
        for(;proom_node!=NULL;proom_node=proom_node->next){
            printf("    %-10s %-20s\n",proom_node->building,proom_node->room_name);
        }
    }
    else{/*���δ�ҵ�*/
        printf ("\n  �ڸ�ʱ��δ��ѯ�����н�����Ϣ��\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}


/**���ݷ���ģ��*/
/**
 * ��������: StatRoomUtilization
 * ��������: ִ�н��������ʷ����Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatRoomUtilization(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"�������","ȷ��"},
                                  {"����ʧ�ܣ�δ��ѯ����Ӧ��ѧ¥��Ϣ","ȷ��"}
                                 };
    char building[20];
    int week;
    int i;//������
    ROOM_NODE *proom_node=NULL;
    COURSE_NODE *pcourse_node;
    UTILI_NODE *putili_node;
    UTILI_NODE *putili_head=NULL;
    int room_num=0;//���Ҽ���
    int lesson_num=0;//�пν���
    int choose_num=0;


    showcursor();/*��ʾ���*/
    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf ("  1.ͨ�������ѧ¥�����������Խ�ѧ¥Ϊ��λ����һ����ָ��¥������������\n");
    printf ("  2.ͨ�������ѧ¥�����������Խ���Ϊ��λ����һ���ڸ�¥������������\n");
    printf ("\n  ������������ѡ���ܣ�");
    scanf("%d",&choose_num);
    hidecursor();/*���ع��*/

    if (choose_num==1){
        showcursor();/*��ʾ���*/
        printf ("\n  �������ѧ¥���ƣ�");
        scanf ("%s", building);        printf ("\n  �������ܴΣ�");
        scanf ("%d", &week);
        hidecursor();/*���ع��*/

        //���ʱ�������ʽ
        if(week<1 || week>29){
            printf("\n  ����������ʽ����\n");
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }

        proom_node = SeekRoomNode2(room_head, building);/*�����������*/

        if(proom_node != NULL){//����ѯ����Ӧ��ѧ¥��Ϣ
            for(;proom_node!=NULL;proom_node=proom_node->next){//����������
                for(pcourse_node=proom_node->rcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){//����ͳ�Ƹý���������
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

            //������
            ShowModule(*plabel_result, 2);
            printf ("\n  �������õ�%d��%s�Ľ��������ʣ�\n",week,building);
            printf("    ���ý��ҽ�����%d\n", room_num*56);
            printf("    ���ý��ҽ�����%d\n", lesson_num);
            if(room_num){
                printf("    ���������ʣ�%.3f\n", (float)lesson_num/(room_num*56));
            }
            else{
                printf("    �����޿��ý��ң�\n");
            }
        }
        else{
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if(choose_num==2){
        showcursor();/*��ʾ���*/
        printf ("\n  �������ѧ¥���ƣ�");
        scanf ("%s", building);        printf ("\n  �������ܴΣ�");
        scanf ("%d", &week);
        hidecursor();/*���ع��*/

        //���ʱ�������ʽ
        if(week<1 || week>29){
            printf("\n  ����������ʽ����\n");
            printf("\n\n  ��������������˵�...\n");
            getch();
            ClearScreen();
            ShowMenu();
            return bRet;
        }

        proom_node = SeekRoomNode2(room_head, building);/*�����������*/

        if(proom_node != NULL){//����ѯ����Ӧ��ѧ¥��Ϣ
            for(;proom_node!=NULL;proom_node=proom_node->next){//����������
                putili_node = (UTILI_NODE*)malloc(sizeof(UTILI_NODE));//�½������ʽ��
                strcpy(putili_node->room_name,proom_node->room_name);
                putili_node->lesson=0;
                for(pcourse_node=proom_node->rcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){//����ͳ�Ƹý���������
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

            //���ɹ������������ �����������
            if(putili_head){
                UTILI_NODE *putili_node_prior;
                UTILI_NODE *putili_node_after;
                UTILI_NODE *putili_node_temp;
                UTILI_NODE *putili_node_cur;

                putili_node_prior = putili_head;
                putili_node_temp = (UTILI_NODE *)malloc(sizeof(UTILI_NODE));/*���ڽ���������ʱ���*/

                while (putili_node_prior -> next != NULL){/*ѡ������*/
                    putili_node_cur = putili_node_prior;
                    putili_node_after = putili_node_prior -> next;
                    while (putili_node_after != NULL){/*cur��(���)��ʦ���Ƶ�ַ*/
                        if (putili_node_cur -> lesson< putili_node_after -> lesson){
                            putili_node_cur = putili_node_after;
                        }
                        putili_node_after = putili_node_after -> next;
                    }

                    if (putili_node_cur != putili_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                        *putili_node_temp = *putili_node_prior;
                        *putili_node_prior = *putili_node_cur;
                        putili_node_prior -> next = putili_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                        putili_node_temp -> next = putili_node_cur -> next;
                        *putili_node_cur = *putili_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
                    }
                    putili_node_prior = putili_node_prior -> next;
                }


                //������
                ShowModule(*plabel_result, 2);
                printf ("\n    �������õ�%d��%s�ĸ�������Ч (����Ч��������)��\n\n",week,building);
                printf ("  ����    ���ý��ҽ���    ���ý��ҽ���    ����������\n");
                for (;putili_head != NULL; putili_head = putili_head ->next){
                    printf("  %-10s", putili_head ->room_name);
                    printf("   %-13d", putili_head ->lesson);
                    printf("   %-10d", 12*7);
                    printf("   %-10.3f\n", (float)(putili_head->lesson)/(12*7));
                }
            }

            else{
                printf("  ��%d��%s�޿��ý��ң�\n",week,building);
            }
        }
        else{
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else{
        printf("\n  ������������\n");
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: StatRoomEfficiency
 * ��������: ִ�н�����Ч�����Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatRoomEfficiency(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"�������","ȷ��"},
                                  {"����ʧ�ܣ�δ��ѯ����Ӧ��ѧ¥��Ϣ","ȷ��"}
                                 };
    char building[20];
    int week;
    int i;//������
    ROOM_NODE *proom_node=NULL;
    COURSE_NODE *pcourse_node;
    UTILI_NODE *putili_head=NULL;//�����ͷ���
    UTILI_NODE *putili_node;

    showcursor();/*��ʾ���*/
    printf ("\n  ��ģ�齫ͨ�������ѧ¥������������������ָ��¥����������Ч\n");
    printf ("\n  �������ѧ¥���ƣ�");
    scanf ("%s", building);    printf ("\n  �������ܴΣ�");
    scanf ("%d", &week);
    hidecursor();/*���ع��*/

    //���ʱ�������ʽ
    if(week<1 || week>29){
        printf("\n  ����������ʽ����\n");
        printf("\n\n  ��������������˵�...\n");
        getch();
        ClearScreen();
        ShowMenu();
        return bRet;
    }

    proom_node = SeekRoomNode2(room_head, building);/*�����������*/

    if(proom_node != NULL){//����ѯ����Ӧ��ѧ¥��Ϣ
        for(;proom_node!=NULL;proom_node=proom_node->next){//����������
            putili_node = (UTILI_NODE*)malloc(sizeof(UTILI_NODE));//�½������ʽ��
            strcpy(putili_node->room_name,proom_node->room_name);
            putili_node->lesson=0;
            putili_node->lesson_day=0;
            putili_node->lesson_night=0;
            for(pcourse_node=proom_node->rcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->rcnext){//����ͳ�Ƹý���������
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
            if(putili_node->lesson_day>0 && putili_node->lesson_night==0){//���а�����ҹ��
                putili_node->effi_rent=100.0;
            }
            else if(putili_node->lesson_day==0 &&putili_node->lesson_night==0){//���ް�����ҹ��
                putili_node->effi_rent=-1.0;
            }
            else{
                putili_node->effi_rent=(float)(putili_node->lesson_day)/(putili_node->lesson_night);
            }
            putili_node->next=putili_head;
            putili_head=putili_node;
        }

        //���ɹ������������ �����������
        if(putili_head){
            UTILI_NODE *putili_node_prior;
            UTILI_NODE *putili_node_after;
            UTILI_NODE *putili_node_temp;
            UTILI_NODE *putili_node_cur;

            putili_node_prior = putili_head;
            putili_node_temp = (UTILI_NODE *)malloc(sizeof(UTILI_NODE));/*���ڽ���������ʱ���*/

            while (putili_node_prior -> next != NULL){/*ѡ������*/
                putili_node_cur = putili_node_prior;
                putili_node_after = putili_node_prior -> next;
                while (putili_node_after != NULL){/*cur��(���)��ַ*/
                    if (putili_node_cur ->effi_rent > putili_node_after ->effi_rent){
                        putili_node_cur = putili_node_after;
                    }
                    putili_node_after = putili_node_after -> next;
                }

                if (putili_node_cur != putili_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                    *putili_node_temp = *putili_node_prior;
                    *putili_node_prior = *putili_node_cur;
                    putili_node_prior -> next = putili_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                    putili_node_temp -> next = putili_node_cur -> next;
                    *putili_node_cur = *putili_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
                }
                putili_node_prior = putili_node_prior -> next;
            }

            //������
            ShowModule(*plabel_result, 2);
            printf ("\n    �������õ�%d��%s�ĸ�������Ч (����Ч��������)��\n\n",week,building);
            printf ("  ����    ����ʹ�ý���    ҹ��ʹ�ý���       ��ֵ\n");
            for (putili_node=putili_head;putili_head != NULL; putili_head = putili_head ->next){
                if(putili_head->effi_rent>-0.5){
                    printf("  %-10s", putili_head ->room_name);
                    printf("   %-13d", putili_head ->lesson_day);
                    printf("   %-10d", putili_head->lesson_night);
                    printf("   %-4.3f\n", putili_head->effi_rent);
                }
            }

            printf("\n  Tips:1.����ҹ���ſν�����ֵΪ100.0����ý��ҽ��а��챻�ſΣ�Ϊ���ܽ���\n");
            printf("       2.δ�ڱ��г��ֵĽ����ڸ������ſΣ�������δ������\n");

            while(putili_node && putili_node->effi_rent<-0.5){//�����ް�����ҹ����
                putili_node = putili_node->next;
            }
            if(putili_node && putili_node->effi_rent<2){//����ǰ���н���Ұ���/ҹ��2��������
                printf("\n\n  �������������½����ڵ�%d���ڵİ����ſε���ҹ���ſε���������Ϊ����Ч���䲻����\n  ",week);
                while(putili_node && putili_node->effi_rent<2){//������������
                    printf("  %s",putili_node->room_name);
                    putili_node = putili_node->next;
                }
            }
            else{
                printf("\n\n  �������������ܸ������ſεİ���ҹ��ֲ���Ժ�����Ч�������\n");
            }

        }

        else{
            printf("\n  ��%d��%s�޿ɷ������ң�\n",week,building);
        }
    }
    else{
        ShowModule(*(plabel_result+1), 2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: StatTeacherValidity
 * ��������: ִ�н�ʦ�ſκ����Է����Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatTeacherValidity(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"ͳ�����","ȷ��"},
                                  {"ͳ��ʧ�ܣ�δ��ѯ����ʦ�ڿ���Ϣ","ȷ��"}
                                 };
    int i,j;//������
    int flag_1=0;//��¼�Ƿ��е��ܲ�����ù���Ĳ��������
    int flag_2=0;//��¼�Ƿ��в�����ÿ����ͻ����ʱ�εĲ��������
    int lesson_max[30];//����ÿ���Ͽν���

    int teacher_num=0;//��ʦ����
    int teacher_sum=0;//���н�ʦ�ܿ�ʱ
    float teacher_ave=0;//��ʦ��ʱƽ��ֵ
    float teacher_dx=0;//��ʦ�ܿ�ʱ����


    TEACHER_NODE *pteacher_node=teacher_head;
    COURSE_NODE *pcourse_node=NULL;
    STATTEACHER_NODE *pstat_node=NULL;
    STATTEACHER_NODE *pstat_head=NULL;//������Ϣ��ͷָ��

    for(;pteacher_node!=NULL;pteacher_node=pteacher_node->next){
        for(i=0;i<30;i++){
            lesson_max[i]=0;
        }
        pstat_node = (STATTEACHER_NODE*)malloc(sizeof(STATTEACHER_NODE));//�½����
        strcpy(pstat_node->teacher_name,pteacher_node->teacher_name);
        strcpy(pstat_node->position,pteacher_node->position);
        pstat_node->lesson_sum=0;
        pstat_node->lesson_max=0;
        pstat_node->week_lesson_max=0;
        pstat_node->subject_num=0;
        //�������ý��
        for(pcourse_node=pteacher_node->tcnext;pcourse_node!=NULL;pcourse_node=pcourse_node->tcnext){//����ͳ�Ƹý���������
            for(i=1;i<30;i++){
                if(pcourse_node->week[i]){
                    for(j=1;j<=12;j++){
                        if(pcourse_node->lesson[j]){//����ѯ��һ�ڿ�
                            pstat_node->lesson_sum++;
                            lesson_max[i]++;
                        }
                        if(pcourse_node->lesson[4]&&pcourse_node->lesson[5]){//�����ÿ�Խ����
                            pstat_node->subject_num=1;
                            strcpy(pstat_node->subject_name,pcourse_node->subject_name);
                            flag_2=1;
                        }
                        if(pcourse_node->lesson[8]&&pcourse_node->lesson[9]){//�����ÿ�Խ����
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
        if(pstat_node->lesson_max>20) flag_1=1;//�����ڿγ���20�ڵ����
        //���ӽ��
        pstat_node->next=pstat_head;
        pstat_head=pstat_node;
    }

    if(pstat_head != NULL){//���ɹ������������ �������򲢽������ �����ܿ�ʱ����������
        STATTEACHER_NODE *pstat_node_prior;
        STATTEACHER_NODE *pstat_node_after;
        STATTEACHER_NODE *pstat_node_temp;
        STATTEACHER_NODE *pstat_node_cur;
        pstat_node_prior = pstat_head;
        pstat_node_temp = (STATTEACHER_NODE *)malloc(sizeof(STATTEACHER_NODE));/*���ڽ���������ʱ���*/
        while (pstat_node_prior -> next != NULL){/*ѡ������*/
            pstat_node_cur = pstat_node_prior;
            pstat_node_after = pstat_node_prior -> next;
            while (pstat_node_after != NULL){/*cur��(���)��ַ*/
                if (pstat_node_cur ->lesson_sum < pstat_node_after ->lesson_sum){
                    pstat_node_cur = pstat_node_after;
                }
                pstat_node_after = pstat_node_after -> next;
            }
            if (pstat_node_cur != pstat_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pstat_node_temp = *pstat_node_prior;
                *pstat_node_prior = *pstat_node_cur;
                pstat_node_prior -> next = pstat_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pstat_node_temp -> next = pstat_node_cur -> next;
                *pstat_node_cur = *pstat_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pstat_node_prior = pstat_node_prior -> next;
        }


        pstat_node = pstat_head;
        ShowModule(*plabel_result, 2);
        printf ("\n    �������ý�ʦ�ο���Ϣ��(���ܿ�ʱ������)\n\n");
        printf ("  ��ʦ����    ��ʦְλ    �����ܿ�ʱ    һ�ܽ��ڿ�ʱ���ֵ    \n");
        for (;pstat_node != NULL; pstat_node = pstat_node ->next){
            printf("  %-10s", pstat_node->teacher_name);
            printf("  %-10s", pstat_node->position);
            printf("      %-12d", pstat_node->lesson_sum);
            printf("  ��%d�� %-10d\n", pstat_node ->week_lesson_max,pstat_node->lesson_max);
            teacher_sum+=pstat_node->lesson_sum;
            teacher_num++;
        }

        //���㷽��
        teacher_ave=(float)teacher_sum/teacher_num;
        for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
            teacher_dx+=((pstat_node->lesson_sum-teacher_ave)*(pstat_node->lesson_sum-teacher_ave));
        }
        teacher_dx=teacher_dx/teacher_num;
        printf("\n\n  ��ʦƽ�����οο�ʱ��Ϊ:%.3f������Ϊ:%.3f��",teacher_ave,teacher_dx);
        if(teacher_dx>1){
            printf("�����ø���ʦ��ѧ���񲻹�ƽ����\n");
        }
        else{
            printf("�����ø���ʦ��ѧ�������ƽ����\n");
        }

        //��������
        if(flag_1 || flag_2){//�����ڲ�������
            printf("\n\n  ���⾭���������ſη��������½�ʦ��������ؽ��������\n");
            if(flag_1){//������һ���ڿι���
                printf("\n  ���½�ʦ��һ���ڵ��ν�ѧ���񽫳���ָ����ʱ����ѧ����Ϸ��أ�\n");
                for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
                    if(pstat_node->lesson_max>20){
                        printf("    %s��ʦ�ڵ�%d�ܵ�����%d����ʱ�Ľ�ѧ����.\n",pstat_node->teacher_name,
                                                                          pstat_node->week_lesson_max,
                                                                          pstat_node->lesson_max);
                    }
                }
            }
            if(flag_2){//�������ڿο�Խ��Ϣʱ��
                printf("\n  ���½�ʦ���εĿγ̿��ܿ����Ϣʱ�䣬��������\n");
                for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
                    if(pstat_node->subject_num==1){
                        printf("    %s��ʦ���ڵ� %s �ſο�Խ������ʱ��.\n",pstat_node->teacher_name,pstat_node->subject_name);
                    }
                    if(pstat_node->subject_num==2){
                        printf("    %s��ʦ���ڵ� %s �ſο�Խ�����ʱ��.\n",pstat_node->teacher_name,pstat_node->subject_name);
                    }
                }
            }
        }
    }
    else{
        ShowModule(*(plabel_result+1), 2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: StatClassValidity
 * ��������: ִ�а༶�ſκ����Է����Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatClassValidity(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"�������","ȷ��"},
                                  {"����ʧ�ܣ�δ��ѯ���༶�Ͽ���Ϣ","ȷ��"}
                                 };
    int class_i;
    int i,j;//������
    int lesson_max[30];//����ÿ���Ͽν���
    int flag=0;//�ж��Ƿ��в������ſ��������
    int day_lesson[30][6];
    int max;
    int min;

    int class_num=0;//�༶����
    int class_sum=0;//���а༶�ܿ�ʱ
    float class_ave=0;//�༶��ʱƽ��ֵ
    float class_dx=0;//�༶�ܿ�ʱ����

    CLASS_NODE *pclass_node=class_head;
    COURSE_NODE *pcourse_node=NULL;
    STATCLASS_NODE *pstat_node=NULL;
    STATCLASS_NODE *pstat_head=NULL;//������Ϣ��ͷָ��

    for(;pclass_node!=NULL;pclass_node=pclass_node->next){
        for(i=0;i<30;i++){
            lesson_max[i]=0;
            for(j=0;j<6;j++){
                day_lesson[i][j]=0;
            }
        }
        pstat_node = (STATCLASS_NODE*)malloc(sizeof(STATCLASS_NODE));//�½����
        strcpy(pstat_node->class_name,pclass_node->class_name);
        pstat_node->lesson_sum=0;
        pstat_node->lesson_max=0;
        pstat_node->week_lesson_max=0;
        pstat_node->max_de_min=0;
        //�������ý��
        for(pcourse_node=pclass_node->ccnext;pcourse_node!=NULL;pcourse_node=pcourse_node->ccnext[class_i]){//����ͳ�Ƹý���������
            for(i=1;i<30;i++){
                if(pcourse_node->week[i]){
                    for(j=1;j<=12;j++){
                        if(pcourse_node->lesson[j]){//����ѯ��һ�ڿ�
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

        //��ֵ������
        for(i=1;i<30;i++){//�������� ����ÿ�ܲ�ֵ
            max=0;
            min=13;
            for(j=1;j<6;j++){
                max=max>day_lesson[i][j]?max:day_lesson[i][j];
                min=min<day_lesson[i][j]?min:day_lesson[i][j];
            }
            day_lesson[i][0]=max-min;//��¼ÿ�ܽ�����ֵ
        }
        for(i=1;i<30;i++){//�����и�ֵ
            if(day_lesson[i][0]>pstat_node->max_de_min){//����ǰ�ܲ�ֵ���
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

        //���ӽ��
        pstat_node->next=pstat_head;
        pstat_head=pstat_node;
    }

    if(pstat_head != NULL){//���ɹ������������ ���༶�����������
        STATCLASS_NODE *pstat_node_prior;
        STATCLASS_NODE *pstat_node_after;
        STATCLASS_NODE *pstat_node_temp;
        STATCLASS_NODE *pstat_node_cur;
        pstat_node_prior = pstat_head;
        pstat_node_temp = (STATTEACHER_NODE *)malloc(sizeof(STATTEACHER_NODE));/*���ڽ���������ʱ���*/
        while (pstat_node_prior -> next != NULL){/*ѡ������*/
            pstat_node_cur = pstat_node_prior;
            pstat_node_after = pstat_node_prior -> next;
            while (pstat_node_after != NULL){/*cur��(���)��ַ*/
                if (strcmp(pstat_node_cur ->class_name , pstat_node_after ->class_name)>0){
                    pstat_node_cur = pstat_node_after;
                }
                pstat_node_after = pstat_node_after -> next;
            }
            if (pstat_node_cur != pstat_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pstat_node_temp = *pstat_node_prior;
                *pstat_node_prior = *pstat_node_cur;
                pstat_node_prior -> next = pstat_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pstat_node_temp -> next = pstat_node_cur -> next;
                *pstat_node_cur = *pstat_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pstat_node_prior = pstat_node_prior -> next;
        }


        ShowModule(*plabel_result, 2);
        printf ("\n    �������ð༶ѧϰ��Ϣ��(���༶��������)\n\n");
        printf ("    �༶����                ��ѧʱ    һ�ܿ�ʱ���ֵ    \n");
        for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
            printf("  %-25s", pstat_node->class_name);
            printf("  %-10d", pstat_node->lesson_sum);
            printf("  ��%d�� %-10d\n", pstat_node ->week_lesson_max,pstat_node->lesson_max);
            class_sum+=pstat_node->lesson_sum;
            class_num++;
            if(pstat_node->max_de_min>=6) flag=1;//��¼���ڲ��������
        }


        //���㷽��
        class_ave=(float)class_sum/class_num;
        for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
            class_dx+=((pstat_node->lesson_sum-class_ave)*(pstat_node->lesson_sum-class_ave));
        }
        class_dx=class_dx/class_num;
        printf("\n\n  �༶ƽ����ѧϰ��ʱ��Ϊ:%.3f������Ϊ:%.3f��",class_ave,class_dx);
        if(class_dx>1){
            printf("�����ø��༶ѧϰ���񲻹�ƽ����\n");
        }
        else{
            printf("�����ø��༶ѧϰ�������ƽ����\n");
        }

        //��������
        if(flag){//�����ڲ�������
            printf("\n\n  ���⾭���������ſη��������°༶��������ؽ��������(��������һ�������Ƿ�ƽ��)\n");
            for (pstat_node=pstat_head;pstat_node != NULL; pstat_node = pstat_node ->next){
                if(pstat_node->max_de_min>=6){
                printf("    %s�� ��%d�� ��%d����%d ���ſο�ʱ�����%d�ڣ�����ƽ��.\n",pstat_node->class_name,
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

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**����ģ��*/
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"��ͨ����ݼ����ò˵�����",
                           "��ͨ�� ���� ����������ҳ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL AboutSys(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"������Ϣ�����пƼ���ѧ",
                           "�ƿ�У��1601�� ���ݷ�",
                           "ȷ��"
                          };
    char *plabel_choose[] = {"ȷ�Ͽ���������ҳ��",
                             "ȷ��    ȡ��"
                            };


    ShowModule(plabel_name, 3);

    if(ChooseModule(plabel_choose)){  //���������
        system("explorer https://github.com/yifaanleo/shujujiegou");
    }

    return bRet;
}




/*******************************************************************
**************************** �� �� �� *****************************
*******************************************************************/

//�ļ�
/**
 * ��������: SaveSysData
 * ��������: ���������������.
 * �������: hd ����ͷ���ָ��
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
 */
BOOL SaveSysData()
{
    int i=0;//������
    TEACHER_NODE *pteacher_node;
    CLASS_NODE *pclass_node;
    ROOM_NODE *proom_node;
    SUBJECT_NODE *psubject_node;
    COURSE_NODE *pcourse_node;

    FILE *pfout;

    //�γ�
    pfout = fopen(gp_subject_info_filename, "wb+");
    for (psubject_node = subject_head; psubject_node != NULL; psubject_node = psubject_node->next){/*����γ���Ϣ*/
        fprintf(pfout,"%s %.1f %d\n",psubject_node->subject_name,psubject_node->subject_credits,psubject_node->subject_hours);
    }
    fclose(pfout);
    //����
    pfout = fopen(gp_room_info_filename, "wb+");
    for (proom_node = room_head; proom_node != NULL; proom_node = proom_node->next){/*���������Ϣ*/
        fprintf(pfout,"%s %s\n",proom_node->building,proom_node->room_name);
    }
    fclose(pfout);
    //��ʦ
    pfout = fopen(gp_teacher_info_filename, "wb+");
    for (pteacher_node = teacher_head; pteacher_node != NULL; pteacher_node = pteacher_node->next){/*�����ʦ��Ϣ*/
        fprintf(pfout,"%s %s\n",pteacher_node->teacher_name,pteacher_node->position);
    }
    fclose(pfout);
    //�༶
    pfout = fopen(gp_class_info_filename, "wb+");
    for (pclass_node = class_head; pclass_node != NULL; pclass_node = pclass_node->next){/*����༶��Ϣ*/
        fprintf(pfout,"%s\n",pclass_node->class_name);
    }
    fclose(pfout);
    //����
    pfout = fopen(gp_course_info_filename, "wb+");
    for (pcourse_node = course_head; pcourse_node != NULL; pcourse_node = pcourse_node->next){/*���������Ϣ*/
        fprintf(pfout,"%s ",pcourse_node->subject_name);
        fprintf(pfout,"%s ",pcourse_node->building);
        fprintf(pfout,"%s ",pcourse_node->room_name);
        fprintf(pfout,"%s ",pcourse_node->teacher_name);
        fprintf(pfout,"%d ",pcourse_node->weekday);

        for(i=1;i<=12;i++){//����
            if(pcourse_node->lesson[i]==1){
                fprintf(pfout,"%d.",i);
            }
        }
        fprintf(pfout," ");

        for(i=1;i<=29;i++){//����
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
 * ��������: BackupSysData
 * ��������: ������������ݱ��ݵ������ļ�.
 * �������: filename �����ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
 */
BOOL BackupSysData(char *filename)
{
    int i=0;//������
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

    //�γ�
    pfout = fopen(subject_info_filename, "wb+");
    for (psubject_node = subject_head; psubject_node != NULL; psubject_node = psubject_node->next){/*����γ���Ϣ*/
        fprintf(pfout,"%s %.1f %d\n",psubject_node->subject_name,psubject_node->subject_credits,psubject_node->subject_hours);
    }
    fclose(pfout);
    //����
    pfout = fopen(room_info_filename, "wb+");
    for (proom_node = room_head; proom_node != NULL; proom_node = proom_node->next){/*���������Ϣ*/
        fprintf(pfout,"%s %s\n",proom_node->building,proom_node->room_name);
    }
    fclose(pfout);
    //��ʦ
    pfout = fopen(teacher_info_filename, "wb+");
    for (pteacher_node = teacher_head; pteacher_node != NULL; pteacher_node = pteacher_node->next){/*�����ʦ��Ϣ*/
        fprintf(pfout,"%s %s\n",pteacher_node->teacher_name,pteacher_node->position);
    }
    fclose(pfout);
    //�༶
    pfout = fopen(class_info_filename, "wb+");
    for (pclass_node = class_head; pclass_node != NULL; pclass_node = pclass_node->next){/*����༶��Ϣ*/
        fprintf(pfout,"%s\n",pclass_node->class_name);
    }
    fclose(pfout);
    //����
    pfout = fopen(course_info_filename, "wb+");
    for (pcourse_node = course_head; pcourse_node != NULL; pcourse_node = pcourse_node->next){/*���������Ϣ*/
        fprintf(pfout,"%s ",pcourse_node->subject_name);
        fprintf(pfout,"%s ",pcourse_node->building);
        fprintf(pfout,"%s ",pcourse_node->room_name);
        fprintf(pfout,"%s ",pcourse_node->teacher_name);
        fprintf(pfout,"%d ",pcourse_node->weekday);

        for(i=1;i<=12;i++){//����
            if(pcourse_node->lesson[i]==1){
                fprintf(pfout,"%d.",i);
            }
        }
        fprintf(pfout," ");

        for(i=1;i<=29;i++){//����
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
 * ��������: RestoreSysData
 * ��������: ��ָ�������ļ��лָ������������.
 * �������: filename ��ű������ݵ������ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
 */
BOOL RestoreSysData(char *filename)
{
    int i=0;//������
    int count=0;//������
    float credits;//ѧ��
    int hours;//ѧʱ
    int weekday;//�ܼ�
    int class_num;//�༶����
    char subject_name[40],building[20],room_name[20],
         teacher_name[20],position[20],class_name[40];
         //�γ��� ��ѧ¥ ������
         //��ʦ�� ְλ �༶��
    char lesson[100];//����
    char week[100];//����

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

    //��ȡ�γ���Ϣ
    if ((pFile = fopen(subject_info_filename, "rb")) == NULL)
    {
        printf("�γ���Ϣ�����ļ���ʧ��!\n");
        return FALSE;
    }
    printf("�γ���Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж��γ���Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ŀγ���Ϣ����*/
    while (fscanf(pFile,"%s %f %d",subject_name,&credits,&hours)!=EOF)
    {
        //�½ڵ㸳ֵ
        pSubjectNode = (SUBJECT_NODE *)malloc(sizeof(SUBJECT_NODE));
        strcpy(pSubjectNode->subject_name,subject_name);
        pSubjectNode->subject_credits=credits;
        pSubjectNode->subject_hours=hours;
        pSubjectNode->scnext=NULL;
        pSubjectNode->next=NULL;

        //����
        //����ͷ���
        if(subject_head==NULL){
            subject_head = pSubjectNode;
            subject_temp = subject_head;
            count++;
        }
        //����Ϊ�������
        else{
            subject_temp -> next = pSubjectNode;
            subject_temp = subject_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (subject_head == NULL)
    {
        printf("�γ���Ϣ�����ļ�����ʧ��!\n");
        return FALSE;
    }
    printf("�γ���Ϣ�����ļ����سɹ�!\n������%d���γ���Ϣ\n",count);
    count = 0;


    //��ȡ������Ϣ
    if ((pFile = fopen(room_info_filename, "rb")) == NULL)
    {
        printf("������Ϣ�����ļ���ʧ��!\n");
        return FALSE;
    }
    printf("������Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж�������Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ľ�����Ϣ����*/
    while (fscanf(pFile,"%s %s",building,room_name)!=EOF)
    {
        //�½ڵ㸳ֵ
        pRoomNode = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
        strcpy(pRoomNode->building,building);
        strcpy(pRoomNode->room_name,room_name);
        pRoomNode->rcnext=NULL;
        pRoomNode->next=NULL;

        //����
        //����ͷ���
        if(room_head==NULL){
            room_head = pRoomNode;
            room_temp = room_head;
            count++;
        }
        //����Ϊ�������
        else{
            room_temp -> next = pRoomNode;
            room_temp = room_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (room_head == NULL)
    {
        printf("������Ϣ�����ļ�����ʧ��!\n");
        return FALSE;
    }
    printf("������Ϣ�����ļ����سɹ�!\n������%d��������Ϣ\n",count);
    count = 0;


    //��ȡ��ʦ��Ϣ
    if ((pFile = fopen(teacher_info_filename, "rb")) == NULL)
    {
        printf("��ʦ��Ϣ�����ļ���ʧ��!\n");
        return FALSE;
    }
    printf("��ʦ��Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж���ʦ��Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ľ�ʦ��Ϣ����*/
    while (fscanf(pFile,"%s %s",teacher_name,position)!=EOF)
    {
        //�½ڵ㸳ֵ
        pTeacherNode = (TEACHER_NODE *)malloc(sizeof(TEACHER_NODE));
        strcpy(pTeacherNode -> teacher_name,teacher_name);
        strcpy(pTeacherNode ->position,position);
        pTeacherNode -> next = NULL;
        pTeacherNode ->tcnext=NULL;

        //����
        //����ͷ���
        if(teacher_head==NULL){
            teacher_head = pTeacherNode;
            teacher_temp = teacher_head;
            count++;
        }
        //����Ϊ�������
        else{
            teacher_temp -> next = pTeacherNode;
            teacher_temp = teacher_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (teacher_head == NULL)
    {
        printf("��ʦ��Ϣ�����ļ�����ʧ��!\n");
        return FALSE;
    }
    printf("��ʦ��Ϣ�����ļ����سɹ�!\n������%d����ʦ��Ϣ\n",count);
    count = 0;


    //��ȡ�༶��Ϣ
    if ((pFile = fopen(class_info_filename, "rb")) == NULL)
    {
        printf("�༶��Ϣ�����ļ���ʧ��!\n");
        return FALSE;
    }
    printf("�༶��Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж��༶��Ϣ���ݣ��������Ƚ��ȳ���ʽ�����İ༶��Ϣ����*/
    while (fscanf(pFile,"%s",class_name)!=EOF)
    {
        //�½ڵ㸳ֵ
        pClassNode = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
        strcpy(pClassNode->class_name,class_name);
        pClassNode->ccnext=NULL;
        pClassNode->next=NULL;

        //����
        //����ͷ���
        if(class_head==NULL){
            class_head = pClassNode;
            class_temp = class_head;
            count++;
        }
        //����Ϊ�������
        else{
            class_temp -> next = pClassNode;
            class_temp = class_temp -> next;
            count++;
        }
    }
    fclose(pFile);
    if (class_head == NULL)
    {
        printf("�༶��Ϣ�����ļ�����ʧ��!\n");
        return FALSE;
    }
    printf("�༶��Ϣ�����ļ����سɹ�!\n������%d���༶��Ϣ\n",count);
    count = 0;


    //��ȡ������Ϣ
    if ((pFile = fopen(course_info_filename, "rb")) == NULL)
    {
        printf("������Ϣ�����ļ���ʧ��!\n");
        return FALSE;
    }
    printf("������Ϣ�����ļ��򿪳ɹ�!\n");
    /*�������ļ��ж�������Ϣ���ݣ��������Ƚ��ȳ���ʽ�����Ŀ�����Ϣ����*/
    while (fscanf(pFile,"%s %s %s %s %d %s %s %d",subject_name,building,
                  room_name,teacher_name,&weekday, lesson, week, &class_num)!=EOF)
    {
        //�½ڵ㸳ֵ
        pCourseNode = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        for(i=0;i<10;i++){//��ʼ��
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

        //������������
        //����ͷ���
        if(course_head==NULL){
            course_head = pCourseNode;
            course_temp = course_head;
            count++;
        }
        //����Ϊ�������
        else{
            course_temp -> next = pCourseNode;
            course_temp ->next->prior=course_temp;
            course_temp = course_temp -> next;
            count++;
        }

        //pcourse�����������Ϣ����
        //�γ�
        psubject_node = SeekSubjectNode(subject_head,pCourseNode->subject_name);
        pCourseNode->scnext = psubject_node->scnext;
        psubject_node->scnext = pCourseNode;
        //�༶
        for(i=0;i<class_num;i++){
            pclass_node = SeekClassNode(class_head,pCourseNode->class_name[i]);
            pCourseNode->ccnext[i]=pclass_node->ccnext;
            pclass_node->ccnext=pCourseNode;
        }
        //��ʦ
        pteacher_node = SeekTeacherNode(teacher_head,pCourseNode->teacher_name);
        pCourseNode->tcnext=pteacher_node->tcnext;
        pteacher_node->tcnext=pCourseNode;
        //����
        proom_node = SeekRoomNode(room_head,pCourseNode->room_name,pCourseNode->building);
        pCourseNode->rcnext=proom_node->rcnext;
        proom_node->rcnext=pCourseNode;
    }
    fclose(pFile);
    if (course_head == NULL)
    {
        printf("������Ϣ�����ļ�����ʧ��!\n");
        return FALSE;
    }
    printf("������Ϣ�����ļ����سɹ�!\n������%d��������Ϣ\n",count);
    count = 0;

    return TRUE;
}


//����ά��
/**
 * ��������: InsertSubjectNode
 * ��������: �ڿγ������в���һ���γ���Ϣ���.
 * �������: hd �γ���ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertSubjectNode(SUBJECT_NODE **hd)
{
    SUBJECT_NODE *psubject_node, *temp;
    psubject_node = (SUBJECT_NODE *)malloc(sizeof(SUBJECT_NODE));
    psubject_node -> scnext = NULL;
    psubject_node -> next = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  ������γ����ƣ�");
    scanf("%s", psubject_node->subject_name);
    printf("\n  ������γ�ѧ�֣�");
    scanf("%f", &psubject_node->subject_credits);
    printf("\n  ������γ�ѧʱ��");
    scanf("%d", &psubject_node->subject_hours);

    hidecursor();/*���ع��*/

    temp = *hd;
    if (*hd == NULL){/*���û��ͷ���*/
        *hd = psubject_node;
        (*hd) -> next = NULL;
        (*hd) -> scnext = NULL;
    }
    else{
        while (temp != NULL){/*�����ظ����*/
            if (strcmp(temp ->subject_name, psubject_node ->subject_name) == 0){
                printf("  �ÿγ���Ϣ�Ѵ��ڣ�\n");
                return FALSE;
            }
            temp = temp -> next;
        }
        psubject_node -> next = (*hd) -> next; /*�����½��*/
        (*hd) -> next = psubject_node;
        psubject_node -> scnext = NULL;
    }
    return TRUE;
}

/**
 * ��������: ModifSubjectNode
 * ��������: ��ָ���Ŀγ���Ϣ������ݽ����޸�.
 * �������: hd �γ���ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 0��ʾ�޸�ʧ��
 *
 * ����˵��:
 */
int ModifSubjectNode(SUBJECT_NODE *hd)
{
    char subject_name[40];
    float subject_credits;
    int subject_hours;
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    SUBJECT_NODE *psubject_node,*psubject_temp;

    showcursor();/*��ʾ���*/

    printf("\n  ��������Ҫ�޸ĵĿγ����ƣ�");
    scanf("%s", subject_name);

    hidecursor();/*���ع��*/

    psubject_node = SeekSubjectNode(hd, subject_name);   /*����ָ��������Ϣ���*/
    if (psubject_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    �γ����ƣ�%s\n", psubject_node ->subject_name);
        printf("    �γ�ѧ�֣�%.1f\n", psubject_node ->subject_credits);
        printf("    �γ�ѧʱ��%d\n", psubject_node ->subject_hours);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }
        showcursor();/*��ʾ���*/
        printf("\n  �������޸ĺ�Ŀγ����ƣ�");
        scanf("%s", subject_name);
        printf("\n  �������޸ĺ�Ŀγ�ѧ�֣�");
        scanf("%f", &subject_credits);
        printf("\n  �������޸ĺ�Ŀγ�ѧʱ��");
        scanf("%d", &subject_hours);
        hidecursor();/*���ع��*/

        //�����ظ����
        psubject_temp=hd;
        while (psubject_temp != NULL){
            if (strcmp(psubject_temp ->subject_name, subject_name) == 0 &&
                strcmp(psubject_node->subject_name,subject_name)!=0){
                printf("  �ÿγ���Ϣ�Ѵ��ڣ�\n");
                return 0;
            }
            psubject_temp = psubject_temp -> next;
        }

        //�޸Ŀγ̽ڵ�
        strcpy(psubject_node->subject_name,subject_name);
        psubject_node->subject_credits=subject_credits;
        psubject_node->subject_hours=subject_hours;

        //�޸Ŀ��ýڵ�
        COURSE_NODE *temp=psubject_node->scnext;//��ֵͷ���
        for(;temp!=NULL;temp=temp->scnext){
            strcpy(temp->subject_name,subject_name);
        }
        return 1;
    }
    else{
        printf("  δ��ѯ���ÿγ���Ϣ��\n");
        return 0;
    }
}

/**
 * ��������: DelSubjectNode
 * ��������: �ӿγ�������ɾ��ָ���Ŀγ���Ϣ���.
 * �������: hd �γ���ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��.
 *
 * ����˵��:
 */
int DelSubjectNode(SUBJECT_NODE **hd)
{
    char subject_name[40];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    SUBJECT_NODE *psubject_node_prior = NULL,
                 *psubject_node_current = *hd;

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ���Ŀγ����ƣ�");
    scanf("%s", subject_name);

    hidecursor();/*���ع��*/

    while (psubject_node_current != NULL
           && strcmp(psubject_node_current ->subject_name, subject_name) != 0){
        psubject_node_prior = psubject_node_current;
        psubject_node_current = psubject_node_current -> next;
    }
    if (psubject_node_current != NULL){  /*����ҵ�*/
        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    �γ����ƣ�%s\n", psubject_node_current ->subject_name );
        printf("    �γ�ѧ�֣�%.1f\n", psubject_node_current ->subject_credits );
        printf("    �γ�ѧʱ��%d\n", psubject_node_current ->subject_hours );
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }

        else{   /*ɾ����Ϣ*/
        if (psubject_node_prior == NULL){   /*���λ�ڿγ̵����ϵ�һ��λ��*/
            while(psubject_node_current->scnext){//ɾ����ؿ��ý��
                DelCourseNodeS(psubject_node_current->scnext);
            }
            *hd = psubject_node_current -> next;
        }
        else{//����λ������λ��
            while(psubject_node_current->scnext){//ɾ����ؿ��ý��
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
 * ��������: InsertRoomNode
 * ��������: �ڽ��������в���һ��������Ϣ���.
 * �������: hd ������ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertRoomNode(ROOM_NODE **hd)
{
    ROOM_NODE *proom_node, *temp;
    proom_node = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
    proom_node -> rcnext = NULL;
    proom_node -> next = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  ���������������ѧ¥���ƣ�");
    scanf("%s", proom_node->building);
    printf("\n  ������������ƣ�");
    scanf("%s", proom_node->room_name);

    hidecursor();/*���ع��*/

    temp = *hd;
    if (*hd == NULL){/*���û��ͷ���*/
        *hd = proom_node;
        (*hd) -> next = NULL;
        (*hd) -> rcnext = NULL;
    }
    else{
        while (temp != NULL){/*�����ظ����*/
            if (strcmp(temp ->room_name, proom_node->room_name) ==0 &&
                strcmp(temp->building,proom_node->building) == 0){
                printf("  �ý�����Ϣ�Ѵ��ڣ�\n");
                return FALSE;
            }
            temp = temp -> next;
        }
        proom_node -> next = (*hd) -> next; /*�����½��*/
        (*hd) -> next = proom_node;
        proom_node -> rcnext = NULL;
    }
    return TRUE;
}


/**
 * ��������: ModifRoomNode
 * ��������: ��ָ���Ľ�����Ϣ������ݽ����޸�.
 * �������: hd ������ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 0��ʾ�޸�ʧ��
 *
 * ����˵��:
 */
int ModifRoomNode(ROOM_NODE *hd)
{
    char room_name[20];
    char building[20];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    ROOM_NODE *proom_node,*proom_temp;

    showcursor();/*��ʾ���*/

    printf("\n  ��������Ҫ�޸ĵĽ���������ѧ¥��");
    scanf("%s", building);
    printf("\n  ��������Ҫ�޸ĵĽ������ƣ�");
    scanf("%s", room_name);

    hidecursor();/*���ع��*/

    proom_node = SeekRoomNode(hd, room_name, building);   /*����ָ��������Ϣ���*/
    if (proom_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    ����������ѧ¥��%s\n", proom_node ->building);
        printf("    �������ƣ�%s\n", proom_node ->room_name);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }
        showcursor();/*��ʾ���*/
        printf("\n  �������޸ĺ�Ľ�ѧ¥���ƣ�");
        scanf("%s", building);
        printf("\n  �������޸ĺ�Ľ������ƣ�");
        scanf("%s", room_name);
        hidecursor();/*���ع��*/

        //�����ظ����
        proom_temp=hd;
        while (proom_temp != NULL){
            if (strcmp(proom_temp ->room_name, room_name) ==0 &&
                strcmp(proom_temp->building,building) == 0 &&(
                strcmp(proom_node->room_name,room_name)!=0 ||
                strcmp(proom_node->building,building)!=0)){
                printf("  �ý�����Ϣ�Ѵ��ڣ�\n");
                return 0;
            }
            proom_temp = proom_temp -> next;
        }

        //�޸Ľ��ҽڵ�
        strcpy(proom_node ->building,building);
        strcpy(proom_node->room_name,room_name);

        //�޸Ŀ��ýڵ�
        COURSE_NODE *temp=proom_node->rcnext;//��ֵͷ���
        for(;temp!=NULL;temp=temp->rcnext){
            strcpy(temp->building,building);
            strcpy(temp->room_name,room_name);
        }
        return 1;
    }
    else{
        printf("  δ��ѯ���ý�����Ϣ��\n");
        return 0;
    }
}

/**
 * ��������: DelRoomNode
 * ��������: �ӽ���������ɾ��ָ���Ľ�����Ϣ���.
 * �������: hd ������ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��.
 *
 * ����˵��:
 */
int DelRoomNode(ROOM_NODE **hd)
{
    char building[20];
    char room_name[20];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    ROOM_NODE *proom_node_prior = NULL,
                 *proom_node_current = *hd;

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ���Ľ���������ѧ¥��");
    scanf("%s", building);
    printf("\n  ������Ҫɾ���Ľ������ƣ�");
    scanf("%s", room_name);

    hidecursor();/*���ع��*/

    while (proom_node_current != NULL
           && (strcmp(proom_node_current ->room_name, room_name) != 0
           || strcmp(proom_node_current->building,building)!=0)){
        proom_node_prior = proom_node_current;
        proom_node_current = proom_node_current -> next;
    }
    if (proom_node_current != NULL){  /*����ҵ�*/
        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    ������ѧ¥��%s\n", proom_node_current ->building );
        printf("    �������ƣ�%s\n", proom_node_current ->room_name );
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*ɾ����Ϣ*/
        if (proom_node_prior == NULL){   /*���λ�ڽ��ҵ����ϵ�һ��λ��*/
            while(proom_node_current->rcnext){//ɾ����ؿ��ý��
                DelCourseNodeS(proom_node_current->rcnext);
            }
            *hd = proom_node_current -> next;
        }
        else{//����λ������λ��
            while(proom_node_current->rcnext){//ɾ����ؿ��ý��
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
 * ��������: InsertTeacherNode
 * ��������: �ڽ�ʦ�����в���һ����ʦ��Ϣ���.
 * �������: hd ��ʦ��ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertTeacherNode(TEACHER_NODE **hd)
{
    TEACHER_NODE *pteacher_node, *temp;
    pteacher_node = (TEACHER_NODE *)malloc(sizeof(TEACHER_NODE));
    pteacher_node -> tcnext = NULL;
    pteacher_node -> next = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  �������ʦ������");
    scanf("%s", pteacher_node->teacher_name);
    printf("\n  �������ʦְλ��");
    scanf("%s", pteacher_node->position);

    hidecursor();/*���ع��*/

    temp = *hd;
    if (*hd == NULL){/*���û��ͷ���*/
        *hd = pteacher_node;
        (*hd) -> next = NULL;
        (*hd) -> tcnext = NULL;
    }
    else{
        while (temp != NULL){/*�����ظ����*/
            if (strcmp(temp -> teacher_name, pteacher_node -> teacher_name) == 0){
                printf("  �ý�ʦ��Ϣ�Ѵ��ڣ�\n");
                return FALSE;
            }
            temp = temp -> next;
        }

        pteacher_node -> next = (*hd) -> next; /*�����½��*/
        (*hd) -> next = pteacher_node;
        pteacher_node -> tcnext = NULL;
    }
    return TRUE;
}

/**
 * ��������: ModifTeacherNode
 * ��������: ��ָ���Ľ�ʦ��Ϣ������ݽ����޸�.
 * �������: hd ��ʦ��ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 0��ʾ�޸�ʧ��
 *
 * ����˵��:
 */
int ModifTeacherNode(TEACHER_NODE *hd)
{
    char teacher_name[20];
    char position[20];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    TEACHER_NODE *pteacher_node,*pteacher_temp;

    showcursor();/*��ʾ���*/

    printf("\n  ��������Ҫ�޸ĵĽ�ʦ������");
    scanf("%s", teacher_name);

    hidecursor();/*���ع��*/

    pteacher_node = SeekTeacherNode(hd, teacher_name);   /*����ָ��������Ϣ���*/
    if (pteacher_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    ��ʦ������%s\n", pteacher_node ->teacher_name);
        printf("    ��ʦְλ��%s\n", pteacher_node ->position);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }
        showcursor();/*��ʾ���*/
        printf("\n  �������޸ĺ�Ľ�ʦ������");
        scanf("%s", teacher_name);
        printf("\n  �������޸ĺ�Ľ�ʦְλ��");
        scanf("%s", position);
        hidecursor();/*���ع��*/

        //�����ظ����
        pteacher_temp=hd;
        while (pteacher_temp != NULL){
            if (strcmp(pteacher_temp -> teacher_name,teacher_name) == 0 &&
                strcmp(pteacher_node->teacher_name,teacher_name)!=0){
                printf("  �ý�ʦ��Ϣ�Ѵ��ڣ�\n");
                return 0;
            }
            pteacher_temp = pteacher_temp -> next;
        }

        //�޸Ľ�ʦ�ڵ�
        strcpy(pteacher_node->teacher_name,teacher_name);
        strcpy(pteacher_node->position,position);

        //�޸Ŀ��ýڵ�
        COURSE_NODE *temp=pteacher_node->tcnext;//��ֵͷ���
        for(;temp!=NULL;temp=temp->tcnext){
            strcpy(temp->teacher_name,teacher_name);
        }
        return 1;
    }
    else{
        printf("  δ��ѯ���ý�ʦ��Ϣ��\n");
        return 0;
    }
}

/**
 * ��������: DelTeacherNode
 * ��������: �ӽ�ʦ������ɾ��ָ���Ľ�ʦ��Ϣ���.
 * �������: hd ��ʦ��ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��.
 *
 * ����˵��:
 */
int DelTeacherNode(TEACHER_NODE **hd)
{
    char teacher_name[20];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    TEACHER_NODE *pteacher_node_prior = NULL,
                 *pteacher_node_current = *hd;

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ���Ľ�ʦ������");
    scanf("%s", teacher_name);

    hidecursor();/*���ع��*/

    while (pteacher_node_current != NULL
           && strcmp(pteacher_node_current ->teacher_name, teacher_name) != 0){
        pteacher_node_prior = pteacher_node_current;
        pteacher_node_current = pteacher_node_current -> next;
    }
    if (pteacher_node_current != NULL){  /*����ҵ�*/
        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    ��ʦ������%s\n", pteacher_node_current ->teacher_name );
        printf("    ��ʦְλ��%s\n", pteacher_node_current ->position );
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*ɾ����Ϣ*/
        if (pteacher_node_prior == NULL){   /*���λ�ڽ�ʦ�����ϵ�һ��λ��*/
            while(pteacher_node_current->tcnext){//ɾ����ؿ��ý��
                DelCourseNodeS(pteacher_node_current->tcnext);
            }
            *hd = pteacher_node_current -> next;
        }
        else{//����λ������λ��
            while(pteacher_node_current->tcnext){//ɾ����ؿ��ý��
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
 * ��������: InsertClassNode
 * ��������: �ڰ༶�����в���һ���༶��Ϣ���.
 * �������: hd �༶��ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertClassNode(CLASS_NODE **hd)
{
    CLASS_NODE *pclass_node, *temp;
    pclass_node = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
    pclass_node -> ccnext = NULL;
    pclass_node -> next = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  ������༶���ƣ�");
    scanf("%s", pclass_node->class_name);

    hidecursor();/*���ع��*/

    temp = *hd;
    if (*hd == NULL){/*���û��ͷ���*/
        *hd = pclass_node;
        (*hd) -> next = NULL;
        (*hd) -> ccnext = NULL;
    }
    else{
        while (temp != NULL){/*�����ظ����*/
            if (strcmp(temp ->class_name, pclass_node ->class_name) == 0){
                printf("  �ð༶��Ϣ�Ѵ��ڣ�\n");
                return FALSE;
            }
            temp = temp -> next;
        }
        pclass_node -> next = (*hd) -> next; /*�����½��*/
        (*hd) -> next = pclass_node;
        pclass_node -> ccnext = NULL;
    }
    return TRUE;
}

/**
 * ��������: ModifClassNode
 * ��������: ��ָ���İ༶��Ϣ������ݽ����޸�.
 * �������: hd �༶��ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 0��ʾ�޸�ʧ��
 *
 * ����˵��:
 */
int ModifClassNode(CLASS_NODE *hd)
{
    int i;
    char class_name[40];
    char class_name_past[40];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    CLASS_NODE *pclass_node,*pclass_temp;

    showcursor();/*��ʾ���*/

    printf("\n  ��������Ҫ�޸ĵİ༶���ƣ�");
    scanf("%s", class_name);

    hidecursor();/*���ع��*/

    strcpy(class_name_past,class_name);
    pclass_node = SeekClassNode(hd, class_name);   /*����ָ��������Ϣ���*/
    if (pclass_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    �༶���ƣ�%s\n", pclass_node ->class_name);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }
        showcursor();/*��ʾ���*/
        printf("\n  �������޸ĺ�İ༶���ƣ�");
        scanf("%s", class_name);
        hidecursor();/*���ع��*/

        //�����ظ����
        pclass_temp=hd;
        while (pclass_temp != NULL){
            if (strcmp(pclass_temp ->class_name, class_name) == 0 &&
                strcmp(pclass_node->class_name,class_name)!= 0){
                printf("  �ð༶��Ϣ�Ѵ��ڣ�\n");
                return 0;
            }
            pclass_temp = pclass_temp -> next;
        }

        //�޸İ༶�ڵ�
        strcpy(pclass_node->class_name,class_name);

        //�޸Ŀ��ýڵ�
        COURSE_NODE *temp=pclass_node->ccnext;//��ֵͷ���
        while(temp!=NULL){
            i=return_i(temp,class_name_past);
            strcpy(temp->class_name[i],class_name);
            temp=temp->ccnext[i];
        }
        return 1;
    }
    else{
        printf("  δ��ѯ���ð༶��Ϣ��\n");
        return 0;
    }
}

/**
 * ��������: DelClassNode
 * ��������: �Ӱ༶������ɾ��ָ���İ༶��Ϣ���.
 * �������: hd �༶��ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��.
 *
 * ����˵��:
 */
int DelClassNode(CLASS_NODE **hd)
{
    int class_i,j;
    char class_name[40];
    char class_name_past[40];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    CLASS_NODE *pclass_node_prior = NULL,
                 *pclass_node_current = *hd;
    COURSE_NODE *pcourse_node;
    COURSE_NODE *pcourse_temp;//���ڴ洢����ɾ����ccnextָ���Լ���ɾ������class

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ���İ༶���ƣ�");
    scanf("%s", class_name);
    strcpy(class_name_past,class_name);

    hidecursor();/*���ع��*/

    while (pclass_node_current != NULL
           && strcmp(pclass_node_current ->class_name, class_name) != 0){
        pclass_node_prior = pclass_node_current;
        pclass_node_current = pclass_node_current -> next;
    }
    if (pclass_node_current != NULL){  /*����ҵ�*/
        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    �༶���ƣ�%s\n", pclass_node_current ->class_name );
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*ɾ����Ϣ*/
            if (pclass_node_prior == NULL){   /*���λ�ڰ༶�����ϵ�һ��λ��*/
                pcourse_temp=pclass_node_current->ccnext;
                while(pcourse_temp){
                    pcourse_node=pcourse_temp;//nodeΪ��ǰ������
                    //����һ�����д�ɾ����class
                    if(pcourse_node->class_num==1){
                        pcourse_temp=pcourse_node->ccnext[0];//�洢����ɾ����ccnextָ��
                        DelCourseNodeS(pcourse_node);
                    }
                    //����һ����к��ж��class
                    else{
                        class_i=return_i(pcourse_node,class_name_past);
                        pcourse_temp=pcourse_node->ccnext[class_i];//�洢����ɾ����ccnextָ��
                        for(j=class_i;j<9;j++){//ɾ������ж�Ӧclass��Ϣ
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
            else{//����λ������λ��
                pcourse_temp=pclass_node_current->ccnext;
                while(pcourse_temp){
                    pcourse_node=pcourse_temp;//nodeΪ��ǰ������
                    //����һ�����д�ɾ����class
                    if(pcourse_node->class_num==1){
                        pcourse_temp=pcourse_node->ccnext[0];//�洢����ɾ����ccnextָ��
                        DelCourseNodeS(pcourse_node);
                    }
                    //����һ����к��ж��class
                    else{
                        class_i=return_i(pcourse_node,class_name_past);
                        pcourse_temp=pcourse_node->ccnext[class_i];//�洢����ɾ����ccnextָ��
                        for(j=class_i;j<9;j++){//ɾ������ж�Ӧclass��Ϣ
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
 * ��������: InsertCourseNode
 * ��������: �ڿ��������в���һ��������Ϣ��㣬�����ʦ���༶�����ҡ��γ����ж�Ӧ���ָ���¿��ý��.
 * �������: hd ������ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertCourseNode(COURSE_NODE **hd)
{
    int class_i;
    int i=0,j=0,k;//������
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

    showcursor();/*��ʾ���*/

    printf("\n  ������γ����ƣ�");
    scanf("%s", pcourse_node->subject_name);
    printf("\n  ���������������ѧ¥��");
    scanf("%s", pcourse_node->building);
    printf("\n  ������������ƣ�");
    scanf("%s", pcourse_node->room_name);
    printf("\n  �������ʦ������");
    scanf("%s", pcourse_node->teacher_name);

    pcourse_node->class_num=0;
    for(i=0;i<10;i++){//��ʼ��
        pcourse_node->class_name[i][0]='\0';
    }
    printf("\n  ������༶����(�ո���м�� �ļ�β��������)��");
    i=0;
    while(scanf("%s", pcourse_node->class_name[i])!=EOF){
        i++;
    }
    pcourse_node->class_num=i;

    printf("\n  ������γ̿������ܼ�(1~7)��");
    scanf("%d", &weekday);
    printf("\n  ������γ̿�ʼ����(1~12)��");
    scanf("%d", &les_start);
    printf("\n  ������γ̽�������(1~12)��");
    scanf("%d", &les_end);
    printf("\n  ������γ�����(1~29 �ո���м�� �ļ�β��������)��");
    i=0;
    while(scanf("%d",&week[i])!=EOF){
        if(week[i]<1 ||week[i]>29){
            printf("  ����������ʽ����\n");
            return FALSE;
        }
        i++;
    }

    hidecursor();/*���ع��*/

    //�ж�����ʱ���ʽ
    if(weekday<1 || weekday>7 ||
       les_start<1 || les_start>12 || les_end<1 || les_end>12 ||
       les_start>les_end ){
        printf("  �������ʱ���ʽ(�ܼ������)����\n");
        return FALSE;
    }

    //���ÿ���ʱ��
    pcourse_node->weekday = weekday;
    for(j=0;j<=12;j++){//��ʼ��
        pcourse_node->lesson[j]=0;
    }
    for(j=0;j<=29;j++){//��ʼ��
        pcourse_node->week[j]=0;
    }
    for(j=les_start;j<=les_end;j++){
        pcourse_node->lesson[j]=1;
    }
    for(j=0;j<i;j++){
        pcourse_node->week[week[j]]=1;
    }
    //week[0]��¼��ʼ����
    for(i=1;i<=29;i++){
        if(pcourse_node->week[i]){
            pcourse_node->week[0]=i;
            break;
        }
    }



    //�ж�ʱ�䲻��ͻ
    //�γ�
    psubject_node = SeekSubjectNode(subject_head,pcourse_node->subject_name);
    if(psubject_node == NULL){//δ��ѯ���γ�
        printf("  δ��ϵͳ�в��ҵ���Ӧ�γ���Ϣ��\n");
        return FALSE;
    }


    //����
    proom_node = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
    if(proom_node == NULL){//δ��ѯ������
        printf("  δ��ϵͳ�в��ҵ���Ӧ������Ϣ��\n");
        return FALSE;
    }
    temp=proom_node->rcnext;
    if(temp!=NULL){//�ý�������ؿ��� �ж�ʱ���Ƿ��ͻ
        for(;temp!=NULL;temp=temp->rcnext){//�����γ���ؿ���
            if(temp->weekday==weekday){//���ܼ���ͬ
                 for(i=1;i<=29;i++){//��������
                    if(temp->week[i] && pcourse_node->week[i]){//�������غ�
                        for(j=les_start;j<=les_end;j++){//�жϽ����Ƿ��ͻ
                            if(temp->lesson[j]){//����ͻ
                                printf("  ����ʱ���ͻ��\n");
                                return FALSE;
                            }
                        }
                    }
                }
            }
        }
    }


    //��ʦ
    pteacher_node = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
    if(pteacher_node == NULL){//δ��ѯ����ʦ
        printf("  δ��ϵͳ�в��ҵ���Ӧ��ʦ��Ϣ��\n");
        return FALSE;
    }
    temp=pteacher_node->tcnext;
    if(temp!=NULL){//�ý�ʦ����ؿ��� �ж�ʱ���Ƿ��ͻ
        for(;temp!=NULL;temp=temp->tcnext){//�����γ���ؿ���
            if(temp->weekday==weekday){//���ܼ���ͬ
                 for(i=1;i<=29;i++){//��������
                    if(temp->week[i] && pcourse_node->week[i]){//�������غ�
                        for(j=les_start;j<=les_end;j++){//�жϽ����Ƿ��ͻ
                            if(temp->lesson[j]){//����ͻ
                                printf("  ��ʦʱ���ͻ��\n");
                                return FALSE;
                            }
                        }
                    }
                }
            }
        }
    }

    //�༶
    for(k=0;k<pcourse_node->class_num;k++){
        pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
        if(pclass_node == NULL){//δ��ѯ���༶
            printf("  δ��ϵͳ�в��ҵ���Ӧ�༶��Ϣ��\n");
            return FALSE;
        }
        temp=pclass_node->ccnext;
        if(temp!=NULL){//�ð༶����ؿ��� �ж�ʱ���Ƿ��ͻ
            class_i=return_i(temp,pcourse_node->class_name[k]);
            for(;temp!=NULL;class_i=return_i(temp,pcourse_node->class_name[k]),temp=temp->ccnext[class_i]){//�����γ���ؿ���
                if(temp->weekday==weekday){//���ܼ���ͬ
                    for(i=1;i<=29;i++){//��������
                        if(temp->week[i] && pcourse_node->week[i]){//�������غ�
                            for(j=les_start;j<=les_end;j++){//�жϽ����Ƿ��ͻ
                                if(temp->lesson[j]){//����ͻ
                                    printf("  �༶(%s)ʱ���ͻ��\n",pcourse_node->class_name[k]);
                                    return FALSE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //�жϿ��ýڵ��Ƿ��ظ�(һ�첻�ܳ���������ͬ��Ϣ��������ͬ�Ŀ���
        temp=course_head;
        while (temp != NULL){/*�����ظ����*/
            if (strcmp(temp->subject_name,pcourse_node->subject_name)==0 &&
                strcmp(temp ->building, pcourse_node ->building) == 0 &&
                strcmp(temp->room_name,pcourse_node->room_name)==0 &&
                strcmp(temp->teacher_name,pcourse_node->teacher_name)==0&&
                temp->weekday ==pcourse_node->weekday){
                for(i=1;i<30;i++){
                    if(temp->week[i]&&pcourse_node->week[i]) {
                        printf("  �ÿ�����Ϣ�Ѵ��ڣ��ɳ����޸����п��õ�ʱ����Ϣ��\n");
                        return 0;
                    }
                }
                }
            temp = temp -> next;
        }


    //��pcourse_node�����������Ϣ����
    //��Ӧ�γ����ӿ���
    pcourse_node->scnext = psubject_node->scnext;
    psubject_node->scnext = pcourse_node;
    //��Ӧ�������ӿ���
    pcourse_node->rcnext=proom_node->rcnext;
    proom_node->rcnext=pcourse_node;
    //��Ӧ��ʦ���ӿ���
    pcourse_node->tcnext=pteacher_node->tcnext;
    pteacher_node->tcnext=pcourse_node;
    //��Ӧ�༶���ӿ���
    for(k=0;k<pcourse_node->class_num;k++){
        pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
        pcourse_node->ccnext[k]=pclass_node->ccnext;
        pclass_node->ccnext=pcourse_node;
    }


    //���õ�������ӿ��ý��
    if(course_head==NULL){//���ǵ�һ��
        pcourse_node->prior=NULL;
        pcourse_node->next=NULL;
        course_head=pcourse_node;
    }
    else{//����
        pcourse_node->prior=NULL;
        pcourse_node->next=course_head;
        pcourse_node->next->prior=pcourse_node;
        course_head=pcourse_node;
    }
    return TRUE;
}

/**
 * ��������: ModifCourseNode
 * ��������: ��ָ���Ŀ�����Ϣ������ݽ����޸�.
 * �������: hd ������ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 2��ʾȡ���޸�
 *
 * ����˵��:
 */
int ModifCourseNode(COURSE_NODE *hd)
{
    int class_i;
    int i,j,k;//������
    int choose_num;
    char subject_name[40];
    char building[20];
    char room_name[20];
    char teacher_name[20];
    int week_start;
    int class_num;
    int weekday;//�ܼ�
    int les_start;//���ÿ�ʼ�������޸Ŀ���ʱ��
    int les_end;//���ý����������޸Ŀ���ʱ��
    int week[50];//�����������޸Ŀ���ʱ��
    char class_name[10][40];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    SUBJECT_NODE *psubject_node,*psubject_node_del;
    CLASS_NODE *pclass_node,*pclass_node_del;
    TEACHER_NODE *pteacher_node,*pteacher_node_del;
    ROOM_NODE *proom_node,*proom_node_del;
    COURSE_NODE *pcourse_node, *temp;
    pcourse_node = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));

    showcursor();/*��ʾ���*/

    printf("\n    �˹��ܽ�ͨ���γ����ơ��������ڵء���ʦ������������ʼʱ��\n  ��Ψһȷ��������Ϣ�������޸�\n");
    printf("\n  ������γ����ƣ�");
    scanf("%s", subject_name);
    printf("\n  ���������������ѧ¥��");
    scanf("%s", building);
    printf("\n  ������������ƣ�");
    scanf("%s", room_name);
    printf("\n  �������ʦ������");
    scanf("%s", teacher_name);
    printf("\n  ���������λ���ܼ���");
    scanf("%d", &weekday);
    printf("\n  �����������ʼ�ܴΣ�");
    scanf("%d", &week_start);

    hidecursor();/*���ع��*/

    //�ж�����ʱ���ʽ
    if(weekday<1 || weekday>7 ||
       week_start>29 || week_start<1 ){
        printf("  �������ʱ���ʽ����\n");
        return 0;
    }

    pcourse_node = SeekCourseNode(hd, subject_name, building, room_name,
                                  teacher_name, weekday, week_start);   /*����ָ��������Ϣ���*/
    if (pcourse_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    �γ����ƣ�%s\n", pcourse_node ->subject_name);
        printf("    ���ҵ�ַ��%s %s\n",pcourse_node->building, pcourse_node ->room_name);
        printf("    ��ʦ������%s\n", pcourse_node ->teacher_name);

        printf("    ����༶��%s\n", pcourse_node ->class_name[0]);
        for(i=1;i<pcourse_node->class_num;i++){
            if(pcourse_node->class_name[i][0]!='\0'){
                printf("              %s\n",pcourse_node->class_name[i]);
            }
        }

        printf("    ����ʱ�䣺��%d ������",pcourse_node->weekday);
        for(i=1;i<=12;i++){
            if(pcourse_node->lesson[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        printf("    �����ܴΣ�");        for(i=1;i<=29;i++){
            if(pcourse_node->week[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }


        //�޸�
        showcursor();/*��ʾ���*/

        printf("\n  1.�γ����� 2.���ҵ�ַ 3.��ʦ���� 4.����༶ 5.����ʱ��\n  �����������ѡ�����޸ĵ����ݣ�");
        scanf("%d",&choose_num);

        if(choose_num==1){//�޸Ŀγ�����
            printf("\n  �������޸ĺ�Ŀγ����ƣ�");
            scanf("%s", subject_name);
            hidecursor();/*���ع��*/

            //�жϿγ��Ѵ��ڼ����޸Ŀγ�
            psubject_node = SeekSubjectNode(subject_head,subject_name);
            if(psubject_node == NULL){//δ��ѯ���γ�
                printf("  δ��ϵͳ�в��ҵ�Ŀ��γ���Ϣ��\n");
                return 0;
            }

            //����ѯ�� ɾ��ԭ������γ��������� ������µ�����
            psubject_node_del = SeekSubjectNode(subject_head,pcourse_node->subject_name);
            //�����ý���ڿγ���(����)����ǰ��
            if(pcourse_node == psubject_node_del->scnext){//�ӿγ�����ɾ��
                psubject_node_del->scnext=psubject_node_del->scnext->scnext;
            }
            //������ǰ�� ��������������Ѱ��
            else{
                for(temp=psubject_node_del->scnext;temp->scnext;temp=temp->scnext){
                    if(temp->scnext == pcourse_node){//temp->next�Ǵ�ɾ�����
                        temp->scnext=temp->scnext->scnext;
                        break;
                    }
                }
            }

            //�޸�Ϊ�¿��ò����ӿγ�
            strcpy(pcourse_node->subject_name,subject_name);
            pcourse_node->scnext = psubject_node->scnext;
            psubject_node->scnext = pcourse_node;

            return 1;
        }

        else if(choose_num==2){//�޸Ľ��ҵ�ַ
            printf("\n  ���������������ѧ¥��");
            scanf("%s", building);
            printf("\n  ������������ƣ�");
            scanf("%s", room_name);
            hidecursor();/*���ع��*/

            //�ж�ʱ�䲻��ͻ�����޸Ľ���
            proom_node = SeekRoomNode(room_head,room_name,building);
            if(proom_node == NULL){//δ��ѯ������
                printf("  δ��ϵͳ�в��ҵ�Ŀ�������Ϣ��\n");
                return 0;
            }
            temp=proom_node->rcnext;
            if(temp!=NULL){//�ý�������ؿ��� �ж�ʱ���Ƿ��ͻ
                for(;temp!=NULL;temp=temp->rcnext){//�����γ���ؿ���
                    if(temp->weekday==weekday){//���ܼ���ͬ
                         for(i=1;i<=29;i++){//��������
                            if(temp->week[i] && pcourse_node->week[i]){//�������غ�
                                for(j=1;j<=12;j++){//�жϽ����Ƿ��ͻ
                                    if(temp->lesson[j] && pcourse_node->lesson[j]){//����ͻ
                                        printf("  ����ʱ���ͻ��\n");
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //����ѯ�� ɾ��ԭ����������������� ������µ�����
            proom_node_del = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
            //�����ý���ڽ�����(����)����ǰ��
            if(pcourse_node == proom_node_del->rcnext){//�ӽ�������ɾ��
                proom_node_del->rcnext=proom_node_del->rcnext->rcnext;
            }
            //������ǰ�� ��������������Ѱ��
            else{
                for(temp=proom_node_del->rcnext;temp->rcnext;temp=temp->rcnext){
                    if(temp->rcnext == pcourse_node){//temp->next�Ǵ�ɾ�����
                        temp->rcnext=temp->rcnext->rcnext;
                        break;
                    }
                }
            }

            //��Ӧ�������ӿ���
            strcpy(pcourse_node->building,building);
            strcpy(pcourse_node->room_name,room_name);
            pcourse_node->rcnext=proom_node->rcnext;
            proom_node->rcnext=pcourse_node;

            return 1;
        }

        else if(choose_num==3){//�޸Ľ�ʦ����
            printf("\n  �������ʦ������");
            scanf("%s", teacher_name);
            hidecursor();/*���ع��*/
            //�ж�ʱ�䲻��ͻ�����޸Ľ�ʦ
            pteacher_node = SeekTeacherNode(teacher_head,teacher_name);
            if(pteacher_node == NULL){//δ��ѯ����ʦ
                printf("  δ��ϵͳ�в��ҵ�Ŀ���ʦ��Ϣ��\n");
                return 0;
            }
            temp=pteacher_node->tcnext;
            if(temp!=NULL){//�ý�ʦ����ؿ��� �ж�ʱ���Ƿ��ͻ
                for(;temp!=NULL;temp=temp->tcnext){//�����γ���ؿ���
                    if(temp->weekday==weekday){//���ܼ���ͬ
                         for(i=1;i<=29;i++){//��������
                            if(temp->week[i] && pcourse_node->week[i]){//�������غ�
                                for(j=1;j<=12;j++){//�жϽ����Ƿ��ͻ
                                    if(temp->lesson[j] && pcourse_node->lesson[j]){//����ͻ
                                        printf("  ��ʦʱ���ͻ��\n");
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //����ѯ�� ɾ��ԭ�������ʦ�������� ������µ�����
            pteacher_node_del = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
            //�����ý���ڽ�ʦ��(����)����ǰ��
            if(pcourse_node == pteacher_node_del->tcnext){//�ӽ�ʦ����ɾ��
                pteacher_node_del->tcnext=pteacher_node_del->tcnext->tcnext;
            }
            //������ǰ�� ������ʦ������Ѱ��
            else{
                for(temp=pteacher_node_del->tcnext;temp->tcnext;temp=temp->tcnext){
                    if(temp->tcnext == pcourse_node){//temp->next�Ǵ�ɾ�����
                        temp->tcnext=temp->tcnext->tcnext;
                        break;
                    }
                }
            }

            //��Ӧ��ʦ���ӿ���
            strcpy(pcourse_node->teacher_name,teacher_name);
            pcourse_node->tcnext=pteacher_node->tcnext;
            pteacher_node->tcnext=pcourse_node;

            return 1;
        }

        else if(choose_num==4){//�޸Ĳ���༶
            class_num=0;
            for(i=0;i<10;i++){//��ʼ��
                class_name[i][0]='\0';
            }
            printf("\n  ������༶����(�ո���м�� �ļ�β��������)��");
            i=0;
            while(scanf("%s", class_name[i])!=EOF){
                i++;
            }
            class_num=i;
            hidecursor();/*���ع��*/
            //�ж�ʱ�䲻��ͻ�����޸İ༶
            for(k=0;k<class_num;k++){
                pclass_node = SeekClassNode(class_head,class_name[k]);
                if(pclass_node == NULL){//δ��ѯ���༶
                    printf("  δ��ϵͳ�в��ҵ�Ŀ��༶(%s)��Ϣ��\n",class_name[k]);
                    return 0;
                }
                temp=pclass_node->ccnext;
                if(temp!=NULL){//�ð༶����ؿ��� �ж�ʱ���Ƿ��ͻ
                    for(;temp!=NULL;class_i=return_i(temp,class_name[k]),temp=temp->ccnext[class_i]){//�����γ���ؿ���
                        if(temp->weekday==weekday &&
                           (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                            strcmp(temp->building,pcourse_node->building)!=0 ||
                            strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                            strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                            temp->week[0] != pcourse_node->week[0]
                            )
                           ){//���ܼ���ͬ �Ҳ�����Ϊͬһ�����ü�¼
                            for(i=1;i<=29;i++){//��������
                                if(temp->week[i] && pcourse_node->week[i]){//�������غ�
                                    for(j=1;j<=12;j++){//�жϽ����Ƿ��ͻ
                                        if(temp->lesson[j] && pcourse_node->lesson[j]){//����ͻ
                                            printf("  %sʱ���ͻ��\n",class_name[k]);
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //����ѯ�� ɾ��ԭ������༶�������� ������µ�����
            for(i=0;i<pcourse_node->class_num;i++){//�������ö��������а༶��Ϣ
                pclass_node_del = SeekClassNode(class_head,pcourse_node->class_name[i]);
                //�����ý���ڰ༶��(����)����ǰ��
                if(pcourse_node == pclass_node_del->ccnext){//�ӽ�������ɾ��
                    class_i=return_i(pclass_node_del->ccnext,pcourse_node->class_name[i]);
                    pclass_node_del->ccnext=pclass_node_del->ccnext->ccnext[class_i];
                }
                //������ǰ�� ��������������Ѱ��
                else{
                    class_i=return_i(pclass_node_del->ccnext,pcourse_node->class_name[i]);
                    temp=pclass_node_del->ccnext;
                    for(;temp->ccnext[class_i];
                        class_i=return_i(temp,pcourse_node->class_name[i]),temp=temp->ccnext){
                        if(temp->ccnext[class_i] == pcourse_node){//temp->next�Ǵ�ɾ�����
                            temp->ccnext[class_i]=temp->ccnext[class_i]->ccnext[return_i(temp->ccnext[class_i],pcourse_node->class_name[i])];
                            break;
                        }
                    }
                }
            }
            //��Ӧ�༶���ӿ���
            //��ʼ��course�İ༶��
            for(k=0;k<10;k++){
                pcourse_node->class_name[k][0]='\0';
                pcourse_node->ccnext[k]=NULL;
            }
            //��ֵ�༶����༶
            pcourse_node->class_num =class_num;
            for(k=0;k<class_num;k++){
                strcpy(pcourse_node->class_name[k],class_name[k]);
                pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
                pcourse_node->ccnext[k]=pclass_node->ccnext;
                pclass_node->ccnext=pcourse_node;
            }
            hidecursor();/*���ع��*/
            return 1;
        }

        else if(choose_num==5){//�޸Ŀ���ʱ��
            //��ʼ����������
            for(i=0;i<50;i++){
                week[i]=0;
            }

            printf("\n  ������γ̿������ܼ�(1~7)��");
            scanf("%d", &weekday);
            printf("\n  ������γ̿�ʼ����(1~12)��");
            scanf("%d", &les_start);
            printf("\n  ������γ̽�������(1~12)��");
            scanf("%d", &les_end);
            printf("\n  ������γ�����(1~29 �ո���м�� �ļ�β��������)��");
            i=0;
            while(scanf("%d",&week[i])!=EOF){
                if(week[i]<1 ||week[i]>29){
                    printf("�������������ʽ����\n");
                    return 0;
                }
                i++;
            }

            //�ж�����ʱ���ʽ
            if(weekday<1 || weekday>7 ||
               les_start<1 || les_start>12 || les_end<1 || les_end>12 ||
               les_start>les_end ){
                printf("�������ʱ���ʽ����\n");
                hidecursor();/*���ع��*/
                return 0;
            }

            //���ÿ���ʱ�䲢��ʱ�洢��time_temp��
            COURSE_NODE *time_temp;
            time_temp=(COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            //��ֵ
            time_temp->weekday = weekday;
            for(j=0;j<=12;j++){//��ʼ������
                time_temp->lesson[j]=0;
            }
            for(j=0;j<=29;j++){//��ʼ������
                time_temp->week[j]=0;
            }
            for(j=les_start;j<=les_end;j++){
                time_temp->lesson[j]=1;
            }
            for(j=0;j<i;j++){
                time_temp->week[week[j]]=1;
            }
            //week[0]��¼��ʼ����
            for(i=1;i<=29;i++){
                if(time_temp->week[i]){
                    time_temp->week[0]=i;
                    break;
                }
            }

            //�ж�ʱ���Ƿ��ͻ
            //����
            proom_node = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
            temp=proom_node->rcnext;
            if(temp!=NULL){//�ý�������ؿ��� �ж�ʱ���Ƿ��ͻ
                for(;temp!=NULL;temp=temp->rcnext){//�����γ���ؿ���
                    if(temp->weekday==weekday){//���ܼ���ͬ
                         for(i=1;i<=29;i++){//��������
                            if(temp->week[i] && time_temp->week[i]){//�������غ�
                                for(j=les_start;j<=les_end;j++){//�жϽ����Ƿ��ͻ
                                    if(temp->lesson[j] &&
                                       (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                                        strcmp(temp->building,pcourse_node->building)!=0 ||
                                        strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                                        strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                                        strcmp(temp->class_name[0],pcourse_node->class_name[0])!=0 ||
                                        temp->week[0] != pcourse_node->week[0]
                                        )){//����ͻ(�������޸Ŀ�����Ϣ�ļ��)
                                        printf("  ����ʱ���ͻ��\n");
                                        hidecursor();/*���ع��*/
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //��ʦ
            pteacher_node = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
            temp=pteacher_node->tcnext;
            if(temp!=NULL){//�ý�ʦ����ؿ��� �ж�ʱ���Ƿ��ͻ
                for(;temp!=NULL;temp=temp->tcnext){//�����γ���ؿ���
                    if(temp->weekday==weekday){//���ܼ���ͬ
                         for(i=1;i<=29;i++){//��������
                            if(temp->week[i] && time_temp->week[i]){//�������غ�
                                for(j=les_start;j<=les_end;j++){//�жϽ����Ƿ��ͻ
                                    if(temp->lesson[j]&&
                                       (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                                        strcmp(temp->building,pcourse_node->building)!=0 ||
                                        strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                                        strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                                        strcmp(temp->class_name[0],pcourse_node->class_name[0])!=0 ||
                                        temp->week[0] != pcourse_node->week[0]
                                        )){//����ͻ(�������޸Ŀ�����Ϣ�ļ��)
                                        printf("  ��ʦʱ���ͻ��\n");
                                        hidecursor();/*���ع��*/
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //�༶
            for(k=0;k<pcourse_node->class_num;k++){
                pclass_node = SeekClassNode(class_head,pcourse_node->class_name[k]);
                temp=pclass_node->ccnext;
                if(temp!=NULL){//�ð༶����ؿ��� �ж�ʱ���Ƿ��ͻ
                    class_i=return_i(temp,pcourse_node->class_name[k]);
                    for(;temp!=NULL;class_i=return_i(temp,pcourse_node->class_name[k]),temp=temp->ccnext[class_i]){//�����γ���ؿ���
                        if(temp->weekday==weekday){//���ܼ���ͬ
                            for(i=1;i<=29;i++){//��������
                                if(temp->week[i] && time_temp->week[i]){//�������غ�
                                    for(j=les_start;j<=les_end;j++){//�жϽ����Ƿ��ͻ
                                        if(temp->lesson[j]&&
                                           (strcmp(temp->subject_name,pcourse_node->subject_name)!=0 ||
                                            strcmp(temp->building,pcourse_node->building)!=0 ||
                                            strcmp(temp->room_name,pcourse_node->room_name)!=0 ||
                                            strcmp(temp->teacher_name,pcourse_node->teacher_name)!=0 ||
                                            strcmp(temp->class_name[0],pcourse_node->class_name[0])!=0 ||
                                            temp->week[0] != pcourse_node->week[0]
                                            )){//����ͻ(�������޸Ŀ�����Ϣ�ļ��)
                                            printf("  �༶(%s)ʱ���ͻ��\n",pcourse_node->class_name[k]);
                                            hidecursor();/*���ع��*/
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            hidecursor();/*���ع��*/
            //�жϿ��ýڵ��Ƿ��ظ�(һ�첻�ܳ���������ͬ��Ϣ��������ͬ�Ŀ���
            temp=course_head;
            while (temp != NULL){/*�����ظ����*/
                if (strcmp(temp->subject_name,pcourse_node->subject_name)==0 &&
                    strcmp(temp ->building, pcourse_node ->building) == 0 &&
                    strcmp(temp->room_name,pcourse_node->room_name)==0 &&
                    strcmp(temp->teacher_name,pcourse_node->teacher_name)==0&&
                    temp->weekday ==time_temp->weekday &&
                    (temp->weekday != pcourse_node->weekday ||
                     temp->week[0] != pcourse_node->week[0])){
                    for(i=1;i<30;i++){
                        if(temp->week[i]&&time_temp->week[i]) {
                            printf("  �ÿ�����Ϣ�Ѵ��ڣ��ɳ����޸����п��õ�ʱ����Ϣ��\n");
                            return 0;
                        }
                    }
                }
                temp = temp -> next;
            }

            //�޸�pcourse_node��ʱ��
            pcourse_node->weekday=time_temp->weekday;
            for(i=0;i<13;i++){
                pcourse_node->lesson[i]=time_temp->lesson[i];
            }
            for(i=0;i<30;i++){
                pcourse_node->week[i]=time_temp->week[i];
            }

            hidecursor();/*���ع��*/
            return 1;

        }

        else{//�����������
            printf("      ������������");
            hidecursor();/*���ع��*/
            return 0;
        }
    }

    else{
        printf("  δ��ѯ����Ӧ������Ϣ��\n");
        hidecursor();/*���ع��*/
        return 0;
    }

}

/**
 * ��������: DelCourseNode
 * ��������: �ӿ�������ɾ��ָ���Ŀ�����Ϣ���.
 * �������: hd ������ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��
 *
 * ����˵��: ���ݿγ�������ַ����ʦ��������ʼ�ܴο���ȷ��Ψһ�Ŀ�����Ϣ
 */
int DelCourseNode(COURSE_NODE **hd)
{
    int i;//������
    char subject_name[40];
    char building[20];
    char room_name[20];
    char teacher_name[20];
    int week_start;
    int weekday;
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    COURSE_NODE *pcourse_node;

    showcursor();/*��ʾ���*/

    printf("\n    �˹��ܽ�ͨ���γ����ơ��������ڵء���ʦ������������ʼʱ��\n  ��Ψһȷ��������Ϣ������ɾ��\n");
    printf("\n  ������γ����ƣ�");
    scanf("%s", subject_name);
    printf("\n  ���������������ѧ¥��");
    scanf("%s", building);
    printf("\n  ������������ƣ�");
    scanf("%s", room_name);
    printf("\n  �������ʦ������");
    scanf("%s", teacher_name);
    printf("\n  ���������λ���ܼ���");
    scanf("%d", &weekday);
    printf("\n  �����������ʼ�ܴΣ�");
    scanf("%d", &week_start);

    hidecursor();/*���ع��*/

    pcourse_node = SeekCourseNode(course_head,subject_name,building,room_name,teacher_name,weekday,week_start);

    if (pcourse_node != NULL){/*����ҵ�*/
        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    �γ����ƣ�%s\n", pcourse_node ->subject_name);
        printf("    ���ҵ�ַ��%s\n", pcourse_node ->room_name);
        printf("    ��ʦ������%s\n", pcourse_node ->teacher_name);

        printf("    ����༶��%s\n", pcourse_node ->class_name[0]);
        for(i=1;i<pcourse_node->class_num;i++){
            if(pcourse_node->class_name[i][0]!='\0'){
                printf("              %s\n",pcourse_node->class_name[i]);
            }
        }

        printf("    ����ʱ�䣺��%d ������",pcourse_node->weekday);
        for(i=1;i<=12;i++){
            if(pcourse_node->lesson[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        printf("    �����ܴΣ�");        for(i=1;i<=29;i++){
            if(pcourse_node->week[i]){
                printf("%d ",i);
            }
        }
        printf("\n");

        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*���ú���ɾ����Ϣ*/
            DelCourseNodeS(pcourse_node);
        }
        return 1;
    }

    return 0;
}

/**
 * ��������: DelCourseNodeS
 * ��������: DelCourseNode���Ӻ���.
 */
void DelCourseNodeS(COURSE_NODE *pcourse_node)
{
    int class_i;
    int find;
    int i=0,j=0,k;//������
    int weekday=0;
    int les_start=0,les_end=0;
    int week_start=0,week_end=0;
    int week[50];

    SUBJECT_NODE *psubject_node;
    CLASS_NODE *pclass_node;
    TEACHER_NODE *pteacher_node;
    ROOM_NODE *proom_node;
    COURSE_NODE *temp;


    //�γ�����ɾ��
    psubject_node = SeekSubjectNode(subject_head,(pcourse_node)->subject_name);
    //�����ý���ڿγ���(����)����ǰ��
    if(pcourse_node == psubject_node->scnext){//�ӿγ�����ɾ��
        psubject_node->scnext=psubject_node->scnext->scnext;
    }
    //������ǰ�� ��������������Ѱ��
    else{
        for(temp=psubject_node->scnext;temp->scnext;temp=temp->scnext){
            if(temp->scnext == pcourse_node){//temp->next�Ǵ�ɾ�����
                temp->scnext=temp->scnext->scnext;
                break;
            }
        }
    }

    //��������ɾ��
    proom_node = SeekRoomNode(room_head,pcourse_node->room_name,pcourse_node->building);
    //�����ý���ڽ�����(����)����ǰ��
    if(pcourse_node == proom_node->rcnext){//�ӽ�������ɾ��
        proom_node->rcnext=proom_node->rcnext->rcnext;
    }
    //������ǰ�� ��������������Ѱ��
    else{
        for(temp=proom_node->rcnext;temp->rcnext;temp=temp->rcnext){
            if(temp->rcnext == pcourse_node){//temp->next�Ǵ�ɾ�����
                temp->rcnext=temp->rcnext->rcnext;
                break;
            }
        }
    }

    //��ʦ����ɾ��
    pteacher_node = SeekTeacherNode(teacher_head,pcourse_node->teacher_name);
    //�����ý���ڽ�ʦ��(����)����ǰ��
    if(pcourse_node == pteacher_node->tcnext){//�ӽ�ʦ����ɾ��
        pteacher_node->tcnext=pteacher_node->tcnext->tcnext;
    }
    //������ǰ�� ������ʦ������Ѱ��
    else{
        for(temp=pteacher_node->tcnext;temp->tcnext;temp=temp->tcnext){
            if(temp->tcnext == pcourse_node){//temp->next�Ǵ�ɾ�����
                temp->tcnext=temp->tcnext->tcnext;
                break;
            }
        }
    }

    //�༶����ɾ��
    for(i=0;i<pcourse_node->class_num;i++){//�������ö��������а༶��Ϣ
        pclass_node = SeekClassNode(class_head,pcourse_node->class_name[i]);
        //�����ý���ڰ༶��(����)����ǰ��
        if(pcourse_node == pclass_node->ccnext){//�ӽ�������ɾ��
            class_i=return_i(pclass_node->ccnext,pcourse_node->class_name[i]);
            pclass_node->ccnext=pclass_node->ccnext->ccnext[class_i];
        }
        //������ǰ�� ��������������Ѱ��
        else{
            class_i=return_i(pclass_node->ccnext,pcourse_node->class_name[i]);
            temp=pclass_node->ccnext;
            for(;temp->ccnext[class_i];
                class_i=return_i(temp,pcourse_node->class_name[i]),temp=temp->ccnext[class_i]){
                if(temp->ccnext[class_i] == pcourse_node){//temp->next�Ǵ�ɾ�����
                    temp->ccnext[class_i]=temp->ccnext[class_i]->ccnext[return_i(temp->ccnext[class_i],pcourse_node->class_name[i])];
                    break;
                }
            }
        }
    }

    //ɾ�����õ����н��
    //�������׽��
    if(course_head->next==NULL && course_head->prior==NULL){
        course_head=NULL;
        return 0;
    }
    //�����׽��
    if(pcourse_node->prior==NULL){//�滻Ϊ��̽ڵ�
        course_head=course_head->next;
        course_head->prior=NULL;
        return 0;
    }
    //����ɾ������β���
    if(pcourse_node->next==NULL){
        pcourse_node->prior->next=NULL;
        return 0;
    }
    //����ɾ��������ͨ���
    pcourse_node->prior->next=pcourse_node->next;
    pcourse_node->next->prior=pcourse_node->prior;
    return 0;
}


//���ݲ�ѯ
/**
 * ��������: SeekSubjectNode
 * ��������: ���γ����Ʋ��ҿγ���Ϣ���.
 * �������: hd �γ���ͷָ��
 *           subject_name �γ�����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
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

    if (find){  /*����ҵ�*/
        return psubject_node;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekSubjectNode2
 * ��������: �ڰ༶��ؿ������в��Ҳ��ظ��Ŀγ����Ʋ�����.
 * �������: hd �༶��ؿγ���ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekSubjectNode2(COURSE_NODE *hd,char *class_name)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior= NULL;
    COURSE_NODE *pcourse_node_after=NULL;
    COURSE_NODE *pcourse_node_cur=NULL;
    COURSE_NODE *pcourse_node_temp=NULL;

    char subject_name[50][40];
    int class_i;
    int flag=0;
    int find = 0;
    int i,j=0;//������

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){
        for(i=0;i<j;i++){
            if(strcmp(pcourse_node->subject_name,subject_name[i])==0){//���γ��ѱ���¼
                flag=1;
            }
        }
        if(!flag){//���γ�δ����¼
            strcpy(subject_name[j++],pcourse_node->subject_name);
            pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            *pcourse_temp = *pcourse_node;//���ƽ��ֵ
            pcourse_temp->next=pcourse_head;
            pcourse_head=pcourse_temp;
        }
        flag=0;
        class_i=return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)�γ����Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekRoomNode
 * ��������: ������������������ѧ¥���ҽ�����Ϣ���.
 * �������: hd ������ͷָ��
 *           room_name ��������
 *           building ����������ѧ¥
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
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

    if (find){  /*����ҵ�*/
        return proom_node;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekRoomNode2
 * ��������: ��ѯ��ѧ¥�����н������Ʋ�����.
 * �������: hd ������ͷָ��
 *           building ����������ѧ¥
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
ROOM_NODE *SeekRoomNode2(ROOM_NODE *hd, char *building)
{
    ROOM_NODE *proom_head=NULL;//ͷָ��
    ROOM_NODE *proom_temp=NULL;//���ڹ�������
    ROOM_NODE *proom_node=hd;//���ڱ���ԭʼ����

    //��������
    ROOM_NODE *proom_node_prior;
    ROOM_NODE *proom_node_after;
    ROOM_NODE *proom_node_cur;
    ROOM_NODE *proom_node_temp;

    while(proom_node !=NULL){
        if(strcmp(proom_node->building,building)==0){//����ѯ����Ӧ��ѧ¥
            proom_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
            *proom_temp = *proom_node;//���ƽ��ֵ
            proom_temp->next=proom_head;
            proom_head=proom_temp;
        }
        proom_node=proom_node->next;
    }

    //���ɹ������������ ��������
    if(proom_head){
        proom_node_prior = proom_head;
        proom_node_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));/*���ڽ���������ʱ���*/

        while (proom_node_prior -> next != NULL){/*ѡ������*/
            proom_node_cur = proom_node_prior;
            proom_node_after = proom_node_prior -> next;
            while (proom_node_after != NULL){/*cur��(��С)�������Ƶ�ַ*/
                if (strcmp (proom_node_cur -> room_name, proom_node_after -> room_name) > 0){
                    proom_node_cur = proom_node_after;
                }
                proom_node_after = proom_node_after -> next;
            }

            if (proom_node_cur != proom_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *proom_node_temp = *proom_node_prior;
                *proom_node_prior = *proom_node_cur;
                proom_node_prior -> next = proom_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                proom_node_temp -> next = proom_node_cur -> next;
                *proom_node_cur = *proom_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            proom_node_prior = proom_node_prior -> next;
        }
    }

    return proom_head;
}

/**
 * ��������: SeekRoomNode3
 * ��������: �ڰ༶�����������У����γ����Ʋ��ҽ�����Ϣ���.
 * �������: hd �༶��ؿγ���ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekRoomNode3(COURSE_NODE *hd,char *subject_name,char *class_name)
{
    int class_i;
    COURSE_NODE *pcourse_node=hd;//���ڱ���������
    COURSE_NODE *pcourse_head=NULL;//ͷָ��
    COURSE_NODE *pcourse_temp=NULL;//���ڹ�������

    while(pcourse_node !=NULL){
        if(strcmp(pcourse_node->subject_name,subject_name)==0){//����ѯ��
            pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            *pcourse_temp = *pcourse_node;//���ƽ��ֵ
            pcourse_temp->next=pcourse_head;
            pcourse_head=pcourse_temp;
        }
        class_i = return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    return pcourse_head;
}

/**
 * ��������: SeekTeacherNode
 * ��������: ����ʦ�������ҽ�ʦ��Ϣ���.
 * �������: hd ��ʦ��ͷָ��
 *           teacher_name ��ʦ����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
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

    if (find){  /*����ҵ�*/
        return pteacher_node;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekTeacherNode2
 * ��������: �ڰ༶��ؿ������в��Ҹ��ݿγ����Ʋ��ҽ�ʦ.
 * �������: hd �༶��ؿγ���ͷָ��
 *           subject_name �γ�����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekTeacherNode2(COURSE_NODE *hd,char *subject_name,char *class_name)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    char teacher_name[10][20];
    int class_i;
    int flag=0;
    int i,j=0;//������

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){
        if(strcmp(pcourse_node->subject_name,subject_name)==0){//����ѯ����Ӧ�γ�
            for(i=0;i<50;i++){
                if(strcmp(pcourse_node->teacher_name,teacher_name[i])==0){//����ʦ�ѱ���¼
                    flag=1;
                }
            }
            if(!flag){//����ʦδ����¼
                strcpy(teacher_name[j++],pcourse_node->teacher_name);
                pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
                *pcourse_temp = *pcourse_node;//���ƽ��ֵ
                pcourse_temp->next=pcourse_head;
                pcourse_head=pcourse_temp;
            }
            flag=0;
        }
        class_i=return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)�γ����Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> teacher_name, pcourse_node_after -> teacher_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekTeacherNode3
 * ��������: �ڿγ���ؿ������в��Ҳ��������н�ʦ.
 * �������: hd �γ���ؿγ���ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekTeacherNode3(COURSE_NODE *hd)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    char teacher_name[10][20];
    int flag=0;
    int i,j=0;//������

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){
        for(i=0;i<50;i++){
            if(strcmp(pcourse_node->teacher_name,teacher_name[i])==0){//����ʦ�ѱ���¼
                flag=1;
            }
        }
        if(!flag){//����ʦδ����¼
            strcpy(teacher_name[j++],pcourse_node->teacher_name);
            pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
            *pcourse_temp = *pcourse_node;//���ƽ��ֵ
            pcourse_temp->next=pcourse_head;
            pcourse_head=pcourse_temp;
        }
        flag=0;
        pcourse_node=pcourse_node->scnext;
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        //��������������
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)�γ����Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> teacher_name, pcourse_node_after -> teacher_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }

        //��ְλ��������
//        pcourse_node_prior = pcourse_head;
//        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

//        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
//            pcourse_node_cur = pcourse_node_prior;
//            pcourse_node_after = pcourse_node_prior -> next;
//            while (pcourse_node_after != NULL){/*cur��(���)�γ����Ƶ�ַ*/
//                if (strcmp (pcourse_node_cur -> position, pcourse_node_after -> position) < 0){
//                    pcourse_node_cur = pcourse_node_after;
 //               }
 //               pcourse_node_after = pcourse_node_after -> next;
 //           }

//            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
//                *pcourse_node_temp = *pcourse_node_prior;
//                *pcourse_node_prior = *pcourse_node_cur;
//                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
//                pcourse_node_temp -> next = pcourse_node_cur -> next;
//                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
//            }
//            pcourse_node_prior = pcourse_node_prior -> next;
//        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekClassNode
 * ��������: ���༶���Ʋ��Ұ༶��Ϣ���.
 * �������: hd �༶��ͷָ��
 *           class_name ��ʦ����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
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

    if (find){  /*����ҵ�*/
        return pclass_node;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekClassNode2
 * ��������: �ڿγ���ؿ������в��Ҳ��������а༶.
 * �������: hd �γ���ؿ�����ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
CLASS_NODE *SeekClassNode2(COURSE_NODE *hd)
{
    COURSE_NODE *pcourse_node=NULL;//���ڱ�����������
    CLASS_NODE *pclass_node=NULL;
    CLASS_NODE *pclass_head=NULL;
    CLASS_NODE *pclass_temp=NULL;

    //��������
    CLASS_NODE *pclass_node_prior;
    CLASS_NODE *pclass_node_after;
    CLASS_NODE *pclass_node_cur;
    CLASS_NODE *pclass_node_temp;

    char class_name[50][40];
    int flag=0;
    int i,j,k=0;//������

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){
        for(j=0;j<pcourse_node->class_num;j++){
            for(i=0;i<k;i++){
                if(strcmp(pcourse_node->class_name[j],class_name[i])==0){//���༶�ѱ���¼
                    flag=1;
                }
            }
            if(!flag){//���༶δ����¼
                strcpy(class_name[k++],pcourse_node->class_name[j]);
                pclass_node=SeekClassNode(class_head,pcourse_node->class_name[j]);
                pclass_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
                *pclass_temp = *pclass_node;//���ƽ��ֵ
                pclass_temp->next=pclass_head;
                pclass_head=pclass_temp;
            }
            flag=0;
        }
        pcourse_node=pcourse_node->scnext;
    }

    //���ɹ������������ ���༶���ƶ�������
    if(pclass_head){
        pclass_node_prior = pclass_head;
        pclass_node_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));/*���ڽ���������ʱ���*/

        while (pclass_node_prior -> next != NULL){/*ѡ������*/
            pclass_node_cur = pclass_node_prior;
            pclass_node_after = pclass_node_prior -> next;
            while (pclass_node_after != NULL){/*cur��(��С)�γ����Ƶ�ַ*/
                if (strcmp (pclass_node_cur -> class_name, pclass_node_after -> class_name) > 0){
                    pclass_node_cur = pclass_node_after;
                }
                pclass_node_after = pclass_node_after -> next;
            }

            if (pclass_node_cur != pclass_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pclass_node_temp = *pclass_node_prior;
                *pclass_node_prior = *pclass_node_cur;
                pclass_node_prior -> next = pclass_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pclass_node_temp -> next = pclass_node_cur -> next;
                *pclass_node_cur = *pclass_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pclass_node_prior = pclass_node_prior -> next;
        }
    }

    return pclass_head;
}

/**
 * ��������: SeekClassNodeM
 * ��������: �����ְ༶���Ʋ��Ұ༶��Ϣ��㣬�����༶��������.
 * �������: hd �༶��ͷָ��
 *           class_namem ���ְ༶����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��: ���ݰ༶��������ȷ����ֲ��Ϣ
 */
CLASS_NODE *SeekClassNodeM(CLASS_NODE *hd, char *class_namem)
{
    CLASS_NODE *pclass_head;/*�������ͷָ��*/
    CLASS_NODE *pclass_temp;
    CLASS_NODE *pclass_node;

    pclass_head = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
    pclass_head = NULL;
    pclass_temp = NULL;
    pclass_node = hd;

    //��������
    CLASS_NODE *pclass_node_prior;
    CLASS_NODE *pclass_node_after;
    CLASS_NODE *pclass_node_cur;
    CLASS_NODE *pclass_node_temp;

    while (pclass_node != NULL){
        if ( (strstr (pclass_node -> class_name, class_namem) ) != NULL){/*�����������*/
            pclass_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
            *pclass_temp = *pclass_node;
            pclass_temp -> next = pclass_head;
            pclass_head = pclass_temp;
        }
        pclass_node = pclass_node -> next;
    }

    //���ɹ������������ ���༶���ƶ�������
    if(pclass_head){
        pclass_node_prior = pclass_head;
        pclass_node_temp = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));/*���ڽ���������ʱ���*/

        while (pclass_node_prior -> next != NULL){/*ѡ������*/
            pclass_node_cur = pclass_node_prior;
            pclass_node_after = pclass_node_prior -> next;
            while (pclass_node_after != NULL){/*cur��(��С)�γ����Ƶ�ַ*/
                if (strcmp (pclass_node_cur -> class_name, pclass_node_after -> class_name) > 0){
                    pclass_node_cur = pclass_node_after;
                }
                pclass_node_after = pclass_node_after -> next;
            }

            if (pclass_node_cur != pclass_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pclass_node_temp = *pclass_node_prior;
                *pclass_node_prior = *pclass_node_cur;
                pclass_node_prior -> next = pclass_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pclass_node_temp -> next = pclass_node_cur -> next;
                *pclass_node_cur = *pclass_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pclass_node_prior = pclass_node_prior -> next;
        }
    }

    return pclass_head;
}

/**
 * ��������: SeekCourseNode
 * ��������: ���γ�������ַ����ʦ��������ʼ�ܴβ��ҿ�����Ϣ���.
 * �������: hd ������ͷָ��
 *           subject_name �γ�����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
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

    if (find){  /*����ҵ�*/
        return pcourse_node;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekCourseNode_S
 * ��������: ����γ����µĿ�������.
 * �������: hd �γ��¸����Ŀ�����ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekCourseNode_S(COURSE_NODE *hd)
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){//���ƽ������

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//���ƽ��ֵ
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        pcourse_node=pcourse_node->scnext;
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)��ʦ���Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> teacher_name, pcourse_node_after -> teacher_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekCourseNode_R
 * ��������: ����������µĿ�������.
 * �������: hd ���ҽ���¸����Ŀ�����ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekCourseNode_R(COURSE_NODE *hd)//����������µĿ�������
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){//���ƽ������

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//���ƽ��ֵ
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        pcourse_node=pcourse_node->rcnext;
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)��ʦ���Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekCourseNode_T
 * ��������: �����ʦ���µĿ�������.
 * �������: hd ��ʦ����¸����Ŀ�����ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekCourseNode_T(COURSE_NODE *hd)//�����ʦ���µĿ�������
{
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){//���ƽ������

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//���ƽ��ֵ
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        pcourse_node=pcourse_node->tcnext;
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)��ʦ���Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekCourseNode_C
 * ��������: ����༶���µĿ�������.
 * �������: hd �༶����¸����Ŀ�����ͷָ��
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
COURSE_NODE *SeekCourseNode_C(COURSE_NODE *hd,char* class_name)//����༶���µĿ�������
{
    int class_i;
    COURSE_NODE *pcourse_head=NULL;
    COURSE_NODE *pcourse_temp=NULL;
    COURSE_NODE *pcourse_node=NULL;

    //��������
    COURSE_NODE *pcourse_node_prior;
    COURSE_NODE *pcourse_node_after;
    COURSE_NODE *pcourse_node_cur;
    COURSE_NODE *pcourse_node_temp;

    pcourse_node=hd;//node���ڱ���������

    while(pcourse_node !=NULL){//���ƽ������

        pcourse_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));
        *pcourse_temp = *pcourse_node;//���ƽ��ֵ
        pcourse_temp->next=pcourse_head;
        pcourse_head=pcourse_temp;

        class_i=return_i(pcourse_node,class_name);
        pcourse_node=pcourse_node->ccnext[class_i];
    }

    //���ɹ������������ ��������
    if(pcourse_head){
        pcourse_node_prior = pcourse_head;
        pcourse_node_temp = (COURSE_NODE *)malloc(sizeof(COURSE_NODE));/*���ڽ���������ʱ���*/

        while (pcourse_node_prior -> next != NULL){/*ѡ������*/
            pcourse_node_cur = pcourse_node_prior;
            pcourse_node_after = pcourse_node_prior -> next;
            while (pcourse_node_after != NULL){/*cur��(��С)��ʦ���Ƶ�ַ*/
                if (strcmp (pcourse_node_cur -> subject_name, pcourse_node_after -> subject_name) > 0){
                    pcourse_node_cur = pcourse_node_after;
                }
                pcourse_node_after = pcourse_node_after -> next;
            }

            if (pcourse_node_cur != pcourse_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pcourse_node_temp = *pcourse_node_prior;
                *pcourse_node_prior = *pcourse_node_cur;
                pcourse_node_prior -> next = pcourse_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pcourse_node_temp -> next = pcourse_node_cur -> next;
                *pcourse_node_cur = *pcourse_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pcourse_node_prior = pcourse_node_prior -> next;
        }
    }

    return pcourse_head;
}

/**
 * ��������: SeekRestRoomNode
 * ��������: ����ָ��ʱ��Ŀ��н��Ҳ����ɽ������.
 * �������: hd ������ͷָ��
 *           week ����
 *           lesson ����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ������ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
 */
ROOM_NODE *SeekRestRoomNode(ROOM_NODE *hd, int week,int weekday,int lesson)//����ʱ����ҿ��н���
{
    ROOM_NODE *proom_head=NULL;//ͷָ��
    ROOM_NODE *proom_temp=NULL;//���ڹ�������
    ROOM_NODE *proom_node=hd;//���ڱ���ԭʼ����
    COURSE_NODE *pcourse_node;//���ڱ��������������Ŀ�����
    int flag=0;

    //��������
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
        if(!flag){//����ѯ����Ӧ�ս���
            proom_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
            *proom_temp = *proom_node;//���ƽ��ֵ
            proom_temp->next=proom_head;
            proom_head=proom_temp;
        }
        proom_node=proom_node->next;
    }

    //���ɹ������������ ������������
    if(proom_head){
        proom_node_prior = proom_head;
        proom_node_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));/*���ڽ���������ʱ���*/

        while (proom_node_prior -> next != NULL){/*ѡ������*/
            proom_node_cur = proom_node_prior;
            proom_node_after = proom_node_prior -> next;
            while (proom_node_after != NULL){/*cur��(��С)�������Ƶ�ַ*/
                if (strcmp (proom_node_cur -> room_name, proom_node_after -> room_name) > 0){
                    proom_node_cur = proom_node_after;
                }
                proom_node_after = proom_node_after -> next;
            }

            if (proom_node_cur != proom_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *proom_node_temp = *proom_node_prior;
                *proom_node_prior = *proom_node_cur;
                proom_node_prior -> next = proom_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                proom_node_temp -> next = proom_node_cur -> next;
                *proom_node_cur = *proom_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            proom_node_prior = proom_node_prior -> next;
        }
    }

    //����ѧ¥����
    if(proom_head){
        proom_node_prior = proom_head;
        proom_node_temp = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));/*���ڽ���������ʱ���*/

        while (proom_node_prior -> next != NULL){/*ѡ������*/
            proom_node_cur = proom_node_prior;
            proom_node_after = proom_node_prior -> next;
            while (proom_node_after != NULL){/*cur��(��С)��ѧ¥���Ƶ�ַ*/
                if (strcmp (proom_node_cur ->building, proom_node_after -> building) > 0){
                    proom_node_cur = proom_node_after;
                }
                proom_node_after = proom_node_after -> next;
            }

            if (proom_node_cur != proom_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *proom_node_temp = *proom_node_prior;
                *proom_node_prior = *proom_node_cur;
                proom_node_prior -> next = proom_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                proom_node_temp -> next = proom_node_cur -> next;
                *proom_node_cur = *proom_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            proom_node_prior = proom_node_prior -> next;
        }
    }

    return proom_head;
}








//���ļ��ж�ȡ������Ϣ
void ScanfLesson(int *c_lesson,char *lesson)
{
    int i=0;
    for(i=0;i<13;i++){
        *(c_lesson+i)=0;
    }
    i=0;
    while(*lesson!='\0'){
        if(*lesson!='.'){//��ȡ������
            i*=10;
            i+=(*lesson-'0');
        }
        if(*lesson=='.'){//��ȡ�����ּ�ļ��
            *(c_lesson+i)=1;
            i=0;
        }
        lesson++;
    }
}

//���ļ��ж�ȡ������Ϣ
void ScanfWeek(int *c_week,char *week)
{
    int i=0;
    *c_week=30;
    for(i=1;i<30;i++){
        *(c_week+i)=0;
    }
    i=0;
    while(*week!='\0'){
        if(*week!='.'){//��ȡ������
            i*=10;
            i+=(*week-'0');
        }
        if(*week=='.'){//��ȡ�����ּ�ļ��
            *(c_week+i)=1;
            if(i<(*c_week)){
                *c_week=i;//������ʼ�ܴ�
            }
            i=0;
        }
        week++;
    }
}

//�ڿ��ý����ͨ���������ƶ�λָ�������е�ָ��
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

