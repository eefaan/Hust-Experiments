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

//��ʱ�䡢���ҡ��γ������༶����ʦ�����Ͽ����ڼ�����ID�ȹ��ɿ�����Ϣ��
/**
 *������Ϣ���ṹ
 **/
typedef struct course_node {
    char subject_name[40];      /**< �γ�����*/
    char building[20];          /**< ����������ѧ¥*/
    char room_name[20];         /**< ��������*/
    char teacher_name[20];      /**< ��ʦ����*/
    int class_num;              /**< �༶����*/
    char class_name[10][40];        /**< �༶����*/
    //����ʱ��
    int weekday;                    /**< �ܼ�*/
    int lesson[13];               /**< ʱ��(1~12����Ϊ�±� 7.8�ڿ��������ж�Ӧ�±�ֵΪ1)*/
    int week[30];               /**< �Ͽ����� ����week[0]Ϊ��ʼ����*/

    struct course_node *scnext;  /**< �γ���-��һ�����ڸÿγ̵Ŀ���*/
    struct course_node *rcnext;  /**< ������-��һ��λ�ڸý��ҵĿ���*/
    struct course_node *tcnext;  /**< ��ʦ��-��һ������ʦ����Ŀ���*/
    struct course_node *ccnext[10];  /**< �༶��-��һ���ð༶����Ŀ���*/

    struct course_node *prior;  /**< �����ڿ��õ�������ɾ�����*/
    struct course_node *next;   /**< ָ����һ���ý���ָ�� ���ڱ�������*/
}COURSE_NODE;

//��ʦ��Ϣ���γ���Ϣ���༶��Ϣ��ѧ����Ϣ��������Ϣ�ȣ�
/**
 *�γ���Ϣ���ṹ
 **/
typedef struct subject_node {
    char subject_name[40];      /**< �γ�����*/
    float subject_credits;      /**< ѧ��*/
    int subject_hours;          /**< ѧʱ*/
    struct course_node *scnext;  /**< ָ��ÿγ̵Ŀ���ָ��*/
    struct subject_node *next;  /**< ָ����һ����ָ��*/
}SUBJECT_NODE;

/**
 *������Ϣ���ṹ
 **/
typedef struct room_node {
    char building[20];          /**< ������ѧ¥*/
    char room_name[20];         /**< ��������*/
    struct course_node *rcnext;  /**< ָ��λ�ڸý��ҵĿ���ָ��*/
    struct room_node *next;     /**< ָ����һ����ָ��*/
}ROOM_NODE;

/**
 *��ʦ��Ϣ���ṹ
 **/
typedef struct teacher_node {
    char position[20];          /**< ��ʦְλ*/
    char teacher_name[20];      /**< ��ʦ����*/
    struct course_node *tcnext;  /**< ָ�����ʦ����Ŀ���ָ��*/
    struct teacher_node *next;  /**< ָ����һ����ָ��*/
}TEACHER_NODE;

/**
 *�༶��Ϣ���ṹ
 **/
typedef struct class_node {
    char class_name[40];        /**< �༶����*/
    struct course_node *ccnext;  /**< ָ��ð༶����Ŀ���ָ��*/
    struct class_node *next;    /**< ָ����һ����ָ��*/
}CLASS_NODE;

/**
 *����������/��Ч���ṹ
 **/
typedef struct utili_node {
    char room_name[20];        /**< ��������*/
    int lesson;                 /**< ����ʹ�ý���*/
    int lesson_day;             /**< ���Ұ���ʹ�ý���*/
    int lesson_night;           /**< ����ҹ��ʹ�ý���*/
    float effi_rent;            /**< ����/ҹ��*/
    struct utili_node *next;    /**< ָ����һ����ָ��*/
}UTILI_NODE;

/**
 *��ʦ�����Է������ṹ
 **/
typedef struct statteacher_node {
    char teacher_name[20];        /**< ��ʦ����*/
    char position[20];              /**< ��ʦְλ*/
    int lesson_sum;                 /**< �ܿ�ʱ��*/
    int lesson_max;                   /**< �ܿ�ʱ���ֵ*/
    int week_lesson_max;              /**< �ܿ�ʱ���ֵ������*/
    char subject_name[40];             /**< �ſβ�����Ŀγ�����*/
    int subject_num;                  /**< ��¼��������� 1Ϊ���� 2Ϊ����*/
    struct statteacher_node *next;    /**< ָ����һ����ָ��*/
}STATTEACHER_NODE;

/**
 *�༶�����Է������ṹ
 **/
typedef struct statclass_node {
    char class_name[40];        /**< �༶����*/
    int lesson_sum;                 /**< ��ѧʱ*/
    int lesson_max;                   /**< �ܿ�ʱ���ֵ*/
    int week_lesson_max;              /**< �ܿ�ʱ���ֵ������*/

    int les_max;                   /**< 1~5�����ڵ���������*/
    int lesson_max_day;               /**< �������ܼ�*/
    int les_min;                   /**< 1~5�����ڵ�����С����*/
    int lesson_min_day;               /**< ��С�����ܼ�*/
    int max_de_min;                   /**< ������ֵ*/
    int week;                         /**< ��ֵ�����������*/

    struct statclass_node *next;    /**< ָ����һ����ָ��*/
}STATCLASS_NODE;




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

