-- 用户【用户ID，姓名，性别，出生年份，所在城市】记录所有注册用户的基本信息，英文表名和字段名如下：
-- USERS(UID 整型，NAME 字符串，SEX 一位汉字，BYEAR 整型，CITY 字符串 )；
CREATE TABLE USERS
(
   UID      INT            NOT NULL PRIMARY KEY,
   Name     VARCHAR(50)    NOT NULL,
   SEX      VARCHAR(2),
   BYEAR    INT,
   CITY     VARCHAR(50)
);

-- 分类【分类ID，分类名称】记录微博平台中所有可能涉及的微博的类型，例如文学、艺术、军事等，英文表名和字段名如下：
-- LABEL(LID 整型，LNAME 字符串)；
CREATE TABLE LABEL
(
	LID		INT				NOT NULL PRIMARY KEY,
	LNAME	VARCHAR(50)
);

-- 博文【博文ID，标题，用户ID，年，月，日，正文】记录每一篇微博的基本信息，英文表名和字段名如下：
-- MBLOG(BID 整型，TITLE 字符串，UID 整型，PYEAR 整型，PMONTH 整型， PDAY 整型，CONT 字符串)，
-- 写出该关系的建表SQL语句；
CREATE TABLE MBLOG
(
    BID     INT             NOT NULL PRIMARY KEY,
    TITLE   VARCHAR(50),
    UID     INT             FOREIGN KEY REFERENCES USERS(UID) NOT NULL,
    PYEAR   INT,
    PMONTH  INT,
    PDAY    INT,
    CONT    VARCHAR(400)
);

-- 博文标注【博文ID，分类ID】记录每一篇微博的作者给该微博贴上的分类标签，一篇微博可以涉及不止一种分类，英文表名和字段名如下：
-- B_L(BID 整型，LID 整型)；
CREATE TABLE B_L
(
    BID     INT             NOT NULL FOREIGN KEY REFERENCES MBLOG(BID),
    LID     INT             NOT NULL FOREIGN KEY REFERENCES LABEL(LID)
);

-- 关注【用户ID，被关注用户ID】记录每位用户关注的其他用户，每位用户可关注多人，英文表名和字段名如下：
-- FOLLOW(UID 整型，UIDFLED 整型)；
CREATE TABLE FOLLOW
(
    UID     INT             NOT NULL FOREIGN KEY REFERENCES USERS(UID),
    UIDFLED INT             NOT NULL FOREIGN KEY REFERENCES USERS(UID)
);

-- 好友【用户ID， 好友ID】记录每位用户的好友（可多个），英文表名和字段名如下：
-- FRIENDS(UID 整型，FUID 整型);
CREATE TABLE FRIENDS
(
    UID     INT             NOT NULL FOREIGN KEY REFERENCES USERS(UID),
    FUID    INT             NOT NULL FOREIGN KEY REFERENCES USERS(UID)
);

-- 订阅【用户ID, 订阅分类ID】记录用户订阅的每一种分类，英文表名和字段名如下：
-- SUB(UID 整型，LID 整型);
CREATE TABLE SUB
(
    UID     INT             NOT NULL FOREIGN KEY REFERENCES USERS(UID),
    LID     INT             NOT NULL FOREIGN KEY REFERENCES LABEL(LID)
);


-- 点赞【用户ID， 博文ID】记录用户点赞的每一篇微博，英文表名和字段名如下：
-- THUMB(UID 整型，BID 整型)，
-- 写出该关系的建表SQL语句；
CREATE TABLE THUMB
(
    UID     INT             NOT NULL FOREIGN KEY REFERENCES USERS(UID),
    BID     INT             NOT NULL FOREIGN KEY REFERENCES MBLOG(BID)
);

-- 头条【年，月，日，博文ID，顺序号】记录每一天的热度排名前十的博文ID号以及该博文在热度前十名中的排名，英文表名和字段名如下：
-- TOPDAY(TYEAR整型，TMONTH 整型，TDAY 整型，BID 整型，TNO 整型)。
CREATE TABLE TOPDAY
(
    TYEAR   INT,
    TMONTH  INT,
    TDAY    INT,
    BID     INT             NOT NULL FOREIGN KEY REFERENCES MBLOG(BID),
    TNO     INT
);

