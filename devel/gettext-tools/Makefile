# NOTE: before committing to this port, contact portmgr to arrange for an
# experimental ports run.  Untested commits may be backed out at portmgr's
# discretion.

PORTNAME=	gettext-tools
PORTREVISION=	0

COMMENT=	GNU gettext development and translation tools
WWW=		https://www.gnu.org/software/gettext/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/../COPYING

.include "${.CURDIR}/../gettext/Makefile.common"

BUILD_DEPENDS=	libtextstyle>=${PORTVERSION}:devel/libtextstyle
LIB_DEPENDS=	libtextstyle.so:devel/libtextstyle

USES=		charsetfix cpe gettext-runtime iconv libtool localbase tar:xz
USE_LDCONFIG=	yes

EXTRA_PATCHES=	${.CURDIR}/../gettext-runtime/files/cheribsd.patch

CPE_PRODUCT=	gettext
CPE_VENDOR=	gnu

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--disable-csharp --disable-java --with-included-glib \
		--with-included-libcroco --with-included-libunistring \
		--with-included-libxml --with-installed-libtextstyle \
		--with-xz --without-emacs \
		ac_cv_lib_rt_sched_yield=no
INSTALL_TARGET=	install-strip
TEST_TARGET=	check
WRKSRC_SUBDIR=	gettext-tools

DATADIR=	${PREFIX}/share/gettext
DOCSDIR=	${PREFIX}/share/doc/gettext
PLIST_SUB=	PORTVERSION=${PORTVERSION} VERSION=${PORTVERSION}
ARCHIVE_SUFX?=	.tar.xz
PLIST_SUB+=	ARCHIVE_SUFX=${ARCHIVE_SUFX}

INFO=		gettext

OPTIONS_DEFINE=	DOCS EXAMPLES THREADS
OPTIONS_DEFAULT=THREADS
OPTIONS_EXCLUDE_DragonFly=	THREADS

THREADS_CONFIGURE_ENABLE=	threads

.include <bsd.port.mk>
