PORTNAME=	tcpreen
PORTVERSION=	1.4.4
PORTREVISION=	3
CATEGORIES=	net
MASTER_SITES=	http://www.remlab.net/files/tcpreen/

MAINTAINER=	jmohacsi@bsd.hu
COMMENT=	Simple TCP session re-engineering tool
WWW=		https://www.remlab.net/tcpreen/

LICENSE=	GPLv2+

USES=		cpe localbase tar:bzip2
GNU_CONFIGURE=	yes

OPTIONS_SUB=	yes

PORTDOCS=	AUTHORS NEWS README THANKS TODO

OPTIONS_DEFINE=	DOCS NLS

NLS_USES=	gettext
NLS_CONFIGURE_OFF=	--disable-nls

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
