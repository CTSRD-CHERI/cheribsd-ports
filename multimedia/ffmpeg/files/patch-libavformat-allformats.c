--- libavformat/allformats.c.orig	2025-03-25 14:36:10.472976000 +0000
+++ libavformat/allformats.c	2025-03-25 14:36:21.282947000 +0000
@@ -560,8 +560,8 @@
 #include "libavformat/muxer_list.c"
 #include "libavformat/demuxer_list.c"
 
-static atomic_uintptr_t indev_list_intptr  = ATOMIC_VAR_INIT(0);
-static atomic_uintptr_t outdev_list_intptr = ATOMIC_VAR_INIT(0);
+static atomic_uintptr_t indev_list_intptr;
+static atomic_uintptr_t outdev_list_intptr;
 
 const AVOutputFormat *av_muxer_iterate(void **opaque)
 {
