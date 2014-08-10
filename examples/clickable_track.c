/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 cino=t0,(0: */
/*
 * clickable_track.c
 * Copyright (C) Martijn Goedhart 2014 <goedhart.martijn@gmail.com>
 *
 * This is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include "osm-gps-map.h"

void
point_selected(OsmGpsMapTrack *osmgpsmaptrack, OsmGpsMapPoint *point, gpointer user_data)
{
    printf("callback function; num: %d\n", (gint)(point->user_data));
}

int
main (int argc, char *argv[])
{
    OsmGpsMap *map;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    map = g_object_new(OSM_TYPE_GPS_MAP, NULL);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(map));

    OsmGpsMapTrack* track = osm_gps_map_track_new();

    OsmGpsMapPoint* p1, *p2;
    p1 = osm_gps_map_point_new_radians_with_user_data(1.25663706, -0.488692191, (gpointer)1);
    p2 = osm_gps_map_point_new_radians_with_user_data(1.06465084, -0.750491578, (gpointer)2);

    osm_gps_map_track_add_point(track, p1);
    osm_gps_map_track_add_point(track, p2);

    g_object_set(track, "clickable", TRUE, NULL);
    g_signal_connect(track, "point-selected", G_CALLBACK(point_selected), NULL);

    osm_gps_map_track_add(map, track);

    gtk_widget_show(GTK_WIDGET(map));
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
