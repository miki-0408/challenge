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

	# var arr2

	# var arr3

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15
	STO (R2+8),R5

	# var t0

	# t0 = &arr1
	LOD R6,R2
	LOD R7,16
	ADD R6,R7

	# var t2

	# var t1

	# t1 = 6 * 4
	LOD R7,6
	LOD R8,4
	MUL R7,R8

	# t2 = t0 + t1
	ADD R6,R7
	STO (R2+24856),R6

	# *t2 = i
	LOD R9,R5
	STO (R6+0),R9
	STO (R2+24860),R6
	STO (R2+24864),R7

	# var t3

	# t3 = &arr2
	LOD R5,R2
	LOD R6,56
	ADD R5,R6

	# var t5

	# var t4

	# t4 = 6 * 80
	LOD R6,6
	LOD R7,80
	MUL R6,R7

	# t5 = t3 + t4
	ADD R5,R6
	STO (R2+24868),R5

	# var t12

	# var t11

	# t11 = 6 * 4
	LOD R8,6
	LOD R9,4
	MUL R8,R9

	# t12 = t5 + t11
	ADD R5,R8
	STO (R2+24872),R5

	# var t6

	# t6 = &arr1
	LOD R10,R2
	LOD R11,16
	ADD R10,R11

	# var t8

	# var t7

	# t7 = 6 * 4
	LOD R11,6
	MUL R11,R9

	# t8 = t6 + t7
	ADD R10,R11
	STO (R2+24888),R10

	# var t9

	# t9 = *t8
	LOD R12,(R10+0)

	# var t10

	# t10 = t9 + 6
	LOD R13,6
	ADD R12,R13
	STO (R2+24900),R12

	# *t12 = t10
	LOD R14,R12
	STO (R5+0),R14
	STO (R2+24880),R5
	STO (R2+24876),R6
	STO (R2+24884),R8
	STO (R2+24892),R10
	STO (R2+24896),R11

	# var t13

	# t13 = &arr3
	LOD R5,R2
	LOD R6,856
	ADD R5,R6

	# var t15

	# var t14

	# t14 = 6 * 2400
	LOD R6,6
	LOD R7,2400
	MUL R6,R7

	# t15 = t13 + t14
	ADD R5,R6
	STO (R2+24908),R5

	# var t17

	# var t16

	# t16 = 6 * 120
	LOD R8,6
	LOD R9,120
	MUL R8,R9

	# t17 = t15 + t16
	ADD R5,R8
	STO (R2+24912),R5

	# var t26

	# var t25

	# t25 = 6 * 4
	LOD R10,6
	LOD R11,4
	MUL R10,R11

	# t26 = t17 + t25
	ADD R5,R10
	STO (R2+24920),R5

	# var t18

	# t18 = &arr2
	LOD R12,R2
	LOD R13,56
	ADD R12,R13

	# var t20

	# var t19

	# t19 = 6 * 80
	LOD R13,6
	LOD R14,80
	MUL R13,R14

	# t20 = t18 + t19
	ADD R12,R13
	STO (R2+24936),R12

	# var t22

	# var t21

	# t21 = 6 * 4
	LOD R7,6
	MUL R7,R11

	# t22 = t20 + t21
	ADD R12,R7
	STO (R2+24940),R12

	# var t23

	# t23 = *t22
	LOD R9,(R12+0)

	# var t24

	# t24 = t23 + 6
	LOD R11,6
	ADD R9,R11
	STO (R2+24956),R9

	# *t26 = t24
	LOD R11,R9
	STO (R5+0),R11
	STO (R2+24928),R5
	STO (R2+24916),R6
	STO (R2+24952),R7
	STO (R2+24924),R8
	STO (R2+24932),R10
	STO (R2+24948),R12
	STO (R2+24944),R13

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

	# var t27

	# t27 = &arr3
	LOD R5,R2
	LOD R6,856
	ADD R5,R6

	# var t29

	# var t28

	# t28 = 6 * 2400
	LOD R6,6
	LOD R7,2400
	MUL R6,R7

	# t29 = t27 + t28
	ADD R5,R6
	STO (R2+24964),R5

	# var t31

	# var t30

	# t30 = 6 * 120
	LOD R8,6
	LOD R9,120
	MUL R8,R9

	# t31 = t29 + t30
	ADD R5,R8
	STO (R2+24968),R5

	# var t33

	# var t32

	# t32 = 6 * 4
	LOD R10,6
	LOD R11,4
	MUL R10,R11

	# t33 = t31 + t32
	ADD R5,R10
	STO (R2+24976),R5

	# var t34

	# t34 = *t33
	LOD R12,(R5+0)

	# j = t34
	STO (R2+24992),R12
	STO (R2+12),R12

	# output j
	LOD R15,R12
	OTI

	# output L1
	LOD R13,L1
	LOD R15,R13
	OTS

	# end
	STO (R2+24984),R5
	STO (R2+24972),R6
	STO (R2+24980),R8
	STO (R2+24988),R10
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
