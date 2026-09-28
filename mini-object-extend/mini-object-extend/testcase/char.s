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

	# input d
	LDC R5,(R2+11)
	ITC
	LOD R5,R15
	STC (R2+11),R5

	# c = 99
	LOD R6,99
	STC (R2+10),R6

	# b = 98
	LOD R7,98
	STC (R2+9),R7

	# input a
	LDC R8,(R2+8)
	ITC
	LOD R8,R15
	STC (R2+8),R8

	# ifz 0 goto L2
	LOD R9,0
	TST R9
	JEZ L2

	# output L1
	LOD R10,L1
	LOD R15,R10
	OTS

	# label L2
L2:

	# output a
	LDC R5,(R2+8)
	LOD R15,R5
	OTC

	# output b
	LDC R6,(R2+9)
	LOD R15,R6
	OTC

	# output c
	LDC R7,(R2+10)
	LOD R15,R7
	OTC

	# output d
	LDC R8,(R2+11)
	LOD R15,R8
	OTC

	# output L1
	LOD R9,L1
	LOD R15,R9
	OTS

	# var t0

	# t0 = a + 1
	LOD R10,1
	ADD R5,R10

	# a = t0
	STO (R2+12),R5
	STC (R2+8),R5

	# output a
	LOD R15,R5
	OTC

	# output L1
	LOD R15,R9
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
