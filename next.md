
# implementer le cooldown
# implementer le edf
# shematiser le processur d'initialisation
# memory check

# Question :
more than 200 coder?

# Test Repport

## TEST NOK
ARG=20 401 200 100 100 10 0 fifo -> segfault
ARG=200 410 200 100 100 10 0 fifo -> segfault
ARG=1 420 200 100 100 10 0 fifo -> One coder: segfault

## TEST OK
ARG=20 410 200 100 100 100 0 fifo. -> OK
ARG=200 450 200 100 100 10 0 fifo -> OK
ARG=200 420 200 100 100 10 0 fifo -> OK