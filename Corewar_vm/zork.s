.name "zork"
.comment "I'M ALIIIIVE"

# l2:		sti r1, %:live, %1
		# and r1, %0, r1

# live:	live %1
		# zjmp %:live


# live %1
# add r1, r2, r3
# sub r1, r2, r3
# or %1, 1, r3
# xor %1, 2, r3
# and %1, 2, r3
# zjmp %1
# aff r1
# lld 1, r2
# ld 1, r2
# lfork %1
fork %1
# sti r1, 2, %3
# st r1, r1
# lldi 1, %2, r3
# ldi 1, %2, r3
