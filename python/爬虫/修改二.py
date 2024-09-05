import re


def extract_info_from_file(file_path):
    # 读取文本文件内容
    with open('C:/Users/86199/Desktop/didi.txt', 'r', encoding='utf-8', errors='ignore') as file:
        file_content = file.read()

    # 使用正则表达式匹配并提取信息
    pattern = r'<a href="(.*?)">\s+<span class="wula">(.*?)</span>\s+<span class="wula">(.*?)</span>\s+</a>'
    matches = re.findall(pattern, file_content, re.DOTALL)

    # 输出提取的信息
    for match in matches:
        href = match[0]
        date = match[1]
        content = match[2]
        print("Href:", href)
        print("Date:", date)
        print("Content:", content)
        print()