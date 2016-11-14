.name "zork"
.comment "I'M ALIIIIVE"


live:	live %20
l2:		sti r1, %:live, %1
		and r1, %0, r1

		zjmp %:live
