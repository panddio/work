var selected_num = 0;
function sbilink_change(action)
{
	var i = 0;	
	var a = "";	
	var id = new Array("sbilink1", "sbilink2" , "sbilink3", "sbilink4");
	
	a = document.getElementById("sbilink_selected");
	a.id = id[selected_num];
	
	for(i=0;i<id.length;i++){
		
		if(i == action){
			a = document.getElementById(id[i]);
			a.id = "sbilink_selected";
			selected_num = i;
		}
		else{
			a = document.getElementById(id[i]);
			a.id = id[i];
		}
	}
}

var i = 0;
var time=2000;//5秒更改
function mothed(){
	if(i==0) document.getElementById("color-change").style.color='#9ACD32';
	else if(i==1)document.getElementById("color-change").style.color='#A020F0';	
	else if(i==2)document.getElementById("color-change").style.color='#FF0000';
	else if(i==3)document.getElementById("color-change").style.color='#8B6914';
	else if(i==4)document.getElementById("color-change").style.color='#CE7014';
	i=i+1;
	if(i==5){
	i=0;}
}
setInterval(mothed,time);