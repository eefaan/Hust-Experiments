#include "vegetable.h"

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
    RunSys(&gp_head);             /*ϵͳ����ģ���ѡ������*/
    CloseSys(gp_head);            /*�˳�ϵͳ*/

    return 0;
}

/**
 * ��������: LoadData
 * ��������: ������������������ݴ������ļ����뵽�ڴ滺������ʮ��������.
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
    Re = CreatList(&gp_head);
    gc_sys_state |= Re;
    gc_sys_state &= ~(4 + 8 + 16 - Re);
    if (gc_sys_state < ( 4 | 8 | 16))
    {  /*���ݼ�����ʾ��Ϣ*/
        printf("\nϵͳ�������ݲ�����!\n");
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
 *           0  ����, ������
 *           4  �Ѽ����߲˷�����Ϣ���ݣ����߲˻�����Ϣ�Ͳ�ũ��ֲ��Ϣ����
 *           12 �Ѽ����߲˷�����Ϣ���߲˻�����Ϣ���ݣ��޲�ũ��ֲ��Ϣ����
 *           28 ����������ݶ��Ѽ���
 *
 * ����˵��:
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
        printf("�߲�������Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�߲�������Ϣ�����ļ��򿪳ɹ�!\n");

    /*�������ļ��ж��߲�������Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
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
        printf("�߲�������Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("�߲�������Ϣ�����ļ����سɹ�!\n������%d���߲�������Ϣ\n",speciesNum);
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_vege_info_filename, "rb")) == NULL)
    {
        printf("�߲˻�����Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�߲˻�����Ϣ�����ļ��򿪳ɹ�!\n");
    re += 8;

    /*�������ļ��ж�ȡ�߲˻�����Ϣ���ݣ�����������Ӧ�����߲˻�����Ϣ֧����*/
    while (fread(&tmp2, sizeof(VEGE_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж������߲˻�����Ϣ*/
        pVegeNode = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
        *pVegeNode = tmp2;
        pVegeNode->vege_id = ++VegeCount; /*�����߲˱��*/
        pVegeNode->pnext = NULL;

        /*�������ϲ��Ҹ��߲����������Ӧ���������*/
        pSpeciesNode = hd;
        while (pSpeciesNode != NULL
               && strcmp(pSpeciesNode->species_id, pVegeNode->species_id) != 0)
        {
            pSpeciesNode = pSpeciesNode->next;
        }
        if (pSpeciesNode != NULL) /*����ҵ����򽫽���Ժ���ȳ���ʽ�����߲���Ϣ֧��*/
        {
            pVegeNode->next = pSpeciesNode->vnext;
            pSpeciesNode->vnext = pVegeNode;
            vegeNum++;
        }
        else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pVegeNode);
        }
    }
    fclose(pFile);
    printf("������%d���߲˻�����Ϣ\n",vegeNum);

    if ((pFile = fopen(gp_plant_info_filename, "rb")) == NULL)
    {
        printf("��ũ��ֲ��Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("��ũ��ֲ��Ϣ�����ļ��򿪳ɹ�!\n");
    re += 16;

    /*�������ļ��ж�ȡ��ũ��ֲ��Ϣ���ݣ������߲˻�����Ϣ֧����Ӧ������ֲ֧����*/
    while (fread(&tmp3, sizeof(PLANT_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж����Ĳ�ũ��ֲ��Ϣ*/
        pPlantNode = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        *pPlantNode = tmp3;
        pPlantNode -> plant_id = ++PlantCount; /*������ũ���*/

        /*�����߲���Ϣ֧���϶�Ӧ��ֲ��Ϣ���*/
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
        if (find)  /*����ҵ����򽫽���Ժ���ȳ���ʽ�����ũ��ֲ��Ϣ֧����*/
        {
            pPlantNode->next = pVegeNode->pnext;
            pVegeNode->pnext = pPlantNode;
            plantNum++;
        }
        else /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);
    printf("������%d����ũ��ֲ��Ϣ\n",plantNum);
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
    //system("color F0\n");/*�׵׺���*/
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*��ɫǰ������ɫ����*/

    SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

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
void CloseSys(SPECIES_NODE *hd)
{
    SPECIES_NODE *pSpeciesNode1 = hd, *pSpeciesNode2;
    VEGE_NODE *pVegeNode1, *pVegeNode2;
    PLANT_NODE *pPlantNode1, *pPlantNode2;

    while (pSpeciesNode1 != NULL) /*�ͷ�ʮ�ֽ�������Ķ�̬�洢��*/
    {
        pSpeciesNode2 = pSpeciesNode1->next;
        pVegeNode1 = pSpeciesNode1->vnext;
        while (pVegeNode1 != NULL) /*�ͷ��߲˻�����Ϣ֧���Ķ�̬�洢��*/
        {
            pVegeNode2 = pVegeNode1->next;
            pPlantNode1 = pVegeNode1->pnext;
            while (pPlantNode1 != NULL) /*�ͷ���ֲ��Ϣ֧���Ķ�̬�洢��*/
            {
                pPlantNode2 = pPlantNode1->next;
                free(pPlantNode1);
                pPlantNode1 = pPlantNode2;
            }
            free(pVegeNode1);
            pVegeNode1 = pVegeNode2;
        }
        free(pSpeciesNode1);  /*�ͷ��������Ķ�̬�洢��*/
        pSpeciesNode1 = pSpeciesNode2;
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
void RunSys(SPECIES_NODE **phead)
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
 *           pHotArea ����������������Ϣ��ŵĵ�ַ
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

/**
 * ��������: showcursor
 * ��������: ��ʾ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void showcursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = TRUE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);   /*���ֹ��*/
}

/**
 * ��������: hidecursor
 * ��������: ���ع��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void hidecursor()
{
    CONSOLE_CURSOR_INFO lpCur;
    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

}

/**
 * ��������: ShowModule
 * ��������: �����˵�.
 * �������: pString �˵������ַ���
 *           n �˵�����
 * �������:
 * �� �� ֵ:
 *
 * ����˵��:
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

/**
 * ��������: ChooseModule
 * ��������: ����ѡ��˵�.
 * �������: pString �˵������ַ���
 * �������: ��
 * �� �� ֵ:
 *
 * ����˵��:
 */
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
 * ��������: SaveData
 * ��������: ִ�����ݱ���, ���߲˷�����Ϣ.�߲˻�����Ϣ.��ֲ��Ϣ��������ֱ�������������ļ���.
 * �������:
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
    SaveSysData(gp_head);   /*������Ϣ*/
    ShowModule(plabel_result, 2);

    return bRet;
}

/**
 * ��������: BackupData
 * ��������: ִ�����ݱ���, ���߲˷�����Ϣ���߲˻�����Ϣ����ֲ��Ϣ����������ݱ��ݵ�һ�������ļ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[] = {"���ݳɹ����ѱ�������",
                             "D:\VegeSysBackup.dat",
                             "ȷ��"
                            };
    char *plabel_choose[] = {"ȷ�ϱ�����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    char *filename = {"D:\VegeSysBackup.dat"};  /*����·��*/

    if (ChooseModule(plabel_choose) == 0){  /*ȡ������*/
        PopOff();
        return bRet;
    }
    PopOff();
    BackupSysData(gp_head, filename);   /*������Ϣ*/
    ShowModule(plabel_result, 3);

    return bRet;
}

/**
 * ��������: RestoreData
 * ��������: ִ�����ݻָ�, ���߲˷�����Ϣ���߲˻�����Ϣ����ֲ��Ϣ����������ݻظ�����ֲ��Ϣϵͳ��.
 * �������: ��
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
    char *filename = {"D:\VegeSysBackup.dat"};  /*�����ļ�����·��*/

    if (ChooseModule(plabel_choose) == 0){  /*ȡ���ָ�*/
        PopOff();
        return bRet;
    }
    PopOff();
    RestoreSysData(&gp_head, filename);   /*�ָ���Ϣ*/
    ShowModule(plabel_result, 2);

    return bRet;
}

/**
 * ��������: ExitSys
 * ��������: �˳�ϵͳ.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
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
 * ��������: MaintainSpeciesInfo
 * ��������: ִ���߲�������Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainSpeciesInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"�߲�������Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ���Ż����������Ѵ��ڣ�","ȷ��"},
                               {"�߲�������Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�δ��ѯ����Ӧ������Ϣ��","ȷ��"},
                               {"�߲�������Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ������Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();
    scanf("%d",&chooseNum);
    fflush(stdin);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*�����߲�������Ϣ*/
        flag = InsertSpeciesNode(&gp_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸��߲�������Ϣ*/
        flag = ModifSpeciesNode(gp_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ���߲�������Ϣ*/
        flag = DelSpeciesNode(&gp_head);
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
 * ��������: MaintainVegeInfo
 * ��������: ִ���߲˻�����Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainVegeInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"�߲˻�����Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ�","ȷ��"},
                               {"�߲˻�����Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�δ��ѯ����Ӧ�߲���Ϣ��","ȷ��"},
                               {"�߲˻�����Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ�߲���Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();/*��ʾ���*/
    scanf("%d",&chooseNum);
    fflush(stdin);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*�����߲˻�����Ϣ*/
        flag = InsertVegeNode(gp_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸��߲˻�����Ϣ*/
        flag = ModifVegeNode(gp_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ���߲˻�����Ϣ*/
        flag = DelVegeNode(gp_head);
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
 * ��������: MaintainPlantInfo
 * ��������: ִ�в�ũ��ֲ��Ϣά���Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL MaintainPlantInfo(void)
{
    BOOL bRet = TRUE;
    int chooseNum=0;
    int flag=0;
    char *plabel_result[7][2]={{"��ũ��ֲ��Ϣ��ӳɹ���","ȷ��"},
                               {"����ʧ�ܣ�","ȷ��"},
                               {"��ũ��ֲ��Ϣ�޸ĳɹ���","ȷ��"},
                               {"�޸�ʧ�ܣ�δ��ѯ����Ӧ��ֲ��Ϣ��","ȷ��"},
                               {"��ũ��ֲ��Ϣɾ���ɹ���","ȷ��"},
                               {"����ʧ�ܣ�δ��ѯ����Ӧ��ֲ��Ϣ��","ȷ��"},
                               {"��Чָ��ص����˵���","ȷ��"}
                              };
    printf("\n  ��ͨ����������ѡ������Ҫ���еĲ���\n     1 : �����Ϣ\n     2 : �޸���Ϣ\n     3 : ɾ����Ϣ\n\n  �������֣�");

    showcursor();  /*���ֹ��*/
    scanf("%d",&chooseNum);
    fflush(stdin);
    ClearScreen();
    ShowMenu();

    if (chooseNum == 1){    /*�����ũ��ֲ��Ϣ*/
        flag = InsertPlantNode(gp_head);
        if(flag){   /*����ɹ�*/
            ShowModule(*plabel_result, 2);
        }
        else{   /*����ʧ��*/
            ShowModule(*(plabel_result+1), 2);
        }
    }

    else if (chooseNum == 2){   /*�޸Ĳ�ũ��ֲ��Ϣ*/
        flag = ModifPlantNode(gp_head);
        if(flag == 1){   /*�޸ĳɹ�*/
            ShowModule(*(plabel_result+2),2);
        }
        else if(flag == 2){ /*ȡ���޸�*/;}
        else{   /*�޸�ʧ��*/
            ShowModule(*(plabel_result+3),2);
        }
    }

    else if (chooseNum == 3){   /*ɾ����ũ��ֲ��Ϣ*/
        flag = DelPlantNode(gp_head);
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
 * ��������: QuerySpeciesInfo
 * ��������: ִ���߲˷�����Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QuerySpeciesInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char species_id[6];
    SPECIES_NODE *pspecies_node;
    pspecies_node = NULL;

    showcursor();/*��ʾ���*/
    printf("\n  ��ģ�齫ͨ�������Ų�ѯ������Ϣ\n");
    printf("\n  ����������ţ�");
    scanf("%[^\n]", species_id);
    getchar();
    hidecursor();/*���ع��*/

    pspecies_node = SeekSpeciesNode(gp_head, species_id);

    if(pspecies_node != NULL){/*����ҵ�*/
        printf ("\n  ��ѯ���ķ�����Ϣ��\n");
        printf ("    �����ţ�%s\n", pspecies_node -> species_id);
        printf ("    �������ƣ�%s\n", pspecies_node -> species_name);
        ShowModule(*plabel_result, 2);
    }
    else{/*���δ�ҵ�*/
        printf ("\n  δ��ѯ����Ӧ������Ϣ��\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryVegeInfo
 * ��������: ִ���߲˻�����Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryVegeInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char species_id[6];
    char vege_nutrim[100];
    char vege_namem[20];
    SPECIES_NODE *pspecies_node;/*�������ݷ����Ų��ҷ�������*/
    VEGE_NODE *pvege_node;/*�������*/
    pvege_node = NULL;
    int ChooseNum = 0;

    showcursor();/*��ʾ���*/

    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1 : ͨ���߲˲������Ʋ���\n");
    printf("    2 : ͨ��������Ͳ���Ӫ���ɷֲ���\n");
    printf("\n  ��������֣�");
    scanf("%d", &ChooseNum);
    fflush(stdin);

    if (ChooseNum == 1){
        printf ("\n  �������߲˲������ƣ�");
        scanf ("%[^\n]", vege_namem);
        getchar();
        pvege_node = SeekVegeNodeM1(gp_head, vege_namem);/*���Ҳ������������*/
    }
    else if (ChooseNum == 2){
        printf ("\n  �����������룺");
        scanf ("%[^\n]", species_id);
        getchar();
        printf ("\n  �������߲���������Ӫ���ɷ֣�");
        scanf ("%[^\n]", vege_nutrim);
        getchar();
        pvege_node = SeekVegeNodeM2(gp_head, species_id, vege_nutrim);/*���Ҳ������������*/
    }
    else{
        printf ("\n  ������������\n");
        printf("\n  ��������������˵�...\n");
        hidecursor();/*���ع��*/
        getch();
        ClearScreen();
        ShowMenu();

        return bRet;
    }

    hidecursor();/*���ع��*/

    if(pvege_node != NULL){/*����ҵ�*/
        ShowModule(*plabel_result, 2);
        printf ("\n\n  ��ѯ�����߲���Ϣ��\n");
        printf ("    �߲˱��    �߲�����    ������    ��������    Ӫ���ɷ�\n");
        for (;pvege_node != NULL; pvege_node = pvege_node -> next){
            pspecies_node = SeekSpeciesNode(gp_head, pvege_node -> species_id);
            printf("    %-10d", pvege_node -> vege_id);
            printf("  %-10s", pvege_node -> vege_name);
            printf("  %-10s", pvege_node -> species_id);
            printf("  %-10s", pspecies_node -> species_name);
            printf("  %-10s\n", pvege_node -> nutrition);
        }
    }
    else{/*���δ�ҵ�*/
        printf ("\n  δ��ѯ����Ӧ�߲���Ϣ��\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: QueryPlantInfo
 * ��������: ִ���߲���ֲ��Ϣ��ѯ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL QueryPlantInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"��ѯ���","ȷ��"},
                                  {"��ѯʧ��","ȷ��"}
                                 };
    char vege_namem[20];
    char year[5];
    char vege_name[20];
    SPECIES_NODE *pspecies_node;/*�������ݷ����Ų��ҷ�������*/
    VEGE_NODE *pvege_node;/*���������߲����Ʋ����߲���Ϣ*/
    PLANT_NODE *pplant_node;/*�������*/
    pplant_node = NULL;
    int ChooseNum = 0;

    showcursor();/*��ʾ���*/

    printf("\n  ͨ����������ѡ���ѯ��ʽ��\n");
    printf("    1 : ͨ���߲˲������ƺ���ֲ��ݲ���\n");
    printf("    2 : ͨ���߲����Ʋ��ң�����ݽ�����ʾ\n\n");
    printf("  ��������֣�");
    scanf("%d", &ChooseNum);
    fflush(stdin);

    if (ChooseNum == 1){
        printf ("\n  �������߲˲������ƣ�");
        scanf ("%[^\n]", vege_namem);
        getchar();
        printf ("\n  ��������ֲ��ݣ�");
        scanf ("%[^\n]", year);
        getchar();
        pplant_node = SeekPlantNodeM1(gp_head, vege_namem, year);/*���Ҳ������������*/
    }
    else if (ChooseNum == 2){
        printf ("\n  �������߲����ƣ�");
        scanf ("%[^\n]", vege_name);
        getchar();
        pplant_node = SeekPlantNodeM2(gp_head, vege_name);/*���Ҳ������������*/
    }
    else{
        printf ("\n  ������������\n");
        printf("\n  ��������������˵�...\n");
        hidecursor();/*���ع��*/
        getch();
        ClearScreen();
        ShowMenu();

        return bRet;
    }

    hidecursor();/*���ع��*/

    if(pplant_node != NULL){/*����ҵ�*/
        ShowModule(*plabel_result, 2);
        printf ("\n  ��ѯ�����߲���Ϣ��\n");
        printf ("    ��ֲ���    ��ũ����    ��������    �߲�����    ��ֲ���    ��ֲ���    �ջ�����\n");
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
    else{/*���δ�ҵ�*/
        printf ("\n  δ��ѯ����Ӧ�߲���Ϣ\n");
        printf ("  ����߲�����ֲ��Ϣ!\n");
        ShowModule(*(plabel_result+1),2);
    }

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}



/**����ͳ��ģ��*/

/**
 * ��������: StatAreaAndHarvest
 * ��������: ͳ��ĳ��ݸ����߲˵���ֲ��������ܲ����Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatAreaAndHarvest(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"ͳ�����","ȷ��"},
                                  {"ͳ��ʧ�ܣ��ڸ����δ��ѯ����ֲ��Ϣ","ȷ��"}
                                 };
    char year[5];
    TOTAL_NODE *ptotal_node;
    ptotal_node = NULL;

    showcursor();/*��ʾ���*/
    printf ("\n  ��ģ�齫ͨ����ֲ���ͳ�������ֲ����\n");
    printf ("\n  ��������ݣ�");
    scanf ("%[^\n]", year);
    getchar();
    hidecursor();/*���ع��*/

    ptotal_node = Stat1(gp_head, year);/*�����������*/

    if(ptotal_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  ͳ�Ƶ�����ֲ��Ϣ (��������������)��\n");
        printf ("    ��������    ��ֲ���    �ջ�����\n");
        for (;ptotal_node != NULL; ptotal_node = ptotal_node ->next){
            printf("    %-10s", ptotal_node -> species_name);
            printf("  %-10d", ptotal_node -> total_area);
            printf("  %-10f\n", ptotal_node -> total_harvest);
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
 * ��������: StatAreaAndHarvestM
 * ��������: ͳ�Ƽ����ĳ���߲˵���ֲ��������ܲ����Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatAreaAndHarvestM(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"ͳ�����","ȷ��"},
                                  {"ͳ��ʧ�ܣ��ڶ�Ӧ���δ��ѯ������ֲ��Ϣ","ȷ��"}
                                 };
    char vege_name[20];
    char year_head[5];
    char year_tail[5];
    TOTAL_NODE *ptotal_node;
    ptotal_node = NULL;

    showcursor();/*��ʾ���*/
    printf ("\n  ��ģ�齫ͨ���߲����ơ���ֹ���ͳ�������ֲ����\n");
    printf ("\n  �������߲����ƣ�");
    scanf ("%[^\n]", vege_name);
    getchar();
    printf ("\n  ��������ʼ��ֲ��ݣ�");
    scanf ("%[^\n]", year_head);
    getchar();
    printf ("\n  ��������ֹ��ֲ��ݣ�");
    scanf ("%[^\n]", year_tail);
    getchar();
    hidecursor();/*���ع��*/

    ptotal_node = Stat2(gp_head, vege_name, year_head, year_tail);/*�����������*/

    if(ptotal_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  ͳ�Ƶ�����ֲ��Ϣ��\n");
        printf ("    �߲�����    ��������    ��ֲ���    �ջ�����\n");
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

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: StatNum
 * ��������: ͳ�Ƹ����߲˷��������߲������Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatNum(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"ͳ�����","ȷ��"},
                                  {"ͳ��ʧ�ܣ�δ��ѯ���߲���Ϣ","ȷ��"}
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

    for (pspecies_node = gp_head; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*����ѭ��������������ÿ�������߲˻�����Ϣ֧��*/
        pvege_node = pspecies_node -> vnext;
        pvege_count = (VEGE_COUNT *)malloc(sizeof(VEGE_COUNT));
        pvege_count -> numcount = 0;
        strcpy(pvege_count -> species_id, pspecies_node -> species_id);
        strcpy(pvege_count -> species_name, pspecies_node -> species_name);

        while (pvege_node != NULL){/*����*/
            pvege_count -> numcount++;
            pvege_node = pvege_node -> next;
        }

        pvege_count -> next = pvege_count_head;/*����ȳ�*/
        pvege_count_head = pvege_count;
    }

    if(pvege_count_head != NULL){
        printf ("\n  ͳ�Ƶ����߲�������Ϣ��\n");
        printf ("    ������    ��������    �߲�����\n");
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

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: StatNutrition
 * ��������: ͳ�ƺ���ĳ��Ӫ���ɷֵ��߲˵���Ϣ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatNutrition(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"ͳ�����","ȷ��"},
                                  {"ͳ��ʧ�ܣ�δ��ѯ�����д�Ӫ���ɷֵ��߲���Ϣ","ȷ��"}
                                 };
    char nutrim[100];
    SPECIES_NODE *pspecies_node;/*���ڲ��ҷ�������*/
    VEGE_NODE *pvege_node;
    pvege_node = NULL;

    showcursor();/*��ʾ���*/
    printf ("\n  ��ģ�齫ͨ���߲˲���Ӫ���ɷ�ͳ������߲���Ϣ\n");
    printf ("\n  �������߲���������Ӫ���ɷ֣�");
    scanf ("%[^\n]", nutrim);
    getchar();
    hidecursor();/*���ع��*/

    pvege_node = SeekVegeNodeM3(gp_head, nutrim);/*�����������*/

    if(pvege_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  ͳ�Ƶ����߲���Ϣ��\n");
        printf ("    �߲�����    ��������    Ӫ���ɷ�\n");
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

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**
 * ��������: StatPlant
 * ��������: ͳ��ĳ��ũ��������ֲ��Ϣ�Ĺ��ܺ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL StatPlant(void)
{
    BOOL bRet = TRUE;
    char *plabel_result[2][20] = {{"ͳ�����","ȷ��"},
                                  {"ͳ��ʧ�ܣ�δ��ѯ���ò�ũ����ֲ��Ϣ","ȷ��"}
                                 };
    char plant_name[20];
    SPECIES_NODE *pspecies_node;/*���ڲ��ҷ�������*/
    VEGE_NODE *pvege_node;/*���ڲ����߲���Ϣ*/
    PLANT_NODE *pplant_node;
    pplant_node = NULL;

    showcursor();/*��ʾ���*/
    printf ("\n  ��ģ�齫ͨ����ũ����ͳ�������ֲ��Ϣ\n");
    printf ("\n  �������ũ������");
    scanf ("%[^\n]", plant_name);
    getchar();
    hidecursor();/*���ع��*/

    pplant_node = SeekPlantNodeM3(gp_head, plant_name);/*�����������*/

    if(pplant_node != NULL){
        ShowModule(*plabel_result, 2);
        printf ("\n  ͳ�Ƶ�����ֲ��Ϣ��\n");
        printf ("    ��ũ����    �߲�����    ��������    ��ֲ���    ��ֲ���    �ջ�����\n");
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

    printf("\n\n  ��������������˵�...\n");
    getch();
    ClearScreen();
    ShowMenu();

    return bRet;
}

/**����ģ��*/

/**
 * ��������: HelpTopic
 * ��������: ��ʾ������Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ:
 *
 * ����˵��:
 */
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"�����ݵ�λ�����(��)      ",
                           "            �ճ�(����)    ",
                           "��ϵͳ֧����������        ",
                           "��ϵͳ֧�ֺ��ո��ַ�������",
                           "��ALT+��ĸ�ɿ��ѡ��˵�  ",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 6);
    return bRet;
}

/**
 * ��������: AboutVegeSys
 * ��������: ��ʾ������Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ:
 *
 * ����˵��:
 */
BOOL AboutVegeSys(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"��������Ϣ: ",
                           "������ũ��ֲ��Ϣ����ϵͳ��",
                           "  ���пƼ���ѧ  �����ѧԺ",
                           "  У�ʽ�����  ���ݷ�  ����",
                           "������: lyf460315457@qq.com",
                           "ȷ��"
                          };
    ShowModule(plabel_name, 6);
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
BOOL SaveSysData(SPECIES_NODE *hd)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    FILE *pfout;

    pfout = fopen(gp_species_info_filename, "wb");
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node->next){/*�����߲�������Ϣ*/
        fwrite(pspecies_node, sizeof(SPECIES_NODE), 1, pfout);
    }
    fclose(pfout);

    pfout = fopen(gp_vege_info_filename, "wb");
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node->next){/*�����߲˻�����Ϣ*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            fwrite(pvege_node, sizeof(VEGE_NODE), 1, pfout);
            pvege_node = pvege_node->next;
        }
    }
    fclose(pfout);

    pfout = fopen(gp_plant_info_filename, "wb");
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node->next){/*�����ũ��ֲ��Ϣ*/
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
 * ��������: BackupSysData
 * ��������: ��ϵͳ����������������ݱ��ݵ�һ�������ļ�.
 * �������: hd ����ͷ���ָ��
 *           filename �����ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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

    /*����ʮ�������ֱ�ͳ�����ֻ�����Ϣ�ļ�¼����*/
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

    /*��������������ݵļ�¼����*/
    fwrite((void*)&species_node_num, sizeof(species_node_num), 1, fp);
    fwrite((void*)&vege_node_num, sizeof(vege_node_num), 1, fp);
    fwrite((void*)&plant_node_num, sizeof(plant_node_num), 1, fp);

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){  /*�����߲˷�����Ϣ*/
        fwrite((void*)pspecies_node, sizeof(SPECIES_NODE), 1, fp);
    }
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){  /*�����߲˻�����Ϣ*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            fwrite((void*)pvege_node, sizeof(VEGE_NODE), 1, fp);
            pvege_node = pvege_node -> next;
        }
    }
    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){  /*���ݲ�ũ��ֲ��Ϣ*/
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
 * ��������: RestoreSysData
 * ��������: ��ָ�������ļ��лָ������������.
 * �������: phead ����ͷ���ָ��ĵ�ַ
 *           filename ��ű������ݵ������ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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

    /*��ȡ���ֻ�����Ϣ�ļ�¼��*/
    read(handle, (char*)&species_node_num, sizeof(species_node_num));
    read(handle, (char*)&vege_node_num, sizeof(vege_node_num));
    read(handle, (char*)&plant_node_num, sizeof(plant_node_num));

    /*��ȡ�߲�������Ϣ������ʮ��������*/
    for (ulloop = 1; ulloop <= species_node_num; ulloop++){
        pspecies_node = (SPECIES_NODE *)malloc(sizeof(SPECIES_NODE));
        read(handle, (char*)pspecies_node, sizeof(SPECIES_NODE));
        pspecies_node -> vnext = NULL;
        pspecies_node -> next = hd;
        hd = pspecies_node;
    }
    *phead = hd;

    /*��ȡ�߲˻�����Ϣ�������߲���Ϣ֧��*/
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

    /*��ȡ��ũ��ֲ��Ϣ��������ֲ��Ϣ֧��*/
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
    SaveSysData(hd);    /*���ڴ��е����ݱ��浽�����ļ�*/
    return TRUE;
}

//����ά��
/**
 * ��������: InsertSpeciesNode
 * ��������: ��ʮ�������в���һ���߲˷�����Ϣ���.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertSpeciesNode(SPECIES_NODE **hd)
{
    SPECIES_NODE *pspecies_node, *temp;
    pspecies_node = (SPECIES_NODE *)malloc(sizeof(SPECIES_NODE));
    pspecies_node -> vnext = NULL;
    pspecies_node -> next = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  �������߲˷�����룺");
    scanf("%[^\n]", pspecies_node -> species_id);
    getchar();
    printf("\n  �������߲��������ƣ�");
    scanf("%[^\n]", pspecies_node -> species_name);
    getchar();

    hidecursor();/*���ع��*/

    temp = *hd;
    if (*hd == NULL){/*���û�������*/
        *hd = pspecies_node;
        (*hd) -> next = NULL;
        (*hd) -> vnext = NULL;
    }
    else{
        while (temp != NULL){/*�����ظ����*/
            if (strcmp(temp -> species_id, pspecies_node -> species_id) == 0 ||
                strcmp(temp -> species_name, pspecies_node -> species_name) == 0){
                return FALSE;
            }
            temp = temp -> next;
        }
        pspecies_node -> next = (*hd) -> next; /*�����½��*/
        (*hd) -> next = pspecies_node;
        pspecies_node -> vnext = NULL;
    }
    return TRUE;
}

/**
 * ��������: ModifSpeciesNode
 * ��������: ��ָ�����߲˷�����Ϣ������ݽ����޸�.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 2��ʾȡ���޸�
 *
 * ����˵��:
 */
int ModifSpeciesNode(SPECIES_NODE *hd)
{
    char species_id[6];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    SPECIES_NODE *pspecies_node;

    showcursor();/*��ʾ���*/

    printf("\n  ��������Ҫ�޸ĵ��߲�����ķ�����룺");
    scanf("%[^\n]", species_id);
    getchar();

    hidecursor();/*���ع��*/

    pspecies_node = SeekSpeciesNode(hd, species_id);   /*����ָ��������Ϣ���*/
    if (pspecies_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    �����ţ�%s\n", pspecies_node -> species_id);
        printf("    �������ƣ�%s\n", pspecies_node -> species_name);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }
        showcursor();/*��ʾ���*/
        printf("\n  �������޸ĺ�ķ������ƣ�");
        scanf("%[^\n]", pspecies_node -> species_name);
        getchar();
        hidecursor();/*���ع��*/
        return 1;
    }
    else{
        return 0;
    }
}

/**
 * ��������: DelSpeciesNode
 * ��������: ��ʮ��������ɾ��ָ�����߲˷�����Ϣ���.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��.
 *
 * ����˵��:
 */
int DelSpeciesNode(SPECIES_NODE **hd)
{
    char species_id[6];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    SPECIES_NODE *pspecies_node_prior = NULL,
                 *pspecies_node_current = *hd;

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ�����߲˷����ţ�");
    scanf("%[^\n]", species_id);
    getchar();

    hidecursor();/*���ع��*/

    while (pspecies_node_current != NULL
           && strcmp(pspecies_node_current -> species_id, species_id) != 0){
        pspecies_node_prior = pspecies_node_current;
        pspecies_node_current = pspecies_node_current -> next;
    }
    if (pspecies_node_current != NULL){  /*����ҵ�*/
        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    �����ţ�%s\n", pspecies_node_current -> species_id);
        printf("    �������ƣ�%s\n", pspecies_node_current -> species_name);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*ɾ����Ϣ*/
            if (pspecies_node_prior == NULL){   /*���λ���߲����������ϵ�һ��λ��*/
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
 * ��������: InsertVegeNode
 * ��������: ��ʮ�������в���һ���߲˻�����Ϣ���.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertVegeNode(SPECIES_NODE *hd)
{
    SPECIES_NODE *pspecies_node;
    pspecies_node = NULL;
    VEGE_NODE *pvege_node;
    VEGE_NODE *pvege_temp;
    pvege_node = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_temp = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  �������߲�����������룺");
    scanf("%[^\n]", pvege_node -> species_id);
    getchar();
    printf("\n  �������߲����ƣ�");
    scanf("%[^\n]", pvege_node -> vege_name);
    getchar();
    printf("\n  �������߲�����Ӫ���ɷ֣�");
    scanf("%[^\n]", pvege_node -> nutrition);
    getchar();

    hidecursor();/*���ع��*/

    for (pspecies_node = hd; pspecies_node != NULL ; pspecies_node = pspecies_node -> next){/*�����ظ����*/
        pvege_temp = pspecies_node -> vnext;
        while (pvege_temp != NULL){
            if (strcmp(pvege_temp -> vege_name, pvege_node -> vege_name ) == 0){
                printf("\n  ���߲˻�����Ϣ�Ѿ����ڣ�");
                return FALSE;
            }
            pvege_temp = pvege_temp -> next;
        }
    }

    pspecies_node = SeekSpeciesNode(hd, pvege_node -> species_id);/*���������϶�Ӧ������*/
    if (pspecies_node == NULL){
        printf("\n  �Ҳ�����Ӧ�߲˷��࣡");
        return FALSE;
    }

    if (pspecies_node -> vnext == NULL){/*���֧��û�н��*/
        pvege_node -> next = NULL;
        pvege_node -> pnext = NULL;
        pvege_node -> vege_id = ++VegeCount;
        pspecies_node -> vnext = pvege_node;
    }
    else{/*֧�����н��*/
        pvege_node -> next = pspecies_node -> vnext;
        pspecies_node -> vnext = pvege_node;
        pvege_node -> pnext = NULL;
        pvege_node -> vege_id = ++VegeCount;
    }

    return TRUE;
}

/**
 * ��������: ModifVegeNode
 * ��������: ��ָ�����߲˻�����Ϣ������ݽ����޸�.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 2��ʾȡ���޸�
 *
 * ����˵��:
 */
int ModifVegeNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    VEGE_NODE *pvege_node;

    showcursor();/*��ʾ���*/
    printf("\n  �������߲������Խ����޸ģ�");
    scanf("%[^\n]", vege_name);
    getchar();
    hidecursor();/*���ع��*/

    pvege_node = SeekVegeNode(hd, vege_name);   /*����ָ���߲���Ϣ���*/
    if (pvege_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    �߲����ƣ�%s\n", pvege_node -> vege_name);
        printf("    Ӫ���ɷ֣�%s\n", pvege_node -> nutrition);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }

        showcursor();/*��ʾ���*/

        printf("\n  �������޸ĺ��Ӫ���ɷ֣�");
        scanf("%[^\n]", pvege_node -> nutrition);
        getchar();

        hidecursor();/*���ع��*/
        return 1;
    }
    else{
        return 0;
    }
    return FALSE;
}

/**
 * ��������: DelVegeNode
 * ��������: ��ʮ��������ɾ��ָ�����߲˻�����Ϣ���.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��
 *
 * ����˵��:
 */
int DelVegeNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node_prior,
              *pvege_node_current;
    pvege_node_current = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ�����߲����ƣ�");
    scanf("%[^\n]", vege_name);
    getchar();

    hidecursor();/*���ع��*/

    pvege_node_current = SeekVegeNode(hd, vege_name);

    if (pvege_node_current != NULL){/*����ҵ�*/
        pspecies_node = SeekSpeciesNode(hd, pvege_node_current -> species_id);/*��ʮ�����в��Ҹ��߲�����������*/
        pvege_node_prior = NULL;
        pvege_node_current = pspecies_node -> vnext;
        while (pvege_node_current != NULL
               && strcmp(pvege_node_current -> vege_name, vege_name) != 0){/*֧���ϲ��Ҹ��߲˽��*/
            pvege_node_prior = pvege_node_current;
            pvege_node_current = pvege_node_current -> next;
        }

        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    �����ţ�%s\n", pvege_node_current -> species_id);
        printf("    �߲����ƣ�%s\n", pvege_node_current -> vege_name);
        printf("    Ӫ���ɷ֣�%s\n", pvege_node_current -> nutrition);

        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*ɾ����Ϣ*/
        if (pvege_node_prior == NULL){   /*���λ���߲˻�����Ϣ֧���ϵ�һ��λ��*/
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
 * ��������: InsertPlantNode
 * ��������: ��ʮ�������в���һ����ֲ��Ϣ���.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE��ʾ����ɹ�, FALSE��ʾ����ʧ��
 *
 * ����˵��:
 */
BOOL InsertPlantNode(SPECIES_NODE *hd)
{
    VEGE_NODE *pvege_node;
    pvege_node = NULL;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_temp;
    pplant_node = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
    pplant_temp = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  �������߲����ƣ�");
    scanf("%[^\n]", pplant_node -> vege_name);
    getchar();
    printf("\n  �������ũ������");
    scanf("%[^\n]", pplant_node -> plant_name);
    getchar();
    printf("\n  ��������ֲ��ݣ�");
    scanf("%[^\n]", pplant_node -> year);
    getchar();
    printf("\n  ��������ֲ�����");
    scanf("%d", &pplant_node -> area);
    fflush(stdin);
    printf("\n  �������ջ�������");
    scanf("%f", &pplant_node -> harvest);
    getchar();

    hidecursor();/*���ع��*/

    pvege_node = SeekVegeNode(hd, pplant_node -> vege_name);/*���Ҷ�Ӧ�߲���Ϣ���*/
    if (pvege_node == NULL){
        printf("\n  �Ҳ�����Ӧ�߲���Ϣ��");
        return FALSE;
    }

    pplant_temp = pvege_node -> pnext;
    while (pplant_temp != NULL){/*�����ظ����*/
        if (strcmp(pplant_temp -> plant_name, pplant_node -> plant_name) == 0
            && strcmp(pplant_temp -> year, pplant_node -> year) == 0){
            printf("\n  ����ֲ��Ϣ�Ѿ����ڣ�");
            return FALSE;
        }
        pplant_temp = pplant_temp -> next;
    }

    if (pvege_node -> pnext == NULL){/*���֧��û�н��*/
        pplant_node -> next = NULL;
        pplant_node -> plant_id = ++PlantCount;
        pvege_node -> pnext = pplant_node;
    }
    else{/*֧�����н��*/
        pplant_node -> next = pvege_node -> pnext;
        pvege_node -> pnext = pplant_node;
        pplant_node -> plant_id = ++PlantCount;
    }

    return TRUE;
}

/**
 * ��������: ModifPlantNode
 * ��������: ��ָ������ֲ��Ϣ������ݽ����޸�.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾ�޸�ʧ��, 1��ʾ�޸ĳɹ�, 2��ʾȡ���޸�
 *
 * ����˵��:
 */
int ModifPlantNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char plant_name[20];
    char year[5];
    char *plabel_choose[] = {"ȷ���޸���Ϣ��",
                             "ȷ��    ȡ��"
                            };
    PLANT_NODE *pplant_node;

    showcursor();/*��ʾ���*/

    printf("\n  �������߲������Խ����޸ģ�");
    scanf("%[^\n]", vege_name);
    getchar();
    printf("\n  �������ũ�����Խ����޸ģ�");
    scanf("%[^\n]", plant_name);
    getchar();
    printf("\n  ��������ֲ����Խ����޸ģ�");
    scanf("%[^\n]", year);
    getchar();

    hidecursor();/*���ع��*/

    pplant_node = SeekPlantNode(hd, vege_name, plant_name, year);   /*����ָ����ֲ��Ϣ���*/
    if (pplant_node != NULL){    /*����ҵ�*/
        printf("\n  ��Ҫ�޸ĵ���Ϣ��\n");
        printf("    �߲����ƣ�%s\n", pplant_node -> vege_name);
        printf("    ��ũ������%s\n", pplant_node -> plant_name);
        printf("    ��ֲ��ݣ�%s\n", pplant_node -> year);
        printf("    ��ֲ�����%d\n", pplant_node -> area);
        printf("    �ջ�������%f\n", pplant_node -> harvest);
        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ��޸�*/
            return 2;  /*ȡ���޸�*/
        }
        showcursor();/*��ʾ���*/
        printf("\n  �������޸ĺ����ֲ�����");
        scanf("%d", &pplant_node -> area);
        fflush(stdin);
        printf("\n  �������޸ĺ���ջ�������");
        scanf("%f", &pplant_node -> harvest);
        getchar();
        hidecursor();/*���ع��*/
        return 1;
    }
    else{
        return 0;
    }
    return FALSE;
}

/**
 * ��������: DelPlantNode
 * ��������: ��ʮ��������ɾ��ָ���Ĳ�ũ��ֲ��Ϣ���.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: int����, 0��ʾɾ��ʧ��, 1��ʾɾ���ɹ�, 2��ʾȡ��ɾ��
 *
 * ����˵��: �����߲����ơ���ũ��������ֲ��ݿ���ȷ��Ψһ�Ĳ�ũ��ֲ��Ϣ
 */
int DelPlantNode(SPECIES_NODE *hd)
{
    char vege_name[20];
    char plant_name[20];
    char year[5];
    char *plabel_choose[] = {"ȷ��ɾ����Ϣ��",
                             "ȷ��    ȡ��"
                            };
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node_prior,
               *pplant_node_current;
    pplant_node_current = NULL;

    showcursor();/*��ʾ���*/

    printf("\n  ������Ҫɾ�����߲����ƣ�");
    scanf("%[^\n]", vege_name);
    getchar();
    printf("\n  �������ũ��������ȷ����ֲ��Ϣ��");
    scanf("%[^\n]", plant_name);
    getchar();
    printf("\n  ��������ֲ�����ȷ����ֲ��Ϣ��");
    scanf("%[^\n]", year);
    getchar();

    hidecursor();/*���ع��*/

    pplant_node_current = SeekPlantNode(hd, vege_name, plant_name, year);

    if (pplant_node_current != NULL){/*����ҵ�*/
        pvege_node = SeekVegeNode(hd, pplant_node_current -> vege_name);/*��ʮ�����в��Ҹ���ֲ��Ϣ�����߲˽��*/
        pplant_node_prior = NULL;
        pplant_node_current = pvege_node -> pnext;
        while (pplant_node_current != NULL
               && strcmp(pplant_node_current -> plant_name, plant_name) != 0){/*֧���ϲ��Ҹ���ֲ���*/
            pplant_node_prior = pplant_node_current;
            pplant_node_current = pplant_node_current -> next;
        }

        printf("\n  ��Ҫɾ������Ϣ��\n");
        printf("    �߲����ƣ�%s\n", pplant_node_current -> vege_name);
        printf("    ��ũ������%s\n", pplant_node_current -> plant_name);
        printf("    ��ֲ��ݣ�%s\n", pplant_node_current -> year);
        printf("    ��ֲ�����%d\n", pplant_node_current -> area);
        printf("    �ջ�������%f\n", pplant_node_current -> harvest);

        if(!ChooseModule(plabel_choose)){   /*ȷ����Ϣ�������Ƿ�ɾ��*/
            return 2;  /*ȡ��ɾ��*/
        }
        else{   /*ɾ����Ϣ*/
        if (pplant_node_prior == NULL){   /*���λ����ֲ��Ϣ֧���ϵ�һ��λ��*/
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

//���ݲ�ѯ
/**
 * ��������: SeekSpeciesNode
 * ��������: �������������߲�������Ϣ���.
 * �������: hd ����ͷָ��
 *           species_id �������
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��:
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

    if (find){  /*����ҵ�*/
        return pspecies_node;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekVegeNode
 * ��������: ���߲����Ʋ����߲˻�����Ϣ���.
 * �������: hd ����ͷָ��
 *           vege_name �߲�����
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ�����򷵻�NULL
 *
 * ����˵��:
 */
VEGE_NODE *SeekVegeNode (SPECIES_NODE *hd, char *vege_name)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    int find = 0;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*����ѭ��������������ÿ�������߲˻�����Ϣ֧��*/
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
 * ��������: SeekVegeNodeM1
 * ��������: ���߲����������Ӵ���ѯ���������������߲˻�����Ϣ���.
 * �������: hd ����ͷָ��
 *           vege_namem �߲��������ִ�
 * �������: ��
 * �� �� ֵ: ���������������Ľ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��:
 */
VEGE_NODE *SeekVegeNodeM1 (SPECIES_NODE *hd, char *vege_namem)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node_head;/*�������ͷָ��*/
    VEGE_NODE *pvege_node_temp;
    VEGE_NODE *pvege_node;

    pvege_node_head = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_node_head = NULL;
    pvege_node_temp = NULL;
    pvege_node = NULL;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*����ѭ�������߲˽��*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            if ( (strstr (pvege_node -> vege_name, vege_namem) ) != NULL){/*�����������*/
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
 * ��������: SeekVegeNodeM2
 * ��������: ���������Ӫ���ɷ���ϲ�ѯ���������������߲˻�����Ϣ���.
 * �������: hd ����ͷָ��
 *           species_id �߲˷�����
 *           vege_nutrim �߲�Ӫ���ɷ��Ӵ�
 * �������: ��
 * �� �� ֵ: ���������������Ľ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��:
 */
VEGE_NODE *SeekVegeNodeM2 (SPECIES_NODE *hd, char *species_id, char *vege_nutrim)
{
    SPECIES_NODE *pspecies_node = hd;
    VEGE_NODE *pvege_node_head;/*�������ͷָ��*/
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

    if (find){  /*����ҵ��߲�����*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){/*�����߲˽��*/
            if ( (strstr (pvege_node -> nutrition , vege_nutrim) ) != NULL){/*�����������*/
                pvege_node_temp = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
                *pvege_node_temp = *pvege_node;
                pvege_node_temp -> next = pvege_node_head;
                pvege_node_head = pvege_node_temp;
            }
            pvege_node = pvege_node -> next;
        }
        return pvege_node_head;
    }
    else{   /*���δ�ҵ�*/
        return NULL;
    }
}

/**
 * ��������: SeekVegeNodeM3
 * ��������: ���߲���������Ӫ���ɷֲ�ѯ���������������߲˻�����Ϣ���.
 * �������: hd ����ͷָ��
 *           nutrim �߲˲���Ӫ���ɷ�
 * �������: ��
 * �� �� ֵ: ���������������Ľ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��:
 */
VEGE_NODE *SeekVegeNodeM3 (SPECIES_NODE *hd, char *nutrim)
{
    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node_head;/*�������ͷָ��*/
    VEGE_NODE *pvege_node_temp;
    VEGE_NODE *pvege_node;

    pvege_node_head = (VEGE_NODE *)malloc(sizeof(VEGE_NODE));
    pvege_node_head = NULL;
    pvege_node_temp = NULL;
    pvege_node = NULL;

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*����ѭ�������߲˽��*/
        pvege_node = pspecies_node -> vnext;
        while (pvege_node != NULL){
            if ( (strstr (pvege_node -> nutrition, nutrim) ) != NULL){/*�����������*/
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
 * ��������: SeekPlantNode
 * ��������: ���߲����ơ���ũ��������ֲ��ݲ�����ֲ��Ϣ���.
 * �������: hd ����ͷָ��
 *           vege_name �߲�����
 *           plant_name ��ũ����
 *           year ��ֲ���
 * �������: ��
 * �� �� ֵ: ����ʱ���ؽ��ĵ�ַ, ���򷵻�NULL
 *
 * ����˵��: �����߲����ơ���ũ��������ֲ��ݿ���ȷ��Ψһ��ֲ��Ϣ
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

    pvege_node = SeekVegeNode(hd, vege_name);/*���Ҷ�Ӧ�߲˻�����Ϣ���*/

    /*����ҵ���������ֲ��Ϣ֧���ϼ�������ָ����ֲ��Ϣ���*/
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
 * ��������: SeekPlantNodeM1
 * ��������: ���߲˲������ƺ���ֲ��ݲ���������ֲ��Ϣ���.
 * �������: hd ����ͷָ��
 *           vege_namem �߲˲�������
 *           year ��ֲ���
 * �������: ��
 * �� �� ֵ: ���������������Ľ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��:
 */
PLANT_NODE *SeekPlantNodeM1(SPECIES_NODE *hd, char *vege_namem, char *year)
{
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    PLANT_NODE *pplant_node_head;    /*������׽��*/
    PLANT_NODE *pplant_node_temp;
    pvege_node = NULL;
    pplant_node = NULL;
    pplant_node_temp = NULL;
    int find = 0;

    pvege_node = SeekVegeNodeM1(hd, vege_namem);/*���Ҷ�Ӧ�߲˻�����Ϣ���*/

    /*����ҵ��������߲����ƽ�������ϼ�������ָ����ֲ��Ϣ���*/
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
 * ��������: SeekPlantNodeM2
 * ��������: ���߲����Ʋ�����ֲ��Ϣ���, ������ֲ��Ϣ��㰴��ֲ�������.
 * �������: hd ����ͷָ��
 *           vege_name �߲�����
 * �������: ��
 * �� �� ֵ: ���������������Ľ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��:
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
    if (pvege_node == NULL || pvege_node -> pnext == NULL){/*���δ�ҵ�*/
        return NULL;
    }

    pplant_node = pvege_node -> pnext;/*��ֲ��Ϣ��ͷָ��*/
    pplant_node_prior = pplant_node;
    pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));/*���ڽ���������ʱ���*/

    while (pplant_node_prior -> next != NULL){/*ѡ������*/
        pplant_node_cur = pplant_node_prior;
        pplant_node_after = pplant_node_prior -> next;
        while (pplant_node_after != NULL){/*cur�������ݵ�ַ*/
            if (strcmp (pplant_node_cur -> year, pplant_node_after -> year) < 0){
                pplant_node_cur = pplant_node_after;
            }
            pplant_node_after = pplant_node_after -> next;
        }

        if (pplant_node_cur != pplant_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
            *pplant_node_temp = *pplant_node_prior;
            *pplant_node_prior = *pplant_node_cur;
            pplant_node_prior -> next = pplant_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
            pplant_node_temp -> next = pplant_node_cur -> next;
            *pplant_node_cur = *pplant_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
        }
        pplant_node_prior = pplant_node_prior -> next;
    }
    free(pplant_node_temp);
    return pplant_node;
}

/**
 * ��������: SeekPlantNodeM3
 * ��������: ����ũ����������ֲ��Ϣ��㣬������ֲ�������.
 * �������: hd ����ͷָ��
 *           plant_name ��ũ����
 * �������: ��
 * �� �� ֵ: ���������������Ľ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��: ���ݲ�ũ��������ȷ����ֲ��Ϣ
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

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*����ѭ��������ֲ���*/
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
        pplant_node_prior = pplant_node_head;/*��ֲ��Ϣ��ͷָ��*/
        pplant_node_temp = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));/*���ڽ���������ʱ���*/

        while (pplant_node_prior -> next != NULL){/*ѡ������*/
            pplant_node_cur = pplant_node_prior;
            pplant_node_after = pplant_node_prior -> next;
            while (pplant_node_after != NULL){/*cur�������ݵ�ַ*/
                if (strcmp (pplant_node_cur -> year, pplant_node_after -> year) < 0){
                    pplant_node_cur = pplant_node_after;
                }
                pplant_node_after = pplant_node_after -> next;
            }

            if (pplant_node_cur != pplant_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *pplant_node_temp = *pplant_node_prior;
                *pplant_node_prior = *pplant_node_cur;
                pplant_node_prior -> next = pplant_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                pplant_node_temp -> next = pplant_node_cur -> next;
                *pplant_node_cur = *pplant_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            pplant_node_prior = pplant_node_prior -> next;
        }
        free(pplant_node_temp);
    }
    return pplant_node_head;
}

//����ͳ��
/**
 * ��������: Stat1
 * ��������: �����ͳ�Ƹ����߲˷��������ֲ������ܲ���.
 * �������: hd ����ͷָ��
 *           year ��ֲ���
 * �������: ��
 * �� �� ֵ: ��ͳ�ƽ�㸴�Ƶ��������, ���ؽ�������ͷ����ַ
 *
 * ����˵��: ������ֲ��ݿ���ȷ����ֲ��Ϣ
 */
TOTAL_NODE *Stat1(SPECIES_NODE *hd, char *year)
{
    int total_area;
    int find;
    float total_harvest;

    SPECIES_NODE *pspecies_node;
    VEGE_NODE *pvege_node;
    PLANT_NODE *pplant_node;
    TOTAL_NODE *ptotal_node_head;/*�������ͷָ��*/
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

    for (pspecies_node = hd; pspecies_node != NULL; pspecies_node = pspecies_node -> next){/*����ѭ��������ֲ���*/
        pvege_node = pspecies_node -> vnext;
        find = 0;
        total_area = 0;
        total_harvest = 0;
        while (pvege_node != NULL){
            pplant_node = pvege_node -> pnext;
            while(pplant_node != NULL){
                if ( (strcmp (pplant_node -> year, year) ) == 0){/*����������*/
                    find = 1;
                    total_area += pplant_node -> area;
                    total_harvest += pplant_node -> harvest;
                }
                pplant_node = pplant_node -> next;
            }
            pvege_node = pvege_node -> next;
        }
        if (find != 0){/*����ҵ��������������*/
            ptotal_node_temp = (TOTAL_NODE *)malloc(sizeof(TOTAL_NODE));
            strcpy (ptotal_node_temp -> species_name, pspecies_node -> species_name);/*��������*/
            ptotal_node_temp -> total_area = total_area;
            ptotal_node_temp -> total_harvest = total_harvest;
            ptotal_node_temp -> next = ptotal_node_head;/*����ȳ�*/
            ptotal_node_head = ptotal_node_temp;
        }
    }

    if (ptotal_node_head != NULL){/*����*/
        ptotal_node_temp = NULL;
        ptotal_node_prior = ptotal_node_head;
        ptotal_node_temp = (TOTAL_NODE *)malloc(sizeof(TOTAL_NODE));/*���ڽ���������ʱ���*/

        while (ptotal_node_prior -> next != NULL){/*ѡ������*/
            ptotal_node_cur = ptotal_node_prior;
            ptotal_node_after = ptotal_node_prior -> next;
            while (ptotal_node_after != NULL){/*cur�����������ַ*/
                if (ptotal_node_cur -> total_harvest < ptotal_node_after -> total_harvest){
                    ptotal_node_cur = ptotal_node_after;
                }
                ptotal_node_after = ptotal_node_after -> next;
            }

            if (ptotal_node_cur != ptotal_node_prior){/*������������е���Ϣ��ָ���򲻽���*/
                *ptotal_node_temp = *ptotal_node_prior;
                *ptotal_node_prior = *ptotal_node_cur;
                ptotal_node_prior -> next = ptotal_node_temp -> next;/*�ָ�prior->nextָ��Ľ��*/
                ptotal_node_temp -> next = ptotal_node_cur -> next;
                *ptotal_node_cur = *ptotal_node_temp;/*cur���ݽ�����->nextָ�򲻱�*/
            }
            ptotal_node_prior = ptotal_node_prior -> next;
        }
        free(ptotal_node_temp);
    }

    return ptotal_node_head;
}

/**
 * ��������: Stat2
 * ��������: ���߲�����ͳ���߲�����������ڵ���ֲ������ܲ���.
 * �������: hd ����ͷָ��
 *           vege_name �߲�����
 *           year_head ��ʼ���
 *           year_tail ��ֹ���
 * �������: ��
 * �� �� ֵ: ��ͳ�ƽ�㸴�Ƶ�����������ؽ�������ͷ����ַ
 *
 * ����˵��: ���ݲ�ũ��������ȷ����ֲ��Ϣ
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

    pvege_node = SeekVegeNode(hd, vege_name);/*�����߲˽��*/

    if (pvege_node != NULL){/*����ҵ�*/
        pspecies_node = SeekSpeciesNode(hd, pvege_node -> species_id);/*������������*/
        strcpy (ptotal_node -> species_name, pspecies_node -> species_name);
        pplant_node = pvege_node -> pnext;

        while (pplant_node != NULL){/*ͳ�ƽ������*/
            if (JudgeYear(year_head, pplant_node -> year, year_tail)){/*��������Ϣ��������*/
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
 * ��������: JudgeYearR
 * ��������: �ж�����ַ�����ʽ�Ƿ���ȷ.
 * �������: year ���
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
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
 * ��������: JudgeYearR
 * ��������: �ж�����ַ����Ƿ������������.
 * �������: year_temp ���ж����
 *           year_head ���������
 *           year_tail �������β
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��:
 */
BOOL JudgeYear(char *year_head, char *year_temp, char* year_tail)
{
    int LenH = strlen(year_head);
    int LenP = strlen(year_temp);
    int LenT = strlen(year_tail);

    if(LenH == LenP && LenP == LenT){/*���λ����ͬ*/
        if(strcmp(year_head, year_temp) <= 0
           &&strcmp(year_temp, year_tail) <= 0){
            return TRUE;
           }
    }
    else if(LenH == LenP && LenP < LenT){/*ǰ�������λ����ͬ*/
        if(strcmp(year_head, year_temp) <= 0){
            return TRUE;
        }
    }
    else if(LenH < LenP && LenP == LenT){/*���������λ����ͬ*/
        if(strcmp(year_temp, year_tail) <= 0){
            return TRUE;
        }
    }

    return FALSE;
}
