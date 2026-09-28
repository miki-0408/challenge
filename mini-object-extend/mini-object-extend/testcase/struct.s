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

	# var k

	# var zs

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15
	STO (R2+8),R5

	# input j
	LOD R6,(R2+12)
	ITI
	LOD R6,R15
	STO (R2+12),R6

	# input k
	LOD R7,(R2+16)
	ITI
	LOD R7,R15
	STO (R2+16),R7

	# var t0

	# t0 = &zs
	LOD R8,R2
	LOD R9,20
	ADD R8,R9

	# var t1

	# t1 = t0 + 0
	LOD R9,0
	ADD R8,R9
	STO (R2+32),R8

	# *t1 = i
	LOD R10,R5
	STO (R8+0),R10
	STO (R2+36),R8

	# var t2

	# t2 = &zs
	LOD R5,R2
	LOD R6,20
	ADD R5,R6

	# var t3

	# t3 = t2 + 4
	LOD R6,4
	ADD R5,R6
	STO (R2+40),R5

	# *t3 = j
	LOD R7,(R2+12)
	STO (R5+0),R7
	STO (R2+44),R5

	# var t4

	# t4 = &zs
	LOD R5,R2
	LOD R6,20
	ADD R5,R6

	# var t5

	# t5 = t4 + 8
	LOD R6,8
	ADD R5,R6
	STO (R2+48),R5

	# *t5 = k
	LOD R7,(R2+16)
	STO (R5+0),R7
	STO (R2+52),R5

	# ifz 0 goto L2
	LOD R5,0
	TST R5
	JEZ L2

	# output L1
	LOD R6,L1
	LOD R15,R6
	OTS

	# label L2
L2:

	# var t6

	# t6 = &zs
	LOD R5,R2
	LOD R6,20
	ADD R5,R6

	# var t7

	# t7 = t6 + 8
	LOD R6,8
	ADD R5,R6
	STO (R2+56),R5

	# var t8

	# t8 = *t7
	LOD R7,(R5+0)

	# var t9

	# t9 = t8 + 100
	LOD R8,100
	ADD R7,R8
	STO (R2+64),R7

	# i = t9
	STO (R2+68),R7
	STO (R2+8),R7

	# var t10

	# t10 = &zs
	LOD R9,R2
	LOD R10,20
	ADD R9,R10

	# var t11

	# t11 = t10 + 4
	LOD R10,4
	ADD R9,R10
	STO (R2+72),R9

	# var t12

	# t12 = *t11
	LOD R11,(R9+0)

	# var t13

	# t13 = t12 + 200
	LOD R12,200
	ADD R11,R12
	STO (R2+80),R11

	# j = t13
	STO (R2+84),R11
	STO (R2+12),R11

	# var t14

	# t14 = &zs
	LOD R13,R2
	LOD R14,20
	ADD R13,R14

	# var t15

	# t15 = t14 + 0
	LOD R14,0
	ADD R13,R14
	STO (R2+88),R13

	# var t16

	# t16 = *t15
	LOD R6,(R13+0)

	# var t17

	# t17 = t16 + 300
	LOD R7,300
	ADD R6,R7
	STO (R2+96),R6

	# k = t17
	STO (R2+100),R6
	STO (R2+16),R6

	# ifz 0 goto L3
	STO (R2+60),R5
	STO (R2+76),R9
	STO (R2+92),R13
	TST R14
	JEZ L3

	# output L1
	LOD R5,L1
	LOD R15,R5
	OTS

	# label L3
L3:

	# output i
	LOD R5,(R2+8)
	LOD R15,R5
	OTI

	# output j
	LOD R6,(R2+12)
	LOD R15,R6
	OTI

	# output k
	LOD R7,(R2+16)
	LOD R15,R7
	OTI

	# output L1
	LOD R8,L1
	LOD R15,R8
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
