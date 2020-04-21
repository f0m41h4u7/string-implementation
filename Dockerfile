FROM		srzzumix/googletest
RUN		apt-get -y update && apt-get -y upgrade && apt-get install -y bash vim curl
WORKDIR		home
COPY		. .
RUN		make test
ENTRYPOINT 	["./test"]
