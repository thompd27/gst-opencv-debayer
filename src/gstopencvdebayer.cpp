/* GStreamer
 * Copyright (C) 2019 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */
/**
 * SECTION:element-gstopencvdebayer
 *
 * The opencvdebayer element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! opencvdebayer ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>
#include "gstopencvdebayer.h"

GST_DEBUG_CATEGORY_STATIC (gst_opencvdebayer_debug_category);
#define GST_CAT_DEFAULT gst_opencvdebayer_debug_category

/* prototypes */


static void gst_opencvdebayer_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_opencvdebayer_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_opencvdebayer_dispose (GObject * object);
static void gst_opencvdebayer_finalize (GObject * object);

static gboolean gst_opencvdebayer_start (GstBaseTransform * trans);
static gboolean gst_opencvdebayer_stop (GstBaseTransform * trans);
static gboolean gst_opencvdebayer_set_info (GstVideoFilter * filter,
    GstCaps * incaps, GstVideoInfo * in_info, GstCaps * outcaps,
    GstVideoInfo * out_info);
static GstFlowReturn gst_opencvdebayer_transform_frame (GstVideoFilter * filter,
    GstVideoFrame * inframe, GstVideoFrame * outframe);
static GstCaps * gst_opencvdebayer_transform_caps (GstBaseTransform * trans, GstPadDirection dir,
  GstCaps * caps, GstCaps * filter);

enum
{
  PROP_0
};

/* pad templates */

#define VIDEO_SRC_CAPS \
    GST_VIDEO_CAPS_MAKE("{ BGRx }")

#define VIDEO_SINK_CAPS \
    GST_VIDEO_CAPS_MAKE("{ GRAY8 }")

static GstStaticPadTemplate gst_video_convert_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (VIDEO_SRC_CAPS)
    );

    static GstStaticPadTemplate gst_video_convert_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (VIDEO_SINK_CAPS)
    );


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstOpencvdebayer, gst_opencvdebayer,
    GST_TYPE_VIDEO_FILTER,
    GST_DEBUG_CATEGORY_INIT (gst_opencvdebayer_debug_category, "opencvdebayer",
        0, "debug category for opencvdebayer element"));

static void
gst_opencvdebayer_class_init (GstOpencvdebayerClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseTransformClass *base_transform_class =
      GST_BASE_TRANSFORM_CLASS (klass);
  GstVideoFilterClass *video_filter_class = GST_VIDEO_FILTER_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. 
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS (klass),
      gst_pad_template_new ("src", GST_PAD_SRC, GST_PAD_ALWAYS,
          gst_caps_from_string (VIDEO_SRC_CAPS)));
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS (klass),
      gst_pad_template_new ("sink", GST_PAD_SINK, GST_PAD_ALWAYS,
          gst_caps_from_string (VIDEO_SINK_CAPS)));*/
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass), &gst_video_convert_src_template);
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass), &gst_video_convert_sink_template);

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS (klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <fixme@example.com>");

  gobject_class->set_property = gst_opencvdebayer_set_property;
  gobject_class->get_property = gst_opencvdebayer_get_property;
  gobject_class->dispose = gst_opencvdebayer_dispose;
  gobject_class->finalize = gst_opencvdebayer_finalize;
  base_transform_class->start = GST_DEBUG_FUNCPTR (gst_opencvdebayer_start);
  base_transform_class->stop = GST_DEBUG_FUNCPTR (gst_opencvdebayer_stop);
  base_transform_class->transform_caps = gst_opencvdebayer_transform_caps;
  video_filter_class->set_info = GST_DEBUG_FUNCPTR (gst_opencvdebayer_set_info);
  video_filter_class->transform_frame =
      GST_DEBUG_FUNCPTR (gst_opencvdebayer_transform_frame);
  //video_filter_class->transform_caps =
    //  GST_DEBUG_FUNCPTR (gst_video_convert_transform_caps);

}

static void
gst_opencvdebayer_init (GstOpencvdebayer * opencvdebayer)
{
    gst_base_transform_set_in_place (GST_BASE_TRANSFORM (opencvdebayer),
      FALSE);
}

