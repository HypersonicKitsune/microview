#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

// useful macros (TODO add it in an other file ?)
#define GUI_PATH "./glade/gui.glade"

// GTK widgets
GtkWidget  *main_window = NULL;
GtkWidget  *image       = NULL;
GtkWidget  *menuopen    = NULL;
GtkWidget  *menuquit    = NULL;

// GTK stuff
GtkBuilder *builder     = NULL;
GError     *error       = NULL;
gchar      *gui_file    = NULL;



/* static void on_open_image(GtkImageMenuItem *menuopen, gpointer user_data)
 * 
 * Called when clicking File -> Open; creates a dialog and loads images
 * TODO 1: Replace GtkStock with non-deprecated stuff!!!
 * TODO 2: Move it to an other file?
 */

static void on_open_image(GtkImageMenuItem *menuopen, gpointer user_data)
{
    GtkWidget *image = GTK_WIDGET(user_data);
	GtkWidget *toplevel = gtk_widget_get_toplevel(image);
    
	GtkFileFilter *filter = gtk_file_filter_new();
	GtkWidget *dialog = gtk_file_chooser_dialog_new(("Open image"),
	                                                GTK_WINDOW(toplevel),
	                                                GTK_FILE_CHOOSER_ACTION_OPEN,
	                                                GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
	                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                NULL);

	gtk_file_filter_add_pixbuf_formats(filter);
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

	switch (gtk_dialog_run (GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
			gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			gtk_image_set_from_file(GTK_IMAGE(image), filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(dialog);
}



/*** MAIN ***/

int main(int argc, char *argv[])
{	
	// setting up GTK
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();

	// loading the interface! \(^o^)/
	gui_file = g_build_filename(GUI_PATH, NULL);

	gtk_builder_add_from_file(builder, gui_file, &error);
	g_free(gui_file);
	if(error)
	{
		gint code = error -> code;
		g_printerr("%s\n", error -> message);
		g_error_free(error);
		return code;
	}

	// get widgets from builder
	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
   	image = GTK_WIDGET(gtk_builder_get_object(builder, "Image"));
   	menuopen = GTK_WIDGET(gtk_builder_get_object(builder, "Open"));
   	menuquit = GTK_WIDGET(gtk_builder_get_object(builder, "Quit"));

	// setting up the main window...
	g_signal_connect(G_OBJECT(main_window), "destroy", (GCallback)gtk_main_quit, NULL);
	g_signal_connect(G_OBJECT(menuopen), "activate", G_CALLBACK(on_open_image), image);
	g_signal_connect(G_OBJECT(menuquit), "activate", (GCallback)gtk_main_quit, NULL);
	gtk_widget_show_all(main_window);

	// main
	gtk_main();

	return EXIT_SUCCESS;
}
