	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4
	JMP main

	# label main
main:

	# begin

	# var i

	# var j

	# var arr1

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15
	STO (R2+8),R5

	# j = 0
	LOD R6,0
	STO (R2+12),R6

	# label L1
L1:

	# var t0

	# t0 = (j < 10)
	LOD R5,(R2+12)
	LOD R6,10
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t0 goto L2
	STO (R2+56),R5
	TST R5
	JEZ L2

	# var t1

	# t1 = &arr1
	LOD R7,R2
	LOD R8,16
	ADD R7,R8

	# var t3

	# var t2

	# t2 = j * 4
	LOD R8,(R2+12)
	LOD R9,4
	MUL R8,R9

	# t3 = t1 + t2
	ADD R7,R8
	STO (R2+60),R7

	# *t3 = i
	LOD R10,(R2+8)
	STO (R7+0),R10
	STO (R2+64),R7
	STO (R2+68),R8

	# var t4

	# t4 = i + 1
	LOD R5,(R2+8)
	LOD R6,1
	ADD R5,R6

	# i = t4
	STO (R2+72),R5
	STO (R2+8),R5

	# var t5

	# t5 = j + 1
	LOD R7,(R2+12)
	ADD R7,R6

	# j = t5
	STO (R2+76),R7
	STO (R2+12),R7

	# goto L1
	JMP L1

	# label L2
L2:

	# ifz 0 goto L4
	LOD R5,0
	TST R5
	JEZ L4

	# output L3
	LOD R6,L3
	LOD R15,R6
	OTS

	# label L4
L4:

	# label L5
L5:

	# var t6

	# t6 = (j > 0)
	LOD R5,(R2+12)
	LOD R6,0
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JGZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t6 goto L6
	STO (R2+80),R5
	TST R5
	JEZ L6

	# var t7

	# t7 = j - 1
	LOD R7,(R2+12)
	LOD R8,1
	SUB R7,R8

	# j = t7
	STO (R2+84),R7
	STO (R2+12),R7

	# var t8

	# t8 = &arr1
	LOD R9,R2
	LOD R10,16
	ADD R9,R10

	# var t10

	# var t9

	# t9 = j * 4
	LOD R10,4
	MUL R7,R10

	# t10 = t8 + t9
	ADD R9,R7
	STO (R2+88),R9

	# var t11

	# t11 = *t10
	LOD R11,(R9+0)

	# i = t11
	STO (R2+100),R11
	STO (R2+8),R11

	# output i
	LOD R15,R11
	OTI

	# goto L5
	STO (R2+96),R7
	STO (R2+92),R9
	JMP L5

	# label L6
L6:

	# output L3
	LOD R5,L3
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L3:
	DBS 10,0
STATIC:
	DBN 0,0
STACK:
