from sqlalchemy import (
    create_engine, MetaData)
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import (
    Table, Column, CHAR, DECIMAL, DATETIME, INTEGER, String, Text, TIMESTAMP, DateTime, func, ForeignKey)
from sqlalchemy.dialects.mysql import \
    BIGINT, BINARY, BIT, BLOB, BOOLEAN, CHAR, DATE, \
    DATETIME, DECIMAL, DECIMAL, DOUBLE, ENUM, FLOAT, INTEGER, \
    LONGBLOB, LONGTEXT, MEDIUMBLOB, MEDIUMINT, MEDIUMTEXT, NCHAR, \
    NUMERIC, NVARCHAR, REAL, SET, SMALLINT, TEXT, TIME, TIMESTAMP, \
    TINYBLOB, TINYINT, TINYTEXT, VARBINARY, VARCHAR, YEAR


db_type = 'mysql'
user = 'dblab'
password = 'dblab'
host = 'localhost'
port = '3306'
db_name = 'db_lab'

def get_engine():
    connect_str = "{}+pymysql://{}:{}@{}:{}/{}?charset=utf8mb4".format(db_type, user, password, host, port, db_name)
    engine = create_engine(connect_str, encoding='utf-8')
    return engine

eng = get_engine()
Base = declarative_base()
Session = sessionmaker(bind=eng)
db_session = Session()
metadata = MetaData(get_engine())

# staff
staff = Table("staff", metadata,
                # critical info
                Column("sno", INTEGER, primary_key=True, index=True, nullable=False, autoincrement=True),
                Column("sname", CHAR(10), nullable=False),
                Column("type", INTEGER, nullable=False),
                # personal info
                Column("age", INTEGER),
                Column("gender", TINYINT, default=None),
                # account info
                Column("account", CHAR(12)),
                Column("password", CHAR(12)),
                )

# buyer
buyer = Table("buyer", metadata,
                Column("bno", INTEGER, ForeignKey('staff.sno'), primary_key=True, index=True, nullable=False),
                )
# TODO: 触发器

# seller
seller = Table("seller", metadata,
                Column("sno", INTEGER, ForeignKey('staff.sno'), primary_key=True, index=True, nullable=False),
                )

# auditor
auditor = Table("auditor", metadata,
                Column("ano", INTEGER, ForeignKey('staff.sno'), primary_key=True, index=True, nullable=False),
                )

# good
good = Table("good", metadata,
                # 货品号
                Column("gno", INTEGER, primary_key=True, index=True, nullable=False, autoincrement=True),
                # 货品名
                Column("gname", CHAR(10), nullable=False),
                # 存放地
                Column("gplace", CHAR(10), nullable=False),
                # 货品库存量
                Column("gnum", INTEGER, nullable=False),
                # 生产厂家
                Column("gmanu", CHAR(10), nullable=False),
                # 缺货记号
                Column("gen", TINYINT, default=None),
                )

# purchase order
p_order = Table("p_order", metadata,
                Column("pono", INTEGER, primary_key=True, index=True, nullable=False, autoincrement=True),
                Column("bno", INTEGER, ForeignKey('buyer.bno'), index=True, nullable=False),
                Column("gno", INTEGER, ForeignKey('good.gno'), index=True, nullable=False),
                Column("gnum", INTEGER, nullable=False),
                Column("ano", INTEGER, ForeignKey('auditor.ano'), index=True, default=None),
                Column("has_audi", TINYINT, default=None),
                Column("date", DATETIME, nullable=False),
                )

# shipment order
s_order = Table("s_order", metadata,
                Column("sono", INTEGER, primary_key=True, index=True, nullable=False, autoincrement=True),
                Column("sno", INTEGER, ForeignKey('seller.sno'), index=True, nullable=False),
                Column("gno", INTEGER, ForeignKey('good.gno'), index=True, nullable=False),
                Column("gnum", INTEGER, nullable=False),
                Column("ano", INTEGER, ForeignKey('auditor.ano'), index=True, default=None),
                Column("has_audi", TINYINT, default=None),
                Column("date", DATETIME, nullable=False),
                )

metadata.create_all()
