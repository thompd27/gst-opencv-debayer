project('gst-opencv-debayer', 'cpp', version : '1.16.2', license : 'LGPL')

plugins_install_dir = join_paths(get_option('libdir'), 'gstreamer-1.0')

cc = meson.get_compiler('cpp')

gst_version = meson.project_version()

api_version = '1.0'

gst_dep = dependency('gstreamer-1.0', version : '>=1.16',
    required : true, fallback : ['gstreamer', 'gst_dep'])
    
#opencv_inc = include_directories('/usr/dalsa/GigeV/include')

opencv_dep = dependency('opencv4', version : '>=4.0',
	required : true)

#declare_dependency(link_args : ['-L/usr/dalsa/GigeV/lib', '-lGevApi'],
#  include_directories : dalsa_inc)

plugin_c_args = ['-DHAVE_CONFIG_H']

cdata = configuration_data()
cdata.set_quoted('PACKAGE_VERSION', gst_version)
cdata.set_quoted('PACKAGE', 'gst-dalsa-plugin')
cdata.set_quoted('GST_LICENSE', 'LGPL')
cdata.set_quoted('GST_API_VERSION', api_version)
cdata.set_quoted('GST_PACKAGE_NAME', 'Teledyne Dalsa Plugin')
cdata.set_quoted('GST_PACKAGE_ORIGIN', '')
configure_file(output : 'config.h', configuration : cdata)

gstvideo_dep = dependency('gstreamer-video-1.0',
	fallback: ['gst-plugins-base', ''])
	
# Plugin 1
plugin_sources = [
  'src/gstopencvdebayer.cpp'
  ]

gstspinnakerplugin= library('gstopencv_debayer',
  plugin_sources,
  c_args: plugin_c_args,
  dependencies : [gst_dep, gstvideo_dep, opencv_dep],
  install : true,
  install_dir : plugins_install_dir,
)
