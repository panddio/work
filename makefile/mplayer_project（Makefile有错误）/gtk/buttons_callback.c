#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>
#include "sungtk_interface.h"
#include "mplayer_ui.h"
#include "buttons_callback.h"

void music_buttons_callback(GtkButton *button, gpointer data)
{
	WINDOW *p_ui = (WINDOW *)data;
	
	if(button == p_ui->hbox_right.button_pause ) // 赞同或播放
	{
		printf("p_ui->button_pause\n");
		
		if(mplayer.playflag)  // 正在播放，则暂停
		{
			write(mplayer.fd_pipe, "pause\n", strlen("pause\n"));
			mplayer.playflag = stop;
					
			GtkWidget *image = gtk_image_new_from_file("./image/style/pause.bmp"); // 图像控件
			gtk_button_set_image(p_ui->hbox_right.button_pause, image);			
		}
		else //否则，开启播放
		{
			write(mplayer.fd_pipe, "pause\n", strlen("pause\n"));
			mplayer.playflag = playing;
					
			GtkWidget *image = gtk_image_new_from_file("./image/style/play.bmp"); // 图像控件
			gtk_button_set_image(p_ui->hbox_right.button_pause, image);					
		}		
	}
	else if(button == p_ui->hbox_right.button_forward ) // 快进
	{	
		write(mplayer.fd_pipe, "seek -10\n", strlen("seek 10\n"));
	}	
	else if(button == p_ui->hbox_right.button_backward)   // 快退
	{		
		write(mplayer.fd_pipe, "seek -10\n", strlen("seek -10\n"));
	}	
	else if(button == p_ui->hbox_right.button_next) //下一曲
	{
		
	}
	else if(button == p_ui->hbox_right.button_back) //上一曲
	{
		
	}
	else if(button == p_ui->hbox_right.button_volume) //静音键
	{
		
	}
	else
	{
		
	}
}