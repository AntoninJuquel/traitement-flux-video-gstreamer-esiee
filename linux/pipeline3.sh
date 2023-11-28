#!/bin/bash

gst-launch-1.0 -v \
    filesrc location="video.avi" \
    ! decodebin \
    ! videoconvert \
    ! autovideosink
