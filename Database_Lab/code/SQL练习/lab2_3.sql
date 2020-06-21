-- 请分别用一条SQL语句完成下列各个小题的需求：

-- 1）查询“张三”用户关注的所有用户的ID号、姓名、性别、出生年份，所在城市，
-- 并且按照出生年份的降序排列，同一个年份的则按照用户ID号升序排列。
SELECT USERS.UID, USERS.Name, USERS.SEX, USERS.BYEAR, USERS.CITY FROM USERS, FOLLOW
WHERE USERS.UID = FOLLOW.UIDFLED
AND FOLLOW.UID IN(
    SELECT UID FROM USERS WHERE Name = '张三'
) ORDER BY USERS.BYEAR DESC, USERS.UID;

-- 2）查找没有被任何人点赞的博文ID、标题以及发表者姓名，并将结果按照标题字符顺序排列。
SELECT MBLOG.BID, MBLOG.TITLE, USERS.Name FROM MBLOG, USERS
WHERE MBLOG.UID = USERS.UID
AND MBLOG.BID NOT IN(
    SELECT BID FROM THUMB
) ORDER BY MBLOG.TITLE;

-- 3）查找2000年以后出生的武汉市用户发表的进入过头条的博文ID；
SELECT DISTINCT TOPDAY.BID FROM MBLOG, USERS, TOPDAY
WHERE MBLOG.UID = USERS.UID
AND MBLOG.BID = TOPDAY.BID
AND USERS.BYEAR >= 2000
AND USERS.CITY LIKE '%武汉%';

-- 4）查找订阅了所有分类的用户ID；
SELECT USERS.UID FROM USERS
WHERE NOT EXISTS(
    SELECT * FROM LABEL WHERE NOT EXISTS(
        SELECT * FROM SUB
        WHERE SUB.UID = USERS.UID
        AND SUB.LID = LABEL.LID
    )
);
-- OR
select UID, Name from USERS
where UID IN(
    select UID from SUB
    group by UID
    having count(*) = (select count(*) from LABEL)
);

-- 5）查找出生年份小于1970年或者大于2010年的用户ID、出生年份、所在城市，
-- 要求where子句中只能有一个条件表达式；
SELECT UID, BYEAR, CITY FROM USERS
WHERE BYEAR NOT BETWEEN 1970 AND 2010;

-- 6）统计每个城市的用户数；
SELECT CITY, COUNT(UID) AS SUM FROM USERS
GROUP BY CITY;

-- 7）统计每个城市的每个出生年份的用户数，并将结果按照城市的升序排列，
-- 同一个城市按照出生用户数的降序排列其相应的年份；
SELECT CITY, BYEAR, COUNT(UID)AS SUM FROM USERS
GROUP BY CITY, BYEAR
ORDER BY CITY, COUNT(UID)DESC;

-- 8）查找被点赞数超过10的博文ID号；
SELECT BID FROM THUMB
GROUP BY BID
HAVING COUNT(UID) > 10;

-- 9）查找被2000年后出生的用户点赞数超过10的博文ID号；
SELECT THUMB.BID FROM THUMB, USERS
WHERE USERS.UID = THUMB.UID
AND USERS.BYEAR >= 2000
GROUP BY THUMB.BID
HAVING COUNT(THUMB.UID) > 10;

-- 10）查找被2000年后出生的用户 点赞数超过10的每篇博文 的进入头条的次数；
SELECT BID, COUNT(TOPDAY.BID)AS TIMES FROM TOPDAY
WHERE BID IN(
    SELECT THUMB.BID FROM THUMB, USERS
    WHERE THUMB.UID = USERS.UID
    AND USERS.BYEAR >= 2000
    GROUP BY THUMB.BID
    HAVING COUNT(THUMB.UID) > 10
) GROUP BY BID;

-- 11）查找订阅了文学、艺术、哲学、音乐中至少一种分类的用户ID，要求不能使用嵌套查询，
-- 且where子句中最多只能包含两个条件；
SELECT SUB.UID FROM SUB, LABEL
WHERE SUB.LID = LABEL.LID
AND LABEL.LNAME in ('文学', '艺术', '哲学' ,'音乐')
GROUP BY SUB.UID;

-- 12）查找标题中包含了“最多地铁站”和“华中科技大学”两个词的博文基本信息；
SELECT * FROM MBLOG
WHERE TITLE LIKE '%最多地铁站%'
AND TITLE LIKE '%华中科技大学%';

-- 13）查找所有相互关注的用户对的两个ID号，要求不能使用嵌套查询；
SELECT FA.UID, FB.UID FROM FOLLOW AS FA, FOLLOW AS FB
WHERE FA.UIDFLED = FB.UID
AND FB.UIDFLED = FA.UID
AND FA.UID > FB.UID;

-- 14）查找好友圈包含了5号用户好友圈的用户ID；
-- SELECT DISTINCT UID FROM FRIENDS
-- WHERE FUID in(
--     -- friends of No.5 User
--     SELECT FUID FROM FRIENDS
--     WHERE UID = 5
-- );
SELECT DISTINCT UID FROM FRIENDS F1
WHERE(
    SELECT COUNT(*) FROM FRIENDS
    WHERE UID = F1.UID
    AND FUID in(
        -- friends of No.5 User
        SELECT FUID FROM FRIENDS
        WHERE UID = 5
    )
) = (
    SELECT COUNT(*) FROM FRIENDS
    WHERE UID = 5
)
AND UID <> 5;

