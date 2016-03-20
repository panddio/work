
function my_fun(action)
{
	var sendData = action;
	
	loadData(sendData);
}

function loadData(sendData)
{
	var xmlhttp = null;

	var url = "/cgi-bin/sql_cgi.cgi?";
	url += sendData;	// url = "/cgi-bin/_cgi2.cgi?1+2"
	
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
			
				var data = xmlhttp.responseText;
				var temp = data.split(":");

				var i = 0;
				var line = 0;
				while(temp[i+3] != null)
				{
					var x=document.getElementById("table").insertRow(line);
					var y=x.insertCell(0);
					var z=x.insertCell(1);
					var t=x.insertCell(2);
					
					y.innerHTML= temp[i];
					z.innerHTML= temp[i+1];
					t.innerHTML= temp[i+2];
					i=i+3;
					line++;
				}
				
		}
	}
	
	xmlhttp.open("GET",url,true);	// 建立连接请求
	xmlhttp.setRequestHeader("If-Modified-Since", "0");//清除缓存
	xmlhttp.send();	 // 向服务器发送请求，先open()，才能再调用send();
}          