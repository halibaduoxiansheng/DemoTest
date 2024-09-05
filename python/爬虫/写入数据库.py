import mysql.connector

# 连接到MySQL数据库
cnx = mysql.connector.connect(
    host="192.168.43.40",
    user="root",
    password="123456",
    database="alumninetwork"
)
cursor = cnx.cursor()

# 读取文本文件
with open('filename.txt', 'r') as file:
    lines = file.readlines()

# 执行批量插入
for line in lines:
    # 解析文本行数据
    data = line.strip().split(' ')
    value = data[0]
    content = ' '.join(data[1:])

    # 构建插入语句
    query = "INSERT INTO bj (num, name) VALUES (%s, %s)"
    values = (value, content)

    # 执行插入语句
    cursor.execute(query, values)

# 提交事务并关闭连接
cnx.commit()
cursor.close()
cnx.close()