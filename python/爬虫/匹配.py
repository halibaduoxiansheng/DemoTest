import re
#   修改文件成功  后续大可能还是需要
# 打开文件并读取内容
with open('C:/Users/86199/Desktop/didi.txt', 'r', encoding='utf-8', errors='ignore') as file:
    content = file.read()

# 使用正则表达式找到每个选项并修改其value属性
pattern = r'<option\s+value\s*=\s*"(.*?)">\s*(.*?)\s*<\/option>'
counter = 1
matches = re.findall(pattern, content)
for match in matches:
    old_option = match[0]
    option_text = match[1].strip()  # 去除空白符号
    new_option = f'<option value="{counter}">{option_text}</option>'
    content = content.replace(f'<option value="{old_option}">{option_text}</option>', new_option)
    counter += 1

# 将修改后的内容写回文件
with open('C:/Users/86199/Desktop/didi.txt', 'w', encoding='utf-8') as file:
    file.write(content)