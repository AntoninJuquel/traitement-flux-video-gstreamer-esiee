#include <gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int app(int argc, char* argv[])
{
    GstElement* pipeline;
    GstBus* bus;
    GstMessage* msg;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Build the pipeline */
    pipeline =
        gst_parse_launch
        ("gst-launch-1.0 -v d3d11screencapturesrc ! videoscale ! videorate ! video/x-raw,width=800,height=600,framerate=5/1  ! timeoverlay valignment=top halignment=center shaded-background=true ! tee name=t ! queue ! autovideosink t. ! queue ! videoconvert ! avimux ! filesink location=video.avi t. ! queue ! videoconvert ! openh264enc bitrate=500 ! rtph264pay ! rtpsink address=127.0.0.1 port=5000 ^",
            NULL);

    /* Start playing */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg =
        gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
            GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
        g_error("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
            "variable set for more details.");
    }

    /* Free resources */
    gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    return 0;
}

int
main(int argc, char* argv[])
{
#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
    return gst_macos_main(app, argc, argv, NULL);
#else
    return app(argc, argv);
#endif
}