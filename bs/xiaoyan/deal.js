
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
	
	xmlhttp.open("GET",url,true);	// ������������
	xmlhttp.setRequestHeader("If-Modified-Since", "0");//�������
	xmlhttp.send();	 // �����������������open()�������ٵ���send();
}          