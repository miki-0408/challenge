
# tac list

0x55ce2e2b7e10	label main
0x55ce2e2b7e50	begin
0x55ce2e2b6830	var a
0x55ce2e2b6900	var pa
0x55ce2e2b69d0	var b
0x55ce2e2b6aa0	var c
0x55ce2e2b6b70	var d
0x55ce2e2b6c40	var ptr
0x55ce2e2b6ca0	input a
0x55ce2e2b6ec0	var t0
0x55ce2e2b6f00	t0 = a + 10
0x55ce2e2b6f40	b = t0
0x55ce2e2b7160	var t1
0x55ce2e2b71a0	t1 = b - 20
0x55ce2e2b71e0	c = t1
0x55ce2e2b7400	var t2
0x55ce2e2b7440	t2 = c * 30
0x55ce2e2b7480	d = t2
0x55ce2e2b74e0	output a
0x55ce2e2b7540	output b
0x55ce2e2b75a0	output c
0x55ce2e2b7600	output d
0x55ce2e2b76d0	output L1
0x55ce2e2b77e0	var t3
0x55ce2e2b7820	t3 = &a
0x55ce2e2b7890	pa = t3
0x55ce2e2b7a00	*pa = 111
0x55ce2e2b7a60	output a
0x55ce2e2b7b10	ptr = pa
0x55ce2e2b7c80	*ptr = 222
0x55ce2e2b7ce0	output a
0x55ce2e2b7d40	output L1
0x55ce2e2b7e90	end
