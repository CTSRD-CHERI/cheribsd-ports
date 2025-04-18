PORTNAME=	powerdevil
DISTVERSION=	${KDE_PLASMA_VERSION}
CATEGORIES=	sysutils kde kde-plasma

MAINTAINER=	kde@FreeBSD.org
COMMENT=	Plasma5 tool to manage the power consumption settings
WWW=		https://www.kde.org/plasma-desktop

OPTIONS_DEFINE=	POLKIT DOCS
OPTIONS_EXCLUDE_purecap=	POLKIT DOCS
OPTIONS_SUB=	yes

DOCS_EXTRA_PATCHES_OFF= ${PATCHDIR}/cheribsd-docs.patch

LIB_DEPENDS=	libudev.so:devel/libudev-devd

.include <bsd.port.options.mk>

.if !${ABI:Mpurecap}
RUN_DEPENDS=	${LOCALBASE}/libexec/upowerd:sysutils/upower
.endif

USES=		cmake compiler:c++11-lib gettext kde:5 pkgconfig qt:5 tar:xz \
		xorg
USE_KDE=	activities auth bookmarks codecs completion config \
		configwidgets coreaddons crash dbusaddons emoticons \
		globalaccel guiaddons i18n iconthemes idletime init itemmodels \
		itemviews jobwidgets kio kirigami2 libkscreen notifications \
		notifyconfig parts plasma-workspace service solid sonnet \
		textwidgets unitconversion wayland widgetsaddons windowsystem \
		xmlgui \
		ecm:build
USE_QT=		concurrent core dbus gui network printsupport widgets \
		x11extras xml \
		buildtools:build qmake:build
USE_XORG=	x11 xcb

.include <bsd.port.mk>
