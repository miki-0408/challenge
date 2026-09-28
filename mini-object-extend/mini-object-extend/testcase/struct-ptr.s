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

	# var pi

	# var a

	# var b

	# var pc

	# var c1

	# var t0

	# t0 = &c1
	LOD R5,R2
	LOD R6,26
	ADD R5,R6

	# var t1

	# t1 = t0 + 14
	LOD R6,14
	ADD R5,R6
	STO (R2+5580),R5

	# var t3

	# var t2

	# t2 = 2 * 554
	LOD R7,2
	LOD R8,554
	MUL R7,R8

	# t3 = t1 + t2
	ADD R5,R7
	STO (R2+5584),R5

	# var t4

	# t4 = t3 + 14
	ADD R5,R6
	STO (R2+5588),R5

	# var t6

	# var t5

	# t5 = 3 * 54
	LOD R9,3
	LOD R10,54
	MUL R9,R10

	# t6 = t4 + t5
	ADD R5,R9
	STO (R2+5596),R5

	# var t9

	# t9 = t6 + 0
	LOD R11,0
	ADD R5,R11
	STO (R2+5600),R5

	# var t7

	# t7 = &c1
	LOD R12,R2
	LOD R13,26
	ADD R12,R13

	# var t8

	# t8 = t7 + 0
	ADD R12,R11
	STO (R2+5612),R12

	# *t9 = t8
	LOD R13,R12
	STO (R5+0),R13
	STO (R2+5608),R5
	STO (R2+5592),R7
	STO (R2+5604),R9

	# var t10

	# t10 = &c1
	LOD R5,R2
	LOD R6,26
	ADD R5,R6

	# var t11

	# t11 = t10 + 14
	LOD R6,14
	ADD R5,R6
	STO (R2+5620),R5

	# var t13

	# var t12

	# t12 = 2 * 554
	LOD R7,2
	LOD R8,554
	MUL R7,R8

	# t13 = t11 + t12
	ADD R5,R7
	STO (R2+5624),R5

	# var t14

	# t14 = t13 + 14
	ADD R5,R6
	STO (R2+5628),R5

	# var t16

	# var t15

	# t15 = 3 * 54
	LOD R9,3
	LOD R10,54
	MUL R9,R10

	# t16 = t14 + t15
	ADD R5,R9
	STO (R2+5636),R5

	# var t17

	# t17 = t16 + 0
	LOD R11,0
	ADD R5,R11
	STO (R2+5640),R5

	# var t18

	# t18 = *t17
	LOD R12,(R5+0)

	# pi = t18
	STO (R2+5652),R12
	STO (R2+16),R12

	# *pi = 999
	LOD R13,999
	STO (R12+0),R13
	STO (R2+5648),R5
	STO (R2+5632),R7
	STO (R2+5644),R9

	# var t19

	# t19 = &c1
	LOD R5,R2
	LOD R6,26
	ADD R5,R6

	# var t20

	# t20 = t19 + 0
	LOD R6,0
	ADD R5,R6
	STO (R2+5656),R5

	# var t21

	# t21 = *t20
	LOD R7,(R5+0)

	# i = t21
	STO (R2+5664),R7
	STO (R2+8),R7

	# output i
	LOD R15,R7
	OTI

	# output L1
	LOD R8,L1
	LOD R15,R8
	OTS

	# end
	STO (R2+5660),R5
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
