from sqlalchemy import (
    create_engine, MetaData)
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import (
    Table, Column, CHAR, DECIMAL, DATETIME, INTEGER, String, Text, TIMESTAMP, DateTime, func)
from sqlalchemy.dialects.mysql import \
    BIGINT, BINARY, BIT, BLOB, BOOLEAN, CHAR, DATE, \
    DATETIME, DECIMAL, DECIMAL, DOUBLE, ENUM, FLOAT, INTEGER, \
    LONGBLOB, LONGTEXT, MEDIUMBLOB, MEDIUMINT, MEDIUMTEXT, NCHAR, \
    NUMERIC, NVARCHAR, REAL, SET, SMALLINT, TEXT, TIME, TIMESTAMP, \
    TINYBLOB, TINYINT, TINYTEXT, VARBINARY, VARCHAR, YEAR

db_type = 'mysql'
user = 'java'
password = 'java'
host = 'localhost'
port = '3306'
db_name = 'java_lab2'

def get_engine():
    connect_str = "{}+pymysql://{}:{}@{}:{}/{}?charset=utf8mb4".format(db_type, user, password, host, port, db_name)
    engine = create_engine(connect_str, encoding='utf-8')
    return engine

eng = get_engine()
Base = declarative_base()
Session = sessionmaker(bind=eng)
db_session = Session()
metadata = MetaData(get_engine())

# T_KSXX
T_KSXX = Table("T_KSXX", metadata,
                Column("KSBH", CHAR(6), primary_key=True, index=True, nullable=False),
                Column("KSMC", CHAR(10), nullable=False),
                Column("PYZS", CHAR(8), nullable=False),
                )

# T_BRXX
T_BRXX = Table("T_BRXX", metadata,
                Column("BRBH", CHAR(6), primary_key=True, index=True, nullable=False),
                Column("BRMC", CHAR(10), nullable=False),
                Column("DLKL", CHAR(8), nullable=False),
                Column("YCJE", DECIMAL(10,2), nullable=False),
                Column("DLRQ", DATETIME),
                )

# T_KSYS
T_KSYS = Table("T_KSYS", metadata,
                Column("YSBH", CHAR(6), primary_key=True, index=True, nullable=False),
                Column("KSBH", CHAR(6), index=True, nullable=False),
                Column("YSMC", CHAR(10), nullable=False),
                Column("PYZS", CHAR(4), nullable=False),
                Column("DLKL", CHAR(8), nullable=False),
                Column("SFZJ", TINYINT, nullable=False),
                Column("DLRQ", DATETIME),
                )

# T_HZXX
T_HZXX = Table("T_HZXX", metadata,
                Column("HZBH", CHAR(6), primary_key=True, index=True, nullable=False),
                Column("HZMC", CHAR(12), nullable=False),
                Column("PYZS", CHAR(8), nullable=False),
                Column("KSBH", CHAR(6), index=True, nullable=False),
                Column("SFZJ", TINYINT, nullable=False),
                Column("GHRS", INTEGER, nullable=False),
                Column("GHFY", DECIMAL(8,2), nullable=False),
                )

# T_GHXX
T_GHXX = Table("T_GHXX", metadata,
                Column("GHBH", CHAR(6), primary_key=True, index=True, nullable=False),
                Column("HZBH", CHAR(6), index=True, nullable=False),
                Column("YSBH", CHAR(6), index=True, nullable=False),
                Column("BRBH", CHAR(6), index=True, nullable=False),
                Column("GHRC", INTEGER, index=True, nullable=False),
                Column("THBZ", TINYINT, nullable=False),
                Column("GHFY", DECIMAL(8,2), nullable=False),
                Column("RQSJ", DATETIME, nullable=False),
                Column("KBSJ", DATETIME),
                )

metadata.create_all()
