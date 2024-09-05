import os

root_directory = 'C:\\Users\\86199\\Desktop\\真正的毕业设计\\项目源码\\AlumniNetwork\\src\\main\\java\\com\\halibaduo'  # 修改为你的根目录路径
output_file = 'new.txt'

def remove_newlines(text):
    return text.replace('\n\n', '').replace('\r', '')

with open(output_file, 'w', encoding='utf-8') as outfile:
    for subdir, _, files in os.walk(root_directory):
        for file in files:
            if file.endswith('.java'):
                file_path = os.path.join(subdir, file)
                with open(file_path, 'r', encoding='utf-8') as infile:
                    content = infile.read()
                    cleaned_content = remove_newlines(content)
                    outfile.write(cleaned_content)
                    outfile.write(" ")  # 添加空格以分隔不同文件内容
