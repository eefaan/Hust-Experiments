-- 1）分别用一条sql语句完成对博文表基本的增、删、改的操作；
INSERT INTO MBLOG VALUES(20, 'biaoti2', 4, 2019, 10, 20, 'zhengwen');
DELETE FROM MBLOG WHERE BID=20;
UPDATE MBLOG SET TITLE='newtitle' WHERE BID=20;

-- 2）批处理操作
--  将关注3号用户的用户信息插入到一个自定义的新表FANS_3中。
SELECT USERS.* INTO FANS_3 FROM USERS,FOLLOW
WHERE USERS.UID = FOLLOW.UID
AND FOLLOW.UIDFLED = 3;

-- 3）数据导入导出
-- 通过查阅DBMS资料学习数据导入导出功能，并将任务2.1所建表格的数据导出到操作系统文件，
-- 然后再将这些文件的数据导入到相应空表。
-- 在后续的上机实验环节，通过导入导出或者备份机制实现前次上机环节的数据恢复。
tasks - export data - source: sql server; target:

-- 4）观察性实验
-- 建立一个关系，但是不设置主码，然后向该关系中插入重复元组，
-- 然后观察在图形化交互界面中对已有数据进行删除和修改时所发生的现象。
CREATE TABLE newtable
(
    test_column int
);
INSERT INTO newtable VALUES
(1),
(2),
(2),
(2),
(2);

-- 5）触发器实验
-- 编写一个触发器，用于实现对点赞表的完整性控制规则：
-- 当插入被点赞博文时，如果博文作者就是点赞者本人，则拒绝执行。
create trigger trigger_test on THUMB
for insert,update as
begin
    declare @Muids int, @Mbid int, @temp int
    select @Muids =uid ,@Mbid = bid from inserted
    select @temp = mblog.uid from mblog where @Mbid =mblog.bid
    if(@Muids = @temp) rollback
end;

insert into thumb values (1,10);

insert into thumb values (5,22);
update thumb set bid = 1 where uid = 5 and bid =22;
