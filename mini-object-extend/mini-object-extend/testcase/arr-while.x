
# tac list

0x560c0f1c19c0	label main
0x560c0f1c1a00	begin
0x560c0f1bf830	var i
0x560c0f1bf900	var j
0x560c0f1bfa70	var arr1
0x560c0f1bfad0	input i
0x560c0f1bfc10	j = 0
0x560c0f1c0990	label L1
0x560c0f1bfe10	var t0
0x560c0f1bfe50	t0 = (j < 10)
0x560c0f1c09d0	ifz t0 goto L2
0x560c0f1bff40	var t1
0x560c0f1bff80	t1 = &arr1
0x560c0f1c02c0	var t3
0x560c0f1c0120	var t2
0x560c0f1c01f0	t2 = j * 4
0x560c0f1c0300	t3 = t1 + t2
0x560c0f1c0340	*t3 = i
0x560c0f1c0560	var t4
0x560c0f1c05a0	t4 = i + 1
0x560c0f1c05e0	i = t4
0x560c0f1c0770	var t5
0x560c0f1c07b0	t5 = j + 1
0x560c0f1c07f0	j = t5
0x560c0f1c0a10	goto L1
0x560c0f1c0a50	label L2
0x560c0f1c0ca0	ifz 0 goto L4
0x560c0f1c0b70	output L3
0x560c0f1c0c60	label L4
0x560c0f1c17d0	label L5
0x560c0f1c0e10	var t6
0x560c0f1c0e50	t6 = (j > 0)
0x560c0f1c1810	ifz t6 goto L6
0x560c0f1c0fe0	var t7
0x560c0f1c1020	t7 = j - 1
0x560c0f1c1060	j = t7
0x560c0f1c1170	var t8
0x560c0f1c11b0	t8 = &arr1
0x560c0f1c1410	var t10
0x560c0f1c1300	var t9
0x560c0f1c1340	t9 = j * 4
0x560c0f1c1450	t10 = t8 + t9
0x560c0f1c1520	var t11
0x560c0f1c1560	t11 = *t10
0x560c0f1c15d0	i = t11
0x560c0f1c1630	output i
0x560c0f1c1850	goto L5
0x560c0f1c1890	label L6
0x560c0f1c18f0	output L3
0x560c0f1c1a40	end
