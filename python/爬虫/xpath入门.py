# xpath 在XML文档里面查找内容
# html是xml的一个子集
# 通过结点之间的关系去查找某个结点
# 安装lxml模块 pip install lxml

# /book/price 语法规则
# lxml解析
from lxml import etree
xml = """
<book>
    <id>1</id>
    <name>野花遍地开</name>
    <price>1.23</price>
    <nick>豆腐</nick>
    <author>
        <nick id = "10086">周大强</nick>
        <nick id = "10087">王晓宇</nick>
        <nick class = "joy">周杰伦</nick>
        <nick class = "jolin">蔡依林</nick>
        <div>
            <nick>热了</nick>
        </div>
        <span>
            <nick>好了</nick>
        </span>
    </author>

    <partner>
        <nick id = "ppc">盘子</nick>
        <nick id = "ppb">丸子</nick>
    </partner>
</book>
"""
tree = etree.XML(xml)
# result = tree.xpath("/book")  # /表示层级关系
# result = tree.xpath("/book/name")
# result = tree.xpath("/book/name/text()")  # text() 是拿文本
# result = tree.xpath("/book/author//nick/text()")  # // 就是找其中的所有
# result = tree.xpath("/book/author/*/nick/text()")  # * 为任意结点
result = tree.xpath("/book//nick/text()")  # 所有nick都出来了

print(result)


