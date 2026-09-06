#include <gst/gst.h>

class AppContext {
public:
  GstElement *pipeline = nullptr;
  GstBus *bus = nullptr;
  GstMessage *msg = nullptr;
  gboolean is_livestream;
  GMainLoop *mainLoop = nullptr;


  AppContext() {}
  ~AppContext() {
    // When expanding: check docs as to whether we own the reference
    if(mainLoop) {
      g_main_loop_unref(mainLoop);
    }
    if(msg) {
      gst_message_unref(msg);
    }
    if(bus) {
      gst_object_unref(bus);
    }
    if(pipeline) {
      gst_element_set_state(pipeline, GST_STATE_NULL);
      gst_object_unref(pipeline); 
    }
  }
};

static void cb_message(GstBus *bus, GstMessage *msg, AppContext *c) {
  switch(GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_ERROR: {
      GError *err;
      gchar *debug;

      gst_message_parse_error (msg, &err, &debug);
      g_print ("Error: %s\n", err->message);
      g_error_free (err);
      g_free (debug);

      gst_element_set_state(c->pipeline, GST_STATE_READY);
      g_main_loop_quit(c->mainLoop);
      break;
    }
    case GST_MESSAGE_EOS: {
      gst_element_set_state (c->pipeline, GST_STATE_READY);
      g_main_loop_quit (c->mainLoop);
      break;
    }
    case GST_MESSAGE_BUFFERING: {
      gint percent = 0;

      if(c->is_livestream) break;

      gst_message_parse_buffering (msg, &percent);
      g_print ("Buffering (%3d%%)\r", percent);
      
      if (percent < 100) {
        gst_element_set_state (c->pipeline, GST_STATE_PAUSED);
      }
      else {
        gst_element_set_state (c->pipeline, GST_STATE_PLAYING);
      }
      break;
    }
    case GST_MESSAGE_CLOCK_LOST: {
      gst_element_set_state (c->pipeline, GST_STATE_PAUSED);
      gst_element_set_state (c->pipeline, GST_STATE_PLAYING);
      break;
    }
    defualt: {
      break;
    }
  }
}

int main(int argc, char** argv) {
  gst_init(&argc, &argv);
  AppContext c;

  c.pipeline = gst_parse_launch("playbin uri=file:///home/stfn/test_media/sintel_trailer-480p.webm", NULL);
  c.bus = gst_element_get_bus(c.pipeline);

  GstStateChangeReturn goplay = gst_element_set_state(c.pipeline, GST_STATE_PLAYING);
  if(goplay == GST_STATE_CHANGE_FAILURE) {
    g_printerr("Unable to set the pipeline to the playing state.\n");
    gst_object_unref(c.pipeline);
    return -1;
  } else if (goplay == GST_STATE_CHANGE_NO_PREROLL) {
    // When we get a livestream, the transition into paused gives this return value. The pipeline FSM must go: READY -> PAUSED -> PLAYING
    c.is_livestream = TRUE;
  }

  c.mainLoop = g_main_loop_new(NULL, false);

  gst_bus_add_signal_watch(c.bus);
  g_signal_connect(c.bus, "message", G_CALLBACK(cb_message), &c);

  g_main_loop_run(c.mainLoop);

  return 0;
}
