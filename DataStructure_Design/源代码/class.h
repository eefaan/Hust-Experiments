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

#define SCR_ROW 25             /*屏幕行数*/
#define SCR_COL 80             /*屏幕列数*/

//由时间、教室、课程名、班级、教师名、上课周期及课堂ID等构成课堂信息。
/**
 *课堂信息结点结构
 **/
typedef struct course_node {
    char subject_name[40];      /**< 课程名称*/
    char building[20];          /**< 教室所属教学楼*/
    char room_name[20];         /**< 教室名称*/
    char teacher_name[20];      /**< 教师姓名*/
    int class_num;              /**< 班级个数*/
    char class_name[10][40];        /**< 班级名称*/
    //课堂时间
    int weekday;                    /**< 周几*/
    int lesson[13];               /**< 时间(1~12节数为下标 7.8节课则数组中对应下标值为1)*/
    int week[30];               /**< 上课周数 其中week[0]为起始周数*/

    struct course_node *scnext;  /**< 课程链-下一个属于该课程的课堂*/
    struct course_node *rcnext;  /**< 教室链-下一个位于该教室的课堂*/
    struct course_node *tcnext;  /**< 教师链-下一个该老师参与的课堂*/
    struct course_node *ccnext[10];  /**< 班级链-下一个该班级参与的课堂*/

    struct course_node *prior;  /**< 方便在课堂单链表中删除结点*/
    struct course_node *next;   /**< 指向下一课堂结点的指针 用于遍历课堂*/
}COURSE_NODE;

//教师信息，课程信息，班级信息，学生信息，教室信息等，
/**
 *课程信息结点结构
 **/
typedef struct subject_node {
    char subject_name[40];      /**< 课程名称*/
    float subject_credits;      /**< 学分*/
    int subject_hours;          /**< 学时*/
    struct course_node *scnext;  /**< 指向该课程的课堂指针*/
    struct subject_node *next;  /**< 指向下一结点的指针*/
}SUBJECT_NODE;

/**
 *教室信息结点结构
 **/
typedef struct room_node {
    char building[20];          /**< 所属教学楼*/
    char room_name[20];         /**< 教室名称*/
    struct course_node *rcnext;  /**< 指向位于该教室的课堂指针*/
    struct room_node *next;     /**< 指向下一结点的指针*/
}ROOM_NODE;

/**
 *教师信息结点结构
 **/
typedef struct teacher_node {
    char position[20];          /**< 教师职位*/
    char teacher_name[20];      /**< 教师姓名*/
    struct course_node *tcnext;  /**< 指向该老师参与的课堂指针*/
    struct teacher_node *next;  /**< 指向下一结点的指针*/
}TEACHER_NODE;

/**
 *班级信息结点结构
 **/
typedef struct class_node {
    char class_name[40];        /**< 班级名称*/
    struct course_node *ccnext;  /**< 指向该班级参与的课堂指针*/
    struct class_node *next;    /**< 指向下一结点的指针*/
}CLASS_NODE;

/**
 *教室利用率/能效结点结构
 **/
typedef struct utili_node {
    char room_name[20];        /**< 教室名称*/
    int lesson;                 /**< 教室使用节数*/
    int lesson_day;             /**< 教室白天使用节数*/
    int lesson_night;           /**< 教室夜晚使用节数*/
    float effi_rent;            /**< 白天/夜晚*/
    struct utili_node *next;    /**< 指向下一结点的指针*/
}UTILI_NODE;

/**
 *教师合理性分析结点结构
 **/
typedef struct statteacher_node {
    char teacher_name[20];        /**< 教师名称*/
    char position[20];              /**< 教师职位*/
    int lesson_sum;                 /**< 总课时数*/
    int lesson_max;                   /**< 周课时最大值*/
    int week_lesson_max;              /**< 周课时最大值所在周*/
    char subject_name[40];             /**< 排课不合理的课程名称*/
    int subject_num;                  /**< 记录不合理情况 1为中午 2为傍晚*/
    struct statteacher_node *next;    /**< 指向下一结点的指针*/
}STATTEACHER_NODE;

/**
 *班级合理性分析结点结构
 **/
typedef struct statclass_node {
    char class_name[40];        /**< 班级名称*/
    int lesson_sum;                 /**< 总学时*/
    int lesson_max;                   /**< 周课时最大值*/
    int week_lesson_max;              /**< 周课时最大值所在周*/

    int les_max;                   /**< 1~5五天内单天最大节数*/
    int lesson_max_day;               /**< 最大节数周几*/
    int les_min;                   /**< 1~5五天内单天最小节数*/
    int lesson_min_day;               /**< 最小节数周几*/
    int max_de_min;                   /**< 节数差值*/
    int week;                         /**< 差值最大所处周数*/

    struct statclass_node *next;    /**< 指向下一结点的指针*/
}STATCLASS_NODE;




/**
 *屏幕窗口信息链结点结点结构
 */
typedef struct layer_node {
    char LayerNo;            /**< 弹出窗口层数*/
    SMALL_RECT rcArea;       /**< 弹出窗口区域坐标*/
    CHAR_INFO *pContent;     /**< 弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;           /**< 弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next; /**< 指向下一结点的指针*/
} LAYER_NODE;

/**
 *标签束结构
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< 标签字符串数组首地址*/
    COORD *pLoc;           /**< 标签定位数组首地址*/
    int num;               /**< 标签个数*/
} LABEL_BUNDLE;

/**
 *热区结构
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< 热区定位数组首地址*/
    char *pSort;           /**< 热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;            /**< 热区序号数组首地址*/
    int num;               /**< 热区个数*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*弹出窗口信息链链头*/

TEACHER_NODE *teacher_head = NULL;             /*教师链头指针*/
SUBJECT_NODE *subject_head = NULL;             /*课程链头指针*/
CLASS_NODE *class_head = NULL;                 /*班级链头指针*/
ROOM_NODE *room_head = NULL;                   /*教室链头指针*/
COURSE_NODE *course_head = NULL;               /*课堂链头指针*/


char *gp_sys_name = "排课评估与分析助手";      /*系统名称*/
char *gp_subject_info_filename = "subject.dat";/*课程信息数据文件*/
char *gp_room_info_filename = "room.dat";      /*教室信息数据文件*/
char *gp_teacher_info_filename = "teacher.dat";/*教师信息数据文件*/
char *gp_class_info_filename = "class.dat";    /*班级信息数据文件*/

char *gp_course_info_filename = "course.dat";  /*课堂信息数据文件*/


char *ga_main_menu[] = {"文件(F)",             /*系统主菜单名*/
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计与分析(S)",
                        "帮助(H)"
                       };

char *ga_sub_menu[] = {"[S] 数据保存",          /*系统子菜单名*/
                       "[B] 数据备份",
                       "[R] 数据恢复",
                       "",           /*空串用来在弹出菜单中分隔子菜单项，下同*/
                       "[X] 退出    Alt+X",

                       "[S] 课程信息",
                       "[R] 教室信息",
                       "[T] 教师信息",
                       "[C] 班级信息",
                       "",
                       "[O] 课堂信息",

                       "[S] 课程信息查询",
                       "[R] 教室信息查询",
                       "[T] 教师信息查询",
                       "[C] 班级信息查询",
                       "",
                       "[O] 课堂信息查询",
                       "",
                       "[L] 空闲教室查询",

                       "[V] 教室利用率",
                       "[A] 教室能效",
                       "[N] 教师承担课堂合理性",
                       "[E] 班级参与课堂合理性",

                       "[T] 帮助主题",
                       "",
                       "[A] 关于 ..."
                      };

int ga_sub_menu_count[] = {5, 6, 8, 4, 3};  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/

HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/


int CreatList(void);           /*数据链表初始化*/
void InitInterface(void);                       /*系统界面初始化*/

void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopPrompt(int num);                        /*显示弹出窗口*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/

void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/

int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
void RunSys(void);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(void);                  /*退出系统*/

BOOL ShowModule(char **pString, int n);     /*弹出窗口的建立*/
BOOL ShowModuleWithExp(char **pString, int n);   /*包含弹出窗口的建立*/
int ShowModuleYON(char **pString);          /*确认或者取消弹出窗口的建立*/
BOOL HShowModule(char **pString, int n);    /*警告弹出窗口的建立*/
BOOL ChooseModule(char **pString);

/**文件*/
BOOL LoadData(void);           /*数据加载*/
BOOL SaveData(void);           /*保存数据*/
BOOL BackupData(void);         /*备份数据*/
BOOL RestoreData(void);        /*恢复数据*/
BOOL ExitSys(void);            /*退出系统*/

/**数据维护*/
BOOL MaintainSubjectInfo(void);     /*课程信息维护*/
BOOL MaintainRoomInfo(void);  /*教室信息维护*/
BOOL MaintainTeacherInfo(void);  /*教师信息维护*/
BOOL MaintainClassInfo(void);  /*班级信息维护*/
BOOL MaintainCourseInfo(void);    /*课堂信息维护*/

/**数据查询*/
BOOL QuerySubjectInfo(void);   /*课程信息查询*/
BOOL QueryRoomInfo(void);      /*教室信息查询*/
BOOL QueryTeacherInfo(void);     /*教师信息查询*/
BOOL QueryClassInfo(void);     /*班级信息查询*/
BOOL QueryCourseInfo(void);     /*课堂信息查询*/
BOOL QueryRestRoomInfo(void);/*空闲教室信息查询*/

/**数据统计*/
BOOL StatRoomUtilization(void);          /*一定时间内 所有教室利用率*/
BOOL StatRoomEfficiency (void);          /*一定时间内 单间教室能效*/
BOOL StatTeacherValidity(void);          /*教师合理性*/
BOOL StatClassValidity(void);            /*班级合理性*/

