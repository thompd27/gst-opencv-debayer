plugin_LTLIBRARIES = libgstopencvdebayer.la

# Path to installation of opencv
OPENCV_CXXFLAGS = -I/usr/include
OPENCVCXX_LIBS = -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -L/usr/lib

# sources used to compile this plug-in
libgstopencvdebayer_la_SOURCES = gstopencvdebayer.cpp

libgstopencvdebayer_la_CXXFLAGS = \
	$(GST_PLUGINS_BASE_CFLAGS) $(GST_CFLAGS) $(GST_BASE_CFLAGS) $(GST_CXXFLAGS) $(OPENCV_CFLAGS) $(OPENCV_CXXFLAGS)

# flags used to compile this facedetect
# add other _CFLAGS and _LIBS as needed
#
# override CV_INLINE: GLib will take care of defining 'inline' sufficiently and
# OpenCV's define isn't good enough to avoid 'unused' gcc warnings (at v2.1.0)
#libgstopencv_la_CFLAGS = $(GST_PLUGINS_BASE_CFLAGS) $(GST_BASE_CFLAGS) \
#	$(GST_CFLAGS) $(OPENCV_CFLAGS) \
#	-DCV_INLINE="static inline" \
#	-DCV_NO_BACKWARD_COMPATIBILITY

libgstopencvdebayer_la_LIBADD = \
	$(GST_LIBS) $(GST_BASE_LIBS) $(OPENCV_LIBS) \
	$(GSTPB_BASE_LIBS) -lgstvideo-$(GST_API_VERSION) $(OPENCVCXX_LIBS)

libgstopencvdebayer_la_LDFLAGS = \
	$(GST_PLUGIN_LDFLAGS) $(GST_LIB_LDFLAGS) $(GST_ALL_LDFLAGS) $(GST_LT_LDFLAGS)

# headers we need but don't want installed
noinst_HEADERS = \
		gstopencvdebayer.h
