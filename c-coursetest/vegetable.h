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

/**
 *蔬菜种类信息链结点结构
 */
typedef struct species_node {
    char species_id[6];        /**< 分类编码*/
    char species_name[8];      /**< 分类名称*/
    struct vege_node *vnext;   /**< 指向蔬菜基本信息支链的指针*/
    struct species_node *next; /**< 指向下一结点的指针*/
} SPECIES_NODE;

/**
 *蔬菜基本信息链结点结构
 */
typedef struct vege_node {
    int vege_id;                /**< 蔬菜编号*/
    char species_id[6];         /**< 分类编码*/
    char vege_name[20];         /**< 蔬菜名称*/
    char nutrition[100];         /**< 营养成分*/
    struct plant_node *pnext;   /**< 指向菜农种植信息支链的指针*/
    struct vege_node *next;     /**< 指向下一结点的指针*/
} VEGE_NODE;

/**
 *菜农种植信息链结点结构
 */
typedef struct plant_node {
    int plant_id;            /**< 种植编号*/
    char plant_name[20];     /**< 菜农姓名*/
    char vege_name[20];      /**< 蔬菜名称*/
    char year[5];            /**< 种植年份*/
    int area;                /**< 种植面积*/
    float harvest;           /**< 收获重量*/
    struct plant_node *next; /**< 指向下一结点的指针*/
} PLANT_NODE;

/**
 *蔬菜种植总面积、收获总重量统计信息链结点结构
 */
typedef struct total_node {
    int vege_id;            	    /**< 蔬菜编号*/
    char vege_name[20];             /**< 蔬菜名称*/
    char species_id[6];             /**< 分类编码*/
    char species_name[20];          /**< 分类名称*/
    int total_area;     	        /**< 种植总面积*/
    float total_harvest;            /**< 收获总重量*/
    struct total_node *next;     	/**< 指向下一结点的指针*/
} TOTAL_NODE;

/**
 *蔬菜数量统计信息链结点结构
 */
typedef struct vege_count {
    int numcount;                   /**< 蔬菜数量*/
    char species_id[6];             /**< 分类编码*/
    char species_name[20];          /**< 分类名称*/
    struct vege_count *next;     	/**< 指向下一结点的指针*/
} VEGE_COUNT;


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
SPECIES_NODE *gp_head = NULL;                  /*主链头指针*/

char *gp_sys_name = "菜农种植信息管理系统";    /*系统名称*/
char *gp_species_info_filename = "species.dat";/*蔬菜种类信息数据文件*/
char *gp_vege_info_filename = "vege.dat";      /*蔬菜基本信息数据文件*/
char *gp_plant_info_filename = "plant.dat";    /*菜农种植信息数据文件*/

char *ga_main_menu[] = {"文件(F)",             /*系统主菜单名*/
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计(S)",
                        "帮助(H)"
                       };

char *ga_sub_menu[] = {"[S] 数据保存",          /*系统子菜单名*/
                       "[B] 数据备份",
                       "[R] 数据恢复",
                       "",           /*空串用来在弹出菜单中分隔子菜单项，下同*/
                       "[X] 退出    Alt+X",

                       "[S] 蔬菜种类信息",
                       "",
                       "[B] 蔬菜基本信息",
                       "",
                       "[P] 菜农种植信息",

                       "[S] 蔬菜种类信息查询",
                       //"[S] 依据分类编码",
                       "",
                       "[B] 蔬菜基本信息查询",
                       //"[C] 依据中文子串",
                       //"[N] 依据分类码及营养成分",
                       "",
                       "[P] 蔬菜种植信息查询",
                       //"[Y] 依据中文子串及种植年份",
                       //"[V] 依据蔬菜名称",

                       "[S] 某年蔬菜数据",
                       "[V] 多年蔬菜数据",
                       "[A] 蔬菜数量数据",
                       "[N] 营养成分数据",
                       "[E] 菜农种植数据",

                       "[T] 帮助主题",
                       "",
                       "[A] 关于 ..."
                      };

int ga_sub_menu_count[] = {5, 5, 5, 5, 3};  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/

HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/


int LoadCode(char *filename, char **ppbuffer);  /*代码表加载*/
int CreatList(SPECIES_NODE **pphead);           /*数据链表初始化*/
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
void RunSys(SPECIES_NODE **pphd);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(SPECIES_NODE *pSPECIES_NODEhd);                  /*退出系统*/

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
BOOL MaintainSpeciesInfo(void);  /*种类信息维护*/
BOOL MaintainVegeInfo(void);     /*蔬菜信息维护*/
BOOL MaintainPlantInfo(void);    /*种植信息维护*/

