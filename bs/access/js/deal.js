function placeholderChange(select_id, input_id)
{
	var objS = document.getElementById(select_id);
	var id = objS.options[objS.selectedIndex].id;
	
	var obj = document.getElementById(input_id);
	obj.placeholder=id;
}
// 1: �¿�ע��
// 2��ע���ɿ�
// 3����ѯ��Ϣ
// 4��������Ϣ

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
	loadData(sendData);	// ���ӣ�sendData = "1+2"
}

function loadData(sendData)
{
	var xmlhttp = null;
	
	/*
	access.cgi: Ϊcgi��ִ�г��򣬼���cgi����Ϊdemo.c ,����ͨ�� gcc demo.c -o access.cgi �������
	access.cgi��ע�������ִ�г����ŵ�·�������� www ���Ǹ� cgi-bin Ŀ¼��
	access.cgi?, ����� "?" ������
	url += sendData;  �൱��������ôһ������ url="/cgi-bin/access.cgi?1+2"
	 */
	var cmd = encodeURI(sendData);
	var url = "./cgi-bin/access.cgi?";
	url += cmd;	// url = "/cgi-bin/access.cgi?1+2"

	alert(url);
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
	
	/* 	�����Է�����������
		GET: ͨ��"GET"����������"POST"����
		url·�������·�����߾���·��
		true,�첽��false,ͬ��*/
	xmlhttp.open("GET",url,true);	// ������������
	xmlhttp.setRequestHeader("If-Modified-Since", "0");//�������
	xmlhttp.send();	 // �����������������open()�������ٵ���send();
}