-- DataBase initialize
INSERT INTO USERS VALUES -- 用户ID，姓名，性别，出生年份，所在城市
(1, '符闻蓬袄', '女', 1981, '海外'),
(2, '浅墨_g', '女', 1999, '云南'),
(3, '泶哩', '女', 1998, '上海'),
(4, '用户2007326376', '男', NULL, '北京 东城区'),
(5, '南海网', '男', 2000, '北京 朝阳区'),
(6, 'Fil小白', '女', 1990, '北京 朝阳区'),
(7, 'Dipsy迪西', '男', 1998, '海外 其他'),
(8, 'viscous166491547978', '女', NULL, '山东 泰安'),
(9, '念奴娇_b', '男', 1990, '湖南'),
(10, '素年未逝_Park', '女', 2001, '黑龙江'),
(11, '他是毒药_immwayne', '女', 1994, '陕西'),
(12, '悠悠_m', '女', 1997, '黑龙江'),
(13, '乖赑_JPY', '男', 1988, '甘肃'),
(14, '愈久愈念_g', '女', 1994, '湖南'),
(15, '张三', '男', 2000, '湖北 武汉'),
(16, 'Name1', '男', 1970, '湖北'),
(17, 'Name2', '女', 1969, '湖南'),
(18, 'Name3', '女', 2010, '湖北 武汉'),
(19, 'Name4', '女', 2011, '湖北 武汉'),
(20, 'Name5', '男', 2010, '湖北 武汉'),
(21, 'Name6', '女', 2012, '湖北 武汉'),
(22, 'Name7', '女', 2012, '湖北 武汉'),
(23, 'Name8', '女', 2012, '湖北 武汉'),
(24, 'Name9', '女', 2012, '湖北 武汉'),
(25, 'Name10', '女', 2014, '湖北 武汉'),
(26, 'Name11', '男', 2011, '湖南');
INSERT INTO LABEL VALUES -- 分类ID，分类名称
(1, '体育'),
(2, '财经'),
(3, '国际'),
(4, '文学'),
(5, '艺术'),
(6, '哲学'),
(7, '音乐');
INSERT INTO MBLOG VALUES -- 博文ID，标题，用户ID，年，月，日，正文
(1, 'biaoti1', 5, 2018, 10, 19, 'zhengwen'),
(2, 'biaoti2', 7, 2018, 11, 12, 'zhengwen'),
(3, 'biaoti3', 10, 2019, 3, 3, 'zhengwen'),
(4, 'biaoti14', 3, 2018, 10, 19, 'zhengwen'),
(5, 'Title4', 15, 2018, 10, 19, 'zhengwen'),
(6, 'ZTitle3', 15, 2018, 10, 19, 'zhengwen'),
(7, 'Title2', 15, 2018, 10, 19, 'zhengwen'),
(8, 'Title1', 15, 2018, 10, 19, 'zhengwen'),
(9, 'TopTitle', 15, 2018, 10, 10, 'toutiao'),
(10, 'submit_by_1', 1, 2019, 1, 1, 'zhengwen'),
(11, '123最多地铁站2', 2, 2019, 2, 1, 'zhengwen'),
(12, '123华中科技大学3', 2, 2019, 3, 2, 'zhengwen'),
(13, '最多地铁站666华中科技大学', 2, 2019, 3, 2, 'zhengwen'),
(14, '华中科技大学7最多地铁站', 2, 2019, 3, 2, 'zhengwen'),
(15, 'TopTitle1_5_5', 10, 2019, 5, 5, 'zhengwen1'),
(16, 'TopTitle2_5_5', 10, 2019, 5, 5, 'zhengwen2'),
(17, 'TopTitle3_5_5', 20, 2019, 5, 5, 'zhengwen3'),
(18, 'TopTitle4_5_5', 21, 2019, 5, 5, 'zhengwen4'),
(19, 'TopTitle5_5_5', 22, 2019, 5, 5, 'zhengwen5'),
(20, 'TopTitle6_5_5', 23, 2019, 5, 5, 'zhengwen6'),
(21, 'TopTitle7_5_5', 24, 2019, 5, 5, 'zhengwen7'),
(22, 'TopTitle8_5_5', 10, 2019, 5, 5, 'zhengwen8'),
(23, 'TopTitle9_5_5', 10, 2019, 5, 5, 'zhengwen9'),
(24, 'TopTitle10_5_5', 10, 2019, 5, 5, 'zhengwen10');
INSERT INTO B_L VALUES -- 博文ID，分类ID
(1, 1),
(2, 1),
(3, 2),
(3, 4),
(3, 5),
(3, 6),
(4, 6);
INSERT INTO FOLLOW VALUES -- 用户ID，被关注用户ID
(1, 2),
(2, 1),
(3, 6),
(9, 12),
(15,7),
(15,1),
(15,2),
(15,3),
(15,4),
(15,5),
(5,3),
(6,3),
(7,3),
(12, 9),
(7, 15);
INSERT INTO FRIENDS VALUES -- 用户ID， 好友ID
(1, 2),
(1, 3),
(1, 4),
(2, 3),
(15, 4),
(5, 2),
(5, 3),
(5, 4),
(6,2),
(6,3),
(6,4),
(6,5),
(7,2),
(7,3);
INSERT INTO SUB VALUES -- 用户ID, 订阅分类ID
(1, 1),
(2, 2),
(3, 3),
(15, 1),
(15, 2),
(15, 3),
(1,4),
(1,5),
(2,6),
(15,4);
INSERT INTO THUMB VALUES -- 用户ID， 博文ID
(1, 1),
(2, 2),
(3, 3),
(1, 9),
(2, 9),
(3, 9),
(4, 9),
(5, 9),
(6, 9),
(7, 9),
(8, 9),
(9, 9),
(10, 9),
(11, 9),
(12, 9),
(15,3),
(18,3),
(19,3),
(20,3),
(21,3),
(22,3),
(23,3),
(24,3),
(25,3),
(5,3),
(26,3),
(26,8),
(10,8),
(18,8),
(19,8),
(20,8),
(21,8),
(22,8),
(23,8),
(24,8),
(25,8),
(5,8),
(1,15),
(2,15),
(3,15),
(4,15),
(5,15),
(6,15),
(7,15),
(8,15),
(9,15),
(1,16),
(2,16),
(3,16),
(4,16),
(5,16),
(6,16),
(7,16),
(8,16),
(1,17),
(2,17),
(3,17),
(4,17),
(5,17),
(6,17),
(7,17),
(1,18),
(2,18),
(3,18),
(4,18),
(5,18),
(6,18),
(1,19),
(2,19),
(3,19),
(4,19),
(5,19),
(1,20),
(2,20),
(3,20),
(4,20),
(1,21),
(2,21),
(3,21),
(1,22),
(2,22),
(1,23);
INSERT INTO TOPDAY VALUES -- 年，月，日，博文ID，顺序号
(2018, 10, 19, 1, 1),
(2018, 10, 19, 4, 2),
(2018, 10, 10, 9, 1),
(2018, 10, 11, 9, 1),
(2018, 10, 12, 9, 1),
(2018, 11, 11, 3, 1),
(2018, 11, 12, 3, 1),
(2018, 11, 13, 3, 1),
(2019, 4, 20, 3, 1),
(2018, 12, 11, 8, 1),
(2018, 12, 12, 8, 1),
(2018, 12, 13, 8, 1),
(2018, 12, 14, 8, 1),
(2019, 4, 20, 8, 2),
(2019, 5, 5, 15, 1),
(2019, 5, 5, 16, 2),
(2019, 5, 5, 17, 3),
(2019, 5, 5, 18, 4),
(2019, 5, 5, 19, 5),
(2019, 5, 5, 20, 6),
(2019, 5, 5, 21, 7),
(2019, 5, 5, 22, 8),
(2019, 5, 5, 23, 9);
