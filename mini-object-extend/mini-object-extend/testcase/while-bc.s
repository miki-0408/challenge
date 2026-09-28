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

	# i = 0
	LOD R5,0
	STO (R2+8),R5

	# input j
	LOD R6,(R2+12)
	ITI
	LOD R6,R15
	STO (R2+12),R6

	# label L3
L3:

	# var t0

	# t0 = (i < j)
	LOD R5,(R2+8)
	LOD R6,(R2+12)
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t0 goto L4
	STO (R2+16),R5
	TST R5
	JEZ L4

	# output i
	LOD R7,(R2+8)
	LOD R15,R7
	OTI

	# var t1

	# t1 = i + 1
	LOD R8,1
	ADD R7,R8

	# i = t1
	STO (R2+20),R7
	STO (R2+8),R7

	# var t2

	# t2 = (i > 10)
	LOD R9,10
	SUB R7,R9
	TST R7
	LOD R3,R1+40
	JGZ R3
	LOD R7,0
	LOD R3,R1+24
	JMP R3
	LOD R7,1

	# ifz t2 goto L2
	STO (R2+24),R7
	TST R7
	JEZ L2

	# output L1
	LOD R10,L1
	LOD R15,R10
	OTS

	# goto L4
	JMP L4

	# label L2
L2:

	# goto L3
	JMP L3

	# label L4
L4:

	# output L5
	LOD R5,L5
	LOD R15,R5
	OTS

	# label L8
L8:

	# var t3

	# t3 = (i < j)
	LOD R5,(R2+8)
	LOD R6,(R2+12)
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t3 goto L9
	STO (R2+28),R5
	TST R5
	JEZ L9

	# output i
	LOD R7,(R2+8)
	LOD R15,R7
	OTI

	# var t4

	# t4 = i + 1
	LOD R8,1
	ADD R7,R8

	# i = t4
	STO (R2+32),R7
	STO (R2+8),R7

	# var t5

	# t5 = (i == 10)
	LOD R9,10
	SUB R7,R9
	TST R7
	LOD R3,R1+40
	JEZ R3
	LOD R7,0
	LOD R3,R1+24
	JMP R3
	LOD R7,1

	# ifz t5 goto L7
	STO (R2+36),R7
	TST R7
	JEZ L7

	# output L6
	LOD R10,L6
	LOD R15,R10
	OTS

	# goto L8
	JMP L8

	# label L7
L7:

	# goto L8
	JMP L8

	# label L9
L9:

	# output L5
	LOD R5,L5
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L6:
	DBS 99,111,110,116,105,110,117,101,0
L5:
	DBS 10,0
L1:
	DBS 98,114,101,97,107,0
STATIC:
	DBN 0,0
STACK:
