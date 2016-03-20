#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>
#include "sungtk_interface.h"
#include "mplayer_ui.h"
#include "buttons_callback.h"

void music_buttons_callback(GtkButton *button, gpointer data)
{
	WINDOW *p_ui = (WINDOW *)data;
	
	if(button == p_ui->hbox_right.button_pause ) // ��ͬ�򲥷�
	{
		printf("p_ui->button_pause\n");
		
		if(mplayer.playflag)  // ���ڲ��ţ�����ͣ
		{
			write(mplayer.fd_pipe, "pause\n", strlen("pause\n"));
			mplayer.playflag = stop;
					
			GtkWidget *image = gtk_image_new_from_file("./image/style/pause.bmp"); // ͼ��ؼ�
			gtk_button_set_image(p_ui->hbox_right.button_pause, image);			
		}
		else //���򣬿�������
		{
			write(mplayer.fd_pipe, "pause\n", strlen("pause\n"));
			mplayer.playflag = playing;
					
			GtkWidget *image = gtk_image_new_from_file("./image/style/play.bmp"); // ͼ��ؼ�
			gtk_button_set_image(p_ui->hbox_right.button_pause, image);					
		}		
	}
	else if(button == p_ui->hbox_right.button_forward ) // ���
	{	
		write(mplayer.fd_pipe, "seek -10\n", strlen("seek 10\n"));
	}	
	else if(button == p_ui->hbox_right.button_backward)   // ����
	{		
		write(mplayer.fd_pipe, "seek -10\n", strlen("seek -10\n"));
	}	
	else if(button == p_ui->hbox_right.button_next) //��һ��
	{
		
	}
	else if(button == p_ui->hbox_right.button_back) //��һ��
	{
		
	}
	else if(button == p_ui->hbox_right.button_volume) //������
	{
		
	}
	else
	{
		
	}
}