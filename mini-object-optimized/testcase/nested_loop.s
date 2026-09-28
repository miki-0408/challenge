	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var i

	# var k

	# k = 0
	LOD R5,0

	# label L5
	STO (R2+12),R5
L5:

	# var t0

	# t0 = (k < 10)
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

	# ifz t0 goto L6
	STO (R2+16),R5
	TST R5
	JEZ L6

	# i = 0
	LOD R7,0

	# label L2
	STO (R2+8),R7
L2:

	# var t1

	# t1 = (i < 10)
	LOD R5,(R2+8)
	LOD R6,10
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t1 goto L3
	STO (R2+20),R5
	TST R5
	JEZ L3

	# var t2

	# t2 = i + i
	LOD R7,(R2+8)
	ADD R7,R7

	# var t3

	# t3 = t2 + 9
	LOD R8,9
	ADD R7,R8

	# output t3
	LOD R15,R7
	OTI

	# output L1
	LOD R9,L1
	LOD R15,R9
	OTS

	# var t4

	# t4 = i + 1
	LOD R10,(R2+8)
	LOD R11,1
	ADD R10,R11

	# i = t4

	# goto L2
	STO (R2+28),R7
	STO (R2+8),R10
	JMP L2

	# label L3
L3:

	# output L4
	LOD R5,L4
	LOD R15,R5
	OTS

	# var t5

	# t5 = k + 1
	LOD R6,(R2+12)
	LOD R7,1
	ADD R6,R7

	# k = t5

	# goto L5
	STO (R2+12),R6
	JMP L5

	# label L6
L6:

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L4:
	DBS 10,0
L1:
	DBS 32,0
STATIC:
	DBN 0,0
STACK:
