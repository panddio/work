var data=[
{name:'xiaoxiao',age:12,gender:'male'},
{name:'xiao',age:22,gender:'male'},
{name:'hh',age:12,gender:'female'},
{name:'ran',age:20,gender:'female'}]; 

//��ҳ������ɺ�ִ�и�onload�¼� 
function create_table(db)
{ 
	sendMsg(db);
	var body=document.getElementsByTagName('body')[0]; 
	body.appendChild(createTable(data));
	
}; 

//���ݴ����json���鴴����� 
var createTable = function(data)
{ 
	//������ 
	var table=document.createElement('table'); 
	table.setAttribute('style','width: 450px;'); 

	//��������� 
	var caption=document.createElement('caption'); 
	caption.innerHTML ='ѧ����Ϣ��'; 

	//��������ӽ���� 
	table.appendChild(caption); 
	//����createTr()�������ɱ����в�������ӵ�table�С� 
	table.appendChild(createTr('����','����','�Ա�')); 
	table.childNodes[1].setAttribute('style','background:#cae8ea;'); 

	//alert(table.firstChild); 
	//forѭ��json����,Ȼ��ѭ�����Ķ���ͨ��createTr()���������У���ӵ�table�� 
	for(var i=0;i<data.length;i++){ 
	table.appendChild(createTr(data[i].name,data[i].age,data[i].gender)); 
	} 
	return table; 
}; 


//�����û��������ı������ɱ�����еķ��� 
var createTr = function(name,age,gender){ 
	//������Ԫ�ر�ǩ 
	var tr=document.createElement('tr'); 
	//������Ԫ�ر�ǩ 
	var tdName=document.createElement('td'); 
	//���ø��нڵ���ı��ڵ��ֵ 
	tdName.innerHTML = name; 
	var tdAge = document.createElement('td'); 

	tdAge.innerHTML = age; 
	var tdGender = document.createElement('td'); 

	tdGender.appendChild(document.createTextNode(gender));//�ȼ��� tdGender.innerHTML = gender; 
	//����ֵ��ӵ���Ԫ�ؽڵ� 
	tr.appendChild(tdName); 
	tr.appendChild(tdAge); 
	tr.appendChild(tdGender); 

	//�������ɵ��б�ǩ 
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
	_table.cgi: Ϊcgi��ִ�г��򣬼���cgi����Ϊdemo.c ,����ͨ�� gcc demo.c -o _table.cgi �������
	_table.cgi��ע�������ִ�г����ŵ�·�������� www ���Ǹ� cgi-bin Ŀ¼��
	_table.cgi?, ����� "?" ������
	url += sendData;  �൱��������ôһ������ url="/cgi-bin/_table.cgi?db_name"
	 */
	var url = "/cgi-bin/_table.cgi?";
	url += sendData;	// url = "/cgi-bin/_table.cgi?1+2"

	// ƥ�������
	if (window.XMLHttpRequest)
	{// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	
	// function()Ϊ�ص���������������(״̬�ı�)������Ϣʱ���Զ����ã��Ա�GTK��"�ź���ص�����"
	xmlhttp.onreadystatechange=function()
	{	
		// readyState������״̬��4 �������
		// status����������HTTP״̬�루200��ӦOK��404��ӦNot Found��δ�ҵ�����
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			// xmlhttp.responseText, ����������Ӧ(�����������ص�����)����ʾΪһ���ַ���
			// ���ﱣ�� cgi �� printf() ���͹���������
			var resp = xmlhttp.responseText;
			
			alert(resp);
			//my_fun();

		}
	}
	
	/* 	�����Է�����������
		GET: ͨ��"GET"����������"POST"����
		url·�������·�����߾���·��
		true,�첽��false,ͬ��*/
	xmlhttp.open("GET",url,true);	// ������������
	xmlhttp.setRequestHeader("If-Modified-Since", "0");//�������
	xmlhttp.send();	 // �����������������open()�������ٵ���send();
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