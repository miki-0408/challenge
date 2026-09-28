	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4
	JMP main

	# label main
main:

	# begin

	# var a

	# var b

	# var c

	# var d

	# input a
	LOD R5,(R2+8)
	ITI
	LOD R5,R15
	STO (R2+8),R5

	# var t0

	# t0 = a + 10
	LOD R6,10
	ADD R5,R6

	# b = t0
	STO (R2+24),R5
	STO (R2+12),R5

	# var t1

	# t1 = b - 20
	LOD R7,20
	SUB R5,R7

	# c = t1
	STO (R2+28),R5
	STO (R2+16),R5

	# var t2

	# t2 = c * 30
	LOD R8,30
	MUL R5,R8

	# d = t2
	STO (R2+32),R5
	STO (R2+20),R5

	# output a
	LOD R9,(R2+8)
	LOD R15,R9
	OTI

	# output b
	LOD R10,(R2+12)
	LOD R15,R10
	OTI

	# output c
	LOD R11,(R2+16)
	LOD R15,R11
	OTI

	# output d
	LOD R15,R5
	OTI

	# output L1
	LOD R12,L1
	LOD R15,R12
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L1:
	DBS 10,0
STATIC:
	DBN 0,0
STACK:
