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
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_OPENCVDEBAYER_H_
#define _GST_OPENCVDEBAYER_H_

#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

G_BEGIN_DECLS

#define GST_TYPE_OPENCVDEBAYER   (gst_opencvdebayer_get_type())
#define GST_OPENCVDEBAYER(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_OPENCVDEBAYER,GstOpencvdebayer))
#define GST_OPENCVDEBAYER_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_OPENCVDEBAYER,GstOpencvdebayerClass))
#define GST_IS_OPENCVDEBAYER(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_OPENCVDEBAYER))
#define GST_IS_OPENCVDEBAYER_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_OPENCVDEBAYER))

typedef struct _GstOpencvdebayer GstOpencvdebayer;
typedef struct _GstOpencvdebayerClass GstOpencvdebayerClass;

struct _GstOpencvdebayer
{
  GstVideoFilter base_opencvdebayer;

};

struct _GstOpencvdebayerClass
{
  GstVideoFilterClass base_opencvdebayer_class;
};

GType gst_opencvdebayer_get_type (void);

G_END_DECLS

#endif
