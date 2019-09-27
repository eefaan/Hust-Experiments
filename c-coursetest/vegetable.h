#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include <time.h>

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*��Ļ����*/
#define SCR_COL 80             /*��Ļ����*/

/**
 *�߲�������Ϣ�����ṹ
 */
typedef struct species_node {
    char species_id[6];        /**< �������*/
    char species_name[8];      /**< ��������*/
    struct vege_node *vnext;   /**< ָ���߲˻�����Ϣ֧����ָ��*/
    struct species_node *next; /**< ָ����һ����ָ��*/
} SPECIES_NODE;

/**
 *�߲˻�����Ϣ�����ṹ
 */
typedef struct vege_node {
    int vege_id;                /**< �߲˱��*/
    char species_id[6];         /**< �������*/
    char vege_name[20];         /**< �߲�����*/
    char nutrition[100];         /**< Ӫ���ɷ�*/
    struct plant_node *pnext;   /**< ָ���ũ��ֲ��Ϣ֧����ָ��*/
    struct vege_node *next;     /**< ָ����һ����ָ��*/
} VEGE_NODE;

/**
 *��ũ��ֲ��Ϣ�����ṹ
 */
typedef struct plant_node {
    int plant_id;            /**< ��ֲ���*/
    char plant_name[20];     /**< ��ũ����*/
    char vege_name[20];      /**< �߲�����*/
    char year[5];            /**< ��ֲ���*/
    int area;                /**< ��ֲ���*/
    float harvest;           /**< �ջ�����*/
    struct plant_node *next; /**< ָ����һ����ָ��*/
} PLANT_NODE;

/**
 *�߲���ֲ��������ջ�������ͳ����Ϣ�����ṹ
 */
typedef struct total_node {
    int vege_id;            	    /**< �߲˱��*/
    char vege_name[20];             /**< �߲�����*/
    char species_id[6];             /**< �������*/
    char species_name[20];          /**< ��������*/
    int total_area;     	        /**< ��ֲ�����*/
    float total_harvest;            /**< �ջ�������*/
    struct total_node *next;     	/**< ָ����һ����ָ��*/
} TOTAL_NODE;

/**
 *�߲�����ͳ����Ϣ�����ṹ
 */
typedef struct vege_count {
    int numcount;                   /**< �߲�����*/
    char species_id[6];             /**< �������*/
    char species_name[20];          /**< ��������*/
    struct vege_count *next;     	/**< ָ����һ����ָ��*/
} VEGE_COUNT;


/**
 *��Ļ������Ϣ�������ṹ
 */
typedef struct layer_node {
    char LayerNo;            /**< �������ڲ���*/
    SMALL_RECT rcArea;       /**< ����������������*/
    CHAR_INFO *pContent;     /**< �������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;           /**< �������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next; /**< ָ����һ����ָ��*/
} LAYER_NODE;

/**
 *��ǩ���ṹ
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< ��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;           /**< ��ǩ��λ�����׵�ַ*/
    int num;               /**< ��ǩ����*/
} LABEL_BUNDLE;

/**
 *�����ṹ
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< ������λ�����׵�ַ*/
    char *pSort;           /**< �������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;            /**< ������������׵�ַ*/
    int num;               /**< ��������*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*����������Ϣ����ͷ*/
SPECIES_NODE *gp_head = NULL;                  /*����ͷָ��*/

char *gp_sys_name = "��ũ��ֲ��Ϣ����ϵͳ";    /*ϵͳ����*/
char *gp_species_info_filename = "species.dat";/*�߲�������Ϣ�����ļ�*/
char *gp_vege_info_filename = "vege.dat";      /*�߲˻�����Ϣ�����ļ�*/
char *gp_plant_info_filename = "plant.dat";    /*��ũ��ֲ��Ϣ�����ļ�*/

char *ga_main_menu[] = {"�ļ�(F)",             /*ϵͳ���˵���*/
    	                "����ά��(M)",
                        "���ݲ�ѯ(Q)",
                        "����ͳ��(S)",
                        "����(H)"
                       };