void
gst_opencvdebayer_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (object);

  GST_DEBUG_OBJECT (opencvdebayer, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_opencvdebayer_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (object);

  GST_DEBUG_OBJECT (opencvdebayer, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static GstCaps *
gst_opencvdebayer_transform_caps (GstBaseTransform * trans, GstPadDirection dir,
  GstCaps * caps, GstCaps * filter)
  {
    /*
    GstCaps *ret;
    GstStructure *structure;
    GValue val = { 0, };
    ret = gst_caps_new_empty ();
    structure = gst_structure_copy (gst_caps_get_structure (caps, 0));
    g_value_init (&val, G_TYPE_STRING);
    g_value_set_string (&val, "GRAY8");
    gst_structure_set_value(structure, "format", &val);
    g_value_unset (&val);
    gst_structure_remove_field (structure, "colorimetry");
    gst_structure_remove_field (structure, "chroma-site");
    gst_caps_append_structure (ret, structure);

    return ret;
    */
 GstCaps *to, *ret;
  GstCaps *templ;
  GstStructure *structure;
  GstPad *other;
  gint i;

  to = gst_caps_new_empty ();

  for (i = 0; i < gst_caps_get_size (caps); i++) {
    const GValue *v;
    GValue list = { 0, };
    GValue val = { 0, };

    structure = gst_structure_copy (gst_caps_get_structure (caps, i));

    g_value_init (&list, GST_TYPE_LIST);

    g_value_init (&val, G_TYPE_STRING);
    g_value_set_string (&val, "GRAY8");
    gst_value_list_append_value (&list, &val);
    g_value_unset (&val);

    g_value_init (&val, G_TYPE_STRING);
    g_value_set_string (&val, "BGRx");
    gst_value_list_append_value (&list, &val);
    g_value_unset (&val);

    v = gst_structure_get_value (structure, "format");

    gst_value_list_merge (&val, v, &list);
    gst_structure_set_value (structure, "format", &val);
    g_value_unset (&val);
    g_value_unset (&list);

    gst_structure_remove_field (structure, "colorimetry");
    gst_structure_remove_field (structure, "chroma-site");

    gst_caps_append_structure (to, structure);

  }
  /* filter against set allowed caps on the pad */
  other = (dir == GST_PAD_SINK) ? trans->srcpad : trans->sinkpad;
  templ = gst_pad_get_pad_template_caps (other);
  ret = gst_caps_intersect (to, templ);
  gst_caps_unref (to);
  gst_caps_unref (templ);

  if (ret && filter) {
    GstCaps *intersection;

    intersection =
        gst_caps_intersect_full (filter, ret, GST_CAPS_INTERSECT_FIRST);
    gst_caps_unref (ret);
    ret = intersection;
  }

  return ret;


  }

void
gst_opencvdebayer_dispose (GObject * object)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (object);

  GST_DEBUG_OBJECT (opencvdebayer, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS (gst_opencvdebayer_parent_class)->dispose (object);
}

void
gst_opencvdebayer_finalize (GObject * object)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (object);

  GST_DEBUG_OBJECT (opencvdebayer, "finalize");

  /* clean up object here */

  G_OBJECT_CLASS (gst_opencvdebayer_parent_class)->finalize (object);
}

static gboolean
gst_opencvdebayer_start (GstBaseTransform * trans)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (trans);

  GST_DEBUG_OBJECT (opencvdebayer, "start");

  return TRUE;
}

static gboolean
gst_opencvdebayer_stop (GstBaseTransform * trans)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (trans);

  GST_DEBUG_OBJECT (opencvdebayer, "stop");

  return TRUE;
}

static gboolean
gst_opencvdebayer_set_info (GstVideoFilter * filter, GstCaps * incaps,
    GstVideoInfo * in_info, GstCaps * outcaps, GstVideoInfo * out_info)
{
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (filter);

  GST_DEBUG_OBJECT (opencvdebayer, "set_info");


  return TRUE;
}

/* transform */
static GstFlowReturn
gst_opencvdebayer_transform_frame (GstVideoFilter * filter,
    GstVideoFrame * inframe, GstVideoFrame * outframe)
{
  gst_base_transform_set_in_place (GST_BASE_TRANSFORM (filter), FALSE);
  GstOpencvdebayer *opencvdebayer = GST_OPENCVDEBAYER (filter);

  GST_DEBUG_OBJECT (opencvdebayer, "transform_frame");
  cv::Mat inputMat = cv::Mat(2000,4000,CV_8UC1,(char *) inframe->data[0],inframe->info.stride[0]);
  cv::Mat temp;
  cv::Mat outputMat = cv::Mat(2000,4000,CV_8UC4,(char *) outframe->data[0],outframe->info.stride[0]);
  //cv::Mat outputMat;
  //cv::imwrite("/home/dj/bayer.png",inputMat);
  cv::cvtColor(inputMat,temp,CV_BayerBG2BGR);
  cv::cvtColor(temp,outputMat,CV_BGR2BGRA);
  //cv::imwrite("/home/dj/color.png",outputMat);
  GST_DEBUG_OBJECT (opencvdebayer, "transform_complete");

  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "opencvdebayer", GST_RANK_NONE,
      GST_TYPE_OPENCVDEBAYER);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
#ifndef VERSION
#define VERSION "0.1"
#endif
#ifndef PACKAGE
#define PACKAGE "opencv_debayer"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "opencv_debayer"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "http://FIXME.org/"
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    opencvdebayer,
    "demosaics image using cvtcolor from opencv",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)
