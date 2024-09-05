import os

file_extensions = ['.java','.css', '.js', '.html', '.xml'] # 替换成自己需要的文件尾椎

root_directory = 'C:\\Users\\86199\\Desktop\\真正的毕业设计\\项目源码\\AlumniNetwork\\src'  # 修改为你的根目录路径
output_file = 'new.txt'

def remove_newlines(text):
    return text.replace('\n\n', '').replace('\r', '')

with open(output_file, 'w', encoding='utf-8') as outfile:
    for subdir, _, files in os.walk(root_directory):
        for file in files:
            if any(file.endswith(ext) for ext in file_extensions):
                file_path = os.path.join(subdir, file)
                with open(file_path, 'r', encoding='utf-8') as infile:
                    content = infile.read()
                    cleaned_content = remove_newlines(content)
                    outfile.write(cleaned_content)
                    outfile.write(" ")


