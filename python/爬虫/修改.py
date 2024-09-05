import re

# 读取文本文件
with open('C:/Users/86199/Desktop/didi.txt', 'r', encoding='utf-8', errors='ignore') as file:
    text = file.read()

# 提取<option>标签中的value属性值和中间文字
pattern = r'<option value="(.*?)">(.*?)</option>'
matches = re.findall(pattern, text)

# 对每个匹配项进行修改
modified_text = ""
for match in matches:
    value = match[0]
    content = match[1]

    # 进行修改
    # 这里给出的是保留value属性值和中间文字的示例修改方法
    modified_content = f'{value} {content}'

    # 更新修改后的文本
    modified_text += modified_content + '\n'

# 将修改后的文本写入新文件
with open('C:/Users/86199/Desktop/didi.txt', 'w', encoding='utf-8') as file:
    file.write(modified_text)