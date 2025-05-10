Win + R ： 输入 regedit
根据图片操作


C:\Program Files
盘下所有有关360的东西全部删除


Win+R输入
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings" /v FlightSettingsMaxPauseDays /t reg_dword /d 36500 /f
然后前往更新界面选择自己的更新推迟时间就会有惊喜


