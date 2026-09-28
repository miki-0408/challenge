	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var i

	# var temp

	# var temp2

	# temp = 56422
	LOD R5,56422

	# i = 0
	LOD R6,0

	# label L59
	STO (R2+12),R5
	STO (R2+8),R6
L59:

	# var t0

	# t0 = (i < 12)
	LOD R5,(R2+8)
	LOD R6,12
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t0 goto L60
	STO (R2+20),R5
	TST R5
	JEZ L60

	# temp2 = 0
	LOD R7,0

	# var t1

	# t1 = (temp == 7340)
	LOD R8,(R2+12)
	LOD R9,7340
	SUB R8,R9
	TST R8
	LOD R3,R1+40
	JEZ R3
	LOD R8,0
	LOD R3,R1+24
	JMP R3
	LOD R8,1

	# ifz t1 goto L2
	STO (R2+16),R7
	STO (R2+24),R8
	TST R8
	JEZ L2

	# var t2

	# t2 = 50636 * i
	LOD R10,50636
	LOD R11,(R2+8)
	MUL R10,R11

	# var t3

	# t3 = temp - t2
	LOD R12,(R2+12)
	SUB R12,R10

	# temp2 = t3

	# output L1
	LOD R7,L1
	LOD R15,R7
	OTS

	# label L2
	STO (R2+28),R10
	STO (R2+16),R12
L2:

	# var t4

	# t4 = (temp == 28935)
	LOD R5,(R2+12)
	LOD R6,28935
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t4 goto L4
	STO (R2+36),R5
	TST R5
	JEZ L4

	# var t5

	# t5 = 2027 * i
	LOD R7,2027
	LOD R8,(R2+8)
	MUL R7,R8

	# var t6

	# t6 = temp - t5
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t6

	# output L3
	LOD R10,L3
	LOD R15,R10
	OTS

	# label L4
	STO (R2+40),R7
	STO (R2+16),R9
L4:

	# var t7

	# t7 = (temp == 26028)
	LOD R5,(R2+12)
	LOD R6,26028
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t7 goto L6
	STO (R2+48),R5
	TST R5
	JEZ L6

	# var t8

	# t8 = temp / 70
	LOD R7,(R2+12)
	LOD R8,70
	DIV R7,R8

	# var t9

	# t9 = t8 + 39976
	LOD R9,39976
	ADD R7,R9

	# temp2 = t9

	# output L5
	LOD R10,L5
	LOD R15,R10
	OTS

	# label L6
	STO (R2+16),R7
L6:

	# var t10

	# t10 = (temp == 56422)
	LOD R5,(R2+12)
	LOD R6,56422
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t10 goto L8
	STO (R2+60),R5
	TST R5
	JEZ L8

	# var t11

	# t11 = temp / 39
	LOD R7,(R2+12)
	LOD R8,39
	DIV R7,R8

	# var t12

	# t12 = t11 + 6265
	LOD R9,6265
	ADD R7,R9

	# temp2 = t12

	# output L7
	LOD R10,L7
	LOD R15,R10
	OTS

	# label L8
	STO (R2+16),R7
L8:

	# var t13

	# t13 = (temp == 12188)
	LOD R5,(R2+12)
	LOD R6,12188
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t13 goto L10
	STO (R2+72),R5
	TST R5
	JEZ L10

	# var t14

	# t14 = 13773 * i
	LOD R7,13773
	LOD R8,(R2+8)
	MUL R7,R8

	# var t15

	# t15 = 27266 - t14
	LOD R9,27266
	SUB R9,R7

	# temp2 = t15

	# output L9
	LOD R10,L9
	LOD R15,R10
	OTS

	# label L10
	STO (R2+76),R7
	STO (R2+16),R9
L10:

	# var t16

	# t16 = (temp == 10943)
	LOD R5,(R2+12)
	LOD R6,10943
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t16 goto L12
	STO (R2+84),R5
	TST R5
	JEZ L12

	# var t17

	# t17 = 24538 * i
	LOD R7,24538
	LOD R8,(R2+8)
	MUL R7,R8

	# var t18

	# t18 = temp + t17
	LOD R9,(R2+12)
	ADD R9,R7

	# temp2 = t18

	# output L11
	LOD R10,L11
	LOD R15,R10
	OTS

	# label L12
	STO (R2+88),R7
	STO (R2+16),R9
L12:

	# var t19

	# t19 = (temp == 21140)
	LOD R5,(R2+12)
	LOD R6,21140
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t19 goto L14
	STO (R2+96),R5
	TST R5
	JEZ L14

	# var t20

	# t20 = temp / 18
	LOD R7,(R2+12)
	LOD R8,18
	DIV R7,R8

	# var t21

	# t21 = t20 + 3561
	LOD R9,3561
	ADD R7,R9

	# temp2 = t21

	# output L13
	LOD R10,L13
	LOD R15,R10
	OTS

	# label L14
	STO (R2+16),R7
L14:

	# var t22

	# t22 = (temp == 17810)
	LOD R5,(R2+12)
	LOD R6,17810
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t22 goto L16
	STO (R2+108),R5
	TST R5
	JEZ L16

	# var t23

	# t23 = 62623 * i
	LOD R7,62623
	LOD R8,(R2+8)
	MUL R7,R8

	# var t24

	# t24 = 16198 - t23
	LOD R9,16198
	SUB R9,R7

	# temp2 = t24

	# output L15
	LOD R10,L15
	LOD R15,R10
	OTS

	# label L16
	STO (R2+112),R7
	STO (R2+16),R9
L16:

	# var t25

	# t25 = (temp == 7711)
	LOD R5,(R2+12)
	LOD R6,7711
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t25 goto L18
	STO (R2+120),R5
	TST R5
	JEZ L18

	# var t26

	# t26 = 44131 * i
	LOD R7,44131
	LOD R8,(R2+8)
	MUL R7,R8

	# var t27

	# t27 = temp + t26
	LOD R9,(R2+12)
	ADD R9,R7

	# temp2 = t27

	# output L17
	LOD R10,L17
	LOD R15,R10
	OTS

	# label L18
	STO (R2+124),R7
	STO (R2+16),R9
L18:

	# var t28

	# t28 = (temp == 13607)
	LOD R5,(R2+12)
	LOD R6,13607
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t28 goto L20
	STO (R2+132),R5
	TST R5
	JEZ L20

	# var t29

	# t29 = temp / 47
	LOD R7,(R2+12)
	LOD R8,47
	DIV R7,R8

	# var t30

	# t30 = t29 + 9692
	LOD R9,9692
	ADD R7,R9

	# temp2 = t30

	# output L19
	LOD R10,L19
	LOD R15,R10
	OTS

	# label L20
	STO (R2+16),R7
L20:

	# var t31

	# t31 = (temp == 48141)
	LOD R5,(R2+12)
	LOD R6,48141
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t31 goto L22
	STO (R2+144),R5
	TST R5
	JEZ L22

	# var t32

	# t32 = 55016 * i
	LOD R7,55016
	LOD R8,(R2+8)
	MUL R7,R8

	# var t33

	# t33 = temp + t32
	LOD R9,(R2+12)
	ADD R9,R7

	# temp2 = t33

	# output L21
	LOD R10,L21
	LOD R15,R10
	OTS

	# label L22
	STO (R2+148),R7
	STO (R2+16),R9
L22:

	# var t34

	# t34 = (temp == 11697)
	LOD R5,(R2+12)
	LOD R6,11697
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t34 goto L24
	STO (R2+156),R5
	TST R5
	JEZ L24

	# var t35

	# t35 = 62840 * i
	LOD R7,62840
	LOD R8,(R2+8)
	MUL R7,R8

	# var t36

	# t36 = temp + t35
	LOD R9,(R2+12)
	ADD R9,R7

	# temp2 = t36

	# output L23
	LOD R10,L23
	LOD R15,R10
	OTS

	# label L24
	STO (R2+160),R7
	STO (R2+16),R9
L24:

	# var t37

	# t37 = (temp == 35028)
	LOD R5,(R2+12)
	LOD R6,35028
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t37 goto L26
	STO (R2+168),R5
	TST R5
	JEZ L26

	# var t38

	# t38 = temp / 178
	LOD R7,(R2+12)
	LOD R8,178
	DIV R7,R8

	# var t39

	# t39 = t38 + 18141
	LOD R9,18141
	ADD R7,R9

	# temp2 = t39

	# output L25
	LOD R10,L25
	LOD R15,R10
	OTS

	# label L26
	STO (R2+16),R7
L26:

	# var t40

	# t40 = (temp == 24485)
	LOD R5,(R2+12)
	LOD R6,24485
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t40 goto L28
	STO (R2+180),R5
	TST R5
	JEZ L28

	# var t41

	# t41 = 48033 * i
	LOD R7,48033
	LOD R8,(R2+8)
	MUL R7,R8

	# var t42

	# t42 = temp - t41
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t42

	# output L27
	LOD R10,L27
	LOD R15,R10
	OTS

	# label L28
	STO (R2+184),R7
	STO (R2+16),R9
L28:

	# var t43

	# t43 = (temp == 9981)
	LOD R5,(R2+12)
	LOD R6,9981
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t43 goto L29
	STO (R2+192),R5
	TST R5
	JEZ L29

	# var t44

	# t44 = 161 * i
	LOD R7,161
	LOD R8,(R2+8)
	MUL R7,R8

	# var t45

	# t45 = temp - t44
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t45

	# output L21
	LOD R10,L21
	LOD R15,R10
	OTS

	# label L29
	STO (R2+196),R7
	STO (R2+16),R9
L29:

	# var t46

	# t46 = (temp == 39373)
	LOD R5,(R2+12)
	LOD R6,39373
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t46 goto L31
	STO (R2+204),R5
	TST R5
	JEZ L31

	# var t47

	# t47 = 6776 * i
	LOD R7,6776
	LOD R8,(R2+8)
	MUL R7,R8

	# var t48

	# t48 = temp - t47
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t48

	# output L30
	LOD R10,L30
	LOD R15,R10
	OTS

	# label L31
	STO (R2+208),R7
	STO (R2+16),R9
L31:

	# var t49

	# t49 = (temp == 57509)
	LOD R5,(R2+12)
	LOD R6,57509
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t49 goto L33
	STO (R2+216),R5
	TST R5
	JEZ L33

	# var t50

	# t50 = 17159 * i
	LOD R7,17159
	LOD R8,(R2+8)
	MUL R7,R8

	# var t51

	# t51 = temp - t50
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t51

	# output L32
	LOD R10,L32
	LOD R15,R10
	OTS

	# label L33
	STO (R2+220),R7
	STO (R2+16),R9
L33:

	# var t52

	# t52 = (temp == 51842)
	LOD R5,(R2+12)
	LOD R6,51842
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t52 goto L35
	STO (R2+228),R5
	TST R5
	JEZ L35

	# var t53

	# t53 = temp / 102
	LOD R7,(R2+12)
	LOD R8,102
	DIV R7,R8

	# var t54

	# t54 = t53 + 57001
	LOD R9,57001
	ADD R7,R9

	# temp2 = t54

	# output L34
	LOD R10,L34
	LOD R15,R10
	OTS

	# label L35
	STO (R2+16),R7
L35:

	# var t55

	# t55 = (temp == 40347)
	LOD R5,(R2+12)
	LOD R6,40347
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t55 goto L37
	STO (R2+240),R5
	TST R5
	JEZ L37

	# var t56

	# t56 = 2568 * i
	LOD R7,2568
	LOD R8,(R2+8)
	MUL R7,R8

	# var t57

	# t57 = 54615 - t56
	LOD R9,54615
	SUB R9,R7

	# temp2 = t57

	# output L36
	LOD R10,L36
	LOD R15,R10
	OTS

	# label L37
	STO (R2+244),R7
	STO (R2+16),R9
L37:

	# var t58

	# t58 = (temp == 8854)
	LOD R5,(R2+12)
	LOD R6,8854
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t58 goto L39
	STO (R2+252),R5
	TST R5
	JEZ L39

	# var t59

	# t59 = temp / 50
	LOD R7,(R2+12)
	LOD R8,50
	DIV R7,R8

	# var t60

	# t60 = t59 + 25851
	LOD R9,25851
	ADD R7,R9

	# temp2 = t60

	# output L38
	LOD R10,L38
	LOD R15,R10
	OTS

	# label L39
	STO (R2+16),R7
L39:

	# var t61

	# t61 = (temp == 10116)
	LOD R5,(R2+12)
	LOD R6,10116
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t61 goto L41
	STO (R2+264),R5
	TST R5
	JEZ L41

	# var t62

	# t62 = temp / 53
	LOD R7,(R2+12)
	LOD R8,53
	DIV R7,R8

	# var t63

	# t63 = t62 + 13417
	LOD R9,13417
	ADD R7,R9

	# temp2 = t63

	# output L40
	LOD R10,L40
	LOD R15,R10
	OTS

	# label L41
	STO (R2+16),R7
L41:

	# var t64

	# t64 = (temp == 20947)
	LOD R5,(R2+12)
	LOD R6,20947
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t64 goto L43
	STO (R2+276),R5
	TST R5
	JEZ L43

	# var t65

	# t65 = 43689 * i
	LOD R7,43689
	LOD R8,(R2+8)
	MUL R7,R8

	# var t66

	# t66 = 64044 - t65
	LOD R9,64044
	SUB R9,R7

	# temp2 = t66

	# output L42
	LOD R10,L42
	LOD R15,R10
	OTS

	# label L43
	STO (R2+280),R7
	STO (R2+16),R9
L43:

	# var t67

	# t67 = (temp == 21250)
	LOD R5,(R2+12)
	LOD R6,21250
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t67 goto L45
	STO (R2+288),R5
	TST R5
	JEZ L45

	# var t68

	# t68 = 29723 * i
	LOD R7,29723
	LOD R8,(R2+8)
	MUL R7,R8

	# var t69

	# t69 = temp - t68
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t69

	# output L44
	LOD R10,L44
	LOD R15,R10
	OTS

	# label L45
	STO (R2+292),R7
	STO (R2+16),R9
L45:

	# var t70

	# t70 = (temp == 16416)
	LOD R5,(R2+12)
	LOD R6,16416
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t70 goto L47
	STO (R2+300),R5
	TST R5
	JEZ L47

	# var t71

	# t71 = 41523 * i
	LOD R7,41523
	LOD R8,(R2+8)
	MUL R7,R8

	# var t72

	# t72 = temp - t71
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t72

	# output L46
	LOD R10,L46
	LOD R15,R10
	OTS

	# label L47
	STO (R2+304),R7
	STO (R2+16),R9
L47:

	# var t73

	# t73 = (temp == 13204)
	LOD R5,(R2+12)
	LOD R6,13204
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t73 goto L49
	STO (R2+312),R5
	TST R5
	JEZ L49

	# var t74

	# t74 = temp / 193
	LOD R7,(R2+12)
	LOD R8,193
	DIV R7,R8

	# var t75

	# t75 = t74 + 53788
	LOD R9,53788
	ADD R7,R9

	# temp2 = t75

	# output L48
	LOD R10,L48
	LOD R15,R10
	OTS

	# label L49
	STO (R2+16),R7
L49:

	# var t76

	# t76 = (temp == 47597)
	LOD R5,(R2+12)
	LOD R6,47597
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t76 goto L51
	STO (R2+324),R5
	TST R5
	JEZ L51

	# var t77

	# t77 = 59581 * i
	LOD R7,59581
	LOD R8,(R2+8)
	MUL R7,R8

	# var t78

	# t78 = temp + t77
	LOD R9,(R2+12)
	ADD R9,R7

	# temp2 = t78

	# output L50
	LOD R10,L50
	LOD R15,R10
	OTS

	# label L51
	STO (R2+328),R7
	STO (R2+16),R9
L51:

	# var t79

	# t79 = (temp == 45195)
	LOD R5,(R2+12)
	LOD R6,45195
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t79 goto L53
	STO (R2+336),R5
	TST R5
	JEZ L53

	# var t80

	# t80 = 22361 * i
	LOD R7,22361
	LOD R8,(R2+8)
	MUL R7,R8

	# var t81

	# t81 = temp - t80
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t81

	# output L52
	LOD R10,L52
	LOD R15,R10
	OTS

	# label L53
	STO (R2+340),R7
	STO (R2+16),R9
L53:

	# var t82

	# t82 = (temp == 6032)
	LOD R5,(R2+12)
	LOD R6,6032
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t82 goto L54
	STO (R2+348),R5
	TST R5
	JEZ L54

	# var t83

	# t83 = 1021 * i
	LOD R7,1021
	LOD R8,(R2+8)
	MUL R7,R8

	# var t84

	# t84 = temp + t83
	LOD R9,(R2+12)
	ADD R9,R7

	# temp2 = t84

	# output L21
	LOD R10,L21
	LOD R15,R10
	OTS

	# label L54
	STO (R2+352),R7
	STO (R2+16),R9
L54:

	# var t85

	# t85 = (temp == 17276)
	LOD R5,(R2+12)
	LOD R6,17276
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t85 goto L56
	STO (R2+360),R5
	TST R5
	JEZ L56

	# var t86

	# t86 = 21834 * i
	LOD R7,21834
	LOD R8,(R2+8)
	MUL R7,R8

	# var t87

	# t87 = 18047 - t86
	LOD R9,18047
	SUB R9,R7

	# temp2 = t87

	# output L55
	LOD R10,L55
	LOD R15,R10
	OTS

	# label L56
	STO (R2+364),R7
	STO (R2+16),R9
L56:

	# var t88

	# t88 = (temp == 34923)
	LOD R5,(R2+12)
	LOD R6,34923
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t88 goto L58
	STO (R2+372),R5
	TST R5
	JEZ L58

	# var t89

	# t89 = 32482 * i
	LOD R7,32482
	LOD R8,(R2+8)
	MUL R7,R8

	# var t90

	# t90 = temp - t89
	LOD R9,(R2+12)
	SUB R9,R7

	# temp2 = t90

	# output L57
	LOD R10,L57
	LOD R15,R10
	OTS

	# label L58
	STO (R2+376),R7
	STO (R2+16),R9
L58:

	# temp = temp2
	LOD R5,(R2+16)

	# var t91

	# t91 = i + 1
	LOD R6,(R2+8)
	LOD R7,1
	ADD R6,R7

	# i = t91

	# goto L59
	STO (R2+12),R5
	STO (R2+8),R6
	JMP L59

	# label L60
L60:

	# output L61
	LOD R5,L61
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L61:
	DBS 10,0
L57:
	DBS 103,0
L55:
	DBS 118,0
L52:
	DBS 106,0
L50:
	DBS 119,0
L48:
	DBS 112,0
L46:
	DBS 108,0
L44:
	DBS 116,0
L42:
	DBS 114,0
L40:
	DBS 105,0
L38:
	DBS 102,0
L36:
	DBS 110,0
L34:
	DBS 122,0
L32:
	DBS 101,0
L30:
	DBS 121,0
L27:
	DBS 99,0
L25:
	DBS 111,0
L23:
	DBS 120,0
L21:
	DBS 32,0
L19:
	DBS 115,0
L17:
	DBS 97,0
L15:
	DBS 113,0
L13:
	DBS 98,0
L11:
	DBS 100,0
L9:
	DBS 104,0
L7:
	DBS 109,0
L5:
	DBS 117,0
L3:
	DBS 33,0
L1:
	DBS 107,0
STATIC:
	DBN 0,0
STACK:
