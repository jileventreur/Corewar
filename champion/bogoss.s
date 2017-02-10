.name "bogoss"
.comment "I WILL CRUSH YOU"

sti r1, %:machine_a_prout, %1
ld %42, r2

forking_loop:
		fork %:machine_a_prout
		zjmp %:forking_loop

machine_a_prout:
	live %42
	zjmp %:machine_a_prout
