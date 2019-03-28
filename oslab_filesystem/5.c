#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct command //命令行
{
	char com[10];
} cmd[22];

struct user //系统用户组
{
	int userid;
	char username[10];
	char password[10];
	int groupid;
} users[8];

struct block // 空闲块信息
{
	int a;		  // 块是否被占用
	int n;		  // 下一组空闲块个数
	int free[50]; // 下一组空闲块中每个块的地址
};

struct super_block // 超级块,使用成组链接法来表示空闲块信息
{
	int n;				 // 空闲栈中空闲块的个数
	int free[50];		 // 空闲块号栈
	struct block memory[20450]; // 全部空闲块
} super_block;

struct physical_block //定义存放文件的数据体
{
	char p[512];
} physicalBlock[20450];

struct node // i结点信息
{
	int file_address[100]; // i结点 文件的物理地址
	int file_length;	   // i结点 文件长度
	int file_style;		   // i结点 文件类型 0代表文件类型是目录文件 1代表文件类型是普通文件
	int file_userid;	   // i结点 所属用户
	int file_groupid;	   // i节点 所属组别
	int file_mode;		   // i结点 读写权限
	int locate[8];		   // 文件位置
} i_node[640];

struct dir // 目录项信息
{
	char file_name[10]; // 文件名
	char dir_name[10];  // 文件所在的目录
	int i_num;			// 文件的i结点号
} root[640];

struct user_open_table //用户打开表项
{
	int point[25]; //用户打开文件指针（指向系统打开表项）
} UserOpenTable[8];

struct system_open_table //系统打开表项
{
	char filename[10]; //文件名称
	int a_num;		   //指针，指向活动i结点
} SystemOpenTable[200];

struct active_node //活动i节点
{
	struct node file_node; //i结点具体信息
	int i_count;		   //计数，打开该文件的用户数
	int i_num;			   //指针，指向i结点号
} ActiveNode[200];

struct user cur_user;			   //当前用户
char cur_dir[10] = "root"; //当前目录
int address_buffer[1000];  //文件地址缓冲区
int a_num;				   //当前活动节点位置
char buffer[512];		   //写文件内容缓冲

//声明函数
void itoa(unsigned long val, char *buf, unsigned radix);
//与文件系统初始化及运行相关的函数
void InitSystem(FILE *fp);
void InitDisks();
void InitUsers();
void InitTable();
void InitCommand();
void Run(FILE *fp);
//读写信息的函数
void ReadFromFile(FILE *fp);
void WriteToFile(FILE *fp);
void ReadUsers(FILE *fps);
void SaveUsers(FILE *fps);
//支持命令运行的函数
void InsertTable(char filename[], int i_num);
int SelectTable(char filename[]);
int IsPermit(int i_num, char operation);
int AllotDisks(int length);
void RecoverDisks(int length);
//与命令有关的函数
int login();
void help();
void show_curdir();
void go_dir(char tmp[]);
void create_dir(char tmp[]);
void del_dir(char tmp[]);
void create_file(char tmp[]);
void open_file(char tmp[]);
void read_file(char tmp[]);
void read_shared_file(char tmp[]);
void write_file(char tmp[]);
void close_file(char tmp[], int filestyle);
void delete_file(char tmp[]);
void show_info();
void logout(FILE *fp);
int change_user(FILE *fp, char tmp[]);
void change_mode(char tmp[]);
void manage_user();
void clear();

