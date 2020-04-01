PROGRAM_NAME = tarea2

all:
	gcc -o $(PROGRAM_NAME) src/*.c -std=gnu11 -Wall -Wextra -O2 -Isrc/ 

debug:
	gcc -o $(PROGRAM_NAME) src/*.c -std=gnu11 -Wall -Wextra -Og -g -Isrc/ -fsanitize=address

clean:
	rm -f $(PROGRAM_NAME) *.o network-config.txt nodes_ids.txt
