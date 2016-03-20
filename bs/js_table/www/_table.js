var data=[
{name:'xiaoxiao',age:12,gender:'male'},
{name:'xiao',age:22,gender:'male'},
{name:'hh',age:12,gender:'female'},
{name:'ran',age:20,gender:'female'}]; 

//网页加载完成后执行该onload事件 
function create_table(db)
{ 
	sendMsg(db);
	var body=document.getElementsByTagName('body')[0]; 
	body.appendChild(createTable(data));
	
}; 

//根据传入的json数组创建表格 
var createTable = function(data)
{ 
	//定义表格 
	var table=document.createElement('table'); 
	table.setAttribute('style','width: 450px;'); 

	//定义表格标题 
	var caption=document.createElement('caption'); 
	caption.innerHTML ='学生信息表'; 

	//将标题添加进表格 
	table.appendChild(caption); 
	//调用createTr()方法生成标题行并将其添加到table中。 
	table.appendChild(createTr('姓名','年龄','性别')); 
	table.childNodes[1].setAttribute('style','background:#cae8ea;'); 

	//alert(table.firstChild); 
	//for循环json对象,然后将循环到的对象通过createTr()方法生成行，添加到table中 
	for(var i=0;i<data.length;i++){ 
	table.appendChild(createTr(data[i].name,data[i].age,data[i].gender)); 
	} 
	return table; 
}; 


//根据用户传过来的变量生成表格中行的方法 
var createTr = function(name,age,gender){ 
	//定义行元素标签 
	var tr=document.createElement('tr'); 
	//定义列元素标签 
	var tdName=document.createElement('td'); 
	//设置该列节点的文本节点的值 
	tdName.innerHTML = name; 
	var tdAge = document.createElement('td'); 

	tdAge.innerHTML = age; 
	var tdGender = document.createElement('td'); 

	tdGender.appendChild(document.createTextNode(gender));//等价与 tdGender.innerHTML = gender; 
	//将列值添加到行元素节点 
	tr.appendChild(tdName); 
	tr.appendChild(tdAge); 
	tr.appendChild(tdGender); 

	//返回生成的行标签 
	return tr; 
}; 

function sendMsg(db)
{
	var sendData = "";
	
	if(db != ""){
		sendData += db;	
		loadData(sendData);
	}
}

function loadData(sendData)
{
	var xmlhttp = null;
	
	/*
	_table.cgi: 为cgi可执行程序，假如cgi程序为demo.c ,最终通过 gcc demo.c -o _table.cgi 编译而成
	_table.cgi，注意这个可执行程序存放的路径，放在 www 里那个 cgi-bin 目录里
	_table.cgi?, 后面的 "?" 别忘了
	url += sendData;  相当于组了这么一个包， url="/cgi-bin/_table.cgi?db_name"
	 */
	var url = "/cgi-bin/_table.cgi?";
	url += sendData;	// url = "/cgi-bin/_table.cgi?1+2"

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
			var resp = xmlhttp.responseText;
			
			alert(resp);
			//my_fun();

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
function my_fun()
{
	var text = "";
	alert("hehe");
	text += "<table border=1>";
	text += "<tr><td>id</td><td>name</td><td>addr</td></tr>";
	text += "<tr><td>1</td><td>lucy</td><td>sz</td></tr>";
	text += "<tr><td>2</td><td>bob</td><td>bj</td></tr>";
	text += "</table>";
	
	document.getElementById("copy").innerHTML = text;
}