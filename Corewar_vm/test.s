.name "zork"
.comment "I'M ALIIIIVE"

# l2:		sti r1, %:live, %1
		# and r1, %0, r1

# live:	live %1
		# zjmp %:live

# xor %1, %4, r3
# and %4, %3, r3
# or %0, %0, r3
# add r1, r3, r4
# sub r1, r3, r4
# lld %0, r2
# ldi %:end, %:end, r3
# sti r3, r3, r3
# lldi %1, %2, r3


# aff r1
# live %1

# ld %1, r2
lfork %:end
# st r2, r2
# jmp: zjmp %:end
end:
# fork %1