char *ga_sub_menu[] = {"[S] ���ݱ���",          /*ϵͳ�Ӳ˵���*/
                       "[B] ���ݱ���",
                       "[R] ���ݻָ�",
                       "",           /*�մ������ڵ����˵��зָ��Ӳ˵����ͬ*/
                       "[X] �˳�    Alt+X",

                       "[S] �߲�������Ϣ",
                       "",
                       "[B] �߲˻�����Ϣ",
                       "",
                       "[P] ��ũ��ֲ��Ϣ",

                       "[S] �߲�������Ϣ��ѯ",
                       //"[S] ���ݷ������",
                       "",
                       "[B] �߲˻�����Ϣ��ѯ",
                       //"[C] ���������Ӵ�",
                       //"[N] ���ݷ����뼰Ӫ���ɷ�",
                       "",
                       "[P] �߲���ֲ��Ϣ��ѯ",
                       //"[Y] ���������Ӵ�����ֲ���",
                       //"[V] �����߲�����",

                       "[S] ĳ���߲�����",
                       "[V] �����߲�����",
                       "[A] �߲���������",
                       "[N] Ӫ���ɷ�����",
                       "[E] ��ũ��ֲ����",

                       "[T] ��������",
                       "",
                       "[A] ���� ..."
                      };

int ga_sub_menu_count[] = {5, 5, 5, 5, 3};  /*�����˵������Ӳ˵��ĸ���*/
int gi_sel_menu = 1;                        /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

char *gp_scr_att = NULL;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
char gc_sys_state = '\0';   /*��������ϵͳ״̬���ַ�*/

HANDLE gh_std_out;          /*��׼����豸���*/
HANDLE gh_std_in;           /*��׼�����豸���*/


int LoadCode(char *filename, char **ppbuffer);  /*��������*/
int CreatList(SPECIES_NODE **pphead);           /*���������ʼ��*/
void InitInterface(void);                       /*ϵͳ�����ʼ��*/

void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
void PopPrompt(int num);                        /*��ʾ��������*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/

void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/

int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(SPECIES_NODE **pphd);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(SPECIES_NODE *pSPECIES_NODEhd);                  /*�˳�ϵͳ*/

BOOL ShowModule(char **pString, int n);     /*�������ڵĽ���*/
BOOL ShowModuleWithExp(char **pString, int n);   /*�����������ڵĽ���*/
int ShowModuleYON(char **pString);          /*ȷ�ϻ���ȡ���������ڵĽ���*/
BOOL HShowModule(char **pString, int n);    /*���浯�����ڵĽ���*/
BOOL ChooseModule(char **pString);

/**�ļ�*/
BOOL LoadData(void);           /*���ݼ���*/
BOOL SaveData(void);           /*��������*/
BOOL BackupData(void);         /*��������*/
BOOL RestoreData(void);        /*�ָ�����*/
BOOL ExitSys(void);            /*�˳�ϵͳ*/

/**����ά��*/
BOOL MaintainSpeciesInfo(void);  /*������Ϣά��*/
BOOL MaintainVegeInfo(void);     /*�߲���Ϣά��*/
BOOL MaintainPlantInfo(void);    /*��ֲ��Ϣά��*/

/**���ݲ�ѯ*/
BOOL QuerySpeciesInfo(void);   /*������Ϣ��ѯ*/
BOOL QueryVegeInfo(void);      /*�߲���Ϣ��ѯ*/
BOOL QueryPlantInfo(void);     /*��ֲ��Ϣ��ѯ*/

/**����ͳ��*/
BOOL StatAreaAndHarvest(void);           /*������ ͳ������ֲ������ջ�������*/
BOOL StatAreaAndHarvestM(void);          /*���߲����� ͳ������ֲ������ջ�������*/
BOOL StatNum(void);                      /*ͳ��ĳ���߲���������*/
BOOL StatNutrition(void);                /*ͳ�ƺ�ĳӪ���ɷֵ��߲�*/
BOOL StatPlant(void);                    /*ͳ��ĳ��ũ��ֲ��Ϣ (��ݽ�������)*/

