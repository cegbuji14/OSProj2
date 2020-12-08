shm_bank: shm_bankaccount.c
	gcc shm_bankaccount.c -D_SVID_SOURCE -pthread -std=c99 -lpthread -o shm_bank
shm_proc: shm_processes.c
	gcc shm_processes.c -D_SVID_SOURCE -pthread -std=c99 -lpthread  -o shm_proc
example: example.c
	gcc example.c -pthread -std=c99 -lpthread  -o example