TEACHER_NODE *teacher_head = NULL;             /*��ʦ��ͷָ��*/
SUBJECT_NODE *subject_head = NULL;             /*�γ���ͷָ��*/
CLASS_NODE *class_head = NULL;                 /*�༶��ͷָ��*/
ROOM_NODE *room_head = NULL;                   /*������ͷָ��*/
COURSE_NODE *course_head = NULL;               /*������ͷָ��*/


char *gp_sys_name = "�ſ��������������";      /*ϵͳ����*/
char *gp_subject_info_filename = "subject.dat";/*�γ���Ϣ�����ļ�*/
char *gp_room_info_filename = "room.dat";      /*������Ϣ�����ļ�*/
char *gp_teacher_info_filename = "teacher.dat";/*��ʦ��Ϣ�����ļ�*/
char *gp_class_info_filename = "class.dat";    /*�༶��Ϣ�����ļ�*/

char *gp_course_info_filename = "course.dat";  /*������Ϣ�����ļ�*/


char *ga_main_menu[] = {"�ļ�(F)",             /*ϵͳ���˵���*/
    	                "����ά��(M)",
                        "���ݲ�ѯ(Q)",
                        "����ͳ�������(S)",
                        "����(H)"
                       };

char *ga_sub_menu[] = {"[S] ���ݱ���",          /*ϵͳ�Ӳ˵���*/
                       "[B] ���ݱ���",
                       "[R] ���ݻָ�",
                       "",           /*�մ������ڵ����˵��зָ��Ӳ˵����ͬ*/
                       "[X] �˳�    Alt+X",

                       "[S] �γ���Ϣ",
                       "[R] ������Ϣ",
                       "[T] ��ʦ��Ϣ",
                       "[C] �༶��Ϣ",
                       "",
                       "[O] ������Ϣ",

                       "[S] �γ���Ϣ��ѯ",
                       "[R] ������Ϣ��ѯ",
                       "[T] ��ʦ��Ϣ��ѯ",
                       "[C] �༶��Ϣ��ѯ",
                       "",
                       "[O] ������Ϣ��ѯ",
                       "",
                       "[L] ���н��Ҳ�ѯ",

                       "[V] ����������",
                       "[A] ������Ч",
                       "[N] ��ʦ�е����ú�����",
                       "[E] �༶������ú�����",

                       "[T] ��������",
                       "",
                       "[A] ���� ..."
                      };

int ga_sub_menu_count[] = {5, 6, 8, 4, 3};  /*�����˵������Ӳ˵��ĸ���*/
int gi_sel_menu = 1;                        /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

char *gp_scr_att = NULL;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
char gc_sys_state = '\0';   /*��������ϵͳ״̬���ַ�*/

HANDLE gh_std_out;          /*��׼����豸���*/
HANDLE gh_std_in;           /*��׼�����豸���*/


int CreatList(void);           /*���������ʼ��*/
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
void RunSys(void);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(void);                  /*�˳�ϵͳ*/

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
BOOL MaintainSubjectInfo(void);     /*�γ���Ϣά��*/
BOOL MaintainRoomInfo(void);  /*������Ϣά��*/
BOOL MaintainTeacherInfo(void);  /*��ʦ��Ϣά��*/
BOOL MaintainClassInfo(void);  /*�༶��Ϣά��*/
BOOL MaintainCourseInfo(void);    /*������Ϣά��*/

/**���ݲ�ѯ*/
BOOL QuerySubjectInfo(void);   /*�γ���Ϣ��ѯ*/
BOOL QueryRoomInfo(void);      /*������Ϣ��ѯ*/
BOOL QueryTeacherInfo(void);     /*��ʦ��Ϣ��ѯ*/
BOOL QueryClassInfo(void);     /*�༶��Ϣ��ѯ*/
BOOL QueryCourseInfo(void);     /*������Ϣ��ѯ*/
BOOL QueryRestRoomInfo(void);/*���н�����Ϣ��ѯ*/

/**����ͳ��*/
BOOL StatRoomUtilization(void);          /*һ��ʱ���� ���н���������*/
BOOL StatRoomEfficiency (void);          /*һ��ʱ���� ���������Ч*/
BOOL StatTeacherValidity(void);          /*��ʦ������*/
BOOL StatClassValidity(void);            /*�༶������*/

/**����*/
BOOL HelpTopic(void);          /*��������*/
BOOL AboutSys(void);       /*����ϵͳ*/