/**����*/
BOOL HelpTopic(void);          /*��������*/
BOOL AboutVegeSys(void);       /*����ϵͳ*/

//�Ӻ���
/**�ļ�*/
BOOL SaveSysData(SPECIES_NODE *phd);                       /*����ϵͳ����*/
BOOL BackupSysData(SPECIES_NODE *phd, char *filename);     /*����ϵͳ����*/
BOOL RestoreSysData(SPECIES_NODE **pphd, char *filename);  /*�ָ�ϵͳ����*/
/**����ά��*/
/*������*/
BOOL InsertSpeciesNode(SPECIES_NODE **phd);/*����������Ϣ���*/
BOOL InsertVegeNode(SPECIES_NODE *phd);/*�����߲���Ϣ���*/
BOOL InsertPlantNode(SPECIES_NODE *phd);/*������ֲ��Ϣ���*/
/*����޸�*/
int ModifSpeciesNode(SPECIES_NODE *phd);/*�޸�������Ϣ���*/
int ModifVegeNode(SPECIES_NODE *phd);/*�޸��߲���Ϣ���*/
int ModifPlantNode(SPECIES_NODE *phd);/*�޸���ֲ��Ϣ���*/
/*�ڵ�ɾ��*/
int DelSpeciesNode(SPECIES_NODE **phd);/*ɾ��������Ϣ���*/
int DelVegeNode(SPECIES_NODE *phd);/*ɾ���߲���Ϣ���*/
int DelPlantNode(SPECIES_NODE *phd);/*ɾ����ֲ��Ϣ���*/
/**���ݲ�ѯ*/
SPECIES_NODE *SeekSpeciesNode(SPECIES_NODE *phd, char *species_id);/*��������� ����������Ϣ���*/
VEGE_NODE *SeekVegeNode (SPECIES_NODE *phd, char *vege_name);/*���߲����� �����߲���Ϣ���*/
VEGE_NODE *SeekVegeNodeM1 (SPECIES_NODE *phd, char *vege_namem);/*������(ģ��) �����߲���Ϣ���*/
VEGE_NODE *SeekVegeNodeM2 (SPECIES_NODE *phd, char *species_id, char *vege_nutrim);/*����������Ӫ���ɷ� �����߲���Ϣ���*/
VEGE_NODE *SeekVegeNodeM3 (SPECIES_NODE *phd, char *nutrim);/*������Ӫ���ɷ� �����߲���Ϣ���*/
PLANT_NODE *SeekPlantNode(SPECIES_NODE *phd, char *vege_name, char *plant_name, char *year);  /*���߲����ƺͲ�ũ���ƺ���ֲ��� �����߲���ֲ��Ϣ*/
PLANT_NODE *SeekPlantNodeM1(SPECIES_NODE *phd, char *vege_namem, char *year);  /*������(ģ��)����ֲ��� �����߲���ֲ��Ϣ*/
PLANT_NODE *SeekPlantNodeM2(SPECIES_NODE *phd, char *vege_name);/*���߲����Ʋ��ң�����ݷֱ���ʾ*/
PLANT_NODE *SeekPlantNodeM3(SPECIES_NODE *phd, char *plant_name);  /*����ũ���� �����߲���ֲ��Ϣ*/
/**����ͳ��*/
TOTAL_NODE *Stat1(SPECIES_NODE *phd, char *year);       /*����� ͳ�Ƹ����߲���ֲ��������ջ�������*/
TOTAL_NODE *Stat2(SPECIES_NODE *phd, char *vege_name, char *year_head, char *year_tail);     /*����ֹ��ݺ��߲����� ͳ���߲����ơ����ࡢ��ֲ�����������*/

BOOL JudgeYear(char *year_head, char *year_temp, char* year_tail);/*�Ƚ���ݣ��ж��Ƿ�������� head <= temp <= tail */
#endif /**< TYPE_H_INCLUDED*/
