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

	# input j
	LOD R5,(R2+12)
	ITI
	LOD R5,R15
	STO (R2+12),R5

	# i = 0
	LOD R6,0
	STO (R2+8),R6

	# label L1
L1:

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

	# ifz t0 goto L3
	STO (R2+16),R5
	TST R5
	JEZ L3

	# output i
	LOD R7,(R2+8)
	LOD R15,R7
	OTI

	# label L2
L2:

	# var t1

	# t1 = i + 1
	LOD R5,(R2+8)
	LOD R6,1
	ADD R5,R6

	# i = t1
	STO (R2+20),R5
	STO (R2+8),R5

	# goto L1
	JMP L1

	# label L3
L3:

	# output L4
	LOD R5,L4
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L4:
	DBS 10,0
STATIC:
	DBN 0,0
STACK:
