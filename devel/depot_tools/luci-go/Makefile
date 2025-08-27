PORTNAME=		luci-go
DISTVERSIONPREFIX=	v
DISTVERSION=    	0.0.0-20240215145537-8e32c0e0589b
CATEGORIES=     	devel 

MAINTAINER=     	graeme@capabilitieslimited.co.uk
COMMENT=        	LUCI (Layered "Universal" Continuous Integration) services and tools in Go
WWW=            	https://chromium.googlesource.com/infra/infra/

LICENSE=        	BSD3CLAUSE 
LICENSE_FILE=   	${WRKSRC}/LICENSE

USES=           	go:1.21,modules
USE_GO=			pkg64
GO_MODULE=      	go.chromium.org/luci
CGO_ENABLED=		0

GO_TARGET=		./auth/client/cmd/luci-auth \
			./auth/client/cmd/authdb-dump \
			./buildbucket/cmd/bb \
			./buildbucket/cmd/bbagent \
			./buildbucket/cmd/bbagent/util/dump_bbagent_arg \
			./buildbucket/cmd/dump_build \
			./cipd/client/cmd/cipd \
			./client/cmd/cas \
			./client/cmd/cloudkms \
			./client/cmd/docker-credential-luci \
			./client/cmd/gerrit \
			./client/cmd/git-credential-luci \
			./client/cmd/gitiles \
			./client/cmd/isolate \
			./client/cmd/swarming \
			./cv/cmd/luci-cv \
			./grpc/cmd/cproto \
			./grpc/cmd/prpc \
			./grpc/cmd/svcdec \
			./grpc/cmd/svcmux \
			./logdog/client/cmd/logdog \
			./logdog/client/cmd/logdog_butler \
			./luci_notify/cmd/preview_email \
			./lucicfg/cmd/docgen \
			./lucicfg/cmd/lucicfg \
			./luciexe/legacy/cmd/run_annotations \
			./mailer/cmd/mailer \
			./mmutex/cmd/mmutex \
			./resultdb/cmd/baselineupdater \
			./resultdb/cmd/bqexporter \
			./resultdb/cmd/deadlineenforcer \
			./resultdb/cmd/finalizer \
			./resultdb/cmd/globalmetrics \
			./resultdb/cmd/purger \
			./resultdb/cmd/rdb \
			./resultdb/cmd/recorder \
			./resultdb/cmd/resultdb \
			./resultdb/cmd/testmetadataupdator \
			./server/cmd/cookieserver \
			./server/cmd/datastore-delete \
			./server/cmd/encryptedcookies-session-backfill \
			./server/cmd/secret-tool \
			./server/cmd/selfsigned-cert \
			./server/cmd/sidecar \
			./server/cmd/statsd-to-tsmon \
			./server/cmd/tq-sweeper-spanner \
			./tokenserver/cmd/luci_machine_tokend \
			./tools/cmd/apigen \
			./tools/cmd/assets \
			./tools/cmd/bqschemaupdater \
			./tools/cmd/fakecas \
			./tools/cmd/gorun \
			./tools/cmd/luapp \
			./tools/cmd/spannerdataupdater

.include <bsd.port.mk>
