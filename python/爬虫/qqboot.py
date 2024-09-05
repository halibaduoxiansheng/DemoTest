import time
from qqbot import QQBotSlot as qqbotslot, RunBot

@qqbotslot
def onQQMessage(bot, contact, member, content):
    # 判断消息类型为私聊或群聊
    if contact.ctype == 'buddy' or contact.ctype == 'group':
        # 设置你要回复的内容
        reply_content = '你好，我现在有事不在，稍后回复lala。'
        # 发送自动回复消息
        bot.SendTo(contact, reply_content)
        # 打印日志，方便调试
        print(f'Replied to {contact.name} ({content}) at {time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())}')

if __name__ == '__main__':
    # 运行 QQBot
    RunBot()