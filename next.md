
# shematiser le processur d'initialisation
# memory check  !!!
# cas d'mpression apres burnout sur ./codexion 20 401 200 100 100 10 0 fifo
# explication clock_gettime
# verifier le type timestamp -> int64_t vs clock_t vs time_t

# Question :
more than 200 coder?

# Test Repport

## TEST NOK

## TEST OK
ARG=20 410 200 100 100 100 0 fifo. -> OK
ARG=200 450 200 100 100 10 0 fifo -> OK
ARG=200 420 200 100 100 10 0 fifo -> OK
ARG=20 401 200 100 100 10 0 fifo -> OK
ARG=1 420 200 100 100 10 0 fifo -> OK
ARG=200 420 200 100 100 10 0 fifo -> BURN