/**数据查询*/
BOOL QuerySpeciesInfo(void);   /*种类信息查询*/
BOOL QueryVegeInfo(void);      /*蔬菜信息查询*/
BOOL QueryPlantInfo(void);     /*种植信息查询*/

/**数据统计*/
BOOL StatAreaAndHarvest(void);           /*按分类 统计总种植面积和收获总重量*/
BOOL StatAreaAndHarvestM(void);          /*按蔬菜名称 统计总种植面积和收获总重量*/
BOOL StatNum(void);                      /*统计某种蔬菜已有数量*/
BOOL StatNutrition(void);                /*统计含某营养成分的蔬菜*/
BOOL StatPlant(void);                    /*统计某菜农种植信息 (年份降序排列)*/

/**帮助*/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL AboutVegeSys(void);       /*关于系统*/

//子函数
/**文件*/
BOOL SaveSysData(SPECIES_NODE *phd);                       /*保存系统数据*/
BOOL BackupSysData(SPECIES_NODE *phd, char *filename);     /*备份系统数据*/
BOOL RestoreSysData(SPECIES_NODE **pphd, char *filename);  /*恢复系统数据*/
/**数据维护*/
/*结点插入*/
BOOL InsertSpeciesNode(SPECIES_NODE **phd);/*插入种类信息结点*/
BOOL InsertVegeNode(SPECIES_NODE *phd);/*插入蔬菜信息结点*/
BOOL InsertPlantNode(SPECIES_NODE *phd);/*插入种植信息结点*/
/*结点修改*/
int ModifSpeciesNode(SPECIES_NODE *phd);/*修改种类信息结点*/
int ModifVegeNode(SPECIES_NODE *phd);/*修改蔬菜信息结点*/
int ModifPlantNode(SPECIES_NODE *phd);/*修改种植信息结点*/
/*节点删除*/
int DelSpeciesNode(SPECIES_NODE **phd);/*删除种类信息结点*/
int DelVegeNode(SPECIES_NODE *phd);/*删除蔬菜信息结点*/
int DelPlantNode(SPECIES_NODE *phd);/*删除种植信息结点*/
/**数据查询*/
SPECIES_NODE *SeekSpeciesNode(SPECIES_NODE *phd, char *species_id);/*按分类编码 查找种类信息结点*/
VEGE_NODE *SeekVegeNode (SPECIES_NODE *phd, char *vege_name);/*按蔬菜名称 查找蔬菜信息结点*/
VEGE_NODE *SeekVegeNodeM1 (SPECIES_NODE *phd, char *vege_namem);/*按名称(模糊) 查找蔬菜信息结点*/
VEGE_NODE *SeekVegeNodeM2 (SPECIES_NODE *phd, char *species_id, char *vege_nutrim);/*按分类编码和营养成分 查找蔬菜信息结点*/
VEGE_NODE *SeekVegeNodeM3 (SPECIES_NODE *phd, char *nutrim);/*按部分营养成分 查找蔬菜信息结点*/
PLANT_NODE *SeekPlantNode(SPECIES_NODE *phd, char *vege_name, char *plant_name, char *year);  /*按蔬菜名称和菜农名称和种植年份 查找蔬菜种植信息*/
PLANT_NODE *SeekPlantNodeM1(SPECIES_NODE *phd, char *vege_namem, char *year);  /*按名称(模糊)和种植年份 查找蔬菜种植信息*/
PLANT_NODE *SeekPlantNodeM2(SPECIES_NODE *phd, char *vege_name);/*按蔬菜名称查找，按年份分别显示*/
PLANT_NODE *SeekPlantNodeM3(SPECIES_NODE *phd, char *plant_name);  /*按菜农名称 查找蔬菜种植信息*/
/**数据统计*/
TOTAL_NODE *Stat1(SPECIES_NODE *phd, char *year);       /*按年份 统计各类蔬菜种植总面积、收获总重量*/
TOTAL_NODE *Stat2(SPECIES_NODE *phd, char *vege_name, char *year_head, char *year_tail);     /*按起止年份和蔬菜名称 统计蔬菜名称、分类、种植面积、总重量*/

BOOL JudgeYear(char *year_head, char *year_temp, char* year_tail);/*比较年份，判断是否符合条件 head <= temp <= tail */
#endif /**< TYPE_H_INCLUDED*/
