PORTNAME?=	kernel-c18n
PORTVERSION=	${SNAPSHOT:S/-//g}
CATEGORIES=	security
MAINTAINER=	konrad.witaszczyk@cl.cam.ac.uk
COMMENT?=	Compartmentalized CheriBSD kernels (experimental ${KERNCONFS:[1]})
WWW=		https://github.com/CTSRD-CHERI/cheripedia/wiki/Kernel-compartmentalization
ONLY_FOR_ARCHS=	aarch64c
NO_BUILD=	yes
NO_WRKSUBDIR=	yes

SNAPSHOT?=	2026-07-10
PORTREVISION?=	0

KERNCONFS?=	GENERIC-MORELLO-PURECAP-COMPARTMENTS \
		GENERIC-MORELLO-PURECAP-COMPARTMENTS-NODEBUG \
		GENERIC-MORELLO-PURECAP-BENCHMARK-COMPARTMENTS \
		GENERIC-MORELLO-PURECAP-BENCHMARK-COMPARTMENTS-NODEBUG
KERNCONFDIR_GENERIC_MORELLO_PURECAP_COMPARTMENTS=	kernel

.for kernconf in ${KERNCONFS}
KERNCONFDIR_${kernconf:S/-/_/g}?=			kernel.${kernconf}
.endfor

BRANCHNAME?=	${PORTNAME}
DIST_SUBDIR=	${BRANCHNAME}/arm64/aarch64c
MASTER_SITES=	CHERIBSD_SNAPSHOTS/${DIST_SUBDIR}
DISTFILES=
.for kernconf in ${KERNCONFS}
DISTFILES+=	${SNAPSHOT}/ftp/${KERNCONFDIR_${kernconf:S/-/_/g}}.txz \
		${SNAPSHOT}/ftp/${KERNCONFDIR_${kernconf:S/-/_/g}}-dbg.txz
.endfor

do-install: _SHAREMODE=0444
.for kernconf in ${KERNCONFS}
	cd ${WRKSRC}/boot/${KERNCONFDIR_${kernconf:S/-/_/g}} && \
	    ${COPYTREE_SHARE} ./ ${STAGEDIR}/boot/kernel.${kernconf}/
	cd ${WRKSRC}/usr/lib/debug/boot/${KERNCONFDIR_${kernconf:S/-/_/g}} && \
	    ${COPYTREE_SHARE} ./ ${STAGEDIR}/usr/lib/debug/boot/kernel.${kernconf}/
.endfor

buildplist:
	${MAKE} makeplist >${PLIST}
	${REINPLACE_CMD} -i '' -e \
	    '/^\/you\/have\/to\/check\/what\/makeplist\/gives\/you$$/d; \
	    /^@dir \/usr\/lib\/debug\/boot$$/d; \
	    /^@dir \/usr\/lib\/debug$$/d' \
	    ${PLIST}

.include <bsd.port.mk>
