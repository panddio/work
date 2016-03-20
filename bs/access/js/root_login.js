
function login_check()
{
	var rootname = "admin";
	var password = "123456";
	
	if(document.getElementById("rootname").value == rootname && 
	   document.getElementById("password").value == password){
		//window.close();
		//window.open("register.html");
		window.location.href("register.html");
	}
	else {
		alert("entry error");
	}
}