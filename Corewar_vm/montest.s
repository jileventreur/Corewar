.name		"mabi"
.comment	"jtecris dessus"

prep_live:
	sti		r1, %:live1, %1
	sti		r1, %:live2, %1

live1:
	live	%255

prep_jump:
	ld		4294967295, r2
	ld		%0, r16

live2:
	live	%255

go_son:
	fork	%:trap

jmp1:
	zjmp	%:jmp2

jmp2:
	zjmp	%20

trap:
	sti		r2, %:prep_live, %0
