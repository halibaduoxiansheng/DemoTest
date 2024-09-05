import itchat
import pandas as pd

@itchat.msg_register(itchat.content.RECORDING, isGroupChat=True)
def receive_excel(msg):
    file_name = msg['FileName']
    # 从消息中获取文件名

    if file_name.endswith('.xlsx') or file_name.endswith('.xls'):
        msg['Text'](file_name)
        # 保存文件

        df = pd.read_excel(file_name)
        # 读取 excel 表格

        # 填入你需要处理的逻辑，例如将数据插入数据库或者执行其他操作
        # ...

        itchat.send_msg('信息已处理完毕！', msg['FromUserName'])
        # 发送消息通知处理结果

itchat.auto_login(hotReload=True)
itchat.run()