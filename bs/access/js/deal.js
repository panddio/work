function placeholderChange(select_id, input_id)
{
	var objS = document.getElementById(select_id);
	var id = objS.options[objS.selectedIndex].id;
	
	var obj = document.getElementById(input_id);
	obj.placeholder=id;
}
// 1: 新卡注册
// 2：注销旧卡
// 3：查询信息
// 4：更新信息

function buttons_callback(action)
{
	var sendData = "";

	switch(action)
	{
		case 1:
		{
			sendData += "1:";
			var username = "";
	        var agentID = "";
			var sex = "";

			username = document.getElementById("name").value;
			agentID = document.getElementById("agentID").value;
			sex = document.getElementById("sex").value;
			
			sendData = sendData + username + ":" + agentID + ":" + sex;
			break;
		}
		case 2:
		{
			sendData += "2:";
			var agentID = document.getElementById("agentID").value;	
			sendData += agentID;
			break;
		}
		case 3:
		{
			sendData += "3:"
			var objS = document.getElementById("querysel");
			var id = objS.options[objS.selectedIndex].id;
			var text = document.getElementById("query").value;
			
			sendData = sendData + id + ":" + text;		
			break;
		}
		case 4:
		{
			sendData += "4:";
			
			var name = document.getElementById("username").value;
			var objS = document.getElementById("updsel");
			var id = objS.options[objS.selectedIndex].id;
			var text = document.getElementById("update").value;
			
			sendData = sendData + name + ":" + id + ":" + text;
			break;
		}
	}
	alert(sendData);
	loadData(sendData);	// 例子：sendData = "1+2"
}

function loadData(sendData)
{
	var xmlhttp = null;
	
	/*
	access.cgi: 为cgi可执行程序，假如cgi程序为demo.c ,最终通过 gcc demo.c -o access.cgi 编译而成
	access.cgi，注意这个可执行程序存放的路径，放在 www 里那个 cgi-bin 目录里
	access.cgi?, 后面的 "?" 别忘了
	url += sendData;  相当于组了这么一个包， url="/cgi-bin/access.cgi?1+2"
	 */
	var cmd = encodeURI(sendData);
	var url = "./cgi-bin/access.cgi?";
	url += cmd;	// url = "/cgi-bin/access.cgi?1+2"

	alert(url);
	// 匹配浏览器
	if (window.XMLHttpRequest)
	{// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	
	// function()为回调函数，当服务器(状态改变)返回信息时，自动调用，对比GTK的"信号与回调函数"
	xmlhttp.onreadystatechange=function()
	{	
		// readyState，加载状态，4 代表完成
		// status，服务器的HTTP状态码（200对应OK，404对应Not Found（未找到））
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			// xmlhttp.responseText, 服务器的响应(即服务器返回的数据)，表示为一个字符串
			// 这里保存 cgi 中 printf() 发送过来的数据
			var recv = xmlhttp.responseText;
			
			var temp = recv.split("$");
			
			if(temp[0] == "query")
			{
				alert("query");
				document.getElementById("dynamic").innerHTML = temp[1];
			}
			else{
				alert(recv);
			}
			
		}
	}
	
	/* 	建立对服务器的请求
		GET: 通过"GET"方法，还有"POST"方法
		url路径，相对路径或者绝对路径
		true,异步；false,同步*/
	xmlhttp.open("GET",url,true);	// 建立连接请求
	xmlhttp.setRequestHeader("If-Modified-Since", "0");//清除缓存
	xmlhttp.send();	 // 向服务器发送请求，先open()，才能再调用send();
}