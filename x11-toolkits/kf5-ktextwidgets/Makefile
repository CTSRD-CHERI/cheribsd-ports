PORTNAME=	ktextwidgets
DISTVERSION=	${KDE_FRAMEWORKS_VERSION}
CATEGORIES=	x11-toolkits kde kde-frameworks

MAINTAINER=	kde@FreeBSD.org
COMMENT=	KF5 advanced text editing widgets

USES=		cmake compiler:c++11-lib gettext kde:5 qt:5 tar:xz
USE_KDE=	auth codecs completion config configwidgets \
		coreaddons i18n service sonnet widgetsaddons \
		ecm:build
USE_QT=		concurrent core gui widgets xml \
		buildtools:build qmake:build

OPTIONS_DEFINE=		AUDIO
OPTIONS_DEFAULT=	AUDIO
OPTIONS_EXCLUDE_purecap=AUDIO

AUDIO_DESC=		Audio notifications/speech support
AUDIO_USE=		QT=speech

.include <bsd.port.mk>