/**帮助*/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL AboutSys(void);       /*关于系统*/

//子函数
/**文件*/
BOOL SaveSysData(void);                       /*保存系统数据*/
BOOL BackupSysData( char *filename);     /*备份系统数据*/
BOOL RestoreSysData( char *filename);  /*恢复系统数据*/
/**数据维护*/
/*结点插入*/
BOOL InsertSubjectNode(SUBJECT_NODE **phd);  /*插入课程信息结点*/
BOOL InsertRoomNode(ROOM_NODE **phd);    /*插入教室信息结点*/
BOOL InsertTeacherNode(TEACHER_NODE **phd); /*插入教师信息结点*/
BOOL InsertClassNode(CLASS_NODE **phd);   /*插入班级信息结点*/
BOOL InsertCourseNode(COURSE_NODE **phd);   /*插入课堂信息结点*/
/*结点修改*/
int ModifSubjectNode(SUBJECT_NODE *phd);    /*修改课程信息结点*/
int ModifRoomNode(ROOM_NODE *phd);       /*修改教室信息结点*/
int ModifTeacherNode(TEACHER_NODE *phd);    /*修改教师信息结点*/
int ModifClassNode(CLASS_NODE *phd);      /*修改班级信息结点*/
int ModifCourseNode(COURSE_NODE *phd);     /*修改课堂信息结点*/
/*节点删除*/
int DelSubjectNode(SUBJECT_NODE **phd);/*删除课程信息结点*/
int DelRoomNode(ROOM_NODE **phd);/*删除教室信息结点*/
int DelTeacherNode(TEACHER_NODE **phd);/*删除教师信息结点*/
int DelClassNode(CLASS_NODE **phd);/*删除班级信息结点*/
int DelCourseNode(COURSE_NODE **phd);/*删除课堂信息结点*/
void DelCourseNodeS(COURSE_NODE *phd);/*删除课堂信息结点*/
/**数据查询*/
/*课程*/
SUBJECT_NODE *SeekSubjectNode(SUBJECT_NODE *hd, char *subject_name); /*按课程名称查找课程信息结点.*/
COURSE_NODE *SeekSubjectNode2(COURSE_NODE *hd,char *class_name); //在班级相关课堂链中查找不重复的课程名称并排序
/*教室*/
ROOM_NODE *SeekRoomNode(ROOM_NODE *hd, char *room_name, char *building); /*按教室名称与所属教学楼查找教室信息结点.*/
ROOM_NODE *SeekRoomNode2(ROOM_NODE *hd,char *building);//按教学楼名称查找 并 排序所有教室
COURSE_NODE *SeekRoomNode3(COURSE_NODE *hd,char *subject_name,char *class_name);//在班级相关课堂链表中按课堂名称和周次周数 查找教室
/*教师*/
TEACHER_NODE *SeekTeacherNode(TEACHER_NODE *hd, char *teacher_name); /*按教师姓名查找教师信息结点.*/
COURSE_NODE *SeekTeacherNode2(COURSE_NODE *hd, char *subject_name,char *class_name);//按课程名称在与班级相关的课堂链中查找 教师姓名
COURSE_NODE *SeekTeacherNode3(COURSE_NODE *hd);//按课程名称查找并排序所有任课教师
/*班级*/
CLASS_NODE *SeekClassNode(CLASS_NODE *hd, char *class_name); /*按班级名称查找班级信息结点.*/
CLASS_NODE *SeekClassNode2(COURSE_NODE *hd);//查找并排序课程链相关课堂链中的所有班级
CLASS_NODE *SeekClassNodeM(CLASS_NODE *hd, char *class_namem);//按部分班级名称模糊查找班级信息
/*课堂*/
COURSE_NODE *SeekCourseNode(COURSE_NODE *hd,char *subject_name,char *building,
                            char *room_name,char *teacher_name,int weekday,int week_start);
COURSE_NODE *SeekCourseNode_S(COURSE_NODE *hd);//排序课程链下的课堂链表
COURSE_NODE *SeekCourseNode_R(COURSE_NODE *hd);//排序教室链下的课堂链表
COURSE_NODE *SeekCourseNode_T(COURSE_NODE *hd);//排序教师链下的课堂链表
COURSE_NODE *SeekCourseNode_C(COURSE_NODE *hd,char *class_name);//排序班级链下的课堂链表
/*空闲教室*/
ROOM_NODE *SeekRestRoomNode(ROOM_NODE *hd, int week,int weekday,int lesson);//依据时间查找空闲教室

/*其他*/
void ScanfLesson(int *c_lesson,char *lesson);//从文件中读取课堂顶点中的节数
void ScanfWeek(int *c_week,char *week);//从文件中读取课堂顶点中的周数
#endif /**< TYPE_H_INCLUDED*/
