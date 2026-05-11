PORTNAME?=	gdb-cheri-purecap
COMMENT?=	GNU Project Debugger with support for the Arm Morello and CHERI-RISC-V architectures (experimental purecap variant)

ONLY_FOR_ABIS=	purecap
ONLY_FOR_ABIS_REASON=is an experimental version for CheriABI

SLAVE_PORT?=	${PORTNAME}
GDBCHERIDIR=	${.CURDIR}/../gdb-cheri
.include "${GDBCHERIDIR}/Makefile"