-- 15）查找2019年4月20日每一篇头条博文的ID号、标题以及该博文的每一个分类ID，
-- 要求即使该博文没有任何分类ID也要输出其ID号、标题；
SELECT MBLOG.BID, MBLOG.TITLE, B_L.LID FROM MBLOG LEFT JOIN B_L
ON MBLOG.BID = B_L.BID
WHERE MBLOG.BID IN(
    SELECT BID FROM TOPDAY
    WHERE TYEAR = 2019 AND TMONTH = 4 AND TDAY = 20
);

-- 16）查找至少有3名共同好友的所有用户对的两个ID号。
SELECT FA.UID, FB.UID FROM FRIENDS AS FA, FRIENDS AS FB
WHERE FA.UID < FB.UID
AND FA.FUID = FB.FUID
GROUP BY FA.UID, FB.UID
HAVING COUNT(FA.FUID) >= 3;

-- 17）创建视图：查阅DBMS内部函数，创建一个显示当日热度排名前十的微博信息的视图，
-- 其中的属性包括：博文ID、博文标题、发表者ID、发表者姓名、被点赞数。
CREATE VIEW TOP10(BID, TITLE, UID, NAME, THUMBNUM) AS
(
    SELECT MBLOG.BID, MBLOG.TITLE, USERS.UID, USERS.NAME, count(*) AS THUMB_NUM
    FROM MBLOG, USERS, THUMB, TOPDAY
    WHERE MBLOG.BID = THUMB.BID
    AND MBLOG.UID = USERS.UID
    AND MBLOG.BID = TOPDAY.BID
    AND TOPDAY.TYEAR = DATEPART(yy, getdate())
    AND TOPDAY.TMONTH = DATEPART(MM, getdate())
    AND TOPDAY.TDAY = DATEPART(dd, getdate())
    GROUP BY MBLOG.BID, MBLOG.TITLE, USERS.UID, USERS.NAME
);


-- TODO: Append
-- 2.4 了解系统的查询性能分析功能（选做，各班指导教师可适当调整）
--     选择上述2.3任务中某些较为复杂的SQL语句，查看其执行之前系统给出的分析计划和实际的执行计划，
--     记录观察的结果，并对其进行简单的分析。

-- 2.5 DBMS函数及存储过程和事务（选做，各班指导教师可适当调整）
-- 1）编写一个依据用户ID号计算其发表的博文进入头条的累计天数的DBMS自定义函数，
-- 并利用其查询2000年后出生的上述头条累计天数达到100天的所有用户ID。
CREATE FUNCTION DAYS(@ID INT) RETURNS INT AS
BEGIN
    DECLARE @DAY INT
    SELECT @DAY = COUNT(*) FROM TOPDAY, MBLOG, USERS
    WHERE TOPDAY.BID = MBLOG.BID
    AND MBLOG.UID = USERS.UID
    AND USERS.UID = @ID
    AND USERS.BYEAR >= 2000

    RETURN @DAY
END
-- call the function HERE
SELECT UID, NAME FROM USERS
WHERE DBO.DAYS(UID) >=1;

-- 2）建立关系“点赞排行榜【博文ID，当天点赞人数】”，
-- 里面存储系统当天点赞数前十名的博文ID及其点赞人数，
-- 尝试编写一个DBMS的存储过程，通过该存储过程更新该表。
CREATE TABLE THUMBRANK(
    BID INT,
    NUM INT,
    PRIMARY KEY(BID),
    FOREIGN KEY(BID) REFERENCES MBLOG(BID)
);

CREATE PROC UPDATERANK AS
BEGIN
    DELETE FROM THUMBRANK;
    INSERT INTO THUMBRANK
        SELECT TOP 10 BID, COUNT(*) FROM THUMB
        GROUP BY BID
        ORDER BY COUNT(*) DESC
END

GO
EXEC UPDATERANK;

-- 3）尝试在DBMS的交互式界面中验证事务机制的执行效果。
-- TABLE FOR TRANS TEST
CREATE TABLE TRANSTEST(
    ID      INT,
    CONT    VARCHAR(50)
);
-- TRANS
BEGIN TRAN
BEGIN TRY
    INSERT INTO TRANSTEST VALUES (1, '苹果');
    INSERT INTO TRANSTEST VALUES ('abc', '梨子');
    INSERT INTO TRANSTEST VALUES (3, '栗子');
END TRY
BEGIN CATCH
    select Error_number() as ErrorNumber,  --错误代码
        Error_severity() as ErrorSeverity,  --错误严重级别，级别小于10 try catch 捕获不到
        Error_state() as ErrorState ,  --错误状态码
        Error_Procedure() as ErrorProcedure , --出现错误的存储过程或触发器的名称。
        Error_line() as ErrorLine,  --发生错误的行号
        Error_message() as ErrorMessage  --错误的具体信息
    if(@@trancount>0)
        ROLLBACK TRAN
END CATCH
if(@@trancount>0)
    COMMIT TRAN


select * from TRANSTEST