int main()
{
	FILE *fp;
	fp = fopen("filesystem", "rb"); //打开文件,用二进制的方式读取
	InitSystem(fp);					//初始化系统
	InitCommand();					//初始化命令
	Run(fp);						//运行
	return 0;
}
//初始化系统操作,如果有系统文件就读取,如果没有就通过调用各初始化函数初始化系统
void InitSystem(FILE *fp)
{
	if (fp == NULL){ //如果filesystem存在读取,如果文件不存在就初始化
		InitDisks(); //首次生成时初始化磁盘
	}
	else{
		ReadFromFile(fp); // 读取系统文件的内容
	}
	InitUsers(); //初始化用户
	InitTable(); //初始化文件表项
}
//初始化命令参数
void InitCommand()
{
	strcpy(cmd[0].com, "exit");
	strcpy(cmd[1].com, "help");
	strcpy(cmd[2].com, "ls");
	strcpy(cmd[3].com, "cd");
	strcpy(cmd[4].com, "clear");
	strcpy(cmd[5].com, "mkdir");
	strcpy(cmd[6].com, "rmdir");
	strcpy(cmd[7].com, "create");
	strcpy(cmd[8].com, "open");
	strcpy(cmd[9].com, "read");
	strcpy(cmd[10].com, "write");
	strcpy(cmd[11].com, "close");
	strcpy(cmd[12].com, "delete");
	strcpy(cmd[13].com, "info");
	strcpy(cmd[14].com, "logout");
	strcpy(cmd[15].com, "switch");
	strcpy(cmd[16].com, "chmod");
	strcpy(cmd[17].com, "manage");
	strcpy(cmd[18].com, "testread");
	strcpy(cmd[19].com, "testwrite");
}
//运行函数,主要提供从界面读取用户操作,并将其与初始化的命令参数比较,执行相对应的操作.
void Run(FILE *fp)
{
	int i, p;
	char com[10], tmp[10];
	while (1)
	{
		if (!login())
			return;
		while (1) //进入文件系统
		{
			printf("[%s]/%s/", cur_user.username, cur_dir);
			scanf("%s", com); // 输入命令并且查找命令的相关操作
			for (i = 0; i < 22; i++)
			{
				if (strcmp(com, cmd[i].com) == 0)
				{
					p = i;
					break;
				}
			}
			if (i == 22) //输入的命令不正确
			{
				p = 22;
			}
			switch (p)
			{
			case 0:// quit
				WriteToFile(fp);
				return;
			case 1:// help
				help();
				break;
			case 2:// ls
				show_curdir();
				break;
			case 3:// cd
				scanf("%s", tmp);
				go_dir(tmp);
				break;
			case 4:// clear
				clear();
				break;
			case 5:// mkdir
				scanf("%s", tmp);
				create_dir(tmp);
				break;
			case 6:// rmdir
				scanf("%s", tmp);
				del_dir(tmp);
				break;
			case 7:// create
				scanf("%s", tmp);
				create_file(tmp);
				break;
			case 8:// open
				scanf("%s", tmp);
				open_file(tmp);
				break;
			case 9:// read
				scanf("%s", tmp);
				read_file(tmp);
				break;
			case 10:// write
				scanf("%s", tmp);
				write_file(tmp);
				break;
			case 11:// close
				scanf("%s", tmp);
				close_file(tmp,3);
				break;
			case 12:// delete
				scanf("%s", tmp);
				delete_file(tmp);
				break;
			case 13:// info
				show_info();
				break;
			case 14:// exit
				logout(fp);
				break;
			case 15:// switch
				scanf("%s", tmp);
				if (change_user(fp, tmp))
					break;
				else
					return;
			case 16:// chmod
				scanf("%s", tmp);
				change_mode(tmp);
				break;
			case 17:// chusr
				manage_user();
				break;
			case 18:
				scanf("%s", tmp);
				read_shared_file(tmp);
				break;
			case 19:// write
				scanf("%s", tmp);
				write_shared_file(tmp);
				break;
			default:
				printf("输入错误！\n");
				break;
			}
		}
	}
}
// 初始化磁盘:将超级块,块信息,i结点以及目录区初始化
void InitDisks()
{
	int i, j, k;
	super_block.n = 50;

	// 初始化空闲块号栈和super_block中的所有空闲块
	for (i = 0; i < 50; i++){// 初始化空闲块号栈中的块为 0-49
		super_block.free[i] = i;
	}
	for (i = 0; i < 20450; i++){// 空闲块信息初始化
		super_block.memory[i].a = 0;
		super_block.memory[i].n = 0;
		for (j = 0; j < 50; j++){// 成组链接未勾链
			super_block.memory[i].free[j] = -1;
		}
	}

	// 成组链接法初始化超级块，下一组的所有空闲块的地址写进每组的最后一个块中
	for (i = 0; i < 20450; i++){// for each memory
		if ((i + 1) % 50 == 0){// 是一组中的最后一个空闲块
			k = i + 1;
			for (j = 0; j < 50; j++){
				if (k < 20450){// in the range [0,20499]
					super_block.memory[i].free[j] = k; // 下一组空闲地址
					super_block.memory[i].n++;		   // 下一组空闲个数
					k++;
				}
			}
		}
	}

	// i结点信息初始化,由于当前无文件打开,则全值为-1
	for (i = 0; i < 640; i++){
		for (j = 0; j < 100; j++){
			i_node[i].file_address[j] = -1; // 文件地址
		}
		i_node[i].file_length = -1; // 文件长度
		i_node[i].file_style = -1;  // 文件类型
	}

	// 根目录区信息初始化
	for (i = 0; i < 640; i++){
		strcpy(root[i].file_name, ""); //文件名
		root[i].i_num = -1;			   //文件节点号
		strcpy(root[i].dir_name, "");  //文件所在目录
		// root[i].is_slink = 0;
		// strcpy(root[i].P_filename, "");
	}

	printf("初始化成功,系统可开始使用\n");
	printf("欢迎使用本系统!\n\n");
}
//初始化用户设置,有文件就读取,没有文件就创建
void InitUsers()
{
	FILE *fps;
	// 判断用户信息文件是否存在,如果用户文件存在,就通过read函数将用户的信息从文件中读取并存入User数据结构中
	if ((fps = fopen("users", "rb")) == NULL)
	{
		users[0].userid = 1; //不存在，则初始化1个用户
		strcpy(users[0].username, "admin");
		strcpy(users[0].password, "admin");
		users[0].groupid = 1;
		//除了初始化时生成的超级管理员之外,其余用户空间都值为负值,等待用户创建
		for (int i = 1; i < 8; i++)
		{
			users[i].userid = -1;
			strcpy(users[i].username, ""); //用户名以及密码都设置为空
			strcpy(users[i].password, "");
			users[i].groupid = -1;
		}
		//调用Save函数将用户的信息存入user文件
		SaveUsers(fps);
	}
	else
	{
		//读出系统用户
		ReadUsers(fps);
	}
}
//初始化系统文件表项、用户文件表项、活动节点
void InitTable()
{
	int i, j;
	//由于系统刚启动时才会执行,此时没有文件正处于打开状态,于是活动i结点以及用户表,系统表都应该为空
	//为三个表项的所有值赋负值,以象征空值.
	//为用户表的指针设置负值
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 25; j++)
		{
			UserOpenTable[i].point[j] = -1;
		}
	}
	//文件名为空,文件数为负值
	for (i = 0; i < 200; i++)
	{
		strcpy(SystemOpenTable[i].filename, "");
		SystemOpenTable[i].a_num = -1;
	}
	//活动i结点个数为0,指针为负值
	for (i = 0; i < 200; i++)
	{
		ActiveNode[i].i_count = 0;
		ActiveNode[i].i_num = -1;
	}
}
//从文件读出系统信息
void ReadFromFile(FILE *fp)
{
	int i;
	//用二进制流的形式打开系统信息文件
	fp = fopen("filesystem", "rb");
	//读出超级块中存放的信息,以一个超级块大小为标准,从文件流中读出一个.
	fread(&super_block, sizeof(struct super_block), 1, fp);
	//从文件中读出总共640个i结点信息
	for (i = 0; i < 640; i++)
	{
		fread(&i_node[i], sizeof(struct node), 1, fp);
	}
	//从文件系统中读出640个目录项信息
	for (i = 0; i < 640; i++)
	{
		fread(&root[i], sizeof(struct dir), 1, fp);
	}
	//读文件信息.
	for (i = 0; i < 20450; i++)
	{
		fread(&physicalBlock[i], sizeof(struct physical_block), 1, fp);
	}
	//关闭文件流
	fclose(fp);
}
// 将信息写入文件中
void WriteToFile(FILE *fp)
{
	//打开文件流,以写二进制流 的方式
	int i;
	fp = fopen("filesystem", "wb");
	//以超级块的大小为标准,向文件中写入一个二进制流
	fwrite(&super_block, sizeof(struct super_block), 1, fp);
	//以节点信息为单位,写入640个节点信息
	for (i = 0; i < 640; i++)
	{
		fwrite(&i_node[i], sizeof(struct node), 1, fp);
	}
	//以目录项的大小为标准,向文件中写入640个二进制流
	for (i = 0; i < 640; i++)
	{
		fwrite(&root[i], sizeof(struct dir), 1, fp);
	}
	//以文件数据单位为标准,存放20449个单位.
	for (i = 0; i < 20450; i++)
	{
		fwrite(&physicalBlock[i], sizeof(struct physical_block), 1, fp);
	}
	fclose(fp);
}
// 从文件读出用户信息
void ReadUsers(FILE *fps)
{
	//以读二进制流的方式打开用户信息文件
	int i;
	fps = fopen("users", "rb");
	//一用户的数据结构大小为单位,读取文件系统的用户信息
	for (i = 0; i < 8; i++)
	{
		fread(&users[i], sizeof(struct user), 1, fps);
	}
	fclose(fps);
}
// 将用户信息写入文件
void SaveUsers(FILE *fps)
{
	//与读用户信息相同,此处以写二进制流的方式打开文件,写入
	int i;
	fps = fopen("users", "wb");
	//通过循环写二进制流
	for (i = 0; i < 8; i++)
	{
		fwrite(&users[i], sizeof(struct user), 1, fps);
	}
	fclose(fps);
}
//往系统文件表项里插入文件
void InsertTable(char filename[], int i_num)
{
	int i, j, k;
	//检查是否当前用户打开表项有该记录
	int point = -1, t;
	//每个用户有二十五个用户打开表项可以使用
	//先查是否有该文件已经被打开,如果有就退出循环,如果没有就将第一个空的文件表获取
	for (i = 0; i < 25; i++)
	{
		//通过用户的id号减一可以得到用户的系统编号.查找文件的指针
		j = UserOpenTable[cur_user.userid - 1].point[i];
		//用户表中的指针在系统表中查找活动结点的编号,
		k = SystemOpenTable[j].a_num;
		//在活动结点中,查找结点的编号.
		t = ActiveNode[k].i_num;
		//系统表中的名字与获得的文件名相同,并且节点号与查找出的节点号相同
		if (strcmp(SystemOpenTable[j].filename, filename) == 0 && i_num == t)
			return;
		//用户表查找不到
		if (j == -1)
		{
			point = i;
			break;
		}
	}
	//如果在用户表中没有空的地方,就弹出警告.
	if (point == -1)
	{
		printf("用户打开表已满!\n");
		return;
	}

	//检查该当前用户打开表项没有该记录，但系统打开表项有
	for (i = 0; i < 200; i++)
	{
		//在系统打开表中查找是否又该文件存在
		k = SystemOpenTable[i].a_num;
		t = ActiveNode[k].i_num;
		if (strcmp(SystemOpenTable[i].filename, filename) == 0 && i_num == t)
		{
			//如果系统打开表中存在,就使用户打开表的内容为系统打开表中的编号,并将活动结点的数量加1
			UserOpenTable[cur_user.userid - 1].point[point] = i;
			ActiveNode[k].i_count += 1;
			return;
		}
	}
	//循环查询是否用户打开表中还有空闲的空间,i=25说明该用户的打开表已经没有空闲了,这时发出警告提示
	for (i = 0; i < 25; i++)
	{
		if (UserOpenTable[cur_user.userid - 1].point[i] == -1)
			break;
	}
	if (i == 25)
	{
		printf("用户打开表已满!\n");
		return;
	}
	//循环查询是否系统打开表中还有空闲的空间,i=200说明系统打开表已经没有空闲了,这时发出警告提示
	for (j = 0; j < 200; j++)
	{
		if (strcmp(SystemOpenTable[j].filename, "") == 0)
			break;
	}
	if (j == 200)
	{
		printf("系统文件表已经满了!\n");
		return;
	}
	//循环查询是否活动i结点的剩余,i=200说明活动i结点已经没有空闲了,这时发出警告提示
	for (k = 0; k < 200; k++)
	{
		if (ActiveNode[k].i_count == 0)
			break;
	}
	if (k == 200)
	{
		printf("活动i结点已经用完!\n");
		return;
	}
	//如果系统打开表与用户打开表中都不存在该文件
	//此时将用户打开表中该用户的指针指向第一个空闲的系统打开表
	UserOpenTable[cur_user.userid - 1].point[i] = j;
	//将文件名放入系统打开表中的文件名项中
	strcpy(SystemOpenTable[j].filename, filename);
	//系统打开表的指针指向活动i结点
	SystemOpenTable[j].a_num = k;
	//活动i结点的各项数据刷新
	ActiveNode[k].i_count += 1;
	ActiveNode[k].file_node = i_node[i_num];
	ActiveNode[k].i_num = i_num;
}
//在当前用户打开文件表项查找是否有该文件 //若有，返回其i_num //若没，返回-1
int SelectTable(char filename[])
{
	int i, j, k, t;
	//检查是否当前用户打开文件表项有该记录
	for (i = 0; i < 25; i++)
	{
		//通过用户的id号减一可以得到用户的系统编号.查找文件的指针
		//用户表中的指针在系统表中查找活动结点的编号,
		//在活动结点中,查找结点的编号
		j = UserOpenTable[cur_user.userid - 1].point[i];
		k = SystemOpenTable[j].a_num;
		t = ActiveNode[k].i_num;
		//系统打开表中的是否有该文件
		if (strcmp(SystemOpenTable[j].filename, filename) == 0)
		{
			//又该文件的话,将当前活动结点的位置刷新
			//将结点编号返回
			a_num = k;
			return t;
		}
	}
	//如果查找之后发现没有该文件存在 ,将当前活动结点位置置为-1,同时返回-1
	if (i == 25)
	{
		a_num = -1;
		return -1;
	}
	return -1;
}
//判断用户是否有相应的操作权限
int IsPermit(int i_num, char operation)
{
	//将该文件的用户id,组id和权限装入变量
	int user_id = i_node[i_num].file_userid;
	int group_id = i_node[i_num].file_groupid;
	int mode = i_node[i_num].file_mode;
	//判断是不是相同用户,相同用户一般都可以使用,故返回1
	if (cur_user.userid == user_id)
	{
		/*
		if( operation=='R' && 2048==(2048&mode) )
			return 1 ;
		if( operation=='W' && 1024==(1024&mode) )
			return 1 ;
		if( operation=='D' && 512==(512&mode) )
			return 1 ;
		if( operation=='E' && 256==(256&mode) )
			return 1 ;
		*/
		return 1;
	}
	//判断是否为同组用户,如果为同组用户,则判断当前用户是否对于文件拥有权限
	else if (cur_user.groupid == group_id)
	{
		if (operation == 'R' && 128 == (128 & mode))
			return 1;
		if (operation == 'W' && 64 == (64 & mode))
			return 1;
		if (operation == 'D' && 32 == (32 & mode))
			return 1;
		if (operation == 'E' && 16 == (16 & mode))
			return 1;
	}
	//当前用户若是与文件的用户不同组则判断是否有相应的权限
	else
	{
		if (operation == 'R' && 8 == (8 & mode))
			return 1;
		if (operation == 'W' && 4 == (4 & mode))
			return 1;
		if (operation == 'D' && 2 == (2 & mode))
			return 1;
		if (operation == 'E' && 1 == (1 & mode))
			return 1;
	}
	return 0;
}
//为文件分配空间（物理块）
int AllotDisks(int length)
{
	int i, j, k, m, p;
	for (i = 0; i < length; i++)
	{
		// 超级块中表示空闲块的个数
		k = 50 - super_block.n;
		// 栈中的相应盘块的地址
		m = super_block.free[k];
		// 栈中的最后一个盘块指向的地址
		p = super_block.free[49];
		// 检测是否还有下一组盘块
		if (m == -1 || super_block.memory[p].a == 1)
		{
			printf("存储空间不足,不能够分配空间\n");
			RecoverDisks(i);
			return 0;
		}
		if (super_block.n == 1)
		{
			//将最后一个盘块分配掉
			super_block.memory[m].a = 1;
			address_buffer[i] = m;
			super_block.n = 0;
			// 从最后一个盘块中取出下一组盘块号写入栈中
			for (j = 0; j < super_block.memory[m].n; j++)
			{
				super_block.free[j] = super_block.memory[m].free[j];
				super_block.n++;
			}
			//要跳过这次循环，下面的语句在if中已经执行过
			continue;
		}
		// 栈中的相应盘块的地址写进 文件地址缓冲区
		address_buffer[i] = m;
		super_block.memory[m].a = 1;
		super_block.n--;
	}
	return 1;
}
// 回收磁盘空间
void RecoverDisks(int length)
{
	int i, j, k, m, q = 0;
	for (i = length - 1; i >= 0; i--)
	{
		k = address_buffer[i];   //需要提供要回收的文件的地址
		m = 49 - super_block.n;  // 回收到栈中的哪个位置
		if (super_block.n == 50) // super_block.n==50的时候栈满了，要将这个栈中的所有地址信息写进下一个地址中
		{
			//如果栈满了,此时将原本的下一组地址放弃,将此时栈中的地址通过循环放入下一组地址
			for (j = 0; j < 50; j++)
			{
				super_block.memory[k].free[j] = super_block.free[j];
			}
			//还原原本的超级块参数
			super_block.n = 0;
			super_block.memory[k].n = 50;
			m = 49;
		}
		// 将下一个文件地址中的盘块号回收到栈中
		super_block.memory[k].a = 0;
		super_block.free[m] = address_buffer[i];
		super_block.n++;
	}
}
//删除文件
void del_file(char filename[])
{
	int i, j, k;
	//通过循环查找是否有该文件存在
	for (i = 0; i < 640; i++)
	{
		//比较该文件名与目录项中的某一个文件名相同
		if (strcmp(filename, root[i].file_name) == 0)
		{
			k = root[i].i_num;
			//权限判断,当前用户为文件的主用户或者该用户对于该文件具有删除权限
			if (((cur_user.userid != i_node[k].file_userid) && ((32 == 32) & i_node[k].file_mode)) || cur_user.userid == i_node[k].file_userid)
			{
				//该文件为普通文件并且文件未打开
				if (i_node[root[i].i_num].file_style == 1 && SelectTable(filename) != -1)
				{
					printf("文件正被使用,请关闭后删除!\n");
					return;
				}
				for (j = 0; j < i_node[k].file_length; j++)
				{
					//通关循环,将该文件占用的地址空间传入全局变量中,以供回收空间时使用
					address_buffer[j] = i_node[k].file_address[j];
				}

				//回收长度为length的空间
				RecoverDisks(i_node[k].file_length);
				//删除文件后要将文件属性和目录项的各个值恢复初值
				for (j = 0; j < 100; j++)
				{
					//地址恢复初值
					i_node[k].file_address[j] = -1;
				}
				//文件名恢复初值
				strcpy(root[i].file_name, "");
				//目录项的I结点信息恢复初值
				root[i].i_num = -1;
				//目录项的文件目录信息恢复初值
				strcpy(root[i].dir_name, "");
				//文件长度恢复
				i_node[k].file_length = -1;
				//文件类型恢复初值
				i_node[k].file_style = -1;
				break;
			}
			//权限不满足时不予删除
			else
			{
				printf("无删除权限\n");
				return;
			}
		}
	}
	//如果未发现此文件名,则提示
	if (i == 640)
	{
		printf("不存在此文件!\n");
	}
}
//用户登录
int login()
{
	char username[10];
	char password[10];
	int count;
	int i = 0;
	//提供三次机会输入用户名密码
	for (count = 0; count < 3; count++)
	{
		printf("login name:");
		//获取输入用户名
		scanf("%s", username);
		printf("password:");
		i = 0;
		//获取输入密码，同时隐藏输入字符
		getchar();
		system("stty -echo");
		while ((password[i] = getchar()) != '\n')
		{
			i++;
		}
		password[i] = '\0';
		system("stty echo");
		printf("\n");
		for (i = 0; i < 8; i++)
		{
			//通过循环将存在的用户与输入的用户名称密码对比
			if (users[i].userid != -1)
				//密码账号都想同
				if ((strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0))
				{
					//将该用户信息设置为当前用户信息
					cur_user.userid = users[i].userid;
					strcpy(cur_user.username, username);
					cur_user.groupid = users[i].groupid;
					printf("登录成功!了解操作信息请输入help!\n");
					return 1;
					break;
				}
		}
		//如果循环到8,则说明用户的信息输入错误,提示
		if (i == 8)
		{
			printf("\n用户名密码输入错误!\n");
		}
	}
	//三次输入错误后,退出系统
	if (count >= 3)
	{
		printf("\n您已三次输入错误，请按任意键退出系统!\n");
		return 0;
	}
	return 0;
}
//打印帮助信息
void help()
{
	printf("命令提示：\n");
	printf("\t01.退出系统(exit)\n");
	printf("\t02.显示帮助命令(help)\n");
	printf("\t03.查看当前目录文件列表(ls)\n");
	printf("\t04.进入当前目录下的指定目录(cd + 目录名), 返回上层使用(cd ..)\n");
	printf("\t06.创建目录(mkdir + 目录名)\n");
	printf("\t07.删除目录(rmdir + 目录名)\n");
	printf("\t08.创建文件(create + 文件名)\n");
	printf("\t09.打开文件(open + 文件名)\n");
	printf("\t10.文件的的读(read + 文件名)\n");
	printf("\t11.文件的写(write + 文件名)\n");
	printf("\t12.文件的的关闭(close + 文件名)\n");
	printf("\t13.删除文件(delete + 文件名)\n");
	printf("\t14.查看系统信息(info)\n");
	printf("\t15.注销(logout)\n");
	// printf("\t16.切换用户(su + 用户名)\n");
	// printf("\t17.更改文件访问权限(chmod + 文件名)\n");
	// printf("\t18.管理用户(chusr)\n");
}
//显示当前目录
void show_curdir()
{
	//输出信息格式
	int i, k;
	printf("\t\t文件名字  文件类型  文件长度  所属目录  备注\n");
	for (i = 0; i < 640; i++)
	{
		//查询文件中 所在目录信息和当前目录信息相同的数据
		if (strcmp(cur_dir, root[i].dir_name) == 0)
		{
			k = root[i].i_num;
			printf("\t\t%s\t", root[i].file_name);
			printf("\t%d\t", i_node[k].file_style);
			printf("%d\t", i_node[k].file_length);
			printf("%s\t", root[i].dir_name);
			printf("\n");
		}
	}
}
//转到指定目录
void go_dir(char filename[])
{
	int i, k;
	char back_str[] = "..";
	if (strcmp(filename, back_str) == 0){// back
		//printf("返回上一级目录\n");
		// 查询和当前目录名相同的目录文件名
		for (i = 0; i < 640; i++)
		{
			k = root[i].i_num;
			//文件名相同,并且为目录文件
			if (strcmp(cur_dir, root[i].file_name) == 0 && (i_node[k].file_style == 0))
			{
				//将目录文件从系统文件表项中移除
				close_file(root[i].file_name,i_node[k].file_style);
				// 将查询到的目录文件名  所在的目录赋值给当前目录
				strcpy(cur_dir, root[i].dir_name);
			}
		}
	}
	else{
		//通过循环查找需要转移到的目录
		for (i = 0; i < 640; i++)
		{
			k = root[i].i_num;
			// 判断文件类型是不是目录类型
			if ((strcmp(filename, root[i].file_name) == 0) && (i_node[k].file_style == 0))
			{
				//将文件插入系统用户表项
				InsertTable(filename, i);
				//将要进入的指定目录设置为当前目录
				strcpy(cur_dir, filename);
				break;
			}
		}
		//如果没有查到
		if (i == 640)
		{
			printf("该目录不存在\n");
		}
	}
}

//创建目录
void create_dir(char filename[])
{
	int length = 4;
	int i, j;
	//是否有相同目录
	for (i = 0; i < 640; i++)
	{
		if (strcmp(filename, root[i].file_name) == 0)
		{
			printf("目录已经存在，不允许建立重名的目录\n");
			return;
		}
	}
	//循环,查找第一个空出来的目录项
	for (i = 0; i < 640; i++)
	{
		//文件节点号为负,则目录项未使用
		if (root[i].i_num == -1)
		{
			//尝试为文件分配长度4
			if (!AllotDisks(length))
				break;
			//写入系统文件表
			// InsertTable(filename, i);

			// 把当前目录名 给新建立的文件
			strcpy(root[i].file_name, filename);
			strcpy(root[i].dir_name, cur_dir);
			// 文件类型为目录文件
			for (int k = 0; k < 640; k++)
			{
				if (i_node[k].file_style == -1)
				{
					//文件节点号
					root[i].i_num = k;
					i_node[k].file_style = 0;
					// 目录文件长度为4
					i_node[k].file_length = length;
					//设定文件用户为当前用户
					i_node[k].file_userid = cur_user.userid;
					i_node[k].file_groupid = cur_user.groupid;
					//初始文件的权限对文件主都有，对同组用户只有读的权限
					i_node[k].file_mode = 2048 | 1024 | 512 | 256 | 128;
					//将文件的物理地址装入结点信息
					for (j = 0; j < length; j++)
					{
						i_node[k].file_address[j] = address_buffer[j];
					}
					break;
				}
			}
			break;
		}
	}
}
//删除目录
void del_dir(char filename[])
{
	int i, j, k;
	for (i = 0; i < 640; i++)
	{
		// 找到目录名字
		k = root[i].i_num;
		//该目录不是当前目录
		if (strcmp(root[i].file_name, filename) == 0 && (i_node[k].file_style) == 0 && strcmp(cur_dir, filename) != 0)
		{
			//查询是否有文件的目录文件为要删除的文件
			for (j = 0; j < 640; j++)
			{
				if (strcmp(filename, root[j].dir_name) == 0)
				{
					printf("目录不为空,无法删除\n");
					return;
				}
			}
			//在系统文件表中去除该目录
			if (j == 640)
			{
				//执行删除文件操作
				close_file(filename,i_node[k].file_style);
				del_file(filename);
				break;
			}
		}
		else if (strcmp(root[i].file_name, filename) == 0 && strcmp(cur_dir, filename) == 0 && (i_node[k].file_style) == 0)
		{
			printf("无法删除当前目录!\n");
			break;
		}
	}
	//不是目录文件,或者不存在
	if (i == 640)
	{
		printf("目录不存在!\n");
	}
}
//创建文件
void create_file(char filename[])
{
	int i, j;
	int length = 80;
	//查找文件是否已存在,
	for (i = 0; i < 640; i++)
	{
		if (strcmp(filename, root[i].file_name) == 0)
		{
			printf("文件已存在，不允许建立\n");
			return;
		}
	}
	//寻找一个空的目录项
	for (i = 0; i < 640; i++)
	{
		if (root[i].i_num == -1)
		{
			//分配空间
			if (!AllotDisks(length))
				break;
			//将文件名插入打开表中
			InsertTable(filename, i);
			// 给新建文件名字赋值
			strcpy(root[i].file_name, filename);
			// 把当前目录名给新建立的文件
			strcpy(root[i].dir_name, cur_dir);
			//为新生成文件的结点中赋各种初值
			for (int k = 0; k < 640; k++)
			{
				if (i_node[k].file_style == -1)
				{
					root[i].i_num = k;
					i_node[k].file_style = 1;
					i_node[k].file_length = length;
					i_node[k].file_userid = cur_user.userid;
					i_node[k].file_groupid = cur_user.groupid;
					//初始权限,与目录相同
					i_node[k].file_mode = 2048 | 1024 | 512 | 256 | 128;
					for (j = 0; j < length; j++)
					{
						//将缓冲区的地址读入文件结点中
						i_node[k].file_address[j] = address_buffer[j];
					}
					for (j = 0; j < 8; j++){
						i_node[k].locate[j] = 0;
					}
					//创建文件,将ilink的值置为0
					break;
				}
			}
			break;
		}
	}
}
//打开文件
void open_file(char filename[])
{
	if (SelectTable(filename)==-1){
		//打开文件,显示文件相应的各项数据
		int i, k;
		char binbuf[32];
		//printf("\t\t文件名字  文件类型   文件长度	访问权限	所属目录\n");
		//查找该文件,将各项数据显示出来
		for (i = 0; i < 640; i++)
		{
			k = root[i].i_num;
			if (strcmp(filename, root[i].file_name) == 0 && (i_node[k].file_style == 1) && strcmp(cur_dir, root[i].dir_name) == 0)
			{// 找到目录项目 是文件 且在当前目录下
				//输出文件的各项状态信息
				printf("\t文件信息：\n");
				printf("\t\t文件名称：\t%s\n", filename);
				printf("\t\t文件类型：\t%d\n", i_node[k].file_style);
				printf("\t\t文件长度：\t%d\n", i_node[k].file_length);
				itoa(i_node[k].file_mode, binbuf, 2);
				printf("\t\t访问权限：\t%s\n", binbuf);
				printf("\t\t所属目录：\t%s\n", root[i].dir_name);
				printf("\t\t文件地址：\n");
				for (int j = 0; j < i_node[k].file_length; j++)
				{
					printf("%d ", i_node[k].file_address[j]);
				}
				printf("\n");
				//将文件插入系统打开表项
				InsertTable(filename, k);
				break;
			}
		}
		//无此文件,提示
		if (i == 640)
		{
			printf("无此文件!\n");
		}
	}
	else{
		printf("文件已打开!\n");
	}
}
//读文件
void read_file(char filename[])
{
	// for (int p = 0; p < 640; p++)
	// {
	// 	int q = root[p].i_num;
	// 	if (strcmp(filename, root[p].file_name) == 0 && (i_node[q].file_style == 1))
	// 	{
	// 		InsertTable(filename, q);
	// 	}
	// }
	int i_num;
	int i;
	int address[100];
	i_num = SelectTable(filename);
	//查询文件是否已打开
	if (i_num == -1)
	{
		printf("未打开该文件！\n");
		return;
	}
	else
	{
		//判断权限
		if (IsPermit(i_num, 'R') == 1)
		{
			//将文件物理地址传入地址缓冲
			for (i = 0; i < 100; i++)
			{
				address[i] = i_node[i_num].file_address[i];
			}
			//通过地址缓冲中的地址,将文件的内容显示出来
			for (i = 0; i < i_node[i_num].file_length; i++)
			{
				printf("%s", physicalBlock[address[i]].p);
			}
			return;
		}
		//权限错误
		else
		{
			printf("无权限操作!\n");
			return;
		}
	}
}
//共享读
void read_shared_file(char filename[])
{
	int i_num;
	int i;
	int address[100];
	i_num = SelectTable(filename);
	//查询文件是否已打开
	if (i_num == -1)
	{
		printf("未打开该文件！\n");
		return;
	}
	else
	{
		//判断权限
		if (IsPermit(i_num, 'R') == 1)
		{
			int j;
			if(i_node[i_num].locate[cur_user.userid]!=0)
				j = i_node[i_num].locate[cur_user.userid];
			else
				j = 0;
			//将文件物理地址传入地址缓冲
			int len = 100-j;
			int locate=j;
			for (i = 0; i < len; i++,j++)
			{
				address[i] = i_node[i_num].file_address[j];
			}
			//通过地址缓冲中的地址,将文件的内容显示出来
			int flag;
			for (i = 0; i < i_node[i_num].file_length - locate; i++)
			{
				printf("%s\n", physicalBlock[address[i]].p);
				i_node[i_num].locate[cur_user.userid]+=1;
				if (i != i_node[i_num].file_length - locate - 1){
					printf("continue?(1:0):");
					scanf("%d",&flag);
					if(flag==0){
						break;
					}
					else if (flag==1){
						int tt;
						for(tt=0;tt<8;tt++){
							if(i_node[i_num].locate[tt]==i_node[i_num].locate[cur_user.userid] && tt!=cur_user.userid){
								printf("somebody else is reading this block, please wait\n");
								i_node[i_num].locate[cur_user.userid]-=1;
								i--;
							}
						}
						continue;
					}
				}
				else{
					i_node[i_num].locate[cur_user.userid] = 0;
					printf("%d",i);
				}
			}
			return;
		}
		//权限错误
		else
		{
			printf("无权限操作!\n");
			return;
		}
	}
}
//写文件
void write_file(char filename[])
{
	int i_num;
	int i;
	int j;
	int address[100];
	i_num = SelectTable(filename);
	//判断文件是否打开
	if (i_num == -1)
	{
		printf("文件未打开！\n");
		return;
	}
	else
	{
		//判断权限
		if (IsPermit(i_num, 'W') == 1)
		{
			//将物理地址装入缓冲
			for (i = 0; i < 100; i++)
				address[i] = i_node[i_num].file_address[i];
			printf("请输入内容,以$结束\n");
			i = 0;
			j = 0;

			//清空缓冲
			fflush(NULL);
			//将输入的字符存入缓冲
			while ((buffer[i++] = getchar()) != '$')
			{
				if (i == 512 && j < 100)
				{
					buffer[i] = '\0';
					//装入文件数据段
					strcpy(physicalBlock[address[j]].p, buffer);
					i = 0;
					j++;
					//i_node[i_num].file_length+=512 ;
				}
				//判断是否写满
				else if (j == 100)
				{
					printf("文件已写满!\n");
					return;
				}
			}
			if (j == 100)
			{
				printf("文件已写满!\n");
				return;
			}
			buffer[i - 1] = '\n';
			buffer[i] = '\0';
			//将文件装入数据区
			strcpy(physicalBlock[address[j]].p, buffer);
			printf("输入完毕!\n");
			//超出80块，还要分配空间
			if (j > 80)
			{
				//再申请多余出的空间块数
				if (!AllotDisks(j - 80))
					return;
				//增加文件长度
				i_node[i_num].file_length += j - 80;
			}
			//加入尾部
			for (j = i + 1; j < 100; j++)
			{
				strcpy(physicalBlock[address[j]].p, "\0");
			}

			return;
		}
		else
		{
			printf("无权限操作!\n");
			return;
		}
	}
}
//写文件
void write_shared_file(char filename[])
{
	int i_num;
	int i;
	int j;
	int address[100];
	i_num = SelectTable(filename);
	//判断文件是否打开
	if (i_num == -1)
	{
		printf("文件未打开！\n");
		return;
	}
	else
	{
		//判断权限
		if (IsPermit(i_num, 'W') == 1)
		{
			//将物理地址装入缓冲
			for (i = 0; i < 100; i++)
				address[i] = i_node[i_num].file_address[i];
			printf("请输入内容,以$结束\n");
			i = 0;
			j = 0;

			//清空缓冲
			fflush(NULL);
			//将输入的字符存入缓冲
			while ((buffer[i++] = getchar()) != '$')
			{
				if (i == 512 && j < 100)
				{
					buffer[i] = '\0';
					//装入文件数据段
					strcpy(physicalBlock[address[j]].p, buffer);
					i = 0;
					j++;
					//i_node[i_num].file_length+=512 ;
				}
				//判断是否写满
				else if (j == 100)
				{
					printf("文件已写满!\n");
					return;
				}
				// buffer[i - 1] = '\n';
				// buffer[i] = '\0';
				//将文件装入数据区
				char temp[3];
				temp[0]=buffer[i-1];
				temp[1]='\n';
				temp[2]='\0';
				strcpy(physicalBlock[address[i-1]].p, temp);
			}
			if (j == 100)
			{
				printf("文件已写满!\n");
				return;
			}
			buffer[i - 1] = '\n';
			buffer[i] = '\0';
			//将文件装入数据区
			// strcpy(physicalBlock[address[j]].p, buffer);
			printf("输入完毕!\n");
			//超出80块，还要分配空间
			if (j > 80)
			{
				//再申请多余出的空间块数
				if (!AllotDisks(j - 80))
					return;
				//增加文件长度
				i_node[i_num].file_length += j - 80;
			}
			//加入尾部
			for (j = i + 1; j < 100; j++)
			{
				strcpy(physicalBlock[address[j]].p, "\0");
			}

			return;
		}
		else
		{
			printf("无权限操作!\n");
			return;
		}
	}
}
//关闭文件 - 清理打开表
void close_file(char filename[],int filestyle)
{
	int i_num;
	int i, j, k, t;
	if(filestyle==3){
		for (i = 0; i < 640; i++)
		{
			// 找到目录名字
			k = root[i].i_num;
			//该目录不是当前目录
			if (strcmp(root[i].file_name, filename) == 0 && strcmp(cur_dir, filename) != 0)
			{
				filestyle = i_node[k].file_style ;
				break;
			}
		}
		if(filestyle == 3){
			printf("文件不存在!\n");
			return;
		}
		if(filestyle == 0){
			printf("不可关闭目录!\n");
			return;
		}
	}


	i_num = SelectTable(filename);
	//文件未打开
	if (i_num == -1 && filestyle == 1){
		printf("文件未打开!\n");
		return;
	}
	if (i_num == -1 && filestyle == 0){//是目录
		return;
	}
	//在系统打开表中查找
	for (i = 0; i < 25; i++)
	{
		j = UserOpenTable[cur_user.userid - 1].point[i];
		k = SystemOpenTable[j].a_num;
		t = ActiveNode[k].i_num;

		if (!strcmp(SystemOpenTable[j].filename, filename) && a_num == k)
		{
			//清除活动i结点
			ActiveNode[k].i_count--;
			//如果全删空了,此时恢复初始化状态,各项数据置负值
			if (ActiveNode[k].i_count == 0)
			{
				UserOpenTable[cur_user.userid - 1].point[i] = -1;
				SystemOpenTable[j].a_num = -1;
				strcpy(SystemOpenTable[j].filename, "");
				ActiveNode[k].i_num = -1;
			}
			if(filestyle == 1){
				printf("文件关闭成功!\n");
			}
			return;
		}
	}
}
//删除文件
void delete_file(char tmp[])
{
	int i, j;
	//查找要删除的文件
	for (i = 0; i < 640; i++)
	{
		j = root[i].i_num;
		//文件名相同,并且为普通文件
		if (strcmp(tmp, root[i].file_name) == 0)
		{
			if (i_node[j].file_style == 1)
			{
				del_file(tmp);
				break;
			}
			else
			{
				printf("该文件是目录文件！不可删除\n");
				break;
			}
		}
	}
	if (i == 640)
	{
		printf("文件不存在!\n");
	}
}
//查看系统信息
void show_info()
{
	//打印系统当前信息
	printf("系统信息:\n");
	int i, m, k = 0;
	for (i = 0; i < 20449; i++)
	{
		if (super_block.memory[i].a == 0)
			k++;
	}
	m = 20449 - k;
	printf("\t空闲的盘块数是：\t");
	printf("%d\n", k);
	printf("\t使用的盘块数是：\t");
	printf("%d\n", m);
	//打印用户打开表状态
	for (i = 0, k = 0; i < 25; i++)
	{
		if (UserOpenTable[cur_user.userid - 1].point[i] != -1)
			k++;
	}
	printf("\t当前用户打开表项为：\t");
	printf("%d\n", k);
	//打印系统打开表状态
	for (i = 0, k = 0; i < 200; i++)
	{
		if (SystemOpenTable[i].a_num != -1)
		{
			k++;
		}
	}
	printf("\t系统打开表项为：\t");
	printf("%d\n", k);
	//打印活动结点状态
	for (i = 0, k = 0; i < 200; i++)
	{
		if (ActiveNode[i].i_num != -1)
		{
			k++;
		}
	}
	printf("\t活动节点已使用数：\t");
	printf("%d\n", k);

	//打印当前用户信息
	printf("\t当前用户信息：\n");
	printf("\t\t用户ID：\t%d\n", cur_user.userid);
	printf("\t\t用户名：\t%s\n", cur_user.username);
	printf("\t\t用户组：\t%d\n", cur_user.groupid);
	/*
	//测试时，查看盘块信息
	for(i=0;i<400;i++)
	{
			printf("%d",super_block.memory[i].a);
	}
	printf("\n");

	for(i=0;i<50;i++)
	{
		printf("%d\t",super_block.free[i]);
	}
	*/
}
//注销
void logout(FILE *fp)
{
	//将系统信息写入文件
	WriteToFile(fp);
	//清屏
	system("clear");
	login();
}
//切换用户
int change_user(FILE *fp, char username[])
{
	char password[10];
	int count;
	int i = 0;
	int f = -1;
	//在已存在的用户中,查找要切换的用户
	for (i = 0; i < 8; i++)
	{
		if (users[i].userid != -1)
			if (strcmp(username, users[i].username) == 0)
			{
				f = i;
				break;
			}
	}
	//查找不到
	if (f == -1)
	{
		printf("无此用户!\n");
		return -1;
	}
	//将目前的信息写入文件
	WriteToFile(fp);
	system("clear");
	//三次机会输入用户名密码
	for (count = 0; count < 3; count++)
	{
		printf("password:");
		i = 0;
		//获取输入密码，同时隐藏输入字符
		getchar();
		system("stty -echo");
		while ((password[i] = getchar()) != '\n')
		{
			i++;
		}
		system("stty echo");
		password[i] = '\0';
		printf("\n");

		if (strcmp(password, users[f].password) == 0)
		{
			cur_user.userid = users[f].userid;
			strcpy(cur_user.username, username);
			cur_user.groupid = users[f].groupid;
			printf("\n登陆成功!\n");
			return 1;
			break;
		}
		else
		{
			printf("密码错误!\n");
		}
	}
	//登陆失败
	if (count >= 3)
	{
		printf("\n登陆失败!\n");
		return 0;
	}
	return 0;
}
//修改文件操作权限
void change_mode(char filename[])
{
	char p[13];
	int i = 0;
	int file_mode = 0; //临时记录权限的变量
	int i_num;
	i_num = SelectTable(filename);
	//查找要更改的文件
	if (i_num == -1)
	{
		printf("系统文件表项中无该文件，请先打开该文件或者创建该文件！\n");
		return;
	}
	else
	{
		//判断权限
		if (IsPermit(i_num, 'E') == 1)
		{
			printf("请输入0、1串（相应的位为一代表有相应的权限，0代表没有）\n");
			printf("格式：文件主读、文件主写、文件主删除、文件主执行、同组用户读、同组用户写、同组用户删除、同组用户执行、不同组用户读、不同组用户写、不同组用户删除、不同组用户执行\n");
			scanf("%s", p);
			//保存文件的操作权限
			for (i = 0; i < 12; i++)
			{
				if (p[i] == '1')
				{
					if (i == 0)
						file_mode = file_mode | 2048;
					if (i == 1)
						file_mode = file_mode | 1024;
					if (i == 2)
						file_mode = file_mode | 512;
					if (i == 3)
						file_mode = file_mode | 256;
					if (i == 4)
						file_mode = file_mode | 128;
					if (i == 5)
						file_mode = file_mode | 64;
					if (i == 6)
						file_mode = file_mode | 32;
					if (i == 7)
						file_mode = file_mode | 16;
					if (i == 8)
						file_mode = file_mode | 8;
					if (i == 9)
						file_mode = file_mode | 4;
					if (i == 10)
						file_mode = file_mode | 2;
					if (i == 11)
						file_mode = file_mode | 1;
				}
			}
			//写权限,清缓存
			i_node[i_num].file_mode = file_mode;
			fflush(NULL);
			return;
		}
		else
		{
			printf("无权修改!\n");
			return;
		}
	}
}
//用户管理模块
void manage_user()
{
	FILE *fp;
	fp = fopen("users", "wb");
	//权限查找
	if (cur_user.groupid != 1)
	{
		printf("对不起，你没有权限进行用户管理！\n");
		return;
	}
	printf("欢迎进入用户管理系统!\n");
	int i, j;
	int f;
	char tempuser[10];
	char temppass[10];
	int tempgroup;
	int tempuid;
	while (1)
	{
		printf("请选择操作(1.查看 2.插入 3.删除 0.退出):\n");
		scanf("%d", &f);
		//将文件信息保存,退出
		if (f == 0)
		{
			SaveUsers(fp);
			break;
		}
		//循环显示用户信息
		if (f == 1)
		{
			printf("用户ID  用户名  用户组\n");
			for (i = 0; i < 8; i++)
			{
				if (users[i].userid != -1)
				{
					printf("%d\t%s\t%d\n", users[i].userid, users[i].username, users[i].groupid);
				}
			}
		}
		//插入用户信息
		if (f == 2)
		{
			//查找第一个空用户
			for (j = 0; j < 8; j++)
			{
				if (users[j].userid == -1)
					break;
			}
			if (j == 8)
			{
				printf("用户已满，不能插入!\n");
				continue;
			}
			//读取用户输入信息
			printf("请输入用户名：");
			scanf("%s", tempuser);
			printf("请输入密码：");
			system("stty -echo");
			scanf("%s", temppass);
			system("stty echo");
			printf("\n请输入组别（1或2或3）：");
			scanf("%d", &tempgroup);
			//验证用户输入信息正确与否
			if (tempgroup < 1 || tempgroup > 3)
			{
				printf("用户组错误，不能插入!\n");
				continue;
			}
			//将用户信息添加
			users[j].userid = j + 1;
			strcpy(users[j].username, tempuser);
			strcpy(users[j].password, temppass);
			users[j].groupid = tempgroup;
		}
		//删除用户信息
		if (f == 3)
		{
			printf("请输入要删除的用户Id：");
			scanf("%d", &tempuid);
			//验证用户输入的id是否正确
			if (tempuid < 1 || tempuid > 8)
			{
				printf("此用户不存在！\n");
				continue;
			}
			//超级管理员不可删除
			if (tempuid == 1)
			{
				printf("超级管理员不可删除！\n");
				continue;
			}
			//保存用户的各种信息
			users[tempuid - 1].userid = -1;
			strcpy(users[tempuid - 1].username, "");
			strcpy(users[tempuid - 1].password, "");
			users[tempuid - 1].groupid = -1;
		}
	}
}

void itoa(unsigned long val, char *buf, unsigned radix)
{
	char *p;
	char *firstdig;
	char temp;
	unsigned digval;
	p = buf;
	firstdig = p;
	do
	{
		digval = (unsigned)(val % radix);
		val /= radix;
		if (digval > 9)
			*p++ = (char)(digval - 10 + 'a');
		else
			*p++ = (char)(digval + '0');
	} while (val > 0);

	*p-- = '\0';
	do
	{
		temp = *p;
		*p = *firstdig;
		*firstdig = temp;
		--p;
		++firstdig;
	} while (firstdig < p);
}

void clear()
{
	system("clear");
	return ;
}