//�Ӻ���
/**�ļ�*/
BOOL SaveSysData(void);                       /*����ϵͳ����*/
BOOL BackupSysData( char *filename);     /*����ϵͳ����*/
BOOL RestoreSysData( char *filename);  /*�ָ�ϵͳ����*/
/**����ά��*/
/*������*/
BOOL InsertSubjectNode(SUBJECT_NODE **phd);  /*����γ���Ϣ���*/
BOOL InsertRoomNode(ROOM_NODE **phd);    /*���������Ϣ���*/
BOOL InsertTeacherNode(TEACHER_NODE **phd); /*�����ʦ��Ϣ���*/
BOOL InsertClassNode(CLASS_NODE **phd);   /*����༶��Ϣ���*/
BOOL InsertCourseNode(COURSE_NODE **phd);   /*���������Ϣ���*/
/*����޸�*/
int ModifSubjectNode(SUBJECT_NODE *phd);    /*�޸Ŀγ���Ϣ���*/
int ModifRoomNode(ROOM_NODE *phd);       /*�޸Ľ�����Ϣ���*/
int ModifTeacherNode(TEACHER_NODE *phd);    /*�޸Ľ�ʦ��Ϣ���*/
int ModifClassNode(CLASS_NODE *phd);      /*�޸İ༶��Ϣ���*/
int ModifCourseNode(COURSE_NODE *phd);     /*�޸Ŀ�����Ϣ���*/
/*�ڵ�ɾ��*/
int DelSubjectNode(SUBJECT_NODE **phd);/*ɾ���γ���Ϣ���*/
int DelRoomNode(ROOM_NODE **phd);/*ɾ��������Ϣ���*/
int DelTeacherNode(TEACHER_NODE **phd);/*ɾ����ʦ��Ϣ���*/
int DelClassNode(CLASS_NODE **phd);/*ɾ���༶��Ϣ���*/
int DelCourseNode(COURSE_NODE **phd);/*ɾ��������Ϣ���*/
void DelCourseNodeS(COURSE_NODE *phd);/*ɾ��������Ϣ���*/
/**���ݲ�ѯ*/
/*�γ�*/
SUBJECT_NODE *SeekSubjectNode(SUBJECT_NODE *hd, char *subject_name); /*���γ����Ʋ��ҿγ���Ϣ���.*/
COURSE_NODE *SeekSubjectNode2(COURSE_NODE *hd,char *class_name); //�ڰ༶��ؿ������в��Ҳ��ظ��Ŀγ����Ʋ�����
/*����*/
ROOM_NODE *SeekRoomNode(ROOM_NODE *hd, char *room_name, char *building); /*������������������ѧ¥���ҽ�����Ϣ���.*/
ROOM_NODE *SeekRoomNode2(ROOM_NODE *hd,char *building);//����ѧ¥���Ʋ��� �� �������н���
COURSE_NODE *SeekRoomNode3(COURSE_NODE *hd,char *subject_name,char *class_name);//�ڰ༶��ؿ��������а��������ƺ��ܴ����� ���ҽ���
/*��ʦ*/
TEACHER_NODE *SeekTeacherNode(TEACHER_NODE *hd, char *teacher_name); /*����ʦ�������ҽ�ʦ��Ϣ���.*/
COURSE_NODE *SeekTeacherNode2(COURSE_NODE *hd, char *subject_name,char *class_name);//���γ���������༶��صĿ������в��� ��ʦ����
COURSE_NODE *SeekTeacherNode3(COURSE_NODE *hd);//���γ����Ʋ��Ҳ����������ον�ʦ
/*�༶*/
CLASS_NODE *SeekClassNode(CLASS_NODE *hd, char *class_name); /*���༶���Ʋ��Ұ༶��Ϣ���.*/
CLASS_NODE *SeekClassNode2(COURSE_NODE *hd);//���Ҳ�����γ�����ؿ������е����а༶
CLASS_NODE *SeekClassNodeM(CLASS_NODE *hd, char *class_namem);//�����ְ༶����ģ�����Ұ༶��Ϣ
/*����*/
COURSE_NODE *SeekCourseNode(COURSE_NODE *hd,char *subject_name,char *building,
                            char *room_name,char *teacher_name,int weekday,int week_start);
COURSE_NODE *SeekCourseNode_S(COURSE_NODE *hd);//����γ����µĿ�������
COURSE_NODE *SeekCourseNode_R(COURSE_NODE *hd);//����������µĿ�������
COURSE_NODE *SeekCourseNode_T(COURSE_NODE *hd);//�����ʦ���µĿ�������
COURSE_NODE *SeekCourseNode_C(COURSE_NODE *hd,char *class_name);//����༶���µĿ�������
/*���н���*/
ROOM_NODE *SeekRestRoomNode(ROOM_NODE *hd, int week,int weekday,int lesson);//����ʱ����ҿ��н���

/*����*/
void ScanfLesson(int *c_lesson,char *lesson);//���ļ��ж�ȡ���ö����еĽ���
void ScanfWeek(int *c_week,char *week);//���ļ��ж�ȡ���ö����е�����
#endif /**< TYPE_H_INCLUDED*/
