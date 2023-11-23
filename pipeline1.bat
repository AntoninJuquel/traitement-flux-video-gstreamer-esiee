gst-launch-1.0 -v ^
    d3d11screencapturesrc ^
        ! videoscale ^
        ! videorate ^
        ! video/x-raw,width=800,height=600,framerate=5/1  ^
        ! timeoverlay valignment=top halignment=center shaded-background=true ^
        ! tee name=t ^
            ! queue ^
            ! autovideosink ^
        t. ^
            ! queue ^
            ! videoconvert ^
            ! avimux ^
            ! filesink location=video.avi ^
        t. ^
            ! queue ^
            ! videoconvert ^
            ! openh264enc bitrate=500 ^
            ! rtph264pay ^
            ! rtpsink address=127.0.0.1 port=5000 ^
