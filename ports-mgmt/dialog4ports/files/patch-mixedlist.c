--- mixedlist.c.orig	2016-07-08 15:49:08.000000000 +0100
+++ mixedlist.c	2023-04-03 16:35:38.479966000 +0100
@@ -652,23 +652,23 @@
 						break;
 					case DLGK_ITEM_PREV:
 						i = choice - 1;
+						if (choice == 0 && scrollamt == 0)
+							continue;
 						if (items[scrollamt + i].type == ITEM_SEPARATOR && (scrollamt + i) == 0)
 							i++;
 						else if (items[scrollamt + i].type == ITEM_SEPARATOR)
 							i--;
-						if (choice == 0 && scrollamt == 0)
-							continue;
 						break;
 					case DLGK_ITEM_NEXT:
 						i = choice + 1;
+						if (scrollamt + choice >= item_no - 1)
+							continue;
 						if (items[scrollamt + i].type == ITEM_SEPARATOR) {
 							if (scrollamt + i + 1 < item_no)
 								i++;
 							else
 								i--;
 						}
-						if (scrollamt + choice >= item_no - 1)
-							continue;
 						break;
 					default:
 						found = false;
