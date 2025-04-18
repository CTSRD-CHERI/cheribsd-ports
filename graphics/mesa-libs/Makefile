PORTNAME=	mesa-libs
PORTVERSION=	${MESAVERSION}
PORTREVISION=	1
CATEGORIES=	graphics

COMMENT=	OpenGL libraries that support GLX and EGL clients
WWW=		https://www.mesa3d.org/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/docs/license.rst

LIB_DEPENDS=	libOpenGL.so:graphics/libglvnd

OPTIONS_GROUP=			PLATFORM
OPTIONS_GROUP_PLATFORM=		PLATFORM_X11 PLATFORM_WAYLAND
PLATFORM_X11_DESC=		Enable X11 support for GBM/EGL
PLATFORM_WAYLAND_DESC=		Enable Wayland support for GBM/EGL
PLATFORM_WAYLAND_IMPLIES=	WAYLAND

OPTIONS_DEFINE=	WAYLAND ZSTD
OPTIONS_DEFAULT=WAYLAND PLATFORM_X11 PLATFORM_WAYLAND ZSTD
OPTIONS_SUB=	yes

WAYLAND_DESC=		Enable support for the Wayland platform in EGL
WAYLAND_BUILD_DEPENDS=	wayland-protocols>=1.8:graphics/wayland-protocols
WAYLAND_LIB_DEPENDS=	libwayland-egl.so:graphics/wayland
WAYLAND_IMPLIES=	PLATFORM_WAYLAND

ZSTD_DESC=		Use ZSTD for shader cache
ZSTD_LIB_DEPENDS=	libzstd.so:archivers/zstd
ZSTD_MESON_ENABLED=	zstd

USE_LDCONFIG=		yes

.include <bsd.port.options.mk>
.include "${.CURDIR:H:H}/graphics/mesa-dri/Makefile.common"

.if ${ABI:Mpurecap}
GALLIUM_DRIVERS=	PANFROST SWRAST
.else
# Building EGL and GBM requires a driver so add r300
GALLIUM_DRIVERS=	R300
.endif

MESON_ARGS+=	-Dgallium-vdpau=disabled \
		-Dgallium-omx=disabled \
		-Dgallium-va=disabled \
		-Dgallium-xa=disabled \
		-Dgallium-nine=false \
		-Dmicrosoft-clc=disabled \
		-Dosmesa=false \
		-Dtools="" \
		-Degl=enabled \
		-Dgbm=enabled \
		-Dvulkan-drivers="" \
		-Dglvnd=true
MESON_ARGS+=	-Dgallium-drivers="${GALLIUM_DRIVERS:ts,:tl}"

.if ${ABI:Mpurecap}
MESON_ARGS+=	-Dgles1=enabled \
		-Dgles2=enabled \
		-Dllvm=disabled
.endif

.if ${PORT_OPTIONS:MPLATFORM_X11}
MESA_PLATFORMS+=	x11
USE_XORG+=		xorgproto x11 xcb xdamage xext \
			xfixes xshmfence xxf86vm xrandr
PLIST_SUB+=		GLX=""
.else
MESON_ARGS+=	-Dglx=disabled
PLIST_SUB+=	GLX="@comment "
.endif

.if ${PORT_OPTIONS:MPLATFORM_WAYLAND} && ${PORT_OPTIONS:MWAYLAND}
MESA_PLATFORMS+=	wayland
.endif

MESON_ARGS+=	-Dplatforms="${MESA_PLATFORMS:ts,:tl}"

.if ${ARCH} == "i386"
# PR230239 Fix the build for i386 when WITH_LLD_IS_LD is set
LDFLAGS+=-Wl,-z,notext
.endif

.include "${MASTERDIR}/Makefile.targets"

post-install:
# Fallback if GLX_EXT_libglvnd is missing or vendor library doesn't exist
	@${ECHO_CMD} "libGLX_indirect.so.0 libGLX_mesa.so.0" \
		>${STAGEDIR}${PREFIX}/etc/libmap.d/mesa.conf

.include <bsd.port.post.mk>
