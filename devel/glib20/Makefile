PORTNAME=	glib
DISTVERSION=	2.76.4
PORTEPOCH=	2
CATEGORIES=	devel
MASTER_SITES=	GNOME
DIST_SUBDIR=	gnome

PATCH_SITES=	https://gitlab.gnome.org/GNOME/${PORTNAME}/-/commit/
PATCHFILES+=	f6c40b1d27ed.patch:-p1 # https://gitlab.gnome.org/GNOME/glib/-/merge_requests/3335

MAINTAINER=	desktop@FreeBSD.org
COMMENT=	Some useful routines of C programming (current stable version)
WWW=		https://www.gtk.org/

LICENSE=	LGPL20

LIB_DEPENDS=	libffi.so:devel/libffi \
		libpcre2-8.so:devel/pcre2

# iconv:wchar_t - our iconv in base doesn't support utf-8 -> wchar_t (boooo)
# (wchar_t is used by glibmm, rawtherapee triggered this)
USES=		compiler:c11 cpe gettext gnome iconv:wchar_t localbase:ldflags \
		meson perl5 pkgconfig python tar:xz trigger
TRIGGERS=	gio-modules glib-schemas
USE_LDCONFIG=	yes
USE_PERL5=	build
USE_PYTHON=	py3kplist
MESON_ARGS=	-Db_lundef=false \
		-Ddefault_library=both \
		-Dinstalled_tests=false \
		-Dlibmount=disabled \
		-Druntime_dir=/var/run \
		-Dselinux=disabled \
		-Dxattr=false

CFLAGS_aarch64c+=	-DG_ENABLE_EXPERIMENTAL_ABI_COMPILATION
BINARY_ALIAS=	python3=${PYTHON_CMD}
PORTSCOUT=	limitw:1,even
CPE_VENDOR=	gnome

CONFLICTS_INSTALL=	p5-Giovanni

_LIBVERSION=	0.7600.4
PLIST_SUB=	LIBVERSION=${_LIBVERSION}

OPTIONS_DEFINE=		DEBUG GTKDOC FAM_ALTBACKEND MANPAGES NLS TEST
OPTIONS_DEFAULT=	MANPAGES
OPTIONS_SUB=		yes

GTKDOC_BUILD_DEPENDS=	gtk-doc>0:textproc/gtk-doc
GTKDOC_IMPLIES=		TEST
GTKDOC_MESON_TRUE=	gtk_doc

FAM_ALTBACKEND_DESC=	Alternate file monitor backend

MANPAGES_BUILD_DEPENDS=	docbook-xml>4.1.2:textproc/docbook-xml \
			docbook-xsl>0:textproc/docbook-xsl
MANPAGES_USE=		GNOME=libxslt:build
MANPAGES_MESON_TRUE=	man

TEST_BUILD_DEPENDS=	dbus-daemon:devel/dbus
TEST_MESON_TRUE=	tests

.include <bsd.port.pre.mk>

# doesn't build yet
MESON_ARGS+=	-Ddtrace=false

pre-configure-FAM_ALTBACKEND-on:
	@${REINPLACE_CMD} -e 's|kqueue-helper.c|kqueue_fnm.c|g ; \
		s|.*kqueue-missing.c.*||g ; \
		s|.*dep-list.c.*||g' \
		${WRKSRC}/gio/kqueue/meson.build
	@${CP} -f ${FILESDIR}/gkqueuefilemonitor.c ${WRKSRC}/gio/kqueue/gkqueuefilemonitor.c
	@${CP} ${FILESDIR}/kqueue_fnm.c ${WRKSRC}/gio/kqueue/kqueue_fnm.c
	@${CP} ${FILESDIR}/kqueue_fnm.h ${WRKSRC}/gio/kqueue/kqueue_fnm.h

# The generation of GIO documentation depends on a types-document
# generated as part of the dbus-object-manager example. With an
# embarrassingly parallel build, failures like this can happen:
#
# Building documentation for gdbus-object-manager-example
# ERROR: Error in gtkdoc helper script:
# FileNotFoundError: [Errno 2] No such file or directory: '_build/docs/reference/gio/gdbus-object-manager-example/gdbus-object-manager-example.types'
#
# Meson does not seem to provide a way to express that dependency.
#
# Hack it into the generated ninja build instead.
post-configure-GTKDOC-on:
	@${REINPLACE_CMD} -e '\+^build docs/reference/gio/gdbus-object-manager-example/gdbus-object-manager-example-decl.txt:+s+$$+ || gio/tests/gdbus-object-manager-example/libgdbus-example-objectmanager.so+' ${BUILD_WRKSRC}/build.ninja

post-patch:
	${REINPLACE_CMD} -e 's|/usr/local|${LOCALBASE}|g ; \
		s|/usr/share/locale/locale|${LOCALBASE}/share/locale/locale|g' \
		${WRKSRC}/glib/gutils.c
	${REINPLACE_CMD} -e 's|@PYTHON@|${PYTHON_CMD}|g' \
		${WRKSRC}/gio/gdbus-2.0/codegen/gdbus-codegen.in \
		${WRKSRC}/glib/gtester-report.in \
		${WRKSRC}/gobject/glib-genmarshal.in \
		${WRKSRC}/gobject/glib-mkenums.in
	${REINPLACE_CMD} -e '/inotify_init1/d' \
		-e '/inotify.h/d' \
		${WRKSRC}/meson.build
	${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|' \
		${WRKSRC}/gio/xdgmime/xdgmime.c \
		${WRKSRC}/glib/gutils.c \
		${WRKSRC}/glib/tests/utils.c

CODEGENDIR=	${PREFIX}/share/glib-2.0/codegen

post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/share/GConf/gsettings
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/gio/modules
# generates .py[co] files for installed modules
# if that's not done, ${PYTHON_SITELIBDIR}/gps will be polluted
# with these files when module is imported from root user
	${FIND} ${STAGEDIR}${PREFIX} -name \*.pyc -delete
	(cd ${STAGEDIR}${PREFIX} && \
	${PYTHON_CMD} ${PYTHON_LIBDIR}/compileall.py \
		-d ${CODEGENDIR} -f ${CODEGENDIR:S;${PREFIX}/;;} && \
	${PYTHON_CMD} -O ${PYTHON_LIBDIR}/compileall.py \
		-d ${CODEGENDIR} -f ${CODEGENDIR:S;${PREFIX}/;;})
# install bash completion regardless if bash is present
	${MKDIR} ${STAGEDIR}${PREFIX}/share/bash-completion/completions
.for file in gapplication gdbus gio gresource gsettings
	${INSTALL_DATA} ${WRKSRC}/gio/completion/${file} \
		${STAGEDIR}${PREFIX}/share/bash-completion/completions/
.endfor
	${RM} -r ${STAGEDIR}${PREFIX}/libexec/installed-tests

.include <bsd.port.post.mk>
