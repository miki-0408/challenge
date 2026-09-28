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

	# var pa

	# var b

	# var c

	# var d

	# var ptr

	# input d
	LDC R5,(R2+15)
	ITC
	LOD R5,R15
	STC (R2+15),R5

	# c = 99
	LOD R6,99
	STC (R2+14),R6

	# b = 98
	LOD R7,98
	STC (R2+13),R7

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
	LDC R6,(R2+13)
	LOD R15,R6
	OTC

	# output c
	LDC R7,(R2+14)
	LOD R15,R7
	OTC

	# output d
	LDC R8,(R2+15)
	LOD R15,R8
	OTC

	# output L1
	LOD R9,L1
	LOD R15,R9
	OTS

	# var t0

	# t0 = &a
	LOD R10,R2
	LOD R11,8
	ADD R10,R11

	# pa = t0
	STO (R2+20),R10
	STO (R2+9),R10

	# *pa = 65
	LOD R11,65
	STC (R10+0),R11

	# output a
	LDC R5,(R2+8)
	LOD R15,R5
	OTC

	# ptr = pa
	LOD R6,(R2+9)
	STO (R2+16),R6

	# *ptr = 66
	LOD R7,66
	STC (R6+0),R7

	# output a
	LDC R5,(R2+8)
	LOD R15,R5
	OTC

	# output L1
	LOD R6,L1
	LOD R15,R6
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
