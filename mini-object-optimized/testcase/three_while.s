	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var sumd

	# var sume

	# var i

	# var j

	# var k

	# sumd = 0
	LOD R5,0

	# sume = 0
	LOD R6,0

	# k = 12
	LOD R7,12

	# label L11
	STO (R2+8),R5
	STO (R2+12),R6
	STO (R2+24),R7
L11:

	# var t45

	# t45 = 2 * 3
	LOD R5,2
	LOD R6,3
	MUL R5,R6

	# var t46

	# t46 = 1 + t45
	LOD R7,1
	ADD R7,R5

	# var t47

	# t47 = 1 + 3
	LOD R8,1
	ADD R8,R6

	# var t48

	# t48 = t47 / 2
	LOD R9,2
	DIV R8,R9

	# var t49

	# t49 = t46 - t48
	SUB R7,R8

	# var t50

	# t50 = t49 + 9
	LOD R10,9
	ADD R7,R10

	# var t52

	# t52 = 1 + t45
	LOD R11,1
	ADD R11,R5

	# var t53

	# t53 = 3 - 1
	LOD R12,1
	SUB R6,R12

	# var t54

	# t54 = t53 / 2
	DIV R6,R9

	# var t55

	# t55 = t52 - t54
	SUB R11,R6

	# var t56

	# t56 = t55 + 13
	LOD R13,13
	ADD R11,R13

	# label L5
	STO (R2+28),R5
	STO (R2+60),R6
	STO (R2+48),R7
	STO (R2+40),R8
	STO (R2+68),R11
L5:

	# var t0

	# t0 = (k > 0)
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

	# ifz t0 goto L6
	STO (R2+72),R5
	TST R5
	JEZ L6

	# j = 15
	LOD R7,15

	# label L10
	STO (R2+20),R7
L10:

	# label L3
L3:

	# var t1

	# t1 = (j > 0)
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

	# ifz t1 goto L4
	STO (R2+76),R5
	TST R5
	JEZ L4

	# i = 18
	LOD R7,18

	# label L9
	STO (R2+16),R7
L9:

	# label L1
L1:

	# var t2

	# t2 = (i > 0)
	LOD R5,(R2+16)
	LOD R6,0
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JGZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t2 goto L2
	STO (R2+80),R5
	TST R5
	JEZ L2

	# var t15

	# t15 = sumd + t50
	LOD R7,(R2+8)
	LOD R8,(R2+48)
	ADD R7,R8

	# sumd = t15

	# var t16

	# t16 = sume + t56
	LOD R9,(R2+12)
	LOD R10,(R2+68)
	ADD R9,R10

	# var t17

	# t17 = t16 + t50
	ADD R9,R8

	# sume = t17

	# var t18

	# t18 = i - 1
	LOD R11,(R2+16)
	LOD R12,1
	SUB R11,R12

	# i = t18

	# goto L1
	STO (R2+8),R7
	STO (R2+12),R9
	STO (R2+16),R11
	JMP L1

	# label L2
L2:

	# var t19

	# t19 = j - 1
	LOD R5,(R2+20)
	LOD R6,1
	SUB R5,R6

	# j = t19

	# goto L3
	STO (R2+20),R5
	JMP L3

	# label L4
L4:

	# var t20

	# t20 = k - 1
	LOD R5,(R2+24)
	LOD R6,1
	SUB R5,R6

	# k = t20

	# goto L5
	STO (R2+24),R5
	JMP L5

	# label L6
L6:

	# output sumd
	LOD R5,(R2+8)
	LOD R15,R5
	OTI

	# output L7
	LOD R6,L7
	LOD R15,R6
	OTS

	# output sume
	LOD R7,(R2+12)
	LOD R15,R7
	OTI

	# output L8
	LOD R8,L8
	LOD R15,R8
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L8:
	DBS 10,0
L7:
	DBS 32,0
STATIC:
	DBN 0,0
STACK:
