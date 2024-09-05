import itchat

# 登录微信
itchat.auto_login(hotReload=True)

# 监听指定群聊
group_name = '群聊名称'

@itchat.msg_register(itchat.content.TEXT, isGroupChat=True)
def process_msg(msg):
    group = itchat.search_chatrooms(name=group_name)[0]
    if msg['FromUserName'] == group['UserName']:
        # 在这里编写需要执行的逻辑
        print('收到来自群聊的消息:', msg['Text'])

# 开始运行脚本
itchat.run()