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

	# var a

	# var b

	# var cls

	# var t0

	# t0 = &cls
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t2

	# var t1

	# t1 = 5 * 5554
	LOD R6,5
	LOD R7,5554
	MUL R6,R7

	# t2 = t0 + t1
	ADD R5,R6
	STO (R2+55558),R5

	# var t3

	# t3 = t2 + 0
	LOD R8,0
	ADD R5,R8
	STO (R2+55562),R5

	# *t3 = 1
	LOD R9,1
	STO (R5+0),R9
	STO (R2+55570),R5
	STO (R2+55566),R6

	# var t4

	# t4 = &cls
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t6

	# var t5

	# t5 = 5 * 5554
	LOD R6,5
	LOD R7,5554
	MUL R6,R7

	# t6 = t4 + t5
	ADD R5,R6
	STO (R2+55574),R5

	# var t7

	# t7 = t6 + 14
	LOD R8,14
	ADD R5,R8
	STO (R2+55578),R5

	# var t9

	# var t8

	# t8 = 2 * 554
	LOD R9,2
	LOD R10,554
	MUL R9,R10

	# t9 = t7 + t8
	ADD R5,R9
	STO (R2+55586),R5

	# var t10

	# t10 = t9 + 0
	LOD R11,0
	ADD R5,R11
	STO (R2+55590),R5

	# *t10 = 2
	LOD R12,2
	STO (R5+0),R12
	STO (R2+55598),R5
	STO (R2+55582),R6
	STO (R2+55594),R9

	# var t11

	# t11 = &cls
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t13

	# var t12

	# t12 = 5 * 5554
	LOD R6,5
	LOD R7,5554
	MUL R6,R7

	# t13 = t11 + t12
	ADD R5,R6
	STO (R2+55602),R5

	# var t14

	# t14 = t13 + 14
	LOD R8,14
	ADD R5,R8
	STO (R2+55606),R5

	# var t16

	# var t15

	# t15 = 2 * 554
	LOD R9,2
	LOD R10,554
	MUL R9,R10

	# t16 = t14 + t15
	ADD R5,R9
	STO (R2+55614),R5

	# var t17

	# t17 = t16 + 14
	ADD R5,R8
	STO (R2+55618),R5

	# var t19

	# var t18

	# t18 = 3 * 54
	LOD R11,3
	LOD R12,54
	MUL R11,R12

	# t19 = t17 + t18
	ADD R5,R11
	STO (R2+55626),R5

	# var t20

	# t20 = t19 + 4
	LOD R13,4
	ADD R5,R13
	STO (R2+55630),R5

	# var t22

	# var t21

	# t21 = 1 * 1
	LOD R14,1
	STO (R2+55638),R5
	LOD R5,R14
	MUL R5,R14

	# t22 = t20 + t21
	LOD R14,(R2+55638)
	ADD R14,R5

	# *t22 = 98
	LOD R7,98
	STC (R14+0),R7
	STO (R2+55646),R5
	STO (R2+55610),R6
	STO (R2+55622),R9
	STO (R2+55634),R11
	STO (R2+55642),R14

	# var t23

	# t23 = &cls
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t25

	# var t24

	# t24 = 5 * 5554
	LOD R6,5
	LOD R7,5554
	MUL R6,R7

	# t25 = t23 + t24
	ADD R5,R6
	STO (R2+55650),R5

	# var t26

	# t26 = t25 + 14
	LOD R8,14
	ADD R5,R8
	STO (R2+55654),R5

	# var t28

	# var t27

	# t27 = 2 * 554
	LOD R9,2
	LOD R10,554
	MUL R9,R10

	# t28 = t26 + t27
	ADD R5,R9
	STO (R2+55662),R5

	# var t29

	# t29 = t28 + 14
	ADD R5,R8
	STO (R2+55666),R5

	# var t31

	# var t30

	# t30 = 3 * 54
	LOD R11,3
	LOD R12,54
	MUL R11,R12

	# t31 = t29 + t30
	ADD R5,R11
	STO (R2+55674),R5

	# var t32

	# t32 = t31 + 4
	LOD R13,4
	ADD R5,R13
	STO (R2+55678),R5

	# var t34

	# var t33

	# t33 = 0 * 1
	LOD R14,0
	LOD R7,1
	MUL R14,R7

	# t34 = t32 + t33
	ADD R5,R14
	STO (R2+55686),R5

	# *t34 = 97
	LOD R7,97
	STC (R5+0),R7
	STO (R2+55690),R5
	STO (R2+55658),R6
	STO (R2+55670),R9
	STO (R2+55682),R11
	STO (R2+55694),R14

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

	# var t35

	# t35 = &cls
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t37

	# var t36

	# t36 = 5 * 5554
	LOD R6,5
	LOD R7,5554
	MUL R6,R7

	# t37 = t35 + t36
	ADD R5,R6
	STO (R2+55698),R5

	# var t38

	# t38 = t37 + 0
	LOD R8,0
	ADD R5,R8
	STO (R2+55702),R5

	# var t39

	# t39 = *t38
	LOD R9,(R5+0)

	# i = t39
	STO (R2+55714),R9
	STO (R2+8),R9

	# var t40

	# t40 = &cls
	LOD R10,R2
	LOD R11,18
	ADD R10,R11

	# var t42

	# var t41

	# t41 = 5 * 5554
	LOD R11,5
	MUL R11,R7

	# t42 = t40 + t41
	ADD R10,R11
	STO (R2+55718),R10

	# var t43

	# t43 = t42 + 14
	LOD R12,14
	ADD R10,R12
	STO (R2+55722),R10

	# var t45

	# var t44

	# t44 = 2 * 554
	LOD R13,2
	LOD R14,554
	MUL R13,R14

	# t45 = t43 + t44
	ADD R10,R13
	STO (R2+55730),R10

	# var t46

	# t46 = t45 + 0
	ADD R10,R8
	STO (R2+55734),R10

	# var t47

	# t47 = *t46
	LOD R7,(R10+0)

	# j = t47
	STO (R2+55746),R7
	STO (R2+12),R7

	# var t48

	# t48 = &cls
	LOD R7,R2
	LOD R8,18
	ADD R7,R8

	# var t50

	# var t49

	# t49 = 5 * 5554
	LOD R8,5
	LOD R8,5554
	LOD R9,5
	MUL R9,R8

	# t50 = t48 + t49
	ADD R7,R9
	STO (R2+55750),R7

	# var t51

	# t51 = t50 + 14
	ADD R7,R12
	STO (R2+55754),R7

	# var t53

	# var t52

	# t52 = 2 * 554
	LOD R8,2
	MUL R8,R14

	# t53 = t51 + t52
	ADD R7,R8
	STO (R2+55762),R7

	# var t54

	# t54 = t53 + 14
	ADD R7,R12
	STO (R2+55766),R7

	# var t56

	# var t55

	# t55 = 3 * 54
	LOD R12,3
	LOD R12,54
	STO (R2+55738),R13
	LOD R13,3
	MUL R13,R12

	# t56 = t54 + t55
	ADD R7,R13
	STO (R2+55774),R7

	# var t57

	# t57 = t56 + 4
	LOD R12,4
	ADD R7,R12
	STO (R2+55778),R7

	# var t59

	# var t58

	# t58 = 0 * 1
	LOD R12,0
	LOD R12,1
	STO (R2+55782),R13
	LOD R13,0
	MUL R13,R12

	# t59 = t57 + t58
	ADD R7,R13
	STO (R2+55786),R7

	# var t60

	# t60 = *t59
	LDC R12,(R7+0)

	# a = t60
	STC (R2+55798),R12
	STC (R2+16),R12

	# var t61

	# t61 = &cls
	LOD R12,R2
	LOD R14,18
	ADD R12,R14

	# var t63

	# var t62

	# t62 = 5 * 5554
	LOD R14,5
	LOD R14,5554
	STO (R2+55710),R5
	LOD R5,5
	MUL R5,R14

	# t63 = t61 + t62
	ADD R12,R5
	STO (R2+55799),R12

	# var t64

	# t64 = t63 + 14
	LOD R14,14
	ADD R12,R14
	STO (R2+55803),R12

	# var t66

	# var t65

	# t65 = 2 * 554
	LOD R14,2
	LOD R14,554
	STO (R2+55807),R5
	LOD R5,2
	MUL R5,R14

	# t66 = t64 + t65
	ADD R12,R5
	STO (R2+55811),R12

	# var t67

	# t67 = t66 + 14
	LOD R14,14
	ADD R12,R14
	STO (R2+55815),R12

	# var t69

	# var t68

	# t68 = 3 * 54
	LOD R14,3
	LOD R14,54
	STO (R2+55819),R5
	LOD R5,3
	MUL R5,R14

	# t69 = t67 + t68
	ADD R12,R5
	STO (R2+55823),R12

	# var t70

	# t70 = t69 + 4
	LOD R14,4
	ADD R12,R14
	STO (R2+55827),R12

	# var t72

	# var t71

	# t71 = 1 * 1
	LOD R14,1
	STO (R2+55831),R5
	LOD R5,R14
	MUL R5,R14

	# t72 = t70 + t71
	ADD R12,R5
	STO (R2+55835),R12

	# var t73

	# t73 = *t72
	LDC R14,(R12+0)

	# b = t73
	STC (R2+55847),R14
	STC (R2+17),R14

	# ifz 0 goto L3
	STO (R2+55843),R5
	STO (R2+55706),R6
	STO (R2+55790),R7
	STO (R2+55770),R8
	STO (R2+55758),R9
	STO (R2+55742),R10
	STO (R2+55726),R11
	STO (R2+55839),R12
	STO (R2+55794),R13
	LOD R5,0
	TST R5
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

	# output a
	LDC R7,(R2+16)
	LOD R15,R7
	OTC

	# output b
	LDC R8,(R2+17)
	LOD R15,R8
	OTC

	# output L1
	LOD R9,L1
	LOD R15,R9
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
