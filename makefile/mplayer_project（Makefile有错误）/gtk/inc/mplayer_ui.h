#ifndef __MPLAYER_UI_H__
#define __MPLAYER_UI_H__
#include <gtk/gtk.h>
#include <glade/glade.h>
typedef struct _hbox_list
{
	GtkButton *bmusic_list;
	GtkButton *bmusic_collect;
	GtkButton *bmusic_recently;
	
	GtkEventBox *eventbox_music;
}HBOX_LEFT;

typedef struct _hbox_show
{
	GtkImage *image_logo;
	
	GtkButton *button_back;
	GtkButton *button_next;
	GtkButton *button_pause;
	GtkButton *button_backward;
	GtkButton *button_forward;
	
	GtkImage *image_back;
	GtkImage *image_next;
	GtkImage *image_pause;
	GtkImage *image_backward;
	GtkImage *image_forward;
	
	GtkLabel *label_head1;
	GtkLabel *label_head2;
	GtkLabel *label_head3;
	
	GtkLabel *label_lrc1;
	GtkLabel *label_lrc2;
	GtkLabel *label_lrc3;
	GtkLabel *label_lrc4;
	GtkLabel *label_lrc5;
	GtkLabel *label_lrc6;
	GtkLabel *label_lrc7;
	
	GtkLabel *label_time_cur;
	GtkLabel *label_time_end;
	
	GtkWidget *progress_bar;	
	GtkEventBox *eventbox_bar;
	
	GtkButton *button_volume;
	GtkEventBox *eventbox_volume;
}HBOX_RIGHT;

typedef struct _window
{
	GtkWidget *main_window;
	GtkImage *image;
		
	HBOX_LEFT  hbox_left;
	HBOX_RIGHT hbox_right;
}WINDOW;

typedef enum
{
	stop = 0,
	playing = 1,
}PLAY_STATUS;

typedef struct _mplayer
{
	int fd_pipe;
	PLAY_STATUS playflag;
}MPLAYER;

extern MPLAYER mplayer;

extern void mplayer_ui_show(int argc, char *argv[]);

#endif
