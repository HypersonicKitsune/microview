#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

// useful macros (TODO add it in an other file ?)
#define GUI_PATH "./glade/gui.glade"

int main(int argc, char *argv[])
{
	GtkWidget  *main_window = NULL;
	GtkBuilder *builder     = NULL;
	GError     *error       = NULL;
	gchar      *gui_file    = NULL;
	
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

	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));

	// setting up the main window...

	g_signal_connect(G_OBJECT(main_window), "destroy", (GCallback)gtk_main_quit, NULL);
	gtk_widget_show_all(main_window);

	// main
	gtk_main();

	return EXIT_SUCCESS;
}
