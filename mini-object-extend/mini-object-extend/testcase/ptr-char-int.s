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

	# var i

	# var pi

	# var j

	# input a
	LDC R5,(R2+8)
	ITC
	LOD R5,R15
	STC (R2+8),R5

	# input i
	LOD R6,(R2+14)
	ITI
	LOD R6,R15
	STO (R2+14),R6

	# ifz 0 goto L2
	LOD R7,0
	TST R7
	JEZ L2

	# output L1
	LOD R8,L1
	LOD R15,R8
	OTS

	# label L2
L2:

	# var t0

	# t0 = &a
	LOD R5,R2
	LOD R6,8
	ADD R5,R6

	# pa = t0
	STO (R2+26),R5
	STO (R2+9),R5

	# var t1

	# t1 = &i
	LOD R6,R2
	LOD R7,14
	ADD R6,R7

	# pi = t1
	STO (R2+30),R6
	STO (R2+18),R6

	# var t2

	# t2 = *pa
	LDC R7,(R5+0)

	# b = t2
	STC (R2+34),R7
	STC (R2+13),R7

	# var t3

	# t3 = *pi
	LOD R8,(R6+0)

	# j = t3
	STO (R2+35),R8
	STO (R2+22),R8

	# ifz 0 goto L3
	LOD R9,0
	TST R9
	JEZ L3

	# output L1
	LOD R10,L1
	LOD R15,R10
	OTS

	# label L3
L3:

	# output b
	LDC R5,(R2+13)
	LOD R15,R5
	OTC

	# output j
	LOD R6,(R2+22)
	LOD R15,R6
	OTI

	# output L1
	LOD R7,L1
	LOD R15,R7
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
