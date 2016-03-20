
function window_login_exit()
{
	window.location.href = "index.html";
}

function window_check_login()
{
	var name = "admin";
	var passwd = "123456";
	
	if(document.getElementById("user").value && document.getElementById("pwd").value){
		window.location.href = "inquire.html";
	}
	else {
		
		alert("entry error");
	}
}

function window_close()
{
	window.close();//关闭当前窗口
}
