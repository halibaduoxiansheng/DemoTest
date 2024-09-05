# lower()  #将str里面的字符全部转化为大写
# upper()  #将str里面的字符全部转化为小写
# 例： str.lower() 或则 str.upper()

# split() 根据逗号分割返回一个列表
# 例: "s, c, e".split()

# count()方法 返回在母字符串中现的次数
# str = "qwff fdsgdsvds"
# str1 = "s"
# print(str.count(str1))

# replace(str1, str2)方法 将str1替换成str2
# str1 = "abdfd"
# str1 = str1.replace("a", "hahaahhah")
# str2 = str1.replace("a", "hahahahah")
# print(str1, str2)

# center(width, [fillchar])函数 将字符串居中显示，width小于length时无影响
# 但是当等于length时，会将字符串居中显示,默认补充空格,当然可以选择补充的字符fillchar

# strip() 去除出现的字符，比replace能同时替换更多 但空格仍需要replace
# join(str) 在str中除去最后一个元素，其余所有的元素后面加上一个字符串
# 例： "p".join("abc")

# 字符串类型的格式化 format 槽来了

# {x}槽中的数字可以不写，写的话注意还是从0开始 要写就必须都写,要么就按照顺序来
# print("{0},{2},{1}".format("第一", "第二", "第三"))
# 用:控制输出格式 :<填充><对齐><宽度>
# <左对齐 >右对齐 ^中间对齐 例{0:=^20} 默认左对齐
# 千位分隔符,      .x 为保留小数个数
# c：字符形式 d：整数形式 f：浮点数形式 o：八进制 x：十六进制 b：二进制
# 例：{0:,.2f}
# {:e}或则{:E}用科学计数法 {:f}用浮点数 {:%}:用百分数形式表示

# print("abcd{1}das{0}".format(12,13))
# import jieba  # 中文分词库
# s = "中华人民共和国是个伟大的国家"
# jieba.lcut(s)

# 词云库  根据词的量来自动生成图片
# from wordcloud import WordCloud
# text = "cat fish dog bird cat bird dog dog"
# wc = WordCloud(background_color="white")
# wc.generate(text)
# wc.to_file("hello.png")

