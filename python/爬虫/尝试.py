# 用户班级数据
# 打开文本文件进行读取
with open('C:/Users/86199/Desktop/didi.txt', 'r', encoding='utf-8', errors='ignore') as file:
    lines = file.readlines()

# 处理每一行数据，生成INSERT INTO语句
insert_statements = []
for line in lines:
    data = line.strip().split(' ')
    num = data[0]
    name = ' '.join(data[1:])
    insert_statement = f'INSERT INTO bj (num, name) VALUES ({num}, "{name}");'
    insert_statements.append(insert_statement)

# 将生成的INSERT INTO语句写入新的文本文件
with open('C:/Users/86199/Desktop/didi.txt', 'w',encoding='utf-8', errors='ignore') as output_file:
    for statement in insert_statements:
        output_file.write(statement + '\n')