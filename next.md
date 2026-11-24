
# shematiser le processur d'initialisation
# memory check  !!!
# cas d'mpression apres burnout sur ./codexion 20 401 200 100 100 10 0 fifo
# explication clock_gettime
# verifier le type timestamp -> int64_t vs clock_t vs time_t

# Question :
more than 200 coder?

# Test Repport

## TEST NOK
5 3000 200 200 200 10 800 edf
5 1000 200 200 200 10 200 edf


## TEST OK
ARG=20 410 200 100 100 100 0 fifo. -> OK
ARG=200 450 200 100 100 10 0 fifo -> OK
ARG=200 420 200 100 100 10 0 fifo -> OK
ARG=20 401 200 100 100 10 0 fifo -> OK
ARG=1 420 200 100 100 10 0 fifo -> OK
ARG=200 420 200 100 100 10 0 fifo -> BURN
./codexion 2 1000 200 50 50 10 200 fifo -> OK
./codexion 2 1000 200 50 50 10 200 fifo -> OK
./codexion 2 1000 200 50 50 10 200 edf -> OK
