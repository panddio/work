/* ************************************************************************
 *       Filename:  gtk_button.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月10日 10时14分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <gtk/gtk.h>
#include <glade/glade.h>
#include "sungtk_interface.h"
#include "mplayer_ui.h"
#include "buttons_callback.h"

MPLAYER mplayer;

static int hbox_left_init(WINDOW *p_ui)
{
	//创建GtkBuilder对象，GtkBuilder在<gtk/gtk.h>声明
	//读取test.glade文件的信息，保存在builder中   
	GtkBuilder *builder = gtk_builder_new(); 
	if(!gtk_builder_add_from_file(builder,"Mplayer.glade", NULL)) 
	{  
		printf("connot Mplayer.glade file!");  
		return(-1);
	} 
	
	p_ui->hbox_left.bmusic_list     = GTK_BUTTON(gtk_builder_get_object(builder, "bmusic_list"));
	p_ui->hbox_left.bmusic_collect  = GTK_BUTTON(gtk_builder_get_object(builder, "bmusic_collect"));
	p_ui->hbox_left.bmusic_recently = GTK_BUTTON(gtk_builder_get_object(builder, "bmusic_recently"));
	
	p_ui->hbox_left.eventbox_music  = (GtkEventBox *)(gtk_builder_get_object(builder, "eventbox_music"));
	gtk_event_box_set_visible_window(p_ui->hbox_left.eventbox_music, FALSE);
	
	return 0;
}

static int hbox_right_init(WINDOW *p_ui)
{
	//创建GtkBuilder对象，GtkBuilder在<gtk/gtk.h>声明
	//读取test.glade文件的信息，保存在builder中   
	GtkBuilder *builder = gtk_builder_new();
	if(!gtk_builder_add_from_file(builder,"Mplayer.glade", NULL))  
	{  
		printf("connot Mplayer.glade file!");  
		return(-1);
	} 

#if 1 // 获取按键空间并初始化
	p_ui->hbox_right.button_pause   = GTK_BUTTON(gtk_builder_get_object(builder, "button_pause"));
	p_ui->hbox_right.button_back    = GTK_BUTTON(gtk_builder_get_object(builder, "button_back"));
	p_ui->hbox_right.button_next    = GTK_BUTTON(gtk_builder_get_object(builder, "button_next"));
	p_ui->hbox_right.button_backward= GTK_BUTTON(gtk_builder_get_object(builder, "button_backward"));
	p_ui->hbox_right.button_forward = GTK_BUTTON(gtk_builder_get_object(builder, "button_forward"));
	p_ui->hbox_right.button_volume  = GTK_BUTTON(gtk_builder_get_object(builder, "button_volume"));
	
	sungtk_button_inset_image(GTK_WIDGET(p_ui->hbox_right.button_back),    "./image/style/back.png",70,70);	
	sungtk_button_inset_image(GTK_WIDGET(p_ui->hbox_right.button_pause),   "./image/style/play.jpg",70,70);
	sungtk_button_inset_image(GTK_WIDGET(p_ui->hbox_right.button_next),    "./image/style/next.png",70,70);	
	sungtk_button_inset_image(GTK_WIDGET(p_ui->hbox_right.button_backward),"./image/style/backward.png",60,60);
	sungtk_button_inset_image(GTK_WIDGET(p_ui->hbox_right.button_forward), "./image/style/forward.png",60,60);
	
	g_signal_connect(p_ui->hbox_right.button_pause,    "clicked", G_CALLBACK(music_buttons_callback), p_ui);
	g_signal_connect(p_ui->hbox_right.button_back,     "clicked", G_CALLBACK(music_buttons_callback), p_ui);
	g_signal_connect(p_ui->hbox_right.button_next,     "clicked", G_CALLBACK(music_buttons_callback), p_ui);
	g_signal_connect(p_ui->hbox_right.button_backward, "clicked", G_CALLBACK(music_buttons_callback), p_ui);
	g_signal_connect(p_ui->hbox_right.button_forward,  "clicked", G_CALLBACK(music_buttons_callback), p_ui);
	g_signal_connect(p_ui->hbox_right.button_volume,   "clicked", G_CALLBACK(music_buttons_callback), p_ui);
#endif	

#if 1 //获取label
	p_ui->hbox_right.label_head1 = GTK_LABEL(gtk_builder_get_object(builder, "label_head1"));
	p_ui->hbox_right.label_head2 = GTK_LABEL(gtk_builder_get_object(builder, "label_head2"));
	p_ui->hbox_right.label_head3 = GTK_LABEL(gtk_builder_get_object(builder, "label_head3"));
	
	p_ui->hbox_right.label_lrc1 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc1"));
	p_ui->hbox_right.label_lrc2 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc2"));
	p_ui->hbox_right.label_lrc3 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc3"));
	p_ui->hbox_right.label_lrc4 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc4"));
	p_ui->hbox_right.label_lrc5 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc5"));
	p_ui->hbox_right.label_lrc6 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc6"));
	p_ui->hbox_right.label_lrc7 = GTK_LABEL(gtk_builder_get_object(builder, "label_lrc7"));	
	
	p_ui->hbox_right.label_time_cur = GTK_LABEL(gtk_builder_get_object(builder, "label_time_cur"));
	p_ui->hbox_right.label_time_end = GTK_LABEL(gtk_builder_get_object(builder, "label_time_end"));	
#endif	

	p_ui->hbox_right.eventbox_bar    = (GtkEventBox *)(gtk_builder_get_object(builder, "eventbox_bar"));
	p_ui->hbox_right.eventbox_volume = (GtkEventBox *)(gtk_builder_get_object(builder, "eventbox_volume"));
	gtk_event_box_set_visible_window(p_ui->hbox_right.eventbox_bar,   FALSE);
	gtk_event_box_set_visible_window(p_ui->hbox_right.eventbox_volume,FALSE);
	
	p_ui->hbox_right.image_logo = GTK_IMAGE(gtk_builder_get_object(builder, "image_logo"));
	sungtk_image_load_picture(GTK_WIDGET(p_ui->hbox_right.image_logo), "./image/style/picture.png", 130, 130);	
	
	return 0;
}

static int window_init(WINDOW *p_ui)
{
	//创建GtkBuilder对象，GtkBuilder在<gtk/gtk.h>声明
	//读取test.glade文件的信息，保存在builder中 
	GtkBuilder *builder = gtk_builder_new(); //创建GtkBuilder对象，GtkBuilder在<gtk/gtk.h>声明
	if(!gtk_builder_add_from_file(builder,"Mplayer.glade", NULL)) //读取test.glade文件的信息，保存在builder中   
	{  
		printf("connot Mplayer.glade file!");  
		return -1;
	}     
	
	//获取窗口指针，注意"main_window"要和glade里面的标签名词匹配
	p_ui->main_window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
	
 	gtk_window_set_title(GTK_WINDOW(p_ui->main_window), "Mplayer");	              // 设置窗口标题
	gtk_window_set_position(GTK_WINDOW(p_ui->main_window), GTK_WIN_POS_CENTER);   // 设置窗口在显示器中的位置为居中
	gtk_widget_set_size_request(p_ui->main_window, 800, 480);		 	          // 设置窗口的最小大小
	gtk_window_set_resizable(GTK_WINDOW(p_ui->main_window), FALSE); 	          // 固定窗口的大小
	//gtk_window_set_decorated(GTK_WINDOW(p_ui->main_window), FALSE);             // 设置无边框
	g_signal_connect(p_ui->main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	
	sungtk_background_set_picture(p_ui->main_window,"./image/background/22.jpg",800, 480);	// 设置窗口背景图	
	return 0;
}

void mplayer_ui_show(int argc, char *argv[])
{
	int ret = 0;
	WINDOW ui;
	
	gtk_init(&argc, &argv);
 
	window_init(&ui);
	hbox_left_init(&ui);
	hbox_right_init(&ui);
	
	gtk_widget_show_all(ui.main_window);
	gtk_main();
}
