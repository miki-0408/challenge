	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var a

	# var b

	# var c

	# var i

	# var j

	# input a
	LOD R5,(R2+8)
	ITI
	LOD R5,R15

	# input b
	LOD R6,(R2+12)
	ITI
	LOD R6,R15

	# input c
	LOD R7,(R2+16)
	ITI
	LOD R7,R15

	# j = 5
	LOD R8,5

	# label L8
	STO (R2+8),R5
	STO (R2+12),R6
	STO (R2+16),R7
	STO (R2+24),R8
L8:

	# var t28

	# t28 = b * c
	LOD R5,(R2+12)
	LOD R6,(R2+16)
	MUL R5,R6

	# var t29

	# t29 = a + t28
	LOD R7,(R2+8)
	ADD R7,R5

	# var t30

	# t30 = a + c
	LOD R8,(R2+8)
	ADD R8,R6

	# var t31

	# t31 = t30 / b
	LOD R9,(R2+12)
	DIV R8,R9

	# var t32

	# t32 = t29 - t31
	SUB R7,R8

	# var t33

	# t33 = t32 + 9
	LOD R10,9
	ADD R7,R10

	# var t35

	# t35 = a + t28
	LOD R11,(R2+8)
	ADD R11,R5

	# var t36

	# t36 = c - a
	LOD R12,(R2+8)
	SUB R6,R12

	# var t37

	# t37 = t36 / b
	DIV R6,R9

	# var t38

	# t38 = t35 - t37
	SUB R11,R6

	# var t39

	# t39 = t38 + 9
	ADD R11,R10

	# label L4
	STO (R2+28),R5
	STO (R2+60),R6
	STO (R2+48),R7
	STO (R2+40),R8
	STO (R2+68),R11
L4:

	# var t0

	# t0 = (j > 0)
	LOD R5,(R2+24)
	LOD R6,0
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JGZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t0 goto L5
	STO (R2+72),R5
	TST R5
	JEZ L5

	# output j
	LOD R7,(R2+24)
	LOD R15,R7
	OTI

	# i = 9
	LOD R8,9

	# label L7
	STO (R2+20),R8
L7:

	# label L1
L1:

	# var t1

	# t1 = (i > 0)
	LOD R5,(R2+20)
	LOD R6,0
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JGZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t1 goto L2
	STO (R2+76),R5
	TST R5
	JEZ L2

	# output i
	LOD R7,(R2+20)
	LOD R15,R7
	OTI

	# var t14

	# t14 = i - 1
	LOD R8,1
	SUB R7,R8

	# i = t14

	# goto L1
	STO (R2+20),R7
	JMP L1

	# label L2
L2:

	# var t15

	# t15 = j - 1
	LOD R5,(R2+24)
	LOD R6,1
	SUB R5,R6

	# j = t15

	# output L3
	LOD R7,L3
	LOD R15,R7
	OTS

	# goto L4
	STO (R2+24),R5
	JMP L4

	# label L5
L5:

	# output L6
	LOD R5,L6
	LOD R15,R5
	OTS

	# output t33
	LOD R6,(R2+48)
	LOD R15,R6
	OTI

	# output L3
	LOD R7,L3
	LOD R15,R7
	OTS

	# output t39
	LOD R8,(R2+68)
	LOD R15,R8
	OTI

	# output L6
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
	DBS 10,0
L3:
	DBS 32,0
STATIC:
	DBN 0,0
STACK:
