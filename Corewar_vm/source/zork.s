.name "zork"
.comment "I'M ALIIIIVE"

		ld %11259375, r1
l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
