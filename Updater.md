# 场景描述
	client中有数个独立的模块，如app1, app2等，每个模块有对应的版本号, 管理员通过server的管理界面对终端的不同模块进行更新，查看和记录终端运行状态

	server  基于 Python 服务端框架 Tornado, 前端框架 Bootstrap, 数据库 MySQL
	client  c++
	利用 websocket 实现长连接通信

# 功能描述

- 客户端
		client进程启动后向服务器报告状态，判断是否更新(在第2点中描述),建立好长连接，server标记其为online状态
		{
			"device_id": ,
			"timestamp": ,
			version_list:[
				{
					"name": "app1",
					"version":版本号
				},
				{}, ...
			]
		}
		client进程每 30s 向服务器发送状态信息，包括(举例)
			{
				"timestamp":,
				"device_id"
				"cpu_utilization":,
				"load_average":,
				"sd_card":[
					{
						"name":"sdcard0",
						"total":,
						"used":,
						"free":,
					}
					{},...
				]
				"temprature":[
					{
						"type": "cpu",
						"degree":,
					}
					{},...
				]
				"status":[
					{
						"process": app1,
						"status":  			//终端上某个日志的内容，如 /sdcard0/app1/status.txt
					}
					{},...
				]
				//GPS INFO
				"location":[      
					"latitude":,
					"longtitude":,
					"altitude":,
				]
				//另有环境状况(天气), 车速等
			}
		server 在长连接中收到 状态报告后，将信息写入Log文件并更新数据库中该终端状态。
		Log格式
			timestamp, key_id
- 更新
		管理员选择待更新的软件包, 确认更新
		server 更新数据库中该软件包的当前版本号
		online
			服务器后台运行一个更新进程updater, 前端也可以显示更新进度
			updater遍历当前在线的所有设备，发出更新请求
				{
					"update_list":[
						{
							"app_name": app1,
							"version": 版本号,
						},
						{}, ...
					]
				}
			终端接收到后检查更新的版本号是否高于自身版本(是否支持回滚)，向服务端回复需更新的 update_list，格式同上
			server 收到 update_list 后进入更新流程，依次向终端推送更新软件包。
		offline
			client进程后向服务器报告状态，并附加所有模块版本信息
			{
				"device_id":,
				"timestamp":,
				"version_list":[
					{
						"app_name":app1,
						"version": 版本号
					}
					{}, ...
				]
			}
			server 收到后与 latest version 对比，便得到了与online状态时类似的update_list
- 管理界面
		管理员
			注册，登录 ? 需要吗
		软件包
			维护不同模块的软件包，包括name, version, package等，提供添加，删除操作
		更新
			选择若干模块的对应软件包，点击更新按钮，显示更新进度
			更新进度实际上是所有终端的列表

		name | state | app1_version | app1_state | app2_version | app2_state 
		-----|-------|--------------|------------|--------------|-----------
		终端1|online  |   当前版本	 |	是否更新   |	当前版本	 |	是否更新 

- 数据库
		表设计待讨论
		模块版本，终端状态等

# 技术实现
	- 管理界面


