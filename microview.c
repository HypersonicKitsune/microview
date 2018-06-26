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
    g_signal_connect(G_OBJECT(menuquit), "activate", (GCallback)gtk_main_quit, NULL);
	gtk_widget_show_all(main_window);

	// main
	gtk_main();

	return EXIT_SUCCESS;
}
