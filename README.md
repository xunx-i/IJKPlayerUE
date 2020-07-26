# IJKPlayerUE
基于bilibili开源项目 ijkplayer 的一个UE4视频播放器插件。
如果你在使用中发现了任何BUG欢迎提交issues

# Introduction
1. 如果需要支持各种直播流的解析播放，自行下载 ijkplayer 编译成库。
2. UI 引用于 jjdxm_ijkplayer 项目，仅作了一点修改并且将ijkplayer更新到了最新的0.8.8。
2020-7-15

	1，修复了更换播放源播放位置异常的BUG。
	2，添加了RTSP和RTMP视频流的支持
	3，修改了解析JSON的方式，使用异步解析
	4，使用本地库

2020-7-2

	1，现在退出按钮可以直接关闭播放器了。

# link
jjdxm_ijkplayer: https://github.com/lingcimi/jjdxm_ijkplayer 
ijkplayer：https://github.com/Bilibili/ijkplayer
