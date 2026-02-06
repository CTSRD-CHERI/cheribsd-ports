# handle ports containing deliberate vulnerabilities
#
# Features:	vulnerable
# Usage:	USES=vulnerable
# Valid ARGS:	<none>
#
# It is sometimes useful to demonstrate software that contains
# unpatched or deliberately introduced vulnerabilities, but doing so is
# risky.  When ports are labled vulnerable they can not be built
# unless ALLOW_DELIBERATE_VULNERABILITIES is defined and when built
# they contain a warning to this effect.

.if !include(_INCLUDE_USES_VULNERABLE_MK)
_INCLUDE_USES_VULNERABLE_MK=	yes

_VULNS_VAR=	ALLOW_DELIBERATE_VULNERABILITIES

.  if emptry(vulnerable_ARGS)

BROKEN=
.  else
.    ifndef ${_VULNS_VAR}
BROKEN=	Contains deliberate vulnerabilities (define ${_VULNS_VAR} to build)
.    endif
_PKGMESSAGES+=	${PORTSDIR}/Templates/pkg-message-vulnerable
PKGNAMEPREFIX=	vulnerable-
.  endif
.endif
