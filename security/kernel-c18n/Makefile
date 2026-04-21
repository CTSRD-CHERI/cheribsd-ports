PORTNAME=	kernel-c18n
SNAPSHOT=	2026-04-14
PORTVERSION=	${SNAPSHOT:S/-//g}
PORTREVISION=	0
CATEGORIES=	security

KERNCONF=	GENERIC-MORELLO-PURECAP-COMPARTMENTS
MAINTAINER=	konrad.witaszczyk@cl.cam.ac.uk
COMMENT=	Compartmentalized CheriBSD kernel (experimental ${KERNCONF})
WWW=		https://github.com/CTSRD-CHERI/cheripedia/wiki/Kernel-compartmentalization

MASTER_SITES=	CHERIBSD_SNAPSHOTS/${PORTNAME}/arm64/aarch64c/${SNAPSHOT}/ftp/
DISTFILES=	kernel.txz \
		kernel-dbg.txz

ONLY_FOR_ARCHS=	aarch64c

NO_BUILD=	yes
NO_WRKSUBDIR=	yes

do-install: _SHAREMODE=0444
	cd ${WRKSRC}/boot/kernel && \
	    ${COPYTREE_SHARE} ./ ${STAGEDIR}/boot/kernel.${KERNCONF}/
	cd ${WRKSRC}/usr/lib/debug/boot/kernel && \
	    ${COPYTREE_SHARE} ./ ${STAGEDIR}/usr/lib/debug/boot/kernel.${KERNCONF}/

buildplist:
	${MAKE} makeplist >${PLIST}
	${REINPLACE_CMD} -i '' -e \
	    '/^\/you\/have\/to\/check\/what\/makeplist\/gives\/you$$/d; \
	    /^@dir \/usr\/lib\/debug\/boot$$/d; \
	    /^@dir \/usr\/lib\/debug$$/d' \
	    ${PLIST}

.include <bsd.port.mk>
