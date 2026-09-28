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

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15
	STO (R2+8),R5

	# var t3

	# t3 = i
	STO (R2+16),R5

	# var t4

	# t4 = (t3 == 3)
	LOD R6,3
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t4 goto L7
	STO (R2+20),R5
	TST R5
	JEZ L7

	# goto L4
	JMP L4

	# label L7
L7:

	# var t5

	# t5 = (t3 == 2)
	LOD R5,(R2+16)
	LOD R6,2
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t5 goto L8
	STO (R2+24),R5
	TST R5
	JEZ L8

	# goto L3
	JMP L3

	# label L8
L8:

	# var t6

	# t6 = (t3 == 1)
	LOD R5,(R2+16)
	LOD R6,1
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t6 goto L9
	STO (R2+28),R5
	TST R5
	JEZ L9

	# goto L2
	JMP L2

	# label L9
L9:

	# goto L6
	JMP L6

	# label L6
L6:

	# output L5
	LOD R5,L5
	LOD R15,R5
	OTS

	# goto L1
	JMP L1

	# label L4
L4:

	# var t2

	# t2 = i + 3
	LOD R5,(R2+8)
	LOD R6,3
	ADD R5,R6

	# j = t2
	STO (R2+32),R5
	STO (R2+12),R5

	# output j
	LOD R15,R5
	OTI

	# goto L1
	JMP L1

	# label L3
L3:

	# var t1

	# t1 = i + 2
	LOD R5,(R2+8)
	LOD R6,2
	ADD R5,R6

	# j = t1
	STO (R2+36),R5
	STO (R2+12),R5

	# output j
	LOD R15,R5
	OTI

	# goto L1
	JMP L1

	# label L2
L2:

	# var t0

	# t0 = i + 1
	LOD R5,(R2+8)
	LOD R6,1
	ADD R5,R6

	# j = t0
	STO (R2+40),R5
	STO (R2+12),R5

	# output j
	LOD R15,R5
	OTI

	# goto L1
	JMP L1

	# label L1
L1:

	# output L10
	LOD R5,L10
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L10:
	DBS 10,0
L5:
	DBS 110,111,116,32,49,32,50,32,51,0
STATIC:
	DBN 0,0
STACK